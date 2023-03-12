void air(){
  //  for (int i= 0; i<4; i++){
//  if (readPMSdata(&Serial1)) {
  if (readPMSdata(&mySerial4)) {
  
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