
int h;

void setup() {

  pinMode(9, OUTPUT);
}

void loop() {
h=3600;
mover();
h=00;
mover();

}

void mover(){
  int k=1;
  while(k<=50){
  k=k+1;
  digitalWrite(9, HIGH);
  delayMicroseconds(h);
  digitalWrite(9, LOW);
  delayMicroseconds(3600-h);
  delay (10);
    }
  
  }
 
