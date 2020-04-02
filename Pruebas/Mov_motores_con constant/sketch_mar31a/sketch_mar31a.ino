const int pin1motorcinta1=2;           //MOTOR 1
const int pin2motorcinta1=4;           //MOTOR 1  

const int pin1motorcinta2=5;           //MOTOR 2  ------>BANDAS 2 PISO
const int pin2motorcinta2=7;           //MOTOR 2
const int pinvelocidad=3;
const int pinvelocidad2=6;

void setup() {
  pinMode(pin1motorcinta1, OUTPUT);     //MOTOR 1
  pinMode(pin2motorcinta1, OUTPUT);     //MOTOR 1

  pinMode(pin1motorcinta2, OUTPUT);     //MOTOR 2
  pinMode(pin2motorcinta2, OUTPUT);     //MOTOR 2

  pinMode(pinvelocidad, OUTPUT); 
  pinMode(pinvelocidad2, OUTPUT); 

}

void loop() {
    digitalWrite(pinvelocidad,HIGH);  
    digitalWrite(pin1motorcinta1,LOW); 
    digitalWrite(pin2motorcinta1,HIGH);
    delay(500);
//    digitalWrite(pinvelocidad,0);  
//    digitalWrite(pin1motorcinta1,LOW); 
//    digitalWrite(pin2motorcinta1,LOW);
//    delay(5000);

}
