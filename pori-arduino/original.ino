#include <MsTimer2.h>
#include <Wire.h>
#include <LiquidCrystal.h>
#include <Servo.h>

const int ACCX = A2;
const int ACCY = A1;
const int ACCZ = A0;
unsigned int j, line = 0;
LiquidCrystal lcd(4,5,6,8,9,10,11);
int angX;
int angY;
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
  int i ;
  long x, y, z;
  lcd.clear();
  
  //50回センサ値を読み込んで平均を算出
  x = y = z = 0;
  for (i = 0 ; i < 50 ; i++) {
    x = x + analogRead(ACCX) ; // Ｘ軸
    y = y + analogRead(ACCY) ; // Ｙ軸
    z = z + analogRead(ACCZ) ; // Ｚ軸
  }
  x = x / 50 ;
  y = y / 50 ;
  z = z / 50 ;

  //角度を求める
  angX = (x - 296) / 2.61 - 90;
  angY = (y - 264) / 2.57 - 90;

  Serial.print("X:");
  Serial.print(x);
  Serial.print(" ") ;
  Serial.print(angX);
  Serial.print(" Y:");
  Serial.print(y);
  Serial.print(" ") ;
  Serial.print(angY) ;
  Serial.print(" Z:");
  Serial.println(z);

  message(2,1,"5");
  Serial.println(readDistance());
  Servo90();
  delay(50);
}
