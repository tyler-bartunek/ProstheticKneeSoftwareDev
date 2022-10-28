/*
  TestHardware: Tests each of the hardware components, allowing for user toggling for which test to run when.

  Might need to modify with a function that allows for a mode that tests everything all at once.

  Be sure to have SPI_Multiple_Buses example open as I comment out the details of how some of 
  those shenanigans work.
*/

//#define and #include
#include<Wire.h>
#include<SPI.h>
#include<Adafruit_Sensor.h>
#include<Adafruit_BNO055.h>

//SPI Stuff
#define SPI_SS 13
#define SPI_MISO 21
#define SPI_MOSI 19
#define SPI_SCK 5

//Create IMU object
Adafruit_BNO055 bno = Adafruit_BNO055();

//Pointers to SPI object
SPIClass * encoder = NULL;

//Pin variables
const int linPotPin = 33;

//Variables for toggling userInput
char userInput;
bool newUserInput = true;


void setup() {
  // put your setup code here, to run once:

  //Initialize Serial communication
  Serial.begin(115200); // Rate in their example sketch



  //Set up SPI comms
  encoder = new SPIClass(SPI);

  #ifndef ALTERNATE_PINS
  encoder->begin();
  #else
  encoder->begin(SPI_SCK, SPI_MISO, SPI_MOSI, SPI_SS);
  #endif

    //Set up pins
  pinMode(encoder->pinSS(),OUTPUT);

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
    newUserInput = true;
  }

  switch (userInput) {

    case 'a':
      if (newUserInput) {
        newUserInput = !newUserInput;
        Serial.println("Testing IMU functionality, prints out orientation data in the form of a tab-deliminated quaternion.");
      }
      TestIMU(bno);
      break;

    case 'b':
      if (newUserInput) {
        newUserInput = !newUserInput;
        Serial.println("Testing the linear potentiometer readings.");
      }
      TestPot(linPotPin);
      break;

    case 'c':
      if (newUserInput) {
        newUserInput != newUserInput;
        Serial.println("Testing the rotary encoder");
      }
      TestRotaryEncoder();
  }


}
