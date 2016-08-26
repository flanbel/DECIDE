
#ifndef _TESTITEM_H_
#define _TESTITEM_H_

#include "Item.h"

//てすや
class CTestItem : public CItem
{
public:
	CTestItem(string name = "") :CItem(name){};

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

#endif //_TESTITEM_H_