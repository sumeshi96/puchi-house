#include <Wire.h>

String isLight = "0";
String temp = "23.8";
String humid = "50.2";
char buffer[32];

void setup() {
  Wire.begin(8);
  Wire.onRequest(DataRequest);
}
void loop() {
}
void DataRequest() {
  Wire.write("54.3 67.5 0");
}