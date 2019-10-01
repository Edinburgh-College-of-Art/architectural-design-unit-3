/*
    What is This?

    What Does it do?

    Pins?

    Who made it?

    when it was made?
*/
//--------------------------------------------------------------------------------
#include <LiquidCrystal.h>
//--------------------------------------------------------------------------------
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
//--------------------------------------------------------------------------------
const int pinAdc = A0; //sound sensor
//--------------------------------------------------------------------------------
const int buttonPin = 1;     // the number of the pushbutton pin
const int ledPin =  13;      // the number of the LED pin
int buttonState = 0;         // variable for reading the pushbutton status
//--------------------------------------------------------------------------------
void setup()
{
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);  
  pinMode(buttonPin, INPUT);
  
  lcd.begin(16, 2); // set up the LCD's number of columns and rows:  
  lcd.print("Sound Intensity");
}

void loop()
{
  //sound sensor:
  long sum = 0;
  for (int i = 0; i < 32; i++)
  {
    sum += analogRead(pinAdc);
  }

  sum >>= 5;

  Serial.println(sum);
  delay(100);

  //push button
  // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);
  // check if the pushbutton is pressed.
  // if it is, the buttonState is HIGH:
  if (buttonState = HIGH) {
    // turn LED on:
    digitalWrite(ledPin, HIGH);
  } else {
    // turn LED off:
    digitalWrite(ledPin, LOW);
  }

  //the LCD screen
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 1);
  lcd.print(analogRead(pinAdc)); //prints value of the sound sensor

}
