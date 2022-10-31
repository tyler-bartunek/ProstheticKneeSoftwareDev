void TestRotaryEncoder(AS5X47 encoder){
    //Might be able to get away with using a neat little library written for this general type of encoder


    //Calculate the time since the last reading
    tslEncoderReading = millis() - encoderReadingTime;
    
    if (tslEncoderReading > encoderTestDelay){
    float angle = encoder.readAngle(); //Get a reading
    Serial.println(angle);             //Display reading

    encoderReadingTime = millis(); //Reset the encoder time
    }

    
}
