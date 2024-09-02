#pragma once
// -=-=-=-=-=-=- Uncomment the platform you're building for -=-=-=-=-=-=-
// #define STICK_C_PLUS
// #define STICK_C_PLUS2
// #define STICK_C
// #define CARDPUTER
// #define DIAL
// #define CoreInk
// -=-=- Uncommenting more than one at a time will result in errors -=-=-

// -=-=- Shark Language for Menu and Portal -=- Thanks, @marivaaldo and @Mmatuda! -=-=-
// #define LANGUAGE_EN_US
// #define LANGUAGE_PT_BR
// #define LANGUAGE_GER
// #define LANGUAGE_IT_IT
// #define LANGUAGE_FR_FR
// #define LANGUAGE_NL_NL


#ifndef SHARK_VERSION
#define SHARK_VERSION "dev 1.0.5"
#endif

#if !defined(CARDPUTER) && !defined(STICK_C_PLUS2) && !defined(STICK_C_PLUS) && !defined(STICK_C) && !defined(DIAL) && !defined(CoreInk)
// #define CoreInk
// #define DIAL
 #define CARDPUTER
#endif

#if !defined(LANGUAGE_EN_US) && !defined(LANGUAGE_PT_BR) && !defined(LANGUAGE_GER) && !defined(LANGUAGE_IT_IT) && !defined(LANGUAGE_FR_FR) && !defined(LANGUAGE_NL_NL)
#define LANGUAGE_EN_US
#endif

// -- DEPRECATED - THESE ARE NOW EEPROM DEFINED -- //
#ifdef CoreInk
uint16_t BGCOLOR = 0x0000;  // placeholder
uint16_t FGCOLOR = 0xFFFF;  // placeholder
#else
uint16_t BGCOLOR = 0x0001;  // placeholder
uint16_t FGCOLOR = 0xFFF1;  // placeholder
#endif

// -=-=- DEAUTHER -=-  @bmorcelli -=-=- | Discord: Pirata#5263 bmorcelli
#define DEAUTHER  //Need to make some changes in arduino IDE, refer to https://github.com/bmorcelli/m5stickC_Plus2-nemo/tree/main/DEAUTH%20Prerequisites


#if defined(STICK_C_PLUS)
#include <M5StickCPlus.h>
  // -=-=- Display -=-=-
String platformName = "StickC+";
#define BIG_TEXT 4
#define MEDIUM_TEXT 3
#define SMALL_TEXT 2
#define TINY_TEXT 1
// -=-=- FEATURES -=-=-
#define M5LED 10
#define RTC
#define AXP
#define ACTIVE_LOW_IR
#define ROTATION
#define USE_EEPROM
#define SDCARD  //Requires a custom-built adapter
#define SONG

// -=-=- ALIASES -=-=-
#define DISP M5.Lcd
#define IRLED 9
#define PortBpinIN 33
#define PortBpinOUT 32
#define SPEAKER M5.Beep
//  #define BITMAP DISP.pushImage(0, 0, 240, 135, (uint16_t *)SHARKMatrix);// NOT TESTED YET
#define BITMAP Serial.println("unsupported")
#define SD_CLK_PIN 0
#define SD_MISO_PIN 36
#define SD_MOSI_PIN 26
#define SD_CS_PIN -1  //can be 14, to avoid serial messages
#define M5LED_ON LOW
#define M5LED_OFF HIGH
#endif

#if defined(STICK_C_PLUS2)
#include <M5StickCPlus2.h>
// -=-=- Display -=-=-
String platformName = "StickC+2";
#define BIG_TEXT 4
#define MEDIUM_TEXT 3
#define SMALL_TEXT 2
#define TINY_TEXT 1
// -=-=- FEATURES -=-=-
#define ACTIVE_LOW_IR
#define M5LED 19
#define ROTATION
#define USE_EEPROM
#define DTime
#define DTget StickCP2.Rtc
#define RTC     //TODO: plus2 has a BM8563 RTC but the class isn't the same, needs work.
#define SDCARD  //Requires a custom-built adapter
#define PWRMGMT
#define SPEAKER M5.Speaker
#define SONG
// -=-=- ALIASES -=-=-
#define DISP M5.Lcd
#define IRLED 19
#define PortBpinIN 33
#define PortBpinOUT 32
#define BITMAP DISP.pushImage(0, 0, 240, 135, (uint16_t *)SHARKMatrix);
#define M5_BUTTON_MENU 35
#define M5_BUTTON_HOME 37
#define M5_BUTTON_RST 39
#define BACKLIGHT 27
#define MINBRIGHT 190
#define SD_CLK_PIN 0
#define SD_MISO_PIN 36
#define SD_MOSI_PIN 26
#define SD_CS_PIN -1  //can be -1, but sends a lot of messages of error in serial monitor
#define M5LED_ON HIGH
#define M5LED_OFF LOW
#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 160

#endif

#if defined(STICK_C)
#include <M5StickC.h>
// -=-=- Display -=-=-
String platformName = "StickC";
#define BIG_TEXT 2
#define MEDIUM_TEXT 2
#define SMALL_TEXT 1
#define TINY_TEXT 1
// -=-=- FEATURES -=-=-
#define M5LED 10
#define RTC
#define AXP
#define ROTATION
#define USE_EEPROM
#define SDCARD  //Requires a custom-built adapter
// -=-=- ALIASES -=-=-
#define DISP M5.Lcd
#define IRLED 9
#define PortBpinIN 33
#define PortBpinOUT 32
#define BITMAP Serial.println("unsupported")
#define SD_CLK_PIN 0
#define SD_MISO_PIN 36
#define SD_MOSI_PIN 26
#define SD_CS_PIN -1  //can be 14, to avoid serial messages
#define M5LED_ON LOW
#define M5LED_OFF HIGH
#endif

#if defined(CARDPUTER)
#include <M5Cardputer.h>
// -=-=- RTC -=-=-
#include <ESP32Time.h>
ESP32Time rtcp;
#define ESPTime
// -=-=- Display -=-=-
String platformName = "Cardputer";
#define BIG_TEXT 4
#define MEDIUM_TEXT 3
#define SMALL_TEXT 2
#define TINY_TEXT 1
// -=-=- FEATURES -=-=-
#define KB
#define RTC
#define HID
#define ACTIVE_LOW_IR
#define USE_EEPROM
#define SDCARD
#define SONG
// -=-=- ALIASES -=-=-
#define DISP M5Cardputer.Display
#define UperBtn 0
#define IRLED 44
#define PortBpinIN 1
#define PortBpinOUT 2
#define BACKLIGHT 38
#define MINBRIGHT 165
#define SPEAKER M5Cardputer.Speaker
#define BITMAP DISP.pushImage(0, 0, 240, 135, (uint16_t *)SHARKMatrix);
#define SD_CLK_PIN 40
#define SD_MISO_PIN 39
#define SD_MOSI_PIN 14
#define SD_CS_PIN 12
#define VBAT_PIN 10
#define M5LED_ON HIGH
#define M5LED_OFF LOW
#endif


#if defined(DIAL)
#include <M5Dial.h>
// -=-=- Display -=-=-
String platformName = "Dial";
#define BIG_TEXT 4
#define MEDIUM_TEXT 3
#define SMALL_TEXT 2
#define TINY_TEXT 1
// -=-=- FEATURES -=-=-
#define DTime
#define DTget M5Dial.Rtc
#define RTC
#define USE_EEPROM
#define SONG
#define ROTATION
// -=-=- ALIASES -=-=-
#define DISP M5Dial.Display
#define UperBtn 0
#define PortBpinIN 1
#define PortBpinOUT 2
#define IRLED 2
#define BACKLIGHT 9
#define MINBRIGHT 20
#define SPEAKER M5Dial.Speaker
#define BITMAP DISP.pushImage(0, 0, 240, 240, (uint16_t *)SHARKMatrix);
#define VBAT_PIN 15
#define M5_BUTTON_HOME 46
#define M5LED_ON HIGH
#define M5LED_OFF LOW
int abstand[] = { 60, 50, 33, 23, 0, 23, 35, 50, 60, 10, 10 };
float Helligkeit[] = { 0.3, 0.5, 0.7, 0.85, 1, 0.85, 0.7, 0.5, 0.3, 0, 0 };
#endif

#if defined(CoreInk)
#include <M5CoreInk.h>
// -=-=- Display -=-=-
Ink_Sprite PageSprite(&M5.M5Ink);
String platformName = "CoreInk";
#define BIG_TEXT 3
#define MEDIUM_TEXT 2
#define SMALL_TEXT 2
#define TINY_TEXT 1
// -=-=- FEATURES -=-=-
#define RTC
#define HID
#define ACTIVE_LOW_IR
#define USE_EEPROM
#define SDCARD
#define SONG
// -=-=- ALIASES -=-=-
#define DISP M5.M5Ink
#define VBAT_PIN 35
#define UperBtn 0
#define IRLED 32
#define PortBpinIN 32
#define PortBpinOUT 33
#define M5_BUTTON_MENU 5
#define M5_BUTTON_HOME 38
#define M5_BUTTON_RST 39
#define M5_BUTTON_UP 37
#define SPEAKER M5.Speaker
#define BITMAP DISP.pushImage(-20, 32, 240, 135, (uint16_t *)SHARKMatrix);
#define SD_CLK_PIN 25
#define SD_MISO_PIN 36
#define SD_MOSI_PIN 26
#define SD_CS_PIN -1
#define VBAT_PIN 10
#define M5LED_ON HIGH
#define M5LED_OFF LOW
#endif


// -=-=-=-=-=- LIST OF CURRENTLY DEFINED FEATURES -=-=-=-=-=-
// M5LED      - A visible LED (Red) exposed on this pin number
// IRLED      - An IR LED exposed on this pin number
// RTC        - Real-time clock exposed as M5.Rtc
// AXP        - AXP192 Power Management exposed as M5.Axp
// PWRMGMT    - StickC+2 Power Management exposed as M5.Power
// KB         - Keyboard exposed as M5Cardputer.Keyboard
// HID        - HID exposed as USBHIDKeyboard
// USE_EEPROM - Store settings in EEPROM
// ROTATION   - Allow screen to be rotated
// DISP       - Set to the API's Display class
// SDCARD     - Device has an SD Card Reader attached
// SONG       - Play melody or beep on startup
// SPEAKER    - Aliased to the prefix used for making noise
// BACKLIGHT  - Alias to the pin used for the backlight on some models
// MINBRIGHT  - The lowest number (0-255) for the backlight to show through
