int ii,pinState;
void shiftOut(byte myDataOut) {
  ii=0;
  //int pinState;
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);

  digitalWrite(dataPin, 0);
  digitalWrite(clockPin, 0);

  //This means that %00000001 or "1" will go through such that it will be pin Q0 that lights. 
  for (ii=7; ii>=0; ii--)  {
    digitalWrite(clockPin, 0);

    if ( myDataOut & (1<<ii) ) {   // bitread  bitRead(aByte, aBit) ? '1' : '0'
      pinState= 1;
    }
    else {	
      pinState= 0;
    }

    //Sets the pin to HIGH or LOW depending on pinState
    digitalWrite(dataPin, pinState);
    //register shifts bits on upstroke of clock pin  
    digitalWrite(clockPin, 1);
    //zero the data pin after shift to prevent bleed through
    digitalWrite(dataPin, 0);
  }

  //stop shifting
  digitalWrite(clockPin, 0);
}
