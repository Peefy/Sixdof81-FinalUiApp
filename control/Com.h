#ifndef __UART_NET_H
#define __UART_NET_H

#include "stdint.h"
#include "../config/inihelper.h"
#include "../communication/SerialPort.h"

signed char	SendUARTMessageLength(const unsigned long ulChannelNo, const char chrMessage[],const unsigned short usLen);
unsigned short CollectUARTData(const unsigned long ulChannelNo, char chrUARTBufferOutput[]);
signed char OpenCOMDevice(const unsigned long ulPortNo);
signed char SetBaundrate(const unsigned long ulPortNo,const unsigned long ulBaundrate);
signed char OpenCOMDevice(const unsigned long ulPortNo,const unsigned long ulBaundrate);
void CloseCOMDevice(void);

#define COM_BASE_BUFFER_MAX   4096

template <typename T>
class BaseCom
{
public:
	BaseCom(uint8_t headerOne, uint8_t headerTwo);
	~BaseCom();
	uint8_t DefaultPackageHeaderOne;
	uint8_t DefaultPackageHeaderTwo;
	int PortNumber;
	int BaudRate;
	bool IsRecievedData;
	bool Open(int portNumber, int baudRate);
	bool Close();
	T GetDataFromCom();
	T Data;
private:
	BaseCom();
	CSerialPort serialPort;
};

template <typename T>
BaseCom<T>::BaseCom()
{
	DefaultPackageHeaderOne = 0x55;
	DefaultPackageHeaderTwo = 0xAA;
}

template <typename T>
BaseCom<T>::BaseCom(uint8_t headerOne, uint8_t headerTwo)
{
	DefaultPackageHeaderOne = headerOne;
	DefaultPackageHeaderTwo = headerTwo;
}

template <typename T>
BaseCom<T>::~BaseCom()
{
	
}

template <typename T>
bool BaseCom<T>::Open(int portNumber, int baudRate)
{
	bool result;
	int baud;
	int portnum;
	config::ReadAll(result, baud, portnum);
	PortNumber = portnum;
	BaudRate = baud;
	return serialPort.InitPort(portnum, baud) == true;
	//return OpenCOMDevice(portnum, baud) == 1;
}

template <typename T>
bool BaseCom<T>::Close()
{
	//serialPort.ClosePort();
	//CloseCOMDevice();
	return true;
}

template <typename T>
T BaseCom<T>::GetDataFromCom()
{
	static char uchrTemp[COM_BASE_BUFFER_MAX];
	static unsigned char chrTemp[COM_BASE_BUFFER_MAX];
	static unsigned char ucRxCnt = 0;	
	static unsigned short usRxLength = 0;
	static int length = sizeof(T);
	auto nowlength = serialPort.GetBytesInCOM();
	unsigned char cRecved;
	for (int i = 0; i < nowlength; ++i)
	{
		serialPort.ReadChar(cRecved);
		uchrTemp[i] = cRecved;
	}
	//auto nowlength = CollectUARTData(PortNumber, uchrTemp);
	memcpy(chrTemp, uchrTemp, sizeof(unsigned char) * COM_BASE_BUFFER_MAX);
	usRxLength += nowlength;
	while (usRxLength >= length)
	{
		if (chrTemp[0] != DefaultPackageHeaderOne)
		{
			usRxLength--;
			memcpy(&chrTemp[0], &chrTemp[1], usRxLength);                        
			continue;
		}
		memcpy(&Data, &chrTemp[0], length);
		usRxLength -= length;
		memcpy(&chrTemp[0], &chrTemp[length], usRxLength);    
		IsRecievedData = true;
	}
	return Data;
}

#endif
