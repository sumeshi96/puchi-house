#include "Wire.h"

#define SUMESHI 8
#define RASPI 0x08

//Slaveから送られてきたデータを格納する用
int slaveData = 0;

void setup() {
  // 値を渡さないで実行するとMasterになる
  Wire.begin();
  Serial.begin(9600);
}

void loop() {
  connectSumeshi();

  connectRaspi();

  delay(500);
}

void connectSumeshi() {
  String sumeshiData = "";
  Wire.requestFrom(SUMESHI, 11);

  while (Wire.available()) {
    char receiveData = Wire.read();
    sumeshiData += receiveData;
  }

  char buf[32];
  sumeshiData.toCharArray(buf, sizeof(buf));

  char* part = strtok(buf, " ");
  float temp = atof(part);  // 温度
  part = strtok(NULL, " ");
  float humid = atof(part);  // 湿度
  part = strtok(NULL, " ");
  int isLight = atoi(part);  // 照度

  String displayLcd = "Temp: " + String(temp) + " Humid: " + String(humid);

  Serial.println(displayLcd);
  Serial.println("Light: " + String(isLight));

  Wire.endTransmission(false);
}

void connectRaspi() {
  bool isData = true;

  Wire.beginTransmission(RASPI);
  Wire.write(isData ? 1 : 0);
  Wire.endTransmission();
}