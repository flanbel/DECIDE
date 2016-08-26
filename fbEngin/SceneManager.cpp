#include "SceneManager.h"
#include "Scene.h"
#include "ObjectManager.h"

CSceneManager* CSceneManager::m_pInstance = new CSceneManager();

void CSceneManager::Add(CScene* pAdd)
{
	m_scenes.push_back(pAdd);
} 

void CSceneManager::StartScene()
{
	m_scenes[m_nowScene]->Start();
	SINSTANCE(CObjectManager)->AwakeObject();
	SINSTANCE(CObjectManager)->StartObject();
}

void CSceneManager::UpdateScene()
{
	SINSTANCE(CObjectManager)->UpdateObject();
	m_scenes[m_nowScene]->Update();
	SINSTANCE(CObjectManager)->LateUpdateObject();
}

void CSceneManager::DrawScene()
{
	SINSTANCE(CObjectManager)->RenderObject();
	m_scenes[m_nowScene]->Draw();

	m_scenes[m_nowScene]->DrawFade();
}

void CSceneManager::ChangeScene(SCENE key)
{
	//�L���b�V���@�\������

	////�V�[���̓Y�����؂�ւ�
	//m_nowScene = key;

	//if (HitCache(key) != -1)
	//{
	//	//�L���b�V���Ɏc���Ă��ꍇ�A�b�v�f�[�g�̂�

	//	//�A�b�v�f�[�g���ĂтȂ���
	//	SINSTANCE(CObjectManager)->UpdateObject();
	//	m_scenes[m_nowScene]->Update();
	//	//LateUpdate�͂܂��Ă΂Ȃ��Ă���
	//}
	//else
	//{
	//	//�L���b�V���ɂȂ��Ȃ珉�������s��

	//	//����������
	//	CSceneManager::StartScene();

	//	//�A�b�v�f�[�g
	//	SINSTANCE(CObjectManager)->UpdateObject();
	//	m_scenes[m_nowScene]->Update();
	//	//LateUpdate�͂܂��Ă΂Ȃ��Ă���
	//}

	////�I�u�W�F�N�g���
	//SINSTANCE(CObjectManager)->ReleaseObject();

	////�L���b�V���ɒǉ�
	//AddCache(m_nowScene);
	//SINSTANCE(CObjectManager)->SetCasheIdx(HitCache);


	SINSTANCE(CObjectManager)->ReleaseObject();

	//�V�[���̓Y�����؂�ւ�
	m_nowScene = key;

	//�t�F�[�h������
	m_scenes[m_nowScene]->InitFade();
	//����������
	CSceneManager::StartScene();

	//�A�b�v�f�[�g
	SINSTANCE(CObjectManager)->UpdateObject();
	m_scenes[m_nowScene]->Update();
	//LateUpdate�͂܂��Ă΂Ȃ��Ă���
}

void CSceneManager::AddCache(SCENE c)
{
	short hit = 0;

	FOR(SCENECASHE_NUM)
	{
		//�����V�[�����L���b�V���ɂ������Ȃ�
		if (m_Cache[i] == c)
		{
			//�Y������Ԃ�
			hit = i;
		}
	}

	for (short i = hit; i < SCENECASHE_NUM - 1; i++)
	{
		//���ɉ����グ
		m_Cache[i] = m_Cache[i + 1];
	}

	//�Ō���ɒǉ�
	m_Cache[SCENECASHE_NUM - 1] = c;
}

short CSceneManager::HitCache(SCENE c)
{
	FOR(SCENECASHE_NUM)
	{
		//�L���b�V���ɂ��邩�ǂ���
		if (m_Cache[i] == c)
			return i;
	}
	//�q�b�g���Ȃ����-1
	return -1;
}

CSceneManager* CSceneManager::getInstance()
{
	if (m_pInstance == NULL)
	{
		m_pInstance = new CSceneManager();
	}
	return m_pInstance;
}