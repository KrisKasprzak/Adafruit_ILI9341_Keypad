#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"
#include "fonts\FreeSans18pt7b.h"
#include "fonts\FreeSans12pt7b.h"
#include "fonts\FreeSansBold12pt7b.h"
#include "fonts\FreeSans9pt7b.h"
#include "Adafruit_ILI9341_Keypad.h"
#define FONT_HEADER FreeSans12pt7b
#define FONT_HEADING FreeSans18pt7b
#define FONT_ITEM FreeSans12pt7b
#define FONT_BUTTON FreeSans12pt7b

#define T_CS 22
#define T_IRQ 15
#define TFT_DC 21
#define TFT_CS 2
#define TFT_RST 5
#define PIN_LED 4

#define DISABLE_COLOR 0x8410

// you will probably need to calibrate your screen, these are coordinates of presses on display
uint16_t ScreenLeft = 350, ScreenRight = 3900, ScreenTop = 300, ScreenBottom = 3800;


Adafruit_ILI9341 Display = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RST);

XPT2046_Touchscreen Touch(T_CS, T_IRQ);

TS_Point TP;


Keyboard SSIDPasswordPad(&Display, &Touch);


void setup() {


  Serial.begin(115200);

  //disableCore0WDT();
  //disableCore1WDT();

  ledcSetup(0, 5000, 8);
  ledcAttachPin(PIN_LED, 0);

  Display.begin();

  ledcWrite(0, 255);

  Display.setRotation(3);
  Display.fillScreen(ILI9341_BLACK);

  Touch.begin();
  Touch.setRotation(3);

  SSIDPasswordPad.init(ILI9341_BLACK, ILI9341_BLACK, ILI9341_LIGHTGREY, ILI9341_WHITE, ILI9341_DARKGREY, &FONT_BUTTON);
  SSIDPasswordPad.setTouchLimits(ScreenLeft, ScreenRight, ScreenTop, ScreenBottom);

  // optional

  // SSIDPasswordPad.clearInput();
  // SSIDPasswordPad.setCornerRadius(5);
  // SSIDPasswordPad.hideInput();
  // SSIDPasswordPad.setDisplayColor(uint16_t TextColor, uint16_t BackColor);
}

void loop() {

  SSIDPasswordPad.getInput();

  Display.fillScreen(ILI9341_BLACK);

  Serial.print("data method 1 ");
  Serial.println(SSIDPasswordPad.data);
  // or
  const char *pw;

  pw = SSIDPasswordPad.data;
  Serial.print("data method 2 ");
  Serial.println(pw);
}
