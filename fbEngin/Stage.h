
#ifndef _STAGE_H_
#define _STAGE_H_

#include "3DObject.h"
#include "SkinModelData.h"
#include "SkinModelManager.h"

//ステージの基底クラス
class CStage : public C3DObject
{
public:
	CStage(string name = "") :C3DObject(name){};

	//初期化を行う関数(一度のみ呼ばれる)
	virtual void Start()override = 0;

	//更新を行う関数
	virtual void Update()override = 0;

	//描画を行う関数
	virtual void Render()override = 0;
protected:
	//モデルデータ
	CSkinModelData m_ModelData;
};

#endif //_STAGE_H_