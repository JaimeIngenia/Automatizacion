#define PIN_MOTOR_1_EN 9
#define PIN_MOTOR_1_N1 10
#define PIN_MOTOR_1_N2 11
#define MOTOR_1_STOP digitalWrite(PIN_MOTOR_1_EN, LOW);digitalWrite(PIN_MOTOR_1_N1,LOW);digitalWrite(PIN_MOTOR_1_N2,LOW)
#define MOTOR_1_FORWARD   digitalWrite(PIN_MOTOR_1_EN, HIGH);digitalWrite(PIN_MOTOR_1_N1,LOW);digitalWrite(PIN_MOTOR_1_N2,HIGH)
#define MOTOR_1_BACKWARD   digitalWrite(PIN_MOTOR_1_EN, HIGH);digitalWrite(PIN_MOTOR_1_N1,HIGH);digitalWrite(PIN_MOTOR_1_N2,LOW)

#define LED_ROJO 2                     //LED ROJO-->PESADO
#define LED_AZUL 3                     //LED AZUL-->LIVIANO

#define PIN_START  48                    // PULSADOR START

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

int estado_apagado = 0;                 //START
int estadoAnterior_apagado = 0;         //START
int estado = 0;                         //START
int estadoAnterior = 0;                 //START
int salida = 0;                         //START

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
  pinMode(PIN_MOTOR_1_EN, OUTPUT);
  pinMode(PIN_MOTOR_1_N1, OUTPUT);
  pinMode(PIN_MOTOR_1_N2, OUTPUT);
  
  pinMode(LED_ROJO, OUTPUT);            //LEDS
  pinMode(LED_AZUL, OUTPUT);            //LEDS
  pinMode(PIN_START, INPUT_PULLUP);     //PULSADOR START

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

enum estados {  
  EST_APAGADO,  //0
  EST_CERRAR_PUERTA,
  EST_ENCENDIDO,//1
  EST_DETECCION,//2        //INICIO DE BANDA 1
  EST_DET_PIEZA_S1,//2        //INICIO DE BANDA 1
  EST_DET_PIEZA_S2,//3        //SENSOR PESO, DETIENE LA BANDA 1 ESPERA 8 SEG
  EST_ENCENDER_LED,
  EST_ENCENDER_LCD,
  EST_DET_PIEZA_HP,//4        //INICIO ASCENSOR  
  EST_SUBIR_PIEZA,//5
  EST_DET_ASC,//6
  EST_DECIDIR_BANDA,//7
  EST_BAJAR_ASC,//8  
  EST_ACTIVAR_CB2,//9
  EST_ACTIVAR_CB3,//10
  EST_CERRADO//11
};

int estado_actual = EST_ENCENDIDO;
int estado_anterior = EST_APAGADO;
float peso;
int estado_peso=0;
int estado_puerta=0;  //0cerrado 1abierto

void loop()
{   
  arrancar(); 
  Serial.println(estado_actual);
  while (salida != 0)
  {
  switch (estado_actual)
  {
    case EST_DETECCION:
      Serial.println("2.ABRIENDO LA HP PUERTA");
      detectar_objeto();
      break;
    case EST_CERRAR_PUERTA:
      Serial.println("2.CERRANDO LA HP PUERTA");
      cerrando_la_puerta();
      break;
    case EST_DET_PIEZA_S1:
      Serial.println("2.AVANZANDO");
      detectar_objeto_inicio();
      break;
    case EST_DET_PIEZA_S2:
      peso = detener_pesar_arrancar();
      Serial.print("3. PESANDO ");
      break;
    case EST_ENCENDER_LED:
      encenderled(peso);
      Serial.print("3. ENCENDIENDO LED");
      break;
      case EST_ENCENDER_LCD:
      encender_lcd(peso);
      Serial.print("3. ENCENDIENDO LED");
      break;
    case EST_DET_PIEZA_HP:
      Serial.println("4.  PARAR BANDA");
      pararbanda1();
      break;
    case EST_SUBIR_PIEZA:
      Serial.println("5.  SUBIR ASCENSOR");
      subir_ascensor();
      break;
    case EST_DET_ASC:
      Serial.println("6. PARAR ASCENSOR"); 
      parar_ascensor();
      break;
    case EST_DECIDIR_BANDA:
      Serial.println("7. EMPUJAR PIEZA");
      decidir_banda();
      break;
    case EST_BAJAR_ASC:
      Serial.println("8. BAJAR ASCENSOR");
      bajar_ascensor();
      break;
    case EST_ACTIVAR_CB2:
      Serial.println("9A. ACTIVAR BANDA 2");
      activar_cinta2();
      break;
    case EST_ACTIVAR_CB3:
      Serial.println("9B. ACTIVAR BANDA 3");
      activar_cinta3();
      break;
    case EST_CERRADO:
      cerrar(peso);
      Serial.println("10. DETENIENDO BANDA");
      break;
    default:
      Serial.println("DEFAULT");
      break;
  }
 }
}

//FUNCIÓN PULSADOR SOSTENIDO START
void arrancar()
{
  Serial.println("ARRANCANDO");
  if (estado_actual == EST_ENCENDIDO)
  {
    estado = digitalRead(PIN_START);
    if((estado == HIGH)&&(estadoAnterior == LOW))
    {
      salida = 1;
      delay (20);            
      estado_actual = EST_DETECCION;   
    }
    estadoAnterior = estado;
  }  
}

void detectar_objeto(){
  if (estado_actual == EST_DETECCION)
  {
    Serial.println(estado_1.lectura(VALOR_1));
    Serial.println(estado_puerta);
    if(estado_1.lectura(VALOR_1) == 0)
    {
      MOTOR_1_BACKWARD; //abrir BANDEJA
      delay(500);
      MOTOR_1_STOP; //ADELANTE
      estado_puerta=1;
      estado_actual = EST_CERRAR_PUERTA;   
    }
  }    
}

void cerrando_la_puerta(){
  if (estado_actual == EST_CERRAR_PUERTA)
  {
    Serial.println(estado_1.lectura(VALOR_1));
    Serial.println(estado_puerta);
    if ((estado_1.lectura(VALOR_1) == 1)&&(estado_puerta==1))
    {
      MOTOR_1_FORWARD; //abrir BANDEJA
      delay(500);
      MOTOR_1_STOP; //ADELANTE
      estado_puerta=0;
      estado_actual = EST_DET_PIEZA_S1;   
    }
  }    
}

void detectar_objeto_inicio(){
  if (estado_actual == EST_DET_PIEZA_S1)
  {
    digitalWrite(pinvelocidad,60);  
    digitalWrite(pin1motorcinta1,HIGH); 
    digitalWrite(pin2motorcinta1,LOW);
    if(estado_2.lectura(VALOR_2) == 0)
    {
      estado_actual = EST_DET_PIEZA_S2;   
    }    
  }
}

float detener_pesar_arrancar()
{
  float i;
  if (estado_actual == EST_DET_PIEZA_S2)
  {
    digitalWrite(pinvelocidad,0);  
    digitalWrite(pin1motorcilindroa1,LOW); 
    digitalWrite(pin2motorcilindroa1,LOW);
    LoadCell.update(); // retrieves data from the load cell
    i = LoadCell.getData(); // get output value
    Serial.println(peso);
    digitalWrite(pinvelocidad,60);  
    digitalWrite(pin1motorcinta1,HIGH); 
    digitalWrite(pin2motorcinta1,LOW);
    if(estado_3.lectura(VALOR_3) == 0)
    {
      estado_actual = EST_ENCENDER_LED;   
    }
    return i;
  }
}

void encenderled(float p)
{
  if (estado_actual == EST_ENCENDER_LED)
  {
    if (p <= 5)
    {
      digitalWrite(LED_AZUL,HIGH);
    }
    else
    {
      digitalWrite(LED_ROJO,HIGH);
    }
    estado_actual = EST_ENCENDER_LCD;   
  }
}

void encender_lcd(float p)
{
  if (estado_actual == EST_ENCENDER_LCD)
  {
    lcd.setCursor(0, 0); // set cursor to first row
    lcd.print("Weight[g]:"); // print out to LCD
    lcd.setCursor(0, 1); // set cursor to secon row
    lcd.print(p); // print out the retrieved value to the second row
    estado_actual = EST_DET_PIEZA_HP;   
  }
}
void pararbanda1()
{
  if (estado_actual == EST_DET_PIEZA_HP)
  {
    digitalWrite(pinvelocidad,0);  
    digitalWrite(pin1motorcinta1,LOW); 
    digitalWrite(pin1motorcinta1,LOW);
    estado_actual = EST_SUBIR_PIEZA;   
  }
}

void subir_ascensor()
{
  if (estado_actual == EST_SUBIR_PIEZA)
  {
    digitalWrite(pinvelocidad,5);  
    digitalWrite(pin1motorcilindroc,HIGH); 
    digitalWrite(pin2motorcilindroc,LOW);
    estado_actual = EST_DET_ASC;   
  }
}

void parar_ascensor()
{
  if (estado_actual == EST_DET_ASC)
  {
    valuefinal_carrera = digitalRead(inputPin); 
    if (valuefinal_carrera == LOW) 
    {
      digitalWrite(pinvelocidad,0);  
      digitalWrite(pin1motorcilindroc,LOW); 
      digitalWrite(pin1motorcilindroc,LOW);
      estado_actual = EST_DECIDIR_BANDA;   
    }
  }
}

void decidir_banda()
{
  if (estado_actual == EST_DECIDIR_BANDA)
  {
    if (peso <= 5)
    {
      extrae_objeto_b2();
      estado_actual = EST_ACTIVAR_CB2; 
    }
    else
    {
      extrae_objeto_b3();
      estado_actual = EST_ACTIVAR_CB3; 
    }
  }
}

void bajar_ascensor()
{
  Serial.println("ENTRO PROC BAJA");
  if (estado_actual == EST_BAJAR_ASC)
  {
    Serial.println("BAJANDO");
    digitalWrite(pinvelocidad,70);  
    digitalWrite(pin1motorcilindroc,LOW); 
    digitalWrite(pin2motorcilindroc,HIGH);
    delay(570);
    digitalWrite(pinvelocidad,0);  
    digitalWrite(pin1motorcilindroc,LOW); 
    digitalWrite(pin2motorcilindroc,LOW);
    estado_actual = EST_CERRADO; 
  }
}

void activar_cinta2()
{
    if (estado_actual == EST_ACTIVAR_CB2)
    {  
      digitalWrite(pinvelocidad,70);  
      digitalWrite(pin1motorcinta3,HIGH); 
      digitalWrite(pin2motorcinta3,LOW);
      delay(3000);
      digitalWrite(pin1motorcinta3,LOW); 
      digitalWrite(pin2motorcinta3,LOW);
      estado_actual = EST_BAJAR_ASC;
    }
}

void activar_cinta3()
{
  if (estado_actual == EST_ACTIVAR_CB3)
    { 
      digitalWrite(pinvelocidad,70);  
      digitalWrite(pin1motorcinta2,HIGH); 
      digitalWrite(pin2motorcinta2,LOW);
      delay(3000);
      digitalWrite(pin1motorcinta2,LOW); 
      digitalWrite(pin2motorcinta2,LOW);
      estado_actual = EST_BAJAR_ASC;
    }
}

void extrae_objeto_b3(){
myservo.write(180);              // 180 tells the continuous rotation servo (CRS) to move forward  
delay(800);                       // waits X ms for the servo to reach the desired position
myservo.write(90);              // 90 tells the CRS to stop (use potentiometer on servo to tune to full stop if there is jitter)
delay(500);                     // Arbitrary wait time before moving actuator backward
myservo.write(0);              // 0 tells the continuous rotation servo (CRS) to move backward
delay(800);                       // waits X ms for the servo to reach the original position
myservo.write(90);
}

void extrae_objeto_b2(){
myservo2.write(180);              // 180 tells the continuous rotation servo (CRS) to move forward  
delay(800);                       // waits X ms for the servo to reach the desired position
myservo2.write(180);              // 90 tells the CRS to stop (use potentiometer on servo to tune to full stop if there is jitter)
delay(500);                     // Arbitrary wait time before moving actuator backward
myservo2.write(0);              // 0 tells the continuous rotation servo (CRS) to move backward
delay(800);                       // waits X ms for the servo to reach the original position
myservo2.write(180);
}

void cerrar(float p)
{
  if (estado_actual == EST_CERRADO)
  {
    if (p <= 5)
    {
      digitalWrite(LED_AZUL,LOW);
    }
    else
    {
      digitalWrite(LED_ROJO,LOW);
    }
   estado_actual = EST_DETECCION;
  }
}


//FUNCIÓN PESAR 

//________________________PROGRAMACIÓN PAPA___________________________
///////////////////////////PROGRAMACIÓN PRUEBA////////////////////////

/*  arrancar(); 
  while (salida != 0)
  {
  valuefinal_carrera = digitalRead(inputPin);  
  if (valuefinal_carrera == HIGH) {
    arrancarbanda1();
    
  }
  else {
    apagarbanda1();
    delay(8000);
 
       }
  }
*/
////////////////////////PROGRAMACIÓN PRUEBA/////////////////////////

//------------------------------------------FINAL DE CARRERA CILINDRO C------------------------------
/*  arrancar(); 
  while (salida != 0)
  {
  valuefinal_carrera = digitalRead(inputPin);  
  if (valuefinal_carrera == HIGH) {
//    extraercilindrob();  
//    extraercilindroa();
//    arrancarbanda3();
//    arrancarbanda2();
//    arrancarbanda1();
      extraercilindroc();
    
  }
  else {
    apagarcilindroc();
    delay(8000);
    retraercilindroc();
    delay(570);
    apagarcilindroc();
    delay(8000);
    
       }
  }
 */
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
  
//Funciones cilindros A Y B CON LOS DOS SERVOS
//360


// cilindro b 180

//---------------------CILINDRO C-----------------------

void extraercilindroc(){
digitalWrite(pinvelocidad,50);  
digitalWrite(pin1motorcilindroc,HIGH); 
digitalWrite(pin2motorcilindroc,LOW);
}

void bajar_parar_ascensor(){
Serial.println("Estoy bajando");
digitalWrite(pinvelocidad,70);  
digitalWrite(pin1motorcilindroc,LOW); 
digitalWrite(pin2motorcilindroc,HIGH);
delay(570);
digitalWrite(pinvelocidad,0);  
digitalWrite(pin1motorcilindroc,LOW); 
digitalWrite(pin2motorcilindroc,LOW);
}

void apagarcilindroc(){
digitalWrite(pinvelocidad,0);  
digitalWrite(pin1motorcilindroa1,LOW); 
digitalWrite(pin2motorcilindroa1,LOW);
}
 
//---------------------BANDAS-----------------------




void arrancarbanda2(){
digitalWrite(pinvelocidad,30);  
digitalWrite(pin1motorcinta2,HIGH); 
digitalWrite(pin2motorcinta2,LOW);
}
void apagarbanda2(){
digitalWrite(pinvelocidad,0);  
digitalWrite(pin1motorcilindroa1,LOW); 
digitalWrite(pin2motorcilindroa1,LOW);
}

void arrancarbanda3(){
digitalWrite(pinvelocidad,70);  
digitalWrite(pin1motorcinta3,HIGH); 
digitalWrite(pin2motorcinta3,LOW);
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
