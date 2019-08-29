/*
   This code is a modified version of an example piece of code written by Tom Igoe.

   This example code is in the public domain.

   LDR signal must be connected to A0 pin on Arduino Uno
 */


const int analogInPin = A0; // Analog input pin that the LDR is attached to

void setup()
{

    Serial.begin(9600); // initialize serial communications at 9600 bps:
}

void loop()
{
    // read the analog in value and print the results to the serial monitor:
    Serial.print("LDR = ");
    Serial.println(analogRead(analogInPin));
    // wait 1 second before the next loop
    delay(1000);
}
