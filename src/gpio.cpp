#include <DallasTemperature.h>
#include "common/util.h"

#define ONE_WIRE_BUS_E 4 // DS18B20
#define ONE_WIRE_BUS_1 13 // DS18B20
#define ONE_WIRE_BUS_2 14 // DS18B20
#define ONE_WIRE_BUS_3 21 // DS18B20

#define ONE_WIRE_BUS_4 47 // DS18B20

#ifdef ONE_WIRE_BUS_E
OneWire one_wire_E(ONE_WIRE_BUS_E);
DallasTemperature DS18B20_E(&one_wire_E);
#endif

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

double m_tempE = 0;
double m_temp1 = 0;
double m_temp2 = 0;
double m_temp3 = 0;
double m_temp4 = 0;

void setupGpio(){
    DS18B20_E.begin();
    DS18B20_1.begin();
    DS18B20_2.begin();
    DS18B20_3.begin();
    DS18B20_4.begin();

    DS18B20_E.setWaitForConversion(false);
    DS18B20_1.setWaitForConversion(false);
    DS18B20_2.setWaitForConversion(false);
    DS18B20_3.setWaitForConversion(false);
    DS18B20_4.setWaitForConversion(false);
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
    return m_tempE;
}


void readTemperatures(){
    DS18B20_E.requestTemperatures();
    m_tempE = DS18B20_E.getTempCByIndex(0);
    DS18B20_1.requestTemperatures();
    m_temp1 = DS18B20_1.getTempCByIndex(0);
    DS18B20_2.requestTemperatures();
    m_temp2 = DS18B20_2.getTempCByIndex(0);
    DS18B20_3.requestTemperatures();
    m_temp3 = DS18B20_3.getTempCByIndex(0);
    //DS18B20_4.requestTemperatures();
    //m_temp4 = DS18B20_4.getTempCByIndex(0);
    lc_DebugPrint("te %.1f, t1 %.1f, t2 %.1f, t3 %.1f, t4 %.1f\n",m_tempE, m_temp1, m_temp2, m_temp3, m_temp4);
    
}