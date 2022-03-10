#include <FastLED.h>
#define LED_PIN     5
#define LED_PIN2    4

#define NUM_LEDS    150
#define NUM_LEDS2   150

CRGB leds[NUM_LEDS];
CRGB leds2[NUM_LEDS2];

void setup() {
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.addLeds<WS2812, LED_PIN2, GRB>(leds, NUM_LEDS2).setCorrection( TypicalLEDStrip );
}
void loop() {
  for (int i = 0; i <= 19; i++) {
    leds[i] = CRGB ( 0, 255, 255);
    FastLED.show();
    delay(40);
  }
  for (int i = 0; i <= 19; i++) {
    leds2[i] = CRGB ( 0, 255, 255);
    FastLED.show();
    delay(40);
  }
  
  for (int i = 19; i >= 0; i--) {
    leds[i] = CRGB ( 255, 255, 0);
    FastLED.show();
    delay(40);
  }
  for (int i = 19; i >= 0; i--) {
    leds2[i] = CRGB ( 255, 255, 0);
    FastLED.show();
    delay(40);
  }
  
}
