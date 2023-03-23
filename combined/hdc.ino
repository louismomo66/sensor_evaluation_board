
void hdc1(){
   TCA9548A(1);
Serial.print(",HDC "); Serial.print(hdc.readTemperature()); Serial.print(" deg.C, ");
hdc1T = hdc.readTemperature();
Serial.print(", "); Serial.print(hdc.readHumidity()); Serial.print(" % ");
hdc1H = hdc.readHumidity();
TCA9548A(2);
Serial.print(",HDC "); Serial.print( hdc.readTemperature()); Serial.print(" deg.C, ");
hdc2T =  hdc.readTemperature();
Serial.print(", "); Serial.print(hdc.readHumidity()); Serial.print(" % ");
hdc2H = hdc.readHumidity();
TCA9548A(3);
Serial.print(",HDC "); Serial.print(hdc.readTemperature()); Serial.print(" deg.C");
hdc3T = hdc.readTemperature();
Serial.print(", "); Serial.print(hdc.readHumidity()); Serial.print(" % ");
hdc3H = hdc.readHumidity();
// delay(2000);
Serial.println();
}

String hdcString() {
  TCA9548A(1);
  float hdc1T = hdc.readTemperature();
  float hdc1H = hdc.readHumidity();
  String hdc1 = "HDC1 " + String(hdc1T) + " deg.C, " + String(hdc1H) + " %, ";

  TCA9548A(2);
  float hdc2T = hdc.readTemperature();
  float hdc2H = hdc.readHumidity();
  String hdc2 = "HDC2 " + String(hdc2T) + " deg.C, " + String(hdc2H) + " %, ";

  TCA9548A(3);
  float hdc3T = hdc.readTemperature();
  float hdc3H = hdc.readHumidity();
  String hdc3 = "HDC3 " + String(hdc3T) + " deg.C, " + String(hdc3H) + " %";

  // delay(2000);

  String hdc_all = hdc1 + hdc2 + hdc3;
  return hdc_all;
}