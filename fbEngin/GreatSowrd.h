
#ifndef _GREATSOWRD_H_
#define _GREATSOWRD_H_

#include "Item.h"

//�O���[�g�\�[�h
class CGreatSowrd : public CItem
{
public:
	CGreatSowrd(string name = "GreatSowrd") :CItem(name){};

	//���������s���֐�(��x�̂݌Ă΂��)
	void Start();

	//�X�V���s���֐�
	void Update();

	//�X�V�̌�ɌĂяo�����֐�
	void LateUpdate()override;

	//�`����s���֐�
	void Render();
private:
};

#endif //_GREATSOWRD_H_