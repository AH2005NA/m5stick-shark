void TransmitIR(uint16_t RAWdata[], uint16_t freq);
uint64_t RecIR(void)
{
  delay(100);
  IRrecv irrecv(IRREC);
  decode_results results;
  irrecv.enableIRIn();
  while(1)
  {
    if (irrecv.decode(&results))
    {
      uint16_t *raw_array = resultToRawArray(&results);
      // Print the raw received IR data to the serial monitor
      Serial.println("Raw IR data:");
      for(uint8_t i=0; i<getCorrectedRawLength(&results); i++)
      {
        Serial.print(String(raw_array[i], HEX));
        Serial.println(", ");
      }
      Serial.print("data: ");
      serialPrintUint64(results.value, HEX);
      Serial.println("");
      while(digitalRead(M5_BUTTON_RST) == LOW)
      {
      TransmitIR(raw_array, 38000);
      }
      irrecv.resume();
      return results.value;
      //return results.value;
      // Enable the IR receiver for the next data
    }
    //delay(100);
  }
}

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