//POSITIVO CON EL MISMO B/BOTÓN CON AUTOSOSTENIMIENTO Y PULLDOWN
//SE PRENDE O APAGA DISOTÓN

#define PIN_START  9 // PULSADOR EMERGENCIA
#define PIN_EMERGENCIA  8 // PULSADOR EMERGENCIA

#define PIN_LED1 10       //LED ROJO
#define PIN_LED2 11       //LED AMARILLO
#define PIN_LED3 12       //LED VERDE
#define PIN_LED4 13       //LED AZUL

int estado_apagado = 0;  //Guarda estado del botón
int estadoAnterior_apagado = 0;  //Guarda estado anterior del botón (para que se lea bien pulso)

int estado = 0;  //Guarda estado del botón
int estadoAnterior = 0;  //Guarda estado anterior del botón (para que se lea bien pulso)
int salida = 0;  //Guarda estado del Led

void setup()
{
   pinMode(PIN_START, INPUT_PULLUP);
   pinMode(PIN_EMERGENCIA, INPUT_PULLUP);
   pinMode(PIN_LED1, OUTPUT);
   pinMode(PIN_LED2, OUTPUT);
   pinMode(PIN_LED3, OUTPUT);
   pinMode(PIN_LED4, OUTPUT);
}

void loop() {

  arrancar(); 
  while (salida != 0)
  {
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
}
void arrancar()
{
  estado = digitalRead(PIN_START);
  if((estado == HIGH)&&(estadoAnterior == LOW))
  {
    salida = 1;
    delay (20);            
  }

  estadoAnterior = estado;  
}
