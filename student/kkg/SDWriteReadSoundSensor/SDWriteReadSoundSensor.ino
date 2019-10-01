/*
  SD card read/write

 This example shows how to read and write data to and from an SD card file
 The circuit:
 * SD card attached to SPI bus as follows:
 ** MOSI - pin 11
 ** MISO - pin 12
 ** CLK - pin 13
 ** CS - pin 4 (for MKRZero SD: SDCARD_SS_PIN)

 created   Nov 2010
 by David A. Mellis
 modified 9 Apr 2012
 by Tom Igoe

 This example code is in the public domain.

 */
 int pinAdc = A0; //sound sensor
#include <SPI.h>
#include <SD.h>

File myFile;
int pinCS = 10;                      // Pin 10 on Arduino Uno
const int analogInPin = A0;          // Analog input pin that the LDR is attached to
void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);



  Serial.print("Initializing SD card...");

  if (!SD.begin(4)) {
    Serial.println("initialization failed!");
    while (1);
  }
  Serial.println("initialization done.");

  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  myFile = SD.open("data001.txt", FILE_WRITE);

  // if the file opened okay, write to it:
  if (myFile) {
    Serial.print("Writing to test.txt...");
    myFile.println("testing 1, 2, 3.");
    // close the file:
    myFile.close();
    Serial.println("done.");
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }
}

void loop() {
      //sound sensor:
  long sound = 0;
  for (int i = 0; i < 30; i++)
  {
    sound += analogRead(pinAdc);
    delay (100);
  }

  sound >>= 5;

  Serial.println(sound);
  
  myFile = SD.open("data001.txt", FILE_WRITE); //8 characters max
  if (myFile) {    
    myFile.print(sound);             // Write the time to .txt file
    myFile.print(",");                          // Write a comma 
    myFile.close();                             // close the file
  }
  // if the file didn't open, print an error:
  else {
    Serial.println("error opening.txt");
  }

}
