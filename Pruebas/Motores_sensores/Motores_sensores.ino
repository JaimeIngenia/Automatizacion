#include <HX711_ADC.h>                   //BALANZA
HX711_ADC LoadCell(6, 7);                //BLANZA

#include <Servo.h>                       //SERVOS CILINDROS A & B
Servo myservo;                          //SEVO_1 
Servo myservo2;                         //SEVO_2                         

#include <Wire.h>                        //PANTALLA
#include <LiquidCrystal_I2C.h>           //PANTALLA 
LiquidCrystal_I2C lcd(0x27, 16, 2);      //PANTALLA

#include <infrarrojo.h>                  //SENSORES DE PRESENCIA      
infrarrojo estado_1(41);                 //S1 (sensor de arranque banda 1)
infrarrojo estado_2(42);                 //S2 (sensor de paro para medir peso)
infrarrojo estado_3(40);                 //S3 (sensor inferior de asensor)

const int inputPin = 50;                 //FINAL DE CARRERA
int valuefinal_carrera = 0;

//Pines de control de las cintas transportadoras
const int pin1motorcinta1=22;           //MOTOR 1
const int pin2motorcinta1=23;           //MOTOR 1  

const int pin1motorcinta2=26;           //MOTOR 2  ------>BANDAS 2 PISO
const int pin2motorcinta2=27;           //MOTOR 2  ------>BANDAS 2 PISO

const int pin1motorcinta3=24;           //MOTOR 3  ------>BANDAS 2 PISO
const int pin2motorcinta3=25;           //MOTOR 3  ------>BANDAS 2 PISO

//Pines de control de cilindros
const int pin1motorcilindroc=28;        //MOTOR 4
const int pin2motorcilindroc=29;        //MOTOR 4

const int pin1motorcilindroa1=30;
const int pin2motorcilindroa1=31;
//pin de velocidad de los pwm
const int pinvelocidad=12;

//Pines de lectura de finales de carrera
int VALOR_1;                             //Recibe dato S1
int VALOR_2;                             //Recibe dato S2
int VALOR_3;                             //Recibe dato S3

int led_estado_1;                        // Variable de estado de sensor de arranque
int led_estado_2;                        // Variable de estado de sensor de paro
int led_estado_3;                        // Variable de estado inferior de sensor de asensor

void setup() {

  LoadCell.begin();                     //BALANZA
  LoadCell.start(2000);                 //BALANZA
  LoadCell.setCalFactor(-300.0);        //BALANZA
  
  myservo.attach(36);                   //SERVOS 1 
  myservo2.attach(34);                  //SERVOS 2 
  Serial.begin(9600);                   //SERVOS

  lcd.begin();                          //PANTALLA LCD
  lcd.backlight();                      //PANTALLA LCD
  
  pinMode(pinvelocidad, OUTPUT);        //MOTORES
//Pines de control de cintas como salidas
  pinMode(pin1motorcinta1, OUTPUT);     //MOTOR 1
  pinMode(pin2motorcinta1, OUTPUT);     //MOTOR 1

  pinMode(pin1motorcinta2, OUTPUT);     //MOTOR 2
  pinMode(pin2motorcinta2, OUTPUT);     //MOTOR 2

  pinMode(pin1motorcinta3, OUTPUT);     //MOTOR 3
  pinMode(pin2motorcinta3, OUTPUT);     //MOTOR 3

  
//Pines de motores de cilindros como salidas

  pinMode(pin1motorcilindroc, OUTPUT); //MOTOR 4
  pinMode(pin2motorcilindroc, OUTPUT); //MOTOR 4
  
  digitalWrite(pinvelocidad,0);
    pinMode(inputPin, INPUT);          //PIN FINAL DE CARRERA
}

void loop() {
  /*
if(led_estado_1 == 0)
{
  arrancarbanda1();
  if(led_estado_2 == 0)
    {
    apagarbanda1();
    delay(8000);
                           //FGUNCION DE PESAR
    if(pesarcarga()<10)
    {
      arrancarbanda1();
      if (led_estado_3 == 0)
      {
        apagarbanda1();
        extraercilindroc();
        if (valuefinal_carrera == HIGH) 
        {
          apagarcilindroc();
          arrancarbanda2();
          extraercilindroa();
          delay(10000);
          apagarbanda2();
          retraercilindroc();
        }
      }
    }
    else
    {
      arrancarbanda1();
      if (led_estado_3 == 0)
      {
        apagarbanda1();
        extraercilindroc();
        if (valuefinal_carrera == HIGH) 
        {
          apagarcilindroc();
          arrancarbanda3();
          extraercilindrob();
          delay(10000);
          apagarbanda3();
          retraercilindroc();
        }
      }      
    }
    arrancarbanda1();
    }
  else
    {
    apagarbanda1();
    }
}
*/


//------------------------------------------FINAL DE CARRERA------------------------------
  valuefinal_carrera = digitalRead(inputPin);  
  if (valuefinal_carrera == HIGH) {
    extraercilindroc();
    Serial.println("Encendido");
  }
  else {
    apagarcilindroc();
    Serial.println("Apagado");
 }
// ------------------------------------------FINAL DE CARRERA-------------------------------


/*
led_estado_1 = estado_1.lectura(VALOR_1);//LED QUE RECOGE EL ESTADO DEL SENSOR
led_estado_2 = estado_2.lectura(VALOR_2);//LED QUE RECOGE EL ESTADO DEL SENSOR
led_estado_3 = estado_3.lectura(VALOR_3);//LED QUE RECOGE EL ESTADO DEL SENSOR


if(led_estado_1 == 0)
{
 // arrancarbanda1();
  arrancarbanda2();
  arrancarbanda3();
  lcd.setCursor(0,0);
  lcd.print("     MOTOR 1    " );
  lcd.setCursor(0,1);
  lcd.print("    ENCENDIDO   ");
}
if(led_estado_2 == 1)
{
  apagarbanda1();
  apagarbanda2();
  apagarbanda3();
  pesarcarga();
  
}

if(led_estado_3 == 0)
{
  //extraercilindroa();
  //extraercilindrob();
  extraercilindroc();
  delay(500);
  apagarcilindroc();
  delay(500);
  retraercilindroc();
  delay(500);
  apagarcilindroc();
  
  
}
*/
  
}
//FUNCIÓN PESAR 
int pesarcarga(){
  LoadCell.update(); // retrieves data from the load cell
  float i = LoadCell.getData(); // get output value
  lcd.setCursor(0, 0); // set cursor to first row
  lcd.print("Weight[g]:"); // print out to LCD
  lcd.setCursor(0, 1); // set cursor to secon row
  lcd.print(i); // print out the retrieved value to the second row
  return i;
  }

//Funciones cilindros A Y B CON LOS DOS SERVOS
//360
void extraercilindroa(){
myservo.write(180);              // 180 tells the continuous rotation servo (CRS) to move forward  
delay(800);                       // waits X ms for the servo to reach the desired position
myservo.write(90);              // 90 tells the CRS to stop (use potentiometer on servo to tune to full stop if there is jitter)
delay(500);                     // Arbitrary wait time before moving actuator backward
myservo.write(5);              // 0 tells the continuous rotation servo (CRS) to move backward
delay(800);                       // waits X ms for the servo to reach the original position
myservo.write(90);
lcd.setCursor(0,0);
lcd.print("    CILIINDRO A    " );
lcd.setCursor(0,1);
lcd.print("    ACCIONADO   ");}

// cilindro b 180
void extraercilindrob(){
myservo2.write(180);              // 180 tells the continuous rotation servo (CRS) to move forward  
delay(800);                       // waits X ms for the servo to reach the desired position
myservo2.write(180);              // 90 tells the CRS to stop (use potentiometer on servo to tune to full stop if there is jitter)
delay(500);                     // Arbitrary wait time before moving actuator backward
myservo2.write(5);              // 0 tells the continuous rotation servo (CRS) to move backward
delay(800);                       // waits X ms for the servo to reach the original position
myservo2.write(180);
}
//---------------------CILINDRO C-----------------------

void extraercilindroc(){
digitalWrite(pinvelocidad,70);  
digitalWrite(pin1motorcilindroc,HIGH); 
digitalWrite(pin2motorcilindroc,LOW);
lcd.setCursor(0,0);
lcd.print("    MOTOR 1    " );
lcd.setCursor(0,1);
lcd.print("    ENCENDIDO   ");}

void retraercilindroc(){
digitalWrite(pinvelocidad,70);  
digitalWrite(pin1motorcilindroc,LOW); 
digitalWrite(pin2motorcilindroc,HIGH);}

void apagarcilindroc(){
digitalWrite(pinvelocidad,0);  
digitalWrite(pin1motorcilindroa1,LOW); 
digitalWrite(pin2motorcilindroa1,LOW);
}
 
//---------------------BANDAS-----------------------

void arrancarbanda1(){
digitalWrite(pinvelocidad,70);  
digitalWrite(pin1motorcinta1,LOW); 
digitalWrite(pin2motorcinta1,HIGH);
}
void apagarbanda1(){
digitalWrite(pinvelocidad,0);  
digitalWrite(pin1motorcilindroa1,LOW); 
digitalWrite(pin2motorcilindroa1,LOW);
}

void arrancarbanda2(){
digitalWrite(pinvelocidad,30);  
digitalWrite(pin1motorcinta2,LOW); 
digitalWrite(pin2motorcinta2,HIGH);
}
void apagarbanda2(){
digitalWrite(pinvelocidad,0);  
digitalWrite(pin1motorcilindroa1,LOW); 
digitalWrite(pin2motorcilindroa1,LOW);
}

void arrancarbanda3(){
digitalWrite(pinvelocidad,70);  
digitalWrite(pin1motorcinta3,LOW); 
digitalWrite(pin2motorcinta3,HIGH);
}
void apagarbanda3(){
digitalWrite(pinvelocidad,0);  
digitalWrite(pin1motorcilindroa1,LOW); 
digitalWrite(pin2motorcilindroa1,LOW);
}
//---------------------FINAL DE CARRERA-----------------------

void finaldecarrera(){
  /*value = digitalRead(inputPin);  
  if (value == HIGH) {
      Serial.println("Encendido");
  }
  else {
      Serial.println("Apagado");
  }
  delay(1000);*/
}

//FUINCIÓN APAGAR SANTI 
void apagarcilindroa(){
digitalWrite(pin1motorcilindroa1,LOW); 
digitalWrite(pin2motorcilindroa1,LOW);}
