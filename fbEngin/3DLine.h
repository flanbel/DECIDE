
#ifndef _3DLINE_H_
#define _3DLINE_H_

#include "GameObject.h"
#include "Effect.h"
#include "Camera.h"
//#include "Collision.h"

#define D3DFVF_LINEVERTEX (D3DFVF_XYZ|D3DFVF_DIFFUSE)

struct LINEVERTEX
{
	float x, y, z;
	D3DCOLOR color;
};

//�O������ԂɃ��C�����������
class C3DLine : public CGameObject
{
public:
	C3DLine();
	~C3DLine()
	{
		m_Vbuf->Release();
		m_Vbuf = NULL;
	}
	void Start();
	void Update();
	void Render();

	//���C���̏��Z�b�g
	//�������FD3DXVECTOR3* �n�_[0]�ƏI�_[1]��pos�̓������z��
	void SetLine(D3DXVECTOR3 line[]);

	////�����蔻��̂ӂ�����������
	////�������FBoxCollision �{�b�N�X�̂����蔻��
	//void SetCollision(BoxCollision box);

	CCamera* m_pcamera;
private:
	//�X�^�e�B�b�N�Ȓ��_�o�b�t�@
	static LPDIRECT3DVERTEXBUFFER9 m_Vbuf;
	CEffect* m_pEffect;
	int m_Primnum;
};
#endif //_3DLINE_H_