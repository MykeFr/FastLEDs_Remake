#include <Packet.h>
#include <PacketCRC.h>
#include <SerialTransfer.h>
#include <I2CTransfer.h>
#include <SPITransfer.h>

#include <SerialTransfer.h>
#include <FastLED.h>

#define NUM_LEDS 300
#define DATA_PIN 3

#define MAX_AMPS 1000
#define VOLTS 5

#define COLS 14
#define ROWS 10
#define USELESS_PER_ROW 5
#define BRIGHTNESS 30

CRGB leds[NUM_LEDS];

void setup() { 
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setMaxPowerInVoltsAndMilliamps(VOLTS,MAX_AMPS);
  FastLED.setBrightness(BRIGHTNESS);
  Serial.begin(115200);

}

// converts from 2D plane to an array index. (0, 0) is in top left
int matrixToIndex(int x, int y){
  // if LED strip starts from right to left from the top. 0 or 1
  bool STARTS_FROM_R_TO_L = (y % 2 == 0);
  
  // either this row is from left to right, or right to left
  // right to left
  if(STARTS_FROM_R_TO_L)
    return (COLS - x - 1) + y * COLS + USELESS_PER_ROW * y;
  
  // left to right
  if(!STARTS_FROM_R_TO_L)
    return x + y * COLS + USELESS_PER_ROW * y;
}

void loop() {
  
  for(int x = 0; x < COLS; ++x){
    for(int y = 0; y < ROWS; ++y){
      int index = matrixToIndex(x, y);
      leds[index] = CHSV(((float)(x + y) / (float)(COLS + ROWS)) * 255, 255, 255);
      Serial.print(x);Serial.print(",");Serial.println(y);
      Serial.println(index);
      FastLED.show();
      delay(100);  
    }
  }

  for(int x = 0; x < COLS; ++x){
    for(int y = 0; y < ROWS; ++y){
      int index = matrixToIndex(x, y);
      leds[index] = CHSV(255 - ((float)(x + y) / (float)(COLS + ROWS)) * 255, 255, 255);
      FastLED.show();
      delay(100);  
    }
  }
}
