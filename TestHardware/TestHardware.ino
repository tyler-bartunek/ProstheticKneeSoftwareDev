/*
  TestHardware: Tests each of the hardware components, allowing for user toggling for which test to run when.

  Might need to modify with a function that allows for a mode that tests everything all at once.

  Uses MISO, MOSI, SCK, and IO13 for SPI comms with rotary encoder, where the last one is the chip select.
*/

//#define and #include
#include<Wire.h>
#include<SPI.h>                           //Might need this library later, gonna try the library made for similar encoders.
#include<Adafruit_Sensor.h>
#include<Adafruit_BNO055.h>
#include <AS5X47.h>                         //This library has not been tested for our encoder specifically, just similar ones. If it works then happy day!

#define ENC_CS 10 //Chip select for rotary encoder
#define ENC_ADDR 0x3FFF //Encoder register, might need to tinker with

SPISettings EncSettings(10e6, MSBFIRST, SPI_MODE1);


//Create IMU object
Adafruit_BNO055 bno = Adafruit_BNO055();  //Argument to this constructor can be the specific address. Trying to determine if the default address is occupied by something else or if wires/board are crap.

//Pin variables
const int linPotPin = A2;                  //Linear potentiometer
int const motorEnPin = 12;
int const motorDirPin = 13;
int const motordacPin = A0;
int const dacResolution = 1023;  //resolution of dac/PWM
float const motorOnV = 3.4;     //[V]
float const maxArduinoV = 3.4;    //[V]

//Variables for toggling userInput
char userInput;
bool newUserInput = true;                  //Flag for determining if something new was entered

//Encoder timing variables
unsigned long encoderTestDelay = 1;
unsigned long tslEncoderReading;
unsigned long encoderReadingTime;

unsigned int reading;

int effort = 50; //start at no speed


void setup() {
  // put your setup code here, to run once:

  //Initialize Serial communication
  Serial.begin(115200); 

  pinMode(ENC_CS,OUTPUT);

  SPI.begin();

  digitalWrite(ENC_CS, HIGH); //Haven't started communicating yet.
  MotorOn(1,50);

  /*//Check if the IMU is on, and if it is then get initial readings
  if (!bno.begin())
  {
   
    Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
    while (1);
  }
  

  delay(1000);
  */
}

void loop() {
  // put your main code here, to run repeatedly:

  //Determine which test to run
  if (Serial.available() >= 2) { 
    userInput = Serial.read();
    Serial.read();
    Serial.print("User entered: ");
    Serial.println(userInput);
    newUserInput = true;              //Set flag to true to capture the reality that we have new input
  }

  userInput = toLowerCase(userInput); //Clean input to convert to lowercase. Simplifies life.

  switch (userInput) {

    case 'a':
      if (newUserInput == 1) {
         
        //Serial.println("Testing IMU functionality, prints out orientation data in the form of a tab-deliminated quaternion.");
        //Serial.println("w\t x\t y\t z"); //Explain the layout of the output
        newUserInput = false; //Flip the flag to false 
      }
      TestIMU(bno);
      break;

    case 'b':
      if (newUserInput == 1) {
        //Serial.println("Testing the linear potentiometer readings from the analog pin.");
        newUserInput = !newUserInput;
      }
      TestPot(linPotPin);
      break;

    case 'c':
      if (newUserInput == 1) {
        //Serial.println("Testing the rotary encoder. Expected output is angles");
        newUserInput != newUserInput;
      }
      TestMotor(); //This should cascade into a test for the rotary encoder.
      break;

    case 'd':
      if (newUserInput == 1) {
        //Serial.println("Testing the motor");
        newUserInput != newUserInput;
      }
      TestMotor(); //This function currently does nothing.
      break;

    
    
  }


}
