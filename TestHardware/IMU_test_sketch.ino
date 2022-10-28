/*
 * IMU_test_sketch: Check the functionality of the BNO055 IMU
 * 
 * Objective is to be able to collect both the raw data stream
 * as well as the orientation quaternion.
 */
 void TestIMU(Adafruit_BNO055 bno){
  
  
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
