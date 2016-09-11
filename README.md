# SerialPort
A working (though simplistic) C# SerialPort implementation.

At WisconsinRobotics, we've tried to use the System.IO.Ports.SerialPort class for serial operations. Writing worked fine.
Reading, on the other hand, was an entirely different story. 

This small C++/CLI library is intended to be a bare bones alternate implementation of the C# SerialPort, only supporting no parity,
1 stop bit, and 8 data bits.
