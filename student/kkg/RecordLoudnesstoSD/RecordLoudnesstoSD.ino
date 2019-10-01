/*
    Record sound loudness to SD Card

    Pins

    Who made it

    when it was made
*/
//--------------------------------------------------------------------------------
#include <SPI.h>
#include <SD.h>
//--------------------------------------------------------
int LED = 12;
int BUTTON = 4;
int pinAdc = A0;
//--------------------------------------------------------
void setup()
{
  Serial.begin(9600);
  pinMode(LED, OUTPUT);
  pinMode(BUTTON, INPUT);
}
//--------------------------------------------------------
void loop()
{
  //--------------------------------------------------------
  unsigned int sound = 0;
  for (int i = 0; i < 30; i++)
  {
    sound += analogRead(pinAdc);
    delay(1);
  }
  sound /= 30;
  Serial.println(sound);
  //--------------------------------------------------------
  if (digitalRead(BUTTON) == HIGH)
  {
    digitalWrite(LED, HIGH);
    File myFile = SD.open("data.txt", FILE_WRITE); //8 characters max
    if (myFile)
    {
      myFile.println(sound); // Write the time to .txt file
//      myFile.print(",");   // Write a comma
      myFile.close();        // close the file
    }
    else
    {
      digitalWrite(LED, LOW);
      Serial.println("error opening temperaturetest.txt");
    }
    digitalWrite(LED, LOW);
  }
  //--------------------------------------------------------
}
//--------------------------------------------------------
// EOF
