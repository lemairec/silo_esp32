#include <FastLED.h>
#include "common/util.h"

#define LED_PIN     5
#define NUM_LEDS    1

CRGB leds[NUM_LEDS];

int m_led_error = 0;

enum LED_COLOR {
    LED_OFF = 0,
    LED_BLUE = 1,
    LED_GREEN = 2,
    LED_RED = 3
};
enum STATE {
    STATE_NOT_INIT = 0,
    STATE_WAITING = 1,
    STATE_ERROR = 2,
    STATE_WARNING = 3,
    STATE_OK = 4,
}; 

STATE m_state = STATE_NOT_INIT;
int m_error = 0;

void setLedStateWaiting() {
    m_state = STATE_WAITING;
}
void setLedStateOk() {
    m_state = STATE_OK;
}
void setLedStateError(int error) {
    m_state = STATE_ERROR;
    m_error = error;
}
void setLedStateWarning(int error) {
    m_state = STATE_WARNING;
    m_error = error;
}

void initLed() {
  FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(50);
  leds[0] = CRGB::Blue;
  FastLED.show();
  lc_DebugPrint("initLed end\n");
}



int i = 0;
void loopLed100ms(int millis){
    if(m_state == STATE_NOT_INIT){
        if(i == 0){
            leds[0] = CRGB::Blue;
        }else if(i == 1){
            leds[0] = CRGB::Green;
        }else if(i == 2){
            leds[0] = CRGB::Red;
        }else if(i == 4){
            leds[0] = CRGB::Black;
        } else {
            i = -1;
        }
    } else if(m_state == STATE_WAITING){
        if(i == 0){
            leds[0] = CRGB::Orange;
        }else if(i < 50){
            leds[0] = CRGB::Black;
        } else {
            i = -1;
        }
    } else if(m_state == STATE_OK){
        if(i == 0){
            leds[0] = CRGB::Green;
        }else if(i < 50){
            leds[0] = CRGB::Black;
        } else {
            i = -1;
        }
    } else if(m_state == STATE_ERROR){
        if(i < m_error * 4){
            if(i % 4 == 0){
                leds[0] = CRGB::Red;
            } else {
                leds[0] = CRGB::Black;
            }
        } else if(i < 50){
            leds[0] = CRGB::Black;
        } else {
            i = -1;
        }
    } else if(m_state == STATE_WARNING){
        if(i < m_error * 4){
            if(i % 4 == 0){
                leds[0] = CRGB::Yellow;
            } else {
                leds[0] = CRGB::Black;
            }
        } else if(i < 50){
            leds[0] = CRGB::Black;
        } else {
            i = -1;
        }
    }else {
        leds[0] = CRGB::Black;
    }
    FastLED.show();
    i++;
}