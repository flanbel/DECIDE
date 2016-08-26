#include "Text.h"

CText::CText(string name) :C2DObject(name)
{
	m_font.SetSprite(&m_Sprite);
};

void CText::Start()
{
	
}

void CText::Update()
{
	m_Transform.UpdateTransform();
}

void CText::Render()
{
	m_font.Render(m_Transform);
}