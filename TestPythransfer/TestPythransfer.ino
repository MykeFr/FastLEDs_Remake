
#include <Packet.h>
#include <PacketCRC.h>
#include <SerialTransfer.h>
#include <I2CTransfer.h>
#include <SPITransfer.h>

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

SerialTransfer myTransfer;

bool mustanswer = false;

void setup()
{
  Serial.begin(115200);
  myTransfer.begin(Serial);

  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
}


void loop()
{
  
  char response[3];
  if(myTransfer.available())
  {
    digitalWrite(13, HIGH);
    delay(100);
    digitalWrite(13, LOW);
    delay(100);
    mustanswer = true;

    for(int i = 0; i < myTransfer.bytesRead; ++i)
      response[i] = myTransfer.packet.rxBuff[i];
 
  myTransfer.packet.txBuff[0] = response[0];
  myTransfer.packet.txBuff[1] = response[1];
  myTransfer.packet.txBuff[2] = response[2];

  }
  
  myTransfer.sendData(3);
  
  delay(200);
}
