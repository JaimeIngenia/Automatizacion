#include <Servo.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define PIN_SERVO 5
#define PIN_POT A0

Servo myservo;
LiquidCrystal_I2C lcd(0x27, 16, 2);
void setup() {
  Serial.begin(9600);
  myservo.attach(PIN_SERVO);
  lcd.begin();
  lcd.backlight();
  lcd.print("      SERVO     ");
  delay(2000);
  lcd.clear();
}
void loop() {
  int pot_value = analogRead(PIN_POT);
  int angle = map(pot_value, 0, 1023, 0, 180);
  myservo.write(angle);
  Serial.println("Potenciometro: " + String(pot_value) + " angle: " + String(angle));
  lcd.setCursor(0,0);
  lcd.print("Pot: " + String(pot_value));
  lcd.setCursor(0,1);
  lcd.print("Ang: " + String(angle));
  delay(100);
}
