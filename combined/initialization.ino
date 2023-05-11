void initialize(){
 pms1.wake();
 pms2.wake();
 pms3.wake();
 delay(1000);
  // pms1.init();
  // pms2.init();
  // pms3.init();

  // Wake up all sensors
  
  
   

   delay(6000);

TCA9548A(1);
if (!bmp.begin(0x76)){
Serial.println("Sensor bme1 fail") ; 
while(1);
}
if (!sht.begin(0x44)){
Serial.println("Sensor sht 1 fail") ; 
while(1);
}
if (!hdc.begin(0x40)){
Serial.println("Sensor hdc 1 fail") ; 
while(1);
}

TCA9548A(2);
if (!bmp.begin(0x76)){
Serial.println("Sensor bme 2 fail");
while(1);
}
if (!sht.begin(0x44)){
Serial.println("Sensor sht 2 fail") ; 
while(1);
}
if (!hdc.begin(0x40)){
Serial.println("Sensor hdc 2 fail") ; 
while(1);
}

TCA9548A(3);
if (!bmp.begin(0x76))
{Serial.println("Sensor bme 3 fail");
while(1);
}
if (!sht.begin(0x44)){
Serial.println("Sensor sht 3 fail") ; 
while(1);
}
if (!hdc.begin(0x40)){
Serial.println("Sensor hdc 3 fail") ; 
while(1);
}
TCA9548A(4);
if (!htu.begin()){
Serial.println("Sensor htu 1  fail") ; 
while(1);
}
TCA9548A(0);
if (!htu.begin()){
Serial.println("Sensor htu 2 fail") ; 
while(1);
}
TCA9548A(5);
if (!htu.begin()){
Serial.println("Sensor htu 3 fail") ; 
while(1);
}
TCA9548A(7);
  if (!ads.begin()) {
    Serial.println("Failed to initialize ADS.");
    while (1);
  }
 ads.setGain(GAIN_TWOTHIRDS);


}