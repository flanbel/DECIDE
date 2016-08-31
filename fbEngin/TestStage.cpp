#include "TestStage.h"

void CTestStage::Start()
{
	m_ModelData = SINSTANCE(CSkinModelManager)->LoadModel("Stage.X");
	m_model.SetModelData(&m_ModelData);
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