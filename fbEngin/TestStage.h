
#ifndef _TESTSTAGE_H_
#define _TESTSTAGE_H_

#include "Stage.h"

//�Ă���
class CTestStage: public CStage
{
public:
	CTestStage(string name = "") :CStage(name){};

	//���������s���֐�(��x�̂݌Ă΂��)
	void Start();

	//�X�V���s���֐�
	void Update();

	//�`����s���֐�
	void Render();
private:
};

#endif //_TESTSTAGE_H_