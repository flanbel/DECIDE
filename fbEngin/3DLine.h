
#ifndef _3DLINE_H_
#define _3DLINE_H_

#include "GameObject.h"
#include "Effect.h"
#include "Camera.h"
//#include "Collision.h"

#define D3DFVF_LINEVERTEX (D3DFVF_XYZ|D3DFVF_DIFFUSE)

struct LINEVERTEX
{
	float x, y, z;
	D3DCOLOR color;
};

//三次元空間にラインを引けるよ
class C3DLine : public CGameObject
{
public:
	C3DLine();
	~C3DLine()
	{
		m_Vbuf->Release();
		m_Vbuf = NULL;
	}
	void Start();
	void Update();
	void Render();

	//ラインの情報セット
	//第一引数：D3DXVECTOR3* 始点[0]と終点[1]のposの入った配列
	void SetLine(D3DXVECTOR3 line[]);

	////あたり判定のふちを可視化する
	////第一引数：BoxCollision ボックスのあたり判定
	//void SetCollision(BoxCollision box);

	CCamera* m_pcamera;
private:
	//スタティックな頂点バッファ
	static LPDIRECT3DVERTEXBUFFER9 m_Vbuf;
	CEffect* m_pEffect;
	int m_Primnum;
};
#endif //_3DLINE_H_