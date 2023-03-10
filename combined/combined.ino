#include <Wire.h>
#include <SPI.h>
#include <Adafruit_BME280.h>
#include <Adafruit_HDC1000.h>
#include "Adafruit_SHT31.h"
#include "Adafruit_HTU21DF.h"
Adafruit_BME280 bmp; // I2C
Adafruit_HTU21DF htu;
Adafruit_SHT31 sht;
Adafruit_HDC1000 hdc;
void TCA9548A(uint8_t bus){
  Wire.beginTransmission(0x70);  // TCA9548A address
  Wire.write(1 << bus);          // send byte
  Wire.endTransmission();
  Serial.print(bus);
}

#define RXD1 15 // To sensor TXD
#define TXD1 4 // To sensor RXD

#define RXD2 18 // To sensor TXD
#define TXD2 14 // To sensor RXD

#define RXD3 32 // To sensor TXD
#define TXD3 33 // To sensor RXD


void setup() {
  Serial1.begin(9600, SERIAL_8N1, RXD1, TXD1);
Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2);
Serial.begin(9600, SERIAL_8N1, RXD3, TXD3);
// Serial.begin(115200);
Wire.begin();

// TCA9548A(1);
// if (!bmp.begin(0x76)){
// Serial.println("Sensor bme 0 fail") ; 
// while(1);
// }
// if (!sht.begin(0x44)){
// Serial.println("Sensor sht 0 fail") ; 
// while(1);
// }
// if (!hdc.begin(0x40)){
// Serial.println("Sensor hdc 0 fail") ; 
// while(1);
// }

// TCA9548A(2);
// if (!bmp.begin(0x76)){
// Serial.println("Sensor bme 1 fail");
// while(1);
// }
// if (!sht.begin(0x44)){
// Serial.println("Sensor sht 2fail") ; 
// while(1);
// }
// if (!hdc.begin(0x40)){
// Serial.println("Sensor hdc 0 fail") ; 
// while(1);
// }

// TCA9548A(3);
// if (!bmp.begin(0x76))
// {Serial.println("Sensor 2 fail");
// while(1);
// }
// if (!sht.begin(0x44)){
// Serial.println("Sensor sht 2 fail") ; 
// while(1);
// }
// if (!hdc.begin(0x40)){
// Serial.println("Sensor hdc 2 fail") ; 
// while(1);
// }
TCA9548A(4);
if (!htu.begin()){
Serial.println("Sensor sht 0 fail") ; 
while(1);
}
TCA9548A(5);
if (!htu.begin()){
Serial.println("Sensor hdc 0 fail") ; 
while(1);
}
TCA9548A(7);
if (htu.begin()){
Serial.println("Sensor sht 0 fail") ; 
while(1);
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
// bme();
// sht3();
// hdc1();
htu1();
Serial.println("*********");
// air();
}










void air(){
  //  for (int i= 0; i<4; i++){
 if (readPMSdata(&Serial1)) {
    // reading data was successful!
    Serial.println();
    Serial.println("First sensor");
   Serial.println("---------------------------------------");

    Serial.print("PM 1.0: "); Serial.print(data.pm10_standard);Serial.println("(u/g3)");
    Serial.print("PM 2.5: "); Serial.print(data.pm25_standard);Serial.println("(u/g3)");
    Serial.print("PM 10: "); Serial.print(data.pm100_standard);Serial.println("(u/g3)");

    // Serial.print("Particles > 0.3um / 0.1L air:"); Serial.println(data.particles_03um);
    // Serial.print("Particles > 0.5um / 0.1L air:"); Serial.println(data.particles_05um);
    // Serial.print("Particles > 1.0um / 0.1L air:"); Serial.println(data.particles_10um);
    // Serial.print("Particles > 2.5um / 0.1L air:"); Serial.println(data.particles_25um);
    // Serial.print("Particles > 5.0um / 0.1L air:"); Serial.println(data.particles_50um);
    // Serial.print("Particles > 10.0 um / 0.1L air:"); Serial.println(data.particles_100um);
    Serial.println("---------------------------------------");
    }

    if (readPMSdata(&Serial2)) {
    // reading data was successful!
    Serial.println();
    Serial.println("Second Sensor");
    Serial.println("---------------------------------------");

    Serial.print("PM 1.0: "); Serial.print(data.pm10_standard);Serial.println("(u/g3)");
    Serial.print("PM 2.5: "); Serial.print(data.pm25_standard);Serial.println("(u/g3)");
    Serial.print("PM 10: "); Serial.print(data.pm100_standard);Serial.println("(u/g3)");


    // Serial.print("Particles > 0.3um / 0.1L air:"); Serial.println(data.particles_03um);
    // Serial.print("Particles > 0.5um / 0.1L air:"); Serial.println(data.particles_05um);
    // Serial.print("Particles > 1.0um / 0.1L air:"); Serial.println(data.particles_10um);
    // Serial.print("Particles > 2.5um / 0.1L air:"); Serial.println(data.particles_25um);
    // Serial.print("Particles > 5.0um / 0.1L air:"); Serial.println(data.particles_50um);
    // Serial.print("Particles > 10.0 um / 0.1L air:"); Serial.println(data.particles_100um);
    Serial.println("---------------------------------------");
    }

    if (readPMSdata(&Serial)) {
    // reading data was successful!
    Serial.println();
    Serial.println("Third Sensor");
    Serial.println("---------------------------------------");

    Serial.print("PM 1.0: "); Serial.print(data.pm10_standard);Serial.println("(u/g3)");
    Serial.print("PM 2.5: "); Serial.print(data.pm25_standard);Serial.println("(u/g3)");
    Serial.print("PM 10: "); Serial.print(data.pm100_standard);Serial.println("(u/g3)");


    // Serial.print("Particles > 0.3um / 0.1L air:"); Serial.println(data.particles_03um);
    // Serial.print("Particles > 0.5um / 0.1L air:"); Serial.println(data.particles_05um);
    // Serial.print("Particles > 1.0um / 0.1L air:"); Serial.println(data.particles_10um);
    // Serial.print("Particles > 2.5um / 0.1L air:"); Serial.println(data.particles_25um);
    // Serial.print("Particles > 5.0um / 0.1L air:"); Serial.println(data.particles_50um);
    // Serial.print("Particles > 10.0 um / 0.1L air:"); Serial.println(data.particles_100um);
    Serial.println("---------------------------------------");
    }
    //  delay(1000);
    // }
 }

boolean readPMSdata(Stream *s) {
  if (! s->available()) {
    return false;
  }

  // Read a byte at a time until we get to the special '0x42' start-byte
  if (s->peek() != 0x42) {
    s->read();
    return false;
  }

  // Now read all 32 bytes
  if (s->available() < 32) {
    return false;
  }

  uint8_t buffer[32];
  uint16_t sum = 0;
  s->readBytes(buffer, 32);

  // get checksum ready
  for (uint8_t i = 0; i < 30; i++) {
    sum += buffer[i];
  }

  /* debugging
    for (uint8_t i=2; i<32; i++) {
    Serial.print("0x"); Serial.print(buffer[i], HEX); Serial.print(", ");
    }
    Serial.println();
  */

  // The data comes in endian'd, this solves it so it works on all platforms
  uint16_t buffer_u16[15];
  for (uint8_t i = 0; i < 15; i++) {
    buffer_u16[i] = buffer[2 + i * 2 + 1];
    buffer_u16[i] += (buffer[2 + i * 2] << 8);
  }

  // put it into a nice struct :)
  memcpy((void *)&data, (void *)buffer_u16, 30);

  if (sum != data.checksum) {
    Serial.println("Checksum failure");
    return false;
  }
  // success!
  return true;
}