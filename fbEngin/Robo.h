
#ifndef _ROBO_H_
#define _ROBO_H_

#include "Character.h"

class CRobo :public CCharacter
{
public:
	CRobo();

	//初期化を行う関数(一度のみ呼ばれる)
	void Start();

	//更新を行う関数
	void Update();

	//描画を行う関数
	void Render();
private:
};
#endif //_ROBO_H_