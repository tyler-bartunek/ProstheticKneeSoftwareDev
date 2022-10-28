void TestRotaryEncoder(void){
    //Tests the Rotary Encoder. Needs SPI stuff to be set up, then we should be able to pass that in to here hopefully.

    //Enable chip select
    digitalWrite(encoder->pinSS(), LOW);
    //SPI.transfer(data); //Read data from the SPI line. Currently fails to compile.
    //Disable chip select
    digitalWrite(encoder->pinSS(), HIGH);
}
