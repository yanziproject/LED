//this code displays a cool water flow light strip
//this code is a basic test

#include <FastLED.h>

#define LED_PIN     0
#define NUM_LEDS    144
#define BRIGHTNESS  30
#define LED_TYPE    WS2812
#define COLOR_ORDER GRB
CRGB leds[NUM_LEDS];
CRGB fadeBlue;

#define UPDATES_PER_SECOND 100

CRGBPalette16 currentPalette;
TBlendType    currentBlending;   //http://fastled.io/docs/3.1/group___colorutils.html

void setup() {
  delay(3000); // power-up safety delay
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness(BRIGHTNESS);
  fadeBlue = CHSV( HUE_BLUE, 255, 5);
  currentBlending = LINEARBLEND;   //渐变的效果，不渐变用NOBLEND
  //http://fastled.io/docs/3.1/group___colorutils.html
}


void loop()
{
  //ChangePalettePeriodically();
  SetupWaterFlowPalette();
  static uint8_t startIndex = 0;
  if (millis() % 3 == 0) {
    startIndex = startIndex + 1; /* motion speed */
  }
  FillLEDsFromPaletteColors(startIndex);
  FastLED.show();
}

void FillLEDsFromPaletteColors( uint8_t colorIndex)
{
  uint8_t brightness = 255;
  for ( int i = 0; i < NUM_LEDS; ++i) {
    leds[i] = ColorFromPalette(currentPalette, colorIndex, brightness, currentBlending);
    colorIndex += 2;
  }
}

void ChangePalettePeriodically()
{
  uint8_t secondHand = (millis() / 1000) % 60;
  static uint8_t lastSecond = 99;
  //currentPalette = myRedWhiteBluePalette_p;
  currentBlending = LINEARBLEND;
}

// This function sets up a palette of water flow stripes.
void SetupWaterFlowPalette()
{
  CRGB fadeBlue0 = CHSV(140, 80, 50);
  CRGB fadeBlue1 = CHSV(139, 100, 100);
  CRGB fadeBlue2 = CHSV(138, 120, 150);
  CRGB fadeBlue3 = CHSV(137, 140, 200);
  CRGB black  = CRGB::Black;
  CRGB darkGray  = CRGB::DarkGray;
  CRGB gray  = CRGB::Gray;
  CRGB cornflowerBlue  = CRGB::CornflowerBlue;
  CRGB steelBlue  = CRGB::SteelBlue;
  currentPalette = CRGBPalette16(
                     darkGray,  gray,  darkGray,  cornflowerBlue,
                     cornflowerBlue, cornflowerBlue, steelBlue,  steelBlue,
                     steelBlue,  fadeBlue3,  fadeBlue2,  fadeBlue1,  fadeBlue0,
                     black, black, black );
}
