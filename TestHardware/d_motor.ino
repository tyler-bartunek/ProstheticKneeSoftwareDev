void TestMotor(void){

  switch (userInput){

    case 'c': //Test the encoder separately
    TestRotaryEncoder();
    break;

    case 'd': //Test the motor being turned on full blast
    //Does nothing
    break;

    default:
    Serial.println("For some reason, the tests failed. Check for break statements");
    break;
  }
  
}

/*
 * Possiblity of moving encoder tab into this tab.
 * 
 * Also add on tests to test ability to move motor to position or velocity.
 * 
 * Will need to merge with Joe's code if possible.
 * 
 */
