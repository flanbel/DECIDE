
#ifndef _2DOBJECT_H_
#define _2DOBJECT_H_

#include "GameObject.h"
#include "Sprite.h"

//2Dのオブジェクト
class C2DObject:public CGameObject
{
public:
	C2DObject(string name = "");
	~C2DObject();

	//初期化を行う関数(一度のみ呼ばれる)
	virtual void Start()override{};

	//更新を行う関数
	virtual void Update()override{};

	//描画を行う関数
	virtual void Render()override{};

	//スプライト系操作関数

	//画像変更
	void SetTex(TEXTURE tex)
	{
		m_Sprite.SetTexture(tex);
	}

	const TEXTURE GetTex()
	{
		return m_Sprite.GetTex();
	}

	TEXTURE* GetpTex()
	{
		return m_Sprite.GetpTex();
	}

	//画像読み込み
	void LoadTex(LPCSTR n)
	{
		m_Sprite.LoadTexture(n);
	}

	//色変更(整数：最大値は255)
	void SetColor(int r, int g, int b)
	{
		m_Sprite.SetBlendColor(r, g, b);
	}
	//α値変更
	void SetAlpha(float a)
	{
		m_Sprite.SetAlpha(a);
	}

	//フェードイン・アウトする関数
	//第一引数：bool　インかアウトか,第二引数：short 何フレームで消えるか
	void Fade(bool mode, short Fream)
	{
		//透明度加算
		m_Sprite.Fade(mode, Fream);
	}
protected:
	//スプライト
	CSprite m_Sprite;
};

#endif //_2DOBJECT_H_