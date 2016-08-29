#include "Camera.h"
#include "EffectManager.h"
#include "3DObject.h"

CCamera::CCamera()
{
	//�n�_������
	m_Pos = VECTOR3_ZERO;
	//�����_������
	m_TargetPos = VECTOR3_ZERO;
	//����������
	m_Dist = VECTOR3_ZERO;
	//�^�[�Q�b�g������
	m_pTarget = nullptr;

	//�s�񏉊���
	D3DXMatrixIdentity(&m_View);
	D3DXMatrixIdentity(&m_Projection);
	D3DXMatrixIdentity(&m_Rotation);

	m_ViewAngle = 45;
	m_Aspect = (16.0f / 9.0f);
	m_Near = 60.0f;
	m_Far = 600.0f;
	//���ʂ�0�Ƃ���
	m_angle = VECTOR3_ZERO;;
}

void CCamera::Start()
{
	
}

void CCamera::Update()
{
	//�^�[�Q�b�g������Ȃ�
	if (m_pTarget != nullptr)
		m_TargetPos = m_pTarget->Transform()->Position;

	//�|�W�V�����v�Z
	m_Pos = m_TargetPos + m_Dist;

	ViewMatrixUpdate();
	ProjectionMatrixUpdate();
}

void CCamera::ViewMatrixUpdate()
{
	//���݂̃|�W�V�����ƃ^�[�Q�b�g�̃|�W�V��������J�����̉�]���v�Z����
	//�����d�Ȃ�Ȃ��悤�ɂ���
	//����
	D3DXVECTOR3 Dir;
	Dir = m_TargetPos - m_Pos;
	D3DXVec3Normalize(&Dir, &Dir);						//���K��
	static const D3DXVECTOR3 AxisY(0.0f, 1.0f, 0.0f);
	float t = fabsf(D3DXVec3Dot(&Dir, &AxisY));
	D3DXVECTOR3 m_UpVec;
	if (fabsf((t - 1.0f)) < 0.00001f) {
		//������Y���ƕ��s�B
		m_UpVec.x = 1.0f;
		m_UpVec.y = 0.0f;
		m_UpVec.z = 0.0f;
	}
	else 
	{
		m_UpVec = AxisY;
	}

	//�ˉe�ϊ�
	D3DXMatrixLookAtLH(&m_View, &m_Pos, &m_TargetPos, &m_UpVec);

	D3DXMATRIX world;
	D3DXMatrixIdentity(&world);
	//�t�s��擾
	D3DXMatrixInverse(&world, NULL, &m_View);
	
	//���s�ړ��s��̕����̂ݍ폜
	world._41 = 0.0f;
	world._42 = 0.0f;
	world._43 = 0.0f;
	world._44 = 1.0f;
	//��]�s��Z�b�g
	m_Rotation = world;
}

void CCamera::ProjectionMatrixUpdate()
{
	// �v���W�F�N�V�����ϊ�(�ˉe�ϊ�)
	D3DXMatrixPerspectiveFovLH(
		&m_Projection,
		D3DXToRadian(m_ViewAngle),	//��p
		m_Aspect,		//�A�X�y�N�g��
		m_Near,			//�N���b�v����(Near)
		m_Far);			//�N���b�v����(far)
}

//�ړ�(��)
void CCamera::Move()
{
	//SHIFT�L�[��������Ă�����㉺�ړ�
	if (GetAsyncKeyState(VK_SHIFT))
	{
		if (GetAsyncKeyState(VK_UP))
		{
			m_Dist.y++;
		}
		else if (GetAsyncKeyState(VK_DOWN))
		{
			m_Dist.y--;
		}
	}
	else
	{
		if (GetAsyncKeyState(VK_UP))
		{
			m_Dist.z++;
		}
		else if (GetAsyncKeyState(VK_DOWN))
		{
			m_Dist.z--;
		}
	}

	if (GetAsyncKeyState(VK_RIGHT))
	{
		m_angle.y++;
	}
	else if (GetAsyncKeyState(VK_LEFT))
	{
		m_angle.y--;
	}

	if (GetAsyncKeyState(VK_UP))
	{
		m_angle.x--;
	}
	else if (GetAsyncKeyState(VK_DOWN))
	{
		m_angle.x++;
	}
	//Y����]
	D3DXVECTOR3 vecY = m_Dist;
	float theta = D3DXToRadian(m_angle.y);
	vecY.x = m_Dist.x * cos(theta) - m_Dist.z * sin(theta);
	vecY.z = m_Dist.x * sin(theta) + m_Dist.z * cos(theta);

	m_Pos = m_TargetPos + vecY;

	//Z�L�[��������Ă���
	if (GetAsyncKeyState(VK_Z))
	{
		if (GetAsyncKeyState(VK_UP))
		{
			m_ViewAngle += 1;
		}
		else if (GetAsyncKeyState(VK_DOWN))
		{
			m_ViewAngle -= 1;
		}
	}
}