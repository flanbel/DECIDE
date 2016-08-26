
#ifndef _SKINMODELMANAGER_H_
#define _SKINMODELMANAGER_H_

#include "SkinModelData.h"

class CSkinModelManager
{
public:
	~CSkinModelManager();
	
	//3Dモデルを読み込み,モデルデータの参照を保持し、データの値を返す
	//第一引数：string ファイルの名前
	CSkinModelData LoadModel(string filename);
	//インスタンスを返す
	static CSkinModelManager* getInstance();
private:
	map<UINT64, CSkinModelData*> m_ModelDataMap;
	static CSkinModelManager* m_pInstance;
};

#endif //_SKINMODELMANAGER_H_