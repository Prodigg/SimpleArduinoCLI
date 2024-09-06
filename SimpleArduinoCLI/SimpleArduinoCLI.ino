/*
MIT License

Copyright (c) 2024 Prodigg

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

/*
* This File is a test enviroment for developement and may also function as a Tutorial. (Until i make a proper one ;))
*/

#include "SimpleCLI/SimpleCLI.h"

void Test1Fun(void* CLI) {
    Serial.println("Test1Function works");
    delay(1000);
}

void Test2Fun(void* CLI) {
    Serial.println("Test2Function works");
    static_cast<SimpleCLI*>(CLI)->activateCLIOption(true, "T1");
}

void Test3Fun(void* CLI) {
    Serial.println("Test3Function works");
    static_cast<SimpleCLI*>(CLI)->activateCLIOption(false, 0);
}

void exitCLI(void* CLI) {
    static_cast<SimpleCLI*>(CLI)->exitCLIFunc();
}

void CycleFN() {
    Serial.println("CycleFunction");
    delay(10);  // in CycleFunction be carefull with delays
}

const uint32_t CLIOptionArrayLength = 4;
CLIOption CLIOptionArray[CLIOptionArrayLength] = {
    //  Name               | cmd       | function
    {   "Test1",         "T1",      Test1Fun },
    {   "Test2",         "T2",      Test2Fun },
    {   "Test3",         "T3",      Test3Fun },
    {   "exits CLI",     "e",       exitCLI  }

};


SimpleCLI CLI(&Serial, CLIOptionArray, CLIOptionArrayLength);



void setup() {
    Serial.begin(115200);
    CLI.disableDefaultExitFN(true);
    //CLI.setCycleFunction(CycleFN);      // set CycleFunction
    //CLI.activateCycleFunction(true);    // Activate CycleFunction
}

void loop() {
    CLI.checkCLI();     // call as oftern as possible
}
