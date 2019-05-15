
#ifndef _UDP_H_ 
#define _UDP_H_ 

#include <winsock2.h>  
#include <windows.h> 
#include <stdio.h>
#include <stdint.h>

// Ĭ�Ͻ������ݳ�ʱ, ��λms
#define DEFAULT_RECIEVE_TIMEOUT_MS 100

class UdpClient
{
private:
	SOCKET s;
	// �����IP��ַ
	sockaddr_in addr;
	// �Է���IP��ַ
	sockaddr_in addrClient;
public:
	explicit UdpClient(int port);
	~UdpClient();
	// ���ò���ʹ��Socket�˿ں�
	void SetPortAndBind(int port);
	// ������IP�Ͷ˿ںŷ�������
	void SendTo(int port, const char * ipstring, const char* bytes, int length);
	// �ӷ��͵����ݷ���������
	int RecieveFrom(char* bytes);
	// �ر�UDP����
	void CloseUdp();
private:

};

#endif
