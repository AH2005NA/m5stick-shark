
uint64_t RecIR(void)
{/*
  IRrecv irrecv(26);
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
        Serial.println(String(raw_array[i], HEX));
      }
      return results.value;
      // Enable the IR receiver for the next data
      irrecv.resume();
    }
    //delay(100);
  }*/
}

void TransmitIR(uint16_t RAWdata[])
{
    uint16_t Adress = 0xdadd;
    uint16_t code = 0x4444;
    IRsend irsender(IRLED);
    irsender.begin();
    int Numpairs = sizeof(RAWdata);
    irsender.sendRaw(RAWdata, Numpairs, 38000);
  //irsender.sendNEC(Adress, 16, true);
  //irsender.sendNEC(code, 16, false);
  //IRsend irsend(IRLED);
  //irsend.sendNEC(0xD11F363F);
  //irsend.sendRaw(0xD11F, (/*numpairs*/4 * 2) , /*freq*/38000);
  //irsend.sendRaw(0x363F, (/*numpairs*/4 * 2) , /*freq*/38000);
  //digitalWrite(IRLED, M5LED_OFF);
}