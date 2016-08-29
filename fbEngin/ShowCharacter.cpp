#include "ShowCharacter.h"

CShowCharacter::CShowCharacter(string name) :C3DObject(name)
{
	m_pChara = nullptr;
}

void CShowCharacter::Start()
{
	y = 0;
	m_Transform.LocalRotation = D3DXVECTOR3(-90.0, 180.0, 0.0);
}

void CShowCharacter::Update()
{
	//m_Transform.LocalRotation = D3DXVECTOR3(0.0f, y++, 0.0f);
	//キャラクター更新
	if (m_pChara != nullptr)
	m_pChara->Update();
	//トランスフォームを更新
	m_Transform.UpdateTransform();
	//m_model.UpdateFrameMatrix();
}

void CShowCharacter::Render()
{
	if (m_pChara != nullptr)
		m_model.Render(*m_ppCamera, m_pLight);
}