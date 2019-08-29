/*
  SD Card: Write Sensor data
*/
//--------------------------------------------------------------------------------
#include <SPI.h>
#include <SD.h>
//--------------------------------------------------------------------------------
void setup()
{
  //------------------------------------------------------------------------------
  Serial.begin(9600);
  while (!Serial) {} // program won't continue until you open Serial Monitor (macOS ⇧⌘M / Windows CTRL⇧M)
  //------------------------------------------------------------------------------
  setupSdCardShield();
}
//--------------------------------------------------------------------------------
void loop()
{
  int sensorData = analogRead(A0);
  writeToFile("data.csv", sensorData);
  Serial.println(sensorData);
  delay(100);
}
//--------------------------------------------------------------------------------
