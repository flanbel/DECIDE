#include "Scene.h"

CScene::CScene()
{
	//右周りに作る
	m_vertices[0] = { -1.0f, -1.0f, 0.0f, 1.0f, D3DCOLOR_RGBA(0, 0, 0, 0) };//左下
	m_vertices[1] = { -1.0f, 1.0f, 0.0f, 1.0f,	D3DCOLOR_RGBA(0, 0, 0, 0) };//左上
	m_vertices[2] = { 1.0f, -1.0f, 0.0f, 1.0f,	D3DCOLOR_RGBA(0, 0, 0, 0) };//右下
	m_vertices[3] = { 1.0f, 1.0f, 0.0f, 1.0f,	D3DCOLOR_RGBA(0, 0, 0, 0) };//右上

	m_pEffect = SINSTANCE(CEffectManager)->LoadEffect("Test.fx");

	InitFade();
}

void CScene::InitFade()
{
	FOR(ARRAY_SIZE(m_vertices))
	{
		m_vertices[i].color = D3DCOLOR_RGBA(0, 0, 0, 0);
	}
	m_Fade = false;
	m_endFade = true;
}

void CScene::FadeOut()
{
	if (!m_Fade)
	{
		m_Fade = true;
		m_endFade = false;
		//黒い透明に初期化
		m_vertices[0].color = D3DCOLOR_RGBA(0, 0, 0, 0);
		m_vertices[1].color = D3DCOLOR_RGBA(0, 0, 0, 0);
		m_vertices[2].color = D3DCOLOR_RGBA(0, 0, 0, 0);
		m_vertices[3].color = D3DCOLOR_RGBA(0, 0, 0, 0);
	}

	bool a1 = false, a2 = false;
	short alpha = 2;

	//透過度が最大のじゃない時
	short alpha1 = (m_vertices[0].color >> 24);//カラーを右に24ビットシフトしてα入手
	if (alpha1 + alpha < 255)
	{
		m_vertices[0].color += D3DCOLOR_RGBA(0, 0, 0, alpha);//α値を増加
		m_vertices[1].color += D3DCOLOR_RGBA(0, 0, 0, alpha);
	}
	else
	{
		a1 = true;
	}


	short alpha2 = (m_vertices[2].color >> 24);//カラーを右に24ビットシフトしてα入手
	if (alpha2 + alpha < 255)
	{
		m_vertices[2].color += D3DCOLOR_RGBA(0, 0, 0, alpha);
		m_vertices[3].color += D3DCOLOR_RGBA(0, 0, 0, alpha);
	}
	else
	{
		a2 = true;
	}

	if (a1 && a2)
	{
		m_endFade = true;
	}
}

void CScene::DrawFade()
{
	if (m_Fade)
	{
		(*graphicsDevice()).SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
		(*graphicsDevice()).SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		(*graphicsDevice()).SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

		//テクニック設定
		m_pEffect->SetTechnique("TestPrimitive");

		m_pEffect->Begin(NULL, 0);
		m_pEffect->BeginPass(0);

		//頂点情報設定
		(*graphicsDevice()).SetFVF(D3DFVF_COLORVERTEX);
		//描画
		//DrawPrimitiveUP関数はこの関数の中で頂点バッファーを作成して描画しているので重い
		(*graphicsDevice()).DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, m_vertices, sizeof(ColorVertex));

		m_pEffect->EndPass();
		m_pEffect->End();

		//変更したステートを元に戻す
		(*graphicsDevice()).SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
		(*graphicsDevice()).SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);
		(*graphicsDevice()).SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ZERO);
	}
}