void bme(){
  TCA9548A(1);
Serial.print(",BME "); Serial.print(bmp.readTemperature()); Serial.print(" deg.C, ");
Serial.print(", "); Serial.print(bmp.readHumidity()); Serial.print(" % ");
TCA9548A(2);
Serial.print(",BME "); Serial.print( bmp.readTemperature()); Serial.print(" deg.C, ");
Serial.print(", "); Serial.print(bmp.readHumidity()); Serial.print(" % ");
TCA9548A(3);
Serial.print(",BME "); Serial.print(bmp.readTemperature()); Serial.print(" deg.C");
Serial.print(", "); Serial.print(bmp.readHumidity()); Serial.print(" % ");
delay(2000);
Serial.println();
}