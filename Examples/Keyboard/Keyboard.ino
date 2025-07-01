#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"
#include "fonts\FreeSans12pt7b.h"
#include "Adafruit_ILI9341_Keypad.h"

#define FONT_BUTTON FreeSans12pt7b

#define T_CS 0
#define T_IRQ 1
#define TFT_DC 9
#define TFT_CS 10
#define TFT_RST 8

#define DISABLE_COLOR 0x8410

Adafruit_ILI9341 Display = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RST);

XPT2046_Touchscreen Touch(T_CS, T_IRQ);

TS_Point TP;


Keyboard SSIDPasswordPad(&Display, &Touch);


void setup() {


  Serial.begin(115200);

  Display.begin();
  Display.setRotation(1);
  Display.fillScreen(ILI9341_BLACK);

  Touch.begin();
  Touch.setRotation(1);
  SSIDPasswordPad.init(ILI9341_BLACK, ILI9341_WHITE, ILI9341_NAVY, ILI9341_WHITE, ILI9341_DARKGREY, &FONT_BUTTON);

  // optional change color of text entry in keyboard
  SSIDPasswordPad.setDisplayColor(ILI9341_WHITE, ILI9341_RED);
  //SSIDPasswordPad.setCornerRadius(5);
  SSIDPasswordPad.setInitialText("Enter password");
  // SSIDPasswordPad.hideInput();
}

void loop() {

  Display.fillScreen(ILI9341_BLACK);
  // optional to clear data before displaying keyboard
  SSIDPasswordPad.clearInput();
  SSIDPasswordPad.getInput();

  Serial.print("Entered value: ");
  Serial.println(SSIDPasswordPad.data);

  const char *pw;

  pw = SSIDPasswordPad.data;
  Serial.println(pw);
}
