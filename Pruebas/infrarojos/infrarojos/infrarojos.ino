#include <infrarrojo.h>                  //SENSORES DE PRESENCIA      
infrarrojo estado_4(8);                 //S4 (sensor final banda 4)
infrarrojo estado_5(9);                 //S5 (sensor final banda 3)
//Pines de lectura de finales de carrera
int VALOR_4;                             //Recibe dato S1
int VALOR_5;                             //Recibe dato S2

int led_estado_4;                        // Variable de estado de sensor de arranque
int led_estado_5;                        // Variable de estado de sensor de paro


void setup()
{
  Serial.begin(9600);

}

void loop()
{

//Serial.println(estado_4.lectura(VALOR_4));
Serial.println(estado_5.lectura(VALOR_5));



delay(100);//GENERA UN TIEMPO PARA LEER E IMPRIMIR EN PUERTO SERIE

}
