#include "BattleScene.h"
#include "ObjectManager.h"
#include "SceneManager.h"

#include "TestStage.h"

#include "TestItem.h"
#include "GreatSowrd.h"

HRESULT CBattleScene::Start()
{
	m_ppCamera = new CCamera*();
	m_pMainCamera = new CGameCamera(1);
	m_pShadowCamera = new CCamera();

	//カメラ登録
	SINSTANCE(CObjectManager)->SetCamera(m_ppCamera);
	SINSTANCE(CObjectManager)->SetLightCamera(m_pShadowCamera);

	//カメラの距離設定
	m_pMainCamera->Dist(D3DXVECTOR3(0.0f, 40.0f, -300.0f));
	m_pShadowCamera->Dist(D3DXVECTOR3(80.0f, 1100.0f, -1600.0f));
	m_pMainCamera->Near(60);
	m_pMainCamera->Far(8000);

	m_pShadowCamera->Near(1100);
	m_pShadowCamera->Far(4000);

	*m_ppCamera = m_pMainCamera;

	//ステージ読み込み
	CTestStage* TestStage = (CTestStage*)SINSTANCE(CObjectManager)->Add(new CTestStage("TestStage"));
	//
	m_CreateStage.Create("abc");
	
	FOR(4)
	{
		//プレイヤー読み込み(前のシーンで登録済み)
		string num; 
		Support::IntToString(&num,i + 1);
		m_Player[i] = (CPlayer*)SINSTANCE(CObjectManager)->FindObject("Player"+num, DIMENSION::D3);
		//居るなら
		if (m_Player != nullptr)
		{
			m_Player[i]->SetCamera(m_ppCamera);
			m_Player[i]->SetLightCamera(m_pShadowCamera);
			//このシーンが終了したら解放されるように設定
			m_Player[i]->Active(true);
		}
	}
	
	//アイテム
	m_ItemSwitch.push_back(new CTestItem);
	m_ItemSwitch.push_back(new CGreatSowrd);
	//アイテムマネージャー初期化
	m_ItemManager.Start(&m_ItemSwitch,100);

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
	D3DXVECTOR3 pos = m_Player[0]->Transform()->LocalPosition;
	pos.y += 10;
	m_pMainCamera->TargetPos(pos);
	m_pShadowCamera->TargetPos(VECTOR3_ZERO);

	m_ItemManager.Update();

	if (m_ItemManager.ItemList()->size() > 0)
	m_Player[0]->SetItem(*m_ItemManager.ItemList());


	//セレクトシーンへ移行
	if (GetAsyncKeyState(VK_P))
	{
		m_ItemSwitch.clear();
		//アイテム削除
		m_ItemManager.clear();
		//カメラを解放
		SAFE_DELETE(m_pMainCamera);
		SAFE_DELETE(m_pShadowCamera);
		SAFE_DELETE(m_ppCamera);
		//セレクトシーンに切り替え
		SINSTANCE(CSceneManager)->ChangeScene(SCENE::CHARASELECT);
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
	};

	CRenderTarget::RemoveRenderTarget(2);
	CRenderTarget::BeforeRenderTarget();

	m_depth.DepthofField(&m_tex[0], &m_tex[1]);

	//m_i.SetTex(m_tex[0]);
	//m_i.Render();

	
	return S_OK;
}