/*
   Created by ArduinoGetStarted.com

   This example code is in the public domain

   Tutorial page: https://arduinogetstarted.com/tutorials/arduino-analog-keypad-library

   This example reads the pressed button from an array of buttons connected to single analog pin and prints it to Serial Monitor.
*/

#include <ezAnalogKeypad.h>

ezAnalogKeypad buttonArray(A0);  // create ezAnalogKeypad object that attach to pin A0

void setup() {
  Serial.begin(9600);

  // MUST READ: You MUST run the calibration example, press button one-by-one to get the analog values
  // The below values is just an example, your button's value may be different
  buttonArray.setNoPressValue(0);  // analog value when no button is pressed
  buttonArray.registerKey(1, 512); // analog value when the button 1 is pressed
  buttonArray.registerKey(2, 341); // analog value when the button 2 is pressed
  buttonArray.registerKey(3, 256); // analog value when the button 3 is pressed
  buttonArray.registerKey(4, 205); // analog value when the button 4 is pressed

  // ADD MORE IF YOUR KEYPAD HAS MORE
}

void loop() {
  unsigned char button = buttonArray.getKey();
  if (button) {
    Serial.print("Button ");
    Serial.print(button);
    Serial.println(" is pressed");
  }
}