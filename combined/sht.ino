void sht3(){
  TCA9548A(1);
Serial.print(",SHT "); Serial.print(sht.readTemperature()); Serial.print(" deg.C, ");
Serial.print(", "); Serial.print(sht.readHumidity()); Serial.print(" % ");
TCA9548A(2);
Serial.print(",SHT "); Serial.print( sht.readTemperature()); Serial.print(" deg.C, ");
Serial.print(", "); Serial.print(sht.readHumidity()); Serial.print(" % ");
TCA9548A(3);
Serial.print(",SHT "); Serial.print(sht.readTemperature()); Serial.print(" deg.C");
Serial.print(", "); Serial.print(sht.readHumidity()); Serial.print(" % ");
delay(2000);
Serial.println();
}