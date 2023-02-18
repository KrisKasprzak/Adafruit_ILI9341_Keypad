// required libraries
#include "Adafruit_ILI9341.h"
#include "fonts\FreeSans12pt7b.h"
#include "XPT2046_Touchscreen.h"
#include "Adafruit_ILI9341_Keypad.h"

#define CS_PIN 10
#define DC_PIN 9
#define RST_PIN 8
#define T_CS 0
#define T_IRQ 1

#define FONT_BUTTON FreeSans12pt7b  // font for keypad buttons that fits well

Adafruit_ILI9341 Display(CS_PIN, DC_PIN, RST_PIN);  //Display object

XPT2046_Touchscreen Touch(T_CS, T_IRQ);

Keyboard MyKeyboard(&Display, &Touch);
// or
NumberPad MyNumberPad(&Display, &Touch);

void setup() {

  Serial.begin(9600);

  Display.begin();
  Display.setRotation(1);

  Touch.begin();
  Touch.setRotation(1);

  Display.fillScreen(ILI9341_BLACK);

  MyKeyboard.init(ILI9341_BLACK, ILI9341_WHITE, ILI9341_BLUE, ILI9341_NAVY, ILI9341_WHITE, ILI9341_CYAN, ILI9341_YELLOW, FONT_BUTTON);
  // or
  // MyNumberPad.init(ILI9341_BLACK, ILI9341_WHITE, ILI9341_BLUE, ILI9341_NAVY, ILI9341_WHITE, ILI9341_CYAN, ILI9341_YELLOW, FONT_BUTTON);

  MyKeyboard.getInput();
  // MyNumberPad.getInput();

  Serial.print(MyKeyboard.data);
  // or
  // Serial.print(MyNumberPad.value);

}

void loop() {

}
