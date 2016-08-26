#include "DInput.h"

LPDIRECTINPUT8 CDirectInput::m_pDIn = NULL;
LPDIRECTINPUTDEVICE8 CDirectInput::lpMouse = NULL;
LPDIRECTINPUTDEVICE8 CDirectInput::lpKey = NULL;

HRESULT CDirectInput::Initialize(HINSTANCE hInstance)
{
	//DirectInputオブジェクトの生成。
	HRESULT ret = DirectInput8Create(hInstance, 0x0800, IID_IDirectInput8, (LPVOID*)&m_pDIn, NULL);
	if (FAILED(ret)) {
		// 作成に失敗
		return -1;
	}
	return S_OK;
}

HRESULT CDirectInput::MouseInit(HWND hwnd)
{
	//GUID(第一引数)のオブジェクトを生成
	//マウスのオブジェクト生成
	HRESULT ret = m_pDIn->CreateDevice(GUID_SysMouse, &lpMouse, NULL);
	if (FAILED(ret))
	{
		return -1;
	}

	//どういったデータ形式で入力データを受け取るかを指定する
	//今回はデフォであるマウスの構造体(?)を使用(デフォでないものは構造体を自分で作る必要がある)
	ret = lpMouse->SetDataFormat(&c_dfDIMouse);
	if (FAILED(ret))
	{
		return -1;
	}

	//このアプリのウィンドウがアクティブでないときは取得しないように設定。
	ret = lpMouse->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY);
	if (FAILED(ret))
	{
		return -1;
	}

	//入力受付開始
	lpMouse->Acquire();

	return S_OK;
}

void CDirectInput::MouseUpdate()
{
	//マウス用構造体。
	ZeroMemory(&m_Mouse, sizeof(m_Mouse));
	//現在の状態をゲット
	HRESULT ret = lpMouse->GetDeviceState(sizeof(m_Mouse), &m_Mouse);
	if (FAILED(ret)) {
		// 失敗なら再開させてもう一度取得
		lpMouse->Acquire();
		lpMouse->GetDeviceState(sizeof(m_Mouse), &m_Mouse);
	}
}

HRESULT CDirectInput::KeyInit(HWND hwnd)
{
	//GUID(第一引数)のオブジェクトを生成
	HRESULT ret = m_pDIn->CreateDevice(GUID_SysKeyboard, &lpKey, NULL);
	if (FAILED(ret))
	{
		return -1;
	}

	//どういったデータ形式で入力データを受け取るかを指定する
	//今回はデフォであるマウスの構造体(?)を使用(デフォでないものは構造体を自分で作る必要がある)
	ret = lpKey->SetDataFormat(&c_dfDIKeyboard);
	if (FAILED(ret))
	{
		return -1;
	}

	//このアプリのウィンドウがアクティブでないときは取得しないように設定。
	ret = lpKey->SetCooperativeLevel(hwnd, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND);
	if (FAILED(ret))
	{
		return -1;
	}

	//入力受付開始
	lpKey->Acquire();

	return S_OK;
}

bool CDirectInput::GetKeyDown(int key)
{

	BYTE diks[256];
	HRESULT ret = lpKey->GetDeviceState(sizeof(diks), &diks);
	if (FAILED(ret)) {
		// 失敗なら再開させてもう一度取得
		lpKey->Acquire();
		lpKey->GetDeviceState(sizeof(diks), &diks);
	}
	if (diks[key] & 0x80)
	{
		return true;
	}
	else
	{
		return false;
	}

}