#include "2DLine.h"

LPD3DXLINE C2DLine::m_pLine = nullptr;

C2DLine::C2DLine()
{
	if (m_pLine == nullptr)
	{
		//ID3DXLine�̃C���X�^���X�𐶐�
		D3DXCreateLine((graphicsDevice()), &m_pLine);
	}
	//�A���`�G�C���A�V���O��L����(�Ȃ�ƂȂ�)
	m_pLine->SetAntialias(true);
	//���̑���
	m_pLine->SetWidth(3.0f);
}

void C2DLine::DrawCollision(SquareCollision sq)
{
	D3DXVECTOR2 L = sq.leftTop;
	D3DXVECTOR2 S = sq.size;

	D3DXVECTOR2 vec[] = 
	{
		L,									//����
		D3DXVECTOR2(L.x + S.x,L.y),			//�E��
		D3DXVECTOR2(L.x + S.x, L.y + S.y),	//�E��
		D3DXVECTOR2(L.x, L.y+S.y),			//����
		L,									//����
	};

	DrawLine(vec, sizeof(vec) / sizeof(*vec));
}

void C2DLine::DrawLine(const D3DXVECTOR2* pvec, DWORD veccnt, D3DCOLOR Color)
{
	m_pLine->Begin();
	m_pLine->Draw(pvec,veccnt,Color);
	m_pLine->End();
}