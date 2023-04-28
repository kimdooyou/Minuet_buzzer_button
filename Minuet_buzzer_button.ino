// 먼저 코드의 상단에서는 "pitches.h" 파일이 include되고
#include "pitches.h"
//다음으로 멜로디와 각 음표들의 연주 시간이 정의된 배열이 선언됩니다
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
//그리고 버튼과 LED, 피에조부저의 핀 번호도 변수로 정의됩니다.
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
//set 함수에서는 Serial 통신을 설정하고, 
//버튼 핀과 LED 핀이 입력 또는 출력으로 설정됩니다. 
void setup() {
  Serial.begin(9600);
  pinMode(led_pin, OUTPUT);
  pinMode(button_pin, INPUT);
//   그리고 버튼에 인터럽트를 설정하여, 
//   버튼이 눌리면 switchPressed() 함수가 호출되도록 합니다.
  attachInterrupt(digitalPinToInterrupt(button_pin), switchPressed, HIGH);
}
// loop() 함수에서는 Serial.available() 함수를 사용하여 시리얼 
// 통신이 가능한지 확인하고, 시리얼 입력을 읽어들입니다
void loop() {
  //Serial.print("buttonState:");
  //Serial.println(buttonState);
  if (Serial.available()){
    a = Serial.readString();
    a.trim();
//     만약 입력값이 "1"이면, 멜로디를 연주합니다.
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

