/*
  The MIT License (MIT)

  library writen by Kris Kasprzak

  Permission is hereby granted, free of charge, to any person obtaining a copy of
  this software and associated documentation files (the "Software"), to deal in
  the Software without restriction, including without limitation the rights to
  use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
  the Software, and to permit persons to whom the Software is furnished to do so,
  subject to the following conditions:
  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.
  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
  FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
  COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
  IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
  CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

  On a personal note, if you develop an application or product using this library
  and make millions of dollars, I'm happy for you!

  rev   date      author        change
  1.0   2/12/2023      kasprzak      initial code
  1.1   2/21/2023      kasprzak      fixed number overrun issue
  2.0   3/14/2023      kasprzak      fixed fonts for MEGA
  3.0   3/14/2024      kasprzak      complete rewrite to support ESP32
  4.0   4/30/2024      kasprzak      added corner rounding added trailing zero removal
  5.0   7/14/2024      kasprzak      added support for audible click when button pressed (requires hardward buzzer)
				     added support to specify decimal places	
*/

#ifndef ADAFRUIT_ILI9341_KEYPAD_H
#define ADAFRUIT_ILI9341_KEYPAD_H

#define ADAFRUIT_ILI9341_KEYPAD_VER 5.0

#if ARDUINO >= 100
	 #include "Arduino.h"
	 #include "Print.h"
#else
	
#endif

#ifdef __cplusplus
	
#endif

#include <Adafruit_ILI9341.h> 
#include <XPT2046_Touchscreen.h>

#define BTNS 30
#define BTNM 2

#define ROW1 54
#define ROW2 86
#define ROW3 118
#define ROW4 150
#define ROW5 182
#define ROW6 220


#define COL1 17
#define COL2 49
#define COL3 81
#define COL4 113
#define COL5 145
#define COL6 177
#define COL7 209
#define COL8 241
#define COL9 273
#define COL10 305

#define BUTTON_PRESSED 0
#define BUTTON_RELEASED 1

#define	ADAFRUIT_ILI9341_KEYPAD_BLUE    		0x001F
#define	ADAFRUIT_ILI9341_KEYPAD_RED     		0xF800
#define	ADAFRUIT_ILI9341_KEYPAD_GREEN   		0x07E0

#define MAX_KEYBOARD_CHARS 10
	
class  NumberPad {
		
public:

	NumberPad(Adafruit_ILI9341 *Display, XPT2046_Touchscreen *Touch);

	void init(uint16_t BackColor,uint16_t TextColor, uint16_t ButtonColor, 
	uint16_t PressedTextColor, uint16_t PressedButtonColor,
	const GFXfont *ButtonFont);

	void getInput();
	
	void setLocation(uint16_t CenterWidth, uint16_t CenterHeight);
	
	void setButtonSizes(uint16_t ButtonWidth, uint16_t ButtonHeight, uint16_t Margins, uint16_t OKButtonWidth, uint16_t OKButtonHeight);
	
	void enableDecimal(bool State = true);

	void setDecimals(uint8_t Value);
	
	void setClickPin(int Value);

	void enableNegative(bool State = true);
	
	void setDisplayColor(uint16_t TextColor, uint16_t BackColor);
	
	void setMinMax(float MininumValue, float MaximumValue);
	
	void setCornerRadius(uint8_t Radius);
	
	void setInitialText(const char *Text);
	
	void hideInput();
	
	void useButtonIcon(bool UseIcon);
	
	char *getCharValue();
	
	void setTouchLimits(uint16_t ScreenLeft, uint16_t ScreenRight,uint16_t ScreenTop, uint16_t ScreenBottom);
	
	void setColors(
		uint16_t BackColor, 
		uint16_t TextColor, 
		uint16_t ButtonColor, 
		uint16_t BorderColor, 
		uint16_t PressedTextColor, 
		uint16_t PressedButtonColor,
		uint16_t PressedBorderColor
		);

	float value;

private:

	
	Adafruit_ILI9341 *d;
	XPT2046_Touchscreen  *t;
	TS_Point p;
	const GFXfont *f;
	
	
	struct BUTTON{	
		uint16_t x;
		uint16_t y;
		uint8_t w;
		uint8_t h;
		uint8_t ascii;
	};
	
	const int Row0 = 10;
	const int Row1 = 50+5;
	const int Row2 = 90+10;
	const int Row3 = 130+15;
	const int Row4 = 170+20;
	bool useicon = false;
	const int Col1 = 50;
	const int Col2 = 90+5;
	const int Col3 = 130+10;
	const int Col4 = 170+15;
	int16_t tx, ty;
	uint16_t tw, th;
	uint8_t bHigh = 40, bWide = 40, rad = 0;
	uint16_t CW = 160;  // width center of screen
	uint16_t CH = 120;  // height center of screen
	uint16_t BH = 35;
	uint16_t BW = 60;
	uint16_t BS = 5;
	uint16_t TBH = 30;
	uint16_t OKBW = 70;
	uint16_t OKBH = 70;
	char inittext[MAX_KEYBOARD_CHARS+2];  // display initial text
	char hc[MAX_KEYBOARD_CHARS+2];
	char dn[MAX_KEYBOARD_CHARS+2];  // display number
	uint16_t BtnX, BtnY;
	uint16_t kcolor;
	uint16_t tcolor; 
	uint16_t bcolor;
	uint16_t ptcolor;
	uint16_t pbcolor;
	int16_t inputb;
	int16_t inputt;
	bool decstate = true;
	bool negstate = true;
	bool minmaxstate = false;
	bool hasinittext = false;
	bool hideinput = false;
	float minval = 0.0;
	float maxval = 0.0;
	bool rangeOK = true;
	uint8_t numdec = 3;
	int clickpin = -1;

	// 'Check', 50x50px
	const unsigned char check [350] PROGMEM = {
		0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x80, 0x00, 0x00, 
		0x00, 0x00, 0x00, 0x1f, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0xc0, 0x00, 0x00, 0x00, 0x00, 
		0x00, 0x7f, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7f, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 
		0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xfe, 0x00, 0x00, 
		0x00, 0x00, 0x00, 0x07, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xfc, 0x00, 0x00, 0x00, 0x00, 
		0x00, 0x0f, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 
		0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7f, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7f, 0xc0, 0x00, 
		0x00, 0x00, 0x00, 0x00, 0xff, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x01, 0xff, 0x80, 0x00, 0x00, 0x00, 
		0x00, 0x03, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 
		0xfe, 0x00, 0x00, 0x03, 0x00, 0x00, 0x0f, 0xfc, 0x00, 0x00, 0x1f, 0xc0, 0x00, 0x1f, 0xfc, 0x00, 
		0x00, 0x1f, 0xe0, 0x00, 0x3f, 0xf8, 0x00, 0x00, 0x3f, 0xf0, 0x00, 0x7f, 0xf0, 0x00, 0x00, 0x3f, 
		0xf0, 0x00, 0x7f, 0xf0, 0x00, 0x00, 0x7f, 0xf8, 0x00, 0xff, 0xe0, 0x00, 0x00, 0x7f, 0xfc, 0x01, 
		0xff, 0xc0, 0x00, 0x00, 0x3f, 0xfc, 0x03, 0xff, 0x80, 0x00, 0x00, 0x3f, 0xfe, 0x07, 0xff, 0x80, 
		0x00, 0x00, 0x1f, 0xff, 0x07, 0xff, 0x00, 0x00, 0x00, 0x1f, 0xff, 0x0f, 0xfe, 0x00, 0x00, 0x00, 
		0x0f, 0xff, 0x9f, 0xfe, 0x00, 0x00, 0x00, 0x07, 0xff, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x07, 0xff, 
		0xff, 0xf8, 0x00, 0x00, 0x00, 0x03, 0xff, 0xff, 0xf8, 0x00, 0x00, 0x00, 0x01, 0xff, 0xff, 0xf0, 
		0x00, 0x00, 0x00, 0x01, 0xff, 0xff, 0xe0, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xe0, 0x00, 0x00, 
		0x00, 0x00, 0x7f, 0xff, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x3f, 0xff, 0x80, 0x00, 0x00, 0x00, 0x00, 
		0x3f, 0xff, 0x80, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xfe, 
		0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xfc, 0x00, 0x00, 
		0x00, 0x00, 0x00, 0x03, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xf0, 0x00, 0x00, 0x00, 0x00, 
		0x00, 0x01, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	};
	// 'backspace', 54x30px
	const unsigned char backspace [210] PROGMEM = {
		0x00, 0x00, 0x1f, 0xff, 0xff, 0xff, 0xc0, 0x00, 0x00, 0x7f, 0xff, 0xff, 0xff, 0xc0, 0x00, 0x00, 
		0xff, 0xff, 0xff, 0xff, 0xe0, 0x00, 0x01, 0xff, 0xff, 0xff, 0xff, 0xe0, 0x00, 0x03, 0xff, 0xff, 
		0xff, 0xff, 0xe0, 0x00, 0x07, 0xff, 0xff, 0xff, 0xff, 0xe0, 0x00, 0x0f, 0xff, 0x8f, 0xff, 0x3f, 
		0xe0, 0x00, 0x1f, 0xff, 0x87, 0xfe, 0x3f, 0xe0, 0x00, 0x3f, 0xff, 0xc3, 0xfc, 0x3f, 0xe0, 0x00, 
		0x7f, 0xff, 0xe1, 0xf8, 0x7f, 0xe0, 0x00, 0xff, 0xff, 0xf0, 0xf0, 0xff, 0xe0, 0x01, 0xff, 0xff, 
		0xf8, 0x61, 0xff, 0xe0, 0x03, 0xff, 0xff, 0xfc, 0x03, 0xff, 0xe0, 0x03, 0xff, 0xff, 0xfe, 0x0f, 
		0xff, 0xe0, 0x07, 0xff, 0xff, 0xff, 0x0f, 0xff, 0xe0, 0x03, 0xff, 0xff, 0xfe, 0x07, 0xff, 0xe0, 
		0x03, 0xff, 0xff, 0xfc, 0x43, 0xff, 0xe0, 0x01, 0xff, 0xff, 0xf8, 0xe1, 0xff, 0xe0, 0x00, 0xff, 
		0xff, 0xf1, 0xf0, 0xff, 0xe0, 0x00, 0x7f, 0xff, 0xe1, 0xf8, 0x7f, 0xe0, 0x00, 0x3f, 0xff, 0xc7, 
		0xfc, 0x3f, 0xe0, 0x00, 0x1f, 0xff, 0x8f, 0xfe, 0x3f, 0xe0, 0x00, 0x0f, 0xff, 0xdf, 0xff, 0x3f, 
		0xe0, 0x00, 0x07, 0xff, 0xff, 0xff, 0xff, 0xe0, 0x00, 0x03, 0xff, 0xff, 0xff, 0xff, 0xe0, 0x00, 
		0x01, 0xff, 0xff, 0xff, 0xff, 0xe0, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xe0, 0x00, 0x00, 0x7f, 
		0xff, 0xff, 0xff, 0xc0, 0x00, 0x00, 0x1f, 0xff, 0xff, 0xff, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 
		0x00, 0x00
	};
	// 'cancel', 50x50px
	const unsigned char cancel [350] PROGMEM = {
		0x00, 0xc0, 0x00, 0x00, 0x00, 0x60, 0x00, 0x01, 0xe0, 0x00, 0x00, 0x00, 0xf0, 0x00, 0x03, 0xf0, 
		0x00, 0x00, 0x01, 0xf8, 0x00, 0x07, 0xf8, 0x00, 0x00, 0x03, 0xfc, 0x00, 0x0f, 0xfc, 0x00, 0x00, 
		0x07, 0xfe, 0x00, 0x1f, 0xfe, 0x00, 0x00, 0x0f, 0xff, 0x00, 0x3f, 0xff, 0x00, 0x00, 0x1f, 0xff, 
		0x80, 0x7f, 0xff, 0x80, 0x00, 0x3f, 0xff, 0xc0, 0x7f, 0xff, 0xc0, 0x00, 0x7f, 0xff, 0xc0, 0x3f, 
		0xff, 0xe0, 0x00, 0xff, 0xff, 0x80, 0x1f, 0xff, 0xf0, 0x01, 0xff, 0xfe, 0x00, 0x0f, 0xff, 0xf8, 
		0x03, 0xff, 0xfe, 0x00, 0x07, 0xff, 0xfc, 0x07, 0xff, 0xfc, 0x00, 0x03, 0xff, 0xfe, 0x0f, 0xff, 
		0xf0, 0x00, 0x01, 0xff, 0xff, 0x1f, 0xff, 0xf0, 0x00, 0x00, 0xff, 0xff, 0xbf, 0xff, 0xe0, 0x00, 
		0x00, 0x7f, 0xff, 0xff, 0xff, 0xc0, 0x00, 0x00, 0x3f, 0xff, 0xff, 0xff, 0x80, 0x00, 0x00, 0x1f, 
		0xff, 0xff, 0xfe, 0x00, 0x00, 0x00, 0x0f, 0xff, 0xff, 0xfe, 0x00, 0x00, 0x00, 0x07, 0xff, 0xff, 
		0xfc, 0x00, 0x00, 0x00, 0x03, 0xff, 0xff, 0xf8, 0x00, 0x00, 0x00, 0x01, 0xff, 0xff, 0xf0, 0x00, 
		0x00, 0x00, 0x00, 0xff, 0xff, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x7f, 0xff, 0xc0, 0x00, 0x00, 0x00, 
		0x00, 0xff, 0xff, 0xe0, 0x00, 0x00, 0x00, 0x01, 0xff, 0xff, 0xf0, 0x00, 0x00, 0x00, 0x03, 0xff, 
		0xff, 0xf8, 0x00, 0x00, 0x00, 0x07, 0xff, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x0f, 0xff, 0xff, 0xfe, 
		0x00, 0x00, 0x00, 0x1f, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x3f, 0xff, 0xff, 0xff, 0x80, 0x00, 
		0x00, 0x7f, 0xff, 0xff, 0xff, 0xc0, 0x00, 0x00, 0xff, 0xff, 0x3f, 0xff, 0xe0, 0x00, 0x01, 0xff, 
		0xfe, 0x1f, 0xff, 0xf0, 0x00, 0x03, 0xff, 0xfe, 0x0f, 0xff, 0xf8, 0x00, 0x07, 0xff, 0xf8, 0x07, 
		0xff, 0xfc, 0x00, 0x0f, 0xff, 0xf0, 0x03, 0xff, 0xfe, 0x00, 0x1f, 0xff, 0xe0, 0x01, 0xff, 0xff, 
		0x00, 0x3f, 0xff, 0xc0, 0x00, 0xff, 0xff, 0x80, 0x7f, 0xff, 0xc0, 0x00, 0x7f, 0xff, 0xc0, 0x7f, 
		0xff, 0x00, 0x00, 0x3f, 0xff, 0xc0, 0x3f, 0xfe, 0x00, 0x00, 0x1f, 0xff, 0x00, 0x1f, 0xfc, 0x00, 
		0x00, 0x0f, 0xfe, 0x00, 0x0f, 0xf8, 0x00, 0x00, 0x07, 0xfc, 0x00, 0x07, 0xf0, 0x00, 0x00, 0x03, 
		0xf8, 0x00, 0x03, 0xe0, 0x00, 0x00, 0x01, 0xf0, 0x00, 0x01, 0xc0, 0x00, 0x00, 0x00, 0xe0, 0x00, 
		0x00, 0x80, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	};
	 
	int16_t screenX0, screenX320;
	int16_t screenY0, screenY240;
	void drawMonoBitmap(uint16_t x, uint16_t y, const unsigned char *bitmap, uint8_t w, uint8_t h, uint16_t color);
	void BuildButton(BUTTON *temp, int Col, int Row, uint8_t Wide, uint8_t High, uint8_t ascii);
	void DrawButton(BUTTON *temp, uint8_t State);
	bool Pressed(BUTTON *temp);
	void DisplayInput();
	void ProcessTouch();


};

class  Keyboard {
		
public:

	Keyboard(Adafruit_ILI9341 *Display, XPT2046_Touchscreen *Touch);

	void init(uint16_t BackColor,uint16_t ButtonTextColor, uint16_t ButtonColor, uint16_t PressedTextColor, uint16_t PressedButtonColor, const GFXfont *TextFont);

	void getInput();
	
	void setCornerRadius(uint8_t Radius);

        void setClickPin(int Value);

	void setDisplayColor(uint16_t TextColor, uint16_t BackColor);
	
    char data[MAX_KEYBOARD_CHARS+1];
	
	void hideInput();
	
	void setTouchLimits(uint16_t ScreenLeft, uint16_t ScreenRight,uint16_t ScreenTop, uint16_t ScreenBottom);
		
	
	void clearInput();

private:

	struct BUTTON{	
		uint16_t x;
		uint16_t y;
		uint8_t w;
	};

	Adafruit_ILI9341 *d;
	XPT2046_Touchscreen  *t;
	TS_Point p;
	
	const GFXfont *f;

	const int Row0 = 24 - 16;
	const int Row1 = 54 - 8;
	const int Row2 = 86 - 8;
	const int Row3 = 118 - 8;
	const int Row4 = 150 - 8;
	const int Row5 = 182 - 8;
	const int Row6 = 214 - 8;

	const int Col1 = 17 - 12;
	const int Col2 = 49 - 12;
	const int Col3 = 81 - 12;
	const int Col4 = 113 - 12;
	const int Col5 = 145 - 12;
	const int Col6 = 177 - 12;
	const int Col7 = 209 - 12;
	const int Col8 = 241 - 12;
	const int Col9 = 273 - 12;
	const int Col10 = 305 - 12;

	void ProcessTouch();
	char dn[MAX_KEYBOARD_CHARS+1];
	char hc[MAX_KEYBOARD_CHARS+2];
	char inittext[MAX_KEYBOARD_CHARS+1];  // display initial text
	
	bool aclear = false;
	bool hideinput = false;
	bool hasinittext = false;
	uint16_t BtnX, BtnY;
	uint16_t kcolor;
	uint16_t tcolor; 
	uint16_t bcolor;
	uint16_t ptcolor;
	uint16_t pbcolor;
	int16_t inputb;
	int16_t inputt;
	uint8_t rad;
	int16_t screenX0, screenX320;
	int16_t screenY0, screenY240;
	int clickpin;
	int8_t Size;
	bool CapsLock = false;

	void BuildButton(BUTTON *temp, int Col, int Row);
	void BuildButton(BUTTON *temp, int Col, int Row, uint8_t Wide);
	void DrawButton(BUTTON *temp, uint8_t ASCII, uint8_t State);
	bool Pressed(BUTTON *temp, uint8_t ASCII);
	void DisplayInput();
	void setInitialText(const char *Text);	
	
	
};

#endif
