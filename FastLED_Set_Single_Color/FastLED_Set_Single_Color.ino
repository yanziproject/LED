/*
   This example demonstrate many ways to set color
   In general there are two modes: RGB and HSV
   RGB: Remember to set the COLOR_ORDER in "GRB" for WS2812B for its special color order,
        we can set the color in RGB order in the code as normal.
        The RGB algorithm in FastLED has its limitations. If the light is too bright,
        we cannot get the proper color but a very light color instand.
        Defferent types of LED many use defferent color order, just need to change the setting.

   HSV: The HSV algorithm in FastLED also has its limitations. With the decreacing of the saturation
        and value, the hue moves.

   How to set color:     https://github.com/FastLED/FastLED/wiki/Controlling-leds
   Color reference link: https://github.com/FastLED/FastLED/wiki/Pixel-reference
*/

//=============== FastLED ================

#include <FastLED.h>
#define NUM_LEDS 1       // How many leds in your strip?
#define DATA_PIN 3       // data line for WS2812 led chips
#define BRIGHTNESS  64   // the brightness of all strip(s), cannot set brightness separately?
#define LED_TYPE WS2811
#define COLOR_ORDER GRB
CRGB leds[NUM_LEDS];  // Define the array of leds
CRGB color;

void setup() {

  //============== FastLED ===============
  FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS);  // GRB ordering is typical

  Serial.begin(9600);
  while (!Serial);

}

void loop() {
  // Turn the LED on, then pause
  leds[0] = CRGB::Red;
  FastLED.show();
  delay(500);
  // Now turn the LED off, then pause
  leds[0] = CRGB::Black;
  FastLED.show();
  delay(500);
  //setRGB_classicWay();
  //setRGB_hexColorCode();
  //setRGB_HTMLColorCode();
  //setRGB_setColorFunction();
  //setRGB_fromAnother();
  //setRGB_fill_solid();
  //setHSV_spectrumWay();
  //setHSV_directly();
  //setHSV_setColorFunction();
  //setHSV_pureHueColor();
  //setHSV_setColorFunction();
  //setHSV_fill_solid();
  //setHSV_rainbowColor();
  FastLED.show();
  delay(500);
  
}

CRGB getcolor() {
  CRGB color = leds[0];
  return color;
}

//============= Set RGB Color ===============
void setRGB_classicWay() {
  leds[0].r = 255;
  leds[0].g = 68;
  leds[0].b = 221;
}

void setRGB_hexColorCode() {
  leds[0] = 0xFF44DD;
}

void setRGB_HTMLColorCode() {
  // Reference link: https://github.com/FastLED/FastLED/wiki/Pixel-reference
  leds[0] = CRGB::HotPink;
}

void setRGB_setColorFunction() {
  leds[0].setRGB(255, 68, 221);
}

void setRGB_fromAnother() {
  leds[0] = leds[0];
  //leds[i] = leds[j];
}

void setRGB_fill_solid() {
  fill_solid( &(leds[0]), 1 /*number of leds*/, CRGB( 255, 68, 221) );
}

//============= Set HSV Color ===============
// The library provides fast, efficient methods
// for converting a CHSV color into a CRGB color.
// Many of these are automatic and require no explicit code.
// HSV reference link: https://github.com/FastLED/FastLED/wiki/Pixel-reference

void setHSV_spectrumWay() {
  CHSV spectrumcolor;
  spectrumcolor.hue = 222;
  spectrumcolor.saturation = 187;
  spectrumcolor.value = 255;
  hsv2rgb_spectrum(spectrumcolor, leds[0]);
}

void setHSV_directly() {
  // Simplest, preferred way: assignment from a CHSV color
  // Set color from Hue, Saturation, and Value.
  // Conversion to RGB is automatic.
  leds[0] = CHSV(224, 187, 255);
}

void setHSV_pureHueColor() {
  // Setting to a pure, bright, fully-saturated rainbow hue
  leds[0].setHue(224);
}

void setHSV_setColorFunction() {
  leds[0].setHSV(224, 187, 255);
}

void setHSV_fill_solid() {
  fill_solid(&(leds[0]), 1 /*number of leds*/, CHSV( 224, 187, 255));
}

void setHSV_rainbowColor() {
  fill_rainbow( &(leds[0]), 1 /*led count*/, 222 /*starting hue*/);
}
