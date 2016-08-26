#include "DInput.h"

LPDIRECTINPUT8 CDirectInput::m_pDIn = NULL;
LPDIRECTINPUTDEVICE8 CDirectInput::lpMouse = NULL;
LPDIRECTINPUTDEVICE8 CDirectInput::lpKey = NULL;

HRESULT CDirectInput::Initialize(HINSTANCE hInstance)
{
	//DirectInput�I�u�W�F�N�g�̐����B
	HRESULT ret = DirectInput8Create(hInstance, 0x0800, IID_IDirectInput8, (LPVOID*)&m_pDIn, NULL);
	if (FAILED(ret)) {
		// �쐬�Ɏ��s
		return -1;
	}
	return S_OK;
}

HRESULT CDirectInput::MouseInit(HWND hwnd)
{
	//GUID(������)�̃I�u�W�F�N�g�𐶐�
	//�}�E�X�̃I�u�W�F�N�g����
	HRESULT ret = m_pDIn->CreateDevice(GUID_SysMouse, &lpMouse, NULL);
	if (FAILED(ret))
	{
		return -1;
	}

	//�ǂ��������f�[�^�`���œ��̓f�[�^���󂯎�邩���w�肷��
	//����̓f�t�H�ł���}�E�X�̍\����(?)���g�p(�f�t�H�łȂ����͍̂\���̂������ō��K�v������)
	ret = lpMouse->SetDataFormat(&c_dfDIMouse);
	if (FAILED(ret))
	{
		return -1;
	}

	//���̃A�v���̃E�B���h�E���A�N�e�B�u�łȂ��Ƃ��͎擾���Ȃ��悤�ɐݒ�B
	ret = lpMouse->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY);
	if (FAILED(ret))
	{
		return -1;
	}

	//���͎�t�J�n
	lpMouse->Acquire();

	return S_OK;
}

void CDirectInput::MouseUpdate()
{
	//�}�E�X�p�\���́B
	ZeroMemory(&m_Mouse, sizeof(m_Mouse));
	//���݂̏�Ԃ��Q�b�g
	HRESULT ret = lpMouse->GetDeviceState(sizeof(m_Mouse), &m_Mouse);
	if (FAILED(ret)) {
		// ���s�Ȃ�ĊJ�����Ă�����x�擾
		lpMouse->Acquire();
		lpMouse->GetDeviceState(sizeof(m_Mouse), &m_Mouse);
	}
}

HRESULT CDirectInput::KeyInit(HWND hwnd)
{
	//GUID(������)�̃I�u�W�F�N�g�𐶐�
	HRESULT ret = m_pDIn->CreateDevice(GUID_SysKeyboard, &lpKey, NULL);
	if (FAILED(ret))
	{
		return -1;
	}

	//�ǂ��������f�[�^�`���œ��̓f�[�^���󂯎�邩���w�肷��
	//����̓f�t�H�ł���}�E�X�̍\����(?)���g�p(�f�t�H�łȂ����͍̂\���̂������ō��K�v������)
	ret = lpKey->SetDataFormat(&c_dfDIKeyboard);
	if (FAILED(ret))
	{
		return -1;
	}

	//���̃A�v���̃E�B���h�E���A�N�e�B�u�łȂ��Ƃ��͎擾���Ȃ��悤�ɐݒ�B
	ret = lpKey->SetCooperativeLevel(hwnd, DISCL_NONEXCLUSIVE | DISCL_BACKGROUND);
	if (FAILED(ret))
	{
		return -1;
	}

	//���͎�t�J�n
	lpKey->Acquire();

	return S_OK;
}

bool CDirectInput::GetKeyDown(int key)
{

	BYTE diks[256];
	HRESULT ret = lpKey->GetDeviceState(sizeof(diks), &diks);
	if (FAILED(ret)) {
		// ���s�Ȃ�ĊJ�����Ă�����x�擾
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