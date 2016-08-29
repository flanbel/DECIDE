#include "BattleScene.h"
#include "ObjectManager.h"
#include "SceneManager.h"

#include "TestChara.h"
#include "TestStage.h"
#include "TestItem.h"

HRESULT CBattleScene::Start()
{
	//�J�����o�^
	SINSTANCE(CObjectManager)->SetCamera(&m_maincamera);
	//�J�����̋����ݒ�
	m_maincamera.Dist(D3DXVECTOR3(0.0f, 100.0f, -150.0f));

	//�X�e�[�W�ǂݍ���
	CTestStage* TestStage = (CTestStage*)SINSTANCE(CObjectManager)->Add(new CTestStage("TestStage"));
	
	FOR(4)
	{
		//�v���C���[�ǂݍ���(�O�̃V�[���œo�^�ς�)
		m_Player = (CPlayer*)SINSTANCE(CObjectManager)->FindObject("Player1", DIMENSION::D3);
		//����Ȃ�
		if (m_Player != nullptr)
		{
			m_Player->SetCamera(&m_maincamera);
			//���̃V�[�����I���������������悤�ɐݒ�
			m_Player->Leave(false);
		}
	}
	
	//�A�C�e��
	m_ItemSwitch.push_back(new CTestItem);
	//�A�C�e���}�l�[�W���[������
	m_ItemManager.Start(&m_maincamera,&m_ItemSwitch);

	m_RenderTarget[0].CreateRenderTarget(&m_tex[0], GAME_CLIENT_WIDTH, GAME_CLIENT_HEIGHT);
	m_RenderTarget[1].CreateRenderTarget(&m_tex[1], GAME_CLIENT_WIDTH, GAME_CLIENT_HEIGHT);

	m_depth.Initialize();

	return S_OK;
}

HRESULT CBattleScene::Update()
{
	//�v���C���[�̓�������悤�ɒ���
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

	//[0]�͌��摜
	//[1]�͐[�x�摜

	CRenderTarget::BeforeRenderTarget();

	m_depth.DepthofField(&m_tex[0], &m_tex[1]);
	
	return S_OK;
}