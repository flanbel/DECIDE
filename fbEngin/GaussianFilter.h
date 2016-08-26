

#ifndef _GAUSSIANFILTER_H_
#define _GAUSSIANFILTER_H_

#include "RenderTarget.h"
#include "TextureManager.h"
#include "EffectManager.h"
#include "Effect.h"

#include "Image.h"

//�K�E�X�t�B���^��������N���X
class CGaussianFilter
{
	//�X�v���C�g�p�̒��_����`
#define D3DFVF_SPRITEVERTEX (D3DFVF_XYZW|D3DFVF_TEX1)
#define NUM_WEIGHTS 8

	//���_���(�X�v���C�g�p���_)
	struct SpriteVertex
	{
		float x, y, z;
		float w;
		float u, v;
	};

public:
	CGaussianFilter();
	//�󂯎�����e�N�X�`���ɂڂ�����������B
	TEXTURE GaussianBlur(TEXTURE* ptex);
	void XBlur(TEXTURE* ptex,FLOAT dispersion);
	void YBlur(TEXTURE* ptex,FLOAT dispersion);
private:
	void UpdateWeight(FLOAT dispersion);

	TEXTURE m_RT;
	CRenderTarget m_RenderTarget;	//�����_�[�^�[�Q�b�g
	CImage m_image;

	CEffect* m_pEffect;
	//���_�o�b�t�@�[
	static LPDIRECT3DVERTEXBUFFER9 m_pVB;

	float	m_weights[NUM_WEIGHTS];
};


#endif //_GAUSSIANFILTER_H_