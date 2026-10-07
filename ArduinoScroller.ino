const int PinLED         = 6;  
const int PinButton      = 7; 

int buttonState = 0; 

void setup() {
  // put your setup code here, to run once:
  pinMode(PinLED, OUTPUT);
  pinMode(PinButton, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  buttonState = digitalRead(PinButton);

    if (buttonState == HIGH) { // Button pressed
    // turn LED on:
    digitalWrite(PinLED, LOW);
    

  } else {
    // turn LED off:
    digitalWrite(PinLED, HIGH);
  }  
}
