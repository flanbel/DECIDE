
#ifndef _GREATSOWRD_H_
#define _GREATSOWRD_H_

#include "Item.h"

//グレートソード
class CGreatSowrd : public CItem
{
public:
	CGreatSowrd(string name = "GreatSowrd") :CItem(name){};

	//初期化を行う関数(一度のみ呼ばれる)
	void Start();

	//更新を行う関数
	void Update();

	//更新の後に呼び出される関数
	void LateUpdate()override;

	//描画を行う関数
	void Render();
private:
};

#endif //_GREATSOWRD_H_