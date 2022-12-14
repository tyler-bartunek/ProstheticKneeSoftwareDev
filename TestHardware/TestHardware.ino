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

//Motor variable
int effort;

//Variables for toggling userInput
char userInput;
bool newUserInput = true;                  //Flag for determining if something new was entered

//Encoder timing variables
unsigned long encoderTestDelay = 1;
unsigned long tslEncoderReading;
unsigned long encoderReadingTime;

unsigned int reading;

//IMU variables
float w;
float x;
float y;
float z;



void setup() {
  // put your setup code here, to run once:

  //Initialize Serial communication
  Serial.begin(115200);

  pinMode(ENC_CS, OUTPUT);

  SPI.begin();

  digitalWrite(ENC_CS, HIGH); //Haven't started communicating yet.

  //Check if the IMU is on, and if it is then get initial readings
  if (!bno.begin())
  {

    Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
    while (1);
  }

  Serial.print("Linear Potentiometer");
  Serial.print("\t");
  Serial.print("Angle [deg]");
  Serial.print("\t");
  Serial.print("w");
  Serial.print("\t");
  Serial.print("x");
  Serial.print("\t");
  Serial.print("y");
  Serial.print("\t");
  Serial.println("z");


  delay(1000);

}

void loop() {
  // put your main code here, to run repeatedly:

  TestMotor();

  Serial.print(TestPot(linPotPin));
  Serial.print("\t");
  Serial.print(TestRotaryEncoder());
  Serial.print("\t");

  TestIMU(bno, w, x, y, z);

  Serial.print(w);
  Serial.print("\t");
  Serial.print(x);
  Serial.print("\t");
  Serial.print(y);
  Serial.print("\t");
  Serial.println(z);



}
