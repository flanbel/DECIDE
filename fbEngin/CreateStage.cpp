#include "CreateStage.h"

CCreateStatge::CCreateStatge()
{
}

CCreateStatge::~CCreateStatge()
{
}

void CCreateStatge::Create(const char* filepath)
{
	int binary[1000];
	//�o�C�i���t�@�C���𕶎���ɕϊ�
	int cnt = ReadBinary(filepath, binary,1000);
	float trans[3][3][3]; //pos,rot,sca
	ZeroMemory(trans, sizeof(float)*(3 * 3 * 3));

	FOR(cnt / 9)
	{
		trans[i][0][0] = binary[i];
		trans[i][0][1] = binary[i+1];
		trans[i][0][2] = binary[i+2];

		trans[i][1][0] = binary[i+3];
		trans[i][1][1] = binary[i+4];
		trans[i][1][2] = binary[i+5];

		trans[i][2][0] = binary[i+6];
		trans[i][2][1] = binary[i+7];
		trans[i][2][2] = binary[i+8];
	}
}

int CCreateStatge::ReadBinary(const char* filepath, int* OutArray,int size)
{
	FILE* fp;
	errno_t err;	//�G���[�m�F
	//�t�@�C���J����
	if (err = fopen_s(&fp, filepath, "rb") != 0)
	{
		//�G���[�����
		string name = filepath;
		string error = "�t�@�C���p�X�F" + name
			+ "\n�t�@�C�������݂��Ȃ��A���̓p�X���Ⴄ�\��������܂�";
		MessageBoxA(NULL, error.c_str(), TEXT("error:�t�@�C�����J���܂���ł����B"), MB_OK);
	}

	ZeroMemory(OutArray, size);
	//�ǂݍ���
	int count = fread_s(OutArray, size, sizeof(int), 3, fp);
	fread_s(OutArray, size, sizeof(int), 3, fp);
	fread_s(OutArray, size, sizeof(int), 3, fp);

	fclose(fp);

	return count;
}