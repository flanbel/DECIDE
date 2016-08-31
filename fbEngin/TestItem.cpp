#include "TestItem.h"

void CTestItem::Start()
{
	m_ModelData = SINSTANCE(CSkinModelManager)->LoadModel("Hunmer.X");
	m_model.SetModelData(&m_ModelData);
	//m_Transform.LocalPosition = D3DXVECTOR3(10.0f, 0.0f, -10.0f);
}

void CTestItem::Update()
{
	m_Transform.UpdateTransform();
}

void CTestItem::LateUpdate()
{
	//m_model.UpdateFrameMatrix();
}

void CTestItem::Render()
{
	m_model.Render(*m_ppCamera, m_pLightCamera, m_pLight);
}