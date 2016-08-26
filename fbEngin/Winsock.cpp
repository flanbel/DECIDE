#include "Winsock.h"

char ServerName[] = "www.geocities.co.jp";           // 接続先のホスト名
char Html[] = "/Playtown-Domino/1056/index.html";    // 目的のhtmlのパス
unsigned short Port = 80;                        //ポート番号

#define BUFSIZE     256                          // バッファサイズ
#define RECVSIZE    65536                        // 受信バッファサイズ


CWinsock::CWinsock()
{
}

CWinsock::~CWinsock()
{
}

int CWinsock::Start()
{
	WSADATA wsaData;
	//SOCKET sock;
	int err;
	//開始
	//引数はversionとポインタ
	err = WSAStartup(MAKEWORD(1, 0), &wsaData);
	if (err != 0) {
		switch (err) {
		case WSASYSNOTREADY:
			//ネットワークサブシステムがネットワークへの接続を準備できていない
			MessageBox(0, TEXT("WSASYSNOTREADY"), TEXT("ERROR"), MB_ICONWARNING);
			break;
		case WSAVERNOTSUPPORTED:
			//要求されたwinsockのバージョンがサポートされていない
			MessageBox(0, TEXT("WSAVERNOTSUPPORTED"), TEXT("ERROR"), MB_ICONWARNING);
			break;
		case WSAEINPROGRESS:
			//ブロッキング操作の実行中であるか、 またはサービスプロバイダがコールバック関数を処理している
			MessageBox(0, TEXT("WSAEINPROGRESS"), TEXT("ERROR"), MB_ICONWARNING);
			break;
		case WSAEPROCLIM:
			//winsockが処理できる最大プロセス数に達した
			MessageBox(0, TEXT("WSAEPROCLIM"), TEXT("ERROR"), MB_ICONWARNING);
			break;
		case WSAEFAULT:
			//第二引数であるlpWSAData は有効なポインタではない
			MessageBox(0, TEXT("WSAEFAULT"), TEXT("ERROR"), MB_ICONWARNING);
			break;
		}
	}
	else
	{

		{

		// ホスト名取得処理

		char name[256];
		int err_no;                                // エラーナンバー

		if (gethostname(name, sizeof(name)) == 0){
			printf("このコンピュータの名前は%sです\n", name);
		}
		else{
			err_no = WSAGetLastError();
			MessageBox(0, TEXT("ホスト名の取得に失敗しました。"), TEXT("ERROR:" + err_no), MB_ICONWARNING);
			exit(0);
		}


		//IPアドレス取得
		//引数はホスト名が格納された文字配列のポインタ

		char lpszIP[16];
		PHOSTENT phostent;
		IN_ADDR in;

		if ((phostent = gethostbyname(name)) != NULL){
			memcpy(&in, phostent->h_addr, 4);
			wsprintf(lpszIP, inet_ntoa(in));
			printf("IPアドレス：%s\n", lpszIP);
		}
		else{
			err_no = WSAGetLastError();
			MessageBox(0, TEXT("IPアドレスの取得に失敗しました。"), TEXT("ERROR:" + err_no), MB_ICONWARNING);
			exit(0);
		}




		// IPアドレスからホスト名取得処理
		//10進数からコンピュータがわかるバイナリ形式のIPアドレスに変換

		u_long ulIPAddress = inet_addr(lpszIP);
		char lpszHostName[256];        // ホストネーム格納領域
		PHOSTENT nam;

		if ((nam = gethostbyaddr((char *)&ulIPAddress, 4, PF_INET)) != NULL){
			wsprintf(lpszHostName, "%s", nam->h_name);
		}
		else{
			err_no = WSAGetLastError();
			MessageBox(0, TEXT("IPアドレスからホスト名の取得に失敗しました。"), TEXT("ERROR:" + err_no), MB_ICONWARNING);
			exit(0);
		}


		// ポート番号取得処理

		PSERVENT pservent;

		if ((pservent = getservbyname("smtp", "tcp")) != NULL){
			printf("%sプロトコルを利用した%sサービスはポート番号%dを使用します。\n",
				pservent->s_proto,
				pservent->s_name,
				ntohs(pservent->s_port));
		}
		else{
			err_no = WSAGetLastError();
			MessageBox(0, TEXT("ポート番号を取得できませんでした。"), TEXT("ERROR:" + err_no), MB_ICONWARNING);
		}
	}

		///////////////////////////////

		// ソケット作成
		int soc;                                    // ソケット
		soc = socket(AF_INET, SOCK_STREAM, 0);
		if (soc == INVALID_SOCKET){
			printf("ソケット作成失敗です\n");
			printf("エラー%dが発生しました\n", WSAGetLastError());
			return -1;
		}

		// サーバのIPアドレス取得
		PHOSTENT phostent;                          // サーバの情報を指すポインタ
		unsigned long ulIPAddress;                  // サーバのIPアドレス格納変数
		ulIPAddress = inet_addr(ServerName);        // IPアドレス取得
		// inet_addr()関数が失敗　ServerNameがホスト名であった場合下の処理に入る
		if (ulIPAddress == -1){
			if ((phostent = gethostbyname(ServerName)) != NULL){
				ulIPAddress = *((unsigned long *)(phostent->h_addr));
			}
			else{
				printf("ホストアドレス取得失敗です\n");
				printf("エラー%dが発生しました\n", WSAGetLastError());
				closesocket(soc);                    // ソケットの破棄
				return -1;
			}
		}

		// サーバへ接続
		SOCKADDR_IN     addrServer;                                       // サーバのアドレス
		addrServer.sin_family = AF_INET;                            // アドレスファミリの指定
		addrServer.sin_addr.s_addr = ulIPAddress;                        // サーバのIPアドレスの指定
		addrServer.sin_port = htons((unsigned short)Port);        // ポート番号の指定
		if (connect(soc, (LPSOCKADDR)&addrServer, sizeof(addrServer)) == SOCKET_ERROR){
			printf("サーバへの接続失敗です\n");
			printf("エラー%dが発生しました\n", WSAGetLastError());
			closesocket(soc);                        // ソケットの破棄
			return -1;
		}

		// サーバに GET リクエストを送信
		char request[BUFSIZE] = "GET http://www.geocities.co.jp/Playtown-Domino/1056/index.html HTTP/1.0\r\n\r\n";
		//sprintf(request, "GET http://www.geocities.co.jp/Playtown-Domino/1056/index.html HTTP/1.0\r\n\r\n", ServerName, Html);
		if (send(soc, request, sizeof(request), 0) == SOCKET_ERROR){
			printf("サーバへの送信失敗です\n");
			printf("エラー%dが発生しました\n", WSAGetLastError());
			shutdown(soc, 2);                        // 送受信を無効にする
			closesocket(soc);                        // ソケットの破棄
			return -1;
		}

		// データの受信
		char recv_buf[RECVSIZE];
		int nBytesRecv;
		while (1){    // 1回では受信しきれないので、受信が終わるまで繰り返す
			nBytesRecv = recv(soc, recv_buf, sizeof(recv_buf), 0);
			if (nBytesRecv == SOCKET_ERROR){
				printf("サーバからの受信失敗です\n");
				printf("エラー%dが発生しました\n", WSAGetLastError());
				break;
			}
			else if (nBytesRecv == 0){                 // 受信終わり
				break;
			}
			recv_buf[nBytesRecv] = '\0';               // 受信バッファの後ろにNULLを付加する
			printf("%s", recv_buf);                  // 画面に受信したhtmlを表示
		}

		shutdown(soc, 2);                            // 送受信を無効にする
		closesocket(soc);                           // ソケットの破棄

	}

	//終了
	WSACleanup();

	return 0;
}