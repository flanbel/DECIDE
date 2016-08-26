#include "Winsock.h"

char ServerName[] = "www.geocities.co.jp";           // �ڑ���̃z�X�g��
char Html[] = "/Playtown-Domino/1056/index.html";    // �ړI��html�̃p�X
unsigned short Port = 80;                        //�|�[�g�ԍ�

#define BUFSIZE     256                          // �o�b�t�@�T�C�Y
#define RECVSIZE    65536                        // ��M�o�b�t�@�T�C�Y


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
	//�J�n
	//������version�ƃ|�C���^
	err = WSAStartup(MAKEWORD(1, 0), &wsaData);
	if (err != 0) {
		switch (err) {
		case WSASYSNOTREADY:
			//�l�b�g���[�N�T�u�V�X�e�����l�b�g���[�N�ւ̐ڑ��������ł��Ă��Ȃ�
			MessageBox(0, TEXT("WSASYSNOTREADY"), TEXT("ERROR"), MB_ICONWARNING);
			break;
		case WSAVERNOTSUPPORTED:
			//�v�����ꂽwinsock�̃o�[�W�������T�|�[�g����Ă��Ȃ�
			MessageBox(0, TEXT("WSAVERNOTSUPPORTED"), TEXT("ERROR"), MB_ICONWARNING);
			break;
		case WSAEINPROGRESS:
			//�u���b�L���O����̎��s���ł��邩�A �܂��̓T�[�r�X�v���o�C�_���R�[���o�b�N�֐����������Ă���
			MessageBox(0, TEXT("WSAEINPROGRESS"), TEXT("ERROR"), MB_ICONWARNING);
			break;
		case WSAEPROCLIM:
			//winsock�������ł���ő�v���Z�X���ɒB����
			MessageBox(0, TEXT("WSAEPROCLIM"), TEXT("ERROR"), MB_ICONWARNING);
			break;
		case WSAEFAULT:
			//�������ł���lpWSAData �͗L���ȃ|�C���^�ł͂Ȃ�
			MessageBox(0, TEXT("WSAEFAULT"), TEXT("ERROR"), MB_ICONWARNING);
			break;
		}
	}
	else
	{

		{

		// �z�X�g���擾����

		char name[256];
		int err_no;                                // �G���[�i���o�[

		if (gethostname(name, sizeof(name)) == 0){
			printf("���̃R���s���[�^�̖��O��%s�ł�\n", name);
		}
		else{
			err_no = WSAGetLastError();
			MessageBox(0, TEXT("�z�X�g���̎擾�Ɏ��s���܂����B"), TEXT("ERROR:" + err_no), MB_ICONWARNING);
			exit(0);
		}


		//IP�A�h���X�擾
		//�����̓z�X�g�����i�[���ꂽ�����z��̃|�C���^

		char lpszIP[16];
		PHOSTENT phostent;
		IN_ADDR in;

		if ((phostent = gethostbyname(name)) != NULL){
			memcpy(&in, phostent->h_addr, 4);
			wsprintf(lpszIP, inet_ntoa(in));
			printf("IP�A�h���X�F%s\n", lpszIP);
		}
		else{
			err_no = WSAGetLastError();
			MessageBox(0, TEXT("IP�A�h���X�̎擾�Ɏ��s���܂����B"), TEXT("ERROR:" + err_no), MB_ICONWARNING);
			exit(0);
		}




		// IP�A�h���X����z�X�g���擾����
		//10�i������R���s���[�^���킩��o�C�i���`����IP�A�h���X�ɕϊ�

		u_long ulIPAddress = inet_addr(lpszIP);
		char lpszHostName[256];        // �z�X�g�l�[���i�[�̈�
		PHOSTENT nam;

		if ((nam = gethostbyaddr((char *)&ulIPAddress, 4, PF_INET)) != NULL){
			wsprintf(lpszHostName, "%s", nam->h_name);
		}
		else{
			err_no = WSAGetLastError();
			MessageBox(0, TEXT("IP�A�h���X����z�X�g���̎擾�Ɏ��s���܂����B"), TEXT("ERROR:" + err_no), MB_ICONWARNING);
			exit(0);
		}


		// �|�[�g�ԍ��擾����

		PSERVENT pservent;

		if ((pservent = getservbyname("smtp", "tcp")) != NULL){
			printf("%s�v���g�R���𗘗p����%s�T�[�r�X�̓|�[�g�ԍ�%d���g�p���܂��B\n",
				pservent->s_proto,
				pservent->s_name,
				ntohs(pservent->s_port));
		}
		else{
			err_no = WSAGetLastError();
			MessageBox(0, TEXT("�|�[�g�ԍ����擾�ł��܂���ł����B"), TEXT("ERROR:" + err_no), MB_ICONWARNING);
		}
	}

		///////////////////////////////

		// �\�P�b�g�쐬
		int soc;                                    // �\�P�b�g
		soc = socket(AF_INET, SOCK_STREAM, 0);
		if (soc == INVALID_SOCKET){
			printf("�\�P�b�g�쐬���s�ł�\n");
			printf("�G���[%d���������܂���\n", WSAGetLastError());
			return -1;
		}

		// �T�[�o��IP�A�h���X�擾
		PHOSTENT phostent;                          // �T�[�o�̏����w���|�C���^
		unsigned long ulIPAddress;                  // �T�[�o��IP�A�h���X�i�[�ϐ�
		ulIPAddress = inet_addr(ServerName);        // IP�A�h���X�擾
		// inet_addr()�֐������s�@ServerName���z�X�g���ł������ꍇ���̏����ɓ���
		if (ulIPAddress == -1){
			if ((phostent = gethostbyname(ServerName)) != NULL){
				ulIPAddress = *((unsigned long *)(phostent->h_addr));
			}
			else{
				printf("�z�X�g�A�h���X�擾���s�ł�\n");
				printf("�G���[%d���������܂���\n", WSAGetLastError());
				closesocket(soc);                    // �\�P�b�g�̔j��
				return -1;
			}
		}

		// �T�[�o�֐ڑ�
		SOCKADDR_IN     addrServer;                                       // �T�[�o�̃A�h���X
		addrServer.sin_family = AF_INET;                            // �A�h���X�t�@�~���̎w��
		addrServer.sin_addr.s_addr = ulIPAddress;                        // �T�[�o��IP�A�h���X�̎w��
		addrServer.sin_port = htons((unsigned short)Port);        // �|�[�g�ԍ��̎w��
		if (connect(soc, (LPSOCKADDR)&addrServer, sizeof(addrServer)) == SOCKET_ERROR){
			printf("�T�[�o�ւ̐ڑ����s�ł�\n");
			printf("�G���[%d���������܂���\n", WSAGetLastError());
			closesocket(soc);                        // �\�P�b�g�̔j��
			return -1;
		}

		// �T�[�o�� GET ���N�G�X�g�𑗐M
		char request[BUFSIZE] = "GET http://www.geocities.co.jp/Playtown-Domino/1056/index.html HTTP/1.0\r\n\r\n";
		//sprintf(request, "GET http://www.geocities.co.jp/Playtown-Domino/1056/index.html HTTP/1.0\r\n\r\n", ServerName, Html);
		if (send(soc, request, sizeof(request), 0) == SOCKET_ERROR){
			printf("�T�[�o�ւ̑��M���s�ł�\n");
			printf("�G���[%d���������܂���\n", WSAGetLastError());
			shutdown(soc, 2);                        // ����M�𖳌��ɂ���
			closesocket(soc);                        // �\�P�b�g�̔j��
			return -1;
		}

		// �f�[�^�̎�M
		char recv_buf[RECVSIZE];
		int nBytesRecv;
		while (1){    // 1��ł͎�M������Ȃ��̂ŁA��M���I���܂ŌJ��Ԃ�
			nBytesRecv = recv(soc, recv_buf, sizeof(recv_buf), 0);
			if (nBytesRecv == SOCKET_ERROR){
				printf("�T�[�o����̎�M���s�ł�\n");
				printf("�G���[%d���������܂���\n", WSAGetLastError());
				break;
			}
			else if (nBytesRecv == 0){                 // ��M�I���
				break;
			}
			recv_buf[nBytesRecv] = '\0';               // ��M�o�b�t�@�̌���NULL��t������
			printf("%s", recv_buf);                  // ��ʂɎ�M����html��\��
		}

		shutdown(soc, 2);                            // ����M�𖳌��ɂ���
		closesocket(soc);                           // �\�P�b�g�̔j��

	}

	//�I��
	WSACleanup();

	return 0;
}