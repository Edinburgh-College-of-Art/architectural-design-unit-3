/*
   EEPROM Test: Basic EEPROM functionality
*/
#include <EEPROM.h>
//====================================================================
const char *message = "Congrats! you've learned to use the EEPROM";
//====================================================================
void setup()
{
  Serial.begin(9600);
  while (!Serial) {}
  for (int i = 0; i < 512; ++i)
  {
    Serial.print(char(EEPROM[i]));
    if (char(EEPROM[i]) == '\0')
      break;
  }
  delay(1000);
  int j;
  for (int i = 0; message[i] != '\0'; ++i)
  {
    EEPROM[i] = message[i];
    j = i;
  }
  EEPROM[j + 1] = '\n';
  EEPROM[j + 2] = '\0';
  Serial.print("\nPress the Reset Button\n");
}//====================================================================
void loop()
{

}
//====================================================================
