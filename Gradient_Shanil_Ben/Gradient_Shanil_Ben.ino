// color swirl! connect an RGB LED to the PWM pins as indicated
// in the #defines
// public domain, enjoy!
// Code from https://learn.adafruit.com/rgb-led-strips/arduino-code
// Code modified for RGB LED strip by Shanil Patel

#include <Wire.h>
#include "Adafruit_MPR121.h"

// You can have up to 4 on one i2c bus but one is enough for testing!
Adafruit_MPR121 cap = Adafruit_MPR121();


// Keeps track of the last pins touched
// so we know when buttons are 'released'
uint16_t lasttouched = 0;
uint16_t currtouched = 0;

#define RED_LED 9
#define BLUE_LED 6
#define GREEN_LED 5




int rBright = 0;
int gBright =0;
int bBright = 0;
int i = -255;

int fadeSpeed = 10;
 
void setup() {

      Serial.begin(9600);

  while (!Serial) {
    delay(10);
  }

   Serial.println("Adafruit MPR121 Capacitive Touch sensor test"); 
 
  // If tied to SDA its 0x5C and if SCL then 0x5D
  if (!cap.begin(0x5A)) {
    Serial.println("MPR121 not found, check wiring?");
    while (1);
  }
  Serial.println("MPR121 found!");
  
      pinMode(BLUE_LED, OUTPUT); 
   pinMode(GREEN_LED, OUTPUT);
   pinMode(RED_LED, OUTPUT);


   delay(1);


}


 
 
void loop() {

 


  // Get the currently touched pads
  currtouched = cap.touched();

  
for (uint8_t i=0; i<12; i++) {
    if ((currtouched & _BV(i)) && !(lasttouched & _BV(i)) ) {
      Serial.print(i); Serial.println(" touched");
    }
    if (!(currtouched & _BV(i)) && (lasttouched & _BV(i)) ) {
      Serial.print(i); Serial.println(" released");
    }
  }

if (cap.touched() & (1 << 0)) { 

  analogWrite(RED_LED, rBright);
  analogWrite(GREEN_LED, gBright);
  analogWrite(BLUE_LED, bBright -=255);
  }


  if (cap.touched() & (1 << 5)) { 

  analogWrite(RED_LED, rBright);
  analogWrite(GREEN_LED, gBright -=255);
  analogWrite(BLUE_LED, bBright);
  
  }

  
  if (cap.touched() & (1 << 10)) { 

  analogWrite(RED_LED, rBright -=255);
  analogWrite(GREEN_LED, gBright);
  analogWrite(BLUE_LED, bBright);
  
  }

    
  

 // reset our state
  lasttouched = currtouched;

  // comment out this line for detailed data from the sensor!
  return;
  
  // debugging info, what
  Serial.print("\t\t\t\t\t\t\t\t\t\t\t\t\t 0x"); Serial.println(cap.touched(), HEX);
  Serial.print("Filt: ");
  for (uint8_t i=0; i<12; i++) {
    Serial.print(cap.filteredData(i)); Serial.print("\t");
  }
  Serial.println();
  Serial.print("Base: ");
  for (uint8_t i=0; i<12; i++) {
    Serial.print(cap.baselineData(i)); Serial.print("\t");
  }
  Serial.println();
  
  // put a delay so it isn't overwhelming
  delay(100);
}
