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
int BUTTON = 2;
int pinAdc = A0;
bool record = false;
//--------------------------------------------------------
void toggleRecord() {
  record = !record;
}
//--------------------------------------------------------
void setup()
{
  Serial.begin(9600);
  pinMode(LED, OUTPUT);
  pinMode(BUTTON, INPUT);
  setupSD();
  attachInterrupt(digitalPinToInterrupt(BUTTON), toggleRecord, RISING);
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

  if (record)
  {
    digitalWrite(LED, HIGH);
    File myFile = SD.open("data.txt", FILE_WRITE); //8 characters max
    if (myFile)
    {
      myFile.println(sound); // Write the time to .txt file
      myFile.close();        // close the file
    }
    else
    {
      Serial.println("error opening data.txt");
    }
  }
  else
  {
    digitalWrite(LED, LOW);
  }
  //--------------------------------------------------------
}
//--------------------------------------------------------

//--------------------------------------------------------
// EOF
