#include <DallasTemperature.h>
#include "common/util.h"

#define ONE_WIRE_BUS_1 13 // DS18B20
#define ONE_WIRE_BUS_2 14 // DS18B20
#define ONE_WIRE_BUS_3 21 // DS18B20

#define ONE_WIRE_BUS_4 47 // DS18B20


#define RELAI_1 45
#define RELAI_2 48
#define RELAI_3 12
#define RELAI_4 11
#define RELAI_5 10
#define RELAI_6 9
#define RELAI_7 46
#define RELAI_8 3


#ifdef ONE_WIRE_BUS_1
OneWire one_wire_1(ONE_WIRE_BUS_1);
DallasTemperature DS18B20_1(&one_wire_1);
#endif

#ifdef ONE_WIRE_BUS_2
OneWire one_wire_2(ONE_WIRE_BUS_2);
DallasTemperature DS18B20_2(&one_wire_2);
#endif

#ifdef ONE_WIRE_BUS_3
OneWire one_wire_3(ONE_WIRE_BUS_3);
DallasTemperature DS18B20_3(&one_wire_3);
#endif

#ifdef ONE_WIRE_BUS_4
OneWire one_wire_4(ONE_WIRE_BUS_4);
DallasTemperature DS18B20_4(&one_wire_4);
#endif

double m_temp1 = 0;
double m_temp2 = 0;
double m_temp3 = 0;
double m_temp4 = 0;

void setupGpio(){
    DS18B20_1.begin();
    DS18B20_2.begin();
    DS18B20_3.begin();
    DS18B20_4.begin();

    DS18B20_1.setWaitForConversion(false);
    DS18B20_2.setWaitForConversion(false);
    DS18B20_3.setWaitForConversion(false);
    DS18B20_4.setWaitForConversion(false);

    pinMode(RELAI_1, OUTPUT);
    pinMode(RELAI_2, OUTPUT);
    pinMode(RELAI_3, OUTPUT);
    pinMode(RELAI_4, OUTPUT);
    pinMode(RELAI_5, OUTPUT);
    pinMode(RELAI_6, OUTPUT);
    pinMode(RELAI_7, OUTPUT);
    pinMode(RELAI_8, OUTPUT);
    
}

double getTemperatureT1(){
    return m_temp1;
}

double getTemperatureT2(){
    return m_temp2;
}

double getTemperatureT3(){
    return m_temp3;
}

double getTemperatureTE(){
    return m_temp4;
}

void setMAirFroid(int value){
    //lc_DebugPrint("setMAirFroid %i\n", value);
    if(value > 0){
        digitalWrite(RELAI_1, HIGH);
    } else {
        digitalWrite(RELAI_1, LOW);
    }
}

void setMAirChaud(int value){
    //lc_DebugPrint("setMAirChaud %i\n", value);
    if(value > 0){
        digitalWrite(RELAI_2, HIGH);
    } else {
        digitalWrite(RELAI_2, LOW);
    }
}

void setMoteurHyd(int value){
    //lc_DebugPrint("setMAirChaud %i\n", value);
    if(value > 0){
        digitalWrite(RELAI_3, HIGH);
    } else {
        digitalWrite(RELAI_3, LOW);
    }
}

void setTrappe1(int value){
    //lc_DebugPrint("setMAirChaud %i\n", value);
    if(value > 0){
        digitalWrite(RELAI_5, HIGH);
    } else {
        digitalWrite(RELAI_5, LOW);
    }
}

void setTrappe2(int value){
    //lc_DebugPrint("setMAirChaud %i\n", value);
    if(value > 0){
        digitalWrite(RELAI_6, HIGH);
    } else {
        digitalWrite(RELAI_6, LOW);
    }
}

void setBruleurGpio(int value){
    //lc_DebugPrint("setMAirChaud %i\n", value);
    if(value > 0){
        digitalWrite(RELAI_4, HIGH);
    } else {
        digitalWrite(RELAI_4, LOW);
    }
}

void setAllure1(int value){
    //lc_DebugPrint("setMAirChaud %i\n", value);
    if(value > 0){
        digitalWrite(RELAI_7, HIGH);
    } else {
        digitalWrite(RELAI_7, LOW);
    }
}

void setAllure2(int value){
    //lc_DebugPrint("setMAirChaud %i\n", value);
    if(value > 0){
        digitalWrite(RELAI_8, HIGH);
    } else {
        digitalWrite(RELAI_8, LOW);
    }
}

void readTemperatures(){
    DS18B20_1.requestTemperatures();
    m_temp1 = DS18B20_1.getTempCByIndex(0);
    DS18B20_2.requestTemperatures();
    m_temp2 = DS18B20_2.getTempCByIndex(0);
    DS18B20_3.requestTemperatures();
    m_temp3 = DS18B20_3.getTempCByIndex(0);
    //DS18B20_4.requestTemperatures();
    //m_temp4 = DS18B20_4.getTempCByIndex(0);
    //lc_DebugPrint("t1 %.1f, t2 %.1f, t3 %.1f, t4 %.1f\n",m_temp1, m_temp2, m_temp3, m_temp4);
    
}