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
  inputt = BackColor;
  inputb = TextColor;
  value = 0.0;
  bfont = ButtonFont;
  
  // in this class we are NOT initially writing to the char[0] as it's reserved for the - sign
  // hence we need to populate it to eliminate null terminator


}

 char *NumberPad::getCharValue(){
	
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

uint8_t NumberPad::get_float_digits(float num)
{
    int digits=0;
    float ori=num;//storing original number
    long num2=num;
    while(num2>0)//count no of digits before floating point
    {
        digits++;
        num2=num2/10;
    }
    if(ori==0)
        digits=1;
    num=ori;
    float  no_float;
    no_float=ori*(pow(10, (8-digits)));
    long long int total=(long long int)no_float;
    int no_of_digits, extrazeroes=0;
    for(int i=0; i<8; i++)
    {
        int dig;
        dig=total%10;
        total=total/10;
        if(dig!=0)
            break;
        else
            extrazeroes++;
    }
    no_of_digits=8-extrazeroes;
	if ( ((long) num) != num){
		// has decimal
		//no_of_digits++;
	}
    return no_of_digits;
}

void NumberPad::getInput() {

	uint16_t KW = (3 * BW) + (5 * BS) + OKBW;
	uint16_t KH = (4 * BH) + (6 * BS) + TBH;
	uint16_t i = 0;
	uint16_t b = 0;
	bool hasDP = false;
	uint8_t np = 1;              // digit number
	bool CanBackUp = false;
	bool hasneg = false;
	bool KeepIn = true;
	float TheNumber = 0.0;
  
  if (hideinput){
	  value = 0;
  }
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
		else {
			value = value * -1.0;
		}
		
		gcvt(value,7,dn);
				
		if (!hasneg){
			value = value * -1.0;
			dn[0] =  ' ';
		}
	  
		np = strlen(dn); // account for possible sign
	}
	
	//  https://javl.github.io/image2cpp/

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
  d->fillRect(CW - (KW / 2), CH - KH / 2, KW, KH, kcolor);

  // text input box
  d->fillRect(CW - (KW / 2) + BS, CH - KH / 2 + BS, 2 * BS + 3 * BW, TBH, inputb);
  d->setCursor(CW - (KW / 2) + BS + 5, CH - KH / 2 + BS + 22);
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
		d->setCursor(CW - (KW / 2) + BS + 5, CH - KH / 2 + BS + 22);
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
  
	// if no negative / shift chars
	if(!negstate) {

		for (i = 1 ; i < MAX_KEYBOARD_CHARS; i++){
			dn[i-1] = dn[i];
		}	
		dn[i] = '\0';
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
    
}
void Keyboard::setDisplayColor(uint16_t TextColor, uint16_t BackColor) {
  inputt = TextColor;
  inputb = BackColor;
}

void Keyboard::BuildButton(BUTTON *temp, int Col, int Row){
	temp->x = Col;
	temp->y = Row;	
	temp->w = 1;	
}

void Keyboard::BuildButton(BUTTON *temp, int Col, int Row, uint8_t Wide){
	temp->x = Col;
	temp->y = Row;	
	temp->w = Wide;	
}

void Keyboard::DrawButton(BUTTON *temp, uint8_t ASCII, uint8_t State){
	
	
	if (State == B_PRESSED){
		d->fillRect(temp->x, temp->y, Size + ((temp->w - 1) * (2 + Size)), Size, pbcolor);
		d->setTextColor(ptcolor, bcolor);
	} 
	else {
		d->fillRect(temp->x, temp->y, Size + ((temp->w - 1) * (2 + Size)), Size, bcolor);
		d->setTextColor(tcolor, bcolor);
	}
	d->setCursor(temp->x + 7, temp->y+21);
	d->setFont(f);
		
	if (ASCII == 168){
		d->print("Space");
	}
	else if (ASCII == 169){
		d->print("Done");
	}
	else if (ASCII == 170){
		d->print("Cancel");
	}
	else if (ASCII == 171){
		d->print("Back");
	}
	else if (ASCII == 172){
		d->print("Aa");
	}
	else if (ASCII == 173){
		d->print("#$%^");
	}
	else {
		d->print((char) ASCII);
	}
}

bool Keyboard::Pressed(BUTTON *temp, uint8_t ASCII){
	bool found = false;
	bool redraw = true;
	bool redrawoff = false;
	
	if ((BtnX > temp->x) && (BtnX < (temp->x + (Size * temp->w)))){
		if ((BtnY > temp->y) && (BtnY < (temp->y + Size))){
		
			while (t->touched()) {
				if (((BtnX > temp->x) && (BtnX < (temp->x + (Size * temp->w)))) && ((BtnY > temp->y) && (BtnY < (temp->y + Size)))){
					if (redraw){
						DrawButton(temp, ASCII, B_PRESSED);
						redraw = false;
						redrawoff = true;
					}
					found = true;
				} 
				else {
					if (redrawoff){
						DrawButton(temp, ASCII, B_RELEASED);
						redrawoff = false;
					}
					found = false;
					redraw = true;
				}
			
				ProcessTouch();
			}

			DrawButton(temp, ASCII, B_RELEASED);
			return found;
		}
	}
	return false;
		
}

void Keyboard::DisplayInput(){
	
	
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

  d->fillScreen(kcolor);



	DisplayInput();


  // draw numbers
  for (i = 15; i < 25; i++) {
    DrawButton(&Buttons[i], i + 33, B_RELEASED);
  }

  if (CapsLock) {
    // A-Z
    for (i = 32; i < 58; i++) {
      DrawButton(&Buttons[i], i + 33, B_RELEASED);
    }
  } else {
    // a-z
    for (i = 32; i < 58; i++) {
      DrawButton(&Buttons[i], i + 33 + 32, B_RELEASED);
    }
  }

  for (i = 68; i < 74; i++) {
    DrawButton(&Buttons[i], i + 100, B_RELEASED);
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
			if (Pressed(&Buttons[b],b + 33)&& !found) {
				dn[np++] = (char)(b + 33);
				DisplayInput();
				found = true;
				break;
			}
        }
        for (b = 58; b < 64; b++) {
			if (Pressed(&Buttons[b],b + 33)&& !found) {
				dn[np++] = (char)(b + 33);
				DisplayInput();
				found = true;
				break;
			}
        }
        for (b = 64; b < 68; b++) {
			if (Pressed(&Buttons[b],b + 33+26)&& !found) {
				dn[np++] = (char)(b + 33+26);
				DisplayInput();
				found = true;
				break;
			}
        }
      } else {
			found = false;
		  // check numbers
		  for (b = 15; b < 25; b++) {
			if (Pressed(&Buttons[b], b + 33)&& !found) {
				dn[np++] = (char)(b + 33);
				DisplayInput();
				found = true;
				break;
			}
		  }
		// check letters
        for (b = 32; b < 58; b++) {
			if (CapsLock) {
				if (Pressed(&Buttons[b], b + 33)&& !found) {
					dn[np++] = (char)(b + 33);
					DisplayInput();
					found = true;
					break;
				}
            } else {
				if (Pressed(&Buttons[b], b + 33+32)&& !found) {
					dn[np++] = (char)(b + 33+32);
					DisplayInput();
					found = true;
					break; 
				}
          }
        }
      }

      for (b = 68; b < 74; b++) {
        if (Pressed(&Buttons[b], b+100)) {
          break;
        }
      }
      
      // caps lock
      if (b == 72) {
        CapsLock = !CapsLock;
		SpecialChar = false;
		  for (i = 15; i < 25; i++) {
			DrawButton(&Buttons[i], i + 33, B_RELEASED);
		}
        if (CapsLock) {
          for (i = 32; i < 58; i++) {
            DrawButton(&Buttons[i], i + 33, B_RELEASED);
          }
        } else {
          for (i = 32; i < 58; i++) {
            DrawButton(&Buttons[i], i + 33 + 32, B_RELEASED);
          }
        }
      }
      // special characters
      if (b == 73) {
        SpecialChar = !SpecialChar;
        d->fillRect(Col1, Row1, Col10 + Size, 4 * (Size + 2), kcolor);
        if (SpecialChar) {
          for (i = 0; i < 15; i++) {
            DrawButton(&Buttons[i], i + 33, B_RELEASED);
          }
          for (i = 25; i < 32; i++) {
            DrawButton(&Buttons[i], i + 33, B_RELEASED);
          }
          for (i = 58; i < 66; i++) {
            DrawButton(&Buttons[i], i + 33, B_RELEASED);
          }
          for (i = 58; i < 64; i++) {
            DrawButton(&Buttons[i], i + 33, B_RELEASED);
          }
          for (i = 64; i < 68; i++) {
            DrawButton(&Buttons[i], i + 33 + 26, B_RELEASED);
          }
        } else {
          for (i = 15; i < 25; i++) {
            DrawButton(&Buttons[i], i + 33, B_RELEASED);
          }
          if (CapsLock) {
            for (i = 32; i < 58; i++) {
              DrawButton(&Buttons[i], i + 33, B_RELEASED);
            }
          } else {
            for (i = 32; i < 58; i++) {
              DrawButton(&Buttons[i], i + 33 + 32, B_RELEASED);
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
	
      delay(100);
    }
  }
}
	
void Keyboard::setInitialText(const char *Text){
	
	uint8_t i;
	
	for (i = 0; i < (MAX_KEYBOARD_CHARS); i++){
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
     Serial.print(" real coordinates:");
     Serial.print(BtnX);
     Serial.print(" ,");
     Serial.print (BtnY);
#endif

    // different displays may require reversing last 2 args
    BtnX = map(p.x, 300, 3975, 0, 320);
    BtnY = map(p.y, 304, 3850, 0, 240);

#ifdef debug
     Serial.print(" , Mapped coordinates:");
     Serial.print(BtnX);
     Serial.print(" ,");
     Serial.println(BtnY);
    d->fillCircle(BtnX, BtnY, 1, ILI9341_RED);
#endif
  }
}

bool Keyboard::ProcessButtonPress(Button TheButton) {

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
