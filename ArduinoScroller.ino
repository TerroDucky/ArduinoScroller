#include "Keyboard.h"

const int LikeLED         = 2;
const int LikeButton      = 3;
const int DownLED         = 6;  
const int DownButton      = 7; 
const int UpLED           = 4;  
const int UpButton        = 5; 

/*const int MuscleSenor1 = A0;
const int MuscleSenor2 = A1;*/

const int scrollBreak    = 500;

int LikeButtonState = 0; 
int DownButtonState = 0; 
int UpButtonState = 0; 
void setup() {
  // initialize control over the keyboard:
  Keyboard.begin();
  
  // put your setup code here, to run once:
  pinMode(LikeLED, OUTPUT);
  pinMode(LikeButton, INPUT);
  pinMode(DownLED, OUTPUT);
  pinMode(DownButton, INPUT);
  pinMode(UpLED, OUTPUT);
  pinMode(UpButton, INPUT);

}

void loop() {
  // put your main code here, to run repeatedly:

  LikeButtonState = digitalRead(LikeButton);

    if (LikeButtonState == LOW) { // Button pressed
    // turn LED on:
    digitalWrite(LikeLED, LOW);
    Keyboard.write('l');  // press l key (like)
    delay(scrollBreak); //delay to not double scroll / like too fast
  } 
  else {
    // turn LED off:
    digitalWrite(LikeLED, HIGH);
  }  

  DownButtonState = digitalRead(DownButton);

    if (DownButtonState == LOW) { // Button pressed
    // turn LED on:
    digitalWrite(DownLED, LOW);
    Keyboard.write(KEY_DOWN_ARROW); // press arrow down button
    delay(scrollBreak); //delay to not double scroll
  } 
  else {
    // turn LED off:
    digitalWrite(DownLED, HIGH);
  }  

  UpButtonState = digitalRead(UpButton);

    if (UpButtonState == LOW) { // Button pressed
    // turn LED on:
    digitalWrite(UpLED, LOW);
    Keyboard.write(KEY_UP_ARROW); // press arrow up button
    delay(scrollBreak); //delay to not double scroll
  } 
  else {
    // turn LED off:
    digitalWrite(UpLED, HIGH);
  }    
}
