# arduino-examples

Documentation and example for the Arduino Uno kits available on bookit.

## About

This repository hopes to collect together some examples of code for Arduino that will be relevant to courses across ECA. There is a particular focus towards IoT device based operations as well as communicating with other environments like MaxMSP and Processing.

### examples

This folder is home to example projects and code snippets that aim to demonstrate how the Arduino operates using real world examples.

### Sensors

In the bookit store there are sensor kits available. Each kit contains a small selection of sensor to help you get started. All sensors in the kits are from the [SEEED Studio Grove range](http://wiki.seeedstudio.com/Sensor/) of sensors.

### SD Card

Included in the kit is a SD Card shield that can be connected to the Arduino. Use this to save data from your sensors or read data from a file to control the Arduino. The documentation for the SD Card shield can be found on the [SEEED Studio Wiki](http://wiki.seeedstudio.com/SD_Card_shield_V4.0/). Their are examples that can be accessed through the Arduino IDE but some extra examples have been included in the `sdcard` folder.

### library

This folder collects together a selection of header files that aim to simplify some operations. Copy these into your Arduino project and include them with a

```c
#include "HEADER_FILE.h"
```

line at the top of your script.

Once you feel more adventurous, you can go into these files and edit them to fit your own needs.

## Links

-   [Arduino Tutorials](https://www.arduino.cc/en/Tutorial/HomePage)
-   [Arduino Language Reference](https://www.arduino.cc/reference/en/)
-   [The Digital Development Resource List](https://eu01.alma.exlibrisgroup.com/leganto/public/44UOE_INST/lists/18896877830002466?auth=SAML)
