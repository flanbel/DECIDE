#include "GaussianFilter.h"
#include "EffectManager.h"

CGaussianFilter::CGaussianFilter()
{
	//エフェクト読み込み
	m_pEffect = SINSTANCE(CEffectManager)->LoadEffect("GaussianFilter.fx");
}

void CGaussianFilter::XBlur(TEXTURE* ptex,FLOAT dispersion)
{
	UpdateWeight(dispersion);

	//ぼかして描画
	{
		D3DXMATRIX  matWorld, matSize, matTrans;

		D3DXMatrixIdentity(&matWorld);
		//画像のサイズを設定
		D3DXMatrixScaling(&matSize, (float)ptex->imgInfo.Width, (float)ptex->imgInfo.Height, 1.0f);
		//移動
		D3DXMatrixTranslation(&matTrans, GAME_CLIENT_WIDTH/2, GAME_CLIENT_HEIGHT/2, 0.0f);

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
				m_pEffect->SetTechnique("GaussianBlur");

				m_pEffect->Begin(NULL, 0);
				m_pEffect->BeginPass(0);

				float size[2] = {
					ptex->imgInfo.Width,
					ptex->imgInfo.Height
				};
				float offset[] = {
					16.0f / ptex->imgInfo.Width,
					0.0f
				};

				m_pEffect->SetMatrix("g_mWVP", &wp);
				m_pEffect->SetTexture("g_tex", ptex->pTexture);
				m_pEffect->SetValue("g_TexSize", size, sizeof(size));
				m_pEffect->SetValue("g_offset", offset, sizeof(offset));
				m_pEffect->SetValue("g_weight", m_weights, sizeof(m_weights));

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
}

void CGaussianFilter::YBlur(TEXTURE* ptex, FLOAT dispersion)
{
	UpdateWeight(dispersion);

	//ぼかして描画
	{
		D3DXMATRIX  matWorld, matSize, matTrans;

		D3DXMatrixIdentity(&matWorld);
		//画像のサイズを設定
		D3DXMatrixScaling(&matSize, (float)ptex->imgInfo.Width, (float)ptex->imgInfo.Height, 1.0f);
		//移動
		D3DXMatrixTranslation(&matTrans, GAME_CLIENT_WIDTH / 2, GAME_CLIENT_HEIGHT / 2, 0.0f);

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

			//Yblur
			{
				//テクニック設定
				m_pEffect->SetTechnique("GaussianBlur");

				m_pEffect->Begin(NULL, 0);
				m_pEffect->BeginPass(1);

				float size[2] = {
					ptex->imgInfo.Width,
					ptex->imgInfo.Height
				};
				float offset[] = {
					0.0f,
					16.0f / ptex->imgInfo.Height
				};

				m_pEffect->SetMatrix("g_mWVP", &wp);
				m_pEffect->SetTexture("g_tex", ptex->pTexture);
				m_pEffect->SetValue("g_TexSize", size, sizeof(size));
				m_pEffect->SetValue("g_offset", offset, sizeof(offset));
				m_pEffect->SetValue("g_weight", m_weights, sizeof(m_weights));

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
}

void CGaussianFilter::UpdateWeight(FLOAT dispersion)
{
	DWORD i;
	FLOAT total = 0;
	for (i = 0; i < NUM_WEIGHTS; i++){
		m_weights[i] = expf(-0.5f*(FLOAT)(i*i) / dispersion);
		if (0 == i){
			total += m_weights[i];
		}
		else{
			// 中心以外は、２回同じ係数を使うので２倍
			total += 2.0f*m_weights[i];
		}
	}
	// 規格化
	for (i = 0; i < NUM_WEIGHTS; i++) m_weights[i] /= total;
}