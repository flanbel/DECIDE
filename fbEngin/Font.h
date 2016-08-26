
#ifndef _FONT_H_
#define _FONT_H_

#include "TextureManager.h"
#include "Sprite.h"

typedef struct _FONT{
	TEXTURE tex;
	GLYPHMETRICS gm;
	//TCHAR fontname;
}FONT;

//文字列描画コンポーネント
class CFont
{
public:
	CFont();
	void Start();
	//描画(外部のトランスフォーム)
	//引数として受け取ったトランスフォームを基準に文字列を描画
	//第一引数：CTransform トランスフォーム
	void Render(CTransform trans);

	//文字のテクスチャ生成
	//戻り値：なし
	//第一引数：WCHAR* テクスチャを生成したい文字列(日本語に対応するためにワイド文字)
	void Createfont(WCHAR*);

	//サイズ変更
	void SetFontSize(short s)
	{
		m_FontSize = s;
	}

	//苦肉の策
	void SetSprite(CSprite* s)
	{
		m_pSprite = s;
	}

private:
	//スプライト
	CSprite* m_pSprite;

	//描画する文字列を保持する
	vector<WCHAR> m_string;

	//フォントのテクスチャ保持
	static std::map<WCHAR, FONT> m_FontMap;

	//フォントサイズ
	short m_FontSize;

	//デバイスコンテキスト
	static HDC m_hdc;
};
#endif //_FONT_H_