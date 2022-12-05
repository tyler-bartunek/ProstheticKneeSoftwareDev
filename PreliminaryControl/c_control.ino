enum TrajType {
  CONSTANT, WALKING, STAIRS
  };

TrajType trajType = WALKING;

float TrajGenerate(void) {

  //Populate and modify with information necessary to generate trajectory
  switch (trajType){
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
    
      if (stanceState){
        // Write stance controller
        if (!prevStanceState){
          stanceStartTime = t;
          }
          
        }
      else {
        // Write swing controller
        if (prevStanceState){
          swingStartTime = t;
          stanceDur = t - stanceStartTime;
          swingDur = stanceDur / STANCERATIO;
          }
          
        Position = InterpolateTrajectory(swingPosTraj, (t - swingStartTime) / swingDur * (sizeof(swingPosTraj) / sizeof(double)));
        
        }
      break;
  
    }

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

  //Update derivative time
  lastDerivative = micros();

  int dutyCycle = (int)(kp * error + ki * iError + kd * dError);

  //Assert only valid PWM commands
  dutyCycle = constrain(dutyCycle, -100, 100); //May need to modify motor functions or this line to make work as intended.

  return dutyCycle; //this is negative because it needs to be
}
