#include "Item.h"

bool CItem::ItemUpdata()
{
	//持たれていない
	if (!m_isHas)
	{
		//寿命から引く
		m_life -= SINSTANCE(CTimer)->DeltaTime();
	}

	//死んでいるかどうか
	return (m_life <= 0);
}