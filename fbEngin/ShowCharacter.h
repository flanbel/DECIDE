
#ifndef _SHOWCHARACTER_H
#define _SHOWCHARACTER_H

#include "3DObject.h"
#include "Character.h"

//�L�����N�^�[��\������N���X
class CShowCharacter :public C3DObject
{
public:
	CShowCharacter(string name = "");
	//���������s���֐�(��x�̂݌Ă΂��)
	void Start();

	//�X�V���s���֐�
	void Update();

	//�`����s���֐�
	void Render();

	//�L�����N�^�[�Z�b�g
	void SetChara(CCharacter* pC)
	{
		m_pChara = pC;
		if (m_pChara != nullptr)
		{
			//���f���f�[�^�Z�b�g
			m_model.SetModelData(m_pChara->GetModelData());
			
			y = 0;
		}
	}
private:
	//�L�����N�^�[�ւ̎Q��
	CCharacter* m_pChara;
	//
	float y;
};

#endif //_SHOWCHARACTER_H