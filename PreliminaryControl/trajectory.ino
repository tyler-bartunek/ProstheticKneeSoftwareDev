double InterpolateTrajectory(double traj[], double index, int lenTraj) {
  // Serial.print("Index (before):");
  // Serial.println(index);
  index = constrain(index, 0, lenTraj-1);

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