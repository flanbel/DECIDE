#include "2DLine.h"

LPD3DXLINE C2DLine::m_pLine = nullptr;

C2DLine::C2DLine()
{
	if (m_pLine == nullptr)
	{
		//ID3DXLineのインスタンスを生成
		D3DXCreateLine((graphicsDevice()), &m_pLine);
	}
	//アンチエイリアシングを有効に(なんとなく)
	m_pLine->SetAntialias(true);
	//線の太さ
	m_pLine->SetWidth(3.0f);
}

void C2DLine::DrawCollision(SquareCollision sq)
{
	D3DXVECTOR2 L = sq.leftTop;
	D3DXVECTOR2 S = sq.size;

	D3DXVECTOR2 vec[] = 
	{
		L,									//左上
		D3DXVECTOR2(L.x + S.x,L.y),			//右上
		D3DXVECTOR2(L.x + S.x, L.y + S.y),	//右下
		D3DXVECTOR2(L.x, L.y+S.y),			//左下
		L,									//左上
	};

	DrawLine(vec, sizeof(vec) / sizeof(*vec));
}

void C2DLine::DrawLine(const D3DXVECTOR2* pvec, DWORD veccnt, D3DCOLOR Color)
{
	m_pLine->Begin();
	m_pLine->Draw(pvec,veccnt,Color);
	m_pLine->End();
}