#include <FastLED.h>
#include <Arduino.h>

#define LED_PIN     5
#define LED_PIN2    4
#define NUM_LEDS    150
#define NUM_LEDS2   150
#define BRIGHTNESS  64
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB

int pulsesIndexes[5];
int pulseWidth = 5; 
boolean sensorEngaged;
CRGB leds[NUM_LEDS];
CRGB leds2[NUM_LEDS2];


#define UPDATES_PER_SECOND 100

CRGBPalette16 currentPalette;
TBlendType    currentBlending;
static uint8_t startIndex;




     

void FillLEDsFromPaletteColors( uint8_t colorIndex)
{
    uint8_t brightness = 255;
    
    for( int i = 0; i < NUM_LEDS; i++) {
        leds[i] = ColorFromPalette( currentPalette, colorIndex, brightness, currentBlending);
        leds2[i] = leds[i];
        colorIndex += 3;
    }
    //for( int i = 0; i < NUM_LEDS2; i++) {
    //    leds2[i] = ColorFromPalette( currentPalette, colorIndex, brightness, currentBlending);
    //    colorIndex += 3;
    //}
}


void SendLightPulse(int pulseStartPos, int width){
     CRGB prev[pulseWidth], prev2[pulseWidth];
     
     unsigned long startWait = millis();
     while (millis()-startWait<100){
     for(int dot = pulseStartPos; dot < NUM_LEDS; dot++) { 
      for(int c = 0; c < pulseWidth; c++) {
            prev[c] = leds[dot+c];
            prev2[c] = leds2[dot+c];
            leds[dot+c] = CRGB(255, 120, 0);
            leds2[dot+c] = leds[dot+c];
            //FastLED.show();
            // clear this led for the next time around the loop
            //delay(30);
        }
       FastLED.show(); //Necessay here??
       for(int c = 0; c < pulseWidth; c++) {
            leds[dot+c] = prev[c];
            //Serial.print(leds[dot+c]);
            leds2[dot+c] = leds[dot+c];
       }
       delay(20);   
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
   for (int i = 0; i < 5; i++){      
        int arrayelement = pulsesIndexes[i];
        int prevpulseIndex;
        int positioninPulseArray;
        boolean emptyarray = true;
        if (arrayelement != NULL){
          emptyarray = false;
          arrayelement = prevpulseIndex;
          positioninPulseArray = i; 
        }
    int x = analogRead(A0);
    FillLEDsFromPaletteColors(startIndex);
    //check if sensor is engaged
    if (x > 400){
      sensorEngaged = true;
    }
    else{
      sensorEngaged = false;
      }
      //first condition = sensor  
    if (sensorEngaged == false){
      //just run through palette
      FillLEDsFromPaletteColors(startIndex);
      FastLED.show(); //Necessary here?
      FastLED.delay(1000 / UPDATES_PER_SECOND);
      }
      else{
      //empty pulse array condition
       boolean emptyarray;
      }
       if (emptyarray == true){
        SendLightPulse(0, pulseWidth);
        pulsesIndexes[0] = 0;
        } 
      //already a pulse inside condition  
      else{ 
   
        //check overlap condition
        if (prevpulseIndex > pulseWidth){
          if (positioninPulseArray < 5){
            SendLightPulse (0, pulseWidth);
            pulsesIndexes[positioninPulseArray + 1] = 0;
          }
 
          if (positioninPulseArray == 5){
             //overwrite prev pulse
             SendLightPulse (0, pulseWidth);
             pulsesIndexes[0] = 0;
          } 
        }

      for (int i=0; i<1; i++){
        int indexValue;
        pulsesIndexes[i] = indexValue;
        pulsesIndexes[i] = indexValue + 1;
      }
      startIndex = startIndex +1;  
      FastLED.show();
    }
   }
}
      
  
      
