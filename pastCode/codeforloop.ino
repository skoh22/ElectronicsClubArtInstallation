#include <FastLED.h>
//Initialize Variables
#define NUM_LEDS 150;
int pulsesIndexes[5];
int pulseWidth = 5; 
boolean sensorEngaged;
CRGB leds[NUM_LEDS];
//end Initialize variables

//Method: SendLightPulse; Args: pulseStartPos, pulsewidth
void sendLightPulse(int pulseStartPos,int pulsewidth){
     CRGB prev[pulseWidth], prev2[pulseWidth];
     unsigned long startWait = millis();
     while (millis()-startWait<100){
      
      for(int dot = pulseStartPos; dot < NUM_LEDS; dot++) { 
        for(int c = 0; c < pulseWidth; c++) {
            prev[c] = leds[dot+c];
            prev2[c] = leds2[dot+c];
            leds[dot+c] = CRGB(255, 120, 0);
            leds2[dot+c] = leds[dot+c];
        }
       FastLED.show(); //Necessary here????
       for(int c = 0; c < pulseWidth; c++) {
            leds[dot+c] = prev[c];
            leds2[dot+c] = leds[dot+c];
       }
       delay(20);   
      }
     }
}
//end SendLightPulse


void setup() {
    delay( 3000 ); // power-up safety delay
}

void loop()
{
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
      for (int i = 0; i < 5; i++){      
        arrayelement = PulsesIndexes[i];
        boolean emptyarray == true;
        if (arrayelement != null){
          emptyarray = false;
          arrayelement = prevpulseIndex;
          positioninPulseArray = i; 
        }
      }
      if (emptyarray == true){
        SendLightPulse(0, width);
        pulsesIndex[0] = 0;
        } 
      //already a pulse inside condition  
      else if ( 
        //check overlap condition
        if {prevpulseIndex > width){
          if (positioninPulseArray < 5{
            SendLightPulse (0, width);
            pulsesIndex[positioninpulseArray + 1] = 0;
          }
 
          if (positioninPulseArray == 5){
             //overwrite prev pulse
             SendLightPulse (0, width);
             PulsesIndexes[0] = 0;
          } 
        }

      for (int i=0; i<1; i++){
        PulsesIndexes[i] = indexValue;
        PulsesIndex[i] = indexValue + 1;
      }
      startIndex = startIndex +1;  
      FastLED.show();
    }
      
 

      
