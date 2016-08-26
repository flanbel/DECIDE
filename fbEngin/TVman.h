
#ifndef _TVMAN_H_
#define _TVMAN_H_

#include "Character.h"

//テレビマン
class CTVman :public CCharacter
{
public:
	CTVman();

	//初期化を行う関数(一度のみ呼ばれる)
	void Start();

	//更新を行う関数
	void Update();

	//描画を行う関数
	void Render();
private:
};
#endif //_TVMAN_H_