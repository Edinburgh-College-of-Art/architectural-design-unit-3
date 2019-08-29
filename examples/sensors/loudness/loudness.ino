// Using the Grove Loudness sensor

int loudness = 0;

void setup()
{
    Serial.begin(9600);
}

void loop()
{
    for(int i = 0 ; i < 40; ++i)
    {      
      uint16_t lastValue = analogRead(0);
      loudness += lastValue;
      delay(4);
    }
 
    Serial.println(loudness);
    loudness = 0;
}
