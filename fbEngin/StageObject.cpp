#include "StageObject.h"

CStageObject::CStageObject(const char* xfile,string name) :C3DObject(name)
{

	m_ModelData = SINSTANCE(CSkinModelManager)->LoadModel("Field/CampFire.X");
	m_model.SetModelData(&m_ModelData);
}

CStageObject::~CStageObject()
{

}

void CStageObject::Start()
{

}

void CStageObject::Update()
{
	m_Transform.UpdateTransform();
}

void CStageObject::Render()
{
	m_model.Render(*m_ppCamera, m_pLightCamera, m_pLight);
}