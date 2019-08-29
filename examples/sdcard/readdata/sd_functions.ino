void setupSdCardShield()
{
  Serial.print("Initializing SD card...");
  if (!SD.begin(4))
  {
    Serial.println("initialization failed!");
    while (1) {}
  }
  Serial.println("initialization done.");
}

//------------------------------------------------------

void printFileToSerial(const char* filename)
{
  myFile = SD.open(filename);
  if (myFile)
  {
    Serial.print(filename);Serial.println(":");
    while (myFile.available())   // read from the file until there's nothing else in it:
    {
      Serial.write(myFile.read());
    }
    myFile.close();
  }
  else
  {
    Serial.println("error opening test.txt");   // if the file didn't open, print an error:
  }
}
