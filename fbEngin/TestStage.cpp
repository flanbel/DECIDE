#include "TestStage.h"

void CTestStage::Start()
{
	m_ModelData = SINSTANCE(CSkinModelManager)->LoadModel("TestStage.X");
	m_model.SetModelData(&m_ModelData);

	m_Transform.LocalRotation = D3DXVECTOR3(-90, 0.0, 0.0);
}

void CTestStage::Update()
{
	m_Transform.UpdateTransform();
	//m_model.UpdateFrameMatrix();
}

void CTestStage::Render()
{
	m_model.Render(*m_ppCamera, m_pLightCamera, m_pLight);
}