#include <MsTimer2.h>
#include <Wire.h>
#include <LiquidCrystal.h>
#include <Servo.h>

const int ACCX = A2;
const int ACCY = A1;
const int ACCZ = A0;

LiquidCrystal lcd(4,5,6,8,9,10,11);
int angX;
int angY;
int x, y, z;
Servo food; 

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(13, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  
  pinMode(12, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);

  lcd.begin(16, 2);

  food.attach(3);
  food.write(0);

  delay(500);
}

void loop() {
  lcd.clear();
  ang();
  message(2,1,"5");
  Serial.print(readDistance());
  Serial.println("cm");
  //Servo90();
  
}
