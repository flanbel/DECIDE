#include "Item.h"

bool CItem::ItemUpdata()
{
	//Ž‚½‚ê‚Ä‚¢‚È‚¢
	if (!m_isHas)
	{
		//Žõ–½‚©‚çˆø‚­
		m_life -= SINSTANCE(CTimer)->DeltaTime();
	}

	//Ž€‚ñ‚Å‚¢‚é‚©‚Ç‚¤‚©
	return (m_life <= 0);
}