void TestRotaryEncoder(void) {
  //Might be able to get away with using a neat little library written for this general type of encoder


  //Calculate the time since the last reading
  tslEncoderReading = millis() - encoderReadingTime;

  if (tslEncoderReading > encoderTestDelay) {

    SPI.beginTransaction(EncSettings);

    digitalWrite(ENC_CS, LOW);
    reading = SPI.transfer16(ENC_ADDR);
    digitalWrite(ENC_CS, HIGH);

    reading = (reading & (ENC_ADDR));

    float theta = ((float)reading) * 360.0 / 16989.0;

    Serial.println(theta);

    encoderReadingTime = millis(); //Reset the encoder time
  }


}
