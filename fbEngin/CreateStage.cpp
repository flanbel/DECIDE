#include "CreateStage.h"
#include <fstream>

#include "ObjectManager.h"
#include "StageObject.h"

CCreateStatge::CCreateStatge()
{
}

CCreateStatge::~CCreateStatge()
{
}

void CCreateStatge::Create(const char* filename)
{
	string bin, na, Bpath, Npath;
	bin = ".bin";
	na = ".name";
	Bpath = filename + bin;
	Npath = filename + na;
	FILE *Ofp, *Nfp;
	errno_t err;	//エラー確認
	//Object
	if (err = fopen_s(&Ofp, Bpath.c_str(), "rb") != 0)
	{
		//エラーだよん
		string name = Bpath;
		string error = "ファイルパス：" + name
			+ "\nファイルが存在しない、又はパスが違う可能性があります";
		MessageBoxA(NULL, error.c_str(), TEXT("error:ファイルが開けませんでした。"), MB_OK);
	}

	//Name
	std::ifstream in(Npath);

	int binary[900];
	ZeroMemory(binary, 900);
	//読み込み
	int cnt = fread_s(binary, 900, sizeof(int), 900, Ofp);

	char name[256];

	D3DXVECTOR3 pos, rot, sca;
	for (short i = 0; i < cnt; i += 9)
	{
		in >> name;
		pos.x = binary[i];
		pos.y = binary[i + 1];
		pos.z = binary[i + 2];

		rot.x = binary[i + 3];
		rot.y = binary[i + 4];
		rot.z = binary[i + 5];

		sca.x = binary[i + 6];
		sca.y = binary[i + 7];
		sca.z = binary[i + 8];

		string a = "Field/";
		string X = ".X";
		string p = a + name + X;
		//生成
		CStageObject* obj = new CStageObject(p.c_str());
		obj->Transform()->LocalPosition = pos;
		obj->Transform()->LocalRotation = rot;
		obj->Transform()->LocalScale = sca;
		//登録
		SINSTANCE(CObjectManager)->Add(obj);
	}

	fclose(Ofp);
}

int CCreateStatge::ReadBinary(const char* filename, int* OutArray, int size)
{
	FILE* fp;
	errno_t err;	//エラー確認
	//ファイル開くよ
	if (err = fopen_s(&fp, filename, "rb") != 0)
	{
		//エラーだよん
		string name = filename;
		string error = "ファイルパス：" + name
			+ "\nファイルが存在しない、又はパスが違う可能性があります";
		MessageBoxA(NULL, error.c_str(), TEXT("error:ファイルが開けませんでした。"), MB_OK);
	}

	ZeroMemory(OutArray, size);
	//読み込み
	int count = fread_s(OutArray, size, sizeof(int), 3, fp);
	fread_s(OutArray, size, sizeof(int), 3, fp);
	fread_s(OutArray, size, sizeof(int), 3, fp);

	fclose(fp);

	return count;
}