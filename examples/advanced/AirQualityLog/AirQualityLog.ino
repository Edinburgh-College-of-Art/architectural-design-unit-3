/* This piece of code is a modified version of a sketch by fat16lib, Arduino forum user and was
   edited by Henri Lacoste for AD3 at UoE.
   This code is in the public domain.
 */
//------------------------------------------------------------------------------
#include "AirQualitySensor.h"
#include "Arduino.h"
#include <SPI.h>
#include <SD.h>
#include <DS3231.h>

//------------------------------------------------------------------------------
const int airQualityPin = A0;      // Analog input pin that the LDR is attached to
AirQualitySensor airqualitysensor(airQualityPin);
//------------------------------------------------------------------------------
DS3231 rtc(SDA, SCL);
//------------------------------------------------------------------------------
#define FILE_BASE_NAME "Data"    // Base name must be six characters or less for short file names.
const uint8_t CS_PIN = 4;       // CS pin of SD card module
File file;
const uint8_t BASE_NAME_SIZE = sizeof(FILE_BASE_NAME) - 1;
char fileName[] = FILE_BASE_NAME "00.txt";
//------------------------------------------------------------------------------
void setup()
{
    Serial.begin(9600);
    airqualitysensor.init();
    setupSdShield();
}
//------------------------------------------------------------------------------
void loop()
{
    airqualitysensor.slope();
    int airQuality = airqualitysensor.getValue();
    Serial.println("now the Air quality sensor is :");
    Serial.println(airQuality);
    delay(500);
    writeToSd(airQuality);
}
//------------------------------------------------------------------------------
void setupSdShield()
{
    if (!SD.begin(CS_PIN))
    {                 // Initializing SD card module
        Serial.println(F("begin failed"));
        return;
    }
    while (SD.exists(fileName)) // Working out what number to name data.txt file
    {
        if (fileName[BASE_NAME_SIZE + 1] != '9')
        {
            fileName[BASE_NAME_SIZE + 1]++;
        }
        else if (fileName[BASE_NAME_SIZE] != '9')
        {
            fileName[BASE_NAME_SIZE + 1] = '0';
            fileName[BASE_NAME_SIZE]++;
        }
        else {
            Serial.println(F("Can't create file name"));
            return;
        }
        rtc.begin(); // Start the real time clock module
    }
    file = SD.open(fileName, FILE_WRITE);
    if (!file)
    {
        Serial.println(F("open failed"));
        return;
    }
    Serial.print(F("opened: ")); // This will print what file name has been created
    Serial.println(fileName);    // for data to be logged to
    file.close();
}
//------------------------------------------------------------------------------
void writeToSd(int data)
{
    file = SD.open(fileName, FILE_WRITE);
    if (file)
    {
        Serial.print(rtc.getTimeStr());   // Print the time
        Serial.print(",");                // Print a comma
        Serial.print(int(rtc.getTemp())); // Print the temperature
        Serial.print(",");                // Print a comma
        Serial.println(data);             // Print data
        file.print(rtc.getTimeStr());     // Write the time to .txt file
        file.print(",");                  // Write a comma
        file.print(int(rtc.getTemp()));   // Write the temperature to .txt file
        file.print(",");                  // Write a comma
        file.println(data);               // Write the data reading to .txt file
        file.close();                     // close the file
        delay(3000);                      // Wait 3000ms before taking another reading
    }
}
