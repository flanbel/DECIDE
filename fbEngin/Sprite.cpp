#include "Sprite.h"
#include "Transform.h"
#include "EffectManager.h"

//全てが終わった後に解放
LPDIRECT3DVERTEXBUFFER9 CSprite::m_pVB = NULL;

CSprite::CSprite()
{
	//共有板ポリ生成
	if (m_pVB == NULL)
	{
		//単位ポリゴン(すごく小さい(縦横1ピクセル))
		//後で上下反転させるのであえて左回りにつくる。
		SpriteVertex vertices[] = {
			{ 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, },//左下
			{ 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, },//右下
			{ 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, },//左上
			{ 1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f, },//右上
		};

		//頂点生成
		(*graphicsDevice()).CreateVertexBuffer(sizeof(SpriteVertex), 0, D3DFVF_SPRITEVERTEX, D3DPOOL_DEFAULT, &m_pVB, NULL);
		//頂点バッファへのアドレスを格納する。
		VOID* pVertices;
		//アドレス取得
		m_pVB->Lock(0, sizeof(vertices), (void**)&pVertices, D3DLOCK_DISCARD);
		//アドレスへ頂点定義をコピー
		memcpy(pVertices, vertices, sizeof(vertices));
		//ロック解除
		m_pVB->Unlock();
	}

	//エフェクト読み込み
	m_pEffect = SINSTANCE(CEffectManager)->LoadEffect("Sprite.fx");

	//UV初期化
	SetUV(0.0f, 0.0f, 1.0f, 1.0f);
	SetBlendColor(D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f));
	//初期値は透明な黒
	m_KillColor = D3DCOLOR_ARGB(0, 0, 0, 0);
}

void CSprite::Render(CTransform trans)
{
	D3DXMATRIX  matWorld, matSize, matScale, matRot, matTrans;

	D3DXMatrixIdentity(&matWorld);
	//画像のサイズを設定
	D3DXMatrixScaling(&matSize, (float)m_tex.imgInfo.Width, (float)m_tex.imgInfo.Height, 1.0f);
	//設定されたスケールを設定
	D3DXMatrixScaling(&matScale, trans.Scale.x, trans.Scale.y, trans.Scale.z);
	//回転
	D3DXMatrixRotationZ(&matRot, D3DXToRadian(trans.Rotation.z));
	//移動
	D3DXMatrixTranslation(&matTrans, trans.Position.x, trans.Position.y, trans.Position.z);

	//画像サイズ　*　スケール　*　回転　*　ポジション
	matWorld = matSize * matScale * matRot * matTrans;

	float h = GAME_CLIENT_HEIGHT;
	float w = GAME_CLIENT_WIDTH;

	// 射影変換行列？
	//縦横を画面のサイズでスケーリング
	//画面の中心が基準になっているのでXに-1.0f,Yに1.0fだけオフセットする。
	D3DXMATRIX Proj(
		2.0f / w, 0.0f, 0.0f, 0.0f,
		0.0f, -2.0f / h, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		-1.0f, 1.0f, 0.0f, 1.0f
		);

	D3DXMATRIX wp = matWorld * Proj;

	//if (m_tex.pTexture != nullptr)
	{

		(*graphicsDevice()).SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
		(*graphicsDevice()).SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		(*graphicsDevice()).SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

		//テクニック設定
		m_pEffect->SetTechnique("SpriteTech");

		m_pEffect->Begin(NULL, 0);
		m_pEffect->BeginPass(0);

		//行列
		m_pEffect->SetMatrix("g_mWVP", &wp);

		if (m_tex.pTexture == nullptr)
		{
			//画像がなかったとき用の救済
			LoadTexture("noimage.png");
		}

		//テクスチャ
		m_pEffect->SetTexture("g_texture", m_tex.pTexture);

		//UV設定
		m_pEffect->SetFloat("uv_left", m_uv.x);
		m_pEffect->SetFloat("uv_top", m_uv.y);
		m_pEffect->SetFloat("uv_width", m_uv.z);
		m_pEffect->SetFloat("uv_height", m_uv.w);

		//pivot設定(スケーリングや回転の基点)
		m_pEffect->SetFloat("pivotx", m_tex.pivot.x);
		m_pEffect->SetFloat("pivoty", m_tex.pivot.y);

		//色設定
		m_pEffect->SetVector("g_blendColor", (D3DXVECTOR4*)&m_BlendColor);
		//透明色設定
		m_pEffect->SetVector("g_killColor", (D3DXVECTOR4*)&m_KillColor);

		//この関数を呼び出すことで、データの転送が確定する。描画を行う前に一回だけ呼び出す。
		m_pEffect->CommitChanges();

		(*graphicsDevice()).SetStreamSource(0, m_pVB, 0, sizeof(SpriteVertex));
		//頂点情報設定
		(*graphicsDevice()).SetFVF(D3DFVF_SPRITEVERTEX);
		//D3DPT_TRIANGLESTRIPは連続した頂点で三角形を形成
		(*graphicsDevice()).DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

		m_pEffect->EndPass();
		m_pEffect->End();

		//変更したステートを元に戻す
		(*graphicsDevice()).SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
		(*graphicsDevice()).SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);
		(*graphicsDevice()).SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ZERO);
	}
}