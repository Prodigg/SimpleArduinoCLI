# how to install 

download the zip file in releses
and install it with arduinoIDE.
Then it can be included with `#include <SimpleCLI.h>` into a project

# Documentation

In this Documentation, the SimpleCLI object is called `CLI` but any other name may be used.

Further examples are in the Arduino Libary. These can be accessed via. the examples in the ArduinoIDE.

## Important

For correct use of the CLI set the Serial settings in the IDE to use a Line Feed, New Line or both.
If not, SimpleCLI may not work correctly.

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
SimpleCLI CLI;
CLI.begin(&Serial, CLIOptionArray, CLIOptionArrayLength);
```
> Important is, that the Serial should be initialised and the Function `CLI.begin` should be called **before** a function call to the CLI is done.
> If a Function of SimpleCLI is called before the serial is initialised or before `CLI.begin` is called can lead to undefined behavior in the SimpleCLI libary.

After that, `checkCLI()` should be called as often as possible. 

> **Warning:** when CLI starts, normal program execution will be stopped and will remain in the CLI until it is stopped.

The CLI starts, when on the specifyed serial, something is recived. Then the CLI starts. 
The CLI runns until the CLI is exited. In that time the Regular programm is **NOT** executed.

## SimpleCLI Options

In SimpleCLI every function you can execute vis SimpleCLI is a so called Option. These Options are stored in an CLIOption array. 
An definition of such an array may look like this: 
```
const uint32_t CLIOptionArrayLength = 3;
CLIOption CLIOptionArray[CLIOptionArrayLength] = {
    //  Name               | cmd       | function
    {   "TestFunc1",        "TF1",       TestFunc1   },
    {   "TestFunc2",        "TF2",       TestFunc2   },
    {   "TestFunc3",        "TF3",       TestFunc3   }
};
```
In the fist Argument of the CLIOption is the name. The name is a short description of the function that the option can execute.
The cmd is the command that should be typed to execute the option. 
Last is the function. The function takes as an argument an function ptr. The function pointer is the following: `void(*function)(void* CLI)`

The user defined function may look like this: 

```
void Test1Fun(void* CLI) {
    Serial.println("Test1Function works");
    delay(1000);
}
```

### using CLI Functions in Options

As shown above, the option function has an argument (`void* CLI`). this is a void pointer to the SimpleCLI object that called the option. 
With this, manipulations to the SimpleCLI object in options becomes possible.

To cast the `void*` to `SimpleCLI*` the following code is used `static_cast<SimpleCLI*>(CLI)`.
In an function the code may look like this: 
```
void exitCLI(void* CLI) {
    static_cast<SimpleCLI*>(CLI)->exitCLIFunc();
}
```
This code exits the CLI.

### update options mid runtime 

To update the CLIOptionArray the folowing code is used: 

```
CLI.updateCLIOptions(CLIOptionArray, CLIOptionArrayLength);
```
> WARINING: when the new array is bigger than the last, more memory is dynamicly allocated. 


## CycleFunction

When the CLI is active and waiting for command, no user code is executed. The solution is the CycleFunction. 
This CycleFunction is executed, when no Command is executed and the CLI is waiting for user input. 
IMPORTAND: The CLI must be Active. That the CycleFunction runns.

To define the CycleFunction the following Code is used:
```
CLI.setCycleFunction(CycleFunction);
```
the Argument is a Function ptr `(void(*CycleFunction)())`

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

## SimpleCLI customising Greetings

To customise the appirance of SimpleCLI there are the following options: 

```
CLI.disableGreetings(disable);
```
With this Function the Welcome and Goodbye messages are disabled. 

With the following Function a custom greeting may be set. Instead of SimpleCLI
```
CLI.setCustomGreetingStr(str);
```

## exiting SimpleCLI

In SimpleCLI by defult, there is an option to exit the CLI.

To take control of exeting SimpleCLI use `disableDefultExitFN` like so: 
```
CLI.disableDefultExitFN(true);
```
With this Command, the defult exit command is removed. 
> WARNING: When disabeling the defult exit command, the exeting **must** be handeled in an other option.
> If not, it may leed to situations, where you can't exit SimpleCLI.

An Option Function to Quit SimpleCLI may look the following: 
```
void exitCLI(void* CLI) {
    static_cast<SimpleCLI*>(CLI)->exitCLIFunc();
}
```



