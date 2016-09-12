
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

	//�J�����ړ��֐�(��)
	virtual void Move();

	//���_�擾
	D3DXVECTOR3 Pos()
	{
		return m_Pos;
	}

	//�����_�ݒ�
	void TargetPos(D3DXVECTOR3 tp)
	{
		m_TargetPos = tp;
	}

	//�����_�擾
	D3DXVECTOR3 TargetPos()
	{
		return m_TargetPos;
	}

	//�����ݒ�
	void Dist(D3DXVECTOR3 d)
	{
		m_Dist = d;
	}

	//�����擾
	D3DXVECTOR3 Dist()
	{
		return m_Dist;
	}

	//��p�ݒ�
	void ViewAngle(float theta)
	{
		m_ViewAngle = theta;
	}
	//�ߕ��ʐݒ�
	void Near(float n)
	{
		m_Near = n;
	}
	//�����ʐݒ�
	void Far(float f)
	{
		m_Far = f;
	}
	//�A�X�y�N�g�䗦�ݒ�
	void Aspect(float aspect)
	{
		m_Aspect = aspect;
	}

protected:
	//�J�����̃|�W�V����
	D3DXVECTOR3 m_Pos;
	//�J�����̒����_
	D3DXVECTOR3 m_TargetPos;
	//�^�[�Q�b�g�ƃJ�����̋���
	D3DXVECTOR3 m_Dist;

	//�r���[�s��
	D3DXMATRIX m_View;
	//�v���W�F�N�V�����s��
	D3DXMATRIX m_Projection;
	//��]
	D3DXMATRIX m_Rotation;

	float m_ViewAngle;	//��p
	float m_Near;		//�ߕ���
	float m_Far;		//������
	float m_Aspect;		//�A�X�y�N�g��
};
#endif //_CAMERA_H_