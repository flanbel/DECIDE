
#ifndef _STAGEOBJECT_H_
#define _STAGEOBJECT_H_

#include "3DObject.h"
#include "SkinModelData.h"
#include "SkinModelManager.h"

//ステージ上のオブジェクト
class CStageObject : public C3DObject
{
public:
	//ファイル名
	CStageObject(const char *xfile, string name = "");
	~CStageObject();
	//初期化を行う関数(一度のみ呼ばれる)
	void Start()override;

	//更新を行う関数
	void Update()override;

	//描画を行う関数
	void Render()override;
private:
	//モデルデータ
	CSkinModelData m_ModelData;
};



#endif //_STAGEOBJECT_H_