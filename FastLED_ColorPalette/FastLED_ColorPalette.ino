/*
   This example shows several ways to set up
   and use 'palettes' of colors with FastLED.

   palette是FastLED当中非常省力的功能，灵活运用可以
   节省大量精力，轻松实现灯光的基础渐变效果的设置和实现。

   本例中注释比较多，因为为了弄清楚这个功能做了很多尝试，
   也删除了一些原示例的内容，力求精简。
    
   如果忘记了，可以搭配color setting的代码一起食用，
   内容涉及多种颜色的表达，适应了这种写法之后就不难了。
*/

//============== FastLED ===============

#include <FastLED.h>

#define LED_PIN     5
#define NUM_LEDS    50
#define BRIGHTNESS  1
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB
CRGB leds[NUM_LEDS];
CRGB leds0[1];

#define UPDATES_PER_SECOND 60   // running update speed

//=========== FastLED Palette ============
// 自己整理的注释，如果有一天忘了，就再看看吧，虽然长，但句句都是精华 ╮(￣▽￣"")╭
// There are basically two ways to set palette:

// 1. FastLED provides several 'preset' palettes:
//    RainbowColors_p, RainbowStripeColors_p, PartyColors_p,
//    OceanColors_p,   ForestColors_p.        LavaColors_p,   CloudColors_p.   

// 2. Treat the palette as an array and assign color value,
//    (manually define your own color palettes,
//    or write code that creates color palettes on the fly).
//    There are several different palettes of colors demonstrated here.

CRGBPalette16 currentPalette;
TBlendType    currentBlending;  // 设置颜色过度模式 http://fastled.io/docs/3.1/group___colorutils.html

//extern CRGBPalette16 myRedWhiteBluePalette;
extern const TProgmemPalette16 myRedWhiteBluePalette_p PROGMEM;   //写法不同，声明不一样

uint8_t colorIndex = 0;

void setup() {
  delay( 3000 ); // power-up safety delay
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.addLeds<LED_TYPE, 6, COLOR_ORDER>(leds0, 1);
  //  FastLED.setBrightness( BRIGHTNESS );

  currentPalette = myRedWhiteBluePalette_p;
  currentBlending = NOBLEND;  //LINEARBLEND色彩间渐变的效果，不渐变、清晰的色彩分隔设置为NOBLEND
}

void loop()
{
  static uint8_t startIndex = 0;
  startIndex = startIndex + 1; /* motion speed */ //可以理解为

  //FillLEDsFromPaletteColors(startIndex);

  colorIndex = startIndex;
  uint8_t brightness = 82;
  //================ FastLED update =================

  for ( int i = 0; i < NUM_LEDS; ++i) {
    leds[i] = ColorFromPalette(currentPalette, colorIndex, brightness, currentBlending);
    colorIndex += 4;
    brightness -= 2;
  }
  leds0[0] = ColorFromPalette(RainbowColors_p, startIndex, brightness / 10, currentBlending);
  FastLED.show();
  FastLED.delay(1000 / UPDATES_PER_SECOND);
}


// 以下是不同的设置palette的写法

// This function fills the palette with totally random colors.
// 法一： 简单的当作数组来赋值就可以了，可以是CRGB也可以是CHSV格式
void SetupTotallyRandomPalette()
{
  for ( int i = 0; i < 16; ++i) {
    currentPalette[i] = CHSV( random8(), 255, random8());
  }
}

// This function sets up a palette of black and white stripes,
// using code. Since the palette is effectively an array of
// sixteen CRGB colors, the various fill_* functions can be used
// to set them up.
// 法二： 用fill_solid对数组批量赋值
void SetupBlackAndWhiteStripedPalette()
{
  // 'black out' all 16 palette entries...
  fill_solid(currentPalette, 16, CRGB::Black);
  // and set every fourth one to white.
  currentPalette[0] = CRGB::White;
  currentPalette[4] = CRGB::White;
  currentPalette[8] = CRGB::White;
  currentPalette[12] = CRGB::White;
}

// This function sets up a palette of purple and green stripes.
// 法三： 先自定义一些颜色，然后用直观的方式排列出来
void SetupPurpleAndGreenPalette()
{
  CRGB purple = CHSV( HUE_PURPLE, 255, 255);
  CRGB green  = CHSV( HUE_GREEN, 255, 255);
  CRGB black  = CRGB::Black;

  currentPalette = CRGBPalette16(
                     green,  green,  black,  black,
                     purple, purple, black,  black,
                     green,  green,  black,  black,
                     purple, purple, black,  black );
}


// 法三： 先自定义一些颜色，然后用直观的方式排列出来
const TProgmemPalette16 myRedWhiteBluePalette_p PROGMEM =
{
  CRGB::Red,
  CRGB::Gray, // 'white' is too bright compared to red and blue
  CRGB::Blue,
  CRGB::Black,

  CRGB::Red,
  CRGB::Gray,
  CRGB::Blue,
  CRGB::Black,

  CRGB::Red,
  CRGB::Red,
  CRGB::Gray,
  CRGB::Gray,
  CRGB::Blue,
  CRGB::Blue,
  CRGB::Black,
  CRGB::Black
};
