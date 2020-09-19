/*
  MIT License
  Copyright (c) 2020 by Jacob Wachlin
  
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

  /brief This example shows how data on the stack can be accessed later than desired, potentially leaking sensitive information

  Going through this example, you must pretend you do not know that the "social security number" ssn. The do_something_else has no need to know this
  sensitive information, yet it can access that information.

*/


#include <string.h>

#define BUFFER_LENGTH         16

void process_secret_data(void)
{
  char buffer[64];
  int ssn = 555555555; // Should NOT be leaked
  snprintf(buffer, 64, "SSN: %i", ssn);

  // Do something with SSN...
}

void do_something_else(void)
{
  char buffer[64];

  Serial.println("Enter your Name");

  int start = millis();
  int index = 0;
  while((millis() - start) < 5000)
  {
    if(Serial.available())
    {
      buffer[index++] = Serial.read();
    }
  }
  
  Serial.print("Your name: ");
  Serial.println(buffer);
}


void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println("Booting...");
  delay(100);
}

void loop() {
  delay(5000);
  Serial.println("Loop still running");

  process_secret_data();
  do_something_else();

}
