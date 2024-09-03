/*
 Name:		SimpleArduinoCLI.ino
 Created:	03.09.2024 22:35:03
 Author:	Raphael
*/

#include "SimpleCLI/SimpleCLI.h"

void exitCLIFunc();

const uint32_t CLIOptionArrayLength = 1;
CLIOption CLIOptionArray[CLIOptionArrayLength] = {
    //  Name               | cmd       | function
    {   "Exit CLI",         "exit",      exitCLIFunc }
};
SimpleCLI CLI(&Serial, CLIOptionArray, CLIOptionArrayLength);

void exitCLIFunc() {
    CLI.exitCLIFunc();
}

// the setup function runs once when you press reset or power the board
void setup() {

}

// the loop function runs over and over again until power down or reset
void loop() {
  
}
