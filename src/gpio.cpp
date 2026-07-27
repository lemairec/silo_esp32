#include <DallasTemperature.h>
#include "common/util.h"

#define ONE_WIRE_BUS_E 4 // DS18B20
#define ONE_WIRE_BUS_1 19 // DS18B20
#define ONE_WIRE_BUS_2 20 // DS18B20
#define ONE_WIRE_BUS_3 21 // DS18B20

#define ONE_WIRE_BUS_4 11 // DS18B20
#define ONE_WIRE_BUS_5 10 // DS18B20
#define ONE_WIRE_BUS_6 9 // DS18B20

#define ONE_WIRE_BUS_7 15 // DS18B20
#define ONE_WIRE_BUS_8 7 // DS18B20
#define ONE_WIRE_BUS_9 6 // DS18B20

/*#define ONE_WIRE_BUS_4 14 // DS18B20
#define ONE_WIRE_BUS_5 13 // DS18B20
#define ONE_WIRE_BUS_6 12 // DS18B20
#define ONE_WIRE_BUS_7 11 // DS18B20
#define ONE_WIRE_BUS_8 10 // DS18B20
#define ONE_WIRE_BUS_9 9 // DS18B20
#define ONE_WIRE_BUS_10 18 // DS18B20
#define ONE_WIRE_BUS_11 17 // DS18B20
#define ONE_WIRE_BUS_12 16 // DS18B20
#define ONE_WIRE_BUS_13 15 // DS18B20
#define ONE_WIRE_BUS_14 7 // DS18B20
#define ONE_WIRE_BUS_15 6 // DS18B20
#define ONE_WIRE_BUS_16 5 // DS18B20*/

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

#ifdef ONE_WIRE_BUS_5
OneWire one_wire_5(ONE_WIRE_BUS_5);
DallasTemperature DS18B20_5(&one_wire_5);
#endif

#ifdef ONE_WIRE_BUS_6
OneWire one_wire_6(ONE_WIRE_BUS_6);
DallasTemperature DS18B20_6(&one_wire_6);
#endif

#ifdef ONE_WIRE_BUS_7
OneWire one_wire_7(ONE_WIRE_BUS_7);
DallasTemperature DS18B20_7(&one_wire_7);
#endif

#ifdef ONE_WIRE_BUS_8
OneWire one_wire_8(ONE_WIRE_BUS_8);
DallasTemperature DS18B20_8(&one_wire_8);
#endif

#ifdef ONE_WIRE_BUS_9
OneWire one_wire_9(ONE_WIRE_BUS_9);
DallasTemperature DS18B20_9(&one_wire_9);
#endif



double m_tempE = 0;
double m_temp1 = 0;
double m_temp2 = 0;
double m_temp3 = 0;
double m_temp4 = 0;
double m_temp5 = 0;
double m_temp6 = 0;
double m_temp7 = 0;
double m_temp8 = 0;
double m_temp9 = 0;

void setupGpio(){
    DS18B20_E.begin();
    DS18B20_1.begin();
    DS18B20_2.begin();
    DS18B20_3.begin();
    DS18B20_4.begin();
    DS18B20_5.begin();
    DS18B20_6.begin();
    DS18B20_7.begin();
    DS18B20_8.begin();
    DS18B20_9.begin();

    DS18B20_E.setWaitForConversion(false);
    DS18B20_1.setWaitForConversion(false);
    DS18B20_2.setWaitForConversion(false);
    DS18B20_3.setWaitForConversion(false);
    DS18B20_4.setWaitForConversion(false);
    DS18B20_5.setWaitForConversion(false);
    DS18B20_6.setWaitForConversion(false);
    DS18B20_7.setWaitForConversion(false);
    DS18B20_8.setWaitForConversion(false);
    DS18B20_9.setWaitForConversion(false);
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


double getTemperatureT4(){
    return m_temp4;
}
double getTemperatureT5(){
    return m_temp5;
}
double getTemperatureT6(){
    return m_temp6;
}
double getTemperatureT7(){
    return m_temp7;
}
double getTemperatureT8(){
    return m_temp8;
}
double getTemperatureT9(){
    return m_temp9;
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
    DS18B20_4.requestTemperatures();
    m_temp4 = DS18B20_4.getTempCByIndex(0);
    DS18B20_5.requestTemperatures();
    m_temp5 = DS18B20_5.getTempCByIndex(0);
    DS18B20_6.requestTemperatures();
    m_temp6 = DS18B20_6.getTempCByIndex(0);
    DS18B20_7.requestTemperatures();
    m_temp7 = DS18B20_7.getTempCByIndex(0);
    DS18B20_8.requestTemperatures();
    m_temp8 = DS18B20_8.getTempCByIndex(0);
    DS18B20_9.requestTemperatures();
    m_temp9 = DS18B20_9.getTempCByIndex(0);
    lc_DebugPrint("te %.1f, t1 %.1f, t2 %.1f, t3 %.1f, t4 %.1f, t5 %.1f, t6 %.1f, t7 %.1f, t8 %.1f, t9 %.1f\n",m_tempE, m_temp1, m_temp2, m_temp3, m_temp4, m_temp5, m_temp6, m_temp7, m_temp8, m_temp9);
    
}