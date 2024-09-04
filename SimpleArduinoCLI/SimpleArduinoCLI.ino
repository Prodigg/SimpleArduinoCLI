/*
 Name:		SimpleArduinoCLI.ino
 Created:	03.09.2024 22:35:03
 Author:	Prodigg
*/

/*
* This File is a test enviroment for developement. It isn't for examples or anything else.
*/


#define SIMPLE_CLI_LOW_MEM

#include "SimpleCLI/SimpleCLI.h"

void Test1Fun(void* CLI) {
    Serial.println("Test1Function works");
    delay(10000);
}

void Test2Fun(void* CLI) {
    Serial.println("Test2Function works");
}

void Test3Fun(void* CLI) {
    Serial.println("Test3Function works");
    static_cast<SimpleCLI*>(CLI); 
}

void CycleFN() {
    Serial.println("CycleFunction");
    delay(10);  // in CycleFunction be carefull with delays
}

const uint32_t CLIOptionArrayLength = 3;
CLIOption CLIOptionArray[CLIOptionArrayLength] = {
    //  Name               | cmd       | function
    {   "Test1",         "T1",      Test1Fun },
    {   "Test2",         "T2",      Test2Fun },
    {   "Test3",         "T3",      Test3Fun }

};


SimpleCLI CLI(&Serial, CLIOptionArray, CLIOptionArrayLength);



void setup() {
    Serial.begin(115200);
    //CLI.setCycleFunction(CycleFN);      // set CycleFunction
    //CLI.activateCycleFunction(true);    // Activate CycleFunction
}

void loop() {
    CLI.checkCLI();     // call as oftern as possible
}
