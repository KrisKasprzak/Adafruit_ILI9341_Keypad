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

*/

#include "Adafruit_ILI9341_Keypad.h"
#include <Adafruit_ILI9341.h>
#include <XPT2046_Touchscreen.h>

NumberPad::NumberPad(Adafruit_ILI9341 *Display, XPT2046_Touchscreen *Touch) {
  d = Display;
  t = Touch;
}

void NumberPad::init(uint16_t BackColor,
                     uint16_t TextColor, uint16_t ButtonColor,
                     uint16_t PressedTextColor,
                     uint16_t PressedButtonColor,
                     const GFXfont *ButtonFont) {

  kcolor = BackColor;
  tcolor = TextColor;
  bcolor = ButtonColor;
  ptcolor = PressedTextColor;
  pbcolor = PressedButtonColor;
  inputb = 0x00;
  inputt = 0xFFFF;
  value = 0.0;
  f = ButtonFont;
  bHigh = 40;
  bWide = 40;

  // in this class we are NOT initially writing to the char[0] as it's reserved for the - sign
  // hence we need to populate it to eliminate null terminator
}

void NumberPad::setTouchLimits(uint16_t ScreenLeft, uint16_t ScreenRight, uint16_t ScreenTop, uint16_t ScreenBottom) {

  screenX0 = ScreenLeft, screenX320 = ScreenRight, screenY0 = ScreenTop, screenY240 = ScreenBottom;
}

char *NumberPad::getCharValue() {

  return dn;
}

void NumberPad::setDisplayColor(uint16_t TextColor, uint16_t BackColor) {
  inputt = TextColor;
  inputb = BackColor;
}

void NumberPad::setLocation(uint16_t CenterWidth, uint16_t CenterHeight) {
  CW = CenterWidth;   // width center of screen
  CH = CenterHeight;  // height center of screen
}

void NumberPad::setButtonSizes(uint16_t ButtonWidth, uint16_t ButtonHeight, uint16_t Margins, uint16_t OKButtonWidth, uint16_t OKButtonHeight) {

  BW = ButtonWidth;
  BH = ButtonHeight;
  BS = Margins;
  OKBW = OKButtonWidth;
  OKBH = OKButtonHeight;
}

void NumberPad::enableDecimal(bool State ) {
  decstate = State;
}

void NumberPad::enableNegative(bool State ) {
  negstate = State;
}

void NumberPad::setMinMax(float MininumValue, float MaximumValue) {

  if (MininumValue == MaximumValue) {
    minmaxstate = false;
  } else {
    minmaxstate = true;
  }

  minval = MininumValue;
  maxval = MaximumValue;
}

void NumberPad::setInitialText(const char *Text) {

  uint8_t i;

  for (i = 0; i < (MAX_KEYBOARD_CHARS); i++) {
    inittext[i] = Text[i];
  }
  hasinittext = true;
}

void NumberPad::hideInput() {

  hideinput = true;
}

uint8_t NumberPad::get_float_digits(float num) {
  int digits = 0;
  float ori = num;  //storing original number
  long num2 = num;
  while (num2 > 0)  //count no of digits before floating point
  {
    digits++;
    num2 = num2 / 10;
  }
  if (ori == 0)
    digits = 1;
  num = ori;
  float no_float;
  no_float = ori * (pow(10, (8 - digits)));
  long long int total = (long long int)no_float;
  int no_of_digits, extrazeroes = 0;
  for (int i = 0; i < 8; i++) {
    int dig;
    dig = total % 10;
    total = total / 10;
    if (dig != 0)
      break;
    else
      extrazeroes++;
  }
  no_of_digits = 8 - extrazeroes;
  if (((long)num) != num) {
    // has decimal
    // no_of_digits++;
  }
  return no_of_digits;
}

void NumberPad::getInput() {

  uint16_t i = 0;
  uint16_t b = 0;
  bool hasDP = false;
  uint8_t np = 1;  // digit number
  bool CanBackUp = false;
  bool hasneg = false;
  bool KeepIn = true;
  float TheNumber = 0.0;
   

 // if (value != 0) {
 //   hasinittext = true;
 // }
  
  memset(dn, '\0', MAX_KEYBOARD_CHARS + 2);
  dn[0] = ' ';
  memset(hc, '\0', MAX_KEYBOARD_CHARS + 2);
  hc[0] = ' ';

  // get the decimals
  if (value != 0.0) {

    // odd but force negative to get the place holder for the sign [0]
    if (value < 0) {
      hasneg = true;
    } else {
      value = value * -1.0;
    }

    gcvt(value, 7, dn);

    if (!hasneg) {
      value = value * -1.0;
      dn[0] = ' ';
    }

    np = strlen(dn);  // account for possible sign
  }
  
  for (i = 0; i < strlen(dn); i++){
	  
	  if(dn[i] == '.'){
		  hasDP = true;
		  break;
	  }
  }
  	
  if (hideinput){
	  hc[0] = ' ';
    for (i = 1; i < strlen(dn); i++){	  
	  hc[i] = '*';
	}
  }

  BUTTON Buttons[15];

  BuildButton(&Buttons[0], Col2, Row4, bWide, bHigh, 0x30);             // 0
  BuildButton(&Buttons[1], Col1, Row1, bWide, bHigh, 0x31);             // 1
  BuildButton(&Buttons[2], Col2, Row1, bWide, bHigh, 0x32);             // 2
  BuildButton(&Buttons[3], Col3, Row1, bWide, bHigh, 0x33);             // 3
  BuildButton(&Buttons[4], Col1, Row2, bWide, bHigh, 0x34);             // 4
  BuildButton(&Buttons[5], Col2, Row2, bWide, bHigh, 0x35);             // 5
  BuildButton(&Buttons[6], Col3, Row2, bWide, bHigh, 0x36);             // 6
  BuildButton(&Buttons[7], Col1, Row3, bWide, bHigh, 0x37);             // 7
  BuildButton(&Buttons[8], Col2, Row3, bWide, bHigh, 0x38);             // 8
  BuildButton(&Buttons[9], Col3, Row3, bWide, bHigh, 0x39);             // 9
  BuildButton(&Buttons[10], Col1, Row4, bWide, bHigh, 0x2E);            // .
  BuildButton(&Buttons[11], Col3, Row4, bWide, bHigh, 0x2D);            // -
  BuildButton(&Buttons[12], Col4, Row0, bWide * 2, bHigh, 0x00);            // back
  BuildButton(&Buttons[13], Col4, Row1, bWide * 2, (bHigh * 2) + 5, 0x01);  // OK
  BuildButton(&Buttons[14], Col4, Row3, bWide * 2, (bHigh * 2) + 5, 0x02);  // cancel

  // large background box
  d->fillRect(Col1 - 5, Row0 - 5, Col4 - Col1 + Buttons[13].w + 10, Row4 - Row0 + bHigh + 10, kcolor);

  // text input box
  d->fillRect(Col1, Row0, Col3 - Col1 + bWide, bHigh, inputb);
  d->setFont(f);
  d->setTextColor(inputt, inputb);
  d->setCursor(Col1 + 5, Row0 + 25);

	if (hasinittext) {
		d->print(inittext);
	} 
	else if (hideinput){
		d->print(hc);
	}
	else {
		d->print(dn);
	}



  for (i = 0; i < 15; i++) {
    DrawButton(&Buttons[i], BUTTON_RELEASED);
  }
  

  while (KeepIn) {

    if (t->touched()) {

      ProcessTouch();
      for (b = 0; b < 15; b++) {
        if (Pressed(&Buttons[b])) {

          //valid number
          if (b <= 9) {

            if (np > MAX_KEYBOARD_CHARS) {

              break;
            }
            if ((dn[1] == '0') && (dn[2] != '.')) {

              dn[1] = b + '0';
              hc[1] = '*';
            } else {

              dn[np] = b + '0';
              hc[np] = '*';
              np++;
            }
            CanBackUp = true;
          } else if (b == 11) {
            //negative number
            if (dn[0] == '-') {
              dn[0] = ' ';
            } else {
              dn[0] = '-';
            }
          } else if (b == 10) {
            // decimal point
            if (!hasDP) {
              dn[np] = '.';
              hc[np] = '*';
              hasDP = true;
              np++;
            }
          } else if (b == 12) {
            // back space
            CanBackUp = false;
            if (np > 1) {
              --np;
              if (dn[np] == '.') { hasDP = false; }
              dn[np] = ' ';
              hc[np] = ' ';
            }

          } else if (b == 13) {
            // done
            TheNumber = atof(dn);
            value = TheNumber;
            KeepIn = false;
            break;
          } else if (b == 14) {
            // cancel, just get the heck out
            KeepIn = false;

            break;
          }
        }
		
	  }
        if (minmaxstate) {
          TheNumber = atof(dn);
          // check min bounds
          if ((TheNumber < minval) || (TheNumber > maxval)){
			  rangeOK = false;
			  DrawButton(&Buttons[13], BUTTON_PRESSED);
          }
		  else {
			  rangeOK = true;
			  DrawButton(&Buttons[13], BUTTON_RELEASED);
		  }
        }
      

      // text input box
      d->fillRect(Col1, Row0, Col3 - Col1 + bWide, bHigh, inputb);
	  d->setFont(f);
      d->setTextColor(inputt, inputb);
	  d->setCursor(Col1 + 5, Row0 + 25);
      

      if (hideinput) {
        d->print(hc);
      } else {
        d->print(dn);
      }
    }
  }

  // if no negative / shift chars
  if (!negstate) {
    for (i = 1; i < MAX_KEYBOARD_CHARS; i++) {
      dn[i - 1] = dn[i];
    }
    dn[i] = '\0';
  }
  
  Serial.println(value);
}

void NumberPad::useButtonIcon(bool UseIcon) { 
		useicon = UseIcon;
	}

void NumberPad::BuildButton(BUTTON *temp, int Col, int Row, uint8_t Wide, uint8_t High, uint8_t ascii) {
  temp->x = Col;
  temp->y = Row;
  temp->w = Wide;
  temp->h = High;
  temp->ascii = ascii;
}

void NumberPad::DrawButton(BUTTON *temp, uint8_t State) {

	if (!decstate && (temp->ascii == 0x2E)){
		Serial.println("no draw dec");
		
		return;
	}

	if (!negstate && (temp->ascii == 0x2D)){
		Serial.println(" no draw neg");
		return;
	}
  
  
  if (State == BUTTON_PRESSED) {
    if (rad > 0) {
      d->fillRoundRect(temp->x, temp->y, temp->w, temp->h, rad, pbcolor);
    } else {
      d->fillRect(temp->x, temp->y, temp->w, temp->h, pbcolor);
    }
    d->setTextColor(ptcolor, bcolor);
  } else {
    if (rad > 0) {
      d->fillRoundRect(temp->x, temp->y, temp->w, temp->h, rad, bcolor);
    } else {
      d->fillRect(temp->x, temp->y, temp->w, temp->h, bcolor);
    }
    d->setTextColor(tcolor, bcolor);
  }
  
	 if (useicon){
		 
		if (temp->ascii == 0x00) {
			drawMonoBitmap(temp->x+ 10,temp->y+5, backspace, 54, 30 , ADAFRUIT_ILI9341_KEYPAD_BLUE);
		} else if (temp->ascii == 0X01) {
			drawMonoBitmap(temp->x+15, temp->y+20, check, 50, 50 , ADAFRUIT_ILI9341_KEYPAD_GREEN);
		} else if (temp->ascii == 0x02) {
			drawMonoBitmap(temp->x+12, temp->y+20, cancel, 50, 50 , ADAFRUIT_ILI9341_KEYPAD_RED);
		}
	 }
	 else {
	  d->setFont(f);
	  if (temp->ascii == 0x00) {
		d->setCursor(temp->x+ 10,temp->y+30);
		d->print("Back");
	  } else if (temp->ascii == 0X01) {
		d->setCursor(temp->x+ 20,temp->y+50);
		d->print("OK");
	  } else if (temp->ascii == 0x02) {
		d->setCursor(temp->x+ 3,temp->y+50);
		d->print("Cancel");
	  }
	  }
// Print numbers	  
	d->getTextBounds("9", temp->x,  temp->y, &tx, &ty, &tw, &th);
	d->setCursor(temp->x - (tw/2) + bWide/2, temp->y + ((th)/2) + bHigh / 2);
	d->print((char)temp->ascii);
	 
	 
}

	void NumberPad::drawMonoBitmap(uint16_t x, uint16_t y, const unsigned char *bitmap, uint8_t w, uint8_t h, uint16_t color) {

	  uint8_t sbyte = 0;
	  uint8_t byteWidth = 0;
	  uint16_t jj, ii;

	  byteWidth = (w + 7) / 8;

	  for (jj = 0; jj < h; jj++) {
		for (ii = 0; ii < w; ii++) {
		  if (ii & 7)  sbyte <<= 1;
		  else sbyte   = pgm_read_byte(bitmap + jj * byteWidth + ii / 8);
		  if (sbyte & 0x80) d->drawPixel(x + ii, y + jj, color);
		}
	  }
	}

bool NumberPad::Pressed(BUTTON *temp) {
  bool found = false;
  bool redraw = true;
  bool redrawoff = false;


	if (!decstate && (temp->ascii == 0x2E)){
		return false;
	}

	if (!negstate && (temp->ascii == 0x2D)){
		return false;
	}
	
		if (!rangeOK && (temp->ascii == 0x01)){
		return false;
	}
	
  if ((BtnX > temp->x) && (BtnX < (temp->x + temp->w))) {
    if ((BtnY > temp->y) && (BtnY < (temp->y + temp->h))) {
      while (t->touched()) {
        if (((BtnX > temp->x) && (BtnX < (temp->x + temp->w))) && ((BtnY > temp->y) && (BtnY < (temp->y + temp->h)))) {
          if (redraw) {
            DrawButton(temp, BUTTON_PRESSED);
            redraw = false;
            redrawoff = true;
          }
          found = true;
        } else {
          if (redrawoff) {
            DrawButton(temp, BUTTON_RELEASED);
            redrawoff = false;
          }
          found = false;
          redraw = true;
        }

        ProcessTouch();
      }

      DrawButton(temp, BUTTON_RELEASED);
      return found;
    }
  }
  return false;
}


void NumberPad::ProcessTouch() {
  if (t->touched()) {

    p = t->getPoint();
    BtnX = p.x;
    BtnY = p.y;

#ifdef debug
    Serial.print("real coordinates:");
    Serial.print(BtnX);
    Serial.print(" ,");
    Serial.print(BtnY);
#endif

    //different displays may require reversing last 2 args
    BtnX = map(BtnX, screenX0, screenX320, 320, 0);
    BtnY = map(BtnY, screenY0, screenY240, 240, 0);
    // d->fillCircle(BtnX, BtnY,2, ILI9341_RED);
#ifdef debug
    Serial.print(" , Mapped coordinates:");
    Serial.print(BtnX);
    Serial.print(" ,");
    Serial.println(BtnY);

#endif
  }
}


/*

class to create a full keyboard with upper, lower case, special characters

due to size all buttons, spacings and location are hard coded. the keyboard will consume an entire 320 x 240 displays

output is a char 


*/



Keyboard::Keyboard(Adafruit_ILI9341 *Display, XPT2046_Touchscreen *Touch) {
  d = Display;
  t = Touch;
}
void Keyboard::init(uint16_t BackColor, uint16_t ButtonTextColor, uint16_t ButtonColor, uint16_t PressedTextColor, uint16_t PressedButtonColor, const GFXfont *TextFont) {
  kcolor = BackColor;
  tcolor = ButtonTextColor;
  bcolor = ButtonColor;
  ptcolor = PressedTextColor;
  pbcolor = PressedButtonColor;
  inputb = ButtonTextColor;
  inputt = ButtonColor;
  Size = 30;
  f = TextFont;

  screenX0 = 185, screenX320 = 3755, screenY0 = 350, screenY240 = 3785;
}

void Keyboard::setTouchLimits(uint16_t ScreenLeft, uint16_t ScreenRight, uint16_t ScreenTop, uint16_t ScreenBottom) {

  screenX0 = ScreenLeft, screenX320 = ScreenRight, screenY0 = ScreenTop, screenY240 = ScreenBottom;
}

void Keyboard::setDisplayColor(uint16_t TextColor, uint16_t BackColor) {
  inputt = TextColor;
  inputb = BackColor;
}

void Keyboard::BuildButton(BUTTON *temp, int Col, int Row) {
  temp->x = Col;
  temp->y = Row;
  temp->w = 1;
}

void Keyboard::BuildButton(BUTTON *temp, int Col, int Row, uint8_t Wide) {
  temp->x = Col;
  temp->y = Row;
  temp->w = Wide;
}

void Keyboard::DrawButton(BUTTON *temp, uint8_t ASCII, uint8_t State) {


  if (State == BUTTON_PRESSED) {
    if (rad > 0) {
      d->fillRoundRect(temp->x, temp->y, Size + ((temp->w - 1) * (2 + Size)), Size, rad, pbcolor);
    } else {
      d->fillRect(temp->x, temp->y, Size + ((temp->w - 1) * (2 + Size)), Size, pbcolor);
    }
    d->setTextColor(ptcolor, bcolor);
  } else {
    if (rad > 0) {
      d->fillRoundRect(temp->x, temp->y, Size + ((temp->w - 1) * (2 + Size)), Size, rad, bcolor);
    } else {
      d->fillRect(temp->x, temp->y, Size + ((temp->w - 1) * (2 + Size)), Size, bcolor);
    }
    d->setTextColor(tcolor, bcolor);
  }
  d->setCursor(temp->x + 7, temp->y + 21);
  d->setFont(f);

  if (ASCII == 168) {
    d->print("Space");
  } else if (ASCII == 169) {
    d->print("Done");
  } else if (ASCII == 170) {
    d->print("Cancel");
  } else if (ASCII == 171) {
    d->print("Back");
  } else if (ASCII == 172) {
    d->print("Aa");
  } else if (ASCII == 173) {
    d->print("#$%^");
  } else {
    d->print((char)ASCII);
  }
}

bool Keyboard::Pressed(BUTTON *temp, uint8_t ASCII) {
  bool found = false;
  bool redraw = true;
  bool redrawoff = false;

  if ((BtnX > temp->x) && (BtnX < (temp->x + (Size * temp->w)))) {
    if ((BtnY > temp->y) && (BtnY < (temp->y + Size))) {

      while (t->touched()) {
        if (((BtnX > temp->x) && (BtnX < (temp->x + (Size * temp->w)))) && ((BtnY > temp->y) && (BtnY < (temp->y + Size)))) {
          if (redraw) {
            DrawButton(temp, ASCII, BUTTON_PRESSED);
            redraw = false;
            redrawoff = true;
          }
          found = true;
        } else {
          if (redrawoff) {
            DrawButton(temp, ASCII, BUTTON_RELEASED);
            redrawoff = false;
          }
          found = false;
          redraw = true;
        }

        ProcessTouch();
      }

      DrawButton(temp, ASCII, BUTTON_RELEASED);
      return found;
    }
  }
  return false;
}

void Keyboard::DisplayInput() {


  d->fillRect(Col1, Row0, Col10 + (2 * 9), Size, inputt);
  d->setCursor(Col1 + 5, Row0 + 25);
  d->setFont(f);
  d->setTextColor(inputb, inputt);


  if (hasinittext) {
    d->print(inittext);
  } else {
    d->print(dn);
  }
}

void Keyboard::setCornerRadius(uint8_t Radius) {
  rad = Radius;
  if (Radius > 10) {
    rad = 10;
  }
}

void Keyboard::clearInput() {
  data[0] = '\0';
}

void Keyboard::getInput() {

  uint8_t np = 0;
  uint16_t b = 0, i = 0;
  CapsLock = false;
  bool SpecialChar = false;
  bool KeepIn = true;
  bool found = false;
  memset(dn, '\0', MAX_KEYBOARD_CHARS + 1);

  if (strlen(data) > 0) {
    strcpy(dn, data);
    np = strlen(dn);
  }

  BUTTON Buttons[74];

  BuildButton(&Buttons[0], Col1, Row1);      //,  "!");
  BuildButton(&Buttons[1], Col5, Row3);      //,  "''");
  BuildButton(&Buttons[2], Col3, Row1);      //,,  "#");
  BuildButton(&Buttons[3], Col4, Row1);      //,,  "$");
  BuildButton(&Buttons[4], Col5, Row1);      //,,  "%");
  BuildButton(&Buttons[5], Col7, Row1);      //,,  "&");
  BuildButton(&Buttons[6], Col6, Row3);      //,,  "'");
  BuildButton(&Buttons[7], Col9, Row1);      //,,  "(");
  BuildButton(&Buttons[8], Col10, Row1);     //,,  ")");
  BuildButton(&Buttons[9], Col8, Row1);      //,,  "*");
  BuildButton(&Buttons[10], Col6, Row2);     //,,  "+");
  BuildButton(&Buttons[11], Col7, Row3);     //,,  ",");
  BuildButton(&Buttons[12], Col3, Row2);     //,,  "-");
  BuildButton(&Buttons[13], Col8, Row3);     //,,  ".");
  BuildButton(&Buttons[14], Col5, Row4);     //,,  "/");
  BuildButton(&Buttons[15], Col1, Row1);     //,, "0");
  BuildButton(&Buttons[16], Col2, Row1);     //,, "1");
  BuildButton(&Buttons[17], Col3, Row1);     //,,  "2");
  BuildButton(&Buttons[18], Col4, Row1);     //,,  "3");
  BuildButton(&Buttons[19], Col5, Row1);     //,,  "4");
  BuildButton(&Buttons[20], Col6, Row1);     //,,  "5");
  BuildButton(&Buttons[21], Col7, Row1);     //,,  "6");
  BuildButton(&Buttons[22], Col8, Row1);     //,,  "7");
  BuildButton(&Buttons[23], Col9, Row1);     //,,  "8");
  BuildButton(&Buttons[24], Col10, Row1);    //,,  "9");
  BuildButton(&Buttons[25], Col3, Row3);     //,,  ":");
  BuildButton(&Buttons[26], Col4, Row3);     //,,  ";");
  BuildButton(&Buttons[27], Col9, Row3);     //,,  "<");
  BuildButton(&Buttons[28], Col5, Row2);     //,,  "=");
  BuildButton(&Buttons[29], Col10, Row3);    //,,  ">");
  BuildButton(&Buttons[30], Col6, Row4);     //,,  "?");
  BuildButton(&Buttons[31], Col2, Row1);     //,,  "@");
  BuildButton(&Buttons[32], Col1, Row3);     //,,  "A");
  BuildButton(&Buttons[33], Col6, Row4);     //,,  "B");
  BuildButton(&Buttons[34], Col4, Row4);     //,,  "C");
  BuildButton(&Buttons[35], Col3, Row3);     //,,  "D");
  BuildButton(&Buttons[36], Col3, Row2);     //,,  "E");
  BuildButton(&Buttons[37], Col4, Row3);     //,,  "F");
  BuildButton(&Buttons[38], Col5, Row3);     //,,  "G");
  BuildButton(&Buttons[39], Col6, Row3);     //,,  "H");
  BuildButton(&Buttons[40], Col8, Row2);     //,,  "I");
  BuildButton(&Buttons[41], Col7, Row3);     //,,  "J");
  BuildButton(&Buttons[42], Col8, Row3);     //,,  "K");
  BuildButton(&Buttons[43], Col9, Row3);     //,,  "L");
  BuildButton(&Buttons[44], Col8, Row4);     //,,  "M");
  BuildButton(&Buttons[45], Col7, Row4);     //,,  "N");
  BuildButton(&Buttons[46], Col9, Row2);     //,,  "O");
  BuildButton(&Buttons[47], Col10, Row2);    //,,  "P");
  BuildButton(&Buttons[48], Col1, Row2);     //,,  "Q");
  BuildButton(&Buttons[49], Col4, Row2);     //,,  "R");
  BuildButton(&Buttons[50], Col2, Row3);     //,,  "S");
  BuildButton(&Buttons[51], Col5, Row2);     //,,  "T");
  BuildButton(&Buttons[52], Col7, Row2);     //,,  "U");
  BuildButton(&Buttons[53], Col5, Row4);     //,,  "V");
  BuildButton(&Buttons[54], Col2, Row2);     //,,  "W");
  BuildButton(&Buttons[55], Col3, Row4);     //,,  "X");
  BuildButton(&Buttons[56], Col6, Row2);     //,,  "Y");
  BuildButton(&Buttons[57], Col2, Row4);     //,,  "Z");
  BuildButton(&Buttons[58], Col7, Row2);     //,,  "[");
  BuildButton(&Buttons[59], Col1, Row3);     //,,  "\\");
  BuildButton(&Buttons[60], Col8, Row2);     //,,  "]");
  BuildButton(&Buttons[61], Col6, Row1);     //,,  "^");
  BuildButton(&Buttons[62], Col4, Row2);     //,,  "_");
  BuildButton(&Buttons[63], Col1, Row2);     //,,  "`");
  BuildButton(&Buttons[64], Col9, Row2);     //,,  "{");
  BuildButton(&Buttons[65], Col2, Row3);     //,,  "|");
  BuildButton(&Buttons[66], Col10, Row2);    //,,  "}");
  BuildButton(&Buttons[67], Col2, Row2);     //,,  "~");
  BuildButton(&Buttons[68], Col4, Row5, 4);  //,, 3, "Space");
  BuildButton(&Buttons[69], Col1, Row6, 3);  //,, 3, "Done");
  BuildButton(&Buttons[70], Col4, Row6, 4);  //,, 3, "Cancel");
  BuildButton(&Buttons[71], Col8, Row6, 3);  //,, 3, "Back");
  BuildButton(&Buttons[72], Col1, Row5, 3);  //,, 3, "Caps");
  BuildButton(&Buttons[73], Col8, Row5, 3);  //,, 3, "$%");

  DisplayInput();

  // draw numbers
  for (i = 15; i < 25; i++) {
    DrawButton(&Buttons[i], i + 33, BUTTON_RELEASED);
  }

  if (CapsLock) {
    // A-Z
    for (i = 32; i < 58; i++) {
      DrawButton(&Buttons[i], i + 33, BUTTON_RELEASED);
    }
  } else {
    // a-z
    for (i = 32; i < 58; i++) {
      DrawButton(&Buttons[i], i + 33 + 32, BUTTON_RELEASED);
    }
  }

  for (i = 68; i < 74; i++) {
    DrawButton(&Buttons[i], i + 100, BUTTON_RELEASED);
  }

  while (KeepIn) {

    if (t->touched()) {

      ProcessTouch();
      //go thru all the KeyboardBtn, checking if they were pressed


      if (SpecialChar) {
        found = false;
        for (b = 0; b < 15; b++) {
          if (Pressed(&Buttons[b], b + 33)) {
            dn[np++] = (char)(b + 33);
            DisplayInput();
            found = true;
            break;
          }
        }
        for (b = 25; b < 32; b++) {
          if (Pressed(&Buttons[b], b + 33) && !found) {
            dn[np++] = (char)(b + 33);
            DisplayInput();
            found = true;
            break;
          }
        }
        for (b = 58; b < 66; b++) {
          if (Pressed(&Buttons[b], b + 33) && !found) {
            dn[np++] = (char)(b + 33);
            DisplayInput();
            found = true;
            break;
          }
        }
        for (b = 58; b < 64; b++) {
          if (Pressed(&Buttons[b], b + 33) && !found) {
            dn[np++] = (char)(b + 33);
            DisplayInput();
            found = true;
            break;
          }
        }
        for (b = 64; b < 68; b++) {
          if (Pressed(&Buttons[b], b + 33 + 26) && !found) {
            dn[np++] = (char)(b + 33 + 26);
            DisplayInput();
            found = true;
            break;
          }
        }
      } else {
        found = false;
        // check numbers
        for (b = 15; b < 25; b++) {
          if (Pressed(&Buttons[b], b + 33) && !found) {
            dn[np++] = (char)(b + 33);
            DisplayInput();
            found = true;
            break;
          }
        }
        // check letters
        for (b = 32; b < 58; b++) {
          if (CapsLock) {
            if (Pressed(&Buttons[b], b + 33) && !found) {
              dn[np++] = (char)(b + 33);
              DisplayInput();
              found = true;
              break;
            }
          } else {
            if (Pressed(&Buttons[b], b + 33 + 32) && !found) {
              dn[np++] = (char)(b + 33 + 32);
              DisplayInput();
              found = true;
              break;
            }
          }
        }
      }

      for (b = 68; b < 74; b++) {
        if (Pressed(&Buttons[b], b + 100)) {
          break;
        }
      }

      // caps lock
      if (b == 72) {
        CapsLock = !CapsLock;
        SpecialChar = false;
        SpecialChar = false;
        for (i = 15; i < 25; i++) {
          DrawButton(&Buttons[i], i + 33, BUTTON_RELEASED);
        }
        if (CapsLock) {
          for (i = 32; i < 58; i++) {
            DrawButton(&Buttons[i], i + 33, BUTTON_RELEASED);
          }
        } else {
          for (i = 32; i < 58; i++) {
            DrawButton(&Buttons[i], i + 33 + 32, BUTTON_RELEASED);
          }
        }
      }
      // special characters
      if (b == 73) {
        SpecialChar = !SpecialChar;
        d->fillRect(Col1, Row1, Col10 + Size, 4 * (Size + 2), kcolor);
        if (SpecialChar) {
          for (i = 0; i < 15; i++) {
            DrawButton(&Buttons[i], i + 33, BUTTON_RELEASED);
          }
          for (i = 25; i < 32; i++) {
            DrawButton(&Buttons[i], i + 33, BUTTON_RELEASED);
          }
          for (i = 58; i < 66; i++) {
            DrawButton(&Buttons[i], i + 33, BUTTON_RELEASED);
          }
          for (i = 58; i < 64; i++) {
            DrawButton(&Buttons[i], i + 33, BUTTON_RELEASED);
          }
          for (i = 64; i < 68; i++) {
            DrawButton(&Buttons[i], i + 33 + 26, BUTTON_RELEASED);
          }
        } else {
          for (i = 15; i < 25; i++) {
            DrawButton(&Buttons[i], i + 33, BUTTON_RELEASED);
          }
          if (CapsLock) {
            for (i = 32; i < 58; i++) {
              DrawButton(&Buttons[i], i + 33, BUTTON_RELEASED);
            }
          } else {
            for (i = 32; i < 58; i++) {
              DrawButton(&Buttons[i], i + 33 + 32, BUTTON_RELEASED);
            }
          }
        }
      }


      if (b == 68) {
        // space
        dn[np] = ' ';
        np++;
        DisplayInput();
        break;
      }
      if (b == 71) {
        // back space
        if (np > 0) {
          --np;
          dn[np] = ' ';
        }
        DisplayInput();
      }
      if (b == 69) {
        // done
        dn[np] = '\0';
        strcpy(data, dn);
        KeepIn = false;
        break;
      }
      if (b == 70) {
        // cancel, just get the heck out
        KeepIn = false;
        break;
      }

      delay(10);
    }
  }
}

void Keyboard::setInitialText(const char *Text) {

  uint8_t i;

  for (i = 0; i < (MAX_KEYBOARD_CHARS); i++) {
    inittext[i] = Text[i];
  }
  hasinittext = true;
}


void Keyboard::ProcessTouch() {

  if (t->touched()) {
    p = t->getPoint();
    BtnX = p.x;
    BtnY = p.y;

#ifdef debug
    Serial.print("real coordinates:");
    Serial.print(BtnX);
    Serial.print(" ,");
    Serial.println(BtnY);
#endif

    // different displays may require reversing last 2 args
    BtnX = map(BtnX, screenX0, screenX320, 320, 0);
    BtnY = map(BtnY, screenY0, screenY240, 240, 0);
//d->fillCircle(BtnX, BtnY, 1, ILI9341_RED);
#ifdef debug
    Serial.print(" , Mapped coordinates:");
    Serial.print(BtnX);
    Serial.print(" ,");
    Serial.println(BtnY);

#endif
  }
}

