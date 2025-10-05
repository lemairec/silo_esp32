#ifndef GPIO_H
#define GPIO_H

void setupGpio();

void readTemperatures();

double getTemperatureT1();
double getTemperatureT2();
double getTemperatureT3();
double getTemperatureTE();

void setMAirFroid(int value);
void setMAirChaud(int value);
void setMoteurHyd(int value);
void setTrappe1(int value);
void setTrappe2(int value);
void setBruleurGpio(int value);
void setAllure1(int value);
void setAllure2(int value);

#endif