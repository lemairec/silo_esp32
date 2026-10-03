#include "wifi.hpp"
#include "common/util.h"
#include "lemca_config.h"
#include "gpio.hpp"
#include "led.hpp"

#include <WiFiClientSecure.h>
#include <HTTPClient.h>
#include <cstring>

const char * host = "maplaine.fr";
const uint16_t port = 443;

int getScoreWifiDb(int db){
    if (db <= -100) {
        return 0;
    } else if (db >= -50) {
        return 10;
    } else {
        return (db + 100) / 5;
    }
}

enum WifiStatus {
    WIFI_INIT = 0,
    WIFI_WARNING = 1,
    WIFI_ERROR = 2
};

// Scans for `ssid` and picks the AP with the strongest RSSI when several
// access points share the same SSID, so we can pin the connection to it
// instead of letting the radio pick (and roam away from) an arbitrary one.
bool logScanRssi(const char * ssid, uint8_t * out_bssid, int32_t * out_channel) {
    int n = WiFi.scanNetworks();
    char buf[100];
    bool found = false;
    int best_rssi = -1000;
    int best_index = -1;
    for (int i = 0; i < n; i++) {
        int db = WiFi.RSSI(i);
        sprintf(buf, "scan - rssi %s : %d dBm => %i", WiFi.SSID(i).c_str(), db, getScoreWifiDb(db));
        lc_DebugPrintBuffer(buf);
        if (WiFi.SSID(i) == ssid) {
            found = true;
            if (db > best_rssi) {
                best_rssi = db;
                best_index = i;
            }
        }
    }
    if (!found) {
        sprintf(buf, "scan - ssid %s not found (%d networks seen)", ssid, n);
        lc_DebugPrintBuffer(buf);
    } else if (best_index >= 0) {
        uint8_t * bssid = WiFi.BSSID(best_index);
        memcpy(out_bssid, bssid, 6);
        *out_channel = WiFi.channel(best_index);
        sprintf(buf, "scan - best AP for %s : %02X:%02X:%02X:%02X:%02X:%02X ch%d %d dBm",
                ssid, bssid[0], bssid[1], bssid[2], bssid[3], bssid[4], bssid[5], (int)*out_channel, best_rssi);
        lc_DebugPrintBuffer(buf);
    }
    WiFi.scanDelete();
    return found && best_index >= 0;
}

void onWifiEvent(WiFiEvent_t event, WiFiEventInfo_t info) {
    if (event == ARDUINO_EVENT_WIFI_STA_DISCONNECTED) {
        char buf[100];
        uint8_t reason = info.wifi_sta_disconnected.reason;
        sprintf(buf, "wifi disconnect reason %u %s", reason, WiFi.disconnectReasonName((wifi_err_reason_t)reason));
        lc_DebugPrintBuffer(buf);
    }
}

class Wifi {
public :
    String m_last_resp;
    char m_debug[100];

    WiFiClientSecure client;
    HTTPClient https;

    int m_error_wifi = 300;
    int m_reconnect_attempts = 0;
    bool m_was_send = false;
    bool m_event_registered = false;
    uint8_t m_best_bssid[6] = {0};
    int32_t m_best_channel = 0;

    // Exponential backoff on reconnect attempts (30, 60, 120, ... capped),
    // so a dead link doesn't retry association at a fixed, wasteful rate.
    int getReconnectThreshold() {
        const int base = 30;
        const int max_threshold = 480;
        int threshold = base << min(m_reconnect_attempts, 4);
        return min(threshold, max_threshold);
    }

    const char * wl_status_to_string(wl_status_t status) {
        switch (status) {
            case WL_NO_SHIELD: return "WL_NO_SHIELD";
            case WL_IDLE_STATUS: return "WL_IDLE_STATUS";
            case WL_NO_SSID_AVAIL: return "WL_NO_SSID_AVAIL";
            case WL_SCAN_COMPLETED: return "WL_SCAN_COMPLETED";
            case WL_CONNECTED: return "WL_CONNECTED";
            case WL_CONNECT_FAILED: return "WL_CONNECT_FAILED";
            case WL_CONNECTION_LOST: return "WL_CONNECTION_LOST";
            case WL_DISCONNECTED: return "WL_DISCONNECTED";
        }
        return "WL_ERROR";
    }

    void setErrorWifi(int error){
        setLedStateError(error);
    }

    void setWarningWifi(int error){
        setLedStateWarning(error);
    }

    void setOkWifi(){
        setLedStateOk();
    }

    void loopWifi2(int i_s){
        if(i_s < 5){
            return;
        }
        if(m_error_wifi > getReconnectThreshold()){
            m_error_wifi = 0;
            m_reconnect_attempts++;
            if(!m_event_registered){
                m_event_registered = true;
                WiFi.onEvent(onWifiEvent);
            }
            WiFi.disconnect();
            WiFi.setSleep(false);
            WiFi.setTxPower(WIFI_POWER_19_5dBm);
            bool has_best_ap = logScanRssi(getWifiSsid(), m_best_bssid, &m_best_channel);
            client.setInsecure();
            if(has_best_ap){
                WiFi.begin(getWifiSsid(), getWifiPass(), m_best_channel, m_best_bssid);
            } else {
                WiFi.begin(getWifiSsid(), getWifiPass());
            }
            sprintf(m_debug, "%i - init wifi (attempt %i, next retry after %i)", i_s, m_reconnect_attempts, getReconnectThreshold());
            lc_DebugPrintBuffer(m_debug);
            return;
        }

        wl_status_t status = WiFi.status();
        if(status != WL_CONNECTED){
            setErrorWifi(1);
            sprintf(m_debug, "%i - error %i %s", i_s, m_error_wifi, wl_status_to_string(status));
            lc_DebugPrintBuffer(m_debug);
            m_error_wifi++;
            return;
        }
        m_reconnect_attempts = 0;
        IPAddress ip = WiFi.localIP();
        int db = WiFi.RSSI();
        sprintf(m_debug, "%i %i - ip %d.%d.%d.%d rssi %d dBm => %i", i_s, -db, ip[0], ip[1], ip[2], ip[3], db, db);
        lc_DebugPrintBuffer(m_debug);

        if(i_s%getWifiS() == 0 || !m_was_send){
            char path[200];
            sprintf(path, "/silo/api_sonde?company=%s&balise=%s&v=%s&wifi=%d&te=%.1f&t1=%.1f&t2=%.1f&t3=%.1f&t4=%.1f&t5=%.1f&t6=%.1f&t7=%.1f&t8=%.1f&t9=%.1f&t10=%.1f&t11=%.1f&t12=%.1f", getCompany(), getBalise(), getVersion(), db, getTemperatureTE(), getTemperatureT1(), getTemperatureT2(), getTemperatureT3(), getTemperatureT4(), getTemperatureT5(), getTemperatureT6(), getTemperatureT7(), getTemperatureT8(), getTemperatureT9(), getTemperatureT10(), getTemperatureT11(), getTemperatureT12() );
           
            lc_DebugPrintBuffer(m_debug);
            lc_DebugPrintBuffer(path);



            if (https.begin(client, host, port, path)) {
                int httpsCode = https.GET();
                if (httpsCode > 0 && httpsCode == HTTP_CODE_OK) {
                    m_last_resp = https.getString();
                    Serial.println(" => ");
                    Serial.println(m_last_resp);
                    m_was_send = true;

                    sprintf(m_debug, "%i %i - get OK %i", i_s, getWifiS(), httpsCode);
                    setOkWifi();
                    m_error_wifi = 0;
                } else {
                    m_last_resp = "fail get";
                    Serial.println(" => ");
                    Serial.print("failed to GET ");
                    Serial.print(httpsCode);
                    Serial.println("");

                    sprintf(m_debug, "%i %i - get Fail %i", i_s, getWifiS(), httpsCode);
                    setWarningWifi(1);
                    m_error_wifi++;
                }
            } else {
                m_last_resp = "fail server";
                Serial.println(" => ");
                Serial.print("failed to connect to server\n");
                
                sprintf(m_debug, "%i %i - fail_server", i_s, getWifiS());
                setWarningWifi(2);
                m_error_wifi++;
            }
            
        }
    };
};

Wifi m_wifi;

void loopWifi(int i_s){
    m_wifi.loopWifi2(i_s);
}

const char * getWifiDebugStr(){
    return m_wifi.m_debug;
}

const char * getWifiLastRespStr(){
    return m_wifi.m_last_resp.c_str();
}