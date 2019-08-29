void setupSdCardShield()
{
  Serial.print("Initializing SD card...");
  if (!SD.begin(4))
  {
    Serial.println("initialization failed!");
    while (1);
  }
  Serial.println("initialization done.");
}

void writeToFile(const char* filename, int sensorData)
{
  File myFile = SD.open("data.csv", FILE_WRITE); // you will have to close this one before opening another.
  if (myFile)
  {
    myFile.println(sensorData);
    myFile.close();
  }
  else
  {
    Serial.println("error opening datalog.txt");
  }
}
