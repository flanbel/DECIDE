#include "GreatSowrd.h"

void CGreatSowrd::Start()
{
	m_ModelData = SINSTANCE(CSkinModelManager)->LoadModel("GreatSowrd.X");
	m_model.SetModelData(&m_ModelData);
	m_Transform.LocalRotation = D3DXVECTOR3(-90.0f, 0.0f, 0.0f);
	m_model.RenderType(TYPE::SPECULAR, true);
}

void CGreatSowrd::Update()
{
	m_Transform.UpdateTransform();
	ItemUpdata();
}

void CGreatSowrd::LateUpdate()
{
	//m_model.UpdateFrameMatrix();
}

void CGreatSowrd::Render()
{
	m_model.Render(*m_ppCamera, m_pLightCamera, m_pLight);
}