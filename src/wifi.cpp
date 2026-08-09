#include "wifi.hpp"
#include "common/util.h"
#include "lemca_config.h"
#include "gpio.hpp"
#include "led.hpp"

#include <WiFiClientSecure.h>
#include <HTTPClient.h>

const char * host = "maplaine.fr";
const uint16_t port = 443;

enum WifiStatus {
    WIFI_INIT = 0,
    WIFI_WARNING = 1,
    WIFI_ERROR = 2
};

class Wifi {
public :
    String m_last_resp;
    char m_debug[100];

    WiFiClientSecure client;
    HTTPClient https;

    int m_error_wifi = 300;
    bool m_was_send = false;

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
        if(m_error_wifi > 30){
            m_error_wifi = 0;
            WiFi.disconnect();
            client.setInsecure();
            WiFi.begin(getWifiSsid(), getWifiPass());
            sprintf(m_debug, "%i - init wifi", i_s);
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
        IPAddress ip = WiFi.localIP();
        sprintf(m_debug, "%i %i - ip %d.%d.%d.%d ", i_s, getWifiS(), ip[0], ip[1], ip[2], ip[3]);
        lc_DebugPrintBuffer(m_debug);

        if(i_s%getWifiS() == 0 || !m_was_send){
            char path[200];
            sprintf(path, "/silo/api_sonde?company=%s&balise=%s&te=%.1f&t1=%.1f&t2=%.1f&t3=%.1f&t4=%.1f&t5=%.1f&t6=%.1f&t7=%.1f&t8=%.1f&t9=%.1f", getCompany(), getBalise(), getTemperatureTE(), getTemperatureT1(), getTemperatureT2(), getTemperatureT3(), getTemperatureT4(), getTemperatureT5(), getTemperatureT6(), getTemperatureT7(), getTemperatureT8(), getTemperatureT9() );
           
            lc_DebugPrintBuffer(m_debug);
            lc_DebugPrintBuffer(path);



            if (https.begin(client, host, port, path)) {
                int httpsCode = https.GET();
                if (httpsCode > 0 && httpsCode == HTTP_CODE_OK) {
                    m_last_resp = https.getString();
                    Serial.println(" => ");
                    Serial.println(m_last_resp);
                    m_was_send = true;

                    setOkWifi();
                    m_error_wifi = 0;
                } else {
                    m_last_resp = "fail get";
                    Serial.println(" => ");
                    Serial.print("failed to GET ");
                    Serial.print(httpsCode);
                    Serial.println("");

                    setWarningWifi(1);
                    m_error_wifi++;
                }
            } else {
                m_last_resp = "fail server";
                Serial.println(" => ");
                Serial.print("failed to connect to server\n");
                
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