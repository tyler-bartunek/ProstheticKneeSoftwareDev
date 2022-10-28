
void test_pot_vals(int potPin){
  
  int potVal = analogRead(potPin);
  
  Serial.println(potVal);
}
