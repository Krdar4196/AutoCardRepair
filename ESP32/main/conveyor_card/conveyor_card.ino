#define MOTOR_PLUS1 4   //12を使うとずっとリセットがかかって動かない
#define MOTOR_MINUS1 13 //13
#define MOTOR_PLUS2 14   //14
#define MOTOR_MINUS2 15  //15


int speed;
//int speed_max = 175;
int speed_min = 100;

void setup() {
  // シリアルポート宣言
  Serial.begin(115200);

  // put your setup code here, to run once:
  pinMode(MOTOR_PLUS1, OUTPUT);
  pinMode(MOTOR_MINUS1, OUTPUT);
  pinMode(MOTOR_PLUS2, OUTPUT);
  pinMode(MOTOR_MINUS2, OUTPUT);
}

void loop() {
  speed = speed_min;

  Serial.println("動作前...");

  analogWrite( MOTOR_PLUS1, speed );
  analogWrite( MOTOR_PLUS2, speed );

  Serial.println("動作中...");

  delay(1000*10);

  analogWrite( MOTOR_PLUS1, 0 );
  analogWrite( MOTOR_PLUS2, 0 );

  Serial.println("動作終了...");

  delay(1000*1);
}