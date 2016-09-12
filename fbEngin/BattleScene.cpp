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

	//�J�����o�^
	SINSTANCE(CObjectManager)->SetCamera(m_ppCamera);
	SINSTANCE(CObjectManager)->SetLightCamera(m_pShadowCamera);

	//�J�����̋����ݒ�
	m_pMainCamera->Dist(D3DXVECTOR3(0.0f, 40.0f, -300.0f));
	m_pShadowCamera->Dist(D3DXVECTOR3(80.0f, 1100.0f, -1600.0f));
	m_pMainCamera->Near(60);
	m_pMainCamera->Far(8000);

	m_pShadowCamera->Near(1100);
	m_pShadowCamera->Far(4000);

	*m_ppCamera = m_pMainCamera;

	//�X�e�[�W�ǂݍ���
	CTestStage* TestStage = (CTestStage*)SINSTANCE(CObjectManager)->Add(new CTestStage("TestStage"));
	//
	m_CreateStage.Create("abc");
	
	FOR(4)
	{
		//�v���C���[�ǂݍ���(�O�̃V�[���œo�^�ς�)
		string num; 
		Support::IntToString(&num,i + 1);
		m_Player[i] = (CPlayer*)SINSTANCE(CObjectManager)->FindObject("Player"+num, DIMENSION::D3);
		//����Ȃ�
		if (m_Player != nullptr)
		{
			m_Player[i]->SetCamera(m_ppCamera);
			m_Player[i]->SetLightCamera(m_pShadowCamera);
			//���̃V�[�����I���������������悤�ɐݒ�
			m_Player[i]->Active(true);
		}
	}
	
	//�A�C�e��
	m_ItemSwitch.push_back(new CTestItem);
	m_ItemSwitch.push_back(new CGreatSowrd);
	//�A�C�e���}�l�[�W���[������
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

	//�v���C���[�̓�������悤�ɒ���
	D3DXVECTOR3 pos = m_Player[0]->Transform()->LocalPosition;
	pos.y += 10;
	m_pMainCamera->TargetPos(pos);
	m_pShadowCamera->TargetPos(VECTOR3_ZERO);

	m_ItemManager.Update();

	if (m_ItemManager.ItemList()->size() > 0)
	m_Player[0]->SetItem(*m_ItemManager.ItemList());


	//�Z���N�g�V�[���ֈڍs
	if (GetAsyncKeyState(VK_P))
	{
		m_ItemSwitch.clear();
		//�A�C�e���폜
		m_ItemManager.clear();
		//�J���������
		SAFE_DELETE(m_pMainCamera);
		SAFE_DELETE(m_pShadowCamera);
		SAFE_DELETE(m_ppCamera);
		//�Z���N�g�V�[���ɐ؂�ւ�
		SINSTANCE(CSceneManager)->ChangeScene(SCENE::CHARASELECT);
		return S_OK;
	}

	return S_OK;
}

HRESULT CBattleScene::Draw()
{
	//�e����
	{
		//���C�g�J�����ɐ؂�ւ�
		*m_ppCamera = m_pShadowCamera;
		m_pShadowCamera->Update();

		m_ShadowBuffer.SetRenderTarget(1);

		//�I�u�W�F�N�g�`��
		SINSTANCE(CObjectManager)->RenderObject();
	};
	CRenderTarget::RemoveRenderTarget(1);

	//�e�̉摜�ݒ�
	SINSTANCE(CObjectManager)->SetLightDepth(m_Shadowtex);

	//�`��
	{
		//���C���J�����ɐ؂�ւ�
		*m_ppCamera = m_pMainCamera;
		m_pMainCamera->Update();

		//[0]�͌��摜
		//[1]�͐[�x�摜
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