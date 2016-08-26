#include "Light.h"

CLight CLight::Standard;
CLight CLight::NoLight;

CLight::CLight()
{
	if (Standard.m_DiffuseLight.Direction == NULL)
	{
		//�f�B�t���[�Y���C�g�B
		LIGHT standardlight[] =
		{
			//������
			{ D3DXVECTOR4(0.0f, 0.0f, 1.0f, 1.0f), D3DXVECTOR4(0.5f, 0.5f, 0.5f, 1.0f) },
			//������
			{ D3DXVECTOR4(0.0f, -1.0f, 0.0f, 1.0f), D3DXVECTOR4(0.5f, 0.5f, 0.5f, 1.0f) },
			//�E����
			{ D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f), D3DXVECTOR4(0.5f, 0.5f, 0.5f, 1.0f) },
			//������
			{ D3DXVECTOR4(-1.0f, 0.0f, 0.0f, 1.0f), D3DXVECTOR4(0.5f, 0.5f, 0.5f, 1.0f) }
		};

		Standard.CreateDiffuseLight(standardlight, sizeof(standardlight) / sizeof(LIGHT));
		//�����B
		Standard.CreateAmbientLight(D3DXVECTOR4(0.5f, 0.5f, 0.5f, 1.0f));
	}

	if (NoLight.m_DiffuseLight.Direction == NULL)
	{
		//�f�B�t���[�Y���C�g�B
		LIGHT standardlight[] =
		{
			//������
			{ D3DXVECTOR4(0.0f, 0.0f, 0.0f, 1.0f), D3DXVECTOR4(0.0f, 0.0f, 0.0f, 0.0f) },
			//������
			{ D3DXVECTOR4(0.0f, 0.0f, 0.0f, 1.0f), D3DXVECTOR4(0.0f, 0.0f, 0.0f, 0.0f) },
			//�E����
			{ D3DXVECTOR4(0.0f, 0.0f, 0.0f, 1.0f), D3DXVECTOR4(0.0f, 0.0f, 0.0f, 0.0f) },
			//������
			{ D3DXVECTOR4(0.0f, 0.0f, 0.0f, 1.0f), D3DXVECTOR4(0.0f, 0.0f, 0.0f, 0.0f) }
		};

		NoLight.CreateDiffuseLight(standardlight, sizeof(standardlight) / sizeof(LIGHT));
		//�����B
		NoLight.CreateAmbientLight(D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f));
	}
}

void CLight::CreateDiffuseLight(LIGHT* date,UINT lightnum)
{
	DLIGHT_NUM = lightnum;
	m_DiffuseLight.Direction = new D3DXVECTOR4[DLIGHT_NUM]();
	m_DiffuseLight.Color = new D3DXVECTOR4[DLIGHT_NUM]();
	for (short i = 0; i < DLIGHT_NUM; i++)
	{
		m_DiffuseLight.Direction[i] = date[i].Direction;
		m_DiffuseLight.Color[i] = date[i].Color;
	}
}

void CLight::CreateAmbientLight(D3DXVECTOR4 ambient)
{
	//�����B
	m_ambientLight = ambient;
}