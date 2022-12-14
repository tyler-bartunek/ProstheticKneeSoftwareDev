double InterpolateTrajectory(double traj[], double index, int lenTraj) {

  /*
     InterpolateTrajectory: Finds the correct index to use as the set point for the controller

     INPUTS: 1. traj[]- Existing global trajectory array.
             2. index- The index estimate from the trajectory planner
             3. lenTraj- The length of the trajectory array

  */
  // Serial.print("Index (before):");
  // Serial.println(index);
  index = constrain(index, 0, lenTraj - 1);

  int lowerIndex = floor(index);
  int upperIndex = ceil(index);

  double lowerVal = traj[lowerIndex];
  double upperVal = traj[upperIndex];

  // Serial.print("Lower Val:");
  // Serial.println(lowerVal);
  // Serial.print("Upper Val:");
  // Serial.println(upperVal);
  // Serial.print("Lower Index:");
  // Serial.println(lowerIndex);
  // Serial.print("Index (after):");
  // Serial.println(index);

  return (lowerVal + (upperVal - lowerVal) * (index - lowerIndex));
}
