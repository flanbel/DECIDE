
#pragma once

#pragma comment(lib, "Xinput.lib")
#include <XInput.h>

enum Analog{
	L_TRIGGER,	//左ﾄﾘｶﾞｰ
	R_TRIGGER,	//右ﾄﾘｶﾞｰ
	L_STICKR,	//左スティック右
	L_STICKL,	//左スティック左
	L_STICKU,	//左スティック上
	L_STICKD,	//左スティック下
	R_STICKR,	//右スティック右
	R_STICKL,	//右スティック左
	R_STICKU,	//右スティック上
	R_STICKD,	//右スティック下
};

//#ifndef _XINPUT_H_
//#define _XINPUT_H_

//Xbox360のコントローラー
class CXInput
{
public:
	
	//第一引数：int プレイヤー番号
	CXInput();
	void Start(int PlayerNum);
	bool IsConnected();	//接続確認
	//値の更新
	void Update();

	//ボタンの瞬間的な押下
	bool isPushButton(int in);
	//ボタンの継続的な押下
	bool IsPressButton(int in);
	//アナログスティック、トリガーが瞬間的に入力されているか
	bool IsPushAnalog(Analog a);
	
	//トリガーやスティックの値が欲しいときにどうぞ。
	XINPUT_GAMEPAD GetGamepad()
	{
		return m_state.Gamepad;
	}

	//モーターを振動させる
	//第一引数：int 右モーターの振動数
	//第二引数：int 左モーターの振動数
	void Vibration(int Rmoter,int Lmoter);
private:
	//丸める
	void Rounding();

	int m_ControllerNumber;		//コントローラーのナンバー(1P,2P...);
	XINPUT_STATE m_state;
	XINPUT_STATE m_Beforstate;	//一つ前のステート
};

//#endif //_XINPUT_H_