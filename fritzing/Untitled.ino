
#define PIN_MOTOR_1_N1 22
#define PIN_MOTOR_1_N2 23


#define MOTOR_1_STOP digitalWrite(PIN_MOTOR_1_N1,LOW);digitalWrite(PIN_MOTOR_1_N2,LOW)
#define MOTOR_1_FORWARD digitalWrite(PIN_MOTOR_1_N1,LOW);digitalWrite(PIN_MOTOR_1_N2,HIGH)
#define MOTOR_1_BACKWARD digitalWrite(PIN_MOTOR_1_N1,HIGH);digitalWrite(PIN_MOTOR_1_N2,LOW)

void setup() {
  pinMode(PIN_MOTOR_1_EN, OUTPUT);
  pinMode(PIN_MOTOR_1_N1, OUTPUT);
  pinMode(PIN_MOTOR_1_N2, OUTPUT);


}


void loop() {
 
  MOTOR_1_FORWARD;
  //MOTOR_2_FORWARD;
  delay(2000);
  MOTOR_1_BACKWARD;
  //MOTOR_2_BACKWARD;
  delay(2000);
}