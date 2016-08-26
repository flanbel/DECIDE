
#ifndef _CHARACTERSELECT_H_
#define _CHARACTERSELECT_H_

#include "2DObject.h"

#include "Image.h"
#include "CobwebChart.h"
#include "Character.h"
#include "ShowCharacter.h"
#include "RenderTarget.h"

#include "Input.h"

//キャラクターを選択するクラス
class CCharacterSelect :public C2DObject
{
public:
	CCharacterSelect(string name = "");
	//初期化を行う関数(一度のみ呼ばれる)
	void Start();

	//更新を行う関数
	void Update();

	//描画を行う関数
	void Render();

	//キャラクターリストセット
	void SetCharaList(vector<CCharacter*> list)
	{
		m_CharacterList = list;
	}

	CCharacter* GetSelectChara()
	{
		return m_SelectChara;
	}
private:
	//レーダーチャート
	CCobwebChart m_Chart;
	//枠
	CImage m_Frame;
	//矢印
	CImage m_Arraw[2];
	//名前表示
	CText m_NameText;

	CCamera m_camera;
	//3dモデル表示
	CShowCharacter m_Show;

	//選択できるキャラクターの情報が格納されているベクターへのポインタ
	vector<CCharacter*> m_CharacterList;
	//リストの添え字
	short m_ListIdx;
	//選択中のキャラクター
	CCharacter* m_SelectChara;
	//
	CInputManager m_input;
	
	//レンダーターゲット
	CRenderTarget m_RenderT;
};

#endif //_CHARACTERSELECT_H_