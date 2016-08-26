
#pragma comment(lib, "wsock32.lib")
#include <winsock.h>

//http://www.golgo.jp/winsock.html

#ifndef _WINSOCK_H_
#define _WINSOCK_H_
//Winsockを使ったオンライン通信
class CWinsock
{
public:
	CWinsock();
	~CWinsock();

	int Start();

private:

};
#endif //_WINSOCK_H_