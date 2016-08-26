#ifndef _TITLESCENE_H_
#define _TITLESCENE_H_

#include "Scene.h"

//オブジェクトのヘッダファイルをインクルード
#include "SelectIcon.h"
#include "SelectCursor.h"
#include "Image.h"

//タイトルシーン
class CTitleScene :public CScene			
{
public:
	CTitleScene();
	~CTitleScene();
	HRESULT Start();
	HRESULT Update();
	HRESULT Draw();
private:
	//秒単位
	double m_timer;
	//シーン切り替えフラグ
	bool m_ChengS;
	CSelectIcon* m_Start;
	CSelectIcon* m_Exit;
};
#endif //_TITLESCENE_H_