
#include "GameCamera.h"

CGameCamera::CGameCamera(int num)
{
	m_PlayerNumber = num;
}

void CGameCamera::Move()
{
	D3DXMATRIX Rot;
	D3DXMatrixIdentity(&Rot);
	//Y������ɉ��
	{
		if (GetAsyncKeyState(VK_RIGHT))
		{
			D3DXMatrixRotationY(&Rot, D3DXToRadian(-1.0));
		}
		else if (GetAsyncKeyState(VK_LEFT))
		{
			D3DXMatrixRotationY(&Rot, D3DXToRadian(1.0));
		}

		D3DXMatrixRotationY(&Rot, D3DXToRadian((float)(-g_Controller[m_PlayerNumber - 1].GetGamepad().sThumbRX / 10000.0f)));

		//Y�������]������
		D3DXVec3TransformCoord(&m_Dist, &m_Dist, &Rot);
	}


	//X����]������
	{
		D3DXVECTOR3 vUP = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		D3DXVECTOR3 RotAxis;
		D3DXVec3Cross(&RotAxis, &m_Dist, &vUP);

		if (GetAsyncKeyState(VK_UP))
		{
			D3DXMatrixRotationAxis(&Rot, &RotAxis, D3DXToRadian(1.0));
		}
		else if (GetAsyncKeyState(VK_DOWN))
		{
			D3DXMatrixRotationAxis(&Rot, &RotAxis, D3DXToRadian(-1.0));
		}

		D3DXMatrixRotationAxis(&Rot, &RotAxis, D3DXToRadian((float)g_Controller[m_PlayerNumber - 1].GetGamepad().sThumbRY / 10000.0f));

		//�x�N�g�����s����g���Ċ|���Z
		D3DXVec3TransformCoord(&m_Dist, &m_Dist, &Rot);
	}

	//�E�V�����_�[�{�^����������Ă���
	if (g_Controller[m_PlayerNumber - 1].IsPressButton(XINPUT_GAMEPAD_RIGHT_SHOULDER))
	{
		m_ViewAngle = 60;
	}
	else
	{
		m_ViewAngle = 45;
	}

	//�|�W�V�����v�Z
	m_Pos = m_TargetPos + m_Dist;
}