/*
* Licence:
* THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, 
* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES 
* OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
* NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
* HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
* WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
* FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
* OTHER DEALINGS IN THE SOFTWARE.
*/
#include "SimpleCLI.h"

namespace SchreiBoxCLIInternal {
#ifndef SIMPLE_CLI_LOW_MEM
	const String WelcomeBanner = R""""(

 _____ _                 _        _____  _     _____ 
/  ___(_)               | |      /  __ \| |   |_   _|
\ `--. _ _ __ ___  _ __ | | ___  | /  \/| |     | |  
 `--. \ | '_ ` _ \| '_ \| |/ _ \ | |    | |     | |  
/\__/ / | | | | | | |_) | |  __/ | \__/\| |_____| |_ 
\____/|_|_| |_| |_| .__/|_|\___|  \____/\_____/\___/ 
                  | |                                
                  |_|                               
                                                                     
                                                                    

		)"""";

	const String GoodBye = R""""(


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
	const String GoodBye = "Goodbye";
	const String WelcomeBanner = "Simple CLI";
#endif // SIMPLE_CLI_MIN_MEM


}

/// <summary>
/// checks if the CLI should be started. WARNING: programm execution remains in this function until CLI  is exited.
/// </summary>
void SimpleCLI::checkCLI() {
	// if something was sent CLI activates
	if (serial->available()) {
		CLIActive = true;
		delay(10);
		clearSerial();
	}

	if (CLIActive == false) return;

	serial->println("Welcome to: ");
	delay(500);
	serial->print(SchreiBoxCLIInternal::WelcomeBanner);
	delay(1000);
	serial->println();
	// CLI Loop
	while (CLIActive) {
		serial->println();
		serial->println();
		CLIPrintCmdOptions();
		serial->println("\nType command: ");
		do {
			if (executeEveryCycleActive) {
				// execute cycleFunction
				executeEveryCycle();
			}
		} while (!serial->available());
		ExecuteCLICommand(getString());
	}

	serial->println("Exiting SchreiBox CLI...");
	delay(500);
	serial->println("Exited");
	delay(500);
	serial->println(SchreiBoxCLIInternal::GoodBye);
	return;
}

/// <summary>
/// function for exiting SchreiBoxCLI
/// </summary>
void SimpleCLI::exitCLIFunc() {
	CLIActive = false;
	return;
}

/// <summary>
/// Clears serial buffer
/// </summary>
void SimpleCLI::clearSerial() {
	while (serial->available()) {
		char tmp = serial->read();
	}
	return;
}

/// <summary>
/// Resolves and executes CLI command
/// </summary>
/// <param name="cmd"></param>
void SimpleCLI::ExecuteCLICommand(String cmd) {
	if (cmd == "") return;

	serial->println("\n");

	// search for option
	for (size_t i = 0; i < CLIOptionArrayLength; i++) {
		if (CLIOptionArray[i].command.equals(cmd)) {
			// execute option
			if (!CLIOptionAvalable(i)) continue;

			serial->println("Executing command...");
			CLIOptionArray[i].function();
			serial->println("Done.");
			return;
		}
		else if (cmd.equals("exit")) {
			SimpleCLI::exitCLIFunc();
		}
	}
	serial->print("ERROR: command not recognised \"");
	serial->print(cmd);
	serial->println("\"");
	return;
}

/// <summary>
/// retrives a string from serial
/// </summary>
String SimpleCLI::getString() {
	String readString = "";
	while (serial->available()) {
		delay(2);  //delay to allow byte to arrive in input buffer
		char c = serial->read();
		readString += c;
	}

	readString.trim();
	return readString;
}

/// <summary>
/// Prints Cmd Options
/// </summary>
void SimpleCLI::CLIPrintCmdOptions() {
	serial->println("Avalable Commands:");
	for (size_t i = 0; i < CLIOptionArrayLength; i++) {
		if (!CLIOptionAvalable(i)) continue;

		serial->print(CLIOptionArray[i].command);
		serial->print(": ");
		serial->println(CLIOptionArray[i].commandDescription);
	}
	serial->println("exit: exits CLI");
	return;
}

/// <summary>
/// Change CLIOptions
/// </summary>
/// <param name="CLIOptionArray"></param>
/// <param name="CLIOptionArrayLength"></param>
void SimpleCLI::updateCLIOptions(CLIOption* CLIOptionArray, const uint32_t CLIOptionArrayLength) {
	SimpleCLI::CLIOptionArray = CLIOptionArray;
	SimpleCLI::CLIOptionArrayLength = CLIOptionArrayLength;

	return;
}

/// <summary>
/// sets a function that should be executed every cycle. Function MUST be activated seperatly. WARNING: if delays are used CLI may not responed correctly.
/// </summary>
/// <param name="CycleFunction"></param>
void SimpleCLI::setCycleFunction(void(*CycleFunction)()) {
	executeEveryCycle = CycleFunction;
	return;
}

/// <summary>
/// Activate or Deactivate CycleFunction. If no CycleFunction is set, bool returns false. 
/// </summary>
/// <param name="activate"></param>
/// <returns></returns>
bool SimpleCLI::activateCycleFunction(bool activate) {
	if (executeEveryCycle == NULL) {
		// cycle function not defined
		executeEveryCycleActive = false;
		errorMsg("ERROR: CycleFunction not defined");
		return false; 
	}

	executeEveryCycleActive = activate;
	return true;
}

/// <summary>
/// checks if Option at optionnumber is active
/// </summary>
/// <param name="OptionNumber"></param>
/// <returns></returns>
bool SimpleCLI::CLIOptionAvalable(int OptionNumber) {
	if (OptionNumber >= ActiveCLIOptionsLength || OptionNumber < 0) {
		// error CLIOption out of bounds
		errorMsg("ERROR: Array access out of bounds");
		return false;
	}
	return ActiveCLIOptions[OptionNumber];
}

/// <summary>
/// activates or deactivates CLI option
/// </summary>
/// <param name="active"></param>
/// <param name="numberOfOption"></param>
void SimpleCLI::activateCLIOption(bool active, int numberOfOption) {
	if (numberOfOption >= ActiveCLIOptionsLength || numberOfOption < 0) {
		// error CLIOption out of bounds
		errorMsg("ERROR: Array access out of bounds");
		return;
	}
	ActiveCLIOptions[numberOfOption] = active;

}

/// <summary>
/// activates or deactivates CLI option
/// </summary>
/// <param name="active"></param>
/// <param name="commandOfOption"></param>
void SimpleCLI::activateCLIOption(bool active, String commandOfOption) {
	// search for option
	for (size_t i = 0; i < CLIOptionArrayLength; i++) {
		if (CLIOptionArray[i].command.equals(commandOfOption)) {
			ActiveCLIOptions[i] = active;
			return;
		}
	}
	errorMsg("ERROR: CLI option not found");
	return;
}

SimpleCLI::SimpleCLI(HardwareSerial* serial, CLIOption* CLIOptionArray, const uint32_t CLIOptionArrayLength) :
	serial(serial),
	CLIOptionArray(CLIOptionArray),
	CLIOptionArrayLength(CLIOptionArrayLength) {

	// init ActiveCLIOptions
	ActiveCLIOptionsLength = CLIOptionArrayLength;
	ActiveCLIOptions = new bool[CLIOptionArrayLength];
	for (size_t i = 0; i < CLIOptionArrayLength; i++) {
		ActiveCLIOptions[i] = true;
	}
}

/// <summary>
/// resizes array and initialises all elements to true
/// </summary>
/// <param name="newSize"></param>
void SimpleCLI::resizeActiveOptionsArray(uint32_t newSize) {
	delete[] ActiveCLIOptions;
	ActiveCLIOptionsLength = newSize;
	ActiveCLIOptions = new bool[newSize];
	return;
}