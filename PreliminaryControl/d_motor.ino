void TestMotor(void) {

  //Turn on the motor
      //if (Serial.available() > 0) {
    //effort = Serial.parseInt();
    //Serial.read();
    //Serial.print("User entered ");
    //Serial.println(effort);
  //}
  MotorOn(motorDir, 50);


}



void MotorOn(int dir, float effort) {
  effort = constrain(effort, 0, 75) / 100;  //conttrain effort in case of out of bounds input
  Serial.println(effort);
  int dac = (1 - effort) * dacResolution * motorOnV / maxArduinoV;
  //Serial.println(dir);
  digitalWrite(motorDirPin, dir);  //set motor direction to arg(motorDir)
  analogWrite(motordacPin, dac);   // set motor power to arg(motorPwr)
  digitalWrite(motorEnPin, 1); // set motor enable to on
}

//Turns the motor off
void MotorOff(void) {
  analogWrite(motordacPin, dacResolution);  // set motor power to 0
  digitalWrite(motorEnPin, 0); // set motor enable to off
}
