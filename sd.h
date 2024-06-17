
bool sdcardMounted = false;
#if defined(SDCARD)
  #include <FS.h>
  #include <SD.h>
  #include <SPI.h>
  
  #if defined(CARDPUTER)
    SPIClass* sdcardSPI = NULL;
  #else
    SPIClass sdcardSPI;
  #endif
  SemaphoreHandle_t sdcardSemaphore;

  void appendToFile(fs::FS& fs, const char* path, const char* text) {
    if (xSemaphoreTake(sdcardSemaphore, portMAX_DELAY) == pdTRUE) {
      File file = fs.open(path, FILE_APPEND);
      if (!file) {
        Serial.println("Failed to open file for appending");
        xSemaphoreGive(sdcardSemaphore);
        return;
      }
      Serial.printf("Appending text '%s' to file: %s\n", text, path);
      if (file.println(text)) {
        Serial.println("Text appended");
      } else {
        Serial.println("Append failed");
      }
      file.close();
      xSemaphoreGive(sdcardSemaphore);
    }
  }
  
String choosefile(fs::FS &fs, const char *dirname, uint8_t number) {
  uint8_t numberindex=0;
  // scrolling menu

  File root = fs.open(dirname);
  if (!root) {
    Serial.println("Failed to open directory");
    return "error";
  }
  if (!root.isDirectory()) {
    Serial.println("Not a directory");
    return "error";
  }

  File file = root.openNextFile();
  while (file) {
    if (file.isDirectory()) {
    } else {
      if (numberindex == number)
      {
      Serial.print("  FILE: ");
      Serial.print(file.name());
      Serial.print("  SIZE: ");
      Serial.println(file.size());
        return file.name();
      }
      numberindex++;
    }
    file = root.openNextFile();
  }
  return "false";
}

  String readFile(fs::FS &fs, const char * path){
    Serial.printf("Reading file: %s\n", path);

    File file = fs.open(path);
    if(!file){
        Serial.println("Failed to open file for reading");
        return "false";
    }
    String rturnstr;
    Serial.print("Read from file: ");
    while(file.available()){
        //Serial.write(file.read());
        //rturnstr = rturnstr + String(file.read());
        rturnstr += (char)file.read();
    }
    file.close();
    return rturnstr;
}
#endif

bool setupSdCard() {
#if defined(SDCARD)
  sdcardSemaphore = xSemaphoreCreateMutex();
  #if defined (CARDPUTER)
    sdcardSPI = new SPIClass(FSPI);
    sdcardSPI->begin(SD_CLK_PIN, SD_MISO_PIN, SD_MOSI_PIN, SD_CS_PIN);
  #else
    sdcardSPI.begin(SD_CLK_PIN, SD_MISO_PIN, SD_MOSI_PIN, SD_CS_PIN); // start SPI communications
  #endif

  delay(10);
  
  #if defined (CARDPUTER)
    if (!SD.begin(SD_CS_PIN, *sdcardSPI)) {
      sdcardSPI->end();
  #else
    if (!SD.begin(SD_CS_PIN, sdcardSPI)) { //excluded * -> poiter indicator -
    sdcardSPI.end(); // Closes SPI connections and release pin header.
  #endif
    Serial.println("Failed to mount SDCARD");
    
    return false;
  } else {
    Serial.println("SDCARD mounted successfully");
    sdcardMounted = true;
    return true;
  }
#else
  return false;
#endif
}

#if defined(SDCARD)
  #ifndef CARDPUTER
    void ToggleSDCard()
    {
      rstOverride = true;
      isSwitching = true;
      uint8_t cardType = NULL;
      uint64_t cardSize = NULL;
      current_proc=1;
      DISP.fillScreen(BGCOLOR);
      DISP.setCursor(5, 1);
      if (sdcardMounted == true) {
        sdcardMounted = false;
        uint8_t cardType = 0;
        uint64_t cardSize = 0;
        SD.end();
        sdcardSPI.end(); // Closes SPI connections and release pins.
        DISP.println("SD Card Unmouted..");
        DISP.println("pin header released.");
        Serial.println("SD Card Unmounted...");
      } else {
        sdcardSPI.begin(SD_CLK_PIN, SD_MISO_PIN, SD_MOSI_PIN, SD_CS_PIN);
        delay(10);

        if (!SD.begin(SD_CS_PIN, sdcardSPI)) {
          Serial.println("Card Mount Failed");
          DISP.println("Card Mount Failed");
          sdcardSPI.end();

        } else {
          // 
          sdcardMounted = true;
          uint8_t cardType = SD.cardType();
          if (cardType == CARD_NONE) {
            DISP.println("None SD Card");
            Serial.println("None SD Card");
          }
          DISP.print("SD Card Type: ");
          if (cardType == CARD_MMC) {
            DISP.println("MMC");
            Serial.println("MMC");
          } else if (cardType == CARD_SD) {
            DISP.println("SDSC");
            Serial.println("SDSC");
          } else if (cardType == CARD_SDHC) {
            DISP.println("SDHC");
            Serial.println("SDHC");
          } else {
            DISP.println("UNKNOWN");
            Serial.println("UNKNOWN");
          }
          uint64_t cardSize = SD.cardSize() / (1024 * 1024);
          DISP.printf("SD Card Size: %lluMB\n", cardSize);
          Serial.printf("SD Card Size: %lluMB\n", cardSize);
        }
      }
      delay(1500);
    }
  #endif
#endif


#ifdef SDCARD
#ifdef CARDPUTER
String Inputfilename(String defaultname){
  DISP.fillScreen(BGCOLOR);
  DISP.setSwapBytes(true);
  DISP.setTextSize(MEDIUM_TEXT);
  DISP.setTextColor(BGCOLOR, FGCOLOR);
  DISP.setCursor(0, 0);
  DISP.println("  File name  ");
  DISP.setTextSize(TINY_TEXT);
  DISP.setTextColor(FGCOLOR, BGCOLOR);
  DISP.setTextSize(SMALL_TEXT);
  uint8_t ssidTextCursorY = DISP.getCursorY();
  String currentname = String(defaultname.c_str());
  DISP.printf("%s", currentname.c_str());
  bool ssid_ok = false;

  while(!ssid_ok){
    M5Cardputer.update();
    if(M5Cardputer.Keyboard.isChange() && M5Cardputer.Keyboard.isPressed()) {
      Keyboard_Class::KeysState status = M5Cardputer.Keyboard.keysState();
      if(status.del) {
        currentname.remove(currentname.length() - 1);
      }
      if(status.enter) {
        ssid_ok = true;
      }
      if(currentname.length() >= 32) {
        continue;
      }
      for(auto i : status.word) {
        if(i != '?' && i != '$' && i != '\"' && i != '[' && i != '\\' && i != ']' && i != '+'){
          currentname += i;
        }
      }
      DISP.fillRect(0, ssidTextCursorY, DISP.width(), DISP.width()- ssidTextCursorY, BLACK);
      DISP.setCursor(0, ssidTextCursorY);
      DISP.printf("%s", currentname.c_str());
    }
  }
  return currentname;
}
#else
String Inputfilename(String defaultname){
  uint8_t i=0;
  String name;
  while (1)
  {
    i++;
    name =  defaultname + String(i) + ".txt";
    if(!(readFile(SD, name.c_str()) == "false"))
    {
      return String(i);
    }
  }
}
#endif
#endif