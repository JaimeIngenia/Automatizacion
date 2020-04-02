int IN1 =2;
int IN2 =4;
int IN3 =8;
int IN4 =9;


void setup() {
pinMode(IN1,OUTPUT);
pinMode(IN2,OUTPUT);
pinMode(IN3,OUTPUT);
pinMode(IN4,OUTPUT);
}

void loop() 
{
cilindro_amarillo();
}
void cilindro_a()
{
digitalWrite(IN1,HIGH);
digitalWrite(IN2,LOW);
delay(30);
digitalWrite(IN1,LOW);
digitalWrite(IN2,HIGH);
delay(30);
digitalWrite(IN1,LOW);
digitalWrite(IN2,LOW);
delay(3000);

digitalWrite(IN1,LOW);
digitalWrite(IN2,LOW);
delay(3000);
}
void cilindro_amarillo()
{
digitalWrite(IN3,HIGH);
digitalWrite(IN4,LOW);
delay(60);
digitalWrite(IN3,LOW);
digitalWrite(IN4,LOW);
delay(3000);
digitalWrite(IN3,LOW);
digitalWrite(IN4,HIGH);
delay(60);
digitalWrite(IN3,LOW);
digitalWrite(IN4,LOW);
delay(3000);
}
