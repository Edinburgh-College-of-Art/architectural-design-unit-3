/* This piece of code is a modified version of a sketch by fat16lib, Arduino forum user and was
 * edited by Henri Lacoste for AD3 at UoE.
 * This code is in the public domain.
 */

#include <SPI.h>
#include <SD.h>
#include <DS3231.h>

DS3231  rtc(SDA, SCL);

const int analogInPin = A0;      // Analog input pin that the LDR is attached to
#define FILE_BASE_NAME "Data"    // Base name must be six characters or less for short file names.

const uint8_t CS_PIN = 10;       // CS pin of SD card module

File file;

const uint8_t BASE_NAME_SIZE = sizeof(FILE_BASE_NAME) - 1;  
char fileName[] = FILE_BASE_NAME "00.txt";

void setup() {
  Serial.begin(9600);
  if (!SD.begin(CS_PIN)) {                 // Initializing SD card module
    Serial.println(F("begin failed"));
    return;
  }
  while (SD.exists(fileName)) {                      // Working out what number to name data.txt file
    if (fileName[BASE_NAME_SIZE + 1] != '9') {
      fileName[BASE_NAME_SIZE + 1]++;
    } else if (fileName[BASE_NAME_SIZE] != '9') {
      fileName[BASE_NAME_SIZE + 1] = '0';
      fileName[BASE_NAME_SIZE]++;
    } else {
      Serial.println(F("Can't create file name"));
      return;
    }
     rtc.begin();                                     // Start the real time clock module
  }
  file = SD.open(fileName, FILE_WRITE);
  if (!file) {
    Serial.println(F("open failed"));
    return;
  }
  Serial.print(F("opened: "));                        // This will print what file name has been created
  Serial.println(fileName);                           // for data to be logged to
  file.close();

}


void loop() {
  
  file = SD.open(fileName, FILE_WRITE);
  if (file) {
   
 
  Serial.print(rtc.getTimeStr());           // Print the time
  Serial.print(",");                        // Print a comma
  Serial.print(int(rtc.getTemp()));         // Print the temperature
  Serial.print(",");                        // Print a comma
  Serial.println(analogRead(analogInPin));  // Print reading from LDR


  file.print(rtc.getTimeStr());             // Write the time to .txt file
  file.print(",");                          // Write a comma 
  file.print(int(rtc.getTemp()));           // Write the temperature to .txt file
  file.print(",");                          // Write a comma
  file.println(analogRead(analogInPin));    // Write the LDR reading to .txt file
  file.close();                             // close the file
   
  delay(3000);                              // Wait 3000ms before taking another reading
}
}
