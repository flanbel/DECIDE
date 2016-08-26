#include "GaussianFilter.h"

LPDIRECT3DVERTEXBUFFER9 CGaussianFilter::m_pVB = nullptr;

CGaussianFilter::CGaussianFilter()
{
	//���L�|������
	if (m_pVB == NULL)
	{
		//�P�ʃ|���S��(������������(�c��1�s�N�Z��))
		//��ŏ㉺���]������̂ł����č����ɂ���B
		SpriteVertex vertices[] = {
			{ 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, },//����
			{ 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, },//�E��
			{ 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, },//����
			{ 1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f, },//�E��
		};

		//���_����
		(*graphicsDevice()).CreateVertexBuffer(sizeof(SpriteVertex), 0, D3DFVF_SPRITEVERTEX, D3DPOOL_DEFAULT, &m_pVB, NULL);
		//���_�o�b�t�@�ւ̃A�h���X���i�[����B
		VOID* pVertices;
		//�A�h���X�擾
		m_pVB->Lock(0, sizeof(vertices), (void**)&pVertices, D3DLOCK_DISCARD);
		//�A�h���X�֒��_��`���R�s�[
		memcpy(pVertices, vertices, sizeof(vertices));
		//���b�N����
		m_pVB->Unlock();
	}

	//�G�t�F�N�g�ǂݍ���
	m_pEffect = SINSTANCE(CEffectManager)->LoadEffect("GaussianFilter.fx");

	//m_RT = new TEXTURE();
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


TEXTURE CGaussianFilter::GaussianBlur(TEXTURE* ptex)
{
	if (m_RT.pTexture ==nullptr)
	m_RenderTarget.CreateRenderTarget(&m_RT, ptex->imgInfo.Width, ptex->imgInfo.Height);

	m_RenderTarget.SetRenderTarget(0);

	UpdateWeight(25.0f);

	//�ڂ����ĕ`��
	{
		D3DXMATRIX  matWorld, matSize, matTrans;

		D3DXMatrixIdentity(&matWorld);
		//�摜�̃T�C�Y��ݒ�
		D3DXMatrixScaling(&matSize, (float)ptex->imgInfo.Width, (float)ptex->imgInfo.Height, 1.0f);
		//�ړ�
		D3DXMatrixTranslation(&matTrans, GAME_CLIENT_WIDTH, GAME_CLIENT_HEIGHT, 0.0f);

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
				m_pEffect->SetValue("g_offset", offset,sizeof(offset) );
				m_pEffect->SetValue("g_weight",m_weights ,sizeof(m_weights) );

				m_pEffect->CommitChanges();

				(*graphicsDevice()).SetStreamSource(0, m_pVB, 0, sizeof(SpriteVertex));
				(*graphicsDevice()).SetFVF(D3DFVF_SPRITEVERTEX);
				(*graphicsDevice()).DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

				m_pEffect->EndPass();
				m_pEffect->End();
			}

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

	m_RenderTarget.BeforeRenderTarget();

	/**ptex->pTexture = *m_RT.pTexture;
	m_image.SetTex(m_RT);
	m_image.Render();*/

	return m_RT;
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