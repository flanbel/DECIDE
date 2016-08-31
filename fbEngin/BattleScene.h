
#ifndef _BATTLESCENE_H_
#define _BATTLESCENE_H_

#include "Scene.h"
#include "Camera.h"
#include "ItemManager.h"
#include "Player.h"

#include "RenderTarget.h"
#include "TextureManager.h"
#include "DepthField.h"

#include "Image.h"

class CBattleScene:public CScene
{
public:
	//初期化を行う関数(一度のみ呼ばれる)
	//オブジェクトのAwakeとStartの間に呼ばれる。
	HRESULT Start();

	//更新を行う関数
	//オブジェクトのUpdateとLateUpdateの間に呼ばれる。
	HRESULT Update();

	//描画を行う関数
	//オブジェクトのRenderより後に呼ばれる
	HRESULT Draw();
private:
	CCamera** m_ppCamera;	//カメラポインタへのポインタを格納
	CCamera* m_pMainCamera;
	CCamera* m_pShadowCamera;

	TEXTURE m_Shadowtex;	//影のテクスチャ
	CRenderTarget m_ShadowBuffer;

	
	vector<CItem*> m_ItemSwitch;	//アイテムスイッチ(出現するアイテム管理)
	CItemManager m_ItemManager;

	CPlayer* m_Player;

	CRenderTarget m_RenderTarget[2];	//被写界深度用
	TEXTURE m_tex[2];
	CDepthField m_depth;

	CImage m_i;	//確認用
	
};

#endif //_BATTLESCENE_H_