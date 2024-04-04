//#define DISP M5.Lcd
//DISP.height()
//DISP.width()

//uint16_t displayBuffer[SCREEN_WIDTH][SCREEN_HEIGHT];
void setTextSize(uint8_t TXT_size)
{
  DISP.setTextSize(TXT_size);
  //Serial.printf("setTextSiz");
  //Serial.write(TXT_size);
}

void fillScreen(uint16_t Backgroud)
{
  DISP.fillScreen(Backgroud);
  //Serial.printf("fillScreen");
  //Serial.write(Backgroud&0xff00);
  //Serial.write(Backgroud&0x00ff);
}

void setCursor(uint8_t x, uint8_t y, uint8_t fond)
{
  DISP.setCursor(x, y, fond);
  //Serial.write(0xff);
  //Serial.printf("setCursor_");
  //Serial.write(x);
  //Serial.write(y);
  //Serial.printf("print-_-_-");
  //Serial.print("Hallo");
  //Serial.write(0x00);
}

void setTextColor(uint16_t BGpCOLOR, uint16_t FGpCOLOR)
{
  DISP.setTextColor(BGpCOLOR, FGpCOLOR);
  //Serial.write(0xff);
  //Serial.printf("setTextCol");
  //Serial.write(BGpCOLOR&0xff00);
  //Serial.write(BGpCOLOR&0x00ff);
  //Serial.write(FGpCOLOR&0xff00);
  //Serial.write(FGpCOLOR&0x00ff);
}

void printf(const char *arg, char* Text)
{
  DISP.printf(arg, Text);
  //Serial.write(0xff);
  //Serial.printf("printf_-_-");
  //Serial.write(arg);
  //Serial.write(0x00);
  //Serial.write(Text);
  //Serial.write(0x00);
}

void print(String tEXT)
{
  DISP.print(tEXT); 
  //Serial.write(0xff);
  //Serial.printf("print-_-_-");
  //Serial.print(tEXT);
  //Serial.write(0x00);
}//