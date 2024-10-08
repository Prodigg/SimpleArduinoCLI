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

#include "SimpleCLI.h"

void Function1(void* CLI) {
    Serial.println("Function1");
}

void ActivateF1(void* CLI) {
    Serial.println("Activate Function1");
    static_cast<SimpleCLI*>(CLI)->activateCLIOption(true, "F1");     // you can use the command string or option index
}

void DeactivateF1(void* CLI) {
    Serial.println("Deactivate Function1");
    static_cast<SimpleCLI*>(CLI)->activateCLIOption(false, 0);      // you can use the command string or option index
}

const uint32_t CLIOptionArrayLength = 3;
CLIOption CLIOptionArray[CLIOptionArrayLength] = {
    //  Name               | cmd       | function
    {   "Function1",         "F1",      Function1 },
    {   "ActivateF1",        "AF1",     ActivateF1 },
    {   "DeactivateF1",      "DF1",     DeactivateF1 }

};

SimpleCLI CLI;

void setup() {
    Serial.begin(115200);
    CLI.begin(&Serial, CLIOptionArray, CLIOptionArrayLength);
}

void loop() {
    CLI.checkCLI();     // call as oftern as possible
}
