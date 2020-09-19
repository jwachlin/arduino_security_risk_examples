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

  /brief This example shows how buffer overflow can overwrite other values on the stack, potentially causing unexpected consequences

  Going through this example, you must pretend you do not know that the password is "super_secret."Is there another way to unlock
  the system?

  While this example shows a trivial case of a "security" risk, the other issue with buffer overflow bugs is making debugging of your code
  very difficult. If values on the stack are overwritten, it can cause unexpected behavior. At worst, for microcontrollers controlling physical
  hardware, this could be dangerous.

*/


#define BUFFER_LENGTH   16

void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println("Booting...");
  delay(100);
}

void loop() {
  delay(5000);

  char buff[BUFFER_LENGTH] = {0};
  uint8_t unlocked_flags[32] = {0};

  Serial.print("Buffer address: ");
  Serial.println((uint32_t) buff);

  Serial.print("Unlocked flags address: ");
  Serial.println((uint32_t) unlocked_flags);

  int start = millis();

  int index = 0;
  Serial.println("Enter your password");
  while((millis() - start) < 5000)
  {
    if(Serial.available())
    {
      buff[index++] = Serial.read();
    }
  }

  if(strcmp("super_secret", buff) == 0)
  {
    Serial.println("Password correct!");
    unlocked_flags[0] = 1;
  }
  

  if(unlocked_flags[0])
  {
    Serial.println("UNLOCKED!!!!");
  }
  else
  {
    Serial.println("Still locked...");
  }

}
