
#ifndef _BUTTON_H_
#define _BUTTON_H_

#include "2DObject.h"
#include "Sprite.h"
#include "DInput.h"
#include "Text.h"

//ボタンの状態
enum BUTTON_STATE
{
	NORMAL,		//通常状態
	HIGHLIGHT,	//ボタンの上の乗っている
	PRESSED,	//押されている
	BUTTON_STATE_NUM	//状態の最大数
};

//ボタンを表示するクラス
class CButton : public C2DObject
{
public:
	CButton(string name = "");

	//初期化を行う関数(一度のみ呼ばれる)
	void Start()override;

	//更新を行う関数
	void Update()override;

	//描画を行う関数
	void Render()override;

	//押されているかどうかを返す
	BUTTON_STATE ButtonState();

	//色変更
	void StateColor(BUTTON_STATE state, D3DXVECTOR4 color)
	{
		m_StateColor[state] = color;
	}

	//文字変更
	void SetText(WCHAR* text)
	{
		m_Text.Createfont(text);
	}
private:
	//文字表示
	CText m_Text;
	//入力受け取り
	CDirectInput m_MouseInput;
	//ステータス
	BUTTON_STATE m_state;

	//各状態の色
	D3DXVECTOR4 m_StateColor[BUTTON_STATE::BUTTON_STATE_NUM];
};

#endif //_BUTTON_H_