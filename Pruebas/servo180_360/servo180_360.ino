// Juan A. Villalpando.
// kio4.com
int servoPin=34;
int h;

void setup() {

  pinMode(servoPin, OUTPUT);
}

void loop() {
h=3600;
mover();
h=00;
mover();
delay (5000);

}
void mover(){
  int k=1;
  while(k<=50){
  k=k+1;
  digitalWrite(servoPin, HIGH);
  delayMicroseconds(h);
  digitalWrite(servoPin, LOW);
  delayMicroseconds(3600-h);
  delay (10);
    }
  
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
