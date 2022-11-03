void TestRotaryEncoder(void){
    //Might be able to get away with using a neat little library written for this general type of encoder


    //Calculate the time since the last reading
    tslEncoderReading = millis() - encoderReadingTime;
    
    if (tslEncoderReading > encoderTestDelay){

        SPI.beginTransaction(spi_setting);
        digitalWrite(encoder_ss_pin,LOW); //Set to low to grab a reading

        high_byte = SPI.transfer(0); //Since we are reading, sending doesn't matter
        low_byte = SPI.transfer(0);

        reading = high_byte << 8;
        reading = reading | low_byte;

        digitalWrite(encoder_ss_pin,HIGH); //Done reading

        Serial.println(reading);

        SPI.endTransaction();

    encoderReadingTime = millis(); //Reset the encoder time
    }

    
}
