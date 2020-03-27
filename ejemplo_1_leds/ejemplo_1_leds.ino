
//MACROS
//Pines de los led
#define PIN_LED1 10   
#define PIN_LED2 11
#define PIN_LED3 12
#define PIN_LED4 13
//pin del boton
#define PIN_BUTTON  9
//Pin del potenciometro
#define PIN_POT A0

void setup() {
    Serial.begin(9600);
    pinMode(PIN_LED1, OUTPUT);
    pinMode(PIN_LED2, OUTPUT);
    pinMode(PIN_LED3, OUTPUT);
    pinMode(PIN_LED4, OUTPUT);
    pinMode(PIN_BUTTON, INPUT_PULLUP);
}

void loop() {
  // put your main code here, to run repeatedly:
   digitalWrite(PIN_LED1, HIGH); 
   delay(1000);
   digitalWrite(PIN_LED2, HIGH); 
   delay(1000);
   digitalWrite(PIN_LED3, HIGH); 
   delay(1000);
   digitalWrite(PIN_LED4, HIGH); 
   delay(1000);
   digitalWrite(PIN_LED4, LOW); 
   delay(50);
   digitalWrite(PIN_LED3, LOW); 
   delay(50);
   digitalWrite(PIN_LED2, LOW); 
   delay(50);
   digitalWrite(PIN_LED1, LOW); 
   delay(50);
  

}
