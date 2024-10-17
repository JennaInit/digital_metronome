//LCD and TONE library
#include <LiquidCrystal.h>
#include <Tone.h>
Tone tone1;


//Setting up Speaker for tone on Pin 6
void setup() {
 Serial.begin(9600);
 tone1.begin(6);
  
//Print message on Boot
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);
lcd.begin(16, 2);
lcd.setCursor(0, 0);
lcd.print("Roll the Knob to");
lcd.setCursor(0, 1);
lcd.print("control Speed");
delay(1000);
}

//Setting up the Potentiometer
float floatMap(float x, float in_min, float in_max, float out_min, float out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

//Variable for Counting beat delay for Speaker
float BPMdelayed;


//LOOP
void loop() {

//LCD
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);
lcd.begin(16, 2);

// Taking analogValue from Potentiometer
int analogValue = analogRead(A0);

//Using 5V InputVoltage from Arduino (Scaling variable from 0V to 5V):
float voltage = floatMap(analogValue, 0, 200, 0, 5);
int BPM = 26 + (voltage*18);

//When Potentiometer has too Low value, displaying message on LCD
if(BPM >= 40){
// Print a message to the LCD (2 lines)
lcd.setCursor(0, 0);
lcd.print("Roll the Knob to");
lcd.setCursor(0, 1);
lcd.print("control Speed");
delay(1000);
}

//BPM when rolled
if(BPM > 39){
// Display BPM based on Potentiometer Value on LCD
lcd.setCursor(0, 0);
lcd.print(BPM);
lcd.setCursor(0, 1);
lcd.print("BPM");

	
//Count delay based on Selected BPM
float BPMdelayed = (60000 - (BPM*1))/BPM;

//Play Tone on Speaker
tone1.play(300,20);
delay(BPMdelayed);
}

}