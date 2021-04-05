# Wifi Clock and Air Quality Monitor

Feng Zhou, 7/29/2020

## Overview

This is a Wifi clock and air quality monitor based on [Kevin Norman's Air Quaility Meter project](https://kn100.me/where-embedded-meets-the-internet-building-your-own-air-quality-meter/)(See [PDF](hardware.pdf) for a local copy).  Hardware is almost the same, so just
follow Kevin's article. The only difference is the addition of a button between pin 
12 and GND. Most of the changes are on the software side. I added easy Wifi configuration 
(the original project uses hard-coded Wifi SSID/password), an always-accurate clock 
(network-synced), and a button to switch between functionalities.

Enjoy!

## Final product

See [product image](Clock_Air_Monitor.JPG)

## Instructions

1. Get the necessary components as mentioned in the original [article](hardware.pdf). 
Don't forget the extra button.

2. Install [Arduino IDE](https://www.arduino.cc/en/main/software) if you have not yet done so.

3. Within Arduino IDE, use `Sketch->Library->Manage Libraries` to install the following libraries:
  * [LiquidCrystal I2C](https://github.com/fdebrabander/Arduino-LiquidCrystal-I2C-library) 1.1.2
  * NTPClient 3.2.0
  * [BigNumbers_I2C](https://github.com/Anush-DP/BigNumbers_I2C)
  * PubSubClient 2.8.0
  * EasyButton 2.0
  * PageBuilder 1.4.2
  * AutoConnect 1.1.7

4. Open `airmonitor/airmonitor.ino` in Arduino IDE.

5. Connect the dev board through USB, and install the firmware with `Sketch->Upload`.

Once installed, the firmware works as follows,

1. The first time when the wifi clock is powered up, it needs some setup for it to connect
   to the Wifi. Just follow the instructions on the screen. Use your phone to connect to the
   clock's Wifi network. Then in the pop-up screen on your phone, choose "add new AP", put in
   Wifi information and you will be done. Remember the board only support 2.4Ghz networks, 
   not 5Ghz ones.

2. After the setup is done, the clock should show accurate time as displayed in the picture
   above.

3. Press the button once to turn on backlight. Press it again to switch to air quality 
monitoring, where you can see air quality index, measure temperature, humidity, pressure, 
VOC and CO2. Press it again to show Wifi configuration page. The last part is not finished 
yet.


## Future work

 * Finish configuration-through-wifi. It would be nice to be able to do things like setting
   alarms, changing time zones and etc.

 * Add LiPo battery for portability. Probably need to lower power consumption by adding
   power management to the firmware (currently unoptimized version is at around 80mA @ 5V). 

 * MQTT for reporting air quality to server.



