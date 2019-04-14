#include "Ledz.h"

//test
#define NUM_LEDS 10
#define LED_PIN 7

//prod
#define UPPER_LEDS 144
#define LOWER_LEDS 120
#define UPPER_PIN 8
#define LOWER_PIN 9

#define B_BUTTON_PIN 2
#define C_BUTTON_PIN 3
#define M_BUTTON_PIN 4

Button b_button = Button(B_BUTTON_PIN);
Button c_button = Button(C_BUTTON_PIN);
Button m_button = Button(M_BUTTON_PIN);

Ledz test;
Ledz upper;
Ledz lower;

int brightness = 0;
#define maxBrightness 5

int colorMode = 0;
#define maxColorMode 3

int mode = 0;
#define whiteMax 4
#define colorMax 20
#define multiMax 10

bool updateMode = true;
bool perFrame = false;

void setup() { 
  //setup leds
  Serial.begin(9600);
  test.setup<LED_PIN>(NUM_LEDS);
  test.setBrightness(brightness);
  upper.setup<UPPER_PIN>(UPPER_LEDS);
  lower.setup<LOWER_PIN>(LOWER_LEDS);
}

void loop() {
  //check for brightness change
  if(b_button.check()){
    brightness++;
    brightness %= maxBrightness;
    test.setBrightness(brightness);  
    return;
  }
  //check for color mode change
  if(c_button.check()){
    Serial.println(colorMode);
    colorMode++;
    colorMode %= maxColorMode;
    mode = 0;
    updateMode = true;
    return;
  }
  //check for mode change
  if(m_button.check()){
    mode++;
    switch(colorMode){
      case 0:
        mode %= whiteMax;
        break;
      case 1:
        mode %= colorMax;
        break;
      case 2:
        mode %= multiMax;
        break;
    }
    updateMode = true;
    test.resetCounter();
    return;
  }
  if(updateMode){
    updateMode = false;
    UpdateMode();
    return;
  }
  if(perFrame){
    UpdateMode();
  }
}

void White(){
  switch(mode){
    case 0:
      test.solidWhite();
      break;
  }
}

void Color(){
  test.solidColor(mode);
}

void Multi(){
  switch(mode){
    case 0:
      perFrame = true;
      test.breathing(8);
      break;
    case 1:
      perFrame = true;
      test.breathing(2);
      break;
    case 2:
      perFrame = true;
      test.movingRainbow(0);
      break;
    case 3:
      perFrame = true;
      test.movingRainbow(4);
      break;
    case 4:
      perFrame = true;
      test.beams(true, 500);
      break;
    case 5:
      perFrame = true;
      test.beams(false, 200);
      break;
    case 6:
      perFrame = true;
      test.bars(true,3,10000);
      break;
    case 7:
      perFrame = true;
      test.bars(false,2,6000);
      break;
  } 
}

void UpdateMode(){
  switch(colorMode){
    case 0:
      White();
      break;
    case 1:
      Color();
      break;
    case 2:
      Multi();
      break;
  }
}
