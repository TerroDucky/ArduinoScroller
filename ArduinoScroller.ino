#include "Keyboard.h"


const int PinLED         = 6;  
const int PinButton      = 7; 

const int scrollBreak    = 500;

int buttonState = 0; 

void setup() {
  // initialize control over the keyboard:
  Keyboard.begin();

  // put your setup code here, to run once:
  pinMode(PinLED, OUTPUT);
  pinMode(PinButton, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  buttonState = digitalRead(PinButton);

    if (buttonState == LOW) { // Button pressed
    // turn LED on:
    digitalWrite(PinLED, LOW);
    Keyboard.write(KEY_DOWN_ARROW); // press arrow down button
    delay(scrollBreak); //delay to not double scroll
  } 

  else {
    // turn LED off:
    digitalWrite(PinLED, HIGH);
  }  
}
