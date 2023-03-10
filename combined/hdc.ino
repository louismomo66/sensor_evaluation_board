void hdc1(){
   TCA9548A(1);
Serial.print(",HDC "); Serial.print(hdc.readTemperature()); Serial.print(" deg.C, ");
Serial.print(", "); Serial.print(hdc.readHumidity()); Serial.print(" % ");
TCA9548A(2);
Serial.print(",HDC "); Serial.print( hdc.readTemperature()); Serial.print(" deg.C, ");
Serial.print(", "); Serial.print(hdc.readHumidity()); Serial.print(" % ");
TCA9548A(3);
Serial.print(",HDC "); Serial.print(hdc.readTemperature()); Serial.print(" deg.C");
Serial.print(", "); Serial.print(hdc.readHumidity()); Serial.print(" % ");
delay(2000);
Serial.println();
}