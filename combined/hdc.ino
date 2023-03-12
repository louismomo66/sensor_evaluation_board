
void hdc1(){
   TCA9548A(1);
Serial.print(",HTU "); Serial.print(htu.readTemperature()); Serial.print(" deg.C, ");
hdc1T = htu.readTemperature();
Serial.print(", "); Serial.print(htu.readHumidity()); Serial.print(" % ");
hdc1H = htu.readHumidity();
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
delay(2000);
Serial.println();
}