
#ifndef _SELECTICON_H_
#define _SELECTICON_H_

#include "2DObject.h"
#include "Sprite.h"
#include "Text.h"
#include "DInput.h"

//アイコンのパターン
enum ICONSTATE
{
	NSELECT,		//未選択
	SELECT,			//選択状態
	ICONSTATE_NUM	//数
};

//選択できるアイコン
class CSelectIcon : public C2DObject
{
public:
	CSelectIcon(string name = "");
	//初期化を行う関数(一度のみ呼ばれる)
	void Start()override;

	//更新を行う関数
	void Update()override;

	//描画を行う関数
	void Render()override;

	void Select(bool flg)
	{
		m_IsSelect = flg;
	}

	bool Select()
	{
		return m_IsSelect;
	}

	//文字変更
	void SetText(WCHAR* text)
	{
		m_Text.Createfont(text);
	}
	//文字の大きさ変更
	void SetTextSize(short s)
	{
		m_Text.SetFontSize(s);
	}
	//色変更 最大値は255
	void SetTextColor(ICONSTATE state,int r, int g, int b)
	{
		m_Color[state] = D3DXVECTOR3((float)r, (float)g, (float)b);
	}

	//呼び出されている間点滅させる
	//第一引数：float 点滅間隔(ミリ秒)
	void Flashing(double interval)
	{
		//タイマー加算
		m_FlashInterval += SINSTANCE(CTimer)->DeltaTime();
		if (m_FlashInterval > interval)
		{
			//初期化
			m_FlashInterval = 0.0;
			if (m_Flash)
			{
				m_Sprite.SetAlpha(1.0f);
				m_Text.SetAlpha(1.0f);
				m_Flash = false;
			}
			else
			{
				m_Sprite.SetAlpha(0.0f);
				m_Text.SetAlpha(0.0f);
				m_Flash = true;
			}
		}
	}

	//フェードイン・アウト
	void Fade(bool mode,short Frame)
	{
		C2DObject::Fade(mode, Frame);
		m_Text.Fade(mode, Frame);
		m_Transform.LocalPosition.y -= 0.2f;
	}
private:
	//文字表示
	CText m_Text;
	//選択されているかどうか
	bool m_IsSelect;
	//アイコンのカラー
	D3DXVECTOR3 m_Color[ICONSTATE::ICONSTATE_NUM];

	bool m_Flash;
	//発光間隔
	double m_FlashInterval;
};

#endif //_SELECTICON_H_