Hello thisi is public file hub
X-STATE Eyedolon # teslasoft >>> thairup@gmail.com
Arduino and PC software


DIGITAL WATERFALL ENGINE
#Digital #waterfall #arduino #esp #shift #registers #water #nozzle #demo #sketch

Описание скетча для цифрового водопада
техническое описание

1. установка на 64 выхода (нормальнозакрытые клапаны с соплами на 24 вольта).
Разрядность выхода 64 бит, ширина картинки 64 пикселя.

2. Процессор ESP32, 3 цифровых выхода на плату регистров сдвига, с платы регистров выходы удут на усилители и на клапаны.

3. Плата регистров 8 штук 74HC595, на выходе 8 блоков по 8 бит

4. Усилители 10 штук ULN2004 (7бит на чип), на выходах резистор 100-150 ом перед клапанами, клапаны установки подключаются 8 жилами кабеля UTP (витая пара).

описание скетча

MAIN_ver 
-задание в файле #include "demo32.h"
// Разрешение изображения: 64 x 320;
const uint16_t demo32_widht PROGMEM = 64; // Размер в пикселях, а не в байтах
const uint16_t demo32_height PROGMEM = 320*4; // 4 блока по 320
const uint16_t demo32_size PROGMEM = 2560*4; // 4 блока по 2560
const uint8_t demo32[demo32_size] PROGMEM = 
-подключается модуль дисплея (oled 32x128 i2c)
-задаются порты для выходной платы (основная)
const int latchPin = 25;   //Pin connected to ST_CP of 74HC595 
const int clockPin = 26;  //Pin connected to SH_CP of 74HC595
const int  dataPin = 27;   //Pin connected to DS of 74HC595
const int resetPin = 12;  //Pin connected to SH_CP of 74HC595
-задаются порты для модуля подсветки (дополн)
const int lig_s = 2;  //SUPER BRIGHT LED Panelx6 STROBE   // 4 0
const int lig_r = 15;  //RGB LED COLOR CHANNEL R.RED
const int lig_g = 16;  //RGB LED COLOR CHANNEL G.GREEN
const int lig_b = 17;  //RGB LED COLOR CHANNEL B.BLUE
-флаги
bool pflag = true;    // PRINT/CONSOLE out toggle вывод в консоль
bool dflag = true;    // Display Out toggle       включает дисплей   
bool needremap = true; // flip display             - перевернуть
bool rflag = true;    // RUN ENGINE  - START Running      если true то движок стартует сразу
bool lflag = !true;    // LIGHT STROBE              включает световой модуль
bool sflag = !true;   // Scroll display !!! NOT WORKS!!! not implemented   скрол. пока не работает
bool ddflag =!true;   // ZOOM x2 DispMode toggle     - полноэкранный вывод картинки
bool iflag = !true;    // INVERSE OUT toggle    - инверсия битов на дисплее и на выходе

-процедуры водопада
void setup - mysetup();            // установка параметров
void loop() {
  myloop();                         //  движок водопада
  JTcom();                          // command processor - обработчик команд консоли  - управление движком
  delay(LoopDelay);                  // основной делей
}









