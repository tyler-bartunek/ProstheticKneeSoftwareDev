/*
 * IMU_test_sketch: Check the functionality of the BNO055 IMU
 * 
 * Objective is to be able to collect both the raw data stream
 * as well as the orientation quaternion.
 */

//10/19/2022

//#define and #include
#include<Wire.h>
#include<Adafruit_Sensor.h>
#include<Adafruit_BNO055.h>


//Create IMU object
Adafruit_BNO055 bno = Adafruit_BNO055();


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
  

  //Retrieve acceleration data
  imu::Vector<3> accel = bno.getVector(Adafruit_BNO055::VECTOR_ACCELEROMETER);
  

  //Retrieve gyro data
  imu::Vector<3> gyro = bno.getVector(Adafruit_BNO055::VECTOR_GYROSCOPE);
  
  //Retrieve orientation quaternion
  imu::Quaternion quat = bno.getQuat();
  Serial.print(quat.w()); Serial.print("\t");
  Serial.print(quat.x()); Serial.print("\t");
  Serial.print(quat.y()); Serial.print("\t");
  Serial.print(quat.z()); Serial.println("");
  
}
