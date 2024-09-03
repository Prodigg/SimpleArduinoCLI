# how to install 

download the zip file in releses
and install it with arduinoIDE.
Then it can be included with `#include <SimpleCLI.h>` into a project

# documentation

## using SimpleCLI on lower end microcontrollers

When using SimpleCLI on lower end microcontrollers like ArduinoUno memory usage is high. to medagate this use the following line:
```
#define SIMPLE_CLI_LOW_MEM
```
This strips down unnessesary data that is used for appearance.

## quick setup

After installing and including the Libary initialise the SimpleCLI Options like so:
```
const uint32_t CLIOptionArrayLength = 3;
CLIOption CLIOptionArray[CLIOptionArrayLength] = {
    //  Name               | cmd       | function
    {   "TestFunc1",        "TF1",       TestFunc1   },
    {   "TestFunc2",        "TF2",       TestFunc2   },
    {   "TestFunc3",        "TF3",       TestFunc3   }
};
```
And then initialise the SimpleCLI Object.
```
SimpleCLI CLI(&Serial, CLIOptionArray, CLIOptionArrayLength);
```
> Important is, that the Serial shuld be initialised **before** Initialising the SimpleCLI Object. That means, calling Serial.begin(); before Creating the SimpleCLI Object.

After that, checkCLI() should be called as often as possible. 

> **Warning:** when CLI starts, normal program execution will be stopped and will remain in the CLI until it is stopped.

The CLI starts, when on the specifyed serial, something is recived. Then the CLI starts. 
The CLI runns until the CLI is exited. In that time the Regular programm is **NOT** executed.

## CycleFunction

When the CLI is active and waiting for command, no user code is executed. The solution is the CycleFunction. 
This CycleFunction is executed, when no Command is executed and the CLI is waiting for user input. 
IMPORTAND: The CLI must be Active. That the CycleFunction runns.

To define the CycleFunction the following Code is used:
```
CLI.setCycleFunction(CycleFunction);
```
the Argument is a Function ptr (void(*CycleFunction)())

To start or stop the CycleFunction feater use the following Function: 
```
CLI.activateCycleFunction(avtive);
```
The argument active is used to specify if the frature is on(true) or off(false)

## deactivating options

To deactivate options the following function may be used: 
```
CLI.activateCLIOption(active, numberOfOption);
```
In this case, active specifyes if the Option is on or off and the numberOfOption is index of following option in the OptionsArray. 

An easier function is the following: 
```
CLI.activateCLIOption(active, commandOfOption);
```
commandOfOption is a string, that is the command of the option to deactivate / activate
