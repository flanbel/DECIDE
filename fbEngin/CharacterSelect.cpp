
#include "CharacterSelect.h"
#include "ObjectManager.h"

CCharacterSelect::CCharacterSelect(string name) :C2DObject(name)
{
	//初期化
	m_SelectChara = nullptr;
};

void CCharacterSelect::Start()
{
	m_ListIdx = 0;

	//枠
	//m_pFrame = (CImage*)SINSTANCE(CObjectManager)->Add(new CImage(m_Name + "Frame"));
	m_Frame.Start();
	m_Frame.name(m_Name + "Frame");
	m_Frame.LoadTex("Fream.png");
	m_Frame.Transform()->SetParent(&m_Transform);
	//フレームのポジション微調整
	m_Frame.Transform()->LocalPosition = D3DXVECTOR3(40.0f, 30.0f, 0.0f);

	FOR(2)
	{
		m_Arraw[i].Start();
		string num;
		Support::IntToString(&num, (i+1));
		m_Arraw[i].name("Arraw" + num);
		m_Arraw[i].LoadTex("Arraw.png");
		m_Arraw[i].Transform()->SetParent(&m_Transform);
	}
	m_Arraw[0].Transform()->LocalPosition.x = -100.0f;
	m_Arraw[1].Transform()->LocalPosition.x = 100.0f;

	m_Arraw[0].Transform()->LocalRotation.z = -90.0f;
	m_Arraw[1].Transform()->LocalRotation.z = 90.0f;

	//レーダーチャートのために更新
	m_Transform.UpdateTransform();

	//レーダーチャート
	//m_pChart = (CCobwebChart*)SINSTANCE(CObjectManager)->Add(new CCobwebChart(m_Name + "Chart"));
	m_Chart.Start();
	m_Chart.name(m_Name + "Chart");
	m_Chart.Transform()->SetParent(&m_Transform);
	m_Chart.Transform()->LocalPosition = D3DXVECTOR3(50.0f, 90.0f, 0.0f);
	m_Chart.Transform()->UpdateTransform();
	m_Chart.CreateChartBase(5, 80, 5);

	//名前テキスト
	m_NameText.Start();
	m_NameText.Createfont(L"NotSelect");
	m_NameText.SetColor(255, 255, 255);
	m_NameText.Transform()->SetParent(&m_Transform);
	m_NameText.Transform()->LocalPosition = D3DXVECTOR3(0.0f, 200.0f, 0.0f);


	m_camera = new CCamera();
	//m_pShow = (CShowCharacter*)SINSTANCE(CObjectManager)->Add(new CShowCharacter(m_Name + "ShowChara"));
	m_Show.SetCamera(&m_camera);
	m_Show.name(m_Name + "ShowChara");
	m_Show.Start();
	
	m_camera->Start();
	m_camera->Dist(D3DXVECTOR3(0.0f, 0.0f, -30.0f));
	m_camera->TargetPos(D3DXVECTOR3(0.0f, 8.5f, 0.0f));

	m_RenderT.CreateRenderTarget(m_Sprite.GetpTex(), 256, 350, D3DCOLOR_RGBA(255, 255, 255, 255));

	//不透明な白をキルカラーに設定
	m_Sprite.SetKillColor(D3DCOLOR_RGBA(255, 255, 255, 255));
}

void CCharacterSelect::Update()
{
	m_camera->Update();
	//m_camera.Move();

	m_Transform.UpdateTransform();
	m_Chart.Update();
	m_NameText.Update();
	m_Frame.Update();
	FOR(2)
		m_Arraw[i].Update();

	//キャラクター変更したか見るフラグ
	bool chenge = false;

	m_input.UpdateKeyboardState();

	if (m_input.isPressed(VK_RIGHT))
	{
		//最大数を超えないように
		m_ListIdx = (m_ListIdx + 1) % (short)m_CharacterList.size();

		chenge = true;

		m_Arraw[1].Transform()->LocalScale = D3DXVECTOR3(1.2f, 1.2f, 1.0f);
	}
	else if (m_input.isPressed(VK_LEFT))
	{
		//マイナスにならないように
		if ((m_ListIdx - 1) < 0)
		{
			m_ListIdx = (short)m_CharacterList.size() - 1;
		}
		else
		{
			m_ListIdx--;
		}

		chenge = true;

		m_Arraw[0].Transform()->LocalScale = D3DXVECTOR3(1.2f, 1.2f, 1.0f);
	}
	else
	{
		m_Arraw[0].Transform()->LocalScale = VECTOR3_ONE;
		m_Arraw[1].Transform()->LocalScale = VECTOR3_ONE;
	}


	//添え字が変更されていたなら
	if (chenge)
	{
		m_SelectChara = m_CharacterList[m_ListIdx];
		STATE s = m_SelectChara->GetState();
		
		short prot[5] = { s.hp, s.power, s.defense, s.skill, s.speed };
		m_Chart.NextProt(prot);

		//キャラクター情報セット
		m_Show.SetChara(m_SelectChara);
		//キャラクターの名前セット
		m_NameText.Createfont(m_SelectChara->GetCharaName());
	}

	m_Show.Update();

	m_Chart.UpdateProt(8.0f);
	m_Chart.CreateChartProt();

	m_Chart.LateUpdate();
}

void CCharacterSelect::Render()
{
	//レンダーターゲット
	{
		m_RenderT.SetRenderTarget(0);

		(*graphicsDevice()).Clear(
			0,
			NULL,
			D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
			D3DCOLOR_XRGB(255, 255, 255),
			1.0f,
			0);

		m_Show.Render();

		m_RenderT.BeforeRenderTarget();
	}

	m_Frame.Render();

	m_Sprite.Render(m_Transform);

	m_NameText.Render();

	m_Chart.Render();

	FOR(2)
		m_Arraw[i].Render();
}