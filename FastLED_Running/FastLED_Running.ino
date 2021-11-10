/*
   本例示范如何用FastLED来写跑马灯，很基础，将灯带
   看成是一个数组，小灯的颜色或亮暗单独控制就好。
*/

//================= FastLED ===================

#include <FastLED.h>

#define NUM_LEDS 42   // How many leds in your strip?
#define DATA_PIN 7
CRGB leds[NUM_LEDS];  // Define the array of leds

float previousMillis;
int fadeINwaittime = 100;
byte x = 0;
byte masterBright_ceiling = 128;

static int i = 0;
static uint8_t hue = 0;

const int interval = 100; // milliseconds


void setup() {
  //================ FastLED ==================

  LEDS.addLeds<WS2812, DATA_PIN, RGB>(leds, NUM_LEDS);

  // setBrightness()的亮度设置会覆盖掉用其他方法设定的亮度，
  // 如果希望不同的小灯亮度不一样，就不能用setBrightness()。
  LEDS.setBrightness(80);

}

void loop() {
  // basicRunning();
  //basicRunning1();
  //basicRunning_fadeTail();
  // Now go in the other direction.
  //	for(int i = (NUM_LEDS)-1; i >= 0; i--) {
  //		// Set the i'th led to red
  //		leds[i] = CHSV(hue++, 255, 255);
  //		// Show the leds
  //		FastLED.show();
  //		// now that we've shown the leds, reset the i'th led to black
  //		// leds[i] = CRGB::Black;
  //		fadeall();
  //		// Wait a little bit before we loop around and do it again
  //		delay(10);
  //	}

}

void basicRunning() {
  leds[(millis() / interval) % NUM_LEDS] = CHSV(hue + (millis() / interval) , 255, 255); // set color value
  FastLED.show();   // display the color
}

void basicRunning1() {
  leds[(millis() / interval) % NUM_LEDS] = CHSV(hue + (millis() / interval) , 255, 255); // set color value

  int lightLength = 5;
  leds[((millis() / interval) - lightLength ) % NUM_LEDS] = CHSV(hue, 0, 0); // trun into black

  FastLED.show();    // display the color
}

void basicRunning_fadeTail() {
  leds[(millis() / interval) % NUM_LEDS] = CHSV(hue + (millis() / interval) , 255, 255); // set color value
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i].nscale8(254);  //scale down a RGB to N 256ths of it's current brightness, using 'plain math' dimming rules, which means that if the low light levels may dim all the way to 100% black.
  }
  FastLED.show();    // display the color
}

void fadeIN()
{
  if (millis() - previousMillis > fadeINwaittime)
  {
    FastLED.setBrightness(x);
    if (x++ > masterBright_ceiling)
    {
      x = 0;
      //break;
    }
  }
}

void fadeall() {
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i].nscale8(254);  //scale down a RGB to N 256ths of it's current brightness, using 'plain math' dimming rules, which means that if the low light levels may dim all the way to 100% black.
  }
}
