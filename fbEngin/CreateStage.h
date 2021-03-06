
#ifndef _CREATESTAGE_H_
#define _CREATESTAGE_H_

//ファイルからステージを生成するクラス
class CCreateStatge
{
public:
	CCreateStatge();
	~CCreateStatge();

	//ステージ作成
	//第一引数：const char* ファイルネーム
	void Create(const char* filename);
	//バイナリファイルを読み取り
	//第一引数：const char* ファイルネーム
	//第二引数：int[] int型の配列
	//第三引数：int 配列の要素数
	//戻り値：int 読み込んだデータ数
	int ReadBinary(const char* filepname,int* OutArray,int size);
private:

};

#endif //_CREATESTAGE_H_