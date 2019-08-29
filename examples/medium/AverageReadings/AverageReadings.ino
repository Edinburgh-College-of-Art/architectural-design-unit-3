uint16_t a = 0;
uint8_t numberOfReadings = 100;

void setup() 
{  
  for (int i = 0; i < numberOfReadings; ++i)
  {
    a += analogRead(A0);
  }
  a /= numberOfReadings;
}

void loop() {
  // put your main code here, to run repeatedly:

}
