#include "CharaSelectScene.h"
#include "ObjectManager.h"
#include "SceneManager.h"

#include "Player.h"
//�L�����N�^�[
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
	//�w�i
	CImage* SelectBack = (CImage*)SINSTANCE(CObjectManager)->Add(new CImage("SelectBack"));
	SelectBack->LoadTex("SelectBack.png");
	SelectBack->Transform()->LocalPosition = D3DXVECTOR3(1040, 520, 0);
	SelectBack->Transform()->LocalScale = D3DXVECTOR3(1.7f, 1.5f, 1.0f);
	
	//�߂�{�^��
	m_BackB = (CImage*)SINSTANCE(CObjectManager)->Add(new CImage("BackB"));
	m_BackB->Transform()->LocalPosition = D3DXVECTOR3(100, 110, 0);
	m_BackB->LoadTex("BackB.png");	

	//�L�����N�^�[���ǂݍ���(������̓I�u�W�F�N�g�}�l�[�W���[�ɓo�^���Ă��Ȃ��̂Ńf���[�g���邱��)
	CTestChara* TestChara = new CTestChara();
	TestChara->Start();
	//TVman 
	CTVman* TVman = new CTVman();
	TVman->Start();
	//Robo
	CRobo* Robo = new CRobo();
	Robo->Start();

	//�L�����N�^�[���X�g�ɓo�^
	m_CharacterList.push_back(TestChara);
	m_CharacterList.push_back(TVman);
	m_CharacterList.push_back(Robo);

	//�L�����N�^�[�I�𐶐�
	FOR(MAX_PLAYER_NUM)
	{
		string n; 
		Support::IntToString(&n, i+1);
		m_Select[i] = (CCharacterSelect*)SINSTANCE(CObjectManager)->Add(new CCharacterSelect(i+1,"Select" + n));
		m_Select[i]->Transform()->LocalPosition = D3DXVECTOR3(170.0f + (i * 315.0f), 440.0f, 0.0f);
		m_Select[i]->SetCharaList(m_CharacterList);
	}

	//�^�C�}�[������
	m_timer = 0.0;

	return S_OK;
}

HRESULT CCharaSelectScene::Update()
{

	m_input.UpdateKeyboardState();

	//�I������Ă���v���C���[�̐�(���l���肳��Ă��邩�H)
	//�v���C���[��������
	short SelectPlayerNum = 0;
	FOR(MAX_PLAYER_NUM)
	{
		//�L�����N�^�[���I������Ă���
		if (m_Select[i]->GetSelectChara() != nullptr)
		{
			SelectPlayerNum++;
		}
	}

	//�^�C�g���Ƀo�b�N
	if (m_input.isKeyDown(VK_B) ||
		g_Controller[0].IsPressButton(XINPUT_GAMEPAD_A))
	{
		m_timer += SINSTANCE(CTimer)->DeltaTime();
		m_BackB->SetAlpha(0.5f);
		//���ȏ㉟����Ă�����
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

	//�퓬�V�[���ɑJ��
	if (SelectPlayerNum > 0 &&
		m_input.isPressed(VK_SPACE)||
		g_Controller[0].isPushButton(XINPUT_GAMEPAD_START))
	{
		//�v���C���[
		SetPlayer();
		SINSTANCE(CSceneManager)->ChangeScene(SCENE::BATTLE);
		//�L�����N�^�[�����f���[�g
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

		//�L�����N�^�[���I������Ă���
		if (chara != nullptr)
		{
			//�v���C���[�o�^
			//�V�[�����܂����ł��c��悤�ɐݒ�
			CPlayer* Player = (CPlayer*)SINSTANCE(CObjectManager)->Add(new CPlayer(i+1,"Player" + num), false);

			//typeid���g���N���X�Ŕ�r���Ă���
			//�����ƃX�}�[�g�ɂł���͂��E�E�E
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