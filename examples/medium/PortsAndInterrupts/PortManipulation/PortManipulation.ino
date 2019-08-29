/*
  Arduino Port Mnipulation
  |
  |
  https://www.arduino.cc/en/Reference/PortManipulation


  This example uses Port D but there are other ports available.
  Check the above link for more info

  Port D: Pins 0 - 7
  
*/

//========================================================================
// Globals
uint8_t ss = 0;

//========================================================================

void setup() 
{
  // pins 76543210
  DDRD = B11111111; // sets Arduino pins 0 to 7 as outputs
  DDRD = DDRD | B11111100;  // this is safer as it sets pins 2 to 7 as outputs
                            // without changing the value of pins 0 & 1, which are RX & TX
  PORTD = ss; 
}

//========================================================================

void loop() 
{
  ss++;
  PORTD = ss;
  delay(100);
}

//========================================================================
