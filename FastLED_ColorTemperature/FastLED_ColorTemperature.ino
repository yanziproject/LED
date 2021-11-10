/*
   本例演示针对LED色偏问题的调整，以及利用色温调整功能
   获得特殊的颜色效果。推荐看看官方的示例，是个切换色温的例子。

   多色LED很可能某颜色比另两个颜色亮或者一个颜色比另两个
   颜色暗，导致设置的颜色和显示的颜色出现偏差。不只是LED灯，
   哪怕是苹果手机显示屏也存在不同程度的屏幕偏绿问题。

   FastLED提供两种调节色温、色偏的方法：
   setCorrection() 调节一根灯带的色偏
   FastLED.setTemperature() 调节全部灯带的色温问题
   (色温间的切换只需要改setTemperature()里的参数就可以了，
   灵活运用会很简单地达到类似于TD里adjust HSV top的效果)

   Reference link
   调色温的原理： https://github.com/FastLED/FastLED/wiki/FastLED-Color-Correction
   预设色温枚举型参数定义： http://fastled.io/docs/3.1/group___color_enums.html
*/

//============== Fast LED ==============

#include <FastLED.h>

#define LED_PIN     5

// Information about the LED strip itself
#define NUM_LEDS    60
#define CHIPSET     WS2811
#define COLOR_ORDER GRB
CRGB leds[NUM_LEDS];

int BRIGHTNESS = 255;
bool up = false;

#define TEMPERATURE_1 SodiumVapor
#define TEMPERATURE_2 UncorrectedTemperature

void setup() {
  delay(3000); // power-up safety delay

  //============= Fast LED =============
  // It's important to set the color correction for your LED strip here,
  // so that colors can be more accurately rendered through the 'temperature' profiles
  // FastLED.addLeds<CHIPSET, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalSMD5050);

  // 不用预设的色偏数据，也可以根据实际情况调整，写十六进制的RGB就可以，如灯带偏红，则可以写为0xAAFFFF 。
  FastLED.addLeds<CHIPSET, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(0xAAFFFF);

  //如果全灯带同色，也可以直接用色温去控制，非常稳
  //  CRGB col1 = CHSV(30, 200, 255);
  //  FastLED.addLeds<CHIPSET, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(col1);
  FastLED.setBrightness( BRIGHTNESS );
}

void loop()
{
  // draw a generic, no-name rainbow
  static uint8_t starthue = 0;
  fill_rainbow( leds + 5, NUM_LEDS - 5, --starthue, 20);

  //FastLED.setTemperature(0x00AAFF); // set temperature to control of the overall output 'color temperature'
  leds[0] = TEMPERATURE_1;            // show indicator pixel
  //
  //  if (up && BRIGHTNESS < 255) {
  //    BRIGHTNESS++;
  //    if (BRIGHTNESS == 255) {
  //      up = false;
  //    }
  //  }
  //  if (up == false) {
  //    BRIGHTNESS--;
  //    if (BRIGHTNESS == 0) {
  //      up = true;
  //    }
  //  }
  //
  //  FastLED.setBrightness( BRIGHTNESS );
  FastLED.show();
  FastLED.delay(50);
}

// FastLED v2.1 provides two color-management controls:
//   (1) color correction settings for each LED strip, and
//   (2) master control of the overall output 'color temperature'
//
// FastLED provides these pre-conigured incandescent color profiles:
//     Candle, Tungsten40W, Tungsten100W, Halogen, CarbonArc,
//     HighNoonSun, DirectSunlight, OvercastSky, ClearBlueSky,
//
// FastLED provides these pre-configured gaseous-light color profiles:
//     WarmFluorescent, StandardFluorescent, CoolWhiteFluorescent,
//     FullSpectrumFluorescent, GrowLightFluorescent, BlackLightFluorescent,
//     MercuryVapor, SodiumVapor, MetalHalide, HighPressureSodium,
//
// FastLED also provides an "Uncorrected temperature" profile
//    UncorrectedTemperature;
