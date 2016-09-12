#ifndef _CHARASELECTSCENE_H_
#define _CHARASELECTSCENE_H_

#include "Scene.h"
#include "Input.h"

#include "Camera.h"
//オブジェクトのヘッダファイルをインクルード
#include "Image.h"
#include "CobwebChart.h"
#include "CharacterSelect.h"
#include "Character.h"

//キャラクター選択シーン
class CCharaSelectScene :public CScene
{
public:
	CCharaSelectScene();
	~CCharaSelectScene();
	HRESULT Start();
	HRESULT Update();
	HRESULT Draw();

	//キャラクターリスト解放
	//シーン移動の際に呼ぶべし
	void DeleteCharacterList();
	//プレイヤーセット
	void SetPlayer();

private:
	//キャラクターリスト
	vector<CCharacter*> m_CharacterList;
	//キャラクター選択
	CCharacterSelect* m_Select[MAX_PLAYER_NUM];

	CInputManager m_input;
	double m_timer;

	CImage* m_BackB;
	CCobwebChart* m_Chart;
};
#endif //_CHARASELECTSCENE_H_