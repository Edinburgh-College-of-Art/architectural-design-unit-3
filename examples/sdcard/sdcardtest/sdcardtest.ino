/*
      SD card test
*/
//--------------------------------------------------------------------------------
#include <SPI.h>
#include <SD.h>
//--------------------------------------------------------------------------------
// set up variables using the SD utility library functions:
Sd2Card card;
SdVolume volume;
SdFile root;
const int chipSelect = 4;
//--------------------------------------------------------------------------------
void setup()
{
  //------------------------------------------------------------------------------
  Serial.begin(9600);
  while (!Serial) {} // program won't continue until you open Serial Monitor (macOS ⇧⌘M / Windows CTRL⇧M)
  //------------------------------------------------------------------------------
  setupSdCardShield();
}

void loop()
{

}
