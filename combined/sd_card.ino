void WriteFile(){
  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  myfile = SD.open("/sensors.csv", FILE_WRITE);
  // if the file opened okay, write to it:
  if (myfile) {
  
      myfile.println(rtc.getDateTime(true));
      myfile.println("SHT");
      myfile.print("TEMP: ");
      myfile.print(sht1T);
      myfile.print(" ");
      myfile.print("HUM: ");
      myfile.println(sht1H);
      myfile.print("TEMP: ");
      myfile.print(sht2T);
      myfile.print(" ");
      myfile.print("HUM: ");
      myfile.println(sht2H);
      myfile.print("TEMP: ");
      myfile.print(sht3T);
      myfile.print(" ");
      myfile.print("HUM: ");
      myfile.println(sht3H);
      myfile.print(",");
      myfile.println("BME");
      myfile.print("TEMP: ");
      myfile.print(bme1T);
      myfile.print(" ");
      myfile.print("HUM: ");
      myfile.println(bme1H);
       myfile.print("TEMP: ");
      myfile.print(bme2T);
      myfile.print(" ");
      myfile.print("HUM: ");
      myfile.println(bme2H);
       myfile.print("TEMP: ");
      myfile.print(bme3T);
      myfile.print(" ");
      myfile.print("HUM: ");
      myfile.println(bme3H);
     myfile.print(",");
      myfile.println("HDC");
      myfile.print("TEMP: ");
      myfile.print(hdc1T);
      myfile.print(" ");
      myfile.print("HUM: ");
      myfile.println(hdc1H);
       myfile.print("TEMP: ");
      myfile.print(hdc2T);
      myfile.print(" ");
      myfile.print("HUM: ");
      myfile.println(hdc2H);
      myfile.print("TEMP: ");
      myfile.print(hdc3T);
       myfile.print(" ");
      myfile.print("HUM: ");
      myfile.println(hdc3H);
      myfile.print(",");
      myfile.println("HDC");
      myfile.print("TEMP: ");
      myfile.print(htu1T);
      myfile.print(" ");
      myfile.print("HUM: ");
      myfile.println(htu1H);
      myfile.print("TEMP: ");
      myfile.print(htu2T);
      myfile.print(" ");
      myfile.print("HUM: ");
      myfile.println(htu2H);
      myfile.print("TEMP: ");
      myfile.print(htu3T);
      myfile.print(" ");
      myfile.print("HUM: ");
      myfile.println(htu3H);
    //  myfile.close();
    Serial.println("completed.");
  } 
  // if the file didn't open, print an error:
  else {
    Serial.println("error opening file ");
    
  }
}