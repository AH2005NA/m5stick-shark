#pragma once
#include "Defines.h"

struct MENU {
  char name[19];
  int command;
};
#if defined(CARDPUTER)
int current_proc = 1;  // Start in Main Menu mode
#elif defined(DIAL)
int current_proc = 1;  // Start in Main Menu mode
#elif defined(RTC)
int current_proc = 0;  //0 Start in Clock Mode
#else
int current_proc = 1;  // Start in Main Menu mode if no RTC
#endif
      bool screen_dim_dimmed = false;
      int screen_dim_time = 30;
      int screen_dim_current = 0;

      void screenBrightness(int bright) {
//Serial.printf("Brightness: %d\n", bright);
#if defined(AXP)
        M5.Axp.ScreenBreath(bright);
#endif
#if defined(BACKLIGHT)
        int bl = MINBRIGHT + round(((255 - MINBRIGHT) * bright / 100));
        analogWrite(BACKLIGHT, bl);
#endif
      }
      
      int uptime() {
        return (int(millis() / 1000));
      }
      
      void dimtimer() {
        if (screen_dim_dimmed) {
          screenBrightness(brightness);
          screen_dim_dimmed = false;
        }
        screen_dim_current = uptime() + screen_dim_time + 2;
      }
      bool check_next_press() {
#if defined(KB)
        M5Cardputer.update();
        if (M5Cardputer.Keyboard.isKeyPressed(';')) {
          // hack to handle the up arrow
          cursor = cursor - 2;
          dimtimer();
          return true;
        }
        //M5Cardputer.update();
        if (M5Cardputer.Keyboard.isKeyPressed(KEY_TAB) || M5Cardputer.Keyboard.isKeyPressed('.')) {
          dimtimer();
          return true;
        }
#elif defined(DIAL)
  M5Dial.update();
  int newPosition = M5Dial.Encoder.read();
  if (-2 > newPosition) {
    M5Dial.Encoder.write(0);
    cursor = cursor - 2;
    dimtimer();
    return true;
  }
  if (2 < newPosition) {
    M5Dial.Encoder.write(0);
    dimtimer();
    return true;
  }
#else
  if (digitalRead(M5_BUTTON_RST) == LOW) {
    dimtimer();
    return true;
  }
#endif
#ifdef M5_BUTTON_UP
        if (digitalRead(M5_BUTTON_UP) == LOW) {
          cursor = cursor - 2;
          dimtimer();
          return true;
        }
#endif
        return false;
      }

#ifdef DIAL

uint8_t CenterText(String Text, uint8_t Textsize) {
  Serial.print(sizeof(Text));
  //return 120 - ((uint16_t)sizeof(Text)*Textsize*3);
  return (240 - ((uint16_t)8 * Textsize * 6)) / 2;
}

void drawmenu(MENU thismenu[], int size) {
  DISP.setTextSize(SMALL_TEXT);
  DISP.fillScreen(BGCOLOR);
  DISP.setCursor(0, 0, 1);
  // scrolling menu
  if (cursor < 0) {
    cursor = size - 1;  // rollover hack for up-arrow on cardputer
  }
  if (cursor > 4) {
    for (int i = 0 + (cursor - 4); i < size; i++) {
      DISP.setCursor(abstand[i - (cursor - 4)], (i - (cursor - 4)) * 30 - 10, 1);
      DISP.setTextColor(blendTowardsBackground(BGCOLOR, FGCOLOR, Helligkeit[(4 - cursor) + i]), BGCOLOR);
      if (cursor == i) {
        DISP.setTextSize(MEDIUM_TEXT);
        DISP.print(">");
        for (uint8_t n = 0; n < 11; n++) {
          DISP.print(thismenu[i].name[n]);
        }
        DISP.setTextSize(SMALL_TEXT);
        if (thismenu[i].name[11] != 0) {
          DISP.setCursor(218, 117, 1);
          DISP.print(".");
          DISP.setCursor(226, 117, 1);
          DISP.print(".");
        }
      } else {
        if (cursor < i) {
          DISP.setCursor(abstand[i - (cursor - 4)], (i - (cursor - 4)) * 30, 1);
        }
        DISP.print(thismenu[i].name);
      }
    }
  } else {
    for (int i = 0; i < size; i++) {
      DISP.setCursor(abstand[(4 - cursor) + i], (110 - (cursor * 30)) + (i * 30), 1);
      DISP.setTextColor(blendTowardsBackground(BGCOLOR, FGCOLOR, Helligkeit[(4 - cursor) + i]), BGCOLOR);
      if (cursor == i) {
        DISP.setTextSize(MEDIUM_TEXT);
        DISP.print(">");
        for (uint8_t n = 0; n < 11; n++) {
          DISP.print(thismenu[i].name[n]);
        }
        DISP.setTextSize(SMALL_TEXT);
        if (thismenu[i].name[11] != 0) {
          DISP.setCursor(218, 117, 1);
          DISP.print(".");
          DISP.setCursor(226, 117, 1);
          DISP.print(".");
        }
      } else {
        if (cursor < i) {
          DISP.setCursor(abstand[(4 - cursor) + i], (120 - (cursor * 30)) + (i * 30), 1);
        }
        DISP.print(thismenu[i].name);
      }
    }
  }
}


uint16_t blendTowardsBackground(uint16_t color, uint16_t backgroundColor, float factor) {
  // Clamp the factor between 0 and 1
  if (factor < 0.0) factor = 0.0;
  if (factor > 1.0) factor = 1.0;

  // Extract the red, green, and blue components from the color
  uint8_t r = (color >> 11) & 0x1F;
  uint8_t g = (color >> 5) & 0x3F;
  uint8_t b = color & 0x1F;

  // Extract the red, green, and blue components from the background color
  uint8_t br = (backgroundColor >> 11) & 0x1F;
  uint8_t bg = (backgroundColor >> 5) & 0x3F;
  uint8_t bb = backgroundColor & 0x1F;

  // Blend the color towards the background color
  r = r + factor * (br - r);
  g = g + factor * (bg - g);
  b = b + factor * (bb - b);

  // Combine the components back into a single RGB565 color
  return (r << 11) | (g << 5) | b;
}
#elif defined(CoreInk)
void drawmenu(MENU thismenu[], int size) {
  PageSprite.setTextSize(SMALL_TEXT);
  PageSprite.fillScreen(BGCOLOR);
  PageSprite.setCursor(0, 0, 1);
  // scrolling menu
  if (cursor < 0) {
    cursor = size - 1;  // rollover hack for up-arrow on cardputer
  }
  if (cursor > 5) {
    for (int i = 0 + (cursor - 5); i < size; i++) {
      if (cursor == i) {
      PageSprite.printf("> %-19s", thismenu[i].name);
      PageSprite.setCursor(0, PageSprite.getCursorY());
      PageSprite.print("     \n");
      }
      else
      {
      PageSprite.printf(" %-19s", thismenu[i].name);
      PageSprite.setCursor(0, PageSprite.getCursorY());
      PageSprite.print("     \n");
      }
    }
  } else {
    for (
      int i = 0; i < size; i++) {
      if (cursor == i) {
      PageSprite.printf("> %-19s", thismenu[i].name);
      PageSprite.setCursor(0, PageSprite.getCursorY());
      PageSprite.print("     \n");
      }
      else
      {
      PageSprite.printf(" %-19s", thismenu[i].name);
      PageSprite.setCursor(0, PageSprite.getCursorY());
      PageSprite.print("     \n");
      }
    }
  }
  //time
  PageSprite.setTextSize(TINY_TEXT);
#if defined(RTC)
  PageSprite.setCursor(170, 0, 1);
  M5.Rtc.GetBm8563Time();
  PageSprite.printf("%02d:%02d\n", M5.Rtc.Hour, M5.Rtc.Minute);
#endif
//Baterie
#if defined(PWRMGMT)
  PageSprite.setCursor(181, 16, 1);
  PageSprite.print(String(M5.Power.getBatteryLevel()));
#endif
#ifdef AXP
  PageSprite.setCursor(181, 16, 1);
  float c = M5.Axp.GetVapsData() * 1.4 / 1000;
  float b = M5.Axp.GetVbatData() * 1.1 / 1000;
  int battery = ((b - 3.0) / 1.2) * 100;
  PageSprite.Print(String(battery));
#endif
  PageSprite.setCursor(181, 16, 1);
  uint8_t battery = map(analogRead(VBAT_PIN), 0, 1023, 0, 100);
  Serial.print(battery);
  //uint8_t battery = ((((analogRead(VBAT_PIN))) * 100) / 1023);
  PageSprite.print(String(battery));
  PageSprite.print("%");
  PageSprite.pushSprite();
}

#else
void drawmenu(MENU thismenu[], int size) {
  DISP.setTextSize(SMALL_TEXT);
  DISP.fillScreen(BGCOLOR);
  DISP.setCursor(0, 0, 1);
  // scrolling menu
  if (cursor < 0) {
    cursor = size - 1;  // rollover hack for up-arrow on cardputer
  }
  if (cursor > 5) {
    for (int i = 0 + (cursor - 5); i < size; i++) {
      if (cursor == i) {
        DISP.setTextColor(BGCOLOR, FGCOLOR);
      }
#ifdef STICK_C
      DISP.printf(" %-25s\n", thismenu[i].name);
#else
      DISP.printf(" %-19s\n", thismenu[i].name);
#endif
      DISP.setTextColor(FGCOLOR, BGCOLOR);
    }
  } else {
    for (
      int i = 0; i < size; i++) {
      if (cursor == i) {
        DISP.setTextColor(BGCOLOR, FGCOLOR);
      }
#ifdef STICK_C
      DISP.printf(" %-25s\n", thismenu[i].name);
#else
      DISP.printf(" %-19s\n", thismenu[i].name);
#endif
      DISP.setTextColor(FGCOLOR, BGCOLOR);
    }
  }
  //time
#if defined(RTC)
  DISP.setCursor(180, 0, 1);
#if defined(DTime)
  auto dt = DTget.getDateTime();
  DISP.printf("%02d:%02d\n", dt.time.hours, dt.time.minutes);
#elif defined(ESPTime)
  DISP.printf("%02d:%02d\n", rtcp.getHour(), rtcp.getMinute());
#elif defined(STICK_C)
  DISP.setCursor(130, 0, 1);
  M5.Rtc.GetBm8563Time();
  DISP.printf("%02d:%02d\n", M5.Rtc.Hour, M5.Rtc.Minute);
#else
  M5.Rtc.GetBm8563Time();
  DISP.printf("%02d:%02d\n", M5.Rtc.Hour, M5.Rtc.Minute);
#endif
#endif
//Baterie
#if defined(PWRMGMT)
  DISP.setCursor(191, 16, 1);
  DISP.print(String(M5.Power.getBatteryLevel()));
#endif
#ifdef AXP
  DISP.setCursor(191, 16, 1);
  float c = M5.Axp.GetVapsData() * 1.4 / 1000;
  float b = M5.Axp.GetVbatData() * 1.1 / 1000;
  int battery = ((b - 3.0) / 1.2) * 100;
#ifdef STICK_C
  DISP.setCursor(141, 16, 1);
#endif
  DISP.print(String(battery));
#endif
#if defined(CARDPUTER)
  DISP.setCursor(191, 16, 1);
  uint8_t battery = ((((analogRead(VBAT_PIN)) - 1842) * 100) / 738);
  DISP.print(String(battery));
#endif
  DISP.print("%");
}
#endif
#ifdef CARDPUTER

void number_drawmenu(int nums) {
  if (check_next_press()) {
    cursor++;
    cursor = cursor % nums;
    if (cursor < 0) {
      cursor = nums - 1;
    }
  }
  uint16_t plus = 0;
  if (M5Cardputer.Keyboard.isKeyPressed(KEY_BACKSPACE)) {
    if (cursor < 10) {
      cursor = 0;
    } else {
      cursor = cursor / 10;
    }
  } else {
    while (1) {
      if (M5Cardputer.Keyboard.isKeyPressed('0')) {
        plus = 0;
      } else if (M5Cardputer.Keyboard.isKeyPressed('1')) {
        plus = 1;
      } else if (M5Cardputer.Keyboard.isKeyPressed('2')) {
        plus = 2;
      } else if (M5Cardputer.Keyboard.isKeyPressed('3')) {
        plus = 3;
      } else if (M5Cardputer.Keyboard.isKeyPressed('4')) {
        plus = 4;
      } else if (M5Cardputer.Keyboard.isKeyPressed('5')) {
        plus = 5;
      } else if (M5Cardputer.Keyboard.isKeyPressed('6')) {
        plus = 6;
      } else if (M5Cardputer.Keyboard.isKeyPressed('7')) {
        plus = 7;
      } else if (M5Cardputer.Keyboard.isKeyPressed('8')) {
        plus = 8;
      } else if (M5Cardputer.Keyboard.isKeyPressed('9')) {
        plus = 9;
      } else {
        break;
      }
      if (cursor == 0) {
      } else if (cursor < 10) {
        cursor = cursor * 10;
      } else if (cursor < 100) {
        cursor = cursor * 100;
      } else if (cursor < 1000) {
        cursor = cursor * 1000;
      } else if (cursor < 10000) {
        cursor = cursor * 10000;
      }
      if (((int32_t)cursor + plus) >= nums) {
        cursor = nums - 1;
      } else {
        cursor += plus;
      }
      break;
    }
  }
  DISP.setTextSize(MEDIUM_TEXT);
  DISP.fillScreen(BGCOLOR);
  DISP.setCursor(20, 20);
  DISP.print(String(cursor, DEC));
}

#elif defined(DIAL)
void number_drawmenu(int nums) {
  if (cursor < 0) {
    cursor = nums - 1;  // rollover hack for up-arrow on cardputer
  }
  if (cursor > 4)
    DISP.setTextSize(SMALL_TEXT);
  DISP.fillScreen(BGCOLOR);
  DISP.setCursor(0, 0, 1);
  if (cursor > 4) {
    for (int i = 0 + (cursor - 4); i < nums; i++) {
      DISP.setCursor(abstand[i - (cursor - 4)], (i - (cursor - 4)) * 30 - 10, 1);
      DISP.setTextColor(blendTowardsBackground(BGCOLOR, FGCOLOR, Helligkeit[(4 - cursor) + i]), BGCOLOR);
      if (cursor == i) {
        DISP.setTextSize(MEDIUM_TEXT);
        DISP.print(">");
        DISP.printf("%d", i);
        DISP.setTextSize(SMALL_TEXT);
      } else {
        if (cursor < i) {
          DISP.setCursor(abstand[i - (cursor - 4)], (i - (cursor - 4)) * 30, 1);
        }
        DISP.printf("%d", i);
      }
    }
  } else {
    for (int i = 0; i < nums; i++) {
      DISP.setCursor(abstand[(4 - cursor) + i], (110 - (cursor * 30)) + (i * 30), 1);
      DISP.setTextColor(blendTowardsBackground(BGCOLOR, FGCOLOR, Helligkeit[(4 - cursor) + i]), BGCOLOR);
      if (cursor == i) {
        DISP.setTextSize(MEDIUM_TEXT);
        DISP.print(">");
        DISP.printf("%d", i);
        DISP.setTextSize(SMALL_TEXT);
      } else {
        if (cursor < i) {
          DISP.setCursor(abstand[(4 - cursor) + i], (120 - (cursor * 30)) + (i * 30), 1);
        }
        DISP.printf("%d", i);
      }
    }
  }
}

#else

void number_drawmenu(int nums) {
  DISP.setTextSize(SMALL_TEXT);
  DISP.fillScreen(BGCOLOR);
  DISP.setCursor(0, 0);
  // scrolling menu
  if (cursor > 5) {
    for (int i = 0 + (cursor - 5); i < nums; i++) {
      if (cursor == i) {
        DISP.setTextColor(BGCOLOR, FGCOLOR);
      }
      DISP.printf(" %-19d\n", i);
      DISP.setTextColor(FGCOLOR, BGCOLOR);
    }
  } else {
    for (
      int i = 0; i < nums; i++) {
      if (cursor == i) {
        DISP.setTextColor(BGCOLOR, FGCOLOR);
      }
      DISP.printf(" %-19d\n", i);
      DISP.setTextColor(FGCOLOR, BGCOLOR);
    }
  }
}
#endif

void switcher_button_proc() {
  if (rstOverride == false) {
    if (check_next_press()) {
      isSwitching = true;
      current_proc = 1;
    }
  }
}

      bool check_select_press() {
#if defined(KB)
        M5Cardputer.update();
        if (M5Cardputer.Keyboard.isKeyPressed(KEY_ENTER) || M5Cardputer.Keyboard.isKeyPressed('/')) {
          dimtimer();
          return true;
        }
#elif defined(DIAL)
  M5Dial.update();
  auto t = M5Dial.Touch.getDetail();
  if (t.isPressed()) {
    dimtimer();
    return true;
  }
#else
  if (digitalRead(M5_BUTTON_HOME) == LOW) {
    dimtimer();
    return true;
  }
#endif
        return false;
      }

// Tap the power button from pretty much anywhere to get to the main menu
bool check_m_press() {
#if defined(AXP)
  if (M5.Axp.GetBtnPress()) {
#endif
#if defined(KB)
        M5Cardputer.update();
    if (M5Cardputer.Keyboard.isKeyPressed(',') || M5Cardputer.Keyboard.isKeyPressed('`')) {
#endif
#if defined(DIAL)
      M5Dial.update();
      auto t = M5Dial.Touch.getDetail();
      if (t.isHolding()) {
#endif
#if defined(M5_BUTTON_MENU)
        if (digitalRead(M5_BUTTON_MENU) == LOW) {
#endif
          return true;
          dimtimer();
        }
        return false;
    }
