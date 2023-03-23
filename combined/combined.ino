#include <Wire.h>
#include <SPI.h>
#include <Adafruit_BME280.h>
#include <Adafruit_HDC1000.h>
#include "Adafruit_SHT31.h"
#include "Adafruit_HTU21DF.h"
#include <SD.h>
#include <ESP32Time.h>
#include <SoftwareSerial.h>
// #include <esp_sleep.h>
// #define SIM800L_IP5306_VERSION_20190610
// // Define the serial console for debug prints, if needed
// #define DUMP_AT_COMMANDS
// #define TINY_GSM_DEBUG          SerialMon
// #include "utilities.h"
// // Set serial for debug console (to the Serial Monitor, default speed 115200)
// #define SerialMon Serial
// // Set serial for AT commands (to the module)
// #define SerialAT  Serial1

// // Configure TinyGSM library
// #define TINY_GSM_MODEM_SIM800          // Modem is SIM800
// #define TINY_GSM_RX_BUFFER      1024   // Set RX buffer to 1Kb

// #include <TinyGsmClient.h>

// #ifdef DUMP_AT_COMMANDS
// #include <StreamDebugger.h>
// StreamDebugger debugger(SerialAT, SerialMon);
// TinyGsm modem(debugger);
// #else
// TinyGsm modem(SerialAT);
// #endif
// // Set phone numbers, if you want to test SMS and Calls
#define SMS_TARGET  "+256787239229"
// #define CALL_TARGET "+256788509024"


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
//#define DUMP_AT_COMMANDS
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
const char *broker = "0.tcp.in.ngrok.io";
const char *topicbme = "topic/bme";
const char *topicsht = "topic/sht";
const char *topichdc= "topic/hdc";
const char *topichtu = "topic/htu";
const char *status_topic = "topic/status";

const char *topicAir1 = "topic/air1";
const char *topicAir2= "topic/air2";
const char *topicAir3 = "topic/air3";
const char *topicb_volt = "topic/b_voltage";
#include <TinyGsmClient.h>
#include <PubSubClient.h>

#ifdef DUMP_AT_COMMANDS
#include <StreamDebugger.h>
StreamDebugger debugger(SerialAT, SerialMon);
TinyGsm modem(debugger);
#else
TinyGsm modem(SerialAT);
#endif

TinyGsmClient client(modem);
PubSubClient mqtt(client);

int ledStatus = LOW;

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
  // Serial.print(bus);
}

// File myfile;
#define SD_CS 5
String dataMessage;

int Vresistor = 36; // VP pin which is the GPIO36 pin this is adc0
int Vrdata;
// #define RXD1 15 // To sensor TXD
// #define TXD1 4 // To sensor RXD
SoftwareSerial mySerial4(15, 4); // RX4, TX4
#define RXD2 12 // To sensor TXD
#define TXD2 14 // To sensor RXD

#define RXD3 32 // To sensor TXD
#define TXD3 33 // To sensor RXD


struct pms5003data {
  uint16_t framelen;
  uint16_t pm10_standard, pm25_standard, pm100_standard;
  uint16_t pm10_env, pm25_env, pm100_env;
  uint16_t particles_03um, particles_05um, particles_10um, particles_25um, particles_50um, particles_100um;
  uint16_t unused;
  uint16_t checksum;
};
struct pms5003data data;


void setup() {

Wire.begin();
mySerial4.begin(9600);
Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2);
SerialMon.begin(9600, SERIAL_8N1, RXD3, TXD3);
// Serial.begin(9600);
// pinMode(36,INPUT);
initialize_sd();
initialize();
WriteFile();
setupModem();

unsigned long start_time = 0; // declare a variable to store the start time

SerialMon.println("Wait...");

// Set GSM module baud rate and UART pins
SerialAT.begin(9600, SERIAL_8N1, MODEM_RX, MODEM_TX);

start_time = millis(); // record the start time

// Wait for 6 seconds before initializing the modem
while (millis() - start_time < 6000) {}

SerialMon.println("Initializing modem...");
modem.restart();

SerialMon.print("Waiting for network...");

start_time = millis(); // record the start time

while (!modem.waitForNetwork()) {
  if (millis() - start_time > 10000) { // exit the loop after 10 seconds
    SerialMon.println(" fail");
    return;
  }
}

SerialMon.println(" success");

if (modem.isNetworkConnected()) {
  SerialMon.println("Network connected");
}

// GPRS connection parameters are usually set after network registration
SerialMon.print(F("Connecting to "));
SerialMon.print(apn);

start_time = millis(); // record the start time

while (!modem.gprsConnect(apn, gprsUser, gprsPass)) {
  if (millis() - start_time > 10000) { // exit the loop after 10 seconds
    SerialMon.println(" fail");
    return;
  }
}

SerialMon.println(" success");

if (modem.isGprsConnected()) {
  SerialMon.println("GPRS connected");
}


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

//     // GPRS connection parameters are usually set after network registration
//     SerialMon.print(F("Connecting to "));
//     SerialMon.print(apn);
//     if (!modem.gprsConnect(apn, gprsUser, gprsPass)) {
//         SerialMon.println(" fail");
//         delay(10000);
//         return;
//     }
//     SerialMon.println(" success");

//     if (modem.isGprsConnected()) {
//         SerialMon.println("GPRS connected");
//     }

    // MQTT Broker setup
mqtt.setServer(broker,12457);
if(!mqtt.connected()){
  reconnect();
}
mqtt.loop();
// air();
// bme();
// hdc1();
// htu1();
// sht3();
send_data();
Serial.println("************");
// air();
// send_data();
// rtc.setTime(10, 15, 17, 10, 3, 2023);  // 17th Jan 2021 15:24:30

 // To send an SMS, call modem.sendSMS(SMS_TARGET, smsMessage)
  // String smsMessage = "Hello from ESP32!";
  // if(modem.sendSMS(SMS_TARGET, smsMessage)){
  //   SerialMon.println(smsMessage);
  // }
  // else{
  //   SerialMon.println("SMS failed to send");
  // }

// Serial.println("Entering deep sleep mode for 1 minute...");
//  // 60e6 microseconds = 1 minute
// esp_sleep_enable_timer_wakeup( * 1000000);
// esp_deep_sleep_start();
 // 1 minute
// digitalWrite(MODEM_POWER_ON, HIGH);
// Serial.println("Going to sleep now");
// delay(5000);
esp_sleep_enable_timer_wakeup(45 * 1000000);
esp_deep_sleep_start();


}



void loop()
{


}
void reconnect(){

unsigned long start_time = 0; // declare a variable to store the start time
int delay_time = 5000; // set the delay time to 5 seconds

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


// while (!mqtt.connected()) {
//     SerialMon.println("=== Attempting Connection... ===");
//     // Reconnect every 10 seconds
//     String clientId = "ESP8266-";
//     clientId += String(random(0xffff),HEX);
// if (mqtt.connect(clientId.c_str())){
//   Serial.println("Connected");
//   mqtt.publish(status_topic,"ESP32 Alive");
// }else{
//   Serial.println(mqtt.state());
//   delay(5000);
// }
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
