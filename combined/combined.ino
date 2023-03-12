#include <Wire.h>
#include <SPI.h>
#include <Adafruit_BME280.h>
#include <Adafruit_HDC1000.h>
#include "Adafruit_SHT31.h"
#include "Adafruit_HTU21DF.h"
#include <SD.h>
#include <ESP32Time.h>
#include <SoftwareSerial.h>

#define SIM800L_IP5306_VERSION_20190610
// Define the serial console for debug prints, if needed
#define DUMP_AT_COMMANDS
#define TINY_GSM_DEBUG          SerialMon
#include "utilities.h"
// Set serial for debug console (to the Serial Monitor, default speed 115200)
#define SerialMon Serial
// Set serial for AT commands (to the module)
#define SerialAT  Serial1

// Configure TinyGSM library
#define TINY_GSM_MODEM_SIM800          // Modem is SIM800
#define TINY_GSM_RX_BUFFER      1024   // Set RX buffer to 1Kb

#include <TinyGsmClient.h>

#ifdef DUMP_AT_COMMANDS
#include <StreamDebugger.h>
StreamDebugger debugger(SerialAT, SerialMon);
TinyGsm modem(debugger);
#else
TinyGsm modem(SerialAT);
#endif
// Set phone numbers, if you want to test SMS and Calls
#define SMS_TARGET  "+256788509024"
#define CALL_TARGET "+256788509024"








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

// #define RXD1 15 // To sensor TXD
// #define TXD1 4 // To sensor RXD
SoftwareSerial mySerial4(15, 4); // RX4, TX4
#define RXD2 14 // To sensor TXD
#define TXD2 18 // To sensor RXD

#define RXD3 33 // To sensor TXD
#define TXD3 32 // To sensor RXD


void setup() {
Wire.begin();
// Serial1.begin(9600, SERIAL_8N1, RXD1, TXD1);
mySerial4.begin(115200);
Serial2.begin(115200, SERIAL_8N1, RXD2, TXD2);
SerialMon.begin(115200, SERIAL_8N1, RXD3, TXD3);
delay(10);
// rtc.setTime(10, 15, 17, 10, 3, 2023);  // 17th Jan 2021 15:24:30
if (setupPMU() == false) {
        Serial.println("Setting power error");
    }

setupModem();
SerialAT.begin(115200, SERIAL_8N1, MODEM_RX, MODEM_TX);
delay(3000);

SerialMon.println("Initializing modem...");
    modem.restart();

 // To send an SMS, call modem.sendSMS(SMS_TARGET, smsMessage)
  // String smsMessage = "Hello from ESP32!";
  // if(modem.sendSMS(SMS_TARGET, smsMessage)){
  //   SerialMon.println(smsMessage);
  // }
  // else{
  //   SerialMon.println("SMS failed to send");
  // }
// initialize();
if (!htu.begin()) { // Initialize the HTU21D sensor
    Serial.println("Couldn't find HTU21D sensor!");
    while (1);
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

float temperature = htu.readTemperature(); // Read temperature data
  float humidity = htu.readHumidity();       // Read humidity data

  // Print the data to the serial monitor
  Serial.print("Temperature = ");
  Serial.print(temperature);
  Serial.println(" °C");

  Serial.print("Humidity = ");
  Serial.print(humidity);
  Serial.println(" %");
// String str1 = "Humidity ";
// String str2 = String(humidity);
// String str3 = "Temperature ";
// String str4 = String(temperature);
//  String str5 = "This is the combined code, ithing it will work. I am esp32 sending";

//  String smsMessage = str1+str2+str3+str4+str5;
//   if(modem.sendSMS(SMS_TARGET, smsMessage)){
//     SerialMon.println(smsMessage);
//   }
//   else{
//     SerialMon.println("SMS failed to send");
//   }
//    while (true) {
//         modem.maintain();
//     }
  delay(1000); // Wait for

// bme();
// sht3();
// hdc1();
// htu1();
//   unsigned long currentMillis = millis();
//   if (currentMillis - previousMillis >= 3000) {
//     WriteFile();
//     previousMillis = currentMillis;
//   }
// Serial.println("*********");
// closeFile();
// air();
}


void closeFile()
{
  if (myfile)
  {
    myfile.close();
    Serial.println("File closed");
  }
}








