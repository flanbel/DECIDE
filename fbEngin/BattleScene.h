
#ifndef _BATTLESCENE_H_
#define _BATTLESCENE_H_

#include "Scene.h"
#include "Camera.h"
#include "ItemManager.h"
#include "Player.h"

#include "RenderTarget.h"
#include "TextureManager.h"
#include "Image.h"
#include "DepthField.h"

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
	CCamera m_maincamera;
	//アイテムスイッチ
	vector<CItem*> m_ItemSwitch;
	CItemManager m_ItemManager;

	CPlayer* m_Player;

	CRenderTarget m_RenderTarget[2];
	TEXTURE m_tex[2];
	CImage m_i;
	CDepthField m_depth;
	
};

#endif //_BATTLESCENE_H_