
#ifndef _TVMAN_H_
#define _TVMAN_H_

#include "Character.h"

//�e���r�}��
class CTVman :public CCharacter
{
public:
	CTVman();

	//���������s���֐�(��x�̂݌Ă΂��)
	void Start();

	//�X�V���s���֐�
	void Update();

	//�`����s���֐�
	void Render();
private:
};
#endif //_TVMAN_H_