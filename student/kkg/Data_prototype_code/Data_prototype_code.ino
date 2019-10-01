/*
    What is This?

    What Does it do?

    Pins?

    Who made it?

    when it was made?
*/
//--------------------------------------------------------------------------------
#include <LiquidCrystal.h>
#include <SPI.h>
#include <SD.h>
//--------------------------------------------------------------------------------
const int rs = 9, en = 8, d4 = 3, d5 = 5, d6 = 6, d7 = 7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
//--------------------------------------------------------------------------------
const int pinAdc = A0; //sound sensor
//--------------------------------------------------------------------------------
const int buttonPin = 2;     // the number of the pushbutton pin
const int ledPin =  10;      // the number of the LED pin
int buttonState = 0;         // variable for reading the pushbutton status
bool record = false;
//--------------------------------------------------------------------------------
void toggleRecord()
{
  record = !record;
}
//--------------------------------------------------------------------------------
void setup()
{
  //--------------------------------------------------------------------------------
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT);
  setupSD();
  //--------------------------------------------------------------------------------
  lcd.begin(16, 2); // set up the LCD's number of columns and rows:
  lcd.print("Sound Intensity");
  //--------------------------------------------------------------------------------
}
//--------------------------------------------------------------------------------
void loop()
{
  //--------------------------------------------------------------------------------
  long sound = 0;
  for (int i = 0; i < 32; i++)
  {
    sound += analogRead(pinAdc);
  }

  sound >>= 5;
  //--------------------------------------------------------------------------------
  Serial.println(sound);
  delay(100);
  //--------------------------------------------------------------------------------
  if (record)
  {
    digitalWrite(ledPin, HIGH);
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
    digitalWrite(ledPin, LOW);
  }
  //--------------------------------------------------------------------------------
  lcd.setCursor(0, 1);
  lcd.print(sound); //prints value of the sound sensor
}
