
#ifndef _SHOWCOLLISION_H_
#define _SHOWCOLLISION_H_

#include "3DObject.h"
#include "Collision.h"
#include "SkinModelData.h"

class CShowCollision:public C3DObject
{
public:
	CShowCollision(string name = "");
	//���������s���֐�(��x�̂݌Ă΂��)
	void Start();

	//�X�V���s���֐�
	void Update();

	//�`����s���֐�
	void Render();
	//�t���[���̂����蔻��\��(��)
	//������:const LPD3DXFRAME �t���[��
	void ShowFrameCollision(const LPD3DXFRAME pFrameBase,const D3DXMATRIX& world);

	//�R���W�����ݒ�
	//void SetCollision(BoxCollision box);
private:
	CSkinModelData m_data;
};

#endif //_SHOWCOLLISION_H_