/***************************************************

 ****************************************************/
/*
  #define ST7735_BLACK   0x0000
  #define ST7735_BLUE    0x001F
  #define ST7735_RED     0xF800
  #define ST7735_GREEN   0x07E0
  #define ST7735_CYAN    0x07FF
  #define ST7735_MAGENTA 0xF81F
  #define ST7735_YELLOW  0xFFE0
  #define ST7735_WHITE   0xFFFF

  ######## TEXT SIZE ##################
  1 - 7px*5px
  2 = 1*2 - 14px*10px
  3 = 1*3 - 21px*15px
*/
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library
#include <SPI.h>

#define wText1 6
#define hText1 7
#define wText2 12
#define hText2 14
#define wText3 17
#define hText3 21

// For the breakout, you can use any 2 or 3 pins
// These pins will also work for the 1.8" TFT shield
#define TFT_CS     10
#define TFT_RST    9  // you can also connect this to the Arduino reset
// in which case, set this #define pin to 0!
#define TFT_DC     8

// Option 1 (recommended): must use the hardware SPI pins
// (for UNO thats sclk = 13 and sid = 11) and pin 10 must be
// an output. This is much faster - also required if you want
// to use the microSD card (see the image drawing example)
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS,  TFT_DC, TFT_RST);

// Option 2: use any pins but a little slower!
#define TFT_SCLK 13   // set these to be whatever pins you like!
#define TFT_MOSI 11   // set these to be whatever pins you like!
//Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);

//################# ПЕРЕМЕННЫЕ #####################################################
#define tftBacklightPin 3                   // пин управления подсветкой tft
int T_IN = -623;
int T_IN_MASS[90] =
{ 8, 8, 11, 8, 5, 5, 5, 8, 11, 5, 5, 5,
  3, 5, 8, 11, 8, 8, 8, 8, 8, 11, 11, 11,
  11, 11, 14, 11, 14, 14, 14, 14, 14, 16,
  16, 14, 14, 14, 14, 14, 14, 11, 11, 11,
  11, 11, 14, 16, 19, 25, 25, 22, 22, 22,
  28, 30, 33, 36, 41, 41, 44, 53, 61, 64,
  72, 80, 80, 89, 89, 89, 86, 89, 91, 94,
  100, 97, 94, 97, 103, 103, 94, 91, 94,
  91, 91, 91, 89, 89, 86, 83
};
int H_IN = 8798;
int H_IN_MASS[90] =
{ 28, 30, 33, 30, 31, 23, 27, 23, 25, 27,
  23, 21, 19, 18, 20, 19, 19, 18, 17, 14,
  11, 10, 12, 11, 12, 12, 14, 14, 14, 17,
  16, 15, 16, 15, 19, 19, 13, 13, 10, 9,
  13, 11, 9, 9, 6, 7, 3, 8, 7, 10, 16, 16,
  17, 19, 20, 25, 28, 34, 35, 42, 44, 52,
  56, 65, 69, 77, 82, 90, 94, 93, 93, 93,
  100, 97, 103, 100, 98, 92, 97, 101, 96,
  88, 79, 75, 70, 66, 55, 46, 40, 38
};

int P_IN = 7659;
int P_IN_MASS[90] =
{ 103, 103, 99, 93, 93, 90, 86, 83, 83, 83,
  83, 83, 80, 77, 77, 73, 70, 67, 67, 64,
  64, 61, 57, 57, 54, 51, 48, 44, 44, 41,
  44, 44, 41, 41, 41, 41, 44, 41, 38, 38,
  38, 35, 35, 35, 38, 32, 28, 25, 25, 22,
  19, 15, 9, 9, 9, 9, 6, 9, 15, 12, 9, 6,
  6, 6, 6, 6, 9, 6, 9, 12, 12, 15, 12, 9,
  6, 6, 3, 6, 6, 6, 9, 9, 9, 6, 6, 3, 3,
  3, 3, 6
};
int Teff = -2050;
int T_OUT = 2185;
int dewPoint = -693;
int dDewPoint = 581;
unsigned long cloudHeight = 1000;
unsigned int VCC = 4500;
unsigned int VCC_MAX = 4300;
unsigned int VCC_MIN = 3200;
byte hourRTC = 23;
byte minuteRTC = 50;
byte monthRTC = 10;
byte dayRTC = 25;
int yearRTC = 2019;
//################# ПЕРЕМЕННЫЕ #####################################################

void setup(void) {
  pinMode(tftBacklightPin, OUTPUT);
  analogWrite(tftBacklightPin, 100);

  // Use this initializer if you're using a 1.8" TFT
  tft.initR(INITR_BLACKTAB);   // initialize a ST7735S chip, black tab

  tft.setRotation(2);

  tft.fillScreen(ST7735_BLACK);

  graph();
  screen1();
}

void loop() {


}

void graph() {
  // построение осей координат
  tft.drawRect( 20, 1, 90, 110, ST7735_WHITE);

  // подписи по осям
  // левая ось Y
  tft.setTextColor(0xff6600);
  tft.setCursor(2, 2);
  tft.print("753");
  tft.setCursor(2, 13);
  tft.print("752");
  tft.setCursor(2, 24);
  tft.print("751");
  tft.setCursor(2, 35);
  tft.print("750");
  tft.setCursor(2, 46);
  tft.print("749");
  tft.setCursor(2, 57);
  tft.print("748");
  tft.setCursor(2, 68);
  tft.print("747");
  tft.setCursor(2, 79);
  tft.print("746");
  tft.setCursor(2, 90);
  tft.print("745");
  tft.setCursor(2, 101);
  tft.print("744");
  // правая ось Y
  tft.setTextColor(ST7735_RED);
  tft.setCursor(113, 2);
  tft.print("14");
  tft.setCursor(113, 13);
  tft.print("13");
  tft.setCursor(113, 24);
  tft.print("12");
  tft.setCursor(113, 35);
  tft.print("11");
  tft.setCursor(113, 46);
  tft.print("10");
  tft.setCursor(113, 57);
  tft.print("9");
  tft.setCursor(113, 68);
  tft.print("8");
  tft.setCursor(113, 79);
  tft.print("7");
  tft.setCursor(113, 90);
  tft.print("6");
  tft.setCursor(113, 101);
  tft.print("5");

  // построение графика влажности
  for (int i = 21; i < 109; i++) {
    tft.drawLine(i, 109, i, 100 - H_IN_MASS[i - 21] + 2, ST7735_BLUE);
    tft.drawPixel(i, T_IN_MASS[i - 21], ST7735_RED);
    tft.drawPixel(i, T_IN_MASS[i - 21]+1, ST7735_RED);
    tft.drawPixel(i, P_IN_MASS[i - 21], 0xff6600);
    tft.drawPixel(i, P_IN_MASS[i - 21]+1, 0xff6600);
  }
}

void screen1() {
  // вывод температуры воздуха
  temp2tft(T_IN, 10, 117, 2, ST7735_RED, 0);

  // вывод давления
  tft.setTextColor(0xff6600);
  tft.setCursor(65, 117);
  tft.print(P_IN / 10);
  temp2tft(270, 101, 117, 1, ST7735_MAGENTA, 10);
  tft.setTextColor(0xff6600);
  tft.setCursor(101, 124);
  tft.print("mmHg");

  // вывод эффективной температуры
  temp2tft(Teff, 10, 133, 2, ST7735_GREEN, 0);

  // вывод влажности
  temp2tft(H_IN, 59, 133, 2, ST7735_BLUE, 1);

  // вывод даты
  tft.setTextSize(1);
  tft.setTextColor(ST7735_YELLOW);
  tft.setCursor(10, tft.height() - hText1 - 2);
  tft.print(hourRTC);
  tft.setCursor(10 + wText1 * 2, tft.height() - hText1 - 2);
  tft.print(":");
  tft.setCursor(10 + wText1 * 3, tft.height() - hText1 - 2);
  tft.print(minuteRTC);

  tft.setTextColor(ST7735_CYAN);
  tft.setCursor(60, tft.height() - hText1 - 2);
  tft.print(dayRTC);
  tft.setCursor(60 + wText1 * 2, tft.height() - hText1 - 2);
  tft.print(".");
  tft.setCursor(60 + wText1 * 3, tft.height() - hText1 - 2);
  tft.print(monthRTC);
  tft.setCursor(60 + wText1 * 5, tft.height() - hText1 - 2);
  tft.print(".");
  tft.setCursor(60 + wText1 * 6, tft.height() - hText1 - 2);
  tft.print(yearRTC);

}

void temp2tft(int var, byte x, byte y, byte textSize, uint16_t color, byte simbol) {
  tft.setTextSize(textSize);
  tft.setTextColor(color);
  int T_int = abs(var / 100);
  int T_frac = abs(var % 100 / 10);
  // температура меньше 0
  if (var <= 0) {
    if (T_int <= 9) {
      tft.setCursor(x, y);
      tft.print(T_int);
      tft.setCursor(x + (5 * textSize + 2), y);
      tft.print("-");
      tft.setCursor(x + 2 * (5 * textSize + 2), y);
      tft.print(T_frac);

    } else {
      tft.setCursor(x, y);
      tft.print("-");
      tft.setCursor(x + (5 * textSize + 2), y);
      tft.print(T_int);

    }
  }
  // температура больше 0
  else {
    if (T_int <= 9) {
      tft.setCursor(x, y);
      tft.print(T_int);
      tft.setCursor(x + (5 * textSize + 2), y);
      tft.print(".");
      tft.setCursor(x + 2 * (5 * textSize + 2), y);
      tft.print(T_frac);

    } else {
      tft.setCursor(x + (5 * textSize + 2), y);
      tft.print(T_int);

    }
  }
  switch (simbol) {
    case 0:
      // знак градуса
      tft.drawCircle(x + 3 * (5 * textSize + 2) + 2, y + 2, textSize, color);
      break;
    case 1:
      tft.setCursor(x + 3 * (5 * textSize + 2) + 2, y + 2);
      tft.print("%");
      break;
  }
}

unsigned long cloud(float ddp) {
  return (208 * fabs(ddp));
}

// функция чтения реального напряжения питания
long readVcc()
{
  /// Read 1.1V reference against AVcc
  // set the reference to Vcc and the measurement to the internal 1.1V reference
#if defined(__AVR_ATmega32U4__) || defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)
  ADMUX = _BV(REFS0) | _BV(MUX4) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1);
#elif defined (__AVR_ATtiny24__) || defined(__AVR_ATtiny44__) || defined(__AVR_ATtiny84__)
  ADMUX = _BV(MUX5) | _BV(MUX0);
#elif defined (__AVR_ATtiny25__) || defined(__AVR_ATtiny45__) || defined(__AVR_ATtiny85__)
  ADMUX = _BV(MUX3) | _BV(MUX2);
#else
  ADMUX = _BV(REFS0) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1);
#endif

  delay(75); // Wait for Vref to settle
  ADCSRA |= _BV(ADSC); // Start conversion
  while (bit_is_set(ADCSRA, ADSC)); // measuring

  uint8_t low  = ADCL; // must read ADCL first - it then locks ADCH
  uint8_t high = ADCH; // unlocks both

  long result = (high << 8) | low;

  result = 1125300L / result; // Calculate Vcc (in mV); 1125300 = 1.1*1023*1000
  long VCC_REAL = result;
  return VCC_REAL; // Vcc in millivolts
}

void testlines(uint16_t color) {
  tft.fillScreen(ST7735_BLACK);
  for (int16_t x = 0; x < tft.width(); x += 6) {
    tft.drawLine(0, 0, x, tft.height() - 1, color);
  }
  for (int16_t y = 0; y < tft.height(); y += 6) {
    tft.drawLine(0, 0, tft.width() - 1, y, color);
  }

  tft.fillScreen(ST7735_BLACK);
  for (int16_t x = 0; x < tft.width(); x += 6) {
    tft.drawLine(tft.width() - 1, 0, x, tft.height() - 1, color);
  }
  for (int16_t y = 0; y < tft.height(); y += 6) {
    tft.drawLine(tft.width() - 1, 0, 0, y, color);
  }

  tft.fillScreen(ST7735_BLACK);
  for (int16_t x = 0; x < tft.width(); x += 6) {
    tft.drawLine(0, tft.height() - 1, x, 0, color);
  }
  for (int16_t y = 0; y < tft.height(); y += 6) {
    tft.drawLine(0, tft.height() - 1, tft.width() - 1, y, color);
  }

  tft.fillScreen(ST7735_BLACK);
  for (int16_t x = 0; x < tft.width(); x += 6) {
    tft.drawLine(tft.width() - 1, tft.height() - 1, x, 0, color);
  }
  for (int16_t y = 0; y < tft.height(); y += 6) {
    tft.drawLine(tft.width() - 1, tft.height() - 1, 0, y, color);
  }
}

void drawText(int x, int y, int num, uint16_t color, int sizeText) {
  tft.setCursor(x , y);
  tft.setTextColor(color);
  //tft.setTextWrap(true);
  tft.setTextSize(sizeText);
  tft.print(num);
}

void testfastlines(uint16_t color1, uint16_t color2) {
  tft.fillScreen(ST7735_BLACK);
  for (int16_t y = 0; y < tft.height(); y += 5) {
    tft.drawFastHLine(0, y, tft.width(), color1);
  }
  for (int16_t x = 0; x < tft.width(); x += 5) {
    tft.drawFastVLine(x, 0, tft.height(), color2);
  }
}

void testdrawrects(uint16_t color) {
  tft.fillScreen(ST7735_BLACK);
  for (int16_t x = 0; x < tft.width(); x += 6) {
    tft.drawRect(tft.width() / 2 - x / 2, tft.height() / 2 - x / 2 , x, x, color);
  }
}

void testfillrects(uint16_t color1, uint16_t color2) {
  tft.fillScreen(ST7735_BLACK);
  for (int16_t x = tft.width() - 1; x > 6; x -= 6) {
    tft.fillRect(tft.width() / 2 - x / 2, tft.height() / 2 - x / 2 , x, x, color1);
    tft.drawRect(tft.width() / 2 - x / 2, tft.height() / 2 - x / 2 , x, x, color2);
  }
}

void testfillcircles(uint8_t radius, uint16_t color) {
  for (int16_t x = radius; x < tft.width(); x += radius * 2) {
    for (int16_t y = radius; y < tft.height(); y += radius * 2) {
      tft.fillCircle(x, y, radius, color);
    }
  }
}

void testdrawcircles(uint8_t radius, uint16_t color) {
  for (int16_t x = 0; x < tft.width() + radius; x += radius * 2) {
    for (int16_t y = 0; y < tft.height() + radius; y += radius * 2) {
      tft.drawCircle(x, y, radius, color);
    }
  }
}

void testtriangles() {
  tft.fillScreen(ST7735_BLACK);
  int color = 0xF800;
  int t;
  int w = tft.width() / 2;
  int x = tft.height() - 1;
  int y = 0;
  int z = tft.width();
  for (t = 0 ; t <= 15; t += 1) {
    tft.drawTriangle(w, y, y, x, z, x, color);
    x -= 4;
    y += 4;
    z -= 4;
    color += 100;
  }
}

void testroundrects() {
  tft.fillScreen(ST7735_BLACK);
  int color = 100;
  int i;
  int t;
  for (t = 0 ; t <= 4; t += 1) {
    int x = 0;
    int y = 0;
    int w = tft.width() - 2;
    int h = tft.height() - 2;
    for (i = 0 ; i <= 16; i += 1) {
      tft.drawRoundRect(x, y, w, h, 5, color);
      x += 2;
      y += 3;
      w -= 4;
      h -= 6;
      color += 1100;
    }
    color += 100;
  }
}

void tftPrintTest() {
  tft.setTextWrap(false);
  tft.fillScreen(ST7735_BLACK);
  tft.setCursor(0, 30);
  tft.setTextColor(ST7735_RED);
  tft.setTextSize(1);
  tft.println("Hello World!");
  tft.setTextColor(ST7735_YELLOW);
  tft.setTextSize(2);
  tft.println("Hello World!");
  tft.setTextColor(ST7735_GREEN);
  tft.setTextSize(3);
  tft.println("Hello World!");
  tft.setTextColor(ST7735_BLUE);
  tft.setTextSize(4);
  tft.print(1234.567);
  delay(1500);
  tft.setCursor(0, 0);
  tft.fillScreen(ST7735_BLACK);
  tft.setTextColor(ST7735_WHITE);
  tft.setTextSize(0);
  tft.println("Hello World!");
  tft.setTextSize(1);
  tft.setTextColor(ST7735_GREEN);
  tft.print(3.14159, 6);
  tft.println(" Want pi?");
  tft.println(" ");
  tft.print(8675309, HEX); // print 8,675,309 out in HEX!
  tft.println(" Print HEX!");
  tft.println(" ");
  tft.setTextColor(ST7735_WHITE);
  tft.println("Sketch has been");
  tft.println("running for: ");
  tft.setTextColor(ST7735_MAGENTA);
  tft.print(millis() / 1000);
  tft.setTextColor(ST7735_WHITE);
  tft.print(" seconds.");
}

void mediabuttons() {
  // play
  tft.fillScreen(ST7735_BLACK);
  tft.fillRoundRect(25, 10, 78, 60, 8, ST7735_WHITE);
  tft.fillTriangle(42, 20, 42, 60, 90, 40, ST7735_RED);
  delay(500);
  // pause
  tft.fillRoundRect(25, 90, 78, 60, 8, ST7735_WHITE);
  tft.fillRoundRect(39, 98, 20, 45, 5, ST7735_GREEN);
  tft.fillRoundRect(69, 98, 20, 45, 5, ST7735_GREEN);
  delay(500);
  // play color
  tft.fillTriangle(42, 20, 42, 60, 90, 40, ST7735_BLUE);
  delay(50);
  // pause color
  tft.fillRoundRect(39, 98, 20, 45, 5, ST7735_RED);
  tft.fillRoundRect(69, 98, 20, 45, 5, ST7735_RED);
  // play color
  tft.fillTriangle(42, 20, 42, 60, 90, 40, ST7735_GREEN);
}
