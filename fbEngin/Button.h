
#ifndef _BUTTON_H_
#define _BUTTON_H_

#include "2DObject.h"
#include "Sprite.h"
#include "DInput.h"
#include "Text.h"

//�{�^���̏��
enum BUTTON_STATE
{
	NORMAL,		//�ʏ���
	HIGHLIGHT,	//�{�^���̏�̏���Ă���
	PRESSED,	//������Ă���
	BUTTON_STATE_NUM	//��Ԃ̍ő吔
};

//�{�^����\������N���X
class CButton : public C2DObject
{
public:
	CButton(string name = "");

	//���������s���֐�(��x�̂݌Ă΂��)
	void Start()override;

	//�X�V���s���֐�
	void Update()override;

	//�`����s���֐�
	void Render()override;

	//������Ă��邩�ǂ�����Ԃ�
	BUTTON_STATE ButtonState();

	//�F�ύX
	void StateColor(BUTTON_STATE state, D3DXVECTOR4 color)
	{
		m_StateColor[state] = color;
	}

	//�����ύX
	void SetText(WCHAR* text)
	{
		m_Text.Createfont(text);
	}
private:
	//�����\��
	CText m_Text;
	//���͎󂯎��
	CDirectInput m_MouseInput;
	//�X�e�[�^�X
	BUTTON_STATE m_state;

	//�e��Ԃ̐F
	D3DXVECTOR4 m_StateColor[BUTTON_STATE::BUTTON_STATE_NUM];
};

#endif //_BUTTON_H_