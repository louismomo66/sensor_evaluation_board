#include <Wire.h>
#include <SPI.h>
#include <Adafruit_BME280.h>
#include <Adafruit_HDC1000.h>
#include "Adafruit_SHT31.h"
#include "Adafruit_HTU21DF.h"
#include <SD.h>
#include <ESP32Time.h>


unsigned long previousMillis = 0;
Adafruit_BME280 bmp; // I2C
Adafruit_HTU21DF htu;
Adafruit_SHT31 sht;
Adafruit_HDC1000 hdc;

 float sht1T;
  float sht1H;
  float sht2T;
  float sht2H;
  float sht3T;
  float sht3H;

  float htu1T;
  float htu1H;
  float htu2T;
  float htu2H;
  float htu3T;
  float htu3H;

  float bme1T;
  float bme1H;
  float bme2T;
  float bme2H;
  float bme3T;
  float bme3H;
 
  float hdc1T;
  float hdc1H;
  float hdc2T;
  float hdc2H;
  float hdc3T;
  float hdc3H;


ESP32Time rtc(3600);

void TCA9548A(uint8_t bus){
  Wire.beginTransmission(0x70);  // TCA9548A address
  Wire.write(1 << bus);          // send byte
  Wire.endTransmission();
  Serial.print(bus);
}

File myfile;
const int CS = 5;

#define RXD1 15 // To sensor TXD
#define TXD1 4 // To sensor RXD

#define RXD2 14 // To sensor TXD
#define TXD2 18 // To sensor RXD

#define RXD3 33 // To sensor TXD
#define TXD3 32 // To sensor RXD


void setup() {
  
Serial1.begin(9600, SERIAL_8N1, RXD1, TXD1);
Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2);
Serial.begin(9600, SERIAL_8N1, RXD3, TXD3);
// rtc.setTime(10, 15, 17, 10, 3, 2023);  // 17th Jan 2021 15:24:30
Wire.begin();



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

struct pms5003data {
  uint16_t framelen;
  uint16_t pm10_standard, pm25_standard, pm100_standard;
  uint16_t pm10_env, pm25_env, pm100_env;
  uint16_t particles_03um, particles_05um, particles_10um, particles_25um, particles_50um, particles_100um;
  uint16_t unused;
  uint16_t checksum;
};
struct pms5003data data;

void loop()
{
bme();
sht3();
hdc1();
htu1();
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= 3000) {
    WriteFile();
    previousMillis = currentMillis;
  }
Serial.println("*********");
closeFile();
air();
}


void closeFile()
{
  if (myfile)
  {
    myfile.close();
    Serial.println("File closed");
  }
}








