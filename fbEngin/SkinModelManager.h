
#ifndef _SKINMODELMANAGER_H_
#define _SKINMODELMANAGER_H_

#include "SkinModelData.h"

class CSkinModelManager
{
public:
	~CSkinModelManager();
	
	//3D���f����ǂݍ���,���f���f�[�^�̎Q�Ƃ�ێ����A�f�[�^�̒l��Ԃ�
	//�������Fstring �t�@�C���̖��O
	CSkinModelData LoadModel(string filename);
	//�C���X�^���X��Ԃ�
	static CSkinModelManager* getInstance();
private:
	map<UINT64, CSkinModelData*> m_ModelDataMap;
	static CSkinModelManager* m_pInstance;
};

#endif //_SKINMODELMANAGER_H_