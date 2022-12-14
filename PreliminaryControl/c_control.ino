
//Possible states for the state machine
enum TrajType {
  CONSTANT,
  WALKING,
  STAIRS
};

TrajType trajType = WALKING;

float TrajGenerate(void) {

  /*
    TrajGenerate: Implements the PID controller for swing with the setpoints determined from the trajectory interpolation function.

    Inputs: bno object, references to orientation angles designated as roll and pitch.
  */

  switch (trajType) {
    //CONSTANT case: check step input position commands
    case CONSTANT:
      if (Serial.available() > 0) {
        kp = 2;
        ki = 4;
        kd = 0;
        Position = Serial.parseFloat();
        Serial.read();
      }
      break;

    case WALKING:
      // Step State Machine
      stanceState = StanceDetect();
      long t = millis();
      kp = 8;
      ki = 16;
      kd = 0;
      if (stanceState) {           // IN STANCE
        Position = 0;
        Serial.println("STANCE");  // Write stance controller
        if (!prevStanceState) {
          //Serial.println("INSIDE IF");

          stanceStartTime = t;
        }

      } else {  // IN SWING
        // Write swing controller
        if (prevStanceState) {
          // Serial.println("INSIDE ELSE");

          swingStartTime = t;
          stanceDur = t - stanceStartTime;
          //swingDur = stanceDur / STANCERATIO;
          swingDur = 800;  // [ms] FOR TESTING, REMOVE WHEN USING IMU
        }
        // Serial.println("STUFF");
        // Serial.print("Time:");
        // Serial.println(t);
        // Serial.print("swingStartTime:");
        // Serial.println(swingStartTime);
        // Serial.print("Percent swing:");
        // Serial.println((t - swingStartTime) / swingDur);
        // Serial.println(swingDur);
        int lenTraj = (sizeof(swingPosTraj) / sizeof(double));
        double k = (float)(t - swingStartTime) / swingDur * lenTraj;
        // Serial.print("Index:");
        // Serial.println(k);
        Position = InterpolateTrajectory(swingPosTraj, k, lenTraj);
      }
      prevStanceState = stanceState;

      break;
  }

  Position = constrain(Position, 0, 65);

  // Serial.print("Controller Info: ");
  // Serial.print("\t");
  // Serial.print(stanceState);
  // Serial.print("\t");
  // Serial.print(stanceStartTime);
  // Serial.print("\t");
  // Serial.print(stanceDur);
  // Serial.print("\t");
  // Serial.print(swingStartTime);
  // Serial.print("\t");
  // Serial.print(swingDur);
  // Serial.print("\t");
  // Serial.print(Position);
  // Serial.println("\t");

  return Position;
}


int PID(float ref) {

  //terms to be used with derivative control (maybe useless, will determine later)
  float errorOld = error;
  float dErrorOld = dError;
  float maxIntegral = 100 / ki;

  //Calculate time interval;
  float dt = (micros() - lastDerivative) / 1000000.0;

  //Update error terms
  error = ref - ReadEncoder();
  iError += error * dt;
  iError = constrain(iError, -maxIntegral, maxIntegral);
  dError = dError * alpha + (error - errorOld) / dt * (1 - alpha);
  //Serial.println(dError);
  //Update derivative time
  lastDerivative = micros();

  int dutyCycle = (int)(kp * error + ki * iError + kd * dError);

  //Assert only valid PWM commands
  dutyCycle = constrain(dutyCycle, -100, 100);  //May need to modify motor functions or this line to make work as intended.

  return dutyCycle;  //this is negative because it needs to be
}
