/*
  TestHardware: Tests each of the hardware components, allowing for user toggling for which test to run when.

  Might need to modify with a function that allows for a mode that tests everything all at once.

  Uses MISO, MOSI, SCK, and IO13 for SPI comms with rotary encoder, where the last one is the chip select.
*/

//#define and #include
#include<Wire.h>
//#include<SPI.h>                           //Might need this library later, gonna try the library made for similar encoders.
#include<Adafruit_Sensor.h>
#include<Adafruit_BNO055.h>
#include <AS5X47.h>                         //This library has not been tested for our encoder specifically, just similar ones. If it works then happy day!


//Create IMU object
Adafruit_BNO055 bno = Adafruit_BNO055();  //Argument to this constructor can be the specific address. Trying to determine if the default address is occupied by something else or if wires/board are crap.

//Pin variables
const int linPotPin = 33;                 //Linear potentiometer
const int encoder_ss_pin = 13;             //chip select for rotary encoder

//Create rotary encoder object
AS5X47 encoder(encoder_ss_pin);

//Variables for toggling userInput
char userInput;
bool newUserInput = true;                 //Flag for determining if something new was entered

//Encoder timing variables
unsigned long encoderTestDelay = 1000;
unsigned long tslEncoderReading;
unsigned long encoderReadingTime;


void setup() {
  // put your setup code here, to run once:

  //Initialize Serial communication
  Serial.begin(921600); // Rate in the IMU example sketch is 115200. Adafruit website recommends 921600 as it "works great", but that isn't a speed Arduino lists as supported. We'll see if it works.


  //Check if the IMU is on, and if it is then get initial readings
  if (!bno.begin())
  {
    /* There was a problem detecting the BNO055 ... check your connections */
    Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
    while (1);
  }

  delay(1000);
}

void loop() {
  // put your main code here, to run repeatedly:


  //Determine which test to run
  if (Serial.available() > 2) { 
    userInput = Serial.read();
    Serial.print("User entered: ");
    Serial.println(userInput);
    newUserInput = true;              //Set flag to true to capture the reality that we have new input
  }

  userInput = toLowerCase(userInput); //Clean input to convert to lowercase. Simplifies life.

  switch (userInput) {

    case 'a':
      if (newUserInput) {
        newUserInput = !newUserInput; //Flip the flag to false 
        Serial.println("Testing IMU functionality, prints out orientation data in the form of a tab-deliminated quaternion.");
        Serial.println("w\t x\t y\t z"); //Explain the layout of the output
      }
      TestIMU(bno);
      break;

    case 'b':
      if (newUserInput) {
        newUserInput = !newUserInput;
        Serial.println("Testing the linear potentiometer readings from the analog pin.");
      }
      TestPot(linPotPin);
      break;

    case 'c':
      if (newUserInput) {
        newUserInput != newUserInput;
        Serial.println("Testing the rotary encoder. Expected output is angles");
      }
      TestMotor(); //This should cascade into a test for the rotary encoder.
      break;

    case 'd':
      if (newUserInput) {
        newUserInput != newUserInput;
        Serial.println("Testing the rotary encoder. Expected output is angles");
      }
      TestMotor(); //This function currently does nothing.

    default:
      Serial.println("Invalid user input, or all cases failed");
    
  }


}
