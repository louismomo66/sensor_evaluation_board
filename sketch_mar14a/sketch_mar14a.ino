/*
 * SD Card Module Interfacing with ESP32 Wifi + Bluetooth Module
 * https://www.electroniclinic.com/
 */

#include "FS.h"
#include "SD.h"
#include <SPI.h>

#define SD_CS 5
String dataMessage;

int Vresistor = 36; // VP pin which is the GPIO36 pin this is adc0
int Vrdata;

void setup() {
  Serial.begin(115200);
  // pinMode(13, OUTPUT); // i use this to supply 3.3volts to the variable resistor
  // digitalWrite(13, HIGH);
  // Initialize SD card
  SD.begin(SD_CS);  
  if(!SD.begin(SD_CS)) {
    Serial.println("Card Mount Failed");
    return;
  }
  uint8_t cardType = SD.cardType();
  if(cardType == CARD_NONE) {
    Serial.println("No SD card attached");
    return;
  }
  Serial.println("Initializing SD card...");
  if (!SD.begin(SD_CS)) {
    Serial.println("ERROR - SD card initialization failed!");
    return;    // init failed
  }
  File file = SD.open("/data.csv");
  if(!file) {
    Serial.println("File doens't exist");
    Serial.println("Creating file...");
    writeFile(SD, "/data.csv", "ESP32 and SD Card \r\n");
  }
  else {
    Serial.println("File already exists");  
  }
  file.close();
}
void loop() {

    // ReadVresistor();
    logSDCard();
    delay(5000); //Wait for 5 seconds before writing the next data 
}

// Write the sensor readings on the SD card
void logSDCard() {
  dataMessage =  "Variable Resistor = " + String(Vrdata) + "\n";
  Serial.print("Save data: ");
  Serial.println(dataMessage);
  appendFile(SD, "/data.csv", dataMessage.c_str());
}
// Write to the SD card (DON'T MODIFY THIS FUNCTION)
void writeFile(fs::FS &fs, const char * path, const char * message) {
  Serial.printf("Writing file: %s\n", path);
  File file = fs.open(path, FILE_WRITE);
  if(!file) {
    Serial.println("Failed to open file for writing");
    return;
  }
  if(file.print(message)) {
    Serial.println("File written");
  } else {
    Serial.println("Write failed");
  }
  file.close();
}
// Append data to the SD card (DON'T MODIFY THIS FUNCTION)
void appendFile(fs::FS &fs, const char * path, const char * message) {
  Serial.printf("Appending to file: %s\n", path);
  File file = fs.open(path, FILE_APPEND);
  if(!file) {
    Serial.println("Failed to open file for appending");
    return;
  }
  if(file.print(message)) {
    Serial.println("Message appended");
  } else {
    Serial.println("Append failed");
  }
  file.close();
}
void ReadVresistor()
{
  Vrdata = analogRead(Vresistor);
  Serial.println(Vrdata);
}