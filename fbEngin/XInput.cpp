#include "XInput.h"

CXInput::CXInput()
{
	
}

void CXInput::Start(int PlayerNum)
{
	m_ControllerNumber = PlayerNum - 1;
	ZeroMemory(&m_state, sizeof(XINPUT_STATE)); // 初期化
	ZeroMemory(&m_Beforstate, sizeof(XINPUT_STATE)); // 初期化
}

bool CXInput::IsConnected()
{
	DWORD er;
	//確認用
	XINPUT_STATE s;
	er = XInputGetState(m_ControllerNumber, &s);
	if (er == ERROR_DEVICE_NOT_CONNECTED)
	{
		return false;
	}
	else if (er == ERROR_SUCCESS)
	{
		return true;
	}

	return true;
}

void CXInput::Update()
{
	m_Beforstate = m_state;
	//コントローラー番目のステート取得
	XInputGetState(m_ControllerNumber, &m_state);
	//デッドゾーンなら値を丸める
	Rounding();
}

bool CXInput::isPushButton(int gamepad)
{
	if (!(m_Beforstate.Gamepad.wButtons & gamepad) &&		//前フレームに押されていない
		(m_state.Gamepad.wButtons & gamepad))				//今押されている
	{
		return true;
	}
	return false;
}

bool CXInput::IsPressButton(int gamepad)
{
	if (m_state.Gamepad.wButtons & gamepad)				//今押されている
	{
		return true;
	}
	return false;
}

bool CXInput::IsPushAnalog(Analog a)
{
	//接続確認
	if (!IsConnected())
	{
		return false;
	}

	switch (a)
	{
	case L_TRIGGER:
		if (m_Beforstate.Gamepad.bLeftTrigger == 0 &&		//押されていない
			m_state.Gamepad.bLeftTrigger > 0)				//今押されている
			return true;
		break;
	case R_TRIGGER:
		if (m_Beforstate.Gamepad.bRightTrigger == 0 &&		//押されていない
			m_state.Gamepad.bRightTrigger > 0)				//今押されている
			return true;
		break;
	case L_STICKR:
		if (m_Beforstate.Gamepad.sThumbLX == 0 &&		//押されていない
			m_state.Gamepad.sThumbLX > 0)				//今押されている
			return true;
		break;
	case L_STICKL:
		if (m_Beforstate.Gamepad.sThumbLX == 0 &&		//押されていない
			m_state.Gamepad.sThumbLX < 0)				//今押されている
			return true;
		break;
	case L_STICKU:
		if (m_Beforstate.Gamepad.sThumbLY == 0 &&		//押されていない
			m_state.Gamepad.sThumbLY > 0)				//今押されている
			return true;
		break;
	case L_STICKD:
		if (m_Beforstate.Gamepad.sThumbLY == 0 &&		//押されていない
			m_state.Gamepad.sThumbLY < 0)				//今押されている
			return true;
		break;
	case R_STICKR:
		if (m_Beforstate.Gamepad.sThumbRX == 0 &&		//押されていない
			m_state.Gamepad.sThumbRX > 0)				//今押されている
			return true;
		break;
	case R_STICKL:
		if (m_Beforstate.Gamepad.sThumbRX == 0 &&		//押されていない
			m_state.Gamepad.sThumbRX < 0)				//今押されている
			return true;
		break;
	case R_STICKU:
		if (m_Beforstate.Gamepad.sThumbRY == 0 &&		//押されていない
			m_state.Gamepad.sThumbRY > 0)				//今押されている
			return true;
		break;
	case R_STICKD:
		if (m_Beforstate.Gamepad.sThumbRY == 0 &&		//押されていない
			m_state.Gamepad.sThumbRY < 0)				//今押されている
			return true;
		break;
	default:
		break;
	}

	return false;
};

void CXInput::Vibration(int Rmoter, int Lmoter)
{
	DWORD error;
	//振動
	XINPUT_VIBRATION vibration;
	ZeroMemory(&vibration, sizeof(XINPUT_VIBRATION));
	vibration.wRightMotorSpeed = Rmoter; // use any value between 0-65535 here
	vibration.wLeftMotorSpeed = Lmoter; // use any value between 0-65535 here
	error = XInputSetState(m_ControllerNumber, &vibration);
}

void CXInput::Rounding()
{
	/*const int LowerLimit = 100;
	const int UpperLimit = 65535;*/

	//下限
	if (-XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE < m_state.Gamepad.sThumbLY && m_state.Gamepad.sThumbLY <  XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE){ m_state.Gamepad.sThumbLY = 0; }

	if (-XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE < m_state.Gamepad.sThumbLX &&
		m_state.Gamepad.sThumbLX <  XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
	{
		m_state.Gamepad.sThumbLX = 0;
	}

	if (-XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE < m_state.Gamepad.sThumbRY && m_state.Gamepad.sThumbRY <  XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE){ m_state.Gamepad.sThumbRY = 0; }

	if (-XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE < m_state.Gamepad.sThumbRX && m_state.Gamepad.sThumbRX <  XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE){ m_state.Gamepad.sThumbRX = 0; }
}