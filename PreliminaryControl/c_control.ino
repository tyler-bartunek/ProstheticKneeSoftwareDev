float TrajGenerate(void){

  //Populate and modify with information necessary to generate trajectory
  Position = 180;


  return Position;
}


int PID(float ref){

  //PID gains
  float kp;
  float ki;
  float kd;
  
  //terms to be used with derivative control (maybe useless, will determine later)
  float errorOld = error;
  float dErrorOld = dError;
  float maxIntegral = 100 / ki;

  //Calculate time interval;
  float dt = (micros() - lastDerivative) / 1000000.0;

  //Update error terms
  error = ref - ReadEncoder();
  iError += error;
  iError = constrain(iError, -maxIntegral, maxIntegral);
  dError = dError * alpha + (error - errorOld) / dt * (1 - alpha);

  //Update derivative time
  lastDerivative = micros();

  int dutyCycle = (int)(kp * error + ki * iError + kd * dError);

  //Assert only valid PWM commands
  dutyCycle = constrain(dutyCycle,-100,100); //May need to modify motor functions or this line to make work as intended.

  return dutyCycle;
}
