
#ifndef _SPRITE_H_
#define _SPRITE_H_

#include "TextureManager.h"
#include "Effect.h"

class CTransform;
//スプライト用の頂点情報定義
#define D3DFVF_SPRITEVERTEX (D3DFVF_XYZW|D3DFVF_TEX1)

//頂点情報(スプライト用頂点)
struct SpriteVertex
{
	float x, y, z;
	float w;
	float u, v;
};

//2D描画を担当するコンポーネント
class CSprite
{
public:
	CSprite();
	//2Dを描画した際は呼んでほしい(シーンのデストラクタで)
	void ReleaseVertex()
	{
		if (m_pVB != NULL)
		{
			m_pVB->Release();
			m_pVB = NULL;
		}
	}

	//引数として受け取ったトランスフォームを基準に画像描画
	//第一引数：CTransform トランスフォーム
	void Render(CTransform trans);

	//テクスチャ変更
	void LoadTexture(LPCSTR FileName)
	{
		//テクスチャ読み込み
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

	//混ぜる色選択(小数点)
	void SetBlendColor(float r,float g,float b)
	{
		m_BlendColor.r = r;
		m_BlendColor.g = g;
		m_BlendColor.b = b;
		
	}
	//混ぜる色選択(整数)
	void SetBlendColor(int r, int g,int b)
	{
		//α保持
		float a = m_BlendColor.a;
		m_BlendColor = D3DCOLOR_XRGB(r, g, b);
		m_BlendColor.a = a;
	}
	//αセット
	void SetAlpha(float alpha)
	{
		m_BlendColor.a = alpha;
	}
	//透明度加算
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
	//テクスチャゲット
	const TEXTURE GetTex()
	{
		return m_tex;
	}
	//テクスチャのポインタゲット
	TEXTURE* GetpTex()
	{
		return &m_tex;
	}

	//フェードイン・アウトする関数
	//第一引数：bool　インかアウトか,第二引数：short 何フレームで消えるか
	void Fade(bool mode, short Fream)
	{
		//1フレーム当たりの増加量算出
		float addAlpha = 1.0f / Fream;
		//フェードアウトなら
		if (!mode)
			addAlpha *= -1;		//反転
		//透明度加算
		AddAlpha(addAlpha);
	}
protected:
	//UV
	D3DXVECTOR4 m_uv;
	//テクスチャ
	TEXTURE m_tex;
	CEffect* m_pEffect;
	//混ぜる色
	D3DXCOLOR m_BlendColor;
	
	//削除する色(透過色指定)
	D3DXCOLOR m_KillColor;

	//こいつを使いまわすのでstatic
	//頂点バッファー
	static LPDIRECT3DVERTEXBUFFER9 m_pVB;
};
#endif //_SPRITE_H_