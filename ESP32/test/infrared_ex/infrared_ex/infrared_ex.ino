const int HUMAN_IR_SENSOR = 22;  // 人感センサ
  
void setup() {
  pinMode(HUMAN_IR_SENSOR, INPUT_PULLUP);
  Serial.begin(115200);
  Serial.println("Sensor Start");
}
  
void loop() {
  int val = digitalRead(HUMAN_IR_SENSOR); // 人感センサ値 読込
  Serial.println(val);
  delay(100);
}
