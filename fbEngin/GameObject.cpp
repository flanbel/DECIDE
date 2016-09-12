#include "GameObject.h"

CGameObject::CGameObject(string name)
{
	//������o�^
	m_Transform.GameObject(this);
	m_Active = true;
	m_Name = name;
	m_Delete = false;
	m_Dimension = DIMENSION::DNON;
}

void CGameObject::Active(bool act)
{
	m_Active = act;
	//�q������
	if (m_Transform.ChildCnt() > 0)
	{
		//����������o��
		map<string, CTransform*> child = m_Transform.Children();
		//�C�e���[�^�擾
		map<string, CTransform*>::iterator it = child.begin();
		//�I���܂Ń��[�v
		while (it != child.end())
		{
			//�q�𓯂���Ԃɂ���
			it->second->GameObject()->m_Active = act;
			it++;
		}
	}
}