
#ifndef _SHOWCOLLISION_H_
#define _SHOWCOLLISION_H_

#include "3DObject.h"
#include "Collision.h"
#include "SkinModelData.h"

class CShowCollision:public C3DObject
{
public:
	CShowCollision(string name = "");
	//初期化を行う関数(一度のみ呼ばれる)
	void Start();

	//更新を行う関数
	void Update();

	//描画を行う関数
	void Render();
	//フレームのあたり判定表示(仮)
	//第一引数:const LPD3DXFRAME フレーム
	void ShowFrameCollision(const LPD3DXFRAME pFrameBase,const D3DXMATRIX& world);

	//コリジョン設定
	//void SetCollision(BoxCollision box);
private:
	CSkinModelData m_data;
};

#endif //_SHOWCOLLISION_H_