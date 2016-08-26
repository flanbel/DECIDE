#include "Image.h"

void CImage::Start()
{
	
}

void CImage::Update()
{
	m_Transform.UpdateTransform();
}

void CImage::Render()
{
	m_Sprite.Render(m_Transform);
}