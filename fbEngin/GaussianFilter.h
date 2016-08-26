

#ifndef _GAUSSIANFILTER_H_
#define _GAUSSIANFILTER_H_

#include "RenderTarget.h"
#include "TextureManager.h"
#include "EffectManager.h"
#include "Effect.h"

#include "Image.h"

//ガウスフィルタをかけるクラス
class CGaussianFilter
{
	//スプライト用の頂点情報定義
#define D3DFVF_SPRITEVERTEX (D3DFVF_XYZW|D3DFVF_TEX1)
#define NUM_WEIGHTS 8

	//頂点情報(スプライト用頂点)
	struct SpriteVertex
	{
		float x, y, z;
		float w;
		float u, v;
	};

public:
	CGaussianFilter();
	//受け取ったテクスチャにぼかしをかける。
	TEXTURE GaussianBlur(TEXTURE* ptex);
	void XBlur(TEXTURE* ptex,FLOAT dispersion);
	void YBlur(TEXTURE* ptex,FLOAT dispersion);
private:
	void UpdateWeight(FLOAT dispersion);

	TEXTURE m_RT;
	CRenderTarget m_RenderTarget;	//レンダーターゲット
	CImage m_image;

	CEffect* m_pEffect;
	//頂点バッファー
	static LPDIRECT3DVERTEXBUFFER9 m_pVB;

	float	m_weights[NUM_WEIGHTS];
};


#endif //_GAUSSIANFILTER_H_