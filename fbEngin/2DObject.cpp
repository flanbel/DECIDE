#include "2DObject.h"

C2DObject::C2DObject(string name) : CGameObject(name)
{
	//�񎟌�
	m_Dimension = DIMENSION::D2;
}

C2DObject::~C2DObject()
{

}