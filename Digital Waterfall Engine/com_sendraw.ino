int y = 0;
int interval = 0x000b;
// 111b – 2 frame
// 100b – 3 frames
// 101b – 4 frames
// 000b – 5 frames
// 110b – 25 frame
// 001b – 64 frames
// 010b – 128 frames
// 011b – 256 frames

int offset = 0x07;  // 01h = 1    3f = 63

byte BytInv(byte byt) {
  return ((byte)~byt);
}

void StartScroll() {
   display.ssd1306_command(SSD1306_ACTIVATE_SCROLL);
}

void StopScroll() {
   display.stopscroll();
}

void SetVertScroll() {
 // StopScroll();
    display.startscrolldiagleft(0x0F, 0x0F);
   //display.ssd1306_command(SSD1306_VERTICAL_AND_RIGHT_HORIZONTAL_SCROLL);  //0
   //display.ssd1306_command(0x00);                                          //1
   //display.ssd1306_command(0x0F);                                          //2
  // display.ssd1306_command(interval);                                      //3
  // display.ssd1306_command(0x0F);                                          //4
  // display.ssd1306_command(offset);
  // display.ssd1306_command(SSD1306_SET_VERTICAL_SCROLL_AREA);              //0
  // display.ssd1306_command(0x00);                                          //1
  // display.ssd1306_command(31);  //31                                    //2
}

void printBin(byte aByte) {
  for (int8_t aBit = RESTASK - 1; aBit >= 0; aBit--)
    Serial.print(bitRead(aByte, aBit) ? '1' : '0');
}

void drawBin(byte aByte) {
// demo verison
}

word bitWriteWord(word w, byte b, byte c) {
  byte wl = lowByte(w);
  byte wh = highByte(w);
  if (b < 8) bitWrite(wl, b, c);  // Lo Byte
  else bitWrite(wh, b - 8, c);    //(w && 0xFF00, b-8);
  return word(wh, wl);
}

void dataOut() {
  // display.stopscroll();
  byte b = TASK[m];
  if (iflag) b = BytInv(b); // inverse out
  m++;
  if (m >= Ts) {
    m = 0;
    cnt++;
  }
  shiftOut(b);

  if (pflag) printBin(b);  //Serial.print(b,BIN);
  //if (dflag) drawBin(b);    // if (sflag) StartScroll();
}


void prepgraf() {
// demo verison
}

void prepbuf() {
// demo verison
}



void drawbitmap(byte yline) {
  display.drawBitmap(0, yline, GRAF, RESMAX * (ddflag + 1), 1, 1);  //last1
  display.display();                                                // delay(1000);
}

void drawbuf() {
// demo verison                                                       // delay(1000);
}


void prinfo() {
  display.setCursor(70, 0);
  display.print(F("DEMO"));
  display.print(ver);
  display.setCursor(70, 10);
  display.print(F("Cycl:"));
  display.print(cnt);
  display.setCursor(70, 20);
  display.print(F("Line:"));
  display.print(row);
  display.setCursor(70, 30);
  display.print(F("D:"));
  display.print(LoopDelay);
  display.print(F("/"));  
  display.print(RowDelay);
  display.setCursor(70, 40);
  display.print(F("Invrt "));
  display.print(iflag);
  display.display();
}



void sendline() {  // ts=8=len Dat
                   //canvas.fillScreen(0x0000);
  if (pflag) Serial.printf("\nCycle:%03d_Line:%03d_Index:%04d > ", cnt, row, m + 1);
  if (dflag) prepgraf();
  //if (dflag) prepbuf();

  digitalWrite(latchPin, 0);
  for (i = 0; i < RESTEP; i++) dataOut();  //send bits
  digitalWrite(latchPin, 1);

  // if (dflag) drawbuf();     // out graf
  if (dflag) drawbitmap(y);        // out graf
  if (dflag && !ddflag) prinfo();  // pout
                                   ///  display.drawBitmap(0, 0, canvas.getBuffer(),canvas.width(), canvas.height(), WHITE, BLACK);
  y++;
  if (sflag) {  // scroll
    if (y > Hs) {
      y = Hs;
      StartScroll();
    }
  } else {  // normal
    if (y > Hs) {
      y = 0;
      display.clearDisplay();
    }
  }

  row++;
  if (row > Rs) row = 1;  //rows for counter
}
