
#ifndef _TESTCHARA_H_
#define _TESTCHARA_H_

#include "Character.h"

class CTestChara :public CCharacter
{
public:
	CTestChara();

	//���������s���֐�(��x�̂݌Ă΂��)
	void Start();

	//�X�V���s���֐�
	void Update();

	//�`����s���֐�
	void Render();
private:
};
#endif //_TESTCHARA_H_