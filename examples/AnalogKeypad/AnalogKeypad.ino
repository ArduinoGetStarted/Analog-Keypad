/*
   Created by ArduinoGetStarted.com

   This example code is in the public domain

   Tutorial page: https://arduinogetstarted.com/library/arduino-analog-keypad-example

   This example reads the pressed key from analog keypad and prints it to Serial Monitor.
*/

#include <ezAnalogKeypad.h>

ezAnalogKeypad keypad(A0);  // create ezAnalogKeypad object that attach to pin A0

void setup() {
  Serial.begin(9600);

  // MUST READ: You MUST run the calibration example, press key one-by-one to get the analog values
  // The below values is just an example, your keypad's value may be different
  keypad.setNoPressValue(0);  // analog value when no key is pressed
  keypad.registerKey('1', 100); // analog value when the key '1' is pressed
  keypad.registerKey('2', 150); // analog value when the key '2' is pressed
  keypad.registerKey('3', 200); // analog value when the key '3' is pressed
  keypad.registerKey('4', 250); // analog value when the key '4' is pressed
  keypad.registerKey('*', 450); // analog value when the key '*' is pressed
  keypad.registerKey('0', 500); // analog value when the key '0' is pressed
  keypad.registerKey('#', 550); // analog value when the key '#' is pressed
  // ADD MORE IF YOUR KEYPAD HAS MORE
}

void loop() {
  unsigned char key = keypad.getKey();
  if (key) {
    Serial.println(key);
  }
}