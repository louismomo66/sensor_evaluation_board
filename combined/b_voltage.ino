
// void current(){

//    adc0 = ads.readADC_SingleEnded(0);
//   volts0 = ads.computeVolts(adc0);
//   current1 = ((adc0-13164)*0.1875/sensitivity);

//   // Serial.println("------------------");
//   // Serial.print("!ADC value: ");
//   // Serial.print(adc0);
//   // Serial.print(" ");
//   // Serial.print(volts0);
//   // Serial.println("V");
//   // Serial.println("--------------------");
//   // Serial.print("Current ");
//   // Serial.print(current1);
//   String cur =String(current1);
//   EEPROM.put(9, current1);
//   mqtt.publish(topicb_curent, cur.c_str());
//   // Serial.println("A");
//   // delay(3000);
// }


 void voltage(){
  TCA9548A(7);
  int offset =20;
  float volts0,volts1;
  int16_t adc0,adc1;
  adc0 = ads.readADC_SingleEnded(0);
  volts0 = ads.computeVolts(adc0);
  int volt = adc0;// read the input
  double voltage = map(volt,0,65535, 0, 2500) + offset;// ma
  voltage /=100;// divide by 100 to get the decimal values
  // Serial.print("Voltage: ");
  // Serial.print(voltage*2.21-0.1);//print the voltge
  // float adc_sum = 0.0;
  // int num_readings = 100;
  // int16_t adc1;
  // adc1 = ads.readADC_SingleEnded(1);
  // for (int i = 0; i < num_readings; i++) {
  //   adc_sum += adc1;
  //   delay(1);
  // }
  
  // float adc_average = adc_sum / num_readings;
  // float voltage = adc_average * 3.3 / 4095.0;

  // // Serial.println("Voltage: ");
  // // Serial.println(adc_average);
  // //  Serial.print(adc_average*0.0006099016-0.22);
  // //  Serial.println(" mA");
  // // Serial.println(voltage*6.191369606-0.18);
  float bat_volt = voltage*2.213;
   int bat_percentage = mapfloat(voltage, 2.4, 5.01, 0, 100); //2.8V as Battery Cut off Voltage & 4.2V as Maximum Voltage
 
  if (bat_percentage >= 100)
  {
    bat_percentage = 100;
  }
  if (bat_percentage <= 0)
  {
    bat_percentage = 1;
  }
 EEPROM.put(0, bat_volt);
 EEPROM.put(9, bat_percentage);
  // Serial.println(voltage, 3);
  // delay(1000);
  // Serial.println( bat_volt);
  // String volts =String(bat_volt);
  // mqtt.publish(topicb_volt, volts.c_str());
  // return bat_volt;
}
float mapfloat(float x, float in_min, float in_max, float out_min, float out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}