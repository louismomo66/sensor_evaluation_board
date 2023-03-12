
void htu1(){
   TCA9548A(4);
Serial.print(",HTU "); Serial.print(htu.readTemperature()); Serial.print(" deg.C, ");
htu1T = htu.readTemperature();
Serial.print(", "); Serial.print(htu.readHumidity()); Serial.print(" % ");
htu1H = htu.readHumidity();
TCA9548A(5);
Serial.print(",HTU "); Serial.print(htu.readTemperature()); Serial.print(" deg.C");
htu2T = htu.readTemperature();
Serial.print(", "); Serial.print(htu.readHumidity()); Serial.print(" % ");
htu2H = htu.readHumidity();
TCA9548A(0);
Serial.print(",HDC "); Serial.print( hdc.readTemperature()); Serial.print(" deg.C, ");
htu3T = hdc.readTemperature();
Serial.print(", "); Serial.print(hdc.readHumidity()); Serial.print(" % ");
htu3H = hdc.readHumidity();
delay(2000);
Serial.println();
}