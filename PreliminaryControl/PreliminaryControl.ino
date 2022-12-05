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
const int linPotPin1 = A1;                  //Linear potentiometer 1
const int linPotPin2 = A2;                  //Linear potentiometer 2
int const motorEnPin = 13;                 //Motor enable pin
int const motorDirPin = 12;                //Motor direction pin
int const motordacPin = A0;                //Dac pin for motor
int const dacResolution = 1023;            //resolution of dac/PWM
float const motorOnV = 3.4;                //[V]
float const maxArduinoV = 3.4;             //[V]

//Motor variable
int effort;                                //Percentage of effort commanded to motor
int motorDir = 1;

//Trajectory variable
float Position;

// PID Gains
float kp = 0;
float ki = 0;
float kd = 0;

//PID error terms
float error, iError, dError; //errors for P,I, and D terms.
float alpha = 0.85; //To be set at some point, if we want a weighted average filter on the derivative term (or if we even need a derivative term)

//Term that is useful for calculating last reading
unsigned long lastDerivative;

//Variable for output from rotary encoder
unsigned int reading;

//IMU variables->Euler angles
float roll, pitch;

// State Machine
bool stanceState = 0;
bool prevStanceState = 1;

const double STANCERATIO = 1.5;

long stanceDur = 0;
long swingDur = 0;

long swingStartTime = 0;
long stanceStartTime = 0;

// Trajectories
double swingPosTraj[] = {0.186,0.188,0.178,0.178,0.18,0.158,0.137,0.097,0.077,0.07,0.067,0.061,0.073,1.327,6.858,14.472,24.658,34.394,43.502,50.942,
      57.031,61.604,63.349,62.728,61.199,59.986,58.768,56.342,52.163,47.059,41.355,36.538,31.751,26.735,21.642,16.999,13.377,11.296,9.068,
      7.059,4.914,3.016,1.895,1.402,0.918,0.212,0.237,0.25,0.247,0.25,0.251};

void setup() {
  // put your setup code here, to run once:

  //Initialize Serial communication
  Serial.begin(115200);

  //Set up chip select as output
  pinMode(ENC_CS, OUTPUT);

  //Set up motor enable as output
  pinMode(motorEnPin, OUTPUT);
  pinMode(motorDirPin, OUTPUT);

  //Begin SPI comms
  SPI.begin();

  //Send the chip select pin high by default
  digitalWrite(ENC_CS, HIGH); //Haven't started communicating yet.

  //  MotorOff();
  //
  delay(1000);


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
  if (dutyCycle > 0) {
    motorDir  = 1;
  }
  else {
    motorDir = 0;
  }
  dutyCycle = abs(dutyCycle);

  dutyCycle = constrain(dutyCycle, 0, 50); // Constrain for testing

  MotorOn(motorDir, dutyCycle);

  //Position \t Encoder reading \t dutyCycle \t error
  Serial.print(Position);
  Serial.print("\t");
  Serial.print(ReadEncoder());
  Serial.print("\t");
  Serial.print(dutyCycle);
  Serial.print("\t");
  Serial.print(error);
  Serial.print("\t");
  Serial.print(motorDir);
  Serial.print("\t");
  Serial.print(ReadPot(linPotPin1));
  Serial.print("\t");
  Serial.print(ReadPot(linPotPin2));
  Serial.print("\t");
  Serial.println(StanceDetect());


}
