
#include "TextureManager.h"

#ifndef _RENDERTARGET_H_
#define _RENDERTARGET_H_

//レンダリングターゲット管理クラス
class CRenderTarget
{
public:
	//レンダーターゲットを保持
	CRenderTarget();

	//レンダーターゲットを変更
	//第一引数：DWORD 設定するレンダーターゲットの添え字
	void SetRenderTarget(DWORD RenderTargetIndex);
	//変更したレンダーターゲットをバックバッファーに戻す。
	static void BeforeRenderTarget();

	//レンダーターゲットから外す
	//第一引数：DWORD　外したいレンダーターゲットの添え字
	static void RemoveRenderTarget(DWORD RenderTargetIndex);

	//新しいレンダリングターゲット作成
	//第一引数：TEXTURE* レンダーターゲットにしたいテクスチャ,
	//第二引数：UINT テクスチャの横幅,
	//第三引数：UINT　テクスチャの縦幅,
	//第四引数：D3DCOLOR レンダーターゲットの色 = デフォルトは不透明の白色
	void CreateRenderTarget(TEXTURE* ptex, UINT texwidth, UINT texheight, D3DCOLOR color = D3DCOLOR_RGBA(255, 255, 255, 255));
private:
	//バックバッファを保持
	static IDirect3DSurface9* m_pBackBuffer;
	//深度バックバッファの保持
	static IDirect3DSurface9* m_pBackZ;
	//保持
	static D3DVIEWPORT9 m_beforeViewport;

	//サーフェス
	IDirect3DSurface9* m_pTexSurface;
	//テクスチャ用の深度
	IDirect3DSurface9* m_pTexZ;
	//新しいの
	D3DVIEWPORT9 m_afterViewport;

	//レンダーターゲットをクリアするときの色
	D3DCOLOR m_ClearColor;
};
#endif //_RENDERTARGET_H_