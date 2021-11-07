#include <FastLED.h>
#include <Arduino.h>

#define LED_PIN     3
#define LED_PIN2    4
#define LED_PIN3    5
#define LED_PIN4    6
#define LED_PIN5    7
#define LED_PIN6    8

#define NUM_LEDS    150
#define NUM_LEDS2   144
#define NUM_LEDS3   144
#define NUM_LEDS4   144
#define NUM_LEDS5   150
#define NUM_LEDS6   150

#define BRIGHTNESS  64
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB

int pulseWidth = 5;
int pulseLocLength = 30;
int pulseLocations[30];
int currentNumPulses = 0;
int currentPulseIndex = 0;

CRGB leds[NUM_LEDS];
CRGB leds2[NUM_LEDS2];
CRGB leds3[NUM_LEDS3];
CRGB leds4[NUM_LEDS4];
CRGB leds5[NUM_LEDS5];
CRGB leds6[NUM_LEDS6];


#define UPDATES_PER_SECOND 100

CRGBPalette16 currentPalette;
TBlendType    currentBlending;
static uint8_t startIndex;




void FillLEDsFromPaletteColors( uint8_t colorIndex)
{
  uint8_t brightness = 255;
  for ( int i = 0; i < NUM_LEDS; i++) {
    leds[i] = ColorFromPalette( currentPalette, colorIndex, brightness, currentBlending);
    leds2[i] = leds[i];
    leds3[i] = leds[i];
    leds4[i] = leds[i];
    leds5[i] = leds[i];
    leds6[i] = leds[i];
    colorIndex += 3;
  }
}


void SetLightPulse(int pulseStartPos, int pulseWidth) {
  unsigned long startWait = millis();
  for (int dot = pulseStartPos; dot < pulseStartPos + pulseWidth; dot++) {
    leds[dot] = CRGB(255, 200, 0);
    leds2[dot] = leds[dot];
    leds3[dot] = leds[dot];
    leds4[dot] = leds[dot];
    leds5[dot] = leds[dot];
    leds6[dot] = leds[dot];
  }
}




void setup() {
  delay( 3000 ); // power-up safety delay
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.addLeds<LED_TYPE, LED_PIN2, COLOR_ORDER>(leds2, NUM_LEDS2).setCorrection( TypicalLEDStrip );
  FastLED.addLeds<LED_TYPE, LED_PIN3, COLOR_ORDER>(leds3, NUM_LEDS3).setCorrection( TypicalLEDStrip );
  FastLED.addLeds<LED_TYPE, LED_PIN4, COLOR_ORDER>(leds4, NUM_LEDS4).setCorrection( TypicalLEDStrip );
  FastLED.addLeds<LED_TYPE, LED_PIN5, COLOR_ORDER>(leds5, NUM_LEDS5).setCorrection( TypicalLEDStrip );
  FastLED.addLeds<LED_TYPE, LED_PIN6, COLOR_ORDER>(leds6, NUM_LEDS6).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness(  BRIGHTNESS );

  CRGB yellow = CRGB(255, 0, 103);
  CRGB white = CRGB(255, 30, 130);
  CRGB red = CRGB(200, 0, 2);
  CRGB orange = CRGB(255, 0, 60);
  CRGB green = CRGB(0, 0, 255);

  currentPalette = CRGBPalette16(white, white, red, red, yellow, yellow, green, orange, orange, orange, red, orange, yellow, yellow, orange, red);
  currentBlending = LINEARBLEND;

  startIndex = 0;

  for( int i=0; i< pulseLocLength; i++){
    pulseLocations[i] = -1; //-1 means can be filled
    }
    
  pinMode(A0, INPUT);
  Serial.begin(9600);
}

void loop()
{
  int sensorVal = analogRead(A0);
  if (sensorVal > 400) { //sensor is triggered, want to update pulse arrays
    if (currentNumPulses == 0) { //no pulses on the strip
      pulseLocations[currentPulseIndex] = 0;
      currentNumPulses = currentNumPulses + 1;
    }
    else if (currentNumPulses < pulseLocLength - 1) { //less than 29 pulses
      if (pulseLocations[currentPulseIndex] >= 5) { //don't hit another pulse
        currentPulseIndex = currentPulseIndex + 1;
        pulseLocations[currentPulseIndex] = 0;
        currentNumPulses = currentNumPulses + 1;
      }
    }
    else { //max pulses : 30 pulses
      if (pulseLocations[currentPulseIndex] >= 5) { //don't hit another pulse
        int maxPulseIndex = 0; //highest pulse gets replaced
        for (int i = 0; i < currentNumPulses; i++) {
          if (pulseLocations[i] > pulseLocations[maxPulseIndex]) {
            maxPulseIndex = i;
          }
        }
        currentPulseIndex = maxPulseIndex;
        pulseLocations[currentPulseIndex] = 0;
      }
    }
  }
  FillLEDsFromPaletteColors(startIndex);
  for (int i = 0; i < currentNumPulses; i++) {
    SetLightPulse(pulseLocations[i], pulseWidth);
  }
  FastLED.show();
  for (int i = 0; i < currentNumPulses; i++) { //incrementing pulses
    int pulseLocation = pulseLocations[i];
    pulseLocations[i] = pulseLocation + 1;
    if (pulseLocations[i] > 139) { //if at the end of the strip
      pulseLocations[i] = NULL;
      currentPulseIndex = i;
      currentNumPulses = currentNumPulses - 1; //decrement number of pulses;
    }
  }
  startIndex = startIndex + 1; //incrementing pallete index
  FastLED.delay(1000 / UPDATES_PER_SECOND);
  //Serial.print("currentNumPulses: ");
  //Serial.println(currentNumPulses);
  //Serial.print("currentPulseIndex: ");
  //Serial.println(currentPulseIndex);
}
