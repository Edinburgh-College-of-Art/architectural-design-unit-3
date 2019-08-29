/* 
 * Interrupts
 * 
 * For Arduino UNO the interrupt pins are 2 and 3. Check here:
 * https://www.arduino.cc/reference/en/language/functions/external-interrupts/attachinterrupt/
 * 
 * 
 */
/*========================================================================*/
/* Globals */
const byte ledPin = LED_BUILTIN;
const byte interruptPin = 2;
volatile byte state = LOW;
 
/*========================================================================*/
/* Call Back Function: called when condition on pin is met */
void blink() 
{
  state = !state;
}

/*========================================================================*/
void setup() 
{
  pinMode(ledPin, OUTPUT);
  pinMode(interruptPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPin), blink, FALLING);
}
/*========================================================================*/

void loop() 
{
  digitalWrite(ledPin, state);
}


