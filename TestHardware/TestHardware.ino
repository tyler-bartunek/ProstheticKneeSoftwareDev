/*
*
*/
//#define and #include
#include<Wire.h>
#include<SPI.h>
#include<Adafruit_Sensor.h>
#include<Adafruit_BNO055.h>

//SPI Stuff
#define CLK 5
#define MISO 21
#define MOSI 19


//Create IMU object
Adafruit_BNO055 bno = Adafruit_BNO055();

//Pin variables
const int linPotPin = 33;

//Variables for toggling userInput
char userInput;
bool newUserInput = true;


void setup() {
  // put your setup code here, to run once:

  //Initialize Serial communication
  Serial.begin(115200); // Rate in their example sketch

  //Check if the IMU is on, and if it is then get initial readings
  if(!bno.begin())
  {
    /* There was a problem detecting the BNO055 ... check your connections */
    Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
    while(1);
  }

  delay(1000);
}

void loop() {
  // put your main code here, to run repeatedly:
  

  //Determine which test to run
  if (Serial.available() > 2){
    userInput = Serial.read();
    Serial.print("User entered: ");
    Serial.println(userInput);
    newUserInput = true;
  }

  switch (userInput){
    
    case 'a':
    if (newUserInput){
      newUserInput = !newUserInput;
      Serial.println("Testing IMU functionality, prints out orientation data in the form of a tab-deliminated quaternion.");
    }
    TestIMU(bno);
    break;

    case 'b':
    if (newUserInput){
      newUserInput = !newUserInput;
      Serial.println("Testing the linear potentiometer readings.");
    }
    test_pot_vals(linPotPin);
    break;
    
  }
  
  
}
