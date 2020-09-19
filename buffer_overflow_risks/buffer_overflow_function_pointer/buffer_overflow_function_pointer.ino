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

  /brief This example shows how buffer overflows can allow an attacker to drastically change the code flow, calling functions that they shouldn't be able to.

  While this is a contrived example, having structs like this is actually not that uncommon. For a architecture that makes use of callback functions,
  something similar to databall_t could certainly be made. Care must be taken to avoid buffer overflows like this. Beyond security risks, these kinds
  of issues can be very difficult to debug, as the flow of the code does not match what is written.

*/


typedef struct
{
  uint8_t buffer[16];
  void (*cb)(int);
} databall_t;

void other_secret_function(int a)
{
  Serial.println("Secret function found!");
}

void secret_function(int a)
{
  Serial.println("Secret function found!");
}

void handle_sum(int s)
{
  Serial.print("Sum of buffer: ");
  Serial.println(s);
}

void handle_data(databall_t * db)
{
  Serial.println("Summing data");
  int sum = 0;
  for(int i = 0; i < 16; i++)
  {
    sum += db->buffer[i];
  }
  db->cb(sum);
}

void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println("Booting...");
  delay(100);

 
}

void loop() {
  delay(1000);
  Serial.println("Loop still running");

  databall_t db;

  char pointer_addr[128];
  snprintf(pointer_addr, 128, "Secret function address: %p", secret_function);
  Serial.println(pointer_addr);

  snprintf(pointer_addr, 128, "Other secret function address: %p", other_secret_function);
  Serial.println(pointer_addr);

  snprintf(pointer_addr, 128, "Handle sum function address: %p", handle_sum);
  Serial.println(pointer_addr);

  Serial.print("Size of databall: ");
  Serial.println(sizeof(db));

  db.cb = handle_sum;

  int start = millis();
  int index = 0;
  Serial.println("Enter the data");
  while((millis() - start) < 5000)
  {
    if(Serial.available())
    {
      db.buffer[index++] = Serial.read();
    }
  }
  handle_data(&db);

}
