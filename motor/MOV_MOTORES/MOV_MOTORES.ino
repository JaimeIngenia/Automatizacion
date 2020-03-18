#define PIN_MOTOR_1_EN 6
#define PIN_MOTOR_1_N1 7
#define PIN_MOTOR_1_N2 5
#define PIN_MOTOR_2_EN 3
#define PIN_MOTOR_2_N3 4
#define PIN_MOTOR_2_N4 2

#define MOTOR_1_STOP digitalWrite(PIN_MOTOR_1_N1,HIGH);digitalWrite(PIN_MOTOR_1_N2,LOW)
#define MOTOR_1_FORWARD digitalWrite(PIN_MOTOR_1_N1,LOW);digitalWrite(PIN_MOTOR_1_N2,HIGH)
#define MOTOR_1_BACKWARD digitalWrite(PIN_MOTOR_1_N1,HIGH);digitalWrite(PIN_MOTOR_1_N2,LOW)


#define MOTOR_2_STOP digitalWrite(PIN_MOTOR_2_N3,HIGH);digitalWrite(PIN_MOTOR_2_N4,LOW)
#define MOTOR_2_FORWARD digitalWrite(PIN_MOTOR_2_N3,LOW);digitalWrite(PIN_MOTOR_2_N4,HIGH)
#define MOTOR_2_BACKWARD digitalWrite(PIN_MOTOR_2_N3,HIGH);digitalWrite(PIN_MOTOR_2_N4,LOW)

#define CAR_FORWARD MOTOR_1_FORWARD;MOTOR_2_FORWARD
#define CAR_BACKWARD MOTOR_1_BACKWARD;MOTOR_2_BACKWARD
#define CAR_RIGTH MOTOR_1_FORWARD;MOTOR_2_BACKWARD
#define CAR_LEFT MOTOR_1_BACKWARD;MOTOR_2_FORWARD

//#define MOTOR_1_SPEED(_SPEED) analogWrite(PIN_MOTOR_1_EN,_SPEED)
//#define MOTOR_2_SPEED(_SPEED) analogWrite(PIN_MOTOR_1_EN,_SPEED)


void setup() {
  pinMode(PIN_MOTOR_1_EN, OUTPUT);
  pinMode(PIN_MOTOR_1_N1, OUTPUT);
  pinMode(PIN_MOTOR_1_N2, OUTPUT);
  pinMode(PIN_MOTOR_2_EN, OUTPUT);
  pinMode(PIN_MOTOR_2_N3, OUTPUT);
  pinMode(PIN_MOTOR_2_N4, OUTPUT);
  digitalWrite(PIN_MOTOR_1_EN, HIGH);
  digitalWrite(PIN_MOTOR_2_EN, HIGH);

}

void loop() {
  CAR_FORWARD;
  delay(4000);
  CAR_BACKWARD;
  delay(4000);
  CAR_RIGTH;
  delay(4000);
  CAR_LEFT;
  delay(4000);



}
