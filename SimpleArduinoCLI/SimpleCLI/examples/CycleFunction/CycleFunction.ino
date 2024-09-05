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


#define SIMPLE_CLI_LOW_MEM      // for devices like arduino Uno where memory is a low resorce


#include "SimpleCLI.h"

void ActivateCycleFN(void* CLI) {
    Serial.println("Activate CycleFunction");
    static_cast<SimpleCLI*>(CLI)->activateCycleFunction(true); // activate CycleFunction
}

void DeactivateCycleFN(void* CLI) {
    Serial.println("Deactivate CycleFunction");
    static_cast<SimpleCLI*>(CLI)->activateCycleFunction(false); // deactivate CycleFunction
}

const uint32_t CLIOptionArrayLength = 2;
CLIOption CLIOptionArray[CLIOptionArrayLength] = {
    //  Name               | cmd       | function
    {   "ActivateCycleFN",   "ACF",      ActivateCycleFN },
    {   "DeactivateCycleFN", "DCF",      DeactivateCycleFN }

};

void CycleFN() {
    Serial.println("Cycle Function Called");
    delay(10);      // be carefull with delays in Cycle Function
}

SimpleCLI CLI(&Serial, CLIOptionArray, CLIOptionArrayLength);



void setup() {
    Serial.begin(115200);
    CLI.setCycleFunction(CycleFN);      // set CycleFunction
}

void loop() {
    CLI.checkCLI();     // call as oftern as possible
}

