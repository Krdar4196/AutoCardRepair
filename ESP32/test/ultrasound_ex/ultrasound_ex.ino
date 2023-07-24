#include <Arduino.h>
#define TRIG 5
#define ECHO 18

int V = 340;//音速

void setup() {
  Serial.begin(115200);
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
  digitalWrite(TRIG, LOW);
}

//Send Trigger pulse
void sendTrigger(){
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);
}

void loop() {
  sendTrigger();

  while(!digitalRead(ECHO)){ 
  }
  unsigned long t1 = micros();

  while(digitalRead(ECHO)){
  }
  unsigned long t2 = micros();
  unsigned long t = t2 - t1;
  Serial.print(V * t /20000);
  Serial.println("cm");
  delay(100);
}