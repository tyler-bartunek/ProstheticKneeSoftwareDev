float TrajGenerate(void){

  //Populate and modify with information necessary to generate trajectory
  if (Serial.available() > 0){
    Position = Serial.parseFloat();
    Serial.read();
    
  }


  return Position;
}


int PID(float ref){



  //looke some code I added
  //PID gains
  float kp = 2;
  float ki = 4;
  float kd = 0;
  
  //terms to be used with derivative control (maybe useless, will determine later)
  float errorOld = error;
  float dErrorOld = dError;
  float maxIntegral = 100 / ki;

  //Calculate time interval;
  float dt = (micros() - lastDerivative) / 1000000.0;

  //Update error terms
  error = ref - ReadEncoder();
  iError += error*dt;
  iError = constrain(iError, -maxIntegral, maxIntegral);
  dError = dError * alpha + (error - errorOld) / dt * (1 - alpha);

  //Update derivative time
  lastDerivative = micros();

  int dutyCycle = (int)(kp * error + ki * iError + kd * dError);

  //Assert only valid PWM commands
  dutyCycle = constrain(dutyCycle,-100,100); //May need to modify motor functions or this line to make work as intended.

  return dutyCycle; //this is negative because it needs to be
}
