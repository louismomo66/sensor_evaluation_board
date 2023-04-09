void initialize_sd(){
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
  File myfile = SD.open("/sensors.csv");
    File myfile2 = SD.open("/air.csv");
   if(!myfile) {
    Serial.println("File doens't exist");
    Serial.println("Creating file...");
    writeFile(SD, "/sensors.csv", "ESP32 and SD Card \r\n");
  }
  else {
    Serial.println("File already exists");  
  }
  if(!myfile2){
    Serial.println("File doens't exist");
    Serial.println("Creating file...");
    writeFile(SD, "/air.csv", "ESP32 Air data \r\n");
  }
  else {
    Serial.println("File already exists");  
  }
  myfile.close();
  myfile2.close();
}




void WriteFile(){
// // CS is connected with D5
// // MOSI is connected with D23
// // SCK is connected with D18
// // // MISO is connected with D19
// // bme();
// // sht3();
// // hdc1();
// // htu1();
//   // open the file. note that only one file can be open at a time,
//   // so you have to close this one before opening another.
//   // myfile = SD.open("/sensors.csv", FILE_WRITE);
//   // if the file opened okay, write to it:
//   // if (myfile) {
    String air_1 = air1string();
    String air_2 =air2string();
    String air_3 =air3string();
    String dataMessage2 = air_1 + "\n" + air_2 + "\n" + air_3 +"\n" ;
    appendFile(SD, "/air.csv", dataMessage2.c_str());

    String bme_all =bmeString();
    String hdc_all =hdcString();
    String htu_all =htuString();
    String sht_all =shtString();
    String dataMessage = bme_all + "\n" + hdc_all + "\n" + htu_all + "\n" + sht_all + "\n";
    appendFile(SD, "/sensors.csv", dataMessage.c_str());

    
      // myfile.println(rtc.getDateTime(true));
  // }
//   //     myfile.println("SHT");
//   //     myfile.print("TEMP: ");
//   //     myfile.print(sht1T);
//   //     myfile.print(" ");
//   //     myfile.print("HUM: ");
//   //     myfile.println(sht1H);
//   //     myfile.print("TEMP: ");
//   //     myfile.print(sht2T);
//   //     myfile.print(" ");
//   //     myfile.print("HUM: ");
//   //     myfile.println(sht2H);
//   //     myfile.print("TEMP: ");
//   //     myfile.print(sht3T);
//   //     myfile.print(" ");
//   //     myfile.print("HUM: ");
//   //     myfile.println(sht3H);
//   //     myfile.print(",");
//   //     myfile.println("BME");
//   //     myfile.print("TEMP: ");
//   //     myfile.print(bme1T);
//   //     myfile.print(" ");
//   //     myfile.print("HUM: ");
//   //     myfile.println(bme1H);
//   //      myfile.print("TEMP: ");
//   //     myfile.print(bme2T);
//   //     myfile.print(" ");
//   //     myfile.print("HUM: ");
//   //     myfile.println(bme2H);
//   //      myfile.print("TEMP: ");
//   //     myfile.print(bme3T);
//   //     myfile.print(" ");
//   //     myfile.print("HUM: ");
//   //     myfile.println(bme3H);
//   //    myfile.print(",");
//   //     myfile.println("HDC");
//   //     myfile.print("TEMP: ");
//   //     myfile.print(hdc1T);
//   //     myfile.print(" ");
//   //     myfile.print("HUM: ");
//   //     myfile.println(hdc1H);
//   //      myfile.print("TEMP: ");
//   //     myfile.print(hdc2T);
//   //     myfile.print(" ");
//   //     myfile.print("HUM: ");
//   //     myfile.println(hdc2H);
//   //     myfile.print("TEMP: ");
//   //     myfile.print(hdc3T);
//   //      myfile.print(" ");
//   //     myfile.print("HUM: ");
//   //     myfile.println(hdc3H);
//   //     myfile.print(",");
//   //     myfile.println("HDC");
//   //     myfile.print("TEMP: ");
//   //     myfile.print(htu1T);
//   //     myfile.print(" ");
//   //     myfile.print("HUM: ");
//   //     myfile.println(htu1H);
//   //     myfile.print("TEMP: ");
//   //     myfile.print(htu2T);
//   //     myfile.print(" ");
//   //     myfile.print("HUM: ");
//   //     myfile.println(htu2H);
//   //     myfile.print("TEMP: ");
//   //     myfile.print(htu3T);
//   //     myfile.print(" ");
//   //     myfile.print("HUM: ");
//   //     myfile.println(htu3H);
//   //    myfile.close();
//   //   Serial.println("completed.");
//   // } 
//   // // if the file didn't open, print an error:
//   // else {
//   //   Serial.println("error opening file ");
    
//   // }
}

void writeFile(fs::FS &fs, const char * path, const char * message) {
  Serial.printf("Writing file: %s\n", path);
  File myfile = fs.open(path, FILE_WRITE);
  File myfile2 = fs.open(path, FILE_WRITE);
  if(!myfile) {
    Serial.println("Failed to open file for writing");
    return;
  }
  if(!myfile2){
     Serial.println("Failed to open file for writing");
    return;
  }
  if(myfile.print(message)) {
    Serial.println("File written");
  } else {
    Serial.println("Write failed");
  }
  if(myfile2.print(message)){
    Serial.println("File air written");
  }
  else {
    Serial.println("Write failed");
  }
  myfile.close();
  myfile2.close();
}
// Append data to the SD card (DON'T MODIFY THIS FUNCTION)
void appendFile(fs::FS &fs, const char * path, const char * message) {
  Serial.printf("Appending to file: %s\n", path);
  File myfile = fs.open(path, FILE_APPEND);
  File myfile2 = fs.open(path, FILE_APPEND);
  if(!myfile) {
    Serial.println("Failed to open file for appending");
    return;
  }
  if(!myfile2){
     Serial.println("Failed to open file for appending");
    return;
  }
  if(myfile.print(message)) {
    Serial.println("Message appended");
  } else {
    Serial.println("Append failed");
  }
  if(myfile2.print(message)){
    Serial.println("File air appended");
  }
  else {
    Serial.println("Append failed");
  }
  myfile.close();
  myfile2.close();
}
// void closeFile()
// {
//   if (myfile)
//   {
//     myfile.close();
//     Serial.println("File closed");
//   }
// }
void readsd(){
  File myfile2 = SD.open("/air.csv");
  if (myfile2) {
    Serial.println("File opened successfully:");
    
    // Read file contents
    while (myfile2.available()) {
      Serial.write(myfile2.read());
    }
    
    // Close file
    myfile2.close();
    Serial.println("\nFile closed.");
  } else {
    Serial.println("Error opening file!");
  }
}