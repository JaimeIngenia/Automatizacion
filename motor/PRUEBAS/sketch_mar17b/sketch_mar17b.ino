
#define PIN_MOTOR_1_EN 3
#define PIN_MOTOR_1_N1 22
#define PIN_MOTOR_1_N2 23
//#define PIN_MOTOR_2_EN 3
//#define PIN_MOTOR_2_N3 24
//#define PIN_MOTOR_2_N4 25

#define MOTOR_1_STOP digitalWrite(PIN_MOTOR_1_N1,LOW);digitalWrite(PIN_MOTOR_1_N2,LOW)
#define MOTOR_1_FORWARD digitalWrite(PIN_MOTOR_1_N1,LOW);digitalWrite(PIN_MOTOR_1_N2,HIGH)
#define MOTOR_1_BACKWARD digitalWrite(PIN_MOTOR_1_N1,HIGH);digitalWrite(PIN_MOTOR_1_N2,LOW)


//#define MOTOR_2_STOP digitalWrite(PIN_MOTOR_2_N3,HIGH);digitalWrite(PIN_MOTOR_2_N4,LOW)
//#define MOTOR_2_FORWARD digitalWrite(PIN_MOTOR_2_N3,LOW);digitalWrite(PIN_MOTOR_2_N4,HIGH)
//#define MOTOR_2_BACKWARD digitalWrite(PIN_MOTOR_2_N3,HIGH);digitalWrite(PIN_MOTOR_2_N4,LOW)

void setup() {
  pinMode(PIN_MOTOR_1_EN, OUTPUT);
  pinMode(PIN_MOTOR_1_N1, OUTPUT);
  pinMode(PIN_MOTOR_1_N2, OUTPUT);

  
//  pinMode(PIN_MOTOR_2_EN, OUTPUT);
//  pinMode(PIN_MOTOR_2_N3, OUTPUT);
//  pinMode(PIN_MOTOR_2_N4, OUTPUT);
//  digitalWrite(PIN_MOTOR_2_EN, 100);
  

}


void loop() {
   analogWrite(PIN_MOTOR_1_EN, 70);
  //MOTOR_1_FORWARD;
  MOTOR_1_FORWARD;
  delay(10000);
  //MOTOR_1_BACKWARD;
  MOTOR_1_BACKWARD;
  delay(5000);
}
