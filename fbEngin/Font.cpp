#include "Font.h"
#include "Sprite.h"
#include "Transform.h"

std::map<WCHAR, FONT> CFont::m_FontMap;
HDC CFont::m_hdc = nullptr;

CFont::CFont()
{
	m_FontSize = 40;
	if (m_hdc == nullptr)
	{
		//取得
		m_hdc = GetDC(NULL);
	}
}

void CFont::Start()
{

}

void CFont::Render(CTransform trans)
{
	CTransform tr = trans;
	D3DXVECTOR3 sca = trans.LocalScale;

	short len = 0;
	//文字列を中央ぞろえにするために
	//文字列のXの長さの合計算出
	for (UINT i = 0; i < m_string.size(); i++)
	{
		FONT f = m_FontMap[m_string[i]];
		len += (short)(f.gm.gmBlackBoxX * tr.Scale.x);
	}

	short sum = 0;
	//スケールをフォントサイズ
	tr.Scale = D3DXVECTOR3(sca.x / (100.0f / m_FontSize), sca.y / (100.0f / m_FontSize), sca.z);
	//文字列文ループ
	for (UINT i = 0; i < m_string.size(); i++)
	{
		FONT f = m_FontMap[m_string[i]];
		D3DXVECTOR3 p = tr.Position;
		D3DXVECTOR3 pos = tr.Position;
		//なんかわからんが/4がちょうどよかった
		pos.x -= (float)len / (2 / tr.Scale.x);
		{
			//横移動合計
			//横幅×　スケール値
			//+0.5で四捨五入
			sum += (short)((f.gm.gmBlackBoxX * tr.Scale.x) + 0.5f);
			pos.x += sum;
		}
		//ここで文字の高さをそろえる。
		pos.y -= (f.gm.gmptGlyphOrigin.y * tr.Scale.y) - (40 * tr.Scale.y);
		tr.Position = pos;
		//テクスチャ設定
		m_pSprite->SetTexture(f.tex);
		m_pSprite->Render(tr);

		tr.Position = p;
	}
}

void CFont::Createfont(WCHAR* st)
{
	//初期化
	m_string.clear();
	short s = 0;
	while (st[s] != '\0')
	{
		//文字列取得
		m_string.push_back(st[s++]);
	}
	
	// フォントの生成
	//大きめに生成して後で倍率を変える
	int fontSize = 100;
	LOGFONT lf = { fontSize, 0, 0, 0, 0, 0, 0, 0, SHIFTJIS_CHARSET, OUT_TT_ONLY_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, DEFAULT_PITCH | FF_MODERN, _T("HGS明朝E") };// _T("ＭＳ 明朝") };

	HFONT hFont = CreateFontIndirect(&lf);

	//// デバイスにフォントを持たせないとGetGlyphOutline関数はエラーとなる
	HFONT oldFont = (HFONT)SelectObject(m_hdc, hFont);

	const int gradFlag = GGO_GRAY4_BITMAP; // GGO_GRAY2_BITMAP or GGO_GRAY4_BITMAP or GGO_GRAY8_BITMAP
	int grad = 0; // 階調の最大値
	switch (gradFlag) {
	case GGO_GRAY2_BITMAP: grad = 4; break;
	case GGO_GRAY4_BITMAP: grad = 16; break;
	case GGO_GRAY8_BITMAP: grad = 64; break;
	}

	for (USHORT i = 0; i < m_string.size(); i++)
	{
		//文字を文字コードに変換
		UINT code = (UINT)m_string[i];
		//未登録の文字なら文字生成
		if (m_FontMap[code].tex.pTexture == nullptr)
		{
			TEXTMETRIC tm;
			GetTextMetrics(m_hdc, &tm);
			GLYPHMETRICS gm;
			CONST MAT2 mat = { { 0, 1 }, { 0, 0 }, { 0, 0 }, { 0, 1 } };
			DWORD size = GetGlyphOutlineW(m_hdc, code, gradFlag, &gm, 0, NULL, &mat);
			BYTE *pMono = new BYTE[size];
			GetGlyphOutlineW(m_hdc, code, gradFlag, &gm, size, pMono, &mat);

			// テクスチャ作成
			TEXTURE Tex;
			int fontWidth = (gm.gmBlackBoxX + 3) / 4 * 4;
			int fontHeight = gm.gmBlackBoxY;
			(*graphicsDevice()).CreateTexture(fontWidth, fontHeight, 1, 0, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, &Tex.pTexture, NULL);

			// テクスチャにフォントビットマップ情報を書き込み
			D3DLOCKED_RECT lockedRect;
			Tex.pTexture->LockRect(0, &lockedRect, NULL, 0);  // ロック
			DWORD *pTexBuf = (DWORD*)lockedRect.pBits;   // テクスチャメモリへのポインタ

			for (int y = 0; y < fontHeight; y++) {
				for (int x = 0; x < fontWidth; x++) {
					DWORD alpha = pMono[y * fontWidth + x] * 255 / grad;
					//テクスチャへの書き込み？
					pTexBuf[y * fontWidth + x] = (alpha << 24) | D3DCOLOR_ARGB(0, 255, 255, 255);// 0x00ffffff;
				}
			}

			Tex.pTexture->UnlockRect(0);  // アンロック
			SAFE_DELETE_ARRAY(pMono);
			//TEXTURE作成
			Tex.imgInfo.Width = fontWidth;
			Tex.imgInfo.Height = fontHeight;
			Tex.pivot = D3DXVECTOR2(1.0f, 0.0f);

			FONT font = { Tex, gm };

			//追加
			m_FontMap[code] = font;
		}
	}
}