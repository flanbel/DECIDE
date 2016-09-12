
#include "GameCamera.h"

CGameCamera::CGameCamera(int num)
{
	m_PlayerNumber = num;
}

void CGameCamera::Move()
{
	D3DXMATRIX Rot;
	D3DXMatrixIdentity(&Rot);
	//Y軸周りに回る
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

		//Y軸周り回転をして
		D3DXVec3TransformCoord(&m_Dist, &m_Dist, &Rot);
	}


	//X軸回転させる
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

		//ベクトルを行列を使って掛け算
		D3DXVec3TransformCoord(&m_Dist, &m_Dist, &Rot);
	}

	//右ショルダーボタンが押されている
	if (g_Controller[m_PlayerNumber - 1].IsPressButton(XINPUT_GAMEPAD_RIGHT_SHOULDER))
	{
		m_ViewAngle = 60;
	}
	else
	{
		m_ViewAngle = 45;
	}

	//ポジション計算
	m_Pos = m_TargetPos + m_Dist;
}