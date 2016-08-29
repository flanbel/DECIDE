#include "BattleScene.h"
#include "ObjectManager.h"
#include "SceneManager.h"

#include "TestChara.h"
#include "TestStage.h"
#include "TestItem.h"

HRESULT CBattleScene::Start()
{
	//カメラ登録
	SINSTANCE(CObjectManager)->SetCamera(&m_maincamera);
	//カメラの距離設定
	m_maincamera.Dist(D3DXVECTOR3(0.0f, 100.0f, -150.0f));

	//ステージ読み込み
	CTestStage* TestStage = (CTestStage*)SINSTANCE(CObjectManager)->Add(new CTestStage("TestStage"));
	
	FOR(4)
	{
		//プレイヤー読み込み(前のシーンで登録済み)
		m_Player = (CPlayer*)SINSTANCE(CObjectManager)->FindObject("Player1", DIMENSION::D3);
		//居るなら
		if (m_Player != nullptr)
		{
			m_Player->SetCamera(&m_maincamera);
			//このシーンが終了したら解放されるように設定
			m_Player->Leave(false);
		}
	}
	
	//アイテム
	m_ItemSwitch.push_back(new CTestItem);
	//アイテムマネージャー初期化
	m_ItemManager.Start(&m_maincamera,&m_ItemSwitch);

	m_RenderTarget[0].CreateRenderTarget(&m_tex[0], GAME_CLIENT_WIDTH, GAME_CLIENT_HEIGHT);
	m_RenderTarget[1].CreateRenderTarget(&m_tex[1], GAME_CLIENT_WIDTH, GAME_CLIENT_HEIGHT);

	m_depth.Initialize();

	return S_OK;
}

HRESULT CBattleScene::Update()
{
	//プレイヤーの頭を見るように調整
	D3DXVECTOR3 pos = m_Player->Transform()->LocalPosition;
	pos.y += 10;
	m_maincamera.TargetPos(pos);

	m_ItemManager.Update();

	if (m_ItemManager.ItemList()->size() > 0)
	m_Player->SetItem(*m_ItemManager.ItemList());

	if (GetAsyncKeyState(VK_P))
	{
		SINSTANCE(CSceneManager)->ChangeScene(SCENE::CHARASELECT);
		m_ItemSwitch.clear();
		m_ItemManager.clear();
		return S_OK;
	}

	m_RenderTarget[0].SetRenderTarget(0);
	m_RenderTarget[1].SetRenderTarget(1);
	
	return S_OK;
}

HRESULT CBattleScene::Draw()
{
	m_ItemManager.Render();

	//[0]は元画像
	//[1]は深度画像

	CRenderTarget::BeforeRenderTarget();

	m_depth.DepthofField(&m_tex[0], &m_tex[1]);
	
	return S_OK;
}