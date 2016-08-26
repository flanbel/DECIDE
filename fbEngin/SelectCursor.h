
#ifndef _SELECTCURSOR_H_
#define _SELECTCURSOR_H_

#include "2DObject.h"
#include "Sprite.h"
#include "Input.h"

class CSelectIcon;

//SelectIcon�p�̃J�[�\��
class CSelectCursor:public C2DObject
{
public:
	CSelectCursor(string name = "");
	//���������s���֐�(��x�̂݌Ă΂��)
	void Start()override;

	//�X�V���s���֐�
	void Update()override;

	//�`����s���֐�
	void Render()override;
	
	//���X�g�ǉ�
	void AddList(CSelectIcon* icon)
	{
		m_SelectList.push_back(icon);
	}
	//���X�g��̃A�C�R���̏ꏊ�Ɉړ�
	void MoveList();
private:
	//���X�g
	list<CSelectIcon*> m_SelectList;
	//�Q��
	list<CSelectIcon*>::iterator it;
	//����
	CInputManager m_input;
	//���ݑI������Ă���A�C�R��
	CSelectIcon* m_NowSelect;
};

#endif //_SELECTCURSOR_H_