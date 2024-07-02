#include "esp32-hal.h"


uint16_t RawIRBuffer[1024];
int LenRAWIR;
uint64_t reslt;

void TransmitIR(uint16_t RAWdata[], uint8_t decodetype, uint16_t Numpairs, uint16_t freq)
{
  delay_ten_us(30500);
  IRsend irsender(IRLED);
  irsender.begin();
  digitalWrite(IRLED, M5LED_OFF);
    Serial.print(decodetype);
    //Serial.print(reslt);
  if (decodetype == 0) {
    irsend.sendRaw(RAWdata, Numpairs, 38000);
    //irsender.sendRaw(RAWdata, Numpairs/*2*/, freq);
    Serial.print(Numpairs);
    Serial.printf("WMW");
    Serial.print(freq);
  } else if (decodetype == 1) {
    irsend.sendNEC(reslt);
  } else if (decodetype == 2) {
    irsend.sendSony(reslt);
  } else if (decodetype == 3) {
    irsend.sendRC5(reslt);
  } else if (decodetype == 4) {
    //irsend.sendRC5X(reslt);
  } else if (decodetype == 5) {
    irsend.sendRCMM(reslt);
  } else if (decodetype == 6) {
    //irsend.sendPANASONIC(reslt);
  }
  if (Numpairs == 0)
  {
    Numpairs = sizeof(RAWdata);
  }

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


uint8_t RecIR(decode_results *result)
{
  uint8_t decoding;

      //enRAWIR = getCorrectedRawLength(&result);
      //int16_t *raw_array = resultToRawArray(&result);
      // Print the raw received IR data to the serial monitor
      Serial.println("Raw IR data:");
      Serial.print(LenRAWIR);
      Serial.println(":");
      //serialPrintUint64(results.value, 16);
      
      //for (uint8_t i = 1; i < LenRAWIR; i++) {
      //  if (i % 100 == 0)
      //    yield();  // Preemptive yield every 100th entry to feed the WDT.
      //  if (i & 1) {
      //    RawIRBuffer[i] = results->rawbuf[i] * kRawTick;
      //    Serial.print(RawIRBuffer[i], HEX);
      //  } else {
      //    Serial.print(", ");
      //    RawIRBuffer[i] = (uint32_t) results->rawbuf[i] * kRawTick;
      //    Serial.print(RawIRBuffer[i], HEX);
      //  }
      //}
    decoding = 0;
    /*
  if (results->decode_type == UNKNOWN) {
  } else if (results->decode_type == NEC) {
    Serial.print("Decoded NEC: ");
    decoding = 1;
  } else if (results->decode_type == SONY) {
    Serial.print("Decoded SONY: ");
    decoding = 2;
  } else if (results->decode_type == RC5) {
    Serial.print("Decoded RC5: ");
    decoding = 3;
  } else if (results->decode_type == RC5X) {
    Serial.print("Decoded RC5X: ");
    decoding = 4;
  } else if (results->decode_type == RC6) {
    Serial.print("Decoded RC6: ");
    decoding = 5;
  } else if (results->decode_type == RCMM) {
    Serial.print("Decoded RCMM: ");
    decoding = 6;
  } else if (results->decode_type == PANASONIC) {
    Serial.print("Decoded PANASONIC - Address: ");
    decoding = 7;
    Serial.print(results->address, HEX);
    Serial.print(" Value: ");
    decoding = 8;
  } else if (results->decode_type == LG) {
    Serial.print("Decoded LG: ");
    decoding = 9;
  } else if (results->decode_type == JVC) {
    Serial.print("Decoded JVC: ");
    decoding = 10;
  } else if (results->decode_type == AIWA_RC_T501) {
    Serial.print("Decoded AIWA RC T501: ");
    decoding = 11;
  } else if (results->decode_type == WHYNTER) {
    Serial.print("Decoded Whynter: ");
    decoding = 12;
  } else if (results->decode_type == NIKAI) {
    Serial.print("Decoded Nikai: ");
    decoding = 13;
  }
  */
  reslt = (uint64_t)result->value;
  serialPrintUint64(reslt, 16);
    Serial.print("decoding");
    Serial.print(decoding);
  return decoding;
}