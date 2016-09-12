#include "SkinModelManager.h"

CSkinModelManager* CSkinModelManager::m_pInstance = new CSkinModelManager();

CSkinModelData CSkinModelManager::LoadModel(string filename, ID3DXAnimationController** pAnime)
{
	//���O����n�b�V������
	UINT64 hash = Support::MakeHash(filename);

	//�o�^����ĂȂ�
	if (m_ModelDataMap[hash] == nullptr)
	{
		//����
		CSkinModelData* Original = new CSkinModelData();
		//�t�@�C���p�X����
		string filepath = "Xfile/" + filename;
		//�ǂݎ��
		Original->LoadModelData(filepath.c_str());
		//�o�^
		m_ModelDataMap[hash] = Original;
	}
	
	//�I���W�i�����f���̃A�j���[�V�����R���g���[���[����R�s�[
	if (pAnime)
	{
		m_ModelDataMap[hash]->GetAnimationController()->CloneAnimationController
			(
			m_ModelDataMap[hash]->GetAnimationController()->GetMaxNumAnimationOutputs(),
			m_ModelDataMap[hash]->GetAnimationController()->GetMaxNumAnimationSets(),
			m_ModelDataMap[hash]->GetAnimationController()->GetMaxNumTracks(),
			m_ModelDataMap[hash]->GetAnimationController()->GetMaxNumEvents(),
			pAnime
			);
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