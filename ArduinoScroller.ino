#include "Keyboard.h"
#include <U8g2lib.h>
#include <Wire.h>

U8G2_SH1106_128X64_NONAME_F_HW_I2C display(U8G2_R0);

unsigned long sleepTimeout = 30000; //Run the sleepPrevention every 30 seconds
unsigned long nextTimeout = 0; //keep track of when to run sleep prevention
bool armed = false; //We can't just trigger directly, because a trigger might be received during sleep prevention, so we arm it, and fire when ready. Disarming is done in the fire() function.

const int LikeLED         = 2;
const int LikeButton      = 3;
const int DownLED         = 8;  
const int DownButton      = 9; 

int modeButton = 5;
int triggerButton = 4;
int upButton = 6;
int downButton = 7;
int powerLevel = 0;

const int scrollBreak    = 500;

int LikeButtonState = 0; 
int DownButtonState = 0; 
int UpButtonState = 0; 

void setup() {
  // initialize control over the keyboard:
  //Keyboard.begin();
  display.begin();
  
  // put your setup code here, to run once:
  pinMode(LikeLED, OUTPUT);
  pinMode(LikeButton, INPUT);
  pinMode(DownLED, OUTPUT);
  pinMode(DownButton, INPUT);


  Serial.begin(115200);
  pinMode(modeButton, OUTPUT);
  pinMode(triggerButton, OUTPUT);
  pinMode(upButton, OUTPUT);
  pinMode(downButton, OUTPUT);
  //Buttons on the remote are active LOW
  digitalWrite(modeButton,HIGH); 
  digitalWrite(triggerButton,HIGH);
  digitalWrite(upButton,HIGH);
  digitalWrite(downButton,HIGH);
}

void loop() {

    if (armed) {
    fire();
  }
  // put your main code here, to run repeatedly:
  display.clearBuffer();
  display.setFont(u8g2_font_ncenB08_tr);
  display.drawStr(5,10,"Start scrolling");
  display.sendBuffer();

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
  int randNum;
  randNum = random(0, 2);  // Generates 0 to 4

  if (randNum == 1) {
      armed = true;
  }
    
    delay(scrollBreak); //delay to not double scroll
  } 
  else {
    // turn LED off:
    digitalWrite(DownLED, HIGH);
  }  
  if(Serial.available()){ //Triggers on anything! CAREFUL!
    char RX = Serial.read();
    if(RX=='T') armed=true;
    if(RX=='+') setPowerLevel(powerLevel+10);
    if(RX=='-') setPowerLevel(powerLevel-10);
    //while(Serial.available()) Serial.read(); //flush the buffer.
}



  if(millis()>nextTimeout){
    sleepPrevention(); //4*(100+50)... sleep prevention routine takes around 600 milliseconds
  }


}
  void fire(){
    Serial.println("FIRING!");
    buttonPress(triggerButton,500);
    armed=false;

}

void buttonPress(int button, int duration){
  digitalWrite(button, LOW);
  delay(duration);
  digitalWrite(button, HIGH);
  delay(50);
}

void sleepPrevention(){
  for(int repetitions=4;repetitions>0;repetitions--){
  buttonPress(modeButton,100);
  delay(50);
  }
  nextTimeout=millis()+sleepTimeout;
}

void setPowerLevel(int target){
  
  if(target>100) target=100;
  if(target<0) target=0;

  Serial.print("Setting power level to "); Serial.println(target);
  while(target>powerLevel){
    buttonPress(upButton, 100);
    powerLevel++;
  }
  while(target<powerLevel){
    buttonPress(downButton, 100);
    powerLevel--;
  }

}
