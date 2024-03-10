// required libraries
#include "Adafruit_ILI9341.h"
#include "fonts\FreeSans12pt7b.h"
#include "XPT2046_Touchscreen.h"
#include "Adafruit_ILI9341_Keypad.h"

#define T_CS 12
#define T_IRQ 27
#define TFT_DC 2
#define TFT_CS 5
#define TFT_RST 25
#define PIN_LED 26

// easy way to include fonts but change globally
#define FONT_BUTTON FreeSans12pt7b  // font for keypad buttons

int BtnX = 0, BtnY = 0;
int i = 0;

// you will probably need to calibrate your screen, these are coordinates of presses on display
uint16_t ScreenLeft = 350, ScreenRight = 3900, ScreenTop = 300, ScreenBottom = 3800;

// you know the drill
Adafruit_ILI9341 Display = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RST);

XPT2046_Touchscreen Touch(T_CS, T_IRQ);
TS_Point p;

// create some keypad objects
NumberPad MyNumberPad(&Display, &Touch);

void setup() {

  Serial.begin(9600);

  // fire up the display
  Display.begin();

  Display.setRotation(1);

  Touch.begin();
  Touch.setRotation(1);

  // pin to set display brightness
  ledcSetup(0, 5000, 8);
  ledcAttachPin(PIN_LED, 0);
  ledcWrite(0, 255);

  Display.fillScreen(ILI9341_BLACK);

  // initialize the numberpad object
  // simulate a good old fashioned number input
  // void init(uint16_t BackColor,uint16_t TextColor, uint16_t ButtonColor,
  // uint16_t PressedTextColor, uint16_t PressedButtonColor,
  // const GFXfont *ButtonFont);

  MyNumberPad.init(ILI9341_BLACK, ILI9341_BLACK, ILI9341_LIGHTGREY, ILI9341_WHITE, ILI9341_DARKGREY, &FONT_BUTTON);
  MyNumberPad.setTouchLimits(ScreenLeft, ScreenRight, ScreenTop, ScreenBottom);

  // optional methods
  MyNumberPad.setDisplayColor(ILI9341_CYAN, ILI9341_DARKGREY);
  // MyNumberPad.useButtonIcon(true); // want icons for action buttons? omit call or false for text.
  MyNumberPad.enableDecimal();   // disable / enable decimal point (enabled by default)
  MyNumberPad.enableNegative();  // disable / enable negative sign (enabled by default)
  // MyNumberPad.setMinMax(3, 300); // want bounds checks (disables OK button if out of range)?
  // use the value property to set the initial value if desired
  // MyNumberPad.setInitialText("Height?");
  // MyNumberPad.value = 3.14159; // set initial value
  // MyNumberPad.hideInput();
}

void loop() {

  Display.fillScreen(ILI9341_RED);
  MyNumberPad.getInput();
  
  Serial.print("Entered value ");
  Serial.println(MyNumberPad.value);
}
