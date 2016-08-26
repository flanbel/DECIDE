
#ifndef _INPUT_H_
#define _INPUT_H_

//�L�[�{�[�h���͊Ǘ��N���X�ł�
class CInputManager
{
public:
	/****************************************************/
	/*UpdateKeyboardState�֐�							*/
	/*	�@�\�F�L�[�{�[�h��Ԃ��X�V����֐�				*/
	/*  �K�����t���[���ďo���Ă�������					*/
	/*	�����F�Ȃ�										*/
	/*	�߂�l�F�Ȃ�									*/
	/****************************************************/
	void UpdateKeyboardState(void)
	{
		memcpy(this->m_prevKeyboardState, this->m_curKeyboardState, sizeof(this->m_prevKeyboardState));
		GetKeyboardState(this->m_curKeyboardState);
	}

	/****************************************************/
	/*isKeyDown�֐�										*/
	/*	�@�\�F�L�[������Ԕ���֐�						*/
	/*	�@�@�@�L�[����������Ă��邩�𔻒肵�܂�		*/
	/*	�����F											*/
	/*	  key		�F���肷��L�[						*/
	/*	�߂�l�F����(true)�@������(false)				*/
	/****************************************************/
	bool isKeyDown(const int& key)
	{
		return (this->m_curKeyboardState[key] & 0x80) != 0;
	}

	/****************************************************/
	/*isPressed�֐�										*/
	/*	�@�\�F�L�[�u�ԉ�����Ԕ���֐�					*/
	/*	�@�@�@�L�[���u�ԓI�ɉ�������Ă��邩�𔻒肵�܂�*/
	/*	�����F											*/
	/*	  key		�F���肷��L�[						*/
	/*	�߂�l�F����(true)�@������(false)				*/
	/****************************************************/
	bool isPressed(const int& key)
	{
		return ((this->isKeyDown(key)) && ((this->m_prevKeyboardState[key] & 0x80) == 0));
	}
private:
	BYTE m_prevKeyboardState[256];	//���O�̃L�[�{�[�h���
	BYTE m_curKeyboardState[256];	//���݂̃L�[�{�[�h���
};

#endif // _INPUT_H_