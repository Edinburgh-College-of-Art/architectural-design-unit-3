/*
  Arduino Binary Clock

  Sketch to illustrate PortManipulation and Interrupts

  Instructions: 
   - attach Ports to LEDs
   - Attach pin2 to button with a pull up resitor
   - Attach ground to other side of button
*/

//========================================================================
// Globals
volatile uint8_t hh = 12; 
volatile uint8_t mm = 26;
uint8_t ss = 0;

const byte interruptPin = 2; // button for
//========================================================================
// Call Backs
void blink() 
{
  ++mm;
  if ( mm >= 60)
  {
    ++hh;
    hh %= 24;
    PORTC = hh;
  }
  mm %= 60;
  PORTB = mm;
}

//========================================================================

void setup() 
{
  
  DDRD = B11110011;
  PORTD = (ss & 3) | ((ss & 60) << 2); // skipping the use of pins 2 and 3 for interrupt
  
  DDRB = DDRB | B00111111;
  PORTB = mm;

  DDRC = DDRC | B00111111;
  PORTC = hh;

  pinMode(interruptPin, INPUT);
  attachInterrupt(digitalPinToInterrupt(interruptPin), blink, FALLING);
  
}
//========================================================================
void loop() 
{
  for (byte h = 0 ; h < 24; ++h)
  {
    PORTC = (h + hh) % 24;
    for (byte m = 0 ; m < 60; ++m)
    {
      PORTB = (m + mm) % 60;
      for (byte s = 0 ; s < 60; ++s)
      {
        byte ns = (s + ss) % 60;
        PORTD = (ns & 3) | ((ns & 60) << 2); // skipping the use of pins 2 and 3 for interrupt
        delay(1000);
      }
    }
  }  
}
//========================================================================
