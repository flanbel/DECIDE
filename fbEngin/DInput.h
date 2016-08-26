#pragma once

#include <dinput.h>				//DirectInputのヘッダー

//DirectInputのライブラリ
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

class CDirectInput
{
public:
	//DirectInputの初期化
	HRESULT Initialize(HINSTANCE hInstance);
	//マウス入力の初期化
	HRESULT MouseInit(HWND hwnd);
	//マウスの情報更新
	void MouseUpdate();
	//マウスの状態取得
	DIMOUSESTATE GetMouse()
	{
		return m_Mouse;
	}

	//キーボード入力初期化
	HRESULT KeyInit(HWND hwnd);
	//押下取得
	bool GetKeyDown(int key);
private:
	//DirectInputオブジェクトのポインタ
	static LPDIRECTINPUT8 m_pDIn;
	//オブジェクトの生成
	//各デバイス一つにつき一つづついる。
	static LPDIRECTINPUTDEVICE8 lpMouse;
	DIMOUSESTATE m_Mouse;
	static LPDIRECTINPUTDEVICE8 lpKey;
};