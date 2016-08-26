#include "Light.h"

CLight CLight::Standard;
CLight CLight::NoLight;

CLight::CLight()
{
	if (Standard.m_DiffuseLight.Direction == NULL)
	{
		//ディフューズライト。
		LIGHT standardlight[] =
		{
			//奥向き
			{ D3DXVECTOR4(0.0f, 0.0f, 1.0f, 1.0f), D3DXVECTOR4(0.5f, 0.5f, 0.5f, 1.0f) },
			//下向き
			{ D3DXVECTOR4(0.0f, -1.0f, 0.0f, 1.0f), D3DXVECTOR4(0.5f, 0.5f, 0.5f, 1.0f) },
			//右向き
			{ D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f), D3DXVECTOR4(0.5f, 0.5f, 0.5f, 1.0f) },
			//左向き
			{ D3DXVECTOR4(-1.0f, 0.0f, 0.0f, 1.0f), D3DXVECTOR4(0.5f, 0.5f, 0.5f, 1.0f) }
		};

		Standard.CreateDiffuseLight(standardlight, sizeof(standardlight) / sizeof(LIGHT));
		//環境光。
		Standard.CreateAmbientLight(D3DXVECTOR4(0.5f, 0.5f, 0.5f, 1.0f));
	}

	if (NoLight.m_DiffuseLight.Direction == NULL)
	{
		//ディフューズライト。
		LIGHT standardlight[] =
		{
			//奥向き
			{ D3DXVECTOR4(0.0f, 0.0f, 0.0f, 1.0f), D3DXVECTOR4(0.0f, 0.0f, 0.0f, 0.0f) },
			//下向き
			{ D3DXVECTOR4(0.0f, 0.0f, 0.0f, 1.0f), D3DXVECTOR4(0.0f, 0.0f, 0.0f, 0.0f) },
			//右向き
			{ D3DXVECTOR4(0.0f, 0.0f, 0.0f, 1.0f), D3DXVECTOR4(0.0f, 0.0f, 0.0f, 0.0f) },
			//左向き
			{ D3DXVECTOR4(0.0f, 0.0f, 0.0f, 1.0f), D3DXVECTOR4(0.0f, 0.0f, 0.0f, 0.0f) }
		};

		NoLight.CreateDiffuseLight(standardlight, sizeof(standardlight) / sizeof(LIGHT));
		//環境光。
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
	//環境光。
	m_ambientLight = ambient;
}