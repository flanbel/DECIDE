#include "Player.h"

CPlayer::CPlayer(string name) : C3DObject(name)
{
	m_pChara = nullptr;
	m_pHasItem = nullptr;
}

CPlayer::~CPlayer()
{
	//キャラクター情報解放
	SAFE_DELETE(m_pChara);
}

void CPlayer::Start()
{
	//キャラクター初期化
	m_pChara->Start();
	//初期化
	m_show.Start();
	m_show.SetCamera(m_pCamera);
	//モデルデータセット
	m_model.SetModelData(m_pChara->GetModelData());
	//キャラクターのステータス代入
	m_State = m_pChara->GetState();

	//m_model.RenderType(TYPE::SPECULAR,true);

	m_Transform.LocalRotation = D3DXVECTOR3(-90.0, 0.0, 0.0);
	m_dir = VECTOR3_ZERO;
}

void CPlayer::Update()
{
	//キーボード更新
	m_input.UpdateKeyboardState();

	//各アクション実行
	Turn();
	Move();

	if (GetAsyncKeyState(VK_N))
	{
		m_pChara->PlayAnimation(0, 100.0f);
	}
	if (GetAsyncKeyState(VK_M))
	{
		m_pChara->PlayAnimation(1, 100.0f);
	}
	
	//アイテムを捨てる
	ThrowAwayItem();

	//キャラクター更新
	m_pChara->Update();
	m_Transform.UpdateTransform();
}

void CPlayer::LateUpdate()
{
	//m_model.UpdateFrameMatrix();
}

void CPlayer::Render()
{
	m_model.Render(m_pCamera,m_pLight);
	if (g_DebugMode)
	{
		//モデルのコリジョン表示
		m_show.ShowFrameCollision(m_pChara->GetModelData()->GetFrameRoot(), m_Transform.WorldMatrix());
		if (m_pHasItem != nullptr)
			m_show.ShowFrameCollision(m_pHasItem->GetModelData().GetFrameRoot(), m_pChara->GetHand()->CombinedTransformationMatrix);
	}
}

void CPlayer::Move()
{
	//向きを求めて正規化
	D3DXVECTOR3 ver = { 0.0f, 0.0f,1.0f };
	float theta = D3DXToRadian(-m_Transform.LocalRotation.y);
	//回転
	m_dir.x = ver.x * cos(theta) - ver.z * sin(theta);
	m_dir.z = ver.x * sin(theta) + ver.z * cos(theta);

	float delta = (float)SINSTANCE(CTimer)->DeltaTime();
	//スピード倍率
	float speedratio = 1.0f + ((m_State.speed - 3) * 0.1);

	//簡易移動
	//前
	if (m_input.isKeyDown(VK_W))
	{
		m_Transform.LocalPosition += m_dir * speedratio;// * 60.0f * delta;
	}
	//後ろ
	if (m_input.isKeyDown(VK_S))
	{
		m_Transform.LocalPosition -= m_dir * speedratio;// *60.0f * delta;
	}
}

void CPlayer::Turn()
{
	float delta = (float)SINSTANCE(CTimer)->DeltaTime();

	//右
	if (m_input.isKeyDown(VK_D))
	{
		m_Transform.LocalRotation.y += 120.0f * delta;
	}
	//左
	if (m_input.isKeyDown(VK_A))
	{
		m_Transform.LocalRotation.y -= 120.0f * delta;
	}
}

void CPlayer::SetItem(const list<CItem*>& itemlist)
{
	//アイテムを持っていない かつ
	//手がある　かつ
	//Xキーが押されたなら
	if (m_pHasItem == nullptr &&
		m_pChara->GetHand() != nullptr &&
		m_input.isPressed(VK_X))
	{
		m_pHasItem = NearItem(itemlist);
		//フラグON
		m_pHasItem->Has();
		//手の行列を親に設定(アニメーション連動)
		m_pHasItem->SetParent(&m_pChara->GetHand()->CombinedTransformationMatrix);
	}
}

void CPlayer::ThrowAwayItem()
{
	//アイテムを持っているなら Zキーで捨てる
	if (m_pHasItem != nullptr &&
		m_input.isPressed(VK_Z))
	{
		//今の場所にアイテムを捨てる
		m_pHasItem->Throw(m_Transform);
		//アイテムをnullptrに
		m_pHasItem = nullptr;
	}
}

CItem* CPlayer::NearItem(const list<CItem*>& itemlist)
{
	float min = 999999;
	CItem* Near = nullptr;
	for each(CItem* item in itemlist)
	{
		D3DXVECTOR3 vec = m_Transform.Position - item->Transform()->Position;
		//長さ
		float len = sqrt(pow(vec.x, 2) + pow(vec.y, 2) + pow(vec.z, 2));
		if (len < min)
		{
			//値更新
			min = len;
			Near = item;
		}
	}

	return Near;
}