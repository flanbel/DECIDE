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
	//キャッシュ機能未実装

	////シーンの添え字切り替え
	//m_nowScene = key;

	//if (HitCache(key) != -1)
	//{
	//	//キャッシュに残ってた場合アップデートのみ

	//	//アップデートも呼びなおす
	//	SINSTANCE(CObjectManager)->UpdateObject();
	//	m_scenes[m_nowScene]->Update();
	//	//LateUpdateはまだ呼ばなくていい
	//}
	//else
	//{
	//	//キャッシュにないなら初期化も行う

	//	//初期化する
	//	CSceneManager::StartScene();

	//	//アップデート
	//	SINSTANCE(CObjectManager)->UpdateObject();
	//	m_scenes[m_nowScene]->Update();
	//	//LateUpdateはまだ呼ばなくていい
	//}

	////オブジェクト解放
	//SINSTANCE(CObjectManager)->ReleaseObject();

	////キャッシュに追加
	//AddCache(m_nowScene);
	//SINSTANCE(CObjectManager)->SetCasheIdx(HitCache);


	SINSTANCE(CObjectManager)->ReleaseObject();

	//シーンの添え字切り替え
	m_nowScene = key;

	//フェード初期化
	m_scenes[m_nowScene]->InitFade();
	//初期化する
	CSceneManager::StartScene();

	//アップデート
	SINSTANCE(CObjectManager)->UpdateObject();
	m_scenes[m_nowScene]->Update();
	//LateUpdateはまだ呼ばなくていい
}

void CSceneManager::AddCache(SCENE c)
{
	short hit = 0;

	FOR(SCENECASHE_NUM)
	{
		//同じシーンがキャッシュにあったなら
		if (m_Cache[i] == c)
		{
			//添え字を返す
			hit = i;
		}
	}

	for (short i = hit; i < SCENECASHE_NUM - 1; i++)
	{
		//一つ上に押し上げ
		m_Cache[i] = m_Cache[i + 1];
	}

	//最後尾に追加
	m_Cache[SCENECASHE_NUM - 1] = c;
}

short CSceneManager::HitCache(SCENE c)
{
	FOR(SCENECASHE_NUM)
	{
		//キャッシュにあるかどうか
		if (m_Cache[i] == c)
			return i;
	}
	//ヒットしなければ-1
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