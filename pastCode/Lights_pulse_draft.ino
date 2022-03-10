#include <FastLED.h>

#define LED_PIN     5
#define LED_PIN2    4
#define NUM_LEDS    150
#define NUM_LEDS2   150
#define BRIGHTNESS  64
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB

CRGB leds[NUM_LEDS];
CRGB leds2[NUM_LEDS2];


#define UPDATES_PER_SECOND 100

CRGBPalette16 currentPalette;
TBlendType    currentBlending;

extern CRGBPalette16 myRedWhiteBluePalette;
extern const TProgmemPalette16 myRedWhiteBluePalette_p PROGMEM;




     

void FillLEDsFromPaletteColors( uint8_t colorIndex)
{
    uint8_t brightness = 255;
    
    for( int i = 0; i < NUM_LEDS; i++) {
        leds[i] = ColorFromPalette( currentPalette, colorIndex, brightness, currentBlending);
        colorIndex += 3;
    }
    for( int i = 0; i < NUM_LEDS2; i++) {
        leds2[i] = ColorFromPalette( currentPalette, colorIndex, brightness, currentBlending);
        colorIndex += 3;
    }
}

void SendLightPulse(){
     unsigned long startWait = millis();
     while (millis()-startWait<100){
     for(int dot = 0; dot < NUM_LEDS; dot++) { 
            leds[dot] = CRGB::Red;
            FastLED.show();
            leds[dot-1] = CRGB::Red;
            FastLED.show();
            // clear this led for the next time around the loop
            leds[dot] = RainbowColors_p;
            leds[dot-1] = RainbowColors_p;
            delay(30);
        }
    }
}

void SendLightPulse2(){
     unsigned long startWait = millis();
     while (millis()-startWait<100){
     for(int dot = 0; dot < NUM_LEDS2; dot++) { 
            leds2[dot] = CRGB::Blue;
            FastLED.show();
            leds2[dot-1] = CRGB::Blue;
            FastLED.show();
            // clear this led for the next time around the loop
            leds[dot] = RainbowColors_p;
            leds[dot-1] = RainbowColors_p;
            delay(30);
        }
    }
}


void setup() {
    delay( 3000 ); // power-up safety delay
    FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
    FastLED.addLeds<LED_TYPE, LED_PIN2, COLOR_ORDER>(leds2, NUM_LEDS2).setCorrection( TypicalLEDStrip );
    FastLED.setBrightness(  BRIGHTNESS );
    
    currentPalette = RainbowColors_p;
    currentBlending = LINEARBLEND;

    pinMode(A0, INPUT);
    Serial.begin(9600);
}

void loop()
{
    int x = analogRead(A0);
    Serial.println(x);
    unsigned long startWait = millis();
    while (millis()-startWait<100){
      if (x > 400) {
      SendLightPulse();
      SendLightPulse2();
      
      FastLED.show();
      FastLED.delay(1000 / UPDATES_PER_SECOND);
      }
      else {
        static uint8_t startIndex = 0;
      FillLEDsFromPaletteColors(startIndex);
      }
      }
      
     
      
      
}
    
