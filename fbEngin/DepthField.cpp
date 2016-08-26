#include "DepthField.h"

void CDepthField::Initialize()
{
	m_RT[0].CreateRenderTarget(&m_tex[0], GAME_CLIENT_WIDTH, GAME_CLIENT_HEIGHT);
	m_RT[1].CreateRenderTarget(&m_tex[1], GAME_CLIENT_WIDTH, GAME_CLIENT_HEIGHT);
	m_RT[2].CreateRenderTarget(&m_tex[2], GAME_CLIENT_WIDTH, GAME_CLIENT_HEIGHT);

	m_image.Transform()->Position = D3DXVECTOR3(0.0f, GAME_CLIENT_HEIGHT / 2, 0.0f);
}

void CDepthField::DepthofField(TEXTURE* tex1, TEXTURE* Depth)
{
	m_RT[0].SetRenderTarget(0);

	m_Gaussian.XBlur(tex1, 5.0f);

	m_RT[1].SetRenderTarget(0);

	m_Gaussian.YBlur(&m_tex[0], 5.0f);

	//[1]‚Ú‚â‚¯

	m_RT[2].SetRenderTarget(0);

	m_Gaussian.XBlur(&m_tex[1], 15.0f);

	m_RT[0].SetRenderTarget(0);

	m_Gaussian.YBlur(&m_tex[2], 15.0f);

	//[0]‚à‚Á‚Æ‚Ú‚â‚¯

	CRenderTarget::BeforeRenderTarget();

	m_image.SetTex(*Depth);
	m_image.Render();
}