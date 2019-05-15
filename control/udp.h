
#ifndef _UDP_H_ 
#define _UDP_H_ 

#include <winsock2.h>  
#include <windows.h> 
#include <stdio.h>
#include <stdint.h>

// 默认接收数据超时, 单位ms
#define DEFAULT_RECIEVE_TIMEOUT_MS 100

class UdpClient
{
private:
	SOCKET s;
	// 自身的IP地址
	sockaddr_in addr;
	// 对方的IP地址
	sockaddr_in addrClient;
public:
	explicit UdpClient(int port);
	~UdpClient();
	// 设置并绑定使用Socket端口号
	void SetPortAndBind(int port);
	// 向其他IP和端口号发送数据
	void SendTo(int port, const char * ipstring, const char* bytes, int length);
	// 从发送的数据方接收数据
	int RecieveFrom(char* bytes);
	// 关闭UDP连接
	void CloseUdp();
private:

};

#endif
