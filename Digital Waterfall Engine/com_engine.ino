void lightstrobe(){
// demo verison
  // ask for full version to get all Lightstrobe function code
}


void myloop() {
              if (rflag) {
                         sendline();                     
                         delay(RowDelay);
                         }
              if (lflag) lightstrobe();   //delay(StepDelay);
}

void mysetup() {
  cnt = 1;
  row = 1;  // step 1
  m = 0;
  Serial.print("LCD Initiating...");
  display.begin(i2c_Address, true); 
  Hs = display.height()-1;
  display.clearDisplay();
  display.setFont();
  display.cp437(true);   
  display.setTextColor(WHITE,BLACK);  // Draw white text
  display.display();
   //
   // demo verison
   //
  Serial.printf("OUTPUT Resolution: %dbit - Using SIPOs SHIFT REGISTERS\n", RESMAX);
  delay(500);
  Serial.printf("Task Data Resolution: %d\n", RESTASK);
  //Serial.println(" -");
  delay(1000);
  
  Serial.print("Ports mapped: ");
  pinMode(latchPin, OUTPUT);
  Serial.print("LATCH:");
  Serial.print(latchPin);
  pinMode(dataPin, OUTPUT);
  Serial.print(" DATA:");
  Serial.print(dataPin);
  pinMode(clockPin, OUTPUT);
  Serial.print(" CLOCK:");
  Serial.print(clockPin);
  pinMode(resetPin, OUTPUT); digitalWrite(resetPin,HIGH);  
  Serial.print(" RESET:");
  Serial.println(resetPin);
  delay(1000);
  Serial.print("SIZE OF TASK: ");
  Serial.println(Ts);
  delay(500);
  Serial.print("LOADING TASK DATA...");
  for (word i = 0; i < (sizeof(TASK) / sizeof(TASK[0])); i++) TASK[i] = demo32[i];
  Serial.println("LOADING COMPLETED");
  delay(500);

//display.setLetterSpacing(1);
//display.displayRemap(needremap);  
  display.setTextSize(1);  
  display.clearDisplay();
  display.setCursor(0, 0);
  display.println(F("JOB BEGIN>"));
  display.display();  
  Serial.println("JOB BEGIN>");
  delay(2000);
}
