#include "Item.h"

void CItem::ItemUpdata()
{
	//Ž‚½‚ê‚Ä‚¢‚È‚¢
	if (!m_isHas)
	{
		//Žõ–½‚©‚çˆø‚­
		m_life -= (float)SINSTANCE(CTimer)->DeltaTime();
	}

	//Ž€‚ñ‚Å‚¢‚é‚©‚Ç‚¤‚©
	if (m_life <= 0)
	{
		Delete(true);
	}
}