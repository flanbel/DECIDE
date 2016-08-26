
#ifndef _TESTSTAGE_H_
#define _TESTSTAGE_H_

#include "Stage.h"

//てすや
class CTestStage: public CStage
{
public:
	CTestStage(string name = "") :CStage(name){};

	//初期化を行う関数(一度のみ呼ばれる)
	void Start();

	//更新を行う関数
	void Update();

	//描画を行う関数
	void Render();
private:
};

#endif //_TESTSTAGE_H_