
void htu1(){
   TCA9548A(4);
// Serial.print(",HTU "); Serial.print(htu.readTemperature()); Serial.print(" deg.C, ");
htu1T = htu.readTemperature();
// Serial.print(", "); Serial.print(htu.readHumidity()); Serial.print(" % ");
htu1H = htu.readHumidity();
TCA9548A(5);
// Serial.print(",HTU "); Serial.print(htu.readTemperature()); Serial.print(" deg.C");
htu2T = htu.readTemperature();
// Serial.print(", "); Serial.print(htu.readHumidity()); Serial.print(" % ");
htu2H = htu.readHumidity();
TCA9548A(0);
// Serial.print(",HTU "); Serial.print( htu.readTemperature()); Serial.print(" deg.C, ");
htu3T = htu.readTemperature();
// Serial.print(", "); Serial.print(htu.readHumidity()); Serial.print(" % ");
htu3H = htu.readHumidity();
// delay(2000);
// Serial.println();
}

String htuString() {
  TCA9548A(4);
  float htu1T = htu.readTemperature();
  float htu1H = htu.readHumidity();
  String htu1 = "HTU1 " + String(htu1T) + " deg.C, " + String(htu1H) + " %, ";

  TCA9548A(5);
  float htu2T = htu.readTemperature();
  float htu2H = htu.readHumidity();
  String htu2 = "HTU2 " + String(htu2T) + " deg.C, " + String(htu2H) + " %, ";

  TCA9548A(0);
  float htu3T = htu.readTemperature();
  float htu3H = htu.readHumidity();
  String htu3 = "HTU3 " + String(htu3T) + " deg.C, " + String(htu3H) + " %";

  // delay(2000);

  String htu_all = htu1 + htu2 + htu3;
  return htu_all;
}