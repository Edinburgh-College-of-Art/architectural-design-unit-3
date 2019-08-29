/*
   Sound Sensor Example
*/
//------------------------------------------------
const int soundSensorPin = A0;
const int readInterval = 10; // number of millis between sensor readings
unsigned long lastReadingTime = 0;
unsigned long loudness;
//------------------------------------------------
void setup()
{
  Serial.begin(115200);
}
//------------------------------------------------
void loop()
{
  long now = millis();
  //--------------------------------------------
  if (now - lastReadingTime > readInterval)
  {
    loudness = getLoudness();
    Serial.println(loudness);
  }
  //--------------------------------------------
  // Do something else here
  //--------------------------------------------
}
//------------------------------------------------
