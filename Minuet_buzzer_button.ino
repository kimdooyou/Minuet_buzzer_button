#include "pitches.h"
int melody[] = {
  NOTE_D5, NOTE_G4, NOTE_A4, NOTE_B4,  NOTE_C5, NOTE_D5,
 NOTE_G4, NOTE_G4, NOTE_E5, NOTE_C5, NOTE_D5, NOTE_E5,
 NOTE_FS5, NOTE_G5, NOTE_G4, NOTE_G4, NOTE_C5, NOTE_D5,
 NOTE_C5, NOTE_B4, NOTE_A4, NOTE_B4, NOTE_C5, NOTE_B4, 
 NOTE_A4, NOTE_G4, NOTE_FS4, NOTE_G4, NOTE_A4, NOTE_B4,
 NOTE_G4, NOTE_B4, NOTE_A4, NOTE_D5, NOTE_G4, NOTE_A4, 
 NOTE_B4,  NOTE_C5, NOTE_D5, NOTE_G4, NOTE_G4,     
 NOTE_E5, NOTE_C5, NOTE_D5, NOTE_E5,   
 NOTE_FS5, NOTE_G5, NOTE_G4, NOTE_G4, NOTE_C5, NOTE_D5,
 NOTE_C5, NOTE_B4, NOTE_A4, NOTE_B4, NOTE_C5, NOTE_B4, 
 NOTE_A4, NOTE_G4, NOTE_A4, NOTE_B4, NOTE_A4, NOTE_G4, NOTE_FS4, NOTE_G4
};
int noteDurations[] = {4,8,8,8,8,4,4,4,4,8,8,8,
                        8,4,4,4,4,8,8,8,8,4,8,8,8,8,4,8,8,8,8,8,2.5,
                        4,8,8,8,8,4,4,4,4,8,8,8,8,4,4,4,4,8,8,8,8,4,8,8,8,8,4,8,8,8,8,2.5
};
int button_pin = 2;
const int led_pin = 3;

int buttonState = 0;
int state = 0;  
int tone_pin = 12; 
String a;

void switchPressed(){
  if (digitalRead (button_pin) == HIGH) {
    buttonState = 1;
    digitalWrite(led_pin, HIGH);
    delay(1000);
  }
  else{
    buttonState = 0;
    digitalWrite(led_pin, LOW);
  }
}

void setup() {
  Serial.begin(9600);
  pinMode(led_pin, OUTPUT);
  pinMode(button_pin, INPUT);
  attachInterrupt(digitalPinToInterrupt(button_pin), switchPressed, HIGH);
}

void loop() {
  //Serial.print("buttonState:");
  //Serial.println(buttonState);
  if (Serial.available()){
    a = Serial.readString();
    a.trim();
    if (a == "1"){    
       for (int thisNote = 0; thisNote <67; thisNote++){
         if (buttonState == 1)
           break;
         int noteDuration = 1000/ noteDurations[thisNote];
         tone(tone_pin, melody[thisNote], noteDuration);
         int pauseBetweenNotes = noteDuration * 1.30;
         delay(pauseBetweenNotes);
         noTone(tone_pin);
         }
    } else {
      Serial.println("not 1");
    }
  }
}

