//POSITIVO CON EL MISMO B/BOTÓN CON AUTOSOSTENIMIENTO Y PULLDOWN
//SE PRENDE O APAGA DISOTÓN

#define PIN_EMERGENCIA  9 // PULSADOR EMERGENCIA
#define PIN_APAGADO  8 // PULSADOR EMERGENCIA

#define PIN_LED1 10       //LED ROJO
#define PIN_LED2 11       //LED AMARILLO
#define PIN_LED3 12       //LED VERDE
#define PIN_LED4 13       //LED AZUL

int estado_apagado = 0;  //Guarda estado del botón
int estadoAnterior_apagado = 0;  //Guarda estado anterior del botón (para que se lea bien pulso)

int estado = 0;  //Guarda estado del botón
int estadoAnterior = 0;  //Guarda estado anterior del botón (para que se lea bien pulso)
int salida = 0;  //Guarda estado del Led

void setup() {

  Serial.begin(9600);
  
   pinMode(PIN_EMERGENCIA, INPUT_PULLUP);
   pinMode(PIN_APAGADO, INPUT_PULLUP);
   pinMode(PIN_LED1, OUTPUT);
   pinMode(PIN_LED2, OUTPUT);
   pinMode(PIN_LED3, OUTPUT);
   pinMode(PIN_LED4, OUTPUT);

}

void loop() {
//  boolean estado_boton = digitalRead(PIN_BUTTON);----------------> NO SE QUE HACER AHÍ
  Serial.println(digitalRead(PIN_APAGADO));
  arrancar(); 
  Serial.println(digitalRead(PIN_APAGADO));
  while (salida != 0)
  {
   digitalWrite(PIN_LED1, HIGH); 
   Serial.println(digitalRead(PIN_APAGADO));
   if (parar() == 0) break;
   Serial.println(digitalRead(PIN_APAGADO));
//   delay(1000);
   
   digitalWrite(PIN_LED2, HIGH);
   Serial.println(digitalRead(PIN_APAGADO));
   if (parar() == 0) break; 
   Serial.println(digitalRead(PIN_APAGADO));
//   delay(1000);
   
   digitalWrite(PIN_LED3, HIGH); 
   Serial.println(digitalRead(PIN_APAGADO));
   if (parar() == 0) break;
   Serial.println(digitalRead(PIN_APAGADO));
//   delay(1000);
    
  }
}
void arrancar()
{
  estado = digitalRead(PIN_EMERGENCIA);
  if((estado == HIGH)&&(estadoAnterior == LOW))
  {
    salida = 1;// - salida;   //Modifica el estado de la variable salida
    delay (20);            //Evitar el rebote del pulsador
  }

  estadoAnterior = estado;  //Guarda el valor actual
}

int parar()
{
  
  estado_apagado = digitalRead(PIN_APAGADO);
  if((estado_apagado == HIGH)&&(estadoAnterior_apagado == LOW))
  {
    salida = 0;   //Modifica el estado de la variable salida
   digitalWrite(PIN_LED3, LOW); 
   delay(1000);
   digitalWrite(PIN_LED2, LOW); 
   delay(1000);
   digitalWrite(PIN_LED1, LOW); 
   delay(1000);

  }
  estadoAnterior_apagado = estado_apagado;  //Guarda el valor actual 
  return salida;
}
