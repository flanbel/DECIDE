#include "Item.h"

void CItem::ItemUpdata()
{
	//������Ă��Ȃ�
	if (!m_isHas)
	{
		//�����������
		m_life -= (float)SINSTANCE(CTimer)->DeltaTime();
	}

	//����ł��邩�ǂ���
	if (m_life <= 0)
	{
		Delete(true);
	}
}