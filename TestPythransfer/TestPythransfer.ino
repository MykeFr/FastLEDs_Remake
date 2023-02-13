#include <SimpleSerialProtocol.h>
#include <Core.h>

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

CRGB leds[NUM_LEDS]={0};

SerialTransfer myTransfer;
uint8_t response[252] = {0};

void setup()
{
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setMaxPowerInVoltsAndMilliamps(VOLTS,MAX_AMPS);
  FastLED.setBrightness(BRIGHTNESS);
  Serial.begin(115200);
  myTransfer.begin(Serial);
 FastLED.show();

  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);

  delay(2000);
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


void loop()
{
  //delay(400);
  
  if(myTransfer.available())
  {
    //digitalWrite(13, HIGH);
    //delay(100);
    //digitalWrite(13, LOW);
    //delay(100);

   uint16_t bytes_read = myTransfer.rxObj(response, 0, myTransfer.bytesRead);
    
    for(int i = 0; i < myTransfer.bytesRead; ++i)
      response[i] = myTransfer.packet.rxBuff[i];
   
    /*response[0] = 0;
    response[1] = 255;
    response[2] = 0;
    response[3] = 0;
    response[4] = 0;
    response[5] = 255;
    response[6] = 0;
    response[7] = 0;
    */
    for(int i = 0; i <  bytes_read; i+=4){
      leds[i/4] = CRGB((int)response[i+2], (int) response[i+1],(int) response[i]);
    }
    FastLED.show();
    delay(200);
  }
  myTransfer.txObj(response, 0, 252);
  
  //for(int i = 0; i < 254; ++i)
    //myTransfer.packet.txBuff[i] = response[i];

 myTransfer.sendData(252);
 delay(200);
}
