/*
 * IMU_test_sketch: Check the functionality of the BNO055 IMU
 * 
 * Objective is to be able to collect both the raw data stream
 * as well as the orientation quaternion.
 */
 void TestIMU(Adafruit_BNO055 bno,float &w, float &x, float &y, float &z){
  

  //Retrieve orientation quaternion
  imu::Quaternion quat = bno.getQuat();

  w= quat.w();
  x = quat.x();
  y = quat.y();
  z = quat.z();
  
  
  

 }
