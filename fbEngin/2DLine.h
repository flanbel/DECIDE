
#ifndef _2DLINE_H_
#define _2DLINE_H_

#include "Collision.h"

//2Dラインを引くクラス
class C2DLine
{
public:
	C2DLine();
	//線を引く関数
	//第一引数：const D3DXVECTOR2* 始点と終点の情報の入った配列,第二引数：DWORD 配列の要素数,第三引数：D3DCOLOR 線の色 = 赤色
	void DrawLine(const D3DXVECTOR2* pvec, DWORD veccnt, D3DCOLOR Color = D3DCOLOR_ARGB(255, 255, 0, 0));

	//あたり判定を受け取ってそのふちにラインを引く関数
	//第一引数：SquareCollision 四角形のあたり判定
	void DrawCollision(SquareCollision);

	//線の太さ変更
	//第一引数：float 線の太さ
	void SetWidth(float w)
	{
		m_pLine->SetWidth(w);
	}
private:
	//デバイス?
	static LPD3DXLINE m_pLine;
};
#endif //_2DLINE_H_