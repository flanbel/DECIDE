#include "TitleScene.h"
#include "ObjectManager.h"
#include "SceneManager.h"

#include "Collision.h"

CTitleScene::CTitleScene()
{

}

CTitleScene::~CTitleScene()
{

}

HRESULT CTitleScene::Start()
{
	//�w�i
	CImage* Back = (CImage*)SINSTANCE(CObjectManager)->Add(new CImage("TitleBack"));
	Back->Transform()->LocalPosition = D3DXVECTOR3(1040, 520, 0);
	Back->LoadTex("TitleBack.png");
	Back->Transform()->LocalScale = D3DXVECTOR3(1.7f, 1.5f, 1.0f);
	
	//�^�C�g�����S
	CImage* Logo = (CImage*)SINSTANCE(CObjectManager)->Add(new CImage("TitleLogo"));
	Logo->Transform()->LocalPosition = D3DXVECTOR3(700, 410, 0);
	Logo->LoadTex("TitleLogo2.png");
	Logo->Transform()->LocalScale = D3DXVECTOR3(1.0f, 1.4f, 1.0f);

	//�I���J�[�\��
	CSelectCursor* cursor = (CSelectCursor*)SINSTANCE(CObjectManager)->Add(new CSelectCursor("Cursor"));
	
	//�X�^�[�g�A�C�R��
	m_Start = (CSelectIcon*)SINSTANCE(CObjectManager)->Add(new CSelectIcon("Start"));
	m_Start->Transform()->LocalPosition = D3DXVECTOR3(640, 490, 0);
	m_Start->SetText(L"Start");
	m_Start->SetTextSize(70);
	m_Start->SetTextColor(ICONSTATE::SELECT , 255, 165, 0);
	//�I���A�C�R��
	m_Exit = (CSelectIcon*)SINSTANCE(CObjectManager)->Add(new CSelectIcon("Exit"));
	m_Exit->Transform()->LocalPosition = D3DXVECTOR3(640, 630, 0);
	m_Exit->SetText(L"Exit");
	m_Exit->SetTextSize(70);
	m_Exit->SetTextColor(ICONSTATE::SELECT, 0, 165, 100);

	cursor->AddList(m_Start);
	cursor->AddList(m_Exit);

	m_timer = 0.0;
	m_ChengS = false;

	return S_OK;
}

HRESULT CTitleScene::Update()
{
	if (GetAsyncKeyState(VK_RETURN))
	{
		if (m_Start->Select())
		{
			m_ChengS = true;
		}
		//�Q�[���I��
		else if (m_Exit->Select())
		{
			PostQuitMessage(0);
		}
	}

	if (m_ChengS)
	{
		//�t�F�[�h�A�E�g
		m_Start->Fade(false, 20);
		//m_Start->Flashing(0.1);
		//�^�C�}�[����
		m_timer += SINSTANCE(CTimer)->DeltaTime();
		FadeOut();
		//��莞�Ԍo��
		if (m_timer > 0.6f)
		{
			if (m_endFade)
			{
				SINSTANCE(CSceneManager)->ChangeScene(SCENE::CHARASELECT);
				return S_OK;
			}
		}
	}

	return S_OK;
}

HRESULT CTitleScene::Draw()
{
	SINSTANCE(CObjectManager)->RenderObject();

	return S_OK;
}