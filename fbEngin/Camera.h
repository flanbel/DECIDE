
#ifndef _CAMERA_H_
#define _CAMERA_H_

class C3DObject;

class CCamera
{
public:
	CCamera();
	void Start();
	void Update();

	void ViewMatrixUpdate();
	void ProjectionMatrixUpdate();

	D3DXMATRIX View(){ return m_View; }
	D3DXMATRIX Projection(){ return m_Projection; }
	D3DXMATRIX Rotation(){ return m_Rotation; }

	//カメラ移動関数(仮)
	void Move();

	//視点取得
	D3DXVECTOR3 Pos()
	{
		return m_Pos;
	}

	//注視点設定
	void TargetPos(D3DXVECTOR3 tp)
	{
		m_TargetPos = tp;
	}

	//注視点取得
	D3DXVECTOR3 TargetPos()
	{
		return m_TargetPos;
	}

	//距離設定
	void Dist(D3DXVECTOR3 d)
	{
		m_Dist = d;
	}

	//距離取得
	D3DXVECTOR3 Dist()
	{
		return m_Dist;
	}

	//ターゲット(オブジェクト)設定
	void Target(C3DObject* pT)
	{
		m_pTarget = pT;
	}

	//画角設定
	void ViewAngle(float theta)
	{
		m_ViewAngle = theta;
	}
	//近平面設定
	void Near(float n)
	{
		m_Near = n;
	}
	//遠平面設定
	void Far(float f)
	{
		m_Far = f;
	}
	//アスペクト比率設定
	void Aspect(float aspect)
	{
		m_Aspect = aspect;
	}

	void m();
private:
	//カメラのポジション
	D3DXVECTOR3 m_Pos;
	//カメラの注視点
	D3DXVECTOR3 m_TargetPos;
	//ターゲットとカメラの距離
	D3DXVECTOR3 m_Dist;
	
	//ターゲット(オブジェクト)
	C3DObject* m_pTarget;

	//ビュー行列
	D3DXMATRIX m_View;
	//プロジェクション行列
	D3DXMATRIX m_Projection;
	//回転
	D3DXMATRIX m_Rotation;

	float m_ViewAngle;	//画角
	float m_Near;		//近平面
	float m_Far;		//遠平面
	float m_Aspect;		//アスペクト比

	//カメラの回転角度
	D3DXVECTOR3 m_angle;
};
#endif //_CAMERA_H_