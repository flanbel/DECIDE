
#pragma once

#pragma comment(lib, "Xinput.lib")
#include <XInput.h>

enum Analog{
	L_TRIGGER,	//���ضް
	R_TRIGGER,	//�E�ضް
	L_STICKR,	//���X�e�B�b�N�E
	L_STICKL,	//���X�e�B�b�N��
	L_STICKU,	//���X�e�B�b�N��
	L_STICKD,	//���X�e�B�b�N��
	R_STICKR,	//�E�X�e�B�b�N�E
	R_STICKL,	//�E�X�e�B�b�N��
	R_STICKU,	//�E�X�e�B�b�N��
	R_STICKD,	//�E�X�e�B�b�N��
};

//#ifndef _XINPUT_H_
//#define _XINPUT_H_

//Xbox360�̃R���g���[���[
class CXInput
{
public:
	
	//�������Fint �v���C���[�ԍ�
	CXInput();
	void Start(int PlayerNum);
	bool IsConnected();	//�ڑ��m�F
	//�l�̍X�V
	void Update();

	//�{�^���̏u�ԓI�ȉ���
	bool isPushButton(int in);
	//�{�^���̌p���I�ȉ���
	bool IsPressButton(int in);
	//�A�i���O�X�e�B�b�N�A�g���K�[���u�ԓI�ɓ��͂���Ă��邩
	bool IsPushAnalog(Analog a);
	
	//�g���K�[��X�e�B�b�N�̒l���~�����Ƃ��ɂǂ����B
	XINPUT_GAMEPAD GetGamepad()
	{
		return m_state.Gamepad;
	}

	//���[�^�[��U��������
	//�������Fint �E���[�^�[�̐U����
	//�������Fint �����[�^�[�̐U����
	void Vibration(int Rmoter,int Lmoter);
private:
	//�ۂ߂�
	void Rounding();

	int m_ControllerNumber;		//�R���g���[���[�̃i���o�[(1P,2P...);
	XINPUT_STATE m_state;
	XINPUT_STATE m_Beforstate;	//��O�̃X�e�[�g
};

//#endif //_XINPUT_H_