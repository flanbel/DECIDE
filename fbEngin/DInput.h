#pragma once

#include <dinput.h>				//DirectInput�̃w�b�_�[

//DirectInput�̃��C�u����
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

class CDirectInput
{
public:
	//DirectInput�̏�����
	HRESULT Initialize(HINSTANCE hInstance);
	//�}�E�X���͂̏�����
	HRESULT MouseInit(HWND hwnd);
	//�}�E�X�̏��X�V
	void MouseUpdate();
	//�}�E�X�̏�Ԏ擾
	DIMOUSESTATE GetMouse()
	{
		return m_Mouse;
	}

	//�L�[�{�[�h���͏�����
	HRESULT KeyInit(HWND hwnd);
	//�����擾
	bool GetKeyDown(int key);
private:
	//DirectInput�I�u�W�F�N�g�̃|�C���^
	static LPDIRECTINPUT8 m_pDIn;
	//�I�u�W�F�N�g�̐���
	//�e�f�o�C�X��ɂ���Â���B
	static LPDIRECTINPUTDEVICE8 lpMouse;
	DIMOUSESTATE m_Mouse;
	static LPDIRECTINPUTDEVICE8 lpKey;
};