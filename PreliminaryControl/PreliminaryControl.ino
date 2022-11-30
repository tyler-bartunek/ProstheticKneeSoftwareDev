/*
  PreliminaryControl: Sandbox for generating a basic control scheme until the rest of the class is ready to join.

  Uses MISO, MOSI, SCK, and pin 10 for SPI comms with rotary encoder, where the last one is the chip select.
*/

//#define and #include
#include<Wire.h>
#include<SPI.h>                  
#include<Adafruit_Sensor.h>
#include<Adafruit_BNO055.h>

#define ENC_CS 10 //Chip select for rotary encoder
#define ENC_ADDR 0x3FFF //Encoder register, also used in some dark magic in the encoder tab. Pulled this value from Justin Francis' code on the Github for the open source leg


//Set up SPI settings
SPISettings EncSettings(10e6, MSBFIRST, SPI_MODE1);


//Create IMU object
Adafruit_BNO055 bno = Adafruit_BNO055();  //Argument to this constructor can be the specific address. 

//Pin variables
const int linPotPin = A1;                  //Linear potentiometer
int const motorEnPin = 12;                 //Motor enable pin       
int const motorDirPin = 13;                //Motor direction pin
int const motordacPin = A0;                //Dac pin for motor
int const dacResolution = 1023;            //resolution of dac/PWM
float const motorOnV = 3.4;                //[V]
float const maxArduinoV = 3.4;             //[V]

//Motor variable
int effort;                                //Percentage of effort commanded to motor
int motorDir = 1;

//Trajectory variable
float Position;

//PID error terms
float error, iError, dError; //errors for P,I, and D terms.
float alpha = 0.85; //To be set at some point, if we want a weighted average filter on the derivative term (or if we even need a derivative term)

//Term that is useful for calculating last reading
unsigned long lastDerivative;

//Variable for output from rotary encoder
unsigned int reading;

//IMU variables->Euler angles
float roll, pitch;

void setup() {
  // put your setup code here, to run once:

  //Initialize Serial communication
  Serial.begin(115200);

  //Set up chip select as output
  pinMode(ENC_CS, OUTPUT);

  //Begin SPI comms
  SPI.begin();

  //Send the chip select pin high by default
  digitalWrite(ENC_CS, HIGH); //Haven't started communicating yet.

  
  //Check if the IMU is on. If not throw an error
  if (!bno.begin())
  {

    Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
    while (1);
  }

}

void loop() {

  //Get trajectory setpoint
  Position = TrajGenerate();

  //Get PWM command signal to achieve setpoint
  int dutyCycle = PID(Position);
  //int dir = bitRead(dutyCycle,31); //Keep for personal reference. This should get the MSB, 1 for negative and 0 for positive
  if (dutyCycle > 0){
    motorDir  = 1;
  }
  else{
    motorDir = 0;
  }
  dutyCycle = abs(dutyCycle);

  MotorOn(motorDir, dutyCycle);

}