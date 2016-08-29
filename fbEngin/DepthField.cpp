#include "DepthField.h"
#include "EffectManager.h"

void CDepthField::Initialize()
{
	m_RT[0].CreateRenderTarget(&m_tex[0], GAME_CLIENT_WIDTH, GAME_CLIENT_HEIGHT);
	m_RT[1].CreateRenderTarget(&m_tex[1], GAME_CLIENT_WIDTH, GAME_CLIENT_HEIGHT);
	m_RT[2].CreateRenderTarget(&m_tex[2], GAME_CLIENT_WIDTH, GAME_CLIENT_HEIGHT);

	//�G�t�F�N�g�ǂݍ���
	m_pEffect = SINSTANCE(CEffectManager)->LoadEffect("DepthField.fx");
}

void CDepthField::DepthofField(TEXTURE* tex1, TEXTURE* Depth)
{
	m_RT[0].SetRenderTarget(0);

	m_Gaussian.XBlur(tex1, 5.0f);

	m_RT[1].SetRenderTarget(0);

	m_Gaussian.YBlur(&m_tex[0], 5.0f);

	//[1]�ڂ₯

	m_RT[2].SetRenderTarget(0);

	m_Gaussian.XBlur(&m_tex[1], 15.0f);

	m_RT[0].SetRenderTarget(0);

	m_Gaussian.YBlur(&m_tex[2], 15.0f);

	//[0]�����Ƃڂ₯

	CRenderTarget::BeforeRenderTarget();

	//��ʊE�[�x
	{
		D3DXMATRIX  matWorld, matSize, matTrans;

		D3DXMatrixIdentity(&matWorld);
		//�摜�̃T�C�Y��ݒ�
		D3DXMatrixScaling(&matSize, (float)tex1->imgInfo.Width, (float)tex1->imgInfo.Height, 1.0f);
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

			//�ύX�����X�e�[�g�����ɖ߂�
			(*graphicsDevice()).SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
			(*graphicsDevice()).SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);
			(*graphicsDevice()).SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ZERO);
		}
	}

	m_pEffect->Begin(0, NULL);
}