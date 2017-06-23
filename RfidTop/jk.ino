void printSumm()
{
  Serial.println ("Out mass");
  for (int i = 0 ; i < 16 ; i++)
  {
    Serial.println (massOut[i],DEC);
  }
}
void printRead()
{
   Serial.println ("id");
   Serial.println (massInput[0]);
   Serial.println (massInput[1]);
   Serial.println (massInput[2]);
   Serial.println (massInput[3]);
   Serial.println (massInput[4]);
   Serial.println ("Time");
   Serial.println (massInput[5]);
   Serial.println (massInput[6]);
   Serial.println (massInput[7]);
   Serial.println (massInput[8]);
   Serial.println (massInput[9]);
   Serial.println (massInput[10]);
   for (int i = 0 ; i < 16 ; i++)
   {
     Serial.print (massInput[i],DEC);
     Serial.print (" ");
   }
   Serial.println();
}
void writeEEPROM()
{
  Wire.beginTransmission(AT24C32);
  Wire.write(highAddressByte(adress));
  Wire.write(lowAddressByte(adress));
  for(byte i=0; i<16; i++)
  {
    Wire.write(massOut[i]);    
  }
  delay(10);
  Wire.endTransmission();
  adress= adress+16;
}
void readEEPROM()
{
  adress = adress-16;
  Wire.beginTransmission(AT24C32);
  Wire.write(highAddressByte(adress));
  Wire.write(highAddressByte(adress));
  Wire.endTransmission();
  delay(10);
  Wire.requestFrom(AT24C32, 16);
  delay(10);
  for(byte i=0; i<16; i++)
  {
    massInput[i] = Wire.read();
  }
  delay(10);
  if (!ControlSumm())
    Serial.println ("Eror read!");
  else
    printRead();
    
  
}
byte setSumm ()
{
  byte summ;
  for (int i = 0 ; i < 15 ; i++)
  {
    summ +=massOut[i];
  }
  return summ;
}
bool ControlSumm ()
{
  byte summ;
  for (int i = 0 ; i < 15 ; i++)
  {
    summ +=massInput[i];
  }
  //printRead();
  //Serial.println("summm");
  //Serial.println(byte(summ/256));
  if ( massInput[15]==summ)
  {
    return true;
  }
  else
  {
    return false;
  }
}
byte highAddressByte(word address)
{
  byte BYTE_1;
  BYTE_1 = address >> 8;
  return BYTE_1;
}

byte lowAddressByte(word address)
{
  byte BYTE_1;
  byte BYTE_2;
  BYTE_1 = address >> 8;
  BYTE_2 = address - (BYTE_1 << 8);
  return BYTE_2;
}
byte perevod (byte val)
{
  return ((val/16*10)+(val%16));
}
void GetDate () 
{
  Wire.beginTransmission(adr);
Wire.write(0);
//Wire.write(1);
Wire.endTransmission();
Wire.requestFrom(adr,7);
sec = perevod(Wire.read()&0x7f);
minut = perevod(Wire.read());
hou = perevod (Wire.read()&0x3f);
Wire.read();// Не используем день не дели
date = perevod (Wire.read());
mont = perevod (Wire.read());
yea = perevod (Wire.read());
/*Serial.print (sec,DEC);
Serial.print (" ");
Serial.print (minut,DEC);
Serial.print (" ");
Serial.print (hou,DEC);
Serial.print (" ");
Serial.print (date,DEC);
Serial.print (" ");
Serial.print (mont,DEC);
Serial.print (" ");
Serial.print (yea,DEC);
Serial.println ();*/
}
