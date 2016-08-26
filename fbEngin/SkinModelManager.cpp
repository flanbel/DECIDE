#include "SkinModelManager.h"

CSkinModelManager* CSkinModelManager::m_pInstance = new CSkinModelManager();

CSkinModelData CSkinModelManager::LoadModel(string filename)
{
	//名前からハッシュ生成
	UINT64 hash = Support::MakeHash(filename);

	//登録されてない
	if (m_ModelDataMap[hash] == nullptr)
	{
		//生成
		CSkinModelData* date = new CSkinModelData();
		//ファイルパス生成
		string filepath = "Xfile/" + filename;
		//読み取り
		date->LoadModelData(filepath.c_str());
		//登録
		m_ModelDataMap[hash] = date;
	}
	//値を引っ張ってくる
	return *m_ModelDataMap[hash];
}

CSkinModelManager* CSkinModelManager::getInstance()
{
	//なかった場合初期化
	if (m_pInstance == NULL)
	{
		m_pInstance = new CSkinModelManager();
	}
	return m_pInstance;
}