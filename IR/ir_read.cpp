/**
 * @file ir_read.cpp
 * @author @im.nix (https://github.com/Niximkk)
 * @author Rennan Cockles (https://github.com/rennancockles)
 * @brief Read IR signals
 * @version 0.2
 * @date 2024-08-03
 */

#include <IRrecv.h>
#include "../Defines.h"
#include "ir_read.h"
#include "../globalfunc.h"
//#include "core/globals.h"
//#include "core/mykeyboard.h"
//#include "core/display.h"
//#include "core/sd_functions.h"
//#include "core/settings.h"

/* Dont touch this */
#define MAX_RAWBUF_SIZE 300
#define IR_FREQUENCY 38000
#define DUTY_CYCLE 0.330000


IrRead::IrRead() {
    setup();
}

void IrRead::setup() {
    irrecv.enableIRIn();

    //Checks if IrRx pin is properly set
    //const std::vector<std::pair<std::string, int>> pins = IR_RX_PINS;
    //int count=0;
    //for (auto pin : pins) {
    //    if(pin.second==IrRx) count++; 
    //}
    //if(count==0) gsetIrRxPin(true); // Open dialog to choose IrRx pin
    
    pinMode(PortBpinIN, INPUT);
    begin();
    return loop();
}

void IrRead::loop() {
    while(1) {
		if(check_m_press())
		{
			current_proc = 24;
			isSwitching = true;
			delay(250);
			break;
		}

        if (check_select_press())
        {save_device();}
        if (check_next_press())
        {save_signal();}
        //if (switcher_button_proc)
        //{discard_signal();}

        read_signal();
    }
}

void IrRead::begin() {
    _read_signal = false;

    display_banner();
    DISP.println("Waiting for signal...");
    DISP.println("");
    display_btn_options();

    delay(300);
}

void IrRead::cls() {
    //drawMainBorder();
	DISP.fillScreen(BGCOLOR);
    DISP.setCursor(0, 0);
    DISP.setTextColor(FGCOLOR, BGCOLOR);
}

void IrRead::display_banner() {
    cls();
    DISP.setTextSize(MEDIUM_TEXT);
    DISP.println("IR_AH Receive");

    DISP.setTextSize(TINY_TEXT);
    DISP.println("Signals captured: " + String(signals_read));
    DISP.println("");
}

void IrRead::display_btn_options() {
    DISP.println("");
    DISP.println("");
    if (_read_signal) {
        DISP.println("Press [PREV] to discard signal");
        DISP.println("Press [NEXT] to save signal");
    }
    if (signals_read > 0) {
	    DISP.println("Press [OK]   to save device");
    }
}

void IrRead::dump_signal_details() {
    DISP.print("  HEX: 0x");
    DISP.println(results.value, HEX);
}

void IrRead::read_signal() {
    if (_read_signal || !irrecv.decode(&results)) return;

    _read_signal = true;

    display_banner();
    dump_signal_details();
    display_btn_options();

    delay(500);
}

void IrRead::discard_signal() {
    if (!_read_signal) return;

    irrecv.resume();
    begin();
}

void IrRead::save_signal() {
    if (!_read_signal) return;
#ifdef SD
    String btn_name = Inputfilename("Btn"+String(signals_read));

    append_to_file_str(btn_name, parse_signal());
#endif
    signals_read++;

    discard_signal();
    delay(100);
}

String IrRead::parse_signal() {
    rawcode = new uint16_t[MAX_RAWBUF_SIZE];
    memset(rawcode, 0, MAX_RAWBUF_SIZE * sizeof(uint16_t));
    raw_data_len = results.rawlen;
    String signal_code = "";

    /* I HAVE NO FUCKING IDEA WHY WE NEED TO MULTIPLY BY 2, BUT WE DO. */
    for (int i = 1; i < raw_data_len; i++) {
        signal_code += String(results.rawbuf[i] * 2) + " ";
        rawcode[i - 1] = results.rawbuf[i] * 2;
    }
    delete[] rawcode;
    rawcode = nullptr;
    signal_code.trim();

    return signal_code;
}

void IrRead::append_to_file_str(String btn_name, String signal_code) {
    strDeviceContent += "#\n";
    strDeviceContent += "name: " + btn_name + "\n";
    strDeviceContent += "type: raw\n";
    strDeviceContent += "frequency: " + String(IR_FREQUENCY) + "\n";
    strDeviceContent += "duty_cycle: " + String(DUTY_CYCLE) + "\n";
    strDeviceContent += "data: " + String(signal_code) + "\n";
}

void IrRead::save_device() {
    if (signals_read == 0) return;

#ifdef SD
    String filename = Inputfilename("MyDevice");
#endif
    display_banner();

#ifdef SD
    if (write_file(filename)) {
        //displaySuccess("File saved.");
        signals_read = 0;
        strDeviceContent = "";
    }
    else {
        //displayError("Error writing file.");
    }
#endif
    delay(1000);
    begin();
}

bool IrRead::write_file(String filename) {
#ifdef SD
    FS *fs;
    if(setupSdCard()) fs=&SD;
    //else {
    //    if(checkLittleFsSize()) fs=&LittleFS;
    //    else {
    //        return false;
     //   }
    //}

    if (!(*fs).exists("/BruceIR")) (*fs).mkdir("/BruceIR");
    if ((*fs).exists("/BruceIR/" + filename + ".ir")) {
        int i = 1;
        filename += "_";
        while((*fs).exists("/BruceIR/" + filename + String(i) + ".ir")) i++;
        filename += String(i);
    }
    File file = (*fs).open("/BruceIR/"+ filename + ".ir", FILE_WRITE);

    if(!file) {
        return false;
    }

    file.println("Filetype: Shark IR File (same as Bruce)");
    file.println("Version 1");
    file.println("#");
    file.println("# " + filename);
    file.print(strDeviceContent);

    file.close();
#endif
    delay(100);
    return true;
}
