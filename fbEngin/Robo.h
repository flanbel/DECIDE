
#ifndef _ROBO_H_
#define _ROBO_H_

#include "Character.h"

class CRobo :public CCharacter
{
public:
	CRobo();

	//���������s���֐�(��x�̂݌Ă΂��)
	void Start();

	//�X�V���s���֐�
	void Update();

	//�`����s���֐�
	void Render();
private:
};
#endif //_ROBO_H_