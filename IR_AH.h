#include "esp32-hal.h"


uint16_t RawIRBuffer[255];
uint8_t LenRAWIR;

void TransmitIR(uint16_t RAWdata[], uint16_t freq)
{
  IRsend irsender(IRLED);
  irsender.begin();
  int Numpairs = sizeof(RAWdata);
  irsender.sendRaw(RAWdata, Numpairs, freq);
  //uint16_t Adress = 0xdadd;
  //uint16_t code = 0x4444;
  //irsender.sendNEC(Adress, 16, true);
  //irsender.sendNEC(code, 16, false);
  //IRsend irsend(IRLED);
  //irsend.sendNEC(0xD11F363F);
  //irsend.sendRaw(0xD11F, (/*numpairs*/4 * 2) , /*freq*/38000);
  //irsend.sendRaw(0x363F, (/*numpairs*/4 * 2) , /*freq*/38000);
  //digitalWrite(IRLED, M5LED_OFF);
}


uint8_t RecIR(decode_results *results)
{
      uint16_t count = results->rawlen;
      if (count>255)
      {
        count=255;
      }
      //uint16_t *raw_array = resultToRawArray(&results);
      // Print the raw received IR data to the serial monitor
      Serial.println("Raw IR data:");
          Serial.print(count);
      Serial.println(":");
      //serialPrintUint64(results.value, 16);
      
      for (uint8_t i = 1; i < count; i++) {
        if (i % 100 == 0)
          yield();  // Preemptive yield every 100th entry to feed the WDT.
        if (i & 1) {
          RawIRBuffer[i] = results->rawbuf[i] * kRawTick;
          Serial.print(RawIRBuffer[i], HEX);
        } else {
          Serial.print(", ");
          RawIRBuffer[i] = (uint32_t) results->rawbuf[i] * kRawTick;
          Serial.print(RawIRBuffer[i], HEX);
        }
      }
      return 1;//results.value;
      //return results.value;
      // Enable the IR receiver for the next data
}