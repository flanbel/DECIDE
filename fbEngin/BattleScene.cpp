#include "BattleScene.h"
#include "ObjectManager.h"
#include "SceneManager.h"

#include "TestChara.h"
#include "TestStage.h"
#include "TestItem.h"

HRESULT CBattleScene::Start()
{
	m_ppCamera = new CCamera*();
	m_pMainCamera = new CCamera();
	m_pShadowCamera = new CCamera();

	//カメラの距離設定
	m_pMainCamera->Dist(D3DXVECTOR3(0.0f, 100.0f, -150.0f));
	m_pShadowCamera->Dist(D3DXVECTOR3(60.0f, 160.0f, -200.0f));

	*m_ppCamera = m_pMainCamera;

	//カメラ登録
	SINSTANCE(CObjectManager)->SetCamera(m_ppCamera);
	SINSTANCE(CObjectManager)->SetLightCamera(m_pShadowCamera);

	//ステージ読み込み
	CTestStage* TestStage = (CTestStage*)SINSTANCE(CObjectManager)->Add(new CTestStage("TestStage"));
	
	FOR(4)
	{
		//プレイヤー読み込み(前のシーンで登録済み)
		m_Player = (CPlayer*)SINSTANCE(CObjectManager)->FindObject("Player1", DIMENSION::D3);
		//居るなら
		if (m_Player != nullptr)
		{
			m_Player->SetCamera(m_ppCamera);
			m_Player->SetLightCamera(m_pShadowCamera);
			//このシーンが終了したら解放されるように設定
			m_Player->Leave(false);
		}
	}
	
	//アイテム
	m_ItemSwitch.push_back(new CTestItem);
	//アイテムマネージャー初期化
	m_ItemManager.Start(m_ppCamera, &m_ItemSwitch);

	m_RenderTarget[0].CreateRenderTarget(&m_tex[0], GAME_CLIENT_WIDTH, GAME_CLIENT_HEIGHT);
	m_RenderTarget[1].CreateRenderTarget(&m_tex[1], GAME_CLIENT_WIDTH, GAME_CLIENT_HEIGHT);

	m_ShadowBuffer.CreateRenderTarget(&m_Shadowtex, GAME_CLIENT_WIDTH, GAME_CLIENT_HEIGHT);

	m_depth.Initialize();

	m_i.Transform()->Position = D3DXVECTOR3(GAME_CLIENT_WIDTH / 2, GAME_CLIENT_HEIGHT / 2, 0.0f);

	return S_OK;
}

HRESULT CBattleScene::Update()
{
	//プレイヤーの頭を見るように調整
	D3DXVECTOR3 pos = m_Player->Transform()->LocalPosition;
	pos.y += 10;
	m_pMainCamera->TargetPos(pos);
	m_pShadowCamera->TargetPos(pos);

	m_ItemManager.Update();

	if (m_ItemManager.ItemList()->size() > 0)
	m_Player->SetItem(*m_ItemManager.ItemList());

	if (GetAsyncKeyState(VK_P))
	{
		SINSTANCE(CSceneManager)->ChangeScene(SCENE::CHARASELECT);
		m_ItemSwitch.clear();
		m_ItemManager.clear();
		SAFE_DELETE(m_pMainCamera);
		SAFE_DELETE(m_pShadowCamera);
		SAFE_DELETE(m_ppCamera);
		return S_OK;
	}
	
	return S_OK;
}

HRESULT CBattleScene::Draw()
{
	//影生成
	{
		//ライトカメラに切り替え
		*m_ppCamera = m_pShadowCamera;
		m_pShadowCamera->Update();

		m_ShadowBuffer.SetRenderTarget(1);

		//オブジェクト描画
		SINSTANCE(CObjectManager)->RenderObject();
		m_ItemManager.Render();
	};
	CRenderTarget::RemoveRenderTarget(1);

	//影の画像設定
	SINSTANCE(CObjectManager)->SetLightDepth(m_Shadowtex);

	//描画
	{
		//メインカメラに切り替え
		*m_ppCamera = m_pMainCamera;
		m_pMainCamera->Update();

		//[0]は元画像
		//[1]は深度画像
		m_RenderTarget[0].SetRenderTarget(0);
		m_RenderTarget[1].SetRenderTarget(2);

		

		SINSTANCE(CObjectManager)->RenderObject();

		m_ItemManager.Render();
	};

	CRenderTarget::RemoveRenderTarget(2);
	CRenderTarget::BeforeRenderTarget();

	m_depth.DepthofField(&m_tex[0], &m_tex[1]);

	//m_i.SetTex(m_tex[0]);
	//m_i.Render();

	
	return S_OK;
}