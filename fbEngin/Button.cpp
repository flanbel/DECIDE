#include "Button.h"
#include "Collision.h"
#include "2DLine.h"

CButton::CButton(string name) :C2DObject(name)
{
	m_Sprite.LoadTexture("Button.png");
	m_Text.Createfont(L"Button");
	m_Text.Transform()->SetParent(&m_Transform);
	m_state = BUTTON_STATE::NORMAL;

	//���̂܂܂̐F
	m_StateColor[BUTTON_STATE::NORMAL] = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	//���������Ȃ�
	m_StateColor[BUTTON_STATE::HIGHLIGHT] = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 0.7f);
	//���Â��Ȃ�
	m_StateColor[BUTTON_STATE::PRESSED] = D3DXVECTOR4(0.7f, 0.7f, 0.7f, 0.7f);
}

void CButton::Start()
{

}

void CButton::Update()
{	
	//�X�V
	m_Transform.UpdateTransform();
	m_Text.Update();
	
	/*m_MouseInput.MouseUpdate();
	m_MouseInput.GetMouse();*/

	//�����蔻��

	D3DXVECTOR2 lefttop, size;
	size.x = (float)m_Sprite.GetTex().imgInfo.Width;
	size.y = (float)m_Sprite.GetTex().imgInfo.Height;
	//pivot��0.0��*0,
	//pivot��0.5��*0.5,
	//pivot��1.0��*1,
	lefttop.x = m_Transform.Position.x - (size.x * m_Sprite.GetTex().pivot.x);
	lefttop.y = m_Transform.Position.y - (size.y * m_Sprite.GetTex().pivot.y);
	SquareCollision sq = { lefttop, size };

	//�}�E�X�J�[�\���擾
	POINT mou;
	GetCursorPos(&mou);

	//�}�E�X�J�[�\���̈ʒu-�E�B���h�E�̍���̍��W�Ń}�E�X�J�[�\�����E�B���h�E���̂ǂ��ɂ��邩
	D3DXVECTOR2 clientmou;
	//-4�͉����̕�
	clientmou.x = mou.x - (float)WINDOW_POS.left-4;
	//-40�̓^�C�g���o�[�ƃ��j���[�o�[��
	clientmou.y = mou.y - (float)WINDOW_POS.top - 40;

	//�����蔻��
	if (CCollision::PointIsHit(clientmou, sq))
	{
		m_state = BUTTON_STATE::HIGHLIGHT;
	}
	else
	{
		m_state = BUTTON_STATE::NORMAL;
	}

	//�{�^���Əd�Ȃ��Ă��� && ���N���b�N
	if (m_state == BUTTON_STATE::HIGHLIGHT && GetAsyncKeyState(VK_LBUTTON))
	{
		m_state = BUTTON_STATE::PRESSED;
	}
}

void CButton::Render()
{
	switch (m_state)
	{
	case BUTTON_STATE::NORMAL:
		m_Sprite.SetBlendColor(m_StateColor[BUTTON_STATE::NORMAL]);
		break;
	case BUTTON_STATE::HIGHLIGHT:
		m_Sprite.SetBlendColor(m_StateColor[BUTTON_STATE::HIGHLIGHT]);
		break;
	case BUTTON_STATE::PRESSED:
		m_Sprite.SetBlendColor(m_StateColor[BUTTON_STATE::PRESSED]);
		break;

	default:
		break;
	}

	m_Sprite.Render(m_Transform);
	m_Text.Render();
}

BUTTON_STATE CButton::ButtonState()
{
	return m_state;
}