
#ifndef _TESTITEM_H_
#define _TESTITEM_H_

#include "Item.h"

//�Ă���
class CTestItem : public CItem
{
public:
	CTestItem(string name = "") :CItem(name){};

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

#endif //_TESTITEM_H_