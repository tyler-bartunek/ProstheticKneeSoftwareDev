const int POT_THRESH = 1.5;

int ReadPot(int potPin){

  //Read the linear potentiometer pin. Future functionality might map it to something
  
  return analogRead(potPin);
  
}

bool StanceDetect(){
  
  return ReadPot(linPotPin1) < POT_THRESH || ReadPot(linPotPin2) < POT_THRESH;
  
  }
