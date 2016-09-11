#pragma once

#include <windows.h>


namespace WisconsinRobotics
{
    namespace Serial
    {
        public ref class SerialPort
        {
        public:
            // assumed no parity, 1 stop bit, and 8 bits per byte
            SerialPort(System::String^ port, System::Int32 baud_rate);
            ~SerialPort();
            System::Boolean Open();
            System::Boolean IsOpen();
            void Close();
            void Write(array<System::Byte>^ buffer, System::Int32 length);
            System::Int32 Read(array<System::Byte>^ buffer, System::Int32 length);

        private:
            HANDLE serialPortHandle;
            System::String^ portName;
            System::Int32 baudRate;
            System::Boolean isOpen;
        };
    }
}
