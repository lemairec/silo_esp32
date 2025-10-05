#include <Arduino.h>
#include "common/util.h"
#include "wifi.hpp"
#include "gpio.hpp"

TaskHandle_t Task1;

int m_last_wifi_s = 0;
void taskLoop( void *  params){
    for(;;) {
        int i = millis();
        int i_s = i/1000;
        if(i_s != m_last_wifi_s){
            //lc_DebugPrint("loop_wifi %i\n",m_last_wifi_s);
            loopWifi(i_s);
            m_last_wifi_s = i_s;
        }
    }
}

void setup(){
    Serial.begin(115200);
    Serial.println("setup_silo");
    Serial.println("setup_silo end");
    setupGpio();

    xTaskCreatePinnedToCore(
        taskLoop, /* Function to implement the task */
        "Task1", /* Name of the task */
        10000,  /* Stack size in words */
        NULL,  /* Task input parameter */
        0,  /* Priority of the task */
        &Task1,  /* Task handle. */
        0); /* Core where the task should run */
    
    lc_DebugPrint("setup end");
}

int m_last_s2 = 0;
int m_last_s = 0;
bool m_init = false;

void loop(void) {
    int i = millis();

    int i_s2 = i/100;
    if(i_s2 != m_last_s2){
        m_last_s2 = i_s2;
        //loopSechoir(i);
    }
}
