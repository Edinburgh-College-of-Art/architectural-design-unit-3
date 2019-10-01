void setupSD()
{
  if (!SD.begin(4))
  {
    Serial.println("initialization failed!");
    while (1) {};
  }
  Serial.println("initialization done.");
}
