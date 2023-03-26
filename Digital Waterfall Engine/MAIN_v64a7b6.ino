// Ting n John
#define ver 7.6

#include "demo32.h"

#include <SPI.h>
#include <Wire.h>
//#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
//#include <Fonts/Picopixel.h>

#include <Adafruit_SH110X.h>
#define WHITE SH110X_WHITE
#define BLACK SH110X_BLACK
#define INVERSE SH110X_INVERSE

// Jag code
const byte RESMAX = 64;                // RESOLUTION LINE - VALVES
const byte RESTASK = 8;                // RESOLUTION of Word in DATA ARRAY Word=Byte
const byte RESTEP = RESMAX / RESTASK;  // 8x8=64
  //PORTS
const int latchPin = 25;   //Pin connected to ST_CP of 74HC595  //14 12 4 5
const int clockPin = 26;  //Pin connected to SH_CP of 74HC595
const int  dataPin = 27;   //Pin connected to DS of 74HC595
const int resetPin = 12;  //Pin connected to SH_CP of 74HC595
const int lig_s = 2;  //SUPER BRIGHT LED Panelx6 STROBE   // 4 0
const int lig_r = 15;  //RGB LED COLOR CHANNEL R.RED
const int lig_g = 16;  //RGB LED COLOR CHANNEL G.GREEN
const int lig_b = 17;  //RGB LED COLOR CHANNEL B.BLUE

const int LoopDelayDefault = 10;
 static int LoopDelay = LoopDelayDefault;               // Loop delay 1..100  old.5
const int RowDelayDefault = 20; 
 static int RowDelay = RowDelayDefault;               // Line delay 20..70   old.100


bool pflag = true;    // PRINT/CONSOLE out toggle
bool dflag = true;    // Display Out toggle
 bool needremap = true; // flip display
bool rflag = true;    // RUN ENGINE  - START Running 

bool lflag = !true;    // LIGHT STROBE
bool sflag = !true;   // Scroll display !!! NOT WORKS!!! not implemented
bool ddflag =!true;   // ZOOM x2 DispMode toggle
bool iflag = !true;    // INVERSE OUT toggle

const word Ts = demo32_size ;  // 1920
const word Rs = demo32_height;

uint8_t TASK[Ts];  //ting240;
uint8_t GRAF[RESTEP*2];
unsigned long cnt;
byte Hs,i, n;
word m, row;


const int frequence = 1000; // PWM frequency of 1 KHz
const int resolution = 8; // 8-bit resolution, 256 possible values

// public code

const int pwmCS = 0; // Selects channel 0
const int pwmCR = 1; // Selects channel 1
const int pwmCG = 2; // Selects channel 2
const int pwmCB = 3; // Selects channel 3

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
// On an arduino UNO:       A4(SDA), A5(SCL)
// On an ESP32:             21(SDA), 22(SCL)
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define i2c_Address 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
//Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
Adafruit_SH1106G display = Adafruit_SH1106G(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

uint8_t OVER[RESTEP*SCREEN_HEIGHT];


void setup() {  // init
  Serial.begin(115200);
  //  SerialBT.begin("JoTiBT"); //Bluetooth device name
  Serial.println();
  Serial.print("Digital Waterfall Shareware Demo ");
  delay(2000);
  Serial.print(">");
  //Serial.println();
  Serial.println("> Ready to go!");
  delay(1000);
  mysetup();
}

void loop() {
  myloop();                         //  waterfall
  JTcom();                // command processor
  delay(LoopDelay);                  //delay(5);   // MAIN LOOP delay
}
