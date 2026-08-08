#ifndef LED
#define LED

#define COLOR_BLUE 0
#define COLOR_GREEN 1

void initLed();

void ledSetError(int i);

void loopLed100ms(int millis);

#endif