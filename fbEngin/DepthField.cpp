#include "DepthField.h"
#include "EffectManager.h"

void CDepthField::Initialize()
{
	m_RT[0].CreateRenderTarget(&m_tex[0], GAME_CLIENT_WIDTH, GAME_CLIENT_HEIGHT);
	m_RT[1].CreateRenderTarget(&m_tex[1], GAME_CLIENT_WIDTH, GAME_CLIENT_HEIGHT);
	m_RT[2].CreateRenderTarget(&m_tex[2], GAME_CLIENT_WIDTH, GAME_CLIENT_HEIGHT);

	//エフェクト読み込み
	m_pEffect = SINSTANCE(CEffectManager)->LoadEffect("DepthField.fx");
}

void CDepthField::DepthofField(TEXTURE* tex1, TEXTURE* Depth)
{
	m_RT[0].SetRenderTarget(0);

	m_Gaussian.XBlur(tex1, 5.0f);

	m_RT[1].SetRenderTarget(0);

	m_Gaussian.YBlur(&m_tex[0], 5.0f);

	//[1]ぼやけ

	m_RT[2].SetRenderTarget(0);

	m_Gaussian.XBlur(&m_tex[1], 15.0f);

	m_RT[0].SetRenderTarget(0);

	m_Gaussian.YBlur(&m_tex[2], 15.0f);

	//[0]もっとぼやけ

	CRenderTarget::BeforeRenderTarget();

	//被写界深度
	{
		D3DXMATRIX  matWorld, matSize, matTrans;

		D3DXMatrixIdentity(&matWorld);
		//画像のサイズを設定
		D3DXMatrixScaling(&matSize, (float)tex1->imgInfo.Width, (float)tex1->imgInfo.Height, 1.0f);
		//移動
		D3DXMatrixTranslation(&matTrans, GAME_CLIENT_WIDTH, GAME_CLIENT_HEIGHT, 0.0f);

		//画像サイズ * ポジション
		matWorld = matSize * matTrans;

		float h = GAME_CLIENT_HEIGHT;
		float w = GAME_CLIENT_WIDTH;

		// 射影変換行列？
		//縦横を画面のサイズでスケーリング
		//画面の中心が基準になっているのでXに-1.0f,Yに1.0fだけオフセットする。
		D3DXMATRIX Proj(
			2.0f / w, 0.0f, 0.0f, 0.0f,
			0.0f, -2.0f / h, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			-1.0f, 1.0f, 0.0f, 1.0f
			);

		D3DXMATRIX wp = matWorld * Proj;


		{
			(*graphicsDevice()).SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
			(*graphicsDevice()).SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			(*graphicsDevice()).SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

			//Xblur
			{
				//テクニック設定
				m_pEffect->SetTechnique("DepthField");

				m_pEffect->Begin(NULL, 0);
				m_pEffect->BeginPass(0);

				m_pEffect->SetMatrix("g_mWVP", &wp);
				m_pEffect->SetTexture("g_Depth", Depth->pTexture);
				m_pEffect->SetTexture("g_Tex1", tex1->pTexture);
				m_pEffect->SetTexture("g_Tex2", m_tex[1].pTexture);
				m_pEffect->SetTexture("g_Tex3", m_tex[0].pTexture);
				m_pEffect->CommitChanges();

				(*graphicsDevice()).SetStreamSource(0, m_pVB, 0, sizeof(SpriteVertex));
				(*graphicsDevice()).SetFVF(D3DFVF_SPRITEVERTEX);
				(*graphicsDevice()).DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

				m_pEffect->EndPass();
				m_pEffect->End();
			}

			//変更したステートを元に戻す
			(*graphicsDevice()).SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
			(*graphicsDevice()).SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);
			(*graphicsDevice()).SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ZERO);
		}
	}

	m_pEffect->Begin(0, NULL);
}