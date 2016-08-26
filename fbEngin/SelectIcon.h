
#ifndef _SELECTICON_H_
#define _SELECTICON_H_

#include "2DObject.h"
#include "Sprite.h"
#include "Text.h"
#include "DInput.h"

//�A�C�R���̃p�^�[��
enum ICONSTATE
{
	NSELECT,		//���I��
	SELECT,			//�I�����
	ICONSTATE_NUM	//��
};

//�I���ł���A�C�R��
class CSelectIcon : public C2DObject
{
public:
	CSelectIcon(string name = "");
	//���������s���֐�(��x�̂݌Ă΂��)
	void Start()override;

	//�X�V���s���֐�
	void Update()override;

	//�`����s���֐�
	void Render()override;

	void Select(bool flg)
	{
		m_IsSelect = flg;
	}

	bool Select()
	{
		return m_IsSelect;
	}

	//�����ύX
	void SetText(WCHAR* text)
	{
		m_Text.Createfont(text);
	}
	//�����̑傫���ύX
	void SetTextSize(short s)
	{
		m_Text.SetFontSize(s);
	}
	//�F�ύX �ő�l��255
	void SetTextColor(ICONSTATE state,int r, int g, int b)
	{
		m_Color[state] = D3DXVECTOR3((float)r, (float)g, (float)b);
	}

	//�Ăяo����Ă���ԓ_�ł�����
	//�������Ffloat �_�ŊԊu(�~���b)
	void Flashing(double interval)
	{
		//�^�C�}�[���Z
		m_FlashInterval += SINSTANCE(CTimer)->DeltaTime();
		if (m_FlashInterval > interval)
		{
			//������
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

	//�t�F�[�h�C���E�A�E�g
	void Fade(bool mode,short Frame)
	{
		C2DObject::Fade(mode, Frame);
		m_Text.Fade(mode, Frame);
		m_Transform.LocalPosition.y -= 0.2f;
	}
private:
	//�����\��
	CText m_Text;
	//�I������Ă��邩�ǂ���
	bool m_IsSelect;
	//�A�C�R���̃J���[
	D3DXVECTOR3 m_Color[ICONSTATE::ICONSTATE_NUM];

	bool m_Flash;
	//�����Ԋu
	double m_FlashInterval;
};

#endif //_SELECTICON_H_