void send_data(){
  //  if (!mqtt.connected()) {
  //   SerialMon.println("=== MQTT NOT CONNECTED ===");
  //   // Reconnect every 10 seconds
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

    String bme_all =bmeString();
    String hdc_all =hdcString();
    String htu_all =htuString();
    String sht_all =shtString();

    String air1 =air1string();
    String air2 =air2string();
    String air3 =air3string();
    String volts =String(voltage());
    mqtt.publish(topicAir1 , air1.c_str());
    mqtt.publish(topicAir2 , air2.c_str());
    mqtt.publish(topicAir3 , air3.c_str());
    // Serial.println(bme_all);
    mqtt.publish(topicbme, bme_all.c_str());
    mqtt.publish(topichdc, hdc_all.c_str());
    mqtt.publish(topichtu, htu_all.c_str());
    mqtt.publish(topicsht, sht_all.c_str());
    mqtt.publish(topicb_volt, volts.c_str());
}