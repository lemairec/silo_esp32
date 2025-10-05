#include "wifi.hpp"
#include "common/util.h"

#include <WiFiClientSecure.h>
#include <HTTPClient.h>

//const char *ssid = "ferme_lemaire";
//const char *pass = "lejard02";
const char *ssid = "Livebox-lemaire";
const char *pass = "lejard54";
const char * host = "maplaine.fr";
const uint16_t port = 443;

String company = "dizy";
String balise = "test";



class Wifi {
public :
    String m_last_resp;
    char m_debug[100];

    WiFiClientSecure client;
    HTTPClient https;

    int m_error_wifi = 300;
    
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

    void loopWifi2(int i_s){
        if(i_s < 5){
            return;
        }
        if(m_error_wifi > 30){
            m_error_wifi = 0;
            WiFi.disconnect();
            client.setInsecure();
            WiFi.begin(ssid, pass);
            sprintf(m_debug, "%i - init wifi", i_s);
            lc_DebugPrintBuffer(m_debug);
            return;
        }

        wl_status_t status = WiFi.status();
        if(status != WL_CONNECTED){
            sprintf(m_debug, "%i - error %i %s", i_s, m_error_wifi, wl_status_to_string(status));
            lc_DebugPrintBuffer(m_debug);
            m_error_wifi++;
            return;
        }
        IPAddress ip = WiFi.localIP();
        sprintf(m_debug, "%i - ip %d.%d.%d.%d ", i_s, ip[0], ip[1], ip[2], ip[3]);
        lc_DebugPrintBuffer(m_debug);

        
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
