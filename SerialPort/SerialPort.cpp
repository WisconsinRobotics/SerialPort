#include "SerialPort.h"

using namespace WisconsinRobotics::Serial;


SerialPort::SerialPort(System::String^ port, System::Int32 baud_rate)
{
    this->portName = port;
    this->baudRate = baud_rate;
    this->isOpen = false;
    this->serialPortHandle = INVALID_HANDLE_VALUE;
}

SerialPort::~SerialPort()
{
    if (this->isOpen)
        this->Close();

    this->isOpen = false;
}

System::Boolean SerialPort::Open()
{
    DCB dcb;
    COMMTIMEOUTS commTO;

    if (this->isOpen)
        return true;

    pin_ptr<wchar_t> pinned = &this->portName->ToCharArray()[0];

    this->serialPortHandle = CreateFile(
        pinned,
        GENERIC_READ | GENERIC_WRITE,
        0,
        0,
        OPEN_EXISTING,
        FILE_FLAG_WRITE_THROUGH | FILE_FLAG_NO_BUFFERING,
        0
    );

    if (this->serialPortHandle == INVALID_HANDLE_VALUE)
        return false;

    memset(&dcb, 0, sizeof(DCB));
    if (!GetCommState(this->serialPortHandle, &dcb))
    {
        CloseHandle(this->serialPortHandle);
        return false;
    }

    dcb.BaudRate = this->baudRate;
    dcb.fParity = FALSE;
    dcb.StopBits = ONESTOPBIT;
    dcb.ByteSize = 8;
    dcb.DCBlength = sizeof(dcb);
    if (!SetCommState(this->serialPortHandle, &dcb))
    {
        CloseHandle(this->serialPortHandle);
        return false;
    }

    memset(&commTO, 0, sizeof(COMMTIMEOUTS));
    commTO.ReadIntervalTimeout = MAXDWORD;
    if (!SetCommTimeouts(this->serialPortHandle, &commTO))
    {
        CloseHandle(this->serialPortHandle);
        return false;
    }

    this->isOpen = true;
    return true;
}

System::Boolean SerialPort::IsOpen()
{
    return this->isOpen;
}

void SerialPort::Close()
{
    if (!this->isOpen)
        return;

    CloseHandle(this->serialPortHandle);
    this->isOpen = false;
}

void SerialPort::Write(array<System::Byte>^ buffer, System::Int32 length)
{
    if (this->serialPortHandle == INVALID_HANDLE_VALUE || !this->isOpen)
        return;

    pin_ptr<System::Byte> converted = &buffer[0];
    WriteFile(this->serialPortHandle, converted, length, nullptr, nullptr);
}

System::Int32 SerialPort::Read(array<System::Byte>^ buffer, System::Int32 length)
{
    DWORD bytesRead;
    if (this->serialPortHandle == INVALID_HANDLE_VALUE || !this->isOpen)
        return -1;

    pin_ptr<System::Byte> converted = &buffer[0];
    BOOL success = ReadFile(this->serialPortHandle, converted, length, &bytesRead, nullptr);
    return success ? bytesRead : -1;
}
