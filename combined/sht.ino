
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
delay(2000);
Serial.println();
}

