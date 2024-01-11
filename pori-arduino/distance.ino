int readDistance(){
  float dist1 = 5.0 * analogRead(3) / 1023;
  float dist2 = 26.549*pow(dist1, -1.2091);
  return dist2;
}
