#include "Sprite.h"
#include "Transform.h"
#include "EffectManager.h"

//�S�Ă��I�������ɉ��
LPDIRECT3DVERTEXBUFFER9 CSprite::m_pVB = NULL;

CSprite::CSprite()
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
	m_pEffect = SINSTANCE(CEffectManager)->LoadEffect("Sprite.fx");

	//UV������
	SetUV(0.0f, 0.0f, 1.0f, 1.0f);
	SetBlendColor(D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f));
	//�����l�͓����ȍ�
	m_KillColor = D3DCOLOR_ARGB(0, 0, 0, 0);
}

void CSprite::Render(CTransform trans)
{
	D3DXMATRIX  matWorld, matSize, matScale, matRot, matTrans;

	D3DXMatrixIdentity(&matWorld);
	//�摜�̃T�C�Y��ݒ�
	D3DXMatrixScaling(&matSize, (float)m_tex.imgInfo.Width, (float)m_tex.imgInfo.Height, 1.0f);
	//�ݒ肳�ꂽ�X�P�[����ݒ�
	D3DXMatrixScaling(&matScale, trans.Scale.x, trans.Scale.y, trans.Scale.z);
	//��]
	D3DXMatrixRotationZ(&matRot, D3DXToRadian(trans.Rotation.z));
	//�ړ�
	D3DXMatrixTranslation(&matTrans, trans.Position.x, trans.Position.y, trans.Position.z);

	//�摜�T�C�Y�@*�@�X�P�[���@*�@��]�@*�@�|�W�V����
	matWorld = matSize * matScale * matRot * matTrans;

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

	//if (m_tex.pTexture != nullptr)
	{

		(*graphicsDevice()).SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
		(*graphicsDevice()).SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		(*graphicsDevice()).SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

		//�e�N�j�b�N�ݒ�
		m_pEffect->SetTechnique("SpriteTech");

		m_pEffect->Begin(NULL, 0);
		m_pEffect->BeginPass(0);

		//�s��
		m_pEffect->SetMatrix("g_mWVP", &wp);

		if (m_tex.pTexture == nullptr)
		{
			//�摜���Ȃ������Ƃ��p�̋~��
			LoadTexture("noimage.png");
		}

		//�e�N�X�`��
		m_pEffect->SetTexture("g_texture", m_tex.pTexture);

		//UV�ݒ�
		m_pEffect->SetFloat("uv_left", m_uv.x);
		m_pEffect->SetFloat("uv_top", m_uv.y);
		m_pEffect->SetFloat("uv_width", m_uv.z);
		m_pEffect->SetFloat("uv_height", m_uv.w);

		//pivot�ݒ�(�X�P�[�����O���]�̊�_)
		m_pEffect->SetFloat("pivotx", m_tex.pivot.x);
		m_pEffect->SetFloat("pivoty", m_tex.pivot.y);

		//�F�ݒ�
		m_pEffect->SetVector("g_blendColor", (D3DXVECTOR4*)&m_BlendColor);
		//�����F�ݒ�
		m_pEffect->SetVector("g_killColor", (D3DXVECTOR4*)&m_KillColor);

		//���̊֐����Ăяo�����ƂŁA�f�[�^�̓]�����m�肷��B�`����s���O�Ɉ�񂾂��Ăяo���B
		m_pEffect->CommitChanges();

		(*graphicsDevice()).SetStreamSource(0, m_pVB, 0, sizeof(SpriteVertex));
		//���_���ݒ�
		(*graphicsDevice()).SetFVF(D3DFVF_SPRITEVERTEX);
		//D3DPT_TRIANGLESTRIP�͘A���������_�ŎO�p�`���`��
		(*graphicsDevice()).DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

		m_pEffect->EndPass();
		m_pEffect->End();

		//�ύX�����X�e�[�g�����ɖ߂�
		(*graphicsDevice()).SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
		(*graphicsDevice()).SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);
		(*graphicsDevice()).SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ZERO);
	}
}