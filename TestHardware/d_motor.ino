void TestMotor(void) {
        effort = 50;
        Serial.read();

      MotorOn(1, effort);


}

/*
   Possiblity of moving encoder tab into this tab.

   Also add on tests to test ability to move motor to position or velocity.

   Will need to merge with Joe's code if possible.

*/

void MotorOn(int dir, float effort) {
  effort = constrain(effort, 0, 100) / 100;  //conttrain effort in case of out of bounds input
  int dac = (1 - effort) * dacResolution * motorOnV / maxArduinoV;
  digitalWrite(motorDirPin, dir);  //set motor direction to arg(motorDir)
  analogWrite(motordacPin, dac);   // set motor power to arg(motorPwr)
  digitalWrite(motorEnPin, 1); // set motor enable to on
}

//Turns the motor off
void MotorOff(void) {
  analogWrite(motordacPin, 0);  // set motor power to 0
  digitalWrite(motorEnPin, 0); // set motor enable to off
}
