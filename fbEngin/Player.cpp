#include "Player.h"

CPlayer::CPlayer(string name) : C3DObject(name)
{
	m_pChara = nullptr;
	m_pHasItem = nullptr;
}

CPlayer::~CPlayer()
{
	//�L�����N�^�[�����
	SAFE_DELETE(m_pChara);
}

void CPlayer::Start()
{
	//�L�����N�^�[������
	m_pChara->Start();
	//������
	m_show.Start();
	m_show.SetCamera(m_pCamera);
	//���f���f�[�^�Z�b�g
	m_model.SetModelData(m_pChara->GetModelData());
	//�L�����N�^�[�̃X�e�[�^�X���
	m_State = m_pChara->GetState();

	//m_model.RenderType(TYPE::SPECULAR,true);

	m_Transform.LocalRotation = D3DXVECTOR3(-90.0, 0.0, 0.0);
	m_dir = VECTOR3_ZERO;
}

void CPlayer::Update()
{
	//�L�[�{�[�h�X�V
	m_input.UpdateKeyboardState();

	//�e�A�N�V�������s
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
	
	//�A�C�e�����̂Ă�
	ThrowAwayItem();

	//�L�����N�^�[�X�V
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
		//���f���̃R���W�����\��
		m_show.ShowFrameCollision(m_pChara->GetModelData()->GetFrameRoot(), m_Transform.WorldMatrix());
		if (m_pHasItem != nullptr)
			m_show.ShowFrameCollision(m_pHasItem->GetModelData().GetFrameRoot(), m_pChara->GetHand()->CombinedTransformationMatrix);
	}
}

void CPlayer::Move()
{
	//���������߂Đ��K��
	D3DXVECTOR3 ver = { 0.0f, 0.0f,1.0f };
	float theta = D3DXToRadian(-m_Transform.LocalRotation.y);
	//��]
	m_dir.x = ver.x * cos(theta) - ver.z * sin(theta);
	m_dir.z = ver.x * sin(theta) + ver.z * cos(theta);

	float delta = (float)SINSTANCE(CTimer)->DeltaTime();
	//�X�s�[�h�{��
	float speedratio = 1.0f + ((m_State.speed - 3) * 0.1);

	//�ȈՈړ�
	//�O
	if (m_input.isKeyDown(VK_W))
	{
		m_Transform.LocalPosition += m_dir * speedratio;// * 60.0f * delta;
	}
	//���
	if (m_input.isKeyDown(VK_S))
	{
		m_Transform.LocalPosition -= m_dir * speedratio;// *60.0f * delta;
	}
}

void CPlayer::Turn()
{
	float delta = (float)SINSTANCE(CTimer)->DeltaTime();

	//�E
	if (m_input.isKeyDown(VK_D))
	{
		m_Transform.LocalRotation.y += 120.0f * delta;
	}
	//��
	if (m_input.isKeyDown(VK_A))
	{
		m_Transform.LocalRotation.y -= 120.0f * delta;
	}
}

void CPlayer::SetItem(const list<CItem*>& itemlist)
{
	//�A�C�e���������Ă��Ȃ� ����
	//�肪����@����
	//X�L�[�������ꂽ�Ȃ�
	if (m_pHasItem == nullptr &&
		m_pChara->GetHand() != nullptr &&
		m_input.isPressed(VK_X))
	{
		m_pHasItem = NearItem(itemlist);
		//�t���OON
		m_pHasItem->Has();
		//��̍s���e�ɐݒ�(�A�j���[�V�����A��)
		m_pHasItem->SetParent(&m_pChara->GetHand()->CombinedTransformationMatrix);
	}
}

void CPlayer::ThrowAwayItem()
{
	//�A�C�e���������Ă���Ȃ� Z�L�[�Ŏ̂Ă�
	if (m_pHasItem != nullptr &&
		m_input.isPressed(VK_Z))
	{
		//���̏ꏊ�ɃA�C�e�����̂Ă�
		m_pHasItem->Throw(m_Transform);
		//�A�C�e����nullptr��
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
		//����
		float len = sqrt(pow(vec.x, 2) + pow(vec.y, 2) + pow(vec.z, 2));
		if (len < min)
		{
			//�l�X�V
			min = len;
			Near = item;
		}
	}

	return Near;
}