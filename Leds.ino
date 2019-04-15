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
    upper.setBrightness(brightness);
    lower.setBrightness(brightness);  
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
    upper.resetCounter();
    lower.resetCounter();
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
      upper.solidWhite();
      lower.solidWhite();
      test.solidWhite();
      break;
  }
}

void Color(){
  upper.solidColor(mode);
  lower.solidColor(mode);
  test.solidColor(mode);
}

void Multi(){
  perFrame = true;
  switch(mode){
    case 0:
      upper.breathing(8);
      lower.breathing(8);
      test.breathing(8);
      break;
    case 1:
      test.breathing(2);
      upper.breathing(2);
      lower.breathing(2);
      break;
    case 2:
      upper.movingRainbow(0);
      lower.movingRainbow(0);
      test.movingRainbow(0);
      break;
    case 3:
      upper.movingRainbow(4);
      lower.movingRainbow(4);
      test.movingRainbow(4);
      break;
    case 4:
      test.beams(true, 500);
      upper.beams(true, 500);
      lower.beams(true, 500);
      break;
    case 5:
      test.beams(false, 200);
      upper.beams(true, 500);
      lower.beams(false, 500);
      break;
    case 6:
      test.bars(true,3,10000);
      upper.bars(true, 10, 7000);
      lower.bars(true, 10, 7000);
      break;
    case 7:
      test.bars(false,2,6000);
      upper.bars(true, 10, 7000);
      lower.bars(false, 10, 7000);
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
