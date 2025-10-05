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
    if(!m_init){
        if(i > 3000){
            printConfig();
            parserInit();
            m_init = true;
        }
    }

    int i_s2 = i/100;
    if(i_s2 != m_last_s2){
        m_last_s2 = i_s2;
        loopSilo(i);
    }

    int i_s = i/1000;
    if(i_s != m_last_s){
        m_last_s = i_s;
        nextionUpdateS();
        //lc_DebugPrint("loop %i\n",m_last_s);
        if(i_s%10 == 0){
            //loopWifi();
        }
    }
    
    while (Serial2.available()){ //Is data coming through the serial from the Nextion?
        int i = Serial2.read();
        readNChar(i);
    }
}


/*SoftwareSerial nextionSerial(D5, D6); // RX, TX
    Nextion nex(nextionSerial);
    uint32_t number;
    nex.sendCommand("get rtc0");
    nex.receiveNumber(&number));
    Serial.println(" >> number: " + String(number));
prints n0.val,2
prints n0.id,1*/