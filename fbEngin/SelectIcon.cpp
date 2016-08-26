#include "SelectIcon.h"

CSelectIcon::CSelectIcon(string name) :C2DObject(name)
{
	m_Sprite.LoadTexture("Select.png");
	m_Text.Createfont(L"Select");
	m_Text.Transform()->SetParent(&m_Transform);

	FOR(ICONSTATE::ICONSTATE_NUM)
	{
		m_Color[i] = D3DXVECTOR3(255, 255, 255);
	}

	m_IsSelect = false;
	m_Flash = false; 
	m_FlashInterval = 0.0;
}

void CSelectIcon::Start()
{
	
}

void CSelectIcon::Update()
{
	m_Transform.UpdateTransform();
	m_Text.Update();
}

void CSelectIcon::Render()
{

	if (!m_IsSelect)
	{
		m_Sprite.SetBlendColor((int)m_Color[ICONSTATE::NSELECT].x, (int)m_Color[ICONSTATE::NSELECT].y, (int)m_Color[ICONSTATE::NSELECT].z);
		m_Text.SetColor((int)m_Color[ICONSTATE::NSELECT].x, (int)m_Color[ICONSTATE::NSELECT].y, (int)m_Color[ICONSTATE::NSELECT].z);
	}
	else
	{
		m_Sprite.SetBlendColor((int)m_Color[ICONSTATE::SELECT].x, (int)m_Color[ICONSTATE::SELECT].y, (int)m_Color[ICONSTATE::SELECT].z);
		m_Text.SetColor((int)m_Color[ICONSTATE::SELECT].x, (int)m_Color[ICONSTATE::SELECT].y, (int)m_Color[ICONSTATE::SELECT].z);
	}

	m_Sprite.Render(m_Transform);
	m_Text.Render();
}