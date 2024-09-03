#pragma once
#include <Arduino.h>
/*
* This file is dedecated for the SchreiBox CLI
*/

// for reporting events to serial with File and line
#define __FILENAME__ (strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 : __FILE__)
#define errorMsg(messgage) Serial.print(messgage); \
Serial.print(" at "); \
Serial.print(__FILENAME__); \
Serial.print(":"); Serial.println(__LINE__);

struct CLIOption {
	String commandDescription = "";
	String command = "";
	void(*function)();
};

namespace SchreiBoxCLIInternal {
#ifndef SIMPLE_CLI_LOW_MEM




	String WelcomeBanner = R""""(

 _____ _                 _        _____  _     _____ 
/  ___(_)               | |      /  __ \| |   |_   _|
\ `--. _ _ __ ___  _ __ | | ___  | /  \/| |     | |  
 `--. \ | '_ ` _ \| '_ \| |/ _ \ | |    | |     | |  
/\__/ / | | | | | | |_) | |  __/ | \__/\| |_____| |_ 
\____/|_|_| |_| |_| .__/|_|\___|  \____/\_____/\___/ 
                  | |                                
                  |_|                               
                                                                     
                                                                    

		)"""";

	String GoodBye = R""""(


 _____                 _ _                
|  __ \               | | |               
| |  \/ ___   ___   __| | |__  _   _  ___ 
| | __ / _ \ / _ \ / _` | '_ \| | | |/ _ \
| |_\ \ (_) | (_) | (_| | |_) | |_| |  __/
 \____/\___/ \___/ \__,_|_.__/ \__, |\___|
                                __/ |     
                               |___/      

		)"""";
#else
	String GoodBye = "Goodbye";
	String WelcomeBanner = "Simple CLI";
#endif // SIMPLE_CLI_MIN_MEM

}

class SimpleCLI {
public:
	SimpleCLI(HardwareSerial* serial, CLIOption* CLIOptionArray, const uint32_t CLIOptionArrayLength);

	/// <summary>
	/// checks if the CLI should be started. WARNING: programm execution remains in this function until CLI  is exited.
	/// </summary>
	void checkCLI();

	/// <summary>
	/// function for exiting SchreiBoxCLI
	/// </summary>
	void exitCLIFunc();

	/// <summary>
	/// Change CLIOptions
	/// </summary>
	/// <param name="CLIOptionArray"></param>
	/// <param name="CLIOptionArrayLength"></param>
	void updateCLIOptions(CLIOption* CLIOptionArray, const uint32_t CLIOptionArrayLength);

	/// <summary>
	/// sets a function that should be executed every cycle. Function MUST be activated seperatly. WARNING: if delays are used CLI may not responed correctly.
	/// </summary>
	/// <param name="CycleFunction"></param>
	void setCycleFunction(void(*CycleFunction)());

	/// <summary>
	/// Activate or Deactivate CycleFunction. If no CycleFunction is set, bool returns false. 
	/// </summary>
	/// <param name="activate"></param>
	/// <returns></returns>
	bool activateCycleFunction(bool activate);

	/// <summary>
	/// activates or deactivates CLI option
	/// </summary>
	/// <param name="active"></param>
	/// <param name="numberOfOption"></param>
	void activateCLIOption(bool active, int numberOfOption);

	/// <summary>
	/// activates or deactivates CLI option
	/// </summary>
	/// <param name="active"></param>
	/// <param name="commandOfOption"></param>
	void activateCLIOption(bool active, String commandOfOption);

private:
	bool CLIActive = false; // true if CLI active
	HardwareSerial* serial; 
	CLIOption* CLIOptionArray;
	uint32_t CLIOptionArrayLength = 0;
	void(*executeEveryCycle)() = NULL;	// ptr to CycleFunction
	bool executeEveryCycleActive = false; // if true executes CycleFunction

	bool* ActiveCLIOptions = NULL;	// ptr to array that store what CLI options are active
	uint32_t ActiveCLIOptionsLength = 0; 

	/// <summary>
	/// Clears serial buffer
	/// </summary>
	void clearSerial();

	/// <summary>
	/// Resolves and executes CLI command
	/// </summary>
	/// <param name="cmd"></param>
	void ExecuteCLICommand(String cmd);

	/// <summary>
	/// retrives a string from serial
	/// </summary>
	String getString();

	/// <summary>
	/// Prints Cmd Options
	/// </summary>
	void CLIPrintCmdOptions();

	/// <summary>
	/// checks if Option at optionnumber is active
	/// </summary>
	/// <param name="OptionNumber"></param>
	/// <returns></returns>
	bool CLIOptionAvalable(int OptionNumber);

	/// <summary>
	/// resizes array and initialises all elements to true
	/// </summary>
	/// <param name="newSize"></param>
	void resizeActiveOptionsArray(uint32_t newSize);
};






