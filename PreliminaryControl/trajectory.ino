double InterpolateTrajectory(double traj[], double index){
  Serial.println(index);
  int lowerIndex = floor(index);
  int upperIndex = ceil(index);

  double lowerVal = traj[lowerIndex];
  double upperVal = traj[upperIndex];

  return ( lowerVal + (upperVal - lowerVal) * (index - lowerIndex) );
  
  }
