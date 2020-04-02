
int servoPin=6;
int h;

void setup() {

pinMode(servoPin, OUTPUT);
}

void loop() {
  horario();
  antihorario(); 
}

void horario() {
  int k=1;
  while(k<=50){
  k=k+1;
  digitalWrite(servoPin, HIGH);
  delayMicroseconds(0);
  digitalWrite(servoPin, LOW);
  delayMicroseconds(3600);
  delay (10);

}
 delay (3000);
}
void antihorario() {
  int k=1;
  while(k<=50){
  k=k+1;
  digitalWrite(servoPin, HIGH);
  delayMicroseconds(3600);
  digitalWrite(servoPin, LOW);
  delayMicroseconds(0);
  delay (10);

}
 delay (3000);
}
