#ifndef LED
#define LED

#define COLOR_BLUE 0
#define COLOR_GREEN 1

void initLed();

void setLedStateWaiting();
void setLedStateOk();
void setLedStateError(int error);
void setLedStateWarning(int error);

void loopLed100ms(int millis);

#endif