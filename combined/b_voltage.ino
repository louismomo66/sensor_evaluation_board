float voltage(){
  float adc_sum = 0.0;
  int num_readings = 100;
  
  for (int i = 0; i < num_readings; i++) {
    adc_sum += analogRead(36);
    delay(1);
  }
  
  float adc_average = adc_sum / num_readings;
  float voltage = adc_average * 3.3 / 4095.0;

  // Serial.println("Voltage: ");
  // Serial.println(adc_average);
  //  Serial.print(adc_average*0.0006099016-0.22);
  //  Serial.println(" mA");
  // Serial.println(voltage*6.191369606-0.18);
  float bat_volt = voltage*6.191369606;
  // Serial.println(voltage, 3);
  // delay(1000);
  return bat_volt;
}