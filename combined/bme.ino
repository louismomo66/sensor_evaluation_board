
void bme(){
  TCA9548A(1);
Serial.print(",BME "); Serial.print(bmp.readTemperature()); Serial.print(" deg.C, ");
bme1T = bmp.readTemperature();
Serial.print(", "); Serial.print(bmp.readHumidity()); Serial.print(" % ");
bme1H = bmp.readHumidity();
TCA9548A(2);
Serial.print(",BME "); Serial.print( bmp.readTemperature()); Serial.print(" deg.C, ");
bme2T = bmp.readTemperature();
Serial.print(", "); Serial.print(bmp.readHumidity()); Serial.print(" % ");
bme2H = bmp.readHumidity();
TCA9548A(3);
Serial.print(",BME "); Serial.print(bmp.readTemperature()); Serial.print(" deg.C");
bme3T = bmp.readTemperature();
Serial.print(", "); Serial.print(bmp.readHumidity()); Serial.print(" % ");
bme3H = bmp.readHumidity();
delay(2000);
Serial.println();
}

void shtreal(){

}