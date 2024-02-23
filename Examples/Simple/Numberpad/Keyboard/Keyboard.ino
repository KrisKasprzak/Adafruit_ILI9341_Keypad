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

#define T_CS 12
#define T_IRQ 27
#define TFT_DC 2
#define TFT_CS 5
#define TFT_RST 25
#define PIN_LED 26

#define DISABLE_COLOR 0x8410


Adafruit_ILI9341 Display = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RST);

XPT2046_Touchscreen Touch(T_CS, T_IRQ);

TS_Point TP;


Keyboard SSIDPasswordPad(&Display, &Touch);


void setup() {


  Serial.begin(115200);

  disableCore0WDT();
  disableCore1WDT();

  ledcSetup(0, 5000, 8);
  ledcAttachPin(PIN_LED, 0);

  Display.begin();

  ledcWrite(0, 255);

  Display.setRotation(3);
  Display.fillScreen(C_BLACK);

  Touch.begin();

  SSIDPasswordPad.init(ILI9341_BLACK, ILI9341_BLACK, ILI9341_CYAN, ILI9341_WHITE, ILI9341_DARKGREY, &FONT_BUTTON);


  // optional to clear data before displaying keyboard
  // SSIDPasswordPad.clearInput();


  // optional change color of text entry in keyboard
  // SSIDPasswordPad.setDisplayColor(uint16_t TextColor, uint16_t BackColor);

  SSIDPasswordPad.getInput();

  Display.fillScreen(C_BLACK);

  Serial.println(SSIDPasswordPad.data);
  // or
  const char *pw;

  pw = SSIDPasswordPad.data;
  Serial.println(pw);
}

void loop() {
}
