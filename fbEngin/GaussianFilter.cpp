#include "GaussianFilter.h"
#include "EffectManager.h"

CGaussianFilter::CGaussianFilter()
{
	//�G�t�F�N�g�ǂݍ���
	m_pEffect = SINSTANCE(CEffectManager)->LoadEffect("GaussianFilter.fx");
}

void CGaussianFilter::XBlur(TEXTURE* ptex,FLOAT dispersion)
{
	UpdateWeight(dispersion);

	//�ڂ����ĕ`��
	{
		D3DXMATRIX  matWorld, matSize, matTrans;

		D3DXMatrixIdentity(&matWorld);
		//�摜�̃T�C�Y��ݒ�
		D3DXMatrixScaling(&matSize, (float)ptex->imgInfo.Width, (float)ptex->imgInfo.Height, 1.0f);
		//�ړ�
		D3DXMatrixTranslation(&matTrans, GAME_CLIENT_WIDTH/2, GAME_CLIENT_HEIGHT/2, 0.0f);

		//�摜�T�C�Y * �|�W�V����
		matWorld = matSize * matTrans;

		float h = GAME_CLIENT_HEIGHT;
		float w = GAME_CLIENT_WIDTH;

		// �ˉe�ϊ��s��H
		//�c������ʂ̃T�C�Y�ŃX�P�[�����O
		//��ʂ̒��S����ɂȂ��Ă���̂�X��-1.0f,Y��1.0f�����I�t�Z�b�g����B
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
				//�e�N�j�b�N�ݒ�
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

			//�ύX�����X�e�[�g�����ɖ߂�
			(*graphicsDevice()).SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
			(*graphicsDevice()).SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);
			(*graphicsDevice()).SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ZERO);
		}
	}
}

void CGaussianFilter::YBlur(TEXTURE* ptex, FLOAT dispersion)
{
	UpdateWeight(dispersion);

	//�ڂ����ĕ`��
	{
		D3DXMATRIX  matWorld, matSize, matTrans;

		D3DXMatrixIdentity(&matWorld);
		//�摜�̃T�C�Y��ݒ�
		D3DXMatrixScaling(&matSize, (float)ptex->imgInfo.Width, (float)ptex->imgInfo.Height, 1.0f);
		//�ړ�
		D3DXMatrixTranslation(&matTrans, GAME_CLIENT_WIDTH / 2, GAME_CLIENT_HEIGHT / 2, 0.0f);

		//�摜�T�C�Y * �|�W�V����
		matWorld = matSize * matTrans;

		float h = GAME_CLIENT_HEIGHT;
		float w = GAME_CLIENT_WIDTH;

		// �ˉe�ϊ��s��H
		//�c������ʂ̃T�C�Y�ŃX�P�[�����O
		//��ʂ̒��S����ɂȂ��Ă���̂�X��-1.0f,Y��1.0f�����I�t�Z�b�g����B
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
				//�e�N�j�b�N�ݒ�
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

			//�ύX�����X�e�[�g�����ɖ߂�
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
			// ���S�ȊO�́A�Q�񓯂��W�����g���̂łQ�{
			total += 2.0f*m_weights[i];
		}
	}
	// �K�i��
	for (i = 0; i < NUM_WEIGHTS; i++) m_weights[i] /= total;
}