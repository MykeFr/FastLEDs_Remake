
#include <Packet.h>
#include <PacketCRC.h>
#include <SerialTransfer.h>
#include <I2CTransfer.h>
#include <SPITransfer.h>

#include <FastLED.h>

#define NUM_LEDS 4
#define DATA_PIN 3

#define MAX_AMPS 1000
#define VOLTS 5

#define COLS 14
#define ROWS 10
#define USELESS_PER_ROW 5
#define BRIGHTNESS 30

CRGB leds[NUM_LEDS];

SerialTransfer myTransfer;


void setup()
{
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setMaxPowerInVoltsAndMilliamps(VOLTS,MAX_AMPS);
  FastLED.setBrightness(BRIGHTNESS);
  Serial.begin(115200);
  myTransfer.begin(Serial);

  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);

  delay(2000);
}


void loop()
{
  leds[1] = CRGB(255, 0, 0);
  leds[2] = CRGB(0, 255, 0);
  leds[3] = CRGB(0, 0, 255);
  FastLED.show();
  //delay(400);
  
  char response[254] = {0};
  if(myTransfer.available())
  {
    //digitalWrite(13, HIGH);
    //delay(100);
    //digitalWrite(13, LOW);
    //delay(100);
    
    for(int i = 0; i < myTransfer.bytesRead; ++i)
      response[i] = myTransfer.packet.rxBuff[i];
 
    for(int i = 0; i < 1; ++i)
      leds[i] = CRGB((int)response[i+0]*2, (int) response[i+1]*2,(int) response[i+2]*2);
    
    FastLED.show();
    delay(200);
   }

  for(int i = 0; i < 254; ++i)
    myTransfer.packet.txBuff[i] = response[i];

 myTransfer.sendData(254);
 delay(200);
}
