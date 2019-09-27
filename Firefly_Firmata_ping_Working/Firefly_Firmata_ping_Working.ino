/* 
 Edited by Johannes Frolich, 
 Modified version from Andrew Payne and original Firefly Firmata
 Firefly Firmata written by Jason Kelly Johnson and Andrew Payne
 
 Copyright 2013 | All Rights Reserved
 
 This Firmata allows you to control an Arduino board from Rhino/Grasshopper/Firefly.
 Updates, Questions, Suggestions visit: http://www.fireflyexperiments.com
 
 1. Plug Arduino boards into your USB port; confirm that your Arduino's green power LED in on
 2. Select your specific Arduino Board and Serial Port (Tools > Board; Tools > Se\rial Port) *Take note of your Serial Port COM #
 3. Verify (play button) and Upload (upload button) this program to your Arduino, close the Arduino program
 4. then open ... Rhino/Grasshopper/Firefly
 
 Note: The Firefly Firmata sets the following pins to perform these functions:
 
 
 
 NOTE== THIS VERSION ONLY WORKS ON ARDUINO UNO, WITH ULTRASONIC PING SENSOR CONNECTED TO DIGITAL PIN 2!!
ON DPIN2 IT SHOWS THE DISTANCE IN CM. 

 */

#include <Servo.h>            // attach Servo library (http://www.arduino.cc/playground/ComponentLib/Servo)
#include <pins_arduino.h>     // attach arduino pins header file to determine which board type is being used

#define BAUDRATE 115200       // Set the Baud Rate to an appropriate speed
#define BUFFSIZE 512          // buffer one command at a time, 12 bytes is longer than the max length

/*==============================================================================
 * GLOBAL VARIABLES
 *============================================================================*/

char buffer[BUFFSIZE];        // declare buffer
uint8_t bufferidx = 0;        // a type of unsigned integer of length 8 bits
char *parseptr;
char buffidx;

int counter = 0;
int numcycles = 1000;
int pingPin = 2;
//TEST

long duration, inches, cm;

 uint16_t APin0, APin1, APin2, APin3, APin4, APin5, DPin2, DPin4, DPin7;             // declare input variables
  uint16_t DPin3, DPin5, DPin6, DPin8, DPin9, DPin10, DPin11, DPin12, DPin13;         // declare output variables  
  Servo Servo3, Servo5, Servo6, Servo8, Servo9, Servo10, Servo11, Servo12, Servo13;   // declare Servo objects


/*==============================================================================
 * SETUP() This code runs once
 *============================================================================*/
void setup()
{ 
  Init();                  //set initial pinmodes
  Serial.begin(BAUDRATE);  // Start Serial communication
}

/*==============================================================================
 * LOOP() This code loops
 *============================================================================*/
void loop()
{
  if(Serial){
    ReadSerial();                       // read and parse string from serial port and write to pins
    if (counter >= numcycles){          // Wait every nth loop 
      ReadInputs();                     // get input data
      entfernung();
      PrintToPort();                    // print data to serial port 
      counter = 0;                      // reset the counter
    }
    counter ++;                         // increment the writecounter
  }
}

/*==============================================================================
 * FUNCTIONS()
 *============================================================================*/

void Init(){
   
   
  //  pinMode(2, OUTPUT); 
    pinMode(4, INPUT); 
    pinMode(7, INPUT);
  

}



void ReadInputs(){ 
    APin0 = analogRead(0);   
    APin1 = analogRead(1);  
    APin2 = analogRead(2); 
    APin3 = analogRead(3); 
    APin4 = analogRead(4); 
    APin5 = analogRead(5); 
   // DPin2 = digitalRead(2);  
    DPin4 = digitalRead(4);  
    DPin7 = digitalRead(7); 
  
 
}

void entfernung(){
    pinMode(2, OUTPUT);
    digitalWrite(2, LOW);
    delay(2);
    digitalWrite(2, HIGH);
    delayMicroseconds(10);
    digitalWrite(2, LOW);
  
  
    pinMode(2, INPUT);
   duration = pulseIn(2, HIGH);
 //  delay(10);
   cm = microsecondsToCentimeters(duration);
   
  }
  
long microsecondsToCentimeters(long microseconds)
{
  // speed of sound: 340 m/s or 29 microseconds/cm.
  // so: half of the distance
  return microseconds / 2.9 / 2;
}
  
  
  
void PrintToPort(){
    Serial.print(APin0); Serial.print(",");  
    Serial.print(APin1); Serial.print(","); 
    Serial.print(APin2); Serial.print(","); 
    Serial.print(APin3); Serial.print(","); 
    Serial.print(APin4); Serial.print(","); 
    Serial.print(APin5); Serial.print(","); 
    Serial.print(cm); Serial.print(","); 
    Serial.print(DPin4); Serial.print(","); 
    Serial.print(DPin4); Serial.print(","); 
    Serial.println("eol");  //end of line marker
  
 
}

void ReadSerial(){

  char c;    // holds one character from the serial port
  if (Serial.available()) {
    c = Serial.read();         // read one character
    buffer[bufferidx] = c;     // add to buffer

    if (c == '\n') {  
      buffer[bufferidx+1] = 0; // terminate it
      parseptr = buffer;       // offload the buffer into temp variable

        DPin13 = parsedecimal(parseptr);     // parse the first number
        parseptr = strchr(parseptr, ',')+1;  // move past the ","
        
        DPin12 = parsedecimal(parseptr);     // parse the second number
        parseptr = strchr(parseptr, ',')+1;  // move past the ","
  
        DPin11 = parsedecimal(parseptr);     // parse the third number
        parseptr = strchr(parseptr, ',')+1;  // move past the ","
  
        DPin10 = parsedecimal(parseptr);     // parse the fourth number
        parseptr = strchr(parseptr, ',')+1;  // move past the ","
  
        DPin9 = parsedecimal(parseptr);      // parse the fifth number
        parseptr = strchr(parseptr, ',')+1;  // move past the ","
  
        DPin8 = parsedecimal(parseptr);      // parse the sixth number
        parseptr = strchr(parseptr, ',')+1;  // move past the ","
  
        DPin6 = parsedecimal(parseptr);      // parse the seventh number
        parseptr = strchr(parseptr, ',')+1;  // move past the ","
  
        DPin5 = parsedecimal(parseptr);      // parse the eighth number
        parseptr = strchr(parseptr, ',')+1;  // move past the ","
  
        DPin3 = parsedecimal(parseptr);      // parse the ninth number
        
        WriteToPin(13, DPin13, Servo13);     //send value out to pin on arduino board
        WriteToPin(12, DPin12, Servo12);
        WriteToPin(11, DPin11, Servo11);
        WriteToPin(10, DPin10, Servo10);
        WriteToPin(9, DPin9, Servo9);
        WriteToPin(8, DPin8, Servo8);
        WriteToPin(6, DPin6, Servo6);
        WriteToPin(5, DPin5, Servo5);
        WriteToPin(3, DPin3, Servo3);
         
      

      
     
      
      bufferidx = 0;                             // reset the buffer for the next read
      return;                                    // return so that we don't trigger the index increment below
    }                                            // didn't get newline, need to read more from the buffer
    bufferidx++;                                 // increment the index for the next character
    if (bufferidx == BUFFSIZE-1) bufferidx = 0;  // if we get to the end of the buffer reset for safety
  }
}

void WriteToPin(int _pin, int _value, Servo _servo){
if (_value >= 1000 && _value < 2000)             // check if value should be used for Digital Write (HIGH/LOW)
{      
  if (_servo.attached()) _servo.detach();        // detach servo is one is attached to pin
  pinMode(_pin, OUTPUT);                         // sets the pin for output 
  _value -=1000;                                 // subtract 1000 from the value sent from Firefly 
  if (_value == 1) digitalWrite(_pin, HIGH);     // Digital Write to pin
  else digitalWrite(_pin, LOW);   
}   
else if (_value >= 2000 && _value < 3000)        // check if value should be used for Analog Write (0-255)
{
  if (_servo.attached()) _servo.detach();        // detach servo is one is attached to pin
  pinMode(_pin, OUTPUT);                         // sets the pin for output 
  _value -= 2000;                                // subtract 2000 from the value sent from Firefly
  analogWrite(_pin, _value);                     // Analog Write to pin
}
else if (_value >= 3000 && _value < 4000)        // check if value should be used for Servo Write (0-180)
{
  _value -= 3000;                                // subtract 3000 from the value sent from Firefly
  if (!_servo.attached())_servo.attach(_pin);    // attaches a Servo to the PWM pin (180 degree standard servos)                                    
  _servo.write(_value);                          // Servo Write to the pin
  }
}

uint32_t parsedecimal(char *str){
  uint32_t d = 0;
  while (str[0] != 0) {
    if ((str[0] > '50') || (str[0] < '0'))
      return d;
    d *= 10;
    d += str[0] - '0';
    str++;
  }
  return d;
}
