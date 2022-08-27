#include <FastLED.h>

#define NUM_LEDS 300
#define DATA_PIN 3

#define MAX_AMPS 1000
#define VOLTS 5

#define COLS 14
#define ROWS 10
#define USELESS_PER_ROW 5
#define BRIGHTNESS 100

CRGB leds[NUM_LEDS];
int loop_count = 0;

void setup() { 
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setMaxPowerInVoltsAndMilliamps(VOLTS,MAX_AMPS);
  FastLED.setBrightness(BRIGHTNESS);
  Serial.begin(9600);
}

int matrixToIndex(int x, int y){
  return x + y * COLS + USELESS_PER_ROW * y;
}

void loop() {
  leds[0] = CRGB::Red;
  FastLED.show();
  delay(2000);
  for(int y = 0; y < ROWS; y++){
    for(int x = 0; x < COLS; x++){
      Serial.print(x);Serial.print(" ");Serial.println(y);
      int index = matrixToIndex(x, y);
      leds[index] = CRGB(((x + y) * 255 / COLS) % 255, ((x + y) * 255 / COLS) % 255, ((x + y) * 255 / COLS) % 255);
      FastLED.show();
      delay(250);
    }
  }

  for(int x = 0; x < COLS; ++x){
    for(int y = 0; y < ROWS; ++y){
      int index = matrixToIndex(x, y);
      leds[index] = CRGB(255 - ((x + y) * 255 / COLS) % 255, 0, 0);
      FastLED.show();
      delay(250);
    }
  }
}
