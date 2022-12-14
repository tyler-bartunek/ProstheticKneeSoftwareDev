float TestRotaryEncoder(void) {
  //Might be able to get away with using a neat little library written for this general type of encoder

    SPI.beginTransaction(EncSettings);

    digitalWrite(ENC_CS, LOW);
    reading = SPI.transfer16(ENC_ADDR);
    digitalWrite(ENC_CS, HIGH);

    reading = (reading & (ENC_ADDR));

    return ((float)reading) * 360.0 / 16989.0;

}
