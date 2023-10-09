# Numberpad for the Adafruit_ILI9341 and XPT2046_Touchscreen Libraries
This library includes a class for getting user input using a 0-9 digit. This library is for the Adafruit_ILI9341 driver to drive common 2.8" LCF displays, and also requires touch screen capability.  This library is dependent on 1) Adafruit_ILI9341, 2) XPT2046_Touchscreen, and 3) Adafruit_ILI9341_Controls libraries.

<b><h3> Latest version 3.0</b></h3>
<br>
<b><h3>Version History</b></h3>
<br>
  rev   date      author        change
  <br>
  1.0   2/12/2023      kasprzak      initial code
  <br>
  1.1   2/21/2023      kasprzak      fixed number overrun issue
  <br>
  2.0   3/14/2023      kasprzak      fixed fonts for MEGA
  <br>
  3.0   10/9/2023      kasprzak      fixed so it compiles on a
  <br>rduing 2.0, added setDecimalPlaces method for controlling float digits
<br>
<b><h3>Note: if you are currently using Adafruit_ILI9341_Controls library, make sure you get the latest Adafruit_ILI9341_Controls version 6.0</b></h3>
<br>
<br>
<b>The keypad library MAY work with an Arduino UNO, NANO, and the MEGA. The full keyboard is not supported with any Arduino MCU. The best I can determine is either memory issue or 8-bit architecture</b>
<br>
<br>
![header image](https://raw.github.com/KrisKasprzak/Adafruit_ILI9341_Keypad/master/Images/09.jpg)
<br>
<br>
Watch this YouTube Video for a demonstration:
https://youtu.be/PrSxA_QEzuk
<br>
<br>
<b><h3>Library highlights</b></h3>
1. Simple to implement library
2. The number pad can be configured for both colors and button sizes
3. This class can allow hidden character input for password entry
4. This class can allow initial instruction text in the input field
5. This class can allow a predefined input 
6. The number input can handle decimal and negative number inputs and can enable or disabled
7. The library handles button presses, hence why you pass in the Touch object

<b><h3>General implementation</b></h3>
<br>
1. include the library
<br>
#include "Adafruit_ILI9341.h"  
<br>
#include "font_Arial.h" 
<br>
#include "Adafruit_ILI9341_Controls.h"
<br>
#include "Adafruit_ILI9341_Keypad.h"
<br>
#include "XPT2046_Touchscreen.h"
<br>
<br>
2. create a display object
<br>
3. create a touch object
<br>
4. create the keyboard and / or numberpad object
<br>
NumberPad MyNumberPad(&Display, &Touch);
<br>
<br>
5. In setup, initialize the objects, and optionally specify any options
<br>
MyNumberPad.init(ILI9341_BLACK, ILI9341_WHITE, ILI9341_BLUE, ILI9341_NAVY, ILI9341_WHITE, ILI9341_CYAN, ILI9341_YELLOW, FONT_BUTTON);
<br>
  // MyNumberPad.enableDecimal(bool State); // disable / enable decimal point (enabled by default)
  <br>
  // MyNumberPad.enableNegative(bool State); // disable / enable negative sign (enabled by default)
  <br>
  // MyNumberPad.setMinMax(float MininumValue, float MaximumValue); // want bound checks?
  <br>
  // use the value property to set the initial value if desired
  <br>
  // MyNumberPad.value = 3.14159;
  <br>
  <br>

6. When ready get user input
<br>
MyNumberPad.getInput(); // this will display the key pad control
<br>
or
<br>
7. Once the user completes input, read the results
<br>
Serial.println(MyNumberPad.value);
<br>
note that the data type is a float so you will need to recast if an int is desired
<br>
Serial.println((int) MyNumberPad.value);
<br>
or
<br>
Serial.println(MyKeyboard.data);
<br>
the data property is a char
<br>
<br>
<b><h3>Caution</b></h3>
<br>
If your touch screen is not being mapped to where you pressed you will probably need to adjust the screen mapping in the .cpp file. This mapping is used to account for touch difference in displays. There is a mapping function for both classes. Once you tweak one, the same map can be used for the other.
<br>
<br>
BtnX = map(p.x, 3975, 169, 0, 320);
<br>
BtnY = map(p.y, 3850, 304, 0, 240);    
<br>
<b><h3>Example Screenshots</b></h3>
<br>
<br>

![header image](https://raw.github.com/KrisKasprzak/Adafruit_ILI9341_Keypad/master/Images/01.jpg)
<br>
![header image](https://raw.github.com/KrisKasprzak/Adafruit_ILI9341_Keypad/master/Images/03.jpg)
![header image](https://raw.github.com/KrisKasprzak/Adafruit_ILI9341_Keypad/master/Images/05.jpg)
![header image](https://raw.github.com/KrisKasprzak/Adafruit_ILI9341_Keypad/master/Images/07.jpg)
![header image](https://raw.github.com/KrisKasprzak/Adafruit_ILI9341_Keypad/master/Images/08.jpg)
![header image](https://raw.github.com/KrisKasprzak/Adafruit_ILI9341_Keypad/master/Images/09.jpg)
![header image](https://raw.github.com/KrisKasprzak/Adafruit_ILI9341_Keypad/master/Images/12.jpg)
![header image](https://raw.github.com/KrisKasprzak/Adafruit_ILI9341_Keypad/master/Images/14.jpg)
![header image](https://raw.github.com/KrisKasprzak/Adafruit_ILI9341_Keypad/master/Images/16.jpg)
<br>
![header image](https://raw.github.com/KrisKasprzak/Adafruit_ILI9341_Keypad/master/Images/18.jpg)
![header image](https://raw.github.com/KrisKasprzak/Adafruit_ILI9341_Keypad/master/Images/20.jpg)
![header image](https://raw.github.com/KrisKasprzak/Adafruit_ILI9341_Keypad/master/Images/23.jpg)
![header image](https://raw.github.com/KrisKasprzak/Adafruit_ILI9341_Keypad/master/Images/25.jpg)
![header image](https://raw.github.com/KrisKasprzak/Adafruit_ILI9341_Keypad/master/Images/27.jpg)



