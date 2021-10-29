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
static uint8_t startIndex;
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
     int pulseWidth = 5;
     CRGB prev[pulseWidth], prev2[pulseWidth];
     
     unsigned long startWait = millis();
     while (millis()-startWait<100){
     for(int dot = 0; dot < NUM_LEDS; dot++) { 
      for(int c = 0; c < 5; c++) {
            CRGB prev[c] = leds[dot+c];
            CRGB prev2[c] = leds2[dot+c];
            leds[dot+c] = CRGB(255, 150, 0);
            leds2[dot+c] = CRGB(255, 150, 0);
            //FastLED.show();
            // clear this led for the next time around the loop
            //delay(30);
        }
       FastLED.show();
        for(int c = 0; c < 5; c++) {
            leds[dot+c] = prev[c];
            Serial.print(leds[dot+c]);
            leds2[dot+c] = prev2[c];
         }
       FastLED.show();   
     }
    }
}




void setup() {
    delay( 3000 ); // power-up safety delay
    FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
    FastLED.addLeds<LED_TYPE, LED_PIN2, COLOR_ORDER>(leds2, NUM_LEDS2).setCorrection( TypicalLEDStrip );
    FastLED.setBrightness(  BRIGHTNESS );

    CRGB yellow = CRGB(255, 0, 103); 
    CRGB white = CRGB(255, 30, 130); 
    CRGB red = CRGB(200, 0, 2); 
    CRGB orange = CRGB(255, 0, 60); 
    CRGB green = CRGB(0, 0, 255);
    CRGB purple = CRGB(255, 255, 0);
    
    currentPalette = CRGBPalette16(white, white, red, red, yellow, yellow, green, orange, orange, orange, red, orange, yellow, yellow, orange, red);
    currentBlending = LINEARBLEND;

    startIndex = 0;
    pinMode(A0, INPUT);
    Serial.begin(9600);
}

void loop()
{
   int x = analogRead(A0);
    //Serial.println(x);
    FillLEDsFromPaletteColors(startIndex);
    unsigned long startWait = millis();
      if (x > 400) {
        SendLightPulse();
      }
      else{
      FillLEDsFromPaletteColors(startIndex);
      FastLED.show();
      FastLED.delay(1000 / UPDATES_PER_SECOND);
      }
    startIndex = startIndex +1;
   }
    /*
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
      */
     /*for(int dot = 0; dot < NUM_LEDS; dot++) { */
      /*
      key: first is red, middle is blue, last is green: RBG
      */
          /*  leds[dot] = CRGB(0, 0, 255) ;
            leds2[dot] = CRGB(50, 0, 255);
            
            FastLED.show();
            // clear this led for the next time around the loop
            //leds[dot] = RainbowColors_p;
            //leds[dot-1] = RainbowColors_p;
            //delay(30);
        }*/
     
      
      
