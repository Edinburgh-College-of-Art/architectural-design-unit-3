unsigned long getLoudness()
{
  unsigned long loudness = 0;
  for (int i = 0; i < 32; i++)
  {
    loudness += analogRead(soundSensorPin);
  }
  loudness >>= 5;
  
  return loudness;
}
