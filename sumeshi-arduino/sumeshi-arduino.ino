#include "DHT.h"

#define LED_R 5
#define LED_G 9
#define LED_B 10

#define SWITCH 2

#define SPEAKER 6

#define DHTPIN 7
#define DHTTYPE DHT11

#define REDLED 12
#define BLUELED 13
#define photoresisterPIN A0

// dht11用
DHT dht(DHTPIN, DHTTYPE);

//スイッチ用
bool playFlag = false;

//照度センサ用
int lightValue = 0;

// 音楽鳴らす用変数
//                        ド1 レ2   ミ3  ファ4 ソ5  ラ6  シ7  ド8
const int doremi[] = { 0, 262, 294, 330, 370, 415, 440, 494, 523 };
const int music[] = { 47, 162, 80, 82, 82, 82, 82, 87, 26, 40, 23, 84, 83, 83, 84, 85, 26, 0 };
int i, j, k;

// 色を制御する関数
void setColor(int redValue, int greenValue, int blueValue) {
  analogWrite(LED_R, redValue);
  analogWrite(LED_G, greenValue);
  analogWrite(LED_B, blueValue);
}

void changeColor(int num) {
  switch (num % 7) {
    case 1:
      setColor(255, 0, 0);
      break;
    case 2:
      setColor(255, 150, 0);
      break;
    case 3:
      setColor(255, 240, 0);
      break;
    case 4:
      setColor(0, 135, 0);
      break;
    case 5:
      setColor(0, 145, 255);
      break;
    case 6:
      setColor(0, 100, 190);
      break;
    case 7:
      setColor(145, 0, 130);
      break;
    default:
      setColor(100, 100, 100);
      break;
  }
}

// 音楽を鳴らす関数
void playMusic() {
  i = 0;
  while (1) {
    changeColor(i);
    j = music[i] / 10;
    k = music[i] % 10;
    if (k) {
      tone(SPEAKER, doremi[k]);
    } else {
      noTone(SPEAKER);
    }
    if (j == 4) {
      delay(500);
    } else if (j == 8) {
      delay(250);
    } else if (j == 2) {
      delay(1000);
    }
    noTone(SPEAKER);
    delay(50);
    i++;
    if (music[i] == 0) {
      noTone(SPEAKER);
      setColor(0, 0, 0);
      delay(1000);
      break;
    }
  }
}

// 温湿度を取得し、シリアルモニタに出力する
String getTempInfo() {
  delay(2000);
  float humid = dht.readHumidity();
  float temp = dht.readTemperature();

  if (isnan(humid) || isnan(temp)) {
    return "Failed to read from DHT sensor!";
  }

  return String(temp, 1) + "," + String(humid, 1);
}

void changePlayFlag() {
  playFlag = !playFlag;
}

String getLightInfo() {
  lightValue = analogRead(photoresisterPIN);

  if (lightValue < 100) {
    digitalWrite(REDLED, HIGH);
    digitalWrite(BLUELED, LOW);
  } else {
    digitalWrite(BLUELED, HIGH);
    digitalWrite(REDLED, LOW);
  }
  return String(lightValue);
}

void setup() {
  pinMode(REDLED, OUTPUT);
  pinMode(BLUELED, OUTPUT);
  pinMode(SPEAKER, OUTPUT);
  pinMode(SWITCH, INPUT_PULLUP);
  attachInterrupt(0, changePlayFlag, RISING);

  Serial.begin(9600);

  // dht11用

  Serial.println(F("DHT11 start!"));
  dht.begin();
}

void loop() {
  if (playFlag) {
    //チャタリング防止
    delay(300);
    changePlayFlag();
    playMusic();
  }
  Serial.println(getTempInfo());
  Serial.println(getLightInfo());
}