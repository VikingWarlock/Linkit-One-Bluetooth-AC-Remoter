## Linkit One Bluetooth AC Remoter

use your linkit one and bluetooth to control the midea AC.

---

The Linkit one doesn't have the essential library that normal Arduino has. So the [Arduino-IRRemote](https://github.com/z3t0/Arduino-IRremote) cannot run on this board.

The command is provided by [ArduMideaWrapper](https://github.com/WiserUFBA/ArduMideaWrapper). Also it requires `Arduino-IRRemote`, so it cannot run directly.

---

In the VKIRSender.h, I create a class, it provides the methods ArduMideaWrapper needs, and it rewrite these methods for Linkit One.

So, it works.

---

#### Function

This project can determine the `temperature` by `DHT` sensor.

also can set AC command and send it via `IR Sender`.

#### PIN MODE

pin D10 for DHT->Data

pin D3 for IR Sender->SIG 

IMPORTANT :`Cause IR Sender need PWM, it can only use D2 or D3`

#### Note

remoter.ino      -> Main
RemoteGATT       -> Used to set the AC Command
RemoterService   -> Used to get the temperature data
VKIRSender       -> Used to send IR signal
midea            -> modified from ArduMideaWrapper, it generate the command


### Have Fun

I want to add some more functions.

For example, I can set a temperature, can the board can turn on the AC when it is too hot or too cold.

And so on...

----

## License

Copyright (C) 2017 Viking Warlock

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.