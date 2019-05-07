/*
 *  Arduino Time, Temperature and Light Data Logging
 *  
 *  by Dejan Nedelkovski, www.HowToMechatronics.com edited by Henri Lacoste for AD3 at UoE
 *  LDR sensor connected to A0 pin on Arduino Uno
 */
#include <SD.h>
#include <SPI.h>
#include <DS3231.h>
File myFile;
DS3231  rtc(SDA, SCL);
int pinCS = 10;                      // Pin 10 on Arduino Uno
const int analogInPin = A0;          // Analog input pin that the LDR is attached to
void setup() {
    
  Serial.begin(9600);
  pinMode(pinCS, OUTPUT);
  
  // SD Card Initialization
  if (SD.begin())
  {
    Serial.println("SD card is ready to use.");
  } else
  {
    Serial.println("SD card initialization failed");
    return;
  }
  rtc.begin();    
}
void loop() {
  Serial.print(rtc.getTimeStr());           // Print the time
  Serial.print(",");                        // Print a comma
  Serial.print(int(rtc.getTemp()));         // Print the temperature
  Serial.print(",");                        // Print a comma
  Serial.println(analogRead(analogInPin));  // Print reading from LDR
 
  myFile = SD.open("data001.txt", FILE_WRITE); //8 characters max
  if (myFile) {    
    myFile.print(rtc.getTimeStr());             // Write the time to .txt file
    myFile.print(",");                          // Write a comma 
    myFile.print(int(rtc.getTemp()));           // Write the temperature to .txt file
    myFile.print(",");                          // Write a comma
    myFile.println(analogRead(analogInPin));    // Write the LDR reading to .txt file
    myFile.close();                             // close the file
  }
  // if the file didn't open, print an error:
  else {
    Serial.println("error opening temperaturetest.txt");
  }
  delay(3000);
}
