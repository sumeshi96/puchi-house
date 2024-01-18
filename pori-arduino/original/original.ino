#include <MsTimer2.h>
#include <Wire.h>
#include <LiquidCrystal.h>
#include <Servo.h>

// I2C用
#define SUMESHI 8
#define RASPI 0x08

// 照度センサ識別用
int isLight = -1;
int lastIsLight = -1;

// Raspiパッシング用
boolean isCap = false;

// 加速度センサ用
const int ACCX = A2;
const int ACCY = A1;
const int ACCZ = A0;

LiquidCrystal lcd(4, 5, 6, 8, 9, 10, 11);
int angX, angY;
int angX1, angY1 = 0;
int x, y, z;
Servo food;

void setup() {
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

  // I2C用
  Wire.begin();

  delay(500);
}

void loop() {
  //lcd.clear();
  ang();



  // 照度センサが反応したら
  if (isLight != lastIsLight) {
    Servo90();
    lastIsLight = isLight;
  }

  // 距離センサが30以下になったらカメラ
  if (readDistance() < 30 || crush() == 1) {
    connectRaspi();
  }
  connectSumeshi();


  angX1 = angX;
  angY1 = angY;
}

// sumeshi-arduinoと通信する
void connectSumeshi() {
  // 送られてきたデータ保管用　”XX.X XX.X X”
  String sumeshiData = "";

  // sumeshi-arduinoにデータをリクエスト
  Wire.requestFrom(SUMESHI, 11);

  // 送るデータが無くなるまで実行
  while (Wire.available()) {
    // 送られてきたデータを読み込み
    char receiveData = Wire.read();
    sumeshiData += receiveData;
  }

  // ここからはパース
  char buf[32];
  sumeshiData.toCharArray(buf, sizeof(buf));

  char* part = strtok(buf, " ");
  float temp = atof(part);  // 温度
  part = strtok(NULL, " ");
  float humid = atof(part);  // 湿度
  part = strtok(NULL, " ");
  isLight = atoi(part);  // 照度

  String displayTemp = "Temp : " + String(temp);
  String displayHumid = " Humid: " + String(humid);

  // LCDに温度と湿度を表示
  message(1, 0, displayTemp);
  message(0, 1, displayHumid);

  //Serial.println("Light: " + String(isLight));

  // セッションを終了　これをしないと接続先切り替えられない
  Wire.endTransmission(false);
}

// raspiと通信する
void connectRaspi() {
  // セッションを開始
  Wire.beginTransmission(RASPI);
  // 加速度か、赤外線が反応したらパッシング
  Wire.write(1);
  // セッションを終了
  Wire.endTransmission();
}