# M5Stick-SHARK
Updated version of M5Stickc-NEMO https://github.com/n0xa/m5stick-nemo.

Firmware for pranks on M5Stack ESP32 Devices

![Shark](https://github.com/AH2005NA/m5stick-shark/blob/main/Shark.png)

## Name and Background
Shark is a Projekt i started at the 29.2.2024 1:12 PM. I saw a tutorial for the M5StickC PLUS2 on youtube and i ordered myself one when i saw that it only costs 30 USD. It arrived two weeks later and i burned the Nemo firmware on it. I wanted to see the code from this firmware and i downloadet the source code at 1:12 PM. I saw a that it is programed with arduino and because of this fact i decided to programm my own version. Thanks to n0xa good programming skills it isnt a big deal to change and add things. Thank you!
I decided to call this firmware shark. I gave it this name because i wanted to name it an other fish as reference to Nemo and i choose Shark because it is the easiest fish to get Images generated from AI 😁.

## My Changelog
DEV 1.0.6
* Add Dutch
* Add Support to the M5Dial
* Add Support to the CoreInk

DEV 1.0.5
* RFID (With SD)

DEV 1.0.4
* M5Button(Btn G0 by Cardputer) presst while (After) Startup: no Startupsound
* add an option to disable the Startupsound
* 2 new language: Italian (IT_IT), French (FR_FR)
* Fixed IRAH Bug
* add IRAH remote

DEV 1.0.3 and older
* Change everything to Shark
* add time and battery on Menu
* add Custom Boot Images and sounds
* IR_AH app (Transmit)
* Changed the Number-Menu for the Cardputer

## My ToDo list
* IR_AH app (IR Receive)
* IR_AH app (save remotes to SD card)
* Windows app
* ideas?

## Features
* [TV B-Gone](http://www.righto.com/2010/11/improved-arduino-tv-b-gone.html) port (thanks to MrArm's [HAKRWATCH](https://github.com/MrARM/hakrwatch)) to shut off many infrared-controlled TVs, projectors and other devices
* [AppleJuice](https://github.com/ECTO-1A/AppleJuice) iOS Bluetooth device pairing spam
* Bluetooth device notification spamming for SwiftPair (Windows) and Android
* WiFi Spam - Funny SSIDs, WiFi Rickrolling, and a Random mode that creates hundreds of randomly-named SSIDs per minute
* WiFi NEMO Portal - A captive portal that tries to social engineer email credentials - saves usernames and passwords to SD Card (if inserted into a supported reader)
* WiFi SSID Scanner - Display 2.4 GHz SSIDs nearby, get information about them, and even clone the SSIDs in NEMO Portal
* User-adjustable 24 Hour digital clock backed by the M5 Stick RTC so it holds relatively stable time even in deep sleep and low battery mode
* EEPROM-backed Settings for rotation, brightness, automatic dimming and NEMO Portal SSID
* Battery level and credits in settings menu
* IR_AH save and replay IR signals
* RFID copy and write RFID tags

## User Interface
There are three main controls:
* Home - Stops the current process and returns you to the menu from almost anywhere in SHARK
* Next - Moves the cursor to the next menu option. In function modes, this usually stops the process and returns you to the previous menu.
* Select - Activates the currently-selected menu option, and wakes up the dimmed screen in function modes  

* StickC and StickC-Plus
  * Power: Long-press the power button for 6 seconds to turn off the unit
  * Home: Tap the power button (closest to the USB port)
  * Next: Tap the side button
  * Select: Tap the M5 button on the front of the unit
  * M5Button presst while Startup: no Startupsound

* Cardputer
  * Home: Tap the Esc/~/` key or the Left-Arrow/, key
  * Next/Prev: Tap the Down-Arrow/. key and Up-Arrow/; keys to navigate
  * Select: Tap the OK/Enter key or Right-Arrow/? key  
  * M5Button presst AFTER switch turn on: no Startupsound

## NEMO Portal
In NEMO Portal mode, NEMO activates an open WiFi Hotspot named "Nemo Free WiFi" (configurable in portal.h) with DNS, DHCP and Web servers activated. 
* NEMO Portal serves a fake login page that claims to provide internet access if you log in.
* This is a social engineering attack, and will log the username and passwords entered on the page. 
* From the Wifi Scan details, you can clone an existing SSID from the scan list. Exiting NEMO Portal will clear the Evil Twin SSID
* You can view captured credentials by connecting to the portal from your own device and browsing to http://172.0.0.1/creds
* You can set a custom SSID by connecting to the portal from your own device and browsing to http://172.0.0.1/ssid
* If your device supports EEPROM for settings, the custom SSID you enter will be saved as the default, even if powered off.
* If your device has an SD Card reader with a FAT filesystem formatted card inserted, the usernames and passwords will be logged to nemo-portal-creds.txt on the SD Card for you to peruse later. 
* SD Card support is only enabled by default on the M5Stack Cardputer platform. It can be enabled on M5Stick devices but an SD Card reader must be built and attached to the front panel pin header.
* NEMO Portal is only for use on professional engagements with a valid scope of work, educational or demonstration purposes. Storage, sale, or use of personal information without consent is against the law. 🤓

## Building from Source
If you want to customize NEMO or contribute to the project, you should be familiar with building NEMO from source.
* Install Arduino IDE. I've used Arduino 1.8 on Linux and Windows, and Arduino 2.2 on Windows successfully.
* Install the M5Stack boards for Arduino IDE: In File -> Preferences, paste this URL into the "Boards Manager URLs" text box. Use commas between URLs if there are already URLs present.  https://m5stack.oss-cn-shenzhen.aliyuncs.com/resource/arduino/package_m5stack_index.json
* If M5Stack -> M5Stick-C-Plus doesn't show up under Tools -> Boards, then use Tools -> Boards -> Boards Manager and search for M5Stack. This will install support for most of the M5Stack boards including the Stick C Plus.
* Ensure the correct device model (e.g. M5Stick-C, M5Stick-C-Plus or M5Cardputer) is selected in the boards menu.
* Install necessary libraries. In Sketch -> Include Library -> Library Manager, search for and install the following libraries and any dependencies they require:
  * M5StickCPlus, M5StickC or M5Cardputer
  * IRRemoteESP8266
* Un-comment the appropriate `#define` line near the top for your platform (STICK_C, STICK_C_PLUS or CARDPUTER)
* Switch partition schemes. `Tools` -> `Partition Scheme` -> `No OTA (Large APP)` - sometimes this option is labeled `Huge APP` 
* Configuration
  * The code should compile cleanly and work on an M5Stick C Plus out of the box from the master branch or a release tag.
  * Uncomment only the one appropriate `#define` option or compiler errors will occur. 
  * If for some reason the screen jumps from very dim at level 0 to almost fully bright at level 1 and further brightness levels don't affect anything, set the pct_brightness variable to false.
* Compile and upload the project

## Building from Source (with Arduino CLI)

- Install Arduino CLI
- Add M5Stack Index to Arduino Core
- Add M5Stack Libraries

```bash

# Install m5stack boards
arduino-cli core install m5stack:esp32  --additional-urls https://m5stack.oss-cn-shenzhen.aliyuncs.com/resource/arduino/package_m5stack_index.json --log-level warn --verbose

# Install required library
arduino-cli lib install M5Cardputer --log-level warn --verbose
arduino-cli lib install IRRemoteESP8266 --log-level warn --verbose

# Compile sketch
arduino-cli compile --fqbn m5stack:esp32:m5stack_cardputer -e --build-property build.partitions=huge_app --build-property upload.maximum_size=3145728 ./m5stick-nemo.ino

```

- This will create multiple binaries based on partition sketch, you can merge a single binary using `esptool``
- Install esptool - `pip install -U esptool`

```bash

esptool.py --chip esp32s3 merge_bin --output final.bin 0x0000 m5stick-nemo.ino.bootloader.bin 0x8000 m5stick-nemo.ino.partitions.bin 0x10000 m5stick-nemo.ino.bin
```

- You can now flash the merged binary firmware using `esptool`

```bash

esptool.exe write_flash -z 0 final.bin
```

## Reporting Bugs
Please report bugs via GitHub Issues. These are easier to track than comments on social media posts, M5Burner entries, etc. If something isn't working, please include:
* Firmware version
* Hardware 
* Specifically what feature and options are not working
* How you determined that it is not working and what testing you did. Include device models and operating systems of what you tested with, and any errors, if applicable.
* If you figure out how to fix a bug you identified, PRs are welcome!
