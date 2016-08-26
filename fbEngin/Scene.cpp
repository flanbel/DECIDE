#include "Scene.h"

CScene::CScene()
{
	//�E����ɍ��
	m_vertices[0] = { -1.0f, -1.0f, 0.0f, 1.0f, D3DCOLOR_RGBA(0, 0, 0, 0) };//����
	m_vertices[1] = { -1.0f, 1.0f, 0.0f, 1.0f,	D3DCOLOR_RGBA(0, 0, 0, 0) };//����
	m_vertices[2] = { 1.0f, -1.0f, 0.0f, 1.0f,	D3DCOLOR_RGBA(0, 0, 0, 0) };//�E��
	m_vertices[3] = { 1.0f, 1.0f, 0.0f, 1.0f,	D3DCOLOR_RGBA(0, 0, 0, 0) };//�E��

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
		//���������ɏ�����
		m_vertices[0].color = D3DCOLOR_RGBA(0, 0, 0, 0);
		m_vertices[1].color = D3DCOLOR_RGBA(0, 0, 0, 0);
		m_vertices[2].color = D3DCOLOR_RGBA(0, 0, 0, 0);
		m_vertices[3].color = D3DCOLOR_RGBA(0, 0, 0, 0);
	}

	bool a1 = false, a2 = false;
	short alpha = 2;

	//���ߓx���ő�̂���Ȃ���
	short alpha1 = (m_vertices[0].color >> 24);//�J���[���E��24�r�b�g�V�t�g���ă�����
	if (alpha1 + alpha < 255)
	{
		m_vertices[0].color += D3DCOLOR_RGBA(0, 0, 0, alpha);//���l�𑝉�
		m_vertices[1].color += D3DCOLOR_RGBA(0, 0, 0, alpha);
	}
	else
	{
		a1 = true;
	}


	short alpha2 = (m_vertices[2].color >> 24);//�J���[���E��24�r�b�g�V�t�g���ă�����
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

		//�e�N�j�b�N�ݒ�
		m_pEffect->SetTechnique("TestPrimitive");

		m_pEffect->Begin(NULL, 0);
		m_pEffect->BeginPass(0);

		//���_���ݒ�
		(*graphicsDevice()).SetFVF(D3DFVF_COLORVERTEX);
		//�`��
		//DrawPrimitiveUP�֐��͂��̊֐��̒��Œ��_�o�b�t�@�[���쐬���ĕ`�悵�Ă���̂ŏd��
		(*graphicsDevice()).DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, m_vertices, sizeof(ColorVertex));

		m_pEffect->EndPass();
		m_pEffect->End();

		//�ύX�����X�e�[�g�����ɖ߂�
		(*graphicsDevice()).SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
		(*graphicsDevice()).SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);
		(*graphicsDevice()).SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ZERO);
	}
}