#include "RenderTarget.h"

IDirect3DSurface9* CRenderTarget::m_pBackBuffer = nullptr;
IDirect3DSurface9* CRenderTarget::m_pBackZ = nullptr;
D3DVIEWPORT9 CRenderTarget::m_beforeViewport;

CRenderTarget::CRenderTarget()
{
	if (m_pBackBuffer == nullptr)
	{
		//ビューポート保持
		(*graphicsDevice()).GetViewport(&m_beforeViewport);
		//バックバッファ(レンダリングターゲット)保持
		(*graphicsDevice()).GetRenderTarget(0, &m_pBackBuffer);
		//深度バッファ保持
		(*graphicsDevice()).GetDepthStencilSurface(&m_pBackZ);
	}
}

//新しいレンダリングターゲット作成
void CRenderTarget::CreateRenderTarget(TEXTURE* ptex, UINT texwidth, UINT texheight, D3DCOLOR color)
{
	m_ClearColor = color;

	//テクスチャ作成
	(*graphicsDevice()).CreateTexture(
		texwidth, texheight,
		1,
		D3DUSAGE_RENDERTARGET,
		D3DFMT_A8R8G8B8,
		D3DPOOL_DEFAULT,
		&ptex->pTexture,
		NULL);

	//ビューポート設定
	//m_afterViewport = { 0, 0, texwidth, texheight, 0.0f, 1.0f };

	m_afterViewport.Width = texwidth;
	m_afterViewport.Height = texheight;
	m_afterViewport.MinZ = 0.0f;
	m_afterViewport.MaxZ = 1.0f;

	//画像サイズを画面サイズに
	ptex->texpath = "RenderTarget";
	ptex->imgInfo.Width = texwidth;
	ptex->imgInfo.Height = texheight;

	//サーフェスのインターフェース取得
	ptex->pTexture->GetSurfaceLevel(0, &m_pTexSurface);

	//深度バッファ作成
	(*graphicsDevice()).CreateDepthStencilSurface(
		texwidth, texheight,
		D3DFMT_D24X8,
		D3DMULTISAMPLE_NONE,
		0,
		TRUE,
		&m_pTexZ,
		NULL);
}

void CRenderTarget::SetRenderTarget(DWORD Index)
{
	//テクスチャをレンダリングターゲットに
	(*graphicsDevice()).SetRenderTarget(Index, m_pTexSurface);
	//テクスチャ用の深度バッファ作成
	(*graphicsDevice()).SetDepthStencilSurface(m_pTexZ);
	//ビューポートを変更に
	(*graphicsDevice()).SetViewport(&m_afterViewport);

	//レンダリングターゲット初期化
	(*graphicsDevice()).Clear(
		0,
		NULL,
		D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		m_ClearColor,
		1.0f,
		0);
}

void CRenderTarget::BeforeRenderTarget()
{
	//元に戻す
	(*graphicsDevice()).SetRenderTarget(0, m_pBackBuffer);
	(*graphicsDevice()).SetDepthStencilSurface(m_pBackZ);
	(*graphicsDevice()).SetViewport(&m_beforeViewport);
}

void CRenderTarget::RemoveRenderTarget(DWORD RenderTargetIndex)
{
	(*graphicsDevice()).SetRenderTarget(RenderTargetIndex, NULL);
}