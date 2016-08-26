#ifndef _MENUSCENE_H_
#define _MENUSCENE_H_

#include "Scene.h"
//メニューシーン
class CMenuScene :public CScene
{
public:
	CMenuScene();
	~CMenuScene();
	HRESULT Start();
	HRESULT Update();
	HRESULT Draw();
private:
};
#endif //_MENUSCENE_H_