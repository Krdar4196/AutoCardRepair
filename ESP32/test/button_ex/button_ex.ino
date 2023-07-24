#include <Arduino.h>

#define MOTOR_PLUS1 4   //12を使うとずっとリセットがかかって動かない
#define MOTOR_MINUS1 13 //13
#define MOTOR_PLUS2 14   //14
#define MOTOR_MINUS2 15  //15
#define BUTTON 17
#define TRIG 5
#define ECHO 18

int V = 340;//音速
int speed;
int speedMin = 100;

int buttonState = 0;

bool bootFlag = 0;//コンベアが起動しているかどうか
bool bootstartFlag = 0;//コンベアの起動処理を行うかどうか

unsigned long bootTime = 1000*5;//ボタンを押してからベルトコンベアを動かす時間
unsigned long pushedMillis = 0;//ボタンを押された時の時間
unsigned long passedMillis = 0;//ボタンを押されてからの経過時間

int currentDistance = 0;
int previousDistance = 0;
int toleranceDistance = 2;

void setup() {
  Serial.begin(115200);

  pinMode(MOTOR_PLUS1, OUTPUT);
  pinMode(MOTOR_MINUS1, OUTPUT);
  pinMode(MOTOR_PLUS2, OUTPUT);
  pinMode(MOTOR_MINUS2, OUTPUT);
  
  pinMode(BUTTON, INPUT);

  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
  digitalWrite(TRIG, LOW);

  Serial.begin(115200);
}

void sendTrigger(){
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);
}

void stopMotor(){
  Serial.println("停止");
  analogWrite( MOTOR_PLUS1, 0 );
  analogWrite( MOTOR_PLUS2, 0 );
}

void loop() {
  //ボタンに関する処理
  buttonState = digitalRead(BUTTON);
  
  if (buttonState == HIGH) {
    Serial.println("ボタンが押されました");
    bootFlag = 1;
    bootstartFlag = 1;
    pushedMillis = millis();
  }else if(passedMillis > bootTime){
    bootFlag = 0;
  }

  //コンベアに関する処理
  speed = speedMin;
  if(bootFlag){
    passedMillis = millis() - pushedMillis;//経過時間の更新
    if(bootstartFlag){
      Serial.println("動作前...");

      analogWrite( MOTOR_PLUS1, speed );
      analogWrite( MOTOR_PLUS2, speed );
    
      bootstartFlag = 0;
    }else{
      Serial.println("動作中...");

      sendTrigger();
      while(!digitalRead(ECHO)){ 
      }
      unsigned long t1 = micros();
      while(digitalRead(ECHO)){
      }
      unsigned long t2 = micros();
      unsigned long t = t2 - t1;
      currentDistance = V * t /20000;
      //Serial.print(V * t /20000);
      //Serial.println("cm");
      if(currentDistance + toleranceDistance < previousDistance){
        Serial.println("物体感知");
        bootFlag = 0;
        stopMotor();
      }
      previousDistance = currentDistance;
    }
  }else{
    stopMotor();
  }
  delay(100);
}