#include <Wire.h>
#include <SPI.h>
// #include <WiFi.h>

#include <ESP32Time.h>
#include <Adafruit_BME280.h>
#include <Adafruit_HDC1000.h>
#include "Adafruit_SHT31.h"
#include "Adafruit_HTU21DF.h"
#include <SD.h>
#include "FS.h"
#include <HardwareSerial.h>
// #include "time.h"
// #include <SoftwareSerial.h>
#include <Adafruit_ADS1X15.h>
#include <EEPROM.h>
#ifndef ESP32
#include <SoftwareSerial.h>
#endif
#include <PMserial.h> // Arduino library for PM sensors with serial interfacerduino library for PM sensors with serial interface
// #include <esp_sleep.h>

// #define SMS_TARGET  "+256787239229"
// #define CALL_TARGET "+256788509024"

SPIClass sdSPI(HSPI);
#define SCK  18 //yellow
#define MISO 19 //blue
#define MOSI 23 //green
#define CS  5 //orange

 #define SIM800L_IP5306_VERSION_20190610
// #define SIM800L_AXP192_VERSION_20200327
// #define SIM800C_AXP192_VERSION_20200609
// #define SIM800L_IP5306_VERSION_20200811

#include "utilities.h"
// Select your modem:
#define TINY_GSM_MODEM_SIM800
// Set serial for debug console (to the Serial Monitor, default speed 115200)
#define SerialMon Serial
// Set serial for AT commands (to the module)
// Use Hardware Serial on Mega, Leonardo, Micro
#define TINY_GSM_RX_BUFFER   1024  
#define SerialAT Serial1
// See all AT commands, if wanted
// #define DUMP_AT_COMMANDS
// Define the serial console for debug prints, if needed
#define TINY_GSM_DEBUG SerialMon
// Add a reception delay - may be needed for a fast processor at a slow baud rate
// #define TINY_GSM_YIELD() { delay(2); }
// Define how you're planning to connect to the internet
#define TINY_GSM_USE_GPRS true
#define TINY_GSM_USE_WIFI false
// set GSM PIN, if any
#define GSM_PIN ""
// Your GPRS credentials, if any
const char apn[] = "airtelgprs.com";
const char gprsUser[] = "";
const char gprsPass[] = "";
// MQTT details
// const char *broker = "0.tcp.ngrok.io";
const char *broker = "137.63.185.130";
const char *topicbme = "topic/bme";
const char *topicsht = "topic/sht";
const char *topichdc= "topic/hdc";
const char *topichtu = "topic/htu";
const char *status_topic = "topic/status";

const char *topicAir1 = "topic/air1";
const char *topicAir2= "topic/air2";
const char *topicAir3 = "topic/air3";
const char *topicb_volt = "topic/b_voltage";
const char *topicb_curent = "topic/current";
#include <TinyGsmClient.h>
#include <PubSubClient.h>
Adafruit_ADS1115 ads;
#ifdef DUMP_AT_COMMANDS
#include <StreamDebugger.h>
StreamDebugger debugger(SerialAT, SerialMon);
TinyGsm modem(debugger);
#else
TinyGsm modem(SerialAT);
#endif

TinyGsmClient client(modem);
PubSubClient mqtt(client);



uint32_t lastReconnectAttempt = 0;



// boolean mqttConnect() {
//   SerialMon.print("Connecting to ");
//   SerialMon.print(broker);

//   // Connect to MQTT Broker without username and password
//   //boolean status = mqtt.connect("GsmClientN");

//   // Or, if you want to authenticate MQTT:
//   boolean status = mqtt.connect("GsmClientN");

//   if (status == false) {
//     SerialMon.println(" fail");
//     ESP.restart();
//     return false;
//   }
//   SerialMon.println(" success");
//   // mqtt.subscribe(topicOutput1);
//   // mqtt.subscribe(topicOutput2);

//   return mqtt.connected();
// }

float current1 = 0;
int16_t adc0;
float volts0;
float sensitivity = 40.00;



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


// ESP32Time rtc(3600);

void TCA9548A(uint8_t bus){
  Wire.beginTransmission(0x70);  // TCA9548A address
  Wire.write(1 << bus);          // send byte
  Wire.endTransmission();
  // Serial.print(bus);
}

// File myfile;
// #define SD_CS 5
String dataMessage;


#define RXD1 15//15  To sensor TXD
#define TXD1  0//0  To sensor RXD
// HardwareSerial mySerial4(0); // RX4, TX4
#define RXD2 4 // To sensor TXD
#define TXD2 14 // To sensor RXD

#define RXD3 33 // To sensor TXD
#define TXD3 32 // To sensor RXD

// SoftwareSerial mySerial4(15, 4);
// #ifndef ESP32

// SerialPM pms1(PMSA003, mySerial4);
// #else
SerialPM pms1(PMS7003, Serial) ;// PMSx003, RX, TX
// #endif
SerialPM pms2(PMS7003, Serial1); // PMSx003, RX, TX
SerialPM pms3(PMS7003, Serial2); 

// struct pms5003data {
//   uint16_t framelen;
//   uint16_t pm10_standard, pm25_standard, pm100_standard;
//   uint16_t pm10_env, pm25_env, pm100_env;
//   uint16_t particles_03um, particles_05um, particles_10um, particles_25um, particles_50um, particles_100um;
//   uint16_t unused;
//   uint16_t checksum;
// };
// struct pms5003data data;

// const char* ssid       = "kl";
// const char* password   = "9999999990";
// const char* ntpServer = "de.pool.ntp.org";
// const char* timeZone = "EAT-3";  // UTC
// struct tm timeinfo;  // time struct

String gsmDateTime;
String helloString;
ESP32Time rtc(3600);

void setup() {

// pinMode(13, OUTPUT);
digitalWrite(13,LOW);
// EEPROM.begin(512);
Wire.begin();
// mySerial4.begin(9600);

Serial1.begin(9600, SERIAL_8N1, RXD3, TXD3);
Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2);
Serial.begin(9600,SERIAL_8N1, RXD1, TXD1);
Serial.println("Started");
//  pms1.wake();
//  pms2.wake();
//  pms3.wake();
// Serial.begin(9600);
// if (!getLocalTime(&timeinfo)) {
//     Serial.println("RTC is not set");
//     // set time via NTP 
//     getNtpTime();    
//   }
// setTimezone(); 
//   Serial.print("current time: ");
//   printLocalTime();
rtc.setTime(30, 24, 15, 17, 1, 2021);
Serial.println(rtc.getTime("%A, %B %d %Y %H:%M:%S")); 
initialize();
initialize_sd();

// readsd();
// readlast();
air();
voltage();

WriteFile();
// voltage();
setupModem();
 
unsigned long start_time = 0; // declare a variable to store the start time

SerialMon.println("Wait...");

// Set GSM module baud rate and UART pins
SerialAT.begin(9600, SERIAL_8N1, MODEM_RX, MODEM_TX);

start_time = millis(); // record the start time

// Wait for 6 seconds before initializing the modem
// while (millis() - start_time < 1000) {}

SerialMon.println("Initializing modem...");
modem.restart();

// SerialMon.print("Waiting for network...");
modem.sendAT("+CNETLIGHT=0");
// start_time = millis(); // record the start time

// while (!modem.waitForNetwork()) {
//   if (millis() - start_time > 1000) { // exit the loop after 10 seconds
//     SerialMon.println(" fail");
//     return;
//   }
// }

// SerialMon.println(" success");

// if (modem.isNetworkConnected()) {
//   SerialMon.println("Network connected");
// }
// SerialAT.println("AT+CCLK?");
// ShowSerialData();

// GPRS connection parameters are usually set after network registration
// SerialMon.print(F("Connecting to "));
// SerialMon.print(apn);

// start_time = millis(); // record the start time

// while (!modem.gprsConnect(apn, gprsUser, gprsPass)) {
//   if (millis() - start_time > 4000) { // exit the loop after 10 seconds
//     SerialMon.println(" fail");
//     return;
//   }
// }

// SerialMon.println(" success");

// if (modem.isGprsConnected()) {
//   SerialMon.println("GPRS connected");
// }


// SerialMon.println("Wait...");
// // // Set GSM module baud rate and UART pins

// SerialAT.begin(9600, SERIAL_8N1, MODEM_RX, MODEM_TX);

// delay(6000);

// // //     // Restart takes quite some time
// // //    // To skip it, call init() instead of restart()
// SerialMon.println("Initializing modem...");
// modem.restart();


// SerialMon.print("Waiting for network...");
//     if (!modem.waitForNetwork()) {
//         SerialMon.println(" fail");
//         delay(10000);
//         return;
//     }
//     SerialMon.println(" success");

//     if (modem.isNetworkConnected()) {
//         SerialMon.println("Network connected");
//     }

    // GPRS connection parameters are usually set after network registration
    // SerialMon.print(F("Connecting to "));
    // SerialMon.print(apn);
    if (!modem.gprsConnect(apn, gprsUser, gprsPass)) {
        SerialMon.println(" fail");
        delay(1000);
        return;
    }
    SerialMon.println(" success");

    // if (modem.isGprsConnected()) {
    //     SerialMon.println("GPRS connected");
    // }

// readsd();
    // MQTT Broker setup
    
mqtt.setServer(broker,8383);
if(!mqtt.connected()){
  reconnect();
}
  
mqtt.loop();

send_data();
// rtc.setTime(10, 15, 17, 10, 3, 2023);  // 17th Jan 2021 15:24:30
 modem.sendAT(GF("+CPOWD=1"));
 // To send an SMS, call modem.sendSMS(SMS_TARGET, smsMessage)
  // String smsMessage = "Hello from ESP32!";
  // if(modem.sendSMS(SMS_TARGET, smsMessage)){
  //   SerialMon.println(smsMessage);
  // }
  // else{
  //   SerialMon.println("SMS failed to send");
  // }
// initialize_sd();
// WriteFile();
// Serial.println("Entering deep sleep mode for 1 minute...");
//  // 60e6 microseconds = 1 minute
// esp_sleep_enable_timer_wakeup( * 1000000);
// esp_deep_sleep_start();
 // 1 minute
// digitalWrite(MODEM_POWER_ON, HIGH);
// Serial.println("Going to sleep now");
// delay(5000);
//  Put all sensors to sleep
// modem.sendAT(GF("+CPOWD=1"));
//  String myString = readStringFromEEPROM(40);
//   Serial.println(myString);
pms1.sleep();
pms2.sleep();
pms3.sleep(); 

// Serial.print("Sleep");
esp_sleep_enable_timer_wakeup(250 * 1000000);
esp_deep_sleep_start();


}



void loop()
{

}

// void setupModem()
// {
// #ifdef MODEM_RST
//     // Keep reset high
//     pinMode(MODEM_RST, OUTPUT);
//     digitalWrite(MODEM_RST, HIGH);
// #endif

//     pinMode(MODEM_PWRKEY, OUTPUT);
//     pinMode(MODEM_POWER_ON, OUTPUT);

//     // Turn on the Modem power first
//     digitalWrite(MODEM_POWER_ON, HIGH);

//     // Pull down PWRKEY for more than 1 second according to manual requirements
//     digitalWrite(MODEM_PWRKEY, HIGH);
//     delay(100);
//     digitalWrite(MODEM_PWRKEY, LOW);
//     delay(1000);
//     digitalWrite(MODEM_PWRKEY, HIGH);

//     // Initialize the indicator as an output
//     pinMode(LED_GPIO, OUTPUT);
//     digitalWrite(LED_GPIO, LED_OFF);
// }

void reconnect(){

unsigned long start_time = 0; // declare a variable to store the start time
int delay_time = 1000; // set the delay time to 5 seconds

while (!mqtt.connected()) {
    SerialMon.println("=== Attempting Connection... ===");

    start_time = millis(); // record the start time

    // Reconnect every 10 seconds
    String clientId = "ESP8266-";
    clientId += String(random(0xffff), HEX);

    if (mqtt.connect(clientId.c_str())){
        Serial.println("Connected");
        mqtt.publish(status_topic, "ESP32 Alive");
    } else {
        Serial.println(mqtt.state());
    }

    // wait for the remaining time in the delay period
    while (millis() - start_time < delay_time) {}
}




//  }

  //   uint32_t t = millis();
  //   if (t - lastReconnectAttempt > 10000L) {
  //     lastReconnectAttempt = t;
  //     if (mqttConnect()) {
  //       lastReconnectAttempt = 0;
  //     }
  //   }
  //   delay(100);
  //   return;
  // }
}

// void getNtpTime(){
//   //connect to WiFi
//   Serial.printf("connecting to %s ", ssid);
//   WiFi.begin(ssid, password);
//   while (WiFi.status() != WL_CONNECTED) {
//     // delay(500);
//     Serial.print(".");
//   }
//   Serial.println(" connected");
  
//   // init, get NTP time, set RTC
//   configTzTime(timeZone,  ntpServer);

//   // debug 
//   Serial.print("get NTP time, RTC set to: ");
//   printLocalTime();
//   Serial.println();

  //disconnect WiFi as it's no longer needed
  // WiFi.disconnect(true);
  // WiFi.mode(WIFI_OFF);
// }

// void setTimezone(){
//   Serial.print("set timezone to ");
//   Serial.println(timeZone);
//   setenv("TZ",timeZone,1);  //  set timezone 
//   tzset();
// }
void ShowSerialData()
{
  while(SerialAT.available()>0){
  gsmDateTime += (char) SerialAT.read();
  SerialMon.print("GSM Date/Time: ");
  SerialMon.println(gsmDateTime);
  helloString = gsmDateTime.substring(10,30);
  Serial.println(helloString);}
  writeStringToEEPROM(40,helloString);
//  Serial.write(SerialAT.read());
  //  delay(5000); 
   
  
}
// void printLocalTime(){ 
//   if(!getLocalTime(&timeinfo)){
//     Serial.println("failed to obtain time");
//     return;
//   }

//   // print time human readable
//   char strftime_buf[64];
//   strftime(strftime_buf, sizeof(strftime_buf), "%Y-%m-%d %H:%M:%S", &timeinfo);
//   Serial.println(strftime_buf);

//   // print epoch time 
//   time_t epoch_ts = mktime(&timeinfo);  // get epoch time from struct
//   Serial.println("epoch time is " + String(epoch_ts));
// }
String readStringFromEEPROM(int addrOffset) {
  String str = "";
  char ch;
  int i = 0;
  while ((ch = EEPROM.read(addrOffset + i)) != '\0') {
    str += ch;
    i++;
  }
  return str;
}
void writeStringToEEPROM(int addrOffset, String str) {
  for (int i = 0; i < str.length(); i++) {
    EEPROM.write(addrOffset + i, str[i]);
  }
  EEPROM.write(addrOffset + str.length(), '\0'); // Add null character at the end
  EEPROM.commit(); // Save changes to the EEPROM
}




// #include <SPI.h>
// #include <Adafruit_BME280.h>
// #include <Adafruit_HDC1000.h>
// #include "Adafruit_SHT31.h"
// #include "Adafruit_HTU21DF.h"
// #include <SD.h>
// #include "FS.h"
// #include <HardwareSerial.h>
// #include "time.h"
// // #include <SoftwareSerial.h>
// #include <Adafruit_ADS1X15.h>
// #include <EEPROM.h>
// #ifndef ESP32
// #include <SoftwareSerial.h>
// #endif
// #include <PMserial.h> // Arduino library for PM sensors with serial interfacerduino library for PM sensors with serial interface
// // #include <esp_sleep.h>

// // #define SMS_TARGET  "+256787239229"
// // #define CALL_TARGET "+256788509024"

// SPIClass sdSPI(HSPI);
// #define SCK  18 //yellow
// #define MISO 19 //blue
// #define MOSI 23 //green
// #define CS  5 //orange
// // const char *broker = "0.tcp.ngrok.io";
// const char *broker = "137.63.185.130";
// const char *topicbme = "topic/bme";
// const char *topicsht = "topic/sht";
// const char *topichdc= "topic/hdc";
// const char *topichtu = "topic/htu";
// const char *status_topic = "topic/status";

// const char *topicAir1 = "topic/air1";
// const char *topicAir2= "topic/air2";
// const char *topicAir3 = "topic/air3";
// const char *topicb_volt = "topic/b_voltage";
// const char *topicb_curent = "topic/current";

// // Select your modem:
// #define TINY_GSM_MODEM_SIM800 // Modem is SIM800L
// // Set serial for debug console (to the Serial Monitor, default speed 115200)
// #define SerialMon Serial
// // Set serial for AT commands
// #define SerialAT Serial1

// // Define the serial console for debug prints, if needed
// #define TINY_GSM_DEBUG SerialMon

// // set GSM PIN, if any
// #define GSM_PIN ""

// // Your GPRS credentials, if any
// const char apn[] = "airtelgprs.com"; // APN (example: internet.vodafone.pt) use https://wiki.apnchanger.org
// const char gprsUser[] = "";
// const char gprsPass[] = "";
// #include <EEPROM.h>
// // SIM card PIN (leave empty, if not defined)
// const char simPIN[]   = ""; 
// Adafruit_ADS1115 ads;
// #include <Wire.h>
// #include <TinyGsmClient.h>
// #include <PubSubClient.h>
// #ifdef DUMP_AT_COMMANDS
//   #include <StreamDebugger.h>
//   StreamDebugger debugger(SerialAT, SerialMon);
//   TinyGsm modem(debugger);
// #else
//   TinyGsm modem(SerialAT);
// #endif

// TinyGsmClient client(modem);
// PubSubClient mqtt(client);

// float current1 = 0;
// int16_t adc0;
// float volts0;
// float sensitivity = 40.00;



// unsigned long previousMillis = 0;
// Adafruit_BME280 bmp; // I2C
// Adafruit_HTU21DF htu;
// Adafruit_SHT31 sht;
// Adafruit_HDC1000 hdc;

//  float sht1T;
//   float sht1H;
//   float sht2T;
//   float sht2H;
//   float sht3T;
//   float sht3H;

//   float htu1T;
//   float htu1H;
//   float htu2T;
//   float htu2H;
//   float htu3T;
//   float htu3H;

//   float bme1T;
//   float bme1H;
//   float bme2T;
//   float bme2H;
//   float bme3T;
//   float bme3H;
 
//   float hdc1T;
//   float hdc1H;
//   float hdc2T;
//   float hdc2H;
//   float hdc3T;
//   float hdc3H;


// // ESP32Time rtc(3600);

// void TCA9548A(uint8_t bus){
//   Wire.beginTransmission(0x70);  // TCA9548A address
//   Wire.write(1 << bus);          // send byte
//   Wire.endTransmission();
//   // Serial.print(bus);
// }

// // File myfile;
// #define SD_CS 5
// String dataMessage;


// #define RXD1 15 // To sensor TXD
// #define TXD1 0 // To sensor RXD
// // HardwareSerial mySerial4(0); // RX4, TX4
// #define RXD2 4 // To sensor TXD
// #define TXD2 14 // To sensor RXD

// #define RXD3 32 // To sensor TXD
// #define TXD3 33 // To sensor RXD

// // SoftwareSerial mySerial4(15, 4);
// // #ifndef ESP32

// // SerialPM pms1(PMSA003, mySerial4);
// // #else
// SerialPM pms1(PMS7003, Serial) ;// PMSx003, RX, TX
// // #endif
// SerialPM pms2(PMS7003, Serial1); // PMSx003, RX, TX
// SerialPM pms3(PMS7003, Serial2); 

// // struct pms5003data {
// //   uint16_t framelen;
// //   uint16_t pm10_standard, pm25_standard, pm100_standard;
// //   uint16_t pm10_env, pm25_env, pm100_env;
// //   uint16_t particles_03um, particles_05um, particles_10um, particles_25um, particles_50um, particles_100um;
// //   uint16_t unused;
// //   uint16_t checksum;
// // };
// // struct pms5003data data;


// // TTGO T-Call pins
// #define MODEM_RST            5
// #define MODEM_PWKEY          4
// #define MODEM_POWER_ON       23
// #define MODEM_TX             27
// #define MODEM_RX             26
// #define I2C_SDA              21
// #define I2C_SCL              22
// // BME280 pins
// #define I2C_SDA_2            18
// #define I2C_SCL_2            19
// #define IP5306_ADDR          0x75
// #define IP5306_REG_SYS_CTL0  0x00

// bool setPowerBoostKeepOn(int en){
//   Wire.beginTransmission(IP5306_ADDR);
//   Wire.write(IP5306_REG_SYS_CTL0);
//   if (en) {
//     Wire.write(0x37); // Set bit1: 1 enable 0 disable boost keep on
//   } else {
//     Wire.write(0x35); // 0x37 is default reg value
//   }
//   return Wire.endTransmission() == 0;
// }


// String gsmDateTime;
// String helloString;
// void setup() {
//  pinMode(13, OUTPUT);
//   digitalWrite(13,LOW);
// EEPROM.begin(512);
//   Wire.begin();
// Serial1.begin(9600, SERIAL_8N1, RXD3, TXD3);
// Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2);
// Serial.begin(9600,SERIAL_8N1, RXD1, TXD1);
// Serial.println("Started");
//   // SerialMon.begin(115200);
//     String myString = readStringFromEEPROM(40);
//   Serial.println(myString);
// initialize();
// air();
// voltage();

// //  String myString = readStringFromEEPROM(30);
// //   Serial.println(myString);
//   bool isOk = setPowerBoostKeepOn(1);
//  // Set modem reset, enable, power pins
//   pinMode(MODEM_PWKEY, OUTPUT);
//   pinMode(MODEM_RST, OUTPUT);
//   pinMode(MODEM_POWER_ON, OUTPUT);
//   digitalWrite(MODEM_PWKEY, LOW);
//   digitalWrite(MODEM_RST, HIGH);
//   digitalWrite(MODEM_POWER_ON, HIGH);
  
  
//   // pinMode(OUTPUT_2, OUTPUT);
  
//   SerialMon.println("Wait...");

//   // Set GSM module baud rate and UART pins
//   SerialAT.begin(9600, SERIAL_8N1, MODEM_RX, MODEM_TX);
//   delay(6000);

//   // Restart takes quite some time
//   // To skip it, call init() instead of restart()
//   SerialMon.println("Initializing modem...");
//   modem.restart();
//   // modem.init();

//   String modemInfo = modem.getModemInfo();
//   SerialMon.print("Modem Info: ");
//   SerialMon.println(modemInfo);

//   // Unlock your SIM card with a PIN if needed
//   if ( GSM_PIN && modem.getSimStatus() != 3 ) {
//     modem.simUnlock(GSM_PIN);
//   }

//  SerialMon.print("Connecting to APN: ");
//   SerialMon.print(apn);
//   if (!modem.gprsConnect(apn, gprsUser, gprsPass)) {
//     SerialMon.println(" fail");
//     ESP.restart();
//   }
//   else {
//     SerialMon.println(" OK");
//   }
  
//   if (modem.isGprsConnected()) {
//     SerialMon.println("GPRS connected");
//   }
// SerialAT.println("AT+CCLK?");
//   delay(1000);
//   // dateTime = modem.readString(); // read the response o
//   // Serial.println(dateTime);
//    ShowSerialData();
// //   String dateTime = modem.getGSMDateTime();
// mqtt.setServer(broker,8383);
// if(!mqtt.connected()){
//   reconnect();
// }  
// mqtt.loop();
// send_data();
// // initialize_sd();
// // WriteFile();
// //   SerialMon.print("Current Date and Time: ");
// //  SerialMon.println(dateTime);
// pms1.sleep();
// pms2.sleep();
// pms3.sleep(); 
// esp_sleep_enable_timer_wakeup(10 * 1000000);
// esp_deep_sleep_start();
// }

// void loop() {
//   // put your main code here, to run repeatedly:

// }
// void reconnect(){

// unsigned long start_time = 0; // declare a variable to store the start time
// int delay_time = 1000; // set the delay time to 5 seconds

// while (!mqtt.connected()) {
//     SerialMon.println("=== Attempting Connection... ===");

//     start_time = millis(); // record the start time

//     // Reconnect every 10 seconds
//     String clientId = "ESP8266-";
//     clientId += String(random(0xffff), HEX);

//     if (mqtt.connect(clientId.c_str())){
//         Serial.println("Connected");
//         mqtt.publish(status_topic, "ESP32 Alive");
//     } else {
//         Serial.println(mqtt.state());
//     }

//     // wait for the remaining time in the delay period
//     while (millis() - start_time < delay_time) {}
// }




// //  }

//   //   uint32_t t = millis();
//   //   if (t - lastReconnectAttempt > 10000L) {
//   //     lastReconnectAttempt = t;
//   //     if (mqttConnect()) {
//   //       lastReconnectAttempt = 0;
//   //     }
//   //   }
//   //   delay(100);
//   //   return;
//   // }
// }

// // void getNtpTime(){
// //   //connect to WiFi
// //   Serial.printf("connecting to %s ", ssid);
// //   WiFi.begin(ssid, password);
// //   while (WiFi.status() != WL_CONNECTED) {
// //     // delay(500);
// //     Serial.print(".");
// //   }
// //   Serial.println(" connected");
  
// //   // init, get NTP time, set RTC
// //   configTzTime(timeZone,  ntpServer);

// //   // debug 
// //   Serial.print("get NTP time, RTC set to: ");
// //   printLocalTime();
// //   Serial.println();

//   //disconnect WiFi as it's no longer needed
//   // WiFi.disconnect(true);
//   // WiFi.mode(WIFI_OFF);
// // }

// // void setTimezone(){
// //   Serial.print("set timezone to ");
// //   Serial.println(timeZone);
// //   setenv("TZ",timeZone,1);  //  set timezone 
// //   tzset();
// // }
// void ShowSerialData()
// {
//   while(SerialAT.available()!=0)
//   gsmDateTime += (char) SerialAT.read();
//    SerialMon.print("GSM Date/Time: ");
//   SerialMon.println(gsmDateTime);
//  helloString = gsmDateTime.substring(10,30);
// Serial.println(helloString);
// writeStringToEEPROM(40,helloString);
// //  Serial.write(SerialAT.read());
//   //  delay(5000); 
   
  
// }
// // void printLocalTime(){ 
// //   if(!getLocalTime(&timeinfo)){
// //     Serial.println("failed to obtain time");
// //     return;
// //   }

// //   // print time human readable
// //   char strftime_buf[64];
// //   strftime(strftime_buf, sizeof(strftime_buf), "%Y-%m-%d %H:%M:%S", &timeinfo);
// //   Serial.println(strftime_buf);

// //   // print epoch time 
// //   time_t epoch_ts = mktime(&timeinfo);  // get epoch time from struct
// //   Serial.println("epoch time is " + String(epoch_ts));
// // }
// String readStringFromEEPROM(int addrOffset) {
//   String str = "";
//   char ch;
//   int i = 0;
//   while ((ch = EEPROM.read(addrOffset + i)) != '\0') {
//     str += ch;
//     i++;
//   }
//   for (int i = 0; i < str.length(); i++) {
//   char ch = str[i];
//   if (ch != ',') {
//      str = ch;
//     // Serial.print(ch);
//   }
//   return str;
// }
// void writeStringToEEPROM(int addrOffset, String str) {
//   for (int i = 0; i < str.length(); i++) {
//     EEPROM.write(addrOffset + i, str[i]);
//   }
//   EEPROM.write(addrOffset + str.length(), '\0'); // Add null character at the end
//   EEPROM.commit(); // Save changes to the EEPROM
// }



