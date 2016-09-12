#include "CharaSelectScene.h"
#include "ObjectManager.h"
#include "SceneManager.h"

#include "Player.h"
//キャラクター
#include "TestChara.h"
#include "TVman.h"
#include "Robo.h"

CCharaSelectScene::CCharaSelectScene()
{
	
}

CCharaSelectScene::~CCharaSelectScene()
{

}

HRESULT CCharaSelectScene::Start()
{
	//背景
	CImage* SelectBack = (CImage*)SINSTANCE(CObjectManager)->Add(new CImage("SelectBack"));
	SelectBack->LoadTex("SelectBack.png");
	SelectBack->Transform()->LocalPosition = D3DXVECTOR3(1040, 520, 0);
	SelectBack->Transform()->LocalScale = D3DXVECTOR3(1.7f, 1.5f, 1.0f);
	
	//戻るボタン
	m_BackB = (CImage*)SINSTANCE(CObjectManager)->Add(new CImage("BackB"));
	m_BackB->Transform()->LocalPosition = D3DXVECTOR3(100, 110, 0);
	m_BackB->LoadTex("BackB.png");	

	//キャラクター情報読み込み(こいつらはオブジェクトマネージャーに登録していないのでデリートすること)
	CTestChara* TestChara = new CTestChara();
	TestChara->Start();
	//TVman 
	CTVman* TVman = new CTVman();
	TVman->Start();
	//Robo
	CRobo* Robo = new CRobo();
	Robo->Start();

	//キャラクターリストに登録
	m_CharacterList.push_back(TestChara);
	m_CharacterList.push_back(TVman);
	m_CharacterList.push_back(Robo);

	//キャラクター選択生成
	FOR(MAX_PLAYER_NUM)
	{
		string n; 
		Support::IntToString(&n, i+1);
		m_Select[i] = (CCharacterSelect*)SINSTANCE(CObjectManager)->Add(new CCharacterSelect(i+1,"Select" + n));
		m_Select[i]->Transform()->LocalPosition = D3DXVECTOR3(170.0f + (i * 315.0f), 440.0f, 0.0f);
		m_Select[i]->SetCharaList(m_CharacterList);
	}

	//タイマー初期化
	m_timer = 0.0;

	return S_OK;
}

HRESULT CCharaSelectScene::Update()
{

	m_input.UpdateKeyboardState();

	//選択されているプレイヤーの数(何人決定されているか？)
	//プレイヤー数初期化
	short SelectPlayerNum = 0;
	FOR(MAX_PLAYER_NUM)
	{
		//キャラクターが選択されている
		if (m_Select[i]->GetSelectChara() != nullptr)
		{
			SelectPlayerNum++;
		}
	}

	//タイトルにバック
	if (m_input.isKeyDown(VK_B) ||
		g_Controller[0].IsPressButton(XINPUT_GAMEPAD_A))
	{
		m_timer += SINSTANCE(CTimer)->DeltaTime();
		m_BackB->SetAlpha(0.5f);
		//一定以上押されていたら
		if (m_timer > 0.8)
		{
			SINSTANCE(CSceneManager)->ChangeScene(SCENE::TITLE);
			DeleteCharacterList();
			return S_OK;
		}
	}
	else
	{
		m_timer = 0.0;
		m_BackB->SetAlpha(1.0f);
	}

	//戦闘シーンに遷移
	if (SelectPlayerNum > 0 &&
		m_input.isPressed(VK_SPACE)||
		g_Controller[0].isPushButton(XINPUT_GAMEPAD_START))
	{
		//プレイヤー
		SetPlayer();
		SINSTANCE(CSceneManager)->ChangeScene(SCENE::BATTLE);
		//キャラクターたちデリート
		DeleteCharacterList();
		return S_OK;
	}

	return S_OK;
}

HRESULT CCharaSelectScene::Draw()
{
	SINSTANCE(CObjectManager)->RenderObject();
	return S_OK;
}

void CCharaSelectScene::SetPlayer()
{
	FOR(MAX_PLAYER_NUM)
	{
		string num;
		Support::IntToString(&num, i+1);
		CCharacter* chara = m_Select[i]->GetSelectChara();

		//キャラクターが選択されている
		if (chara != nullptr)
		{
			//プレイヤー登録
			//シーンをまたいでも残るように設定
			CPlayer* Player = (CPlayer*)SINSTANCE(CObjectManager)->Add(new CPlayer(i+1,"Player" + num), false);

			//typeidを使いクラスで比較している
			//もっとスマートにできるはず・・・
			//Player->SetCharacter(chara);
			if (typeid(CTestChara) == typeid(*chara))
			{
				Player->SetCharacter(new CTestChara);
			}
			else if (typeid(CTVman) == typeid(*chara))
			{
				Player->SetCharacter(new CTVman);
			}
			else if (typeid(CRobo) == typeid(*chara))
			{
				Player->SetCharacter(new CRobo);
			}
		}
	}
}

void CCharaSelectScene::DeleteCharacterList()
{
	for each (CCharacter* c in m_CharacterList)
	{
		SAFE_DELETE(c);
	}
	m_CharacterList.clear();
}