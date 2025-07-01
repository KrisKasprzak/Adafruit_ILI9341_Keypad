# Numberpad and Keyboard for the Adafruit_ILI9341 and XPT2046_Touchscreen Libraries
This library includes two classes 1) a class for getting user input using a 0-9 digit and 2) a full keyboard. This library is for the Adafruit_ILI9341 driver to drive common 2.8" LCD displays, and also requires touch screen capability.  This library is dependent on 1) Adafruit_ILI9341, 2) XPT2046_Touchscreen libraries.
<b><h3> Latest version 4.0</b></h3>
<br>
<b><h3>Version History</b></h3>
<br>
  rev   date      author        change
  <br>
  rev   date      author        change
   <br>
  1.0   2/12/2023      kasprzak      initial code
   <br>
   1.1   2/21/2023      kasprzak      fixed number overrun issue
    <br>
  2.0   3/14/2023      kasprzak      fixed fonts for MEGA
   <br>
  3.0   3/14/2024      kasprzak      complete rewrite to support ESP32
   <br>
  4.0   4/30/2024      kasprzak      added corner rounding added trailing zero removal
   <br>
  5.0   7/14/2024      kasprzak      added support for audible click when button pressed (requires hardward buzzer)
										added support to specify decimal places	
   <br>
  6.0   7/14/2024      kasprzak 	updated to work with Teensy 4.0 (removed PROGMEM)
<br>
<b>The keyboard library has been tested with Teensy 3.2, Teensy 4.0, ESP32. Not tested: Arduino's.</b>
Note: if you are using a Teensy, consider using ILI9341_t3 driver and ILI9341_t3_Keypad
<br>
<br>
Watch this YouTube Video for a demonstration:
https://youtu.be/PrSxA_QEzuk
<br>
<br>
<b><h3>Library highlights</b></h3>
<li>Simple to implement library</li>
<li>The number pad can be configured for inpput colors</li>
<li>This class can allow hidden character input for password entry</li>
<li>This class can allow initial instruction text in the input field</li>
<li>This class can allow a predefined input value</li>
<li>The number input can handle decimal and negative number inputs and can enable or disabled</li>
<li>The library handles button presses, hence why you pass in the Touch object</li>
<li>The library consumes approx. 16K memory</li>

<b><h3>General implementation</b></h3>
<br>
1. include the library
<br>
#include "Adafruit_ILI9341.h"  
<br>
#include "font_Arial.h" 
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
4. create the numberpad object
<br>
NumberPad MyNumberPad(&Display, &Touch);
<br>
<br>
5. In setup, initialize the object, and optionally specify any options
<br>
MyNumberPad.init(back color, button text color, button color, button pressed text color, button pressed color, & Adafruit_GFX font name);
<br>
MyNumberPad.setTouchLimits(ScreenLeft, ScreenRight, ScreenTop, ScreenBottom); // important to set the screen calibration values
<br>
 <br>
// optional methods
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

7. When ready get user input
<br>
MyNumberPad.getInput(); // this will display the key pad control
<br>
8. Once the user completes input (by pressing OK or Cancel, programmer can read the results
<br>
Serial.println(MyNumberPad.value);
<br>
note that the data type is a float so you will need to recast if an int is desired
<br>
Serial.println((int) MyNumberPad.value);
<br>
<br>
<b><h3>Caution</b></h3>
<br>
If your touch screen is not being mapped to where you pressed you will probably need to adjust the screen limits with the setTouchLimits method.
<br>
<b><h3>Example Screenshots (a bit outdated)</b></h3>
<br>
<br>

![header image](https://raw.github.com/KrisKasprzak/Adafruit_ILI9341_Keypad/master/Images/03.jpg)
![header image](https://raw.github.com/KrisKasprzak/Adafruit_ILI9341_Keypad/master/Images/05.jpg)
![header image](https://raw.github.com/KrisKasprzak/Adafruit_ILI9341_Keypad/master/Images/08.jpg)
![header image](https://raw.github.com/KrisKasprzak/Adafruit_ILI9341_Keypad/master/Images/09.jpg)
![header image](https://raw.github.com/KrisKasprzak/Adafruit_ILI9341_Keypad/master/Images/12.jpg)
![header image](https://raw.github.com/KrisKasprzak/Adafruit_ILI9341_Keypad/master/Images/14.jpg)
<br>
<br>
![header image](https://raw.github.com/KrisKasprzak/Adafruit_ILI9341_Keypad/master/Images/18.jpg)
![header image](https://raw.github.com/KrisKasprzak/Adafruit_ILI9341_Keypad/master/Images/20.jpg)
![header image](https://raw.github.com/KrisKasprzak/Adafruit_ILI9341_Keypad/master/Images/23.jpg)
![header image](https://raw.github.com/KrisKasprzak/Adafruit_ILI9341_Keypad/master/Images/23.jpg)
![header image](https://raw.github.com/KrisKasprzak/Adafruit_ILI9341_Keypad/master/Images/25.jpg)
![header image](https://raw.github.com/KrisKasprzak/Adafruit_ILI9341_Keypad/master/Images/27.jpg)



