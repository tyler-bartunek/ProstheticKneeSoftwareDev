double InterpolateTrajectory(double traj[], double index){
  Serial.print("index:");Serial.println(index);

  index = constrain(index, 0, sizeof(index)/sizeof(double));

  int lowerIndex = floor(index);
  int upperIndex = ceil(index);

  double lowerVal = traj[lowerIndex];
  double upperVal = traj[upperIndex];

  return ( lowerVal + (upperVal - lowerVal) * (index - lowerIndex) );
  
  }
