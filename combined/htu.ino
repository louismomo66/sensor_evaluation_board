void htu1(){
   TCA9548A(4);
Serial.print(",HTU "); Serial.print(htu.readTemperature()); Serial.print(" deg.C, ");
Serial.print(", "); Serial.print(htu.readHumidity()); Serial.print(" % ");

TCA9548A(5);
Serial.print(",HTU "); Serial.print(htu.readTemperature()); Serial.print(" deg.C");
Serial.print(", "); Serial.print(htu.readHumidity()); Serial.print(" % ");
TCA9548A(7);
Serial.print(",HTU "); Serial.print( hdc.readTemperature()); Serial.print(" deg.C, ");
Serial.print(", "); Serial.print(htu.readHumidity()); Serial.print(" % ");
delay(2000);
Serial.println();
}