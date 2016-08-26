
#ifndef _2DLINE_H_
#define _2DLINE_H_

#include "Collision.h"

//2D���C���������N���X
class C2DLine
{
public:
	C2DLine();
	//���������֐�
	//�������Fconst D3DXVECTOR2* �n�_�ƏI�_�̏��̓������z��,�������FDWORD �z��̗v�f��,��O�����FD3DCOLOR ���̐F = �ԐF
	void DrawLine(const D3DXVECTOR2* pvec, DWORD veccnt, D3DCOLOR Color = D3DCOLOR_ARGB(255, 255, 0, 0));

	//�����蔻����󂯎���Ă��̂ӂ��Ƀ��C���������֐�
	//�������FSquareCollision �l�p�`�̂����蔻��
	void DrawCollision(SquareCollision);

	//���̑����ύX
	//�������Ffloat ���̑���
	void SetWidth(float w)
	{
		m_pLine->SetWidth(w);
	}
private:
	//�f�o�C�X?
	static LPD3DXLINE m_pLine;
};
#endif //_2DLINE_H_