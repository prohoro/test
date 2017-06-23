#include <SPI.h>
#include <RFID.h>
#include <Wire.h>
#define RST_PIN    9    // 
#define SS_PIN    10    //
#define AT24C32 0x50
RFID rfid(SS_PIN, RST_PIN);
const int maxval =4096;
int adress = 0;
byte data;
byte massOut [16];
byte massInput [16];
int adr = 0x68;
byte sec =0;
byte minut=0;
byte hou=0;
byte mont=0;
byte date=0;
byte yea=0;
void setup() 
{
 // Serial.begin(9600);
  Wire.begin();
  while (!Serial);
  SPI.begin();
  rfid.init();
}
void loop() 
{
  char zapros; 
  if (Serial)
  {
    while (Serial.available() > 0) {
    zapros +=char(Serial.read());
  }
  if (zapros == 'r')
  {
    Serial.println ("ok");
    Serial.println ("read....");
    readEEPROM();
    
  }
  if (zapros == 'c')
  {
    Serial.println ("ok");
    Serial.println ("clean....");
    adress=0;
  }
  }
  delay (100);
  if (rfid.isCard()) 
        if (rfid.readCardSerial()) 
        {
                massOut[0] = rfid.serNum[0];
                massOut[1] = rfid.serNum[1];
                massOut[2] = rfid.serNum[2];
                massOut[3] = rfid.serNum[3];
                massOut[4] = rfid.serNum[4];
                GetDate();
                massOut[5] = sec;
                massOut[6] = minut;
                massOut[7] = hou;
                massOut[8] = date;
                massOut[9] = mont;
                massOut[10] = yea;
                massOut[15] = setSumm();
                printSumm();
                writeEEPROM();    
        }

}

