
void sht3(){
  TCA9548A(1);
Serial.print(",SHT "); Serial.print(sht.readTemperature()); Serial.print(" deg.C, ");
sht1T = sht.readTemperature();
Serial.print(", "); Serial.print(sht.readHumidity()); Serial.print(" % ");
sht1H = sht.readHumidity();
TCA9548A(2);
Serial.print(",SHT "); Serial.print( sht.readTemperature()); Serial.print(" deg.C, ");
sht2T = sht.readTemperature();
Serial.print(", "); Serial.print(sht.readHumidity()); Serial.print(" % ");
sht2H = sht.readHumidity();
TCA9548A(3);
Serial.print(",SHT "); Serial.print(sht.readTemperature()); Serial.print(" deg.C");
sht3T = sht.readTemperature();
Serial.print(", "); Serial.print(sht.readHumidity()); Serial.print(" % ");
sht3H = sht.readHumidity();
// delay(2000);
Serial.println();
}
String shtString() {
  TCA9548A(1);
  float sht1T = sht.readTemperature();
  float sht1H = sht.readHumidity();
  String sht1 = "SHT1," + String(sht1T) + "," + String(sht1H) + ",";

  TCA9548A(2);
  float sht2T = sht.readTemperature();
  float sht2H = sht.readHumidity();
  String sht2 = "SHT2," + String(sht2T) + "," + String(sht2H) + ",";

  TCA9548A(3);
  float sht3T = sht.readTemperature();
  float sht3H = sht.readHumidity();
  String sht3 = "SHT3," + String(sht3T) + "," + String(sht3H);

  // delay(2000);

  String sht_all = sht1 + sht2 + sht3;
  return sht_all;
}
