
#ifndef _TESTCHARA_H_
#define _TESTCHARA_H_

#include "Character.h"

class CTestChara :public CCharacter
{
public:
	CTestChara();

	//初期化を行う関数(一度のみ呼ばれる)
	void Start();

	//更新を行う関数
	void Update();

	//描画を行う関数
	void Render();
private:
};
#endif //_TESTCHARA_H_