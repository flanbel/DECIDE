#include "Camera.h"
#include "EffectManager.h"
#include "3DObject.h"

CCamera::CCamera()
{
	//始点初期化
	m_Pos = VECTOR3_ZERO;
	//注視点初期化
	m_TargetPos = VECTOR3_ZERO;
	//距離初期化
	m_Dist = VECTOR3_ZERO;
	//ターゲット初期化
	m_pTarget = nullptr;

	//行列初期化
	D3DXMatrixIdentity(&m_View);
	D3DXMatrixIdentity(&m_Projection);
	D3DXMatrixIdentity(&m_Rotation);

	m_ViewAngle = 45;
	m_Aspect = (16.0f / 9.0f);
	m_Near = 60.0f;
	m_Far = 600.0f;
	//正面を0とする
	m_angle = VECTOR3_ZERO;;
}

void CCamera::Start()
{
	
}

void CCamera::Update()
{
	//ターゲットが居るなら
	if (m_pTarget != nullptr)
		m_TargetPos = m_pTarget->Transform()->Position;

	//ポジション計算
	m_Pos = m_TargetPos + m_Dist;

	ViewMatrixUpdate();
	ProjectionMatrixUpdate();
}

void CCamera::ViewMatrixUpdate()
{
	//現在のポジションとターゲットのポジションからカメラの回転を計算する
	//軸が重ならないようにする
	//視線
	D3DXVECTOR3 Dir;
	Dir = m_TargetPos - m_Pos;
	D3DXVec3Normalize(&Dir, &Dir);						//正規化
	static const D3DXVECTOR3 AxisY(0.0f, 1.0f, 0.0f);
	float t = fabsf(D3DXVec3Dot(&Dir, &AxisY));
	D3DXVECTOR3 m_UpVec;
	if (fabsf((t - 1.0f)) < 0.00001f) {
		//方向がY軸と並行。
		m_UpVec.x = 1.0f;
		m_UpVec.y = 0.0f;
		m_UpVec.z = 0.0f;
	}
	else 
	{
		m_UpVec = AxisY;
	}

	//射影変換
	D3DXMatrixLookAtLH(&m_View, &m_Pos, &m_TargetPos, &m_UpVec);

	D3DXMATRIX world;
	D3DXMatrixIdentity(&world);
	//逆行列取得
	D3DXMatrixInverse(&world, NULL, &m_View);
	
	//平行移動行列の部分のみ削除
	world._41 = 0.0f;
	world._42 = 0.0f;
	world._43 = 0.0f;
	world._44 = 1.0f;
	//回転行列セット
	m_Rotation = world;
}

void CCamera::ProjectionMatrixUpdate()
{
	// プロジェクション変換(射影変換)
	D3DXMatrixPerspectiveFovLH(
		&m_Projection,
		D3DXToRadian(m_ViewAngle),	//画角
		m_Aspect,		//アスペクト比
		m_Near,			//クリップ距離(Near)
		m_Far);			//クリップ距離(far)
}

//移動(仮)
void CCamera::Move()
{
	//SHIFTキーが押されていたら上下移動
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
	//Y軸回転
	D3DXVECTOR3 vecY = m_Dist;
	float theta = D3DXToRadian(m_angle.y);
	vecY.x = m_Dist.x * cos(theta) - m_Dist.z * sin(theta);
	vecY.z = m_Dist.x * sin(theta) + m_Dist.z * cos(theta);

	m_Pos = m_TargetPos + vecY;

	//Zキーが押されている
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