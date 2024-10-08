/**
 * @file tag_o_matic.h
 * @author Rennan Cockles (https://github.com/rennancockles)
 * @brief Read and Write RFID tags
 * @version 0.1
 * @date 2024-07-17
 */

#include <IRrecv.h>
//#define IrRx 1
//#include "core/globals.h"


class IrRead {
public:
	IRrecv irrecv = IRrecv(PortBpinIN);


	/////////////////////////////////////////////////////////////////////////////////////
	// Constructor
	/////////////////////////////////////////////////////////////////////////////////////
	IrRead();

	///////////////////////////////////////////////////////////////////////////////////
	// Arduino Life Cycle
	///////////////////////////////////////////////////////////////////////////////////
	void setup();
	void loop();

private:
	bool _read_signal = false;
	decode_results results;
	uint16_t* rawcode;
	int raw_data_len;
	int signals_read = 0;
	String strDeviceContent = "";

	/////////////////////////////////////////////////////////////////////////////////////
	// Display functions
	/////////////////////////////////////////////////////////////////////////////////////
  void cls();
  void display_banner();
  void display_btn_options();
	void dump_signal_details();

	/////////////////////////////////////////////////////////////////////////////////////
	// Operations
	/////////////////////////////////////////////////////////////////////////////////////
  void begin();
	void read_signal();
	void save_device();
	void save_signal();
	void discard_signal();
	void append_to_file_str(String btn_name, String signal_code);
  bool write_file(String filename);
  String parse_signal();
};
