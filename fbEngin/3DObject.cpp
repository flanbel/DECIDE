#include "3DObject.h"

//�R���X�g���N�^�𖾎��I�ɌĂ�ł���
C3DObject::C3DObject(string name) :
CGameObject(name),
m_model(&m_Transform)
{
	m_Dimension = DIMENSION::D3;
	m_pCamera = nullptr;
	m_pLight = &CLight::Standard;
}