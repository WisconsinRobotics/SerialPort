using System;
using WisconsinRobotics.Serial;

namespace SerialPortTester
{
    class Program
    {
        static void Main(string[] args)
        {
            if (args.Length != 0)
            {
                Console.WriteLine("usage: SerialPortTester.exe COMX");
                return;
            }

            SerialPort port = new SerialPort(@"\\.\COM12", 115200);
            if (!port.Open())
            {
                Console.WriteLine("Failed to open serial port!");
                return;
            }

            byte[] buffer = new byte[100];
            port.Read(buffer, 4);

            for (int i = 0; i < 4; i++)
            {
                Console.Write("{0} ", buffer[i].ToString("X2"));
            }

            Console.Read();
        }
    }
}
