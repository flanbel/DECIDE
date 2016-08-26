
#ifndef _SPRITE_H_
#define _SPRITE_H_

#include "TextureManager.h"
#include "Effect.h"

class CTransform;
//�X�v���C�g�p�̒��_����`
#define D3DFVF_SPRITEVERTEX (D3DFVF_XYZW|D3DFVF_TEX1)

//���_���(�X�v���C�g�p���_)
struct SpriteVertex
{
	float x, y, z;
	float w;
	float u, v;
};

//2D�`���S������R���|�[�l���g
class CSprite
{
public:
	CSprite();
	//2D��`�悵���ۂ͌Ă�łق���(�V�[���̃f�X�g���N�^��)
	void ReleaseVertex()
	{
		if (m_pVB != NULL)
		{
			m_pVB->Release();
			m_pVB = NULL;
		}
	}

	//�����Ƃ��Ď󂯎�����g�����X�t�H�[������ɉ摜�`��
	//�������FCTransform �g�����X�t�H�[��
	void Render(CTransform trans);

	//�e�N�X�`���ύX
	void LoadTexture(LPCSTR FileName)
	{
		//�e�N�X�`���ǂݍ���
		m_tex = SINSTANCE(CTextureManager)->LoadTexture(FileName);
	}

	void SetUV(float left,float top,float width,float height)
	{
		m_uv = { left, top, width, height };
	}

	void SetBlendColor(D3DXVECTOR4 v)
	{
		m_BlendColor.r = v.x;
		m_BlendColor.g = v.y;
		m_BlendColor.b = v.z;
		m_BlendColor.a = v.w;
	}

	//������F�I��(�����_)
	void SetBlendColor(float r,float g,float b)
	{
		m_BlendColor.r = r;
		m_BlendColor.g = g;
		m_BlendColor.b = b;
		
	}
	//������F�I��(����)
	void SetBlendColor(int r, int g,int b)
	{
		//���ێ�
		float a = m_BlendColor.a;
		m_BlendColor = D3DCOLOR_XRGB(r, g, b);
		m_BlendColor.a = a;
	}
	//���Z�b�g
	void SetAlpha(float alpha)
	{
		m_BlendColor.a = alpha;
	}
	//�����x���Z
	void AddAlpha(float alpha)
	{
		m_BlendColor.a += alpha;
	}

	void SetKillColor(D3DXCOLOR color)
	{
		m_KillColor = color;
	}

	void SetTexture(TEXTURE tex)
	{
		m_tex = tex;
	}
	//�e�N�X�`���Q�b�g
	const TEXTURE GetTex()
	{
		return m_tex;
	}
	//�e�N�X�`���̃|�C���^�Q�b�g
	TEXTURE* GetpTex()
	{
		return &m_tex;
	}

	//�t�F�[�h�C���E�A�E�g����֐�
	//�������Fbool�@�C�����A�E�g��,�������Fshort ���t���[���ŏ����邩
	void Fade(bool mode, short Fream)
	{
		//1�t���[��������̑����ʎZ�o
		float addAlpha = 1.0f / Fream;
		//�t�F�[�h�A�E�g�Ȃ�
		if (!mode)
			addAlpha *= -1;		//���]
		//�����x���Z
		AddAlpha(addAlpha);
	}
protected:
	//UV
	D3DXVECTOR4 m_uv;
	//�e�N�X�`��
	TEXTURE m_tex;
	CEffect* m_pEffect;
	//������F
	D3DXCOLOR m_BlendColor;
	
	//�폜����F(���ߐF�w��)
	D3DXCOLOR m_KillColor;

	//�������g���܂킷�̂�static
	//���_�o�b�t�@�[
	static LPDIRECT3DVERTEXBUFFER9 m_pVB;
};
#endif //_SPRITE_H_