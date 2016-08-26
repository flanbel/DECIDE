
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "3DObject.h"
#include "Character.h"
#include "Item.h"
#include "Input.h"

#include "Collision.h"
#include "ShowCollision.h"

class CPlayer :public C3DObject
{
public:
	CPlayer(string name = "");
	~CPlayer();

	//���������s���֐�(��x�̂݌Ă΂��)
	void Start();

	//�X�V���s���֐�
	void Update();

	//�`����s���֐�
	void Render();

	void LateUpdate()override;

	//�ړ�
	void Move();
	//��]
	void Turn();

	//�L�����N�^�[�ւ̎Q�ƃZ�b�g
	void SetCharacter(CCharacter* pC)
	{
		m_pChara = pC;
	}

	//�A�C�e������Ɏ�������
	void SetItem(const list<CItem*>& itemlist);
	//�A�C�e�����̂Ă�֐�
	void ThrowAwayItem();
	//�߂��ɂ���A�C�e����T��
	CItem* NearItem(const list<CItem*>& itemlist);
private:
	//�L�����N�^�[���ێ�
	CCharacter* m_pChara;
	//�����Ă���A�C�e��
	CItem* m_pHasItem;
	//����
	CInputManager m_input;
	//����
	D3DXVECTOR3 m_dir;

	//�����蔻��\��(�f�o�b�O�p)
	CShowCollision m_show;

	//�X�e�[�^�X
	STATE m_State;
};

#endif //_PLAYER_H_