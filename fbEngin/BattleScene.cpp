#include "BattleScene.h"
#include "ObjectManager.h"
#include "SceneManager.h"

#include "TestChara.h"
#include "TestStage.h"
#include "TestItem.h"

HRESULT CBattleScene::Start()
{
	m_pCamera = new CCamera*();
	m_pMainCamera = new CCamera();
	m_pShadowCamera = new CCamera();

	//�J�����̋����ݒ�
	m_pMainCamera->Dist(D3DXVECTOR3(0.0f, 100.0f, -150.0f));
	m_pShadowCamera->Dist(D3DXVECTOR3(0.0f, 150.0f, -150.0f));

	*m_pCamera = m_pMainCamera;

	//�J�����o�^
	SINSTANCE(CObjectManager)->SetCamera(m_pCamera);

	//�X�e�[�W�ǂݍ���
	CTestStage* TestStage = (CTestStage*)SINSTANCE(CObjectManager)->Add(new CTestStage("TestStage"));
	
	FOR(4)
	{
		//�v���C���[�ǂݍ���(�O�̃V�[���œo�^�ς�)
		m_Player = (CPlayer*)SINSTANCE(CObjectManager)->FindObject("Player1", DIMENSION::D3);
		//����Ȃ�
		if (m_Player != nullptr)
		{
			m_Player->SetCamera(m_pCamera);
			//���̃V�[�����I���������������悤�ɐݒ�
			m_Player->Leave(false);
		}
	}
	
	//�A�C�e��
	m_ItemSwitch.push_back(new CTestItem);
	//�A�C�e���}�l�[�W���[������
	m_ItemManager.Start(m_pCamera, &m_ItemSwitch);

	m_RenderTarget[0].CreateRenderTarget(&m_tex[0], GAME_CLIENT_WIDTH, GAME_CLIENT_HEIGHT);
	m_RenderTarget[1].CreateRenderTarget(&m_tex[1], GAME_CLIENT_WIDTH, GAME_CLIENT_HEIGHT);

	m_ShadowBuffer.CreateRenderTarget(&m_Shadowtex, GAME_CLIENT_WIDTH, GAME_CLIENT_HEIGHT);

	m_depth.Initialize();

	m_i.Transform()->Position = D3DXVECTOR3(GAME_CLIENT_WIDTH / 2, GAME_CLIENT_HEIGHT / 2, 0.0f);

	return S_OK;
}

HRESULT CBattleScene::Update()
{
	//�v���C���[�̓�������悤�ɒ���
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
		SAFE_DELETE(m_pCamera);
		SAFE_DELETE(m_pMainCamera);
		SAFE_DELETE(m_pShadowCamera);
		return S_OK;
	}
	
	return S_OK;
}

HRESULT CBattleScene::Draw()
{
	//�e����
	{
		//���C�g�J�����ɐ؂�ւ�
		*m_pCamera = m_pShadowCamera;

		m_ShadowBuffer.SetRenderTarget(1);

		//�Ȃ񂩃N���A���Ȃ��Ɖf��Ȃ�����
		(*graphicsDevice()).Clear(0,
			NULL,
			D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
			D3DCOLOR_XRGB(255, 255, 255),
			1.0f,
			0);

		SINSTANCE(CObjectManager)->RenderObject();

		m_ItemManager.Render();
	};

	//�`��
	{
		//���C���J�����ɐ؂�ւ�
		*m_pCamera = m_pMainCamera;

		//[0]�͌��摜
		//[1]�͐[�x�摜
		m_RenderTarget[0].SetRenderTarget(0);
		m_RenderTarget[1].SetRenderTarget(1);

		//�Ȃ񂩃N���A���Ȃ��Ɖf��Ȃ�����
		(*graphicsDevice()).Clear(0,
			NULL,
			D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
			D3DCOLOR_XRGB(255, 255, 255),
			1.0f,
			0);

		SINSTANCE(CObjectManager)->RenderObject();

		m_ItemManager.Render();
	};

	CRenderTarget::BeforeRenderTarget();

	//m_depth.DepthofField(&m_tex[0], &m_tex[1]);

	m_i.SetTex(m_Shadowtex);
	m_i.Render();

	
	return S_OK;
}