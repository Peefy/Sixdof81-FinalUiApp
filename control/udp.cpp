
#include "stdafx.h"
#include "udp.h"

#pragma comment(lib, "ws2_32.lib")

UdpClient::UdpClient(int port)
{
	WSADATA data;
	WORD wVersionRequired = MAKEWORD(2, 0);
	WSAStartup(wVersionRequired, &data);
}

UdpClient::~UdpClient()
{
	closesocket(s);
	WSACleanup();
}

void UdpClient::SetPortAndBind(int port)
{
	s = socket(AF_INET, SOCK_DGRAM, 0);
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.S_un.S_addr = INADDR_ANY;
	bind(s, (sockaddr*)&addr, sizeof(addr));
	timeval tv = {0, DEFAULT_RECIEVE_TIMEOUT_MS};
	setsockopt(s, SOL_SOCKET, SO_RCVTIMEO, (char*)&tv, sizeof(timeval));
}

void UdpClient::SendTo(int port, const char * ipstring, const char* bytes, int length)
{
	addrClient.sin_family = AF_INET;
	addrClient.sin_port = htons(port);
	addrClient.sin_addr.S_un.S_addr = inet_addr(ipstring);
	int nSockAddrSize = sizeof(addrClient);
	sendto(s, bytes, length, 0, (sockaddr*)&addrClient, nSockAddrSize);
}

int UdpClient::RecieveFrom(char* bytes)
{
	int nSockAddrSize = sizeof(addrClient);
	int len = recvfrom(s, bytes, 1024, 0, (sockaddr*)&addrClient, &nSockAddrSize);
	return len <= SOCKET_ERROR ? 0 : len;
}

void UdpClient::CloseUdp()
{
	closesocket(s);
	WSACleanup();
}
