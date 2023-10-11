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

*/

#include "Adafruit_ILI9341_Keypad.h"
#include <Adafruit_ILI9341.h>
#include <Adafruit_ILI9341_Controls.h>  // button library
#include <XPT2046_Touchscreen.h>

  // https:javl.github.io image2cpp 
	    // 20 x 20
  // 'check', 40x40px
  const unsigned char check[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xff, 0x80, 0x00, 0x00, 0x0f, 0xff, 0xf0, 0x00, 0x00,
    0x3f, 0xff, 0xfc, 0x00, 0x00, 0x7e, 0x00, 0x7e, 0x00, 0x01, 0xf8, 0x00, 0x1f, 0x80, 0x03, 0xe0,
    0x00, 0x07, 0x00, 0x07, 0xc0, 0x00, 0x02, 0x38, 0x07, 0x80, 0x00, 0x00, 0x7c, 0x0f, 0x00, 0x00,
    0x00, 0xfc, 0x1e, 0x00, 0x00, 0x01, 0xfe, 0x1c, 0x00, 0x00, 0x03, 0xfc, 0x3c, 0x00, 0x00, 0x07,
    0xf8, 0x38, 0x00, 0x00, 0x0f, 0xf0, 0x38, 0x00, 0x00, 0x1f, 0xe0, 0x70, 0x10, 0x00, 0x3f, 0xc6,
    0x70, 0x38, 0x00, 0x7f, 0xce, 0x70, 0x7c, 0x00, 0xff, 0x8e, 0x70, 0xfe, 0x01, 0xff, 0x0e, 0x70,
    0xff, 0x01, 0xfe, 0x0e, 0x70, 0xff, 0x83, 0xfc, 0x0e, 0x70, 0x7f, 0xc7, 0xf8, 0x0e, 0x70, 0x7f,
    0xef, 0xf0, 0x0e, 0x70, 0x3f, 0xff, 0xf0, 0x0e, 0x70, 0x1f, 0xff, 0xe0, 0x0e, 0x78, 0x0f, 0xff,
    0xc0, 0x1c, 0x38, 0x07, 0xff, 0x80, 0x1c, 0x38, 0x03, 0xff, 0x80, 0x1c, 0x1c, 0x01, 0xff, 0x00,
    0x38, 0x1e, 0x00, 0xfe, 0x00, 0x78, 0x0e, 0x00, 0x7c, 0x00, 0x70, 0x0f, 0x00, 0x1c, 0x00, 0xf0,
    0x07, 0x80, 0x00, 0x01, 0xe0, 0x03, 0xe0, 0x00, 0x07, 0xc0, 0x01, 0xf0, 0x00, 0x0f, 0x80, 0x00,
    0xfe, 0x00, 0x7f, 0x00, 0x00, 0x3f, 0xff, 0xfc, 0x00, 0x00, 0x0f, 0xff, 0xf0, 0x00, 0x00, 0x03,
    0xff, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
  };
  
    // 'Arrow', 20x20px
  const unsigned char arrow[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x06,
    0x00, 0x00, 0x0e, 0x00, 0x00, 0x1e, 0x00, 0x00, 0x3f, 0xff, 0xf0, 0x7f, 0xff, 0xf0, 0x7f, 0xff,
    0xf0, 0x3f, 0xff, 0xf0, 0x1e, 0x00, 0x00, 0x0e, 0x00, 0x00, 0x06, 0x00, 0x00, 0x02, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
  };
  // 'x', 40x40px
  const unsigned char cancel[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xff, 0xc0, 0x00, 0x00, 0x0f, 0xff, 0xf0, 0x00, 0x00,
    0x3f, 0xff, 0xfc, 0x00, 0x00, 0xfe, 0x00, 0xff, 0x00, 0x01, 0xf8, 0x00, 0x1f, 0x80, 0x03, 0xe0,
    0x00, 0x07, 0xc0, 0x07, 0xc0, 0x00, 0x03, 0xe0, 0x0f, 0x80, 0x00, 0x01, 0xf0, 0x0f, 0x1c, 0x00,
    0x00, 0xf0, 0x1e, 0x3e, 0x00, 0x3c, 0x78, 0x1c, 0x7f, 0x00, 0x7e, 0x38, 0x3c, 0x7f, 0x00, 0xfe,
    0x3c, 0x38, 0x7f, 0x81, 0xfe, 0x1c, 0x78, 0x7f, 0xc3, 0xfe, 0x1c, 0x70, 0x3f, 0xef, 0xfc, 0x1e,
    0x70, 0x1f, 0xff, 0xf8, 0x0e, 0x70, 0x1f, 0xff, 0xe0, 0x0e, 0x70, 0x0f, 0xff, 0xc0, 0x0e, 0x70,
    0x07, 0xff, 0x80, 0x0e, 0x70, 0x03, 0xff, 0x00, 0x0e, 0x70, 0x03, 0xff, 0x00, 0x0e, 0x70, 0x07,
    0xff, 0x00, 0x0e, 0x70, 0x0f, 0xff, 0x80, 0x0e, 0x70, 0x0f, 0xff, 0xc0, 0x0e, 0x78, 0x1f, 0xff,
    0xe0, 0x1e, 0x38, 0x3f, 0xdf, 0xf0, 0x1c, 0x3c, 0x7f, 0x8f, 0xf8, 0x3c, 0x3c, 0xff, 0x07, 0xfc,
    0x38, 0x19, 0xfe, 0x03, 0xfc, 0x78, 0x0b, 0xfe, 0x01, 0xfc, 0xf0, 0x03, 0xfc, 0x00, 0xf9, 0xf0,
    0x07, 0xf8, 0x00, 0x73, 0xe0, 0x07, 0xf0, 0x00, 0x07, 0xc0, 0x03, 0xe0, 0x00, 0x1f, 0x80, 0x01,
    0xce, 0x00, 0x7f, 0x00, 0x00, 0x8f, 0xff, 0xfc, 0x00, 0x00, 0x1f, 0xff, 0xf8, 0x00, 0x00, 0x03,
    0xff, 0xc0, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00
  };
  

NumberPad::NumberPad(Adafruit_ILI9341 *Display, XPT2046_Touchscreen *Touch) {
  d = Display;
  t = Touch;
}


void NumberPad::init(uint16_t BackColor, uint16_t TextColor,
                  uint16_t ButtonColor, uint16_t BorderColor,
                  uint16_t PressedTextColor,
                  uint16_t PressedButtonColor, uint16_t PressedBorderColor,
                  const GFXfont *ButtonFont) {

  kcolor = BackColor;
  tcolor = TextColor;
  bcolor = ButtonColor;
  rcolor = BorderColor;
  ptextcolor = PressedTextColor;
  inputt = TextColor;
  inputb = ButtonColor;
  value = 0.0;
  bfont = ButtonFont;
  
  OKBH = (2 * BH) + BS;
  
  
  
  // in this class we are NOT initially writing to the char[0] as it's reserved for the - sign
  // hence we need to populate it to eliminate null terminator


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

void NumberPad::enableDecimal(bool State = true) {
  decstate = State;
}

void NumberPad::enableNegative(bool State = true) {
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

void NumberPad::setInitialText(const char *Text){
	
	uint8_t i;
	
	for (i = 0; i < (MAX_KEYBOARD_CHARS); i++){
		inittext[i] = Text[i];
	}
	hasinittext = true;
	
}

void NumberPad::hideInput(){
	
	hideinput = true;
}

void NumberPad::getInput() {

	uint16_t KW = (3 * BW) + (5 * BS) + OKBW;
	uint16_t KH = (4 * BH) + (6 * BS) + TBH;
	uint16_t i = 0;
	uint16_t b = 0;
	uint8_t digits = 0;
	bool hasDP = false;
	uint8_t np = 1;            
	bool CanBackUp = false;
	bool hasneg = false;
	bool KeepIn = true;
	float TheNumber = 0.0;
		
	memset(dn,'\0',MAX_KEYBOARD_CHARS+2);
	dn[0] = ' ';
	memset(hc,'\0',MAX_KEYBOARD_CHARS+2);
	hc[0] = ' ';

  	// get the decimals
	if (value != 0.0){

		// odd but force negative to get the place holder for the sign [0]
		if (value < 0) {
			hasneg = true;
			
		}
		
		// note value is a public property
		if (dp == 0){
			sprintf(dn,"% 0.f",value);
		}
		else if (dp == 1){
			sprintf(dn,"% 0.1f",value);
		}
		else if (dp == 2){
			sprintf(dn,"% 0.2f",value);
		}
		else if (dp == 3){
			sprintf(dn,"% 0.3f",value);
		}
		else if (dp == 4){
			sprintf(dn,"% 0.4f",value);
		}
		else if (dp == 5){
			sprintf(dn,"% 0.5f",value);
		}
		else if (dp == 6){
			sprintf(dn,"% 0.6f",value);
		}
		else if (dp == 7){
			sprintf(dn,"% 0.7f",value);
		}
		else {
			sprintf(dn,"% 0.2f",value);
		}
	  
		np = strlen(dn); // account for possible sign
	}
	
	Button NumberPadBtn[16]{
	  { d },
	  { d },
	  { d },
	  { d },
	  { d },
	  { d },
	  { d },
	  { d },
	  { d },
	  { d },
	  { d },
	  { d },
	  { d },
	  { d },
	  { d },
	  { d }

	};


  //7
  NumberPadBtn[7].init(CW - (KW / 2) + BS + (BW / 2), CH - KH / 2 + BS + BS + TBH + (BH / 2), BW, BH, rcolor, bcolor, tcolor, kcolor, "7", 0, 0, bfont);
  //8
  NumberPadBtn[8].init(CW - (KW / 2) + 2 * BS + BW + (BW / 2), CH - KH / 2 + BS + BS + TBH + (BH / 2), BW, BH, rcolor, bcolor, tcolor, kcolor, "8", 0, 0, bfont);
  //9
  NumberPadBtn[9].init(CW - (KW / 2) + 3 * BS + 2 * BW + (BW / 2), CH - KH / 2 + BS + BS + TBH + (BH / 2), BW, BH, rcolor, bcolor, tcolor, kcolor, "9", 0, 0, bfont);
  //4
  NumberPadBtn[4].init(CW - (KW / 2) + BS + (BW / 2), CH - KH / 2 + 3 * BS + TBH + BH + (BH / 2), BW, BH, rcolor, bcolor, tcolor, kcolor, "4", 0, 0, bfont);
  // 5
  NumberPadBtn[5].init(CW - (KW / 2) + 2 * BS + BW + (BW / 2), CH - KH / 2 + 3 * BS + TBH + BH + (BH / 2), BW, BH, rcolor, bcolor, tcolor, kcolor, "5", 0, 0, bfont);
  //6
  NumberPadBtn[6].init(CW - (KW / 2) + 3 * BS + 2 * BW + (BW / 2), CH - KH / 2 + 3 * BS + TBH + BH + (BH / 2), BW, BH, rcolor, bcolor, tcolor, kcolor, "6", 0, 0, bfont);
  // 1
  NumberPadBtn[1].init(CW - (KW / 2) + BS + (BW / 2), CH - KH / 2 + 4 * BS + TBH + 2 * BH + (BH / 2), BW, BH, rcolor, bcolor, tcolor, kcolor, "1", 0, 0, bfont);
  // 2
  NumberPadBtn[2].init(CW - (KW / 2) + 2 * BS + BW + (BW / 2), CH - KH / 2 + 4 * BS + TBH + 2 * BH + (BH / 2), BW, BH, rcolor, bcolor, tcolor, kcolor, "2", 0, 0, bfont);
  // 3
  NumberPadBtn[3].init(CW - (KW / 2) + 3 * BS + 2 * BW + (BW / 2), CH - KH / 2 + 4 * BS + TBH + 2 * BH + (BH / 2), BW, BH, rcolor, bcolor, tcolor, kcolor, "3", 0, 0, bfont);
  // -
  NumberPadBtn[10].init(CW - (KW / 2) + BS + (BW / 2), CH - KH / 2 + 5 * BS + TBH + 3 * BH + (BH / 2), BW, BH, rcolor, bcolor, tcolor, kcolor, "-", 0, 0, bfont);
  // 0
  NumberPadBtn[0].init(CW - (KW / 2) + 2 * BS + BW + (BW / 2), CH - KH / 2 + 5 * BS + TBH + 3 * BH + (BH / 2), BW, BH, rcolor, bcolor, tcolor, kcolor, "0", 0, 0, bfont);
  // .
  NumberPadBtn[11].init(CW - (KW / 2) + 3 * BS + 2 * BW + (BW / 2), CH - KH / 2 + 5 * BS + TBH + 3 * BH + (BH / 2), BW, BH, rcolor, bcolor, tcolor, kcolor, ".", 0, 0, bfont);
  // backspace
  NumberPadBtn[12].init(CW + (KW / 2) - BS - (OKBW / 2), CH - (KH / 2) + BS + (TBH / 2), OKBW, TBH, rcolor, bcolor, tcolor, kcolor, arrow, 20, 20, (OKBW - 20) / 2, (TBH - 20) / 5);
  
  // done
  NumberPadBtn[13].init(CW + (KW / 2) - BS - (OKBW / 2), CH - (KH / 2) + BS + TBH + BH + (2*BS) + (BS/2) + OKBH, OKBW, OKBH, rcolor, bcolor, ILI9341_GREEN, kcolor, check, 40, 40, (OKBW - 40) / 2, (OKBH - 40) / 2);  
  // cancel
  NumberPadBtn[14].init(CW + (KW / 2) - BS - (OKBW / 2),   CH - (KH / 2) + BS + TBH + BH + BS + (BS/2) , OKBW, OKBH, rcolor, bcolor, ILI9341_RED, kcolor, cancel, 40, 40, (OKBW - 40) / 2, (OKBH - 40) / 2);
 
 
 
  // large background box
  d->fillRect(CW - (KW / 2), CH - (KH / 2) - (BS/2), KW, KH, kcolor);

  // text input box
  d->fillRect(CW - (KW / 2) + BS, CH - KH / 2 + BS, 2 * BS + 3 * BW, TBH, inputb);
  d->setCursor(CW - (KW / 2) + BS + 5, CH - KH / 2 + BS + 18);
  d->setFont(bfont);
  d->setTextColor(inputt, inputb);
  
  if (hasinittext){
	d->print(inittext);
  }
    else {
	d->print(dn);
  }
  
  for (i = 0; i <= 14; i++) {
    NumberPadBtn[i].setCornerRadius(3);
  }
  NumberPadBtn[0].draw();
  NumberPadBtn[1].draw();
  NumberPadBtn[2].draw();
  NumberPadBtn[3].draw();
  NumberPadBtn[4].draw();
  NumberPadBtn[5].draw();
  NumberPadBtn[6].draw();
  NumberPadBtn[7].draw();
  NumberPadBtn[8].draw();
  NumberPadBtn[9].draw();
  if (negstate) { NumberPadBtn[10].draw(); }
  if (decstate) { NumberPadBtn[11].draw(); }
  NumberPadBtn[12].draw();
  NumberPadBtn[13].draw();
  NumberPadBtn[14].draw();

  while (KeepIn) {
	  
    if (t->touched()) {
		
      ProcessTouch();
      //go thru all the NumberPadBtn, checking if they were pressed
      for (b = 0; b <= 14; b++) {
		  	  
        if (ProcessButtonPress(NumberPadBtn[b])) {
		
          //valid number
          if ((b >= 0) & (b <= 9)) {
			  
			 Serial.println(np);
			  
            if (np > MAX_KEYBOARD_CHARS) { 
				Serial.println(340);
				break; 
			}
			if ((dn[1] == '0') && (dn[2] != '.')) {
				Serial.println(344);
				dn[1] = b + '0';
				hc[1] = '*';
			} else {
				Serial.println(348);
				dn[np] = b + '0';
				hc[np] = '*';
				np++;
			}
			CanBackUp = true;
          } else if (b == 10) {
            //negative number
            if (dn[0] == '-') {
              dn[0] = ' ';
            } else {
              dn[0] = '-';
            }
          } else if (b == 11) {
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
        if (minmaxstate) {
          TheNumber = atof(dn);
          // check min bounds
          if (TheNumber < minval) {
            // back out last entry
			if (CanBackUp){
				np--;
				dn[np] = ' ';
			}
          }
          // check max bounds
          if (TheNumber > maxval) {
            // back out last entry
            np--;
            dn[np] = ' ';
			
          }
        }
      }
		d->fillRect(CW - (KW / 2) + BS, CH - KH / 2 + BS, 2 * BS + 3 * BW, TBH, inputb);
		d->setCursor(CW - (KW / 2) + BS + 5, CH - KH / 2 + BS + 18);
		d->setFont(bfont);
		d->setTextColor(inputt, inputb);

		if (hideinput){
			d->print(hc);
		}
		else{
			d->print(dn);
		}
		
    }
  }
  

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
    BtnX = map(p.x, 169, 3975, 0, 320);
    BtnY = map(p.y, 304, 3850, 0, 240);
	
#ifdef debug 
	Serial.print(" , Mapped coordinates:");
    Serial.print(BtnX);
    Serial.print(" ,");
    Serial.println(BtnY);
    d->fillCircle(BtnX, BtnY,2, ILI9341_RED);
#endif
  }
}

void NumberPad::setDecimalPlaces(uint8_t Places) {
	dp = Places;

	if (dp > 7){
		dp = 7;
	}

}

bool NumberPad::ProcessButtonPress(Button TheButton) {
  if (TheButton.press(BtnX, BtnY)) {
    TheButton.draw(B_PRESSED);
    while (t->touched()) {
      if (TheButton.press(BtnX, BtnY)) {
	
        TheButton.draw(B_PRESSED);
      } else {
        TheButton.draw(B_RELEASED);
        return false;
      }
      ProcessTouch();
    }
    TheButton.draw(B_RELEASED);
    return true;
  }
  return false;
}


