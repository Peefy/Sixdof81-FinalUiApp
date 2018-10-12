#ifndef __UART_NET_H
#define __UART_NET_H

#include "stdint.h"

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
	bool Open(int portNumber, int baudRate);
	bool Close();
	T* GetDataFromCom();
	bool IsRecievedData;
	T * Data;
private:
	BaseCom();
};

template <typename T>
BaseCom<T>::BaseCom()
{
	Data = new T;
	DefaultPackageHeaderOne = 0x55;
	DefaultPackageHeaderTwo = 0xAA;
}

template <typename T>
BaseCom<T>::BaseCom(uint8_t headerOne, uint8_t headerTwo)
{
	Data = new T;
	DefaultPackageHeaderOne = headerOne;
	DefaultPackageHeaderTwo = headerTwo;
}

template <typename T>
BaseCom<T>::~BaseCom()
{
	delete Data;
}

template <typename T>
bool BaseCom<T>::Open(int portNumber, int baudRate)
{
	PortNumber = portNumber;
	BaudRate = baudRate;
	return OpenCOMDevice(portNumber, baudRate);
}

template <typename T>
bool BaseCom<T>::Close()
{
	CloseCOMDevice();
	return true;
}

template <typename T>
T* BaseCom<T>::GetDataFromCom()
{
	static char uchrTemp[COM_BASE_BUFFER_MAX];
	static unsigned char chrTemp[COM_BASE_BUFFER_MAX];
	static unsigned char ucRxCnt = 0;	
	static unsigned short usRxLength = 0;
	static int length = sizeof(T);
	auto nowlength = CollectUARTData(PortNumber, uchrTemp);
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
		if(chrTemp[1] == DefaultPackageHeaderTwo)
		{
			memcpy(Data, &chrTemp[0], length);
		}
		usRxLength -= length;
		memcpy(&chrTemp[0], &chrTemp[length], usRxLength);    
		IsRecievedData = true;
	}
	return Data;
}

#endif
