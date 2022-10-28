
void TestPot(int potPin){
  
  int potVal = analogRead(potPin);
  
  Serial.println(potVal);
}
