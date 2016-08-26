#include "SkinModelManager.h"

CSkinModelManager* CSkinModelManager::m_pInstance = new CSkinModelManager();

CSkinModelData CSkinModelManager::LoadModel(string filename)
{
	//���O����n�b�V������
	UINT64 hash = Support::MakeHash(filename);

	//�o�^����ĂȂ�
	if (m_ModelDataMap[hash] == nullptr)
	{
		//����
		CSkinModelData* date = new CSkinModelData();
		//�t�@�C���p�X����
		string filepath = "Xfile/" + filename;
		//�ǂݎ��
		date->LoadModelData(filepath.c_str());
		//�o�^
		m_ModelDataMap[hash] = date;
	}
	//�l�����������Ă���
	return *m_ModelDataMap[hash];
}

CSkinModelManager* CSkinModelManager::getInstance()
{
	//�Ȃ������ꍇ������
	if (m_pInstance == NULL)
	{
		m_pInstance = new CSkinModelManager();
	}
	return m_pInstance;
}