#include "Item.h"

void CItem::ItemUpdata()
{
	//持たれていない
	if (!m_isHas)
	{
		//寿命から引く
		m_life -= (float)SINSTANCE(CTimer)->DeltaTime();
	}

	//死んでいるかどうか
	if (m_life <= 0)
	{
		Delete(true);
	}
}