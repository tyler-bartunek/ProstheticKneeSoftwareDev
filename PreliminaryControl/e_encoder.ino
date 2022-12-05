float ReadEncoder(void) {
  
    //Begin the transaction with the SPI object
    SPI.beginTransaction(EncSettings);

    //Signal that we want to get a reading
    digitalWrite(ENC_CS, LOW);

    //Get a reading
    reading = SPI.transfer16(ENC_ADDR);

    //Stop reading
    digitalWrite(ENC_CS, HIGH);

    //Extract position data from SPI signal received
    reading = (reading & (ENC_ADDR));

    //Map to degrees, 16989 is the resolution of the encoder.
    return 189. -((float)reading) * 360.0 / 16989.0;

}
