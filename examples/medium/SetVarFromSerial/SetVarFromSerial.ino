int val = 0;

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  Serial.println("\n\nSet value");
  Serial.flush();
  while (!Serial.available());
  while (Serial.available())
  {
    val = Serial.read();
  }
  Serial.println(val);
  Serial.flush();
}
