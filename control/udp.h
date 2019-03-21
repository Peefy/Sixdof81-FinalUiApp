
#ifndef _UDP_H_ 
#define _UDP_H_ 

#include <winsock2.h>  
#include <windows.h> 
#include <stdio.h>
#include <stdint.h>

class UdpClient
{
private:
	bool isDisposed;

	SOCKET s;
	sockaddr_in addr;

	sockaddr_in addrClient;

public:
	UdpClient(int port);
	~UdpClient();
	void SetPortAndBind(int port);
	void SendTo(int port, const char * ipstring, const char* bytes, int length);
	int RecieveFrom(char* bytes);
	void CloseUdp();
private:

};



#endif
