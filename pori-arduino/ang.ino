void ang(){
  int i;
  
  //50回センサ値を読み込んで平均を算出
  x = y = z = 0;
  for (i = 0 ; i <50 ; i++) {
    x = x + analogRead(ACCX) ; // Ｘ軸
    y = y + analogRead(ACCY) ; // Ｙ軸
    z = z + analogRead(ACCZ) ; // Ｚ軸
  }
  x = x / 50 ;
  y = y / 50 ;
  z = z / 50 ;
  /*
  x = analogRead(ACCX) ; // Ｘ軸
  y = analogRead(ACCY) ; // Ｙ軸
  z = analogRead(ACCZ) ; // Ｚ軸
  */

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
}
