#include <FastLED.h>
#include "common/util.h"

#define LED_PIN     5
#define NUM_LEDS    1

CRGB leds[NUM_LEDS];

int m_led_error = 0;

void initLed() {
  FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(50);
  leds[0] = CRGB::Blue;
  FastLED.show();
  lc_DebugPrint("initLed end\n");
}

void loopLed100ms(int millis){
    leds[0] = CRGB::Red;     // Erreur
    FastLED.show();
    //lc_DebugPrint("%i loopLed100ms\n", millis);
}