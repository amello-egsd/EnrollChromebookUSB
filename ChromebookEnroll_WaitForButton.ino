#include "TrinketKeyboard.h"

//https://github.com/adafruit/Adafruit-Trinket-USB/blob/master/TrinketKeyboard/TrinketKeyboard.h

int ledPin    = 1; //LED 
int buttonPIN = 2; //pin connected to GND with a switch

char escChar[ ] = "\\twrE"; // Characters for special control keys

// uncomment one of the char statements below
// test string
//char outputText[ ] = "start\\t\\x\\r\\Wait\\wait\\r\\Eusername@domain.org\\r\\wPaSs\\\\WoRd\\r\\w\\w\\t\\t\\t\\r\\w\\w\\wchrome://chrome\\rend";
// old OS version (37?)
//char outputText[ ] = "\\t\\t\\t\\r\\w\\w\\r\\w\\w\\E\\w\\wusername@domain.org\\tPaSsWoRd\\r\\w\\w\\w\\r\\t\\t\\t\\w\\wchrome://chrome\\r";
// newer OS (42+?)
char outputText[ ] = "\\t\\t\\t\\t\\r\\w\\w\\r\\w\\w\\w\\w\\w\\w\\E\\w\\tusername@domain.org\\r\\wPaSsWoRd\\r\\w\\w\\t\\t\\t\\r\\w\\wchrome://chrome\\r";

// the setup routine runs once when you press reset:
void setup() {
  
  pinMode(buttonPIN, INPUT_PULLUP);   // initialize button pin with pullup
  
  while (digitalRead(buttonPIN) == HIGH) {   // wait for button press
    for (int i = 0; i < 2 ; i++) {
      analogWrite(ledPin, 0);
      delay(50);
      analogWrite(ledPin, 150);
      delay(50);
    }
    delay(250);
  }
  
  analogWrite(ledPin, 250);
  
  TrinketKeyboard.begin();
}

// the loop routine runs over and over again forever:
void loop() {
  
  int loopCount = 0;
  while (loopCount < 300 ) { //wait 3 seconds for the computer to see the keyboard
    TrinketKeyboard.poll(); // this (or "press" something) must be called at least once every 10ms
    delay(10);
    loopCount++;
  }

  for (int i = 0; i < sizeof(outputText) - 1 ; i++) {
    if ( outputText[i] != escChar[0] ) {
      TrinketKeyboard.print(outputText[i]);
    } else if ( outputText[i + 1] == escChar[1] ) {
      // equals t
      TrinketKeyboard.pressKey(0, KEYCODE_TAB);
      TrinketKeyboard.pressKey(0, 0);
      i++;
    } else if ( outputText[i + 1] == escChar[2] ) {
      // equals w
      int loopCount = 0;
      while (loopCount < 500 ) { //wait 5 seconds 
        TrinketKeyboard.poll(); 
        analogWrite(ledPin, 0);
        delay(5);
        analogWrite(ledPin, 100);
        delay(5);
        loopCount++;
      }
      i++;
    } else if ( outputText[i + 1] == escChar[3] ) {
      // equals r
      TrinketKeyboard.pressKey(0, KEYCODE_ENTER);
      TrinketKeyboard.pressKey(0, 0);
      i++;
    } else if ( outputText[i + 1] == escChar[4] ) {
      // equals E
      TrinketKeyboard.pressKey(KEYCODE_MOD_LEFT_CONTROL+KEYCODE_MOD_LEFT_ALT,KEYCODE_E);
      TrinketKeyboard.pressKey(0, 0);
      i++;
    } else if ( outputText[i + 1] == escChar[0] ) {
      // equals \
      // the next line .pressKey(0, 0) should not be needed but it wasn't working without it
      TrinketKeyboard.pressKey(0, 0); 
      TrinketKeyboard.pressKey(0, KEYCODE_BACKSLASH);
      TrinketKeyboard.pressKey(0, 0);
      i++;
    }
  }

// fade the LED up and down when done
  while (true) {
    for (int fadeValue = 0 ; fadeValue <= 255; fadeValue += 5) {
      // sets the value (range from 0 to 255):
      analogWrite(ledPin, fadeValue);
      // wait for 30 milliseconds to see the dimming effect
      delay(20);
    }
    for (int fadeValue = 255 ; fadeValue >= 0; fadeValue -= 5) {
      // sets the value (range from 0 to 255):
      analogWrite(ledPin, fadeValue);
      // wait for 30 milliseconds to see the dimming effect
      delay(20);
    }
  }
  
}

