void air(){
pms1.init();
  pms1.read();
   if (pms1) {
    Serial.print(F("Sensor 1 - PM1.0 "));
    Serial.print(pms1.pm01);
    Serial.print(F(", "));
    Serial.print(F("PM2.5 "));
    Serial.print(pms1.pm25);
    Serial.print(F(", "));
    Serial.print(F("PM10 "));
    Serial.print(pms1.pm10);
    Serial.println(F(" [ug/m3]"));
    
  }
  pms2.init();
  pms2.read();
  if (pms2) {
    Serial.print(F("Sensor 2 - PM1.0 "));
    Serial.print(pms2.pm01);
    Serial.print(F(", "));
    Serial.print(F("PM2.5 "));
    Serial.print(pms2.pm25);
    Serial.print(F(", "));
    Serial.print(F("PM10 "));
    Serial.print(pms2.pm10);
    Serial.println(F(" [ug/m3]"));
  }
  pms3.init();
  pms3.read();
  if (pms3) {
    Serial.print(F("Sensor 3 - PM1.0 "));
    Serial.print(pms3.pm01);
    Serial.print(F(", "));
    Serial.print(F("PM2.5 "));
    Serial.print(pms3.pm25);
    Serial.print(F(", "));
    Serial.print(F("PM10 "));
    Serial.print(pms3.pm10);
    Serial.println(F(" [ug/m3]"));
  }
}


// void air(){
//   //  for (int i= 0; i<4; i++){
// //  if (readPMSdata(&Serial1)) {
//   if (readPMSdata(&mySerial4)) {
//     // reading data was successful!
//     Serial.println();
//     Serial.println("First sensor");
//    Serial.println("---------------------------------------");

//     Serial.print("PM 1.0: "); Serial.print(data.pm10_standard);Serial.println("(u/g3)");
//     Serial.print("PM 2.5: "); Serial.print(data.pm25_standard);Serial.println("(u/g3)");
//     Serial.print("PM 10: "); Serial.print(data.pm100_standard);Serial.println("(u/g3)");
   
//     // Serial.print("Particles > 0.3um / 0.1L air:"); Serial.println(data.particles_03um);
//     // Serial.print("Particles > 0.5um / 0.1L air:"); Serial.println(data.particles_05um);
//     // Serial.print("Particles > 1.0um / 0.1L air:"); Serial.println(data.particles_10um);
//     // Serial.print("Particles > 2.5um / 0.1L air:"); Serial.println(data.particles_25um);
//     // Serial.print("Particles > 5.0um / 0.1L air:"); Serial.println(data.particles_50um);
//     // Serial.print("Particles > 10.0 um / 0.1L air:"); Serial.println(data.particles_100um);
//     Serial.println("---------------------------------------");
//     }

//     if (readPMSdata(&Serial2)) {
//     // reading data was successful!
//     Serial.println();
//     Serial.println("Second Sensor");
//     Serial.println("---------------------------------------");

//     Serial.print("PM 1.0: "); Serial.print(data.pm10_standard);Serial.println("(u/g3)");
//     Serial.print("PM 2.5: "); Serial.print(data.pm25_standard);Serial.println("(u/g3)");
//     Serial.print("PM 10: "); Serial.print(data.pm100_standard);Serial.println("(u/g3)");


//     // Serial.print("Particles > 0.3um / 0.1L air:"); Serial.println(data.particles_03um);
//     // Serial.print("Particles > 0.5um / 0.1L air:"); Serial.println(data.particles_05um);
//     // Serial.print("Particles > 1.0um / 0.1L air:"); Serial.println(data.particles_10um);
//     // Serial.print("Particles > 2.5um / 0.1L air:"); Serial.println(data.particles_25um);
//     // Serial.print("Particles > 5.0um / 0.1L air:"); Serial.println(data.particles_50um);
//     // Serial.print("Particles > 10.0 um / 0.1L air:"); Serial.println(data.particles_100um);
//     Serial.println("---------------------------------------");
//     }

//     if (readPMSdata(&SerialMon)) {
//     // reading data was successful!
//     Serial.println();
//     Serial.println("Third Sensor");
//     Serial.println("---------------------------------------");

//     Serial.print("PM 1.0: "); Serial.print(data.pm10_standard);Serial.println("(u/g3)");
//     Serial.print("PM 2.5: "); Serial.print(data.pm25_standard);Serial.println("(u/g3)");
//     Serial.print("PM 10: "); Serial.print(data.pm100_standard);Serial.println("(u/g3)");


//     // Serial.print("Particles > 0.3um / 0.1L air:"); Serial.println(data.particles_03um);
//     // Serial.print("Particles > 0.5um / 0.1L air:"); Serial.println(data.particles_05um);
//     // Serial.print("Particles > 1.0um / 0.1L air:"); Serial.println(data.particles_10um);
//     // Serial.print("Particles > 2.5um / 0.1L air:"); Serial.println(data.particles_25um);
//     // Serial.print("Particles > 5.0um / 0.1L air:"); Serial.println(data.particles_50um);
//     // Serial.print("Particles > 10.0 um / 0.1L air:"); Serial.println(data.particles_100um);
//     Serial.println("---------------------------------------");
//     }
//     //  delay(1000);
//     // }
//  }
String air1string(){
  pms1.init();
  delay(10);
  pms1.read();
  if (pms1) {
    // reading data was successf
   String one = "PM1.0:," + String(pms1.pm01);
    String two = "PM2.5:," + String(pms1.pm25);
    String three = "PM10:," + String(pms1.pm10);

    String air1 = "One:," + one +","+ two +","+ three;
    // Serial.print("Particles > 0.3um / 0.1L air:"); Serial.println(data.particles_03um);
    // Serial.print("Particles > 0.5um / 0.1L air:"); Serial.println(data.particles_05um);
    // Serial.print("Particles > 1.0um / 0.1L air:"); Serial.println(data.particles_10um);
    // Serial.print("Particles > 2.5um / 0.1L air:"); Serial.println(data.particles_25um);
    // Serial.print("Particles > 5.0um / 0.1L air:"); Serial.println(data.particles_50um);
    // Serial.print("Particles > 10.0 um / 0.1L air:"); Serial.println(data.particles_100um);
  return air1;
    }}

String air2string(){
  pms2.init();
  pms2.read();
    if (pms2) {
   String one1 = "PM1.0:,"+ String(pms2.pm01);
    String two2 = "PM2.5:," + String(pms2.pm25);
    String three3 = "PM10:,"+ String(pms2.pm10);

    // String air2 = "Two: " + one1+ two2 + three3 + "(u/m3)";
    String air2= "Two:," + one1 +","+ two2 +","+ three3;
    // Serial.print("Particles > 0.3um / 0.1L air:"); Serial.println(data.particles_03um);
    // Serial.print("Particles > 0.5um / 0.1L air:"); Serial.println(data.particles_05um);
    // Serial.print("Particles > 1.0um / 0.1L air:"); Serial.println(data.particles_10um);
    // Serial.print("Particles > 2.5um / 0.1L air:"); Serial.println(data.particles_25um);
    // Serial.print("Particles > 5.0um / 0.1L air:"); Serial.println(data.particles_50um);
    // Serial.print("Particles > 10.0 um / 0.1L air:"); Serial.println(data.particles_100um);
   return air2;
    }}

String air3string(){
  pms3.init();
  pms3.read();
    if (pms3) {
    // reading data was successful!
 String one11 = "PM1.0:," + String(pms3.pm01);
    String two22 = "PM2.5:," + String(pms3.pm25);
    String three33 = "PM10:," + String(pms3.pm10);

    // String air3 = "Three: " + one11+ two22 + three33 + "(u/m3)";
    String air3 = "Three:," + one11 +","+ two22 +","+ three33;
    // Serial.print("Particles > 0.3um / 0.1L air:"); Serial.println(data.particles_03um);
    // Serial.print("Particles > 0.5um / 0.1L air:"); Serial.println(data.particles_05um);
    // Serial.print("Particles > 1.0um / 0.1L air:"); Serial.println(data.particles_10um);
    // Serial.print("Particles > 2.5um / 0.1L air:"); Serial.println(data.particles_25um);
    // Serial.print("Particles > 5.0um / 0.1L air:"); Serial.println(data.particles_50um);
    // Serial.print("Particles > 10.0 um / 0.1L air:"); Serial.println(data.particles_100um);
    return air3;
    }
   
 }

// boolean readPMSdata(Stream *s) {
//   if (! s->available()) {
//     return false;
//   }

//   // Read a byte at a time until we get to the special '0x42' start-byte
//   if (s->peek() != 0x42) {
//     s->read();
//     return false;
//   }

//   // Now read all 32 bytes
//   if (s->available() < 32) {
//     return false;
//   }

//   uint8_t buffer[32];
//   uint16_t sum = 0;
//   s->readBytes(buffer, 32);

//   // get checksum ready
//   for (uint8_t i = 0; i < 30; i++) {
//     sum += buffer[i];
//   }

//   /* debugging
//     for (uint8_t i=2; i<32; i++) {
//     Serial.print("0x"); Serial.print(buffer[i], HEX); Serial.print(", ");
//     }
//     Serial.println();
//   */

//   // The data comes in endian'd, this solves it so it works on all platforms
//   uint16_t buffer_u16[15];
//   for (uint8_t i = 0; i < 15; i++) {
//     buffer_u16[i] = buffer[2 + i * 2 + 1];
//     buffer_u16[i] += (buffer[2 + i * 2] << 8);
//   }

//   // put it into a nice struct :)
//   memcpy((void *)&data, (void *)buffer_u16, 30);

//   if (sum != data.checksum) {
//     Serial.println("Checksum failure");
//     return false;
//   }
//   // success!
//   return true;
// }