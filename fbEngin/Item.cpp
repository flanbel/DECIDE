#include "Item.h"

bool CItem::ItemUpdata()
{
	//������Ă��Ȃ�
	if (!m_isHas)
	{
		//�����������
		m_life -= SINSTANCE(CTimer)->DeltaTime();
	}

	//����ł��邩�ǂ���
	return (m_life <= 0);
}