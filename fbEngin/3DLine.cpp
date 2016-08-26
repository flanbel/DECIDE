#include "3DLine.h"
#include "EffectManager.h"

LPDIRECT3DVERTEXBUFFER9 C3DLine::m_Vbuf = NULL;

C3DLine::C3DLine()
{
	if (m_Vbuf == NULL)
	{
		//単位ベクトル生成
		static LINEVERTEX LineV[] =
		{
			{ 0.0f, 0.0f, 0.0f, D3DCOLOR_ARGB(255, 255, 0, 0) },
			{ 1.0f, 0.0f, 0.0f, D3DCOLOR_ARGB(255, 255, 0, 0) },
		};

		(*graphicsDevice()).CreateVertexBuffer(sizeof(LINEVERTEX), 0, D3DFVF_LINEVERTEX, D3DPOOL_DEFAULT, &m_Vbuf, NULL);
		VOID* pVertices;
		m_Vbuf->Lock(0, sizeof(LineV), (void**)&pVertices, 0);
		memcpy(pVertices, LineV, sizeof(LineV));
		m_Vbuf->Unlock();
	}
}

void C3DLine::Start()
{
	//エフェクト読み込み
	m_pEffect = SINSTANCE(CEffectManager)->LoadEffect("3Dline.fx");
}

void C3DLine::Update()
{
	m_Transform.UpdateTransform();
}

void C3DLine::Render()
{
	m_pEffect->SetTechnique("Line");
	m_pEffect->Begin(NULL, D3DXFX_DONOTSAVESHADERSTATE);
	m_pEffect->BeginPass(0);

	////ワールド行列の転送。
	m_pEffect->SetMatrix("g_worldMatrix", &m_Transform.WorldMatrix());
	m_pEffect->SetMatrix("g_rotationMatrix", &m_Transform.WorldMatrix());
	//ビュー行列の転送。
	m_pEffect->SetMatrix("g_viewMatrix", &m_pcamera->View());
	//プロジェクション行列の転送。
	m_pEffect->SetMatrix("g_projectionMatrix", &m_pcamera->Projection());

	(*graphicsDevice()).SetStreamSource(0, m_Vbuf, 0, sizeof(LINEVERTEX));
	(*graphicsDevice()).SetFVF(D3DFVF_LINEVERTEX);
	(*graphicsDevice()).DrawPrimitive(D3DPT_LINELIST, 0, 1);

	m_pEffect->EndPass();
	m_pEffect->End();
}

void C3DLine::SetLine(D3DXVECTOR3 line[])
{
	//始点と終点定義
	D3DXVECTOR3 start = line[0], end = line[1];
	//各辺の長さ算出
	float x, y, z;
	x = sqrt(pow(end.x - start.x, 2));
	y = sqrt(pow(end.y - start.y, 2));
	z = sqrt(pow(end.z - start.z, 2));
	//ベクトルの長さの絶対値算出
	float length = fabsf(x + y + z);
	//角度算出
	D3DXVECTOR3 ang;
	//x算出
	ang.x = atan2(end.y - start.y, end.z - start.z) * 180.0f / 3.1415f;
	//y算出
	ang.y = atan2(end.z - start.z, end.x - start.x) * 180.0f / 3.1415f;
	//z算出
	ang.z = atan2(end.y - start.y, end.x - start.x) * 180.0f / 3.1415f;
	//始点セット
	m_Transform.LocalPosition = start;
	//サイズセット
	m_Transform.LocalScale = D3DXVECTOR3(length, 1.0f, 1.0f);
	//角度セット
	//なんかよくわからんけどいい感じになった
	m_Transform.LocalRotation = D3DXVECTOR3(0, ang.y, ang.z);

	//更新
	m_Transform.UpdateTransform();
}

//void C3DLine::SetCollision(BoxCollision box)
//{
//	//ボックスの幅保持
//	D3DXVECTOR3 s = box.size;
//	//ライン
//	D3DXVECTOR3 line[2];
//
//	//F 前 B 後ろ
//	//L 左 R 右
//	//U 下 T 上 
//
//	//手前左下の頂点
//	D3DXVECTOR3 FLU = box.pos - (s / 2);
//	//手前左上の頂点
//	D3DXVECTOR3 FLT = FLU;
//	FLT.y += s.y;
//	//手前右下の頂点
//	D3DXVECTOR3 FRU = FLU;
//	FRU.x += s.x;
//	//手前右上の頂点
//	D3DXVECTOR3 FRT = FRU;
//	FRU.y += s.y;
//
//	{
//		line[0] = FLU;
//		line[1] = FLT;
//		//ラインセット
//		SetLine(line);
//		Render();
//
//		line[0] = FLU;
//		line[1] = FRU;
//		//ラインセット
//		SetLine(line);
//		Render();
//
//		line[0] = FRU;
//		line[1] = FRT;
//		//ラインセット
//		SetLine(line);
//		Render();
//
//		line[0] = FLT;
//		line[1] = FRT;
//		//ラインセット
//		SetLine(line);
//		Render();
//	}
//}