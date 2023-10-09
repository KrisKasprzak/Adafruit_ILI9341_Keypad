// required libraries
#include "Adafruit_ILI9341.h"
#include "fonts\FreeSans12pt7b.h"
#include "XPT2046_Touchscreen.h"
#include "Adafruit_ILI9341_Keypad.h"
#include "Adafruit_ILI9341_Controls.h" // make sure you have version 6.0

// easy way to include fonts but change globally
#define FONT_BUTTON FreeSans12pt7b  // font for keypad buttons

int BtnX = 0, BtnY = 0;
int i = 0;

// you know the drill
// use the second one, this is a mod I made to the lib
Adafruit_ILI9341 Display(27, 12, 5);  //Display object
// ILI9341_t3 Display(CS_PIN, DC_PIN, 8);  //Display object

XPT2046_Touchscreen Touch(2, 15);
TS_Point p;

// create some keypad objects
NumberPad MyNumberPad(&Display, &Touch);

void setup() {

pinMode(2, INPUT_PULLUP);

  Serial.begin(9600);

  // while ((millis() > 5000) || (!Serial)) {}

  // fire up the display
  Display.begin();
  Display.setRotation(3);

  Touch.begin();
  Touch.setRotation(1);

  Display.fillScreen(ILI9341_BLACK);

  // initialize the numberpad object
  // simulate a good old fashioned number input
  //void init(uint16_t BackColor,uint16_t TextColor, uint16_t ButtonColor, uint16_t BorderColor, 
  //	uint16_t PressedTextColor, uint16_t PressedButtonColor, uint16_t PressedBorderColor,
	// const GFXfont *ButtonFont);

  MyNumberPad.init(ILI9341_BLACK, ILI9341_BLACK, ILI9341_LIGHTGREY, ILI9341_DARKGREY, ILI9341_BLACK, ILI9341_DARKGREY, ILI9341_DARKGREY, &FONT_BUTTON);
 
  // optional methods
  // MyNumberPad.enableDecimal(bool State);   // disable / enable decimal point (enabled by default)
  // MyNumberPad.enableNegative(bool State);  // disable / enable negative sign (enabled by default)
  // MyNumberPad.setMinMax(float MininumValue, float MaximumValue); // want bound checks?
   MyNumberPad.setDecimalPlaces(3);           // want to control the number of displayed decimals
  // use the value property to set the initial value if desired
  MyNumberPad.value = 3.14159;


}

void loop() {

      Display.fillScreen(ILI9341_BLACK);
      MyNumberPad.getInput();

   
}


