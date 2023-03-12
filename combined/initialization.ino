void initialize(){
  TCA9548A(1);
if (!bmp.begin(0x76)){
Serial.println("Sensor bme 0 fail") ; 
while(1);
}
if (!sht.begin(0x44)){
Serial.println("Sensor sht 0 fail") ; 
while(1);
}
if (!htu.begin()){
Serial.println("Sensor hdc 0 fail") ; 
while(1);
}

TCA9548A(2);
if (!bmp.begin(0x76)){
Serial.println("Sensor bme 1 fail");
while(1);
}
if (!sht.begin(0x44)){
Serial.println("Sensor sht 2fail") ; 
while(1);
}
if (!hdc.begin(0x40)){
Serial.println("Sensor hdc 0 fail") ; 
while(1);
}

TCA9548A(3);
if (!bmp.begin(0x76))
{Serial.println("Sensor 2 fail");
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
TCA9548A(4);
if (!htu.begin()){
Serial.println("Sensor htu 1 fail") ; 
while(1);
}
TCA9548A(5);
if (!htu.begin()){
Serial.println("Sensor htu 2 fail") ; 
while(1);
}
TCA9548A(0);
if (hdc.begin(0x40)){
Serial.println("Sensor hdc 3 fail") ; 
while(1);
}

Serial.println("Initializing SD card...");
  if (!SD.begin(CS)) {
    Serial.println("initialization failed!");
    return;
  }
}