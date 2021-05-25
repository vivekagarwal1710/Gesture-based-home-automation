#define NOTE_FS5 740
#define NOTE_D5  587
#define NOTE_B5  988
#define NOTE_GS5 831
#define NOTE_E5  659
#define NOTE_A5  880
#define NOTE_B4  494

#include <Servo.h> 


int melody[] = {
  NOTE_FS5, NOTE_FS5, NOTE_D5, NOTE_B4, NOTE_B4, NOTE_E5, 
  NOTE_E5, NOTE_E5, NOTE_GS5, NOTE_GS5, NOTE_A5, NOTE_B5, 
  NOTE_A5, NOTE_A5, NOTE_A5, NOTE_E5, NOTE_D5, NOTE_FS5, 
  NOTE_FS5, NOTE_FS5, NOTE_E5, NOTE_E5, NOTE_FS5, NOTE_E5
};

int durations[] = {
  8, 8, 8, 4, 4, 4, 
  4, 5, 8, 8, 8, 8, 
  8, 8, 8, 4, 4, 4, 
  4, 5, 8, 8, 8, 8
};
int songLength = sizeof(melody)/sizeof(melody[0]);

Servo myServo;

const int flexPinServo = A1;
const int flexPinLED = A0;
const int flexPinBuzzer = A2; 
const int ledPin = 3; 
const int Piezo = 2;
int cnt=0; 

void setup() 
{ 
  Serial.begin(9600);
  myServo.attach(11);
  pinMode(ledPin,OUTPUT);
  pinMode (Piezo, OUTPUT);

} 
int flag=1;
void loop() 
{ 
  int flexValueServo;
  int servoPosition;
  
  flexValueServo = analogRead(flexPinServo);
  if(flexValueServo>890){
    delay(1000);
    if(flag==0)
      flag=1;
    else
      flag=0;
  }
  if (flag==0){
    myServo.write(180);
    delay(1000);
    myServo.write(0);
    delay(1000);
    
  }
  else
    myServo.write(0);
  
  

  int flexValueLED;
  flexValueLED = analogRead(flexPinLED);
  
  if(cnt ==0 && flexValueLED>890){
     digitalWrite(ledPin,HIGH);
     cnt=1;
     delay(1000);
     
   }
  else if(cnt==1 && flexValueLED>890){
     digitalWrite(ledPin,LOW);
     cnt=0;
     delay(1000);
     
   }
  


  int flexValueBuzzer = analogRead(flexPinBuzzer); 
  Serial.println(flexValueBuzzer);
  if (flexValueBuzzer>890) {
    for (int thisNote = 0; thisNote < songLength; thisNote++){
  int duration = 1000/ durations[thisNote];
        tone(Piezo, melody[thisNote], duration);
        int pause = duration * 1.3;
        delay(pause);
        noTone(Piezo);
    }
  }
  delay(20);
}