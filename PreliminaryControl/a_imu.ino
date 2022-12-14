/*
   IMU_test_sketch: Check the functionality of the BNO055 IMU

   Inputs: bno object, references to orientation angles designated as roll and pitch.
*/
void ReadIMU(Adafruit_BNO055 bno, float &roll, float &pitch) {

  //Set up sensors event variable for recording sensor data
  sensors_event_t event;
  bno.getEvent(&event);

  //Extract roll and pitch data
  roll = event.orientation.x;
  pitch = event.orientation.y;


}
