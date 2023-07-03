
void bme(){
  TCA9548A(1);
Serial.print(",BME "); Serial.print(bmp.readTemperature()); Serial.print(" deg.C, ");
bme1T = bmp.readTemperature();
String bme1 = String(bme1T);
Serial.print(", "); Serial.print(bmp.readHumidity()); Serial.print(" % ");
bme1H = bmp.readHumidity();
String bme2 = String(bme1H);
TCA9548A(2);
Serial.print(",BME "); Serial.print( bmp.readTemperature()); Serial.print(" deg.C, ");
bme2T = bmp.readTemperature();
String bme3 = String(bme2T); 
Serial.print(", "); Serial.print(bmp.readHumidity()); Serial.print(" % ");
bme2H = bmp.readHumidity();
String bme4 = String(bme2H);
TCA9548A(3);
Serial.print(",BME "); Serial.print(bmp.readTemperature()); Serial.print(" deg.C");
bme3T = bmp.readTemperature();
String bme5 = String(bme3T);
Serial.print(", "); Serial.print(bmp.readHumidity()); Serial.print(" % ");
bme3H = bmp.readHumidity();
String bme6 = String(bme3H);
// delay(2000);

// String bme_all = bme1 + bme2 + bme3 + bme4 + bme4 + bme5 + bme6;
// mqtt.publish(topicbme, bme_all);
Serial.println();
// return bme_all;
}
String bmeString() {
  TCA9548A(1);
  float bme1T = bmp.readTemperature();
  float bme1H = bmp.readHumidity();
  float bmep =  bmp.readPressure() / 100.0F;
  String bme1 = "BME1," + String(bme1T) + "," + String(bme1H) +","+String(bmep)+ ",";

  TCA9548A(2);
  float bme2T = bmp.readTemperature();
  float bme2H = bmp.readHumidity();
   float bmep1 =  bmp.readPressure() / 100.0F;
  String bme2 = "BME2," + String(bme2T) + "," + String(bme2H) +","+ String(bmep1)+ ",";

  TCA9548A(3);
  float bme3T = bmp.readTemperature();
  float bme3H = bmp.readHumidity();
   float bmep2 =  bmp.readPressure() / 100.0F;
  String bme3 = "BME3," + String(bme3T) + "," + String(bme3H)+ "," + String(bmep2);

  delay(2000);

  String bme_all = bme1 + bme2 + bme3;
  return bme_all;
}

