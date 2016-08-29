
#ifndef _ITEMMANAGER_H_
#define _ITEMMANAGER_H_

#include "Item.h"

//�A�C�e���𐶐��A�Ǘ�
class CItemManager
{
public:
	CItemManager();

	//���������s���֐�(��x�̂݌Ă΂��)
	//�������Fshort �A�C�e�������m��?
	void Start(CCamera** ppcamera, const vector<CItem*>* pitemswitch, short probability = 100);

	//�X�V���s���֐�
	void Update();

	//�`����s���֐�
	void Render();

	//�A�C�e���S�폜
	void clear()
	{
		list<CItem*>::iterator it = m_ItemList.begin();
		while (it != m_ItemList.end())
		{
			//���������
			SAFE_DELETE((*it));
			it = m_ItemList.erase(it);
		}
	}

	//�A�C�e�����X�g�̎Q�Ƃ�Ԃ�
	list<CItem*>* ItemList()
	{
		return &m_ItemList;
	}
private:
	//�J�����Q��
	CCamera** m_ppCamera;
	//�t�B�[���h��̃A�C�e�����i�[
	list<CItem*> m_ItemList;
	//�A�C�e�������m��
	short m_probability;
	//�����͈�
	D3DXVECTOR3 m_range;

	//�A�C�e���X�C�b�`�ւ̎Q��
	vector<CItem*>* m_ItemSwitch;
	//�A�C�e���̎��
	short m_maxnum;
};

#endif //_ITEMMANAGER_H_