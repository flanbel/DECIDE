#include "SelectCursor.h"
#include "SelectIcon.h"

CSelectCursor::CSelectCursor(string name) :C2DObject(name)
{
	//m_Sprite.LoadTexture("a");
}

void CSelectCursor::Start()
{
	it = m_SelectList.begin();
	m_NowSelect = m_SelectList._Myval(it._Mynode());
}

void CSelectCursor::Update()
{
	m_input.UpdateKeyboardState();
	MoveList();
	m_Transform.UpdateTransform();
}

void CSelectCursor::Render()
{
	//m_Sprite.Render(m_Transform);
}

void CSelectCursor::MoveList()
{	
	if (m_input.isPressed(VK_UP) ||
		g_Controller[0].isPushButton(XINPUT_GAMEPAD_DPAD_UP) ||
		g_Controller[0].IsPushAnalog(Analog::L_STICKU))
	{
		//�O�̃m�[�h���Ȃ��Ȃ�
		if (it != m_SelectList.begin())
		{
			//�ړ�
			it--;
		}
		else
		{
			//�Ō�ɍs��
			it = m_SelectList.end();
			it--;
		}
		//�ړ������̂Ńt���O�폜
		m_NowSelect->Select(false);
	}

	if (m_input.isPressed(VK_DOWN)||
		g_Controller[0].isPushButton(XINPUT_GAMEPAD_DPAD_DOWN) ||
		g_Controller[0].IsPushAnalog(Analog::L_STICKD))
	{
		//���̃m�[�h���Ȃ��Ȃ�
		if (++it == m_SelectList.end())
		{
			//�ŏ��ɖ߂�
			it = m_SelectList.begin();
		}
		//�ړ������̂Ńt���O�폜
		m_NowSelect->Select(false);
	}

	//it����|�C���^���擾
	m_NowSelect = m_SelectList._Myval(it._Mynode());
	//�V���Ɍ��肵���̂Ńt���Otrue
	m_NowSelect->Select(true);

	//�A�C�R���̃|�W�V����
	/*D3DXVECTOR3 pos = m_NowSelect->Transform()->LocalPosition;
	float halfw = (float)m_NowSelect->GetTex().imgInfo.Width / 2;
	pos.x -= halfw;
	m_Transform.LocalPosition = pos;*/
}