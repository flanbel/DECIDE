#include "Button.h"
#include "Collision.h"
#include "2DLine.h"

CButton::CButton(string name) :C2DObject(name)
{
	m_Sprite.LoadTexture("Button.png");
	m_Text.Createfont(L"Button");
	m_Text.Transform()->SetParent(&m_Transform);
	m_state = BUTTON_STATE::NORMAL;

	//そのままの色
	m_StateColor[BUTTON_STATE::NORMAL] = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	//少し薄くなる
	m_StateColor[BUTTON_STATE::HIGHLIGHT] = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 0.7f);
	//薄暗くなる
	m_StateColor[BUTTON_STATE::PRESSED] = D3DXVECTOR4(0.7f, 0.7f, 0.7f, 0.7f);
}

void CButton::Start()
{

}

void CButton::Update()
{	
	//更新
	m_Transform.UpdateTransform();
	m_Text.Update();
	
	/*m_MouseInput.MouseUpdate();
	m_MouseInput.GetMouse();*/

	//あたり判定

	D3DXVECTOR2 lefttop, size;
	size.x = (float)m_Sprite.GetTex().imgInfo.Width;
	size.y = (float)m_Sprite.GetTex().imgInfo.Height;
	//pivotが0.0→*0,
	//pivotが0.5→*0.5,
	//pivotが1.0→*1,
	lefttop.x = m_Transform.Position.x - (size.x * m_Sprite.GetTex().pivot.x);
	lefttop.y = m_Transform.Position.y - (size.y * m_Sprite.GetTex().pivot.y);
	SquareCollision sq = { lefttop, size };

	//マウスカーソル取得
	POINT mou;
	GetCursorPos(&mou);

	//マウスカーソルの位置-ウィンドウの左上の座標でマウスカーソルがウィンドウ内のどこにいるか
	D3DXVECTOR2 clientmou;
	//-4は横幅の分
	clientmou.x = mou.x - (float)WINDOW_POS.left-4;
	//-40はタイトルバーとメニューバー分
	clientmou.y = mou.y - (float)WINDOW_POS.top - 40;

	//あたり判定
	if (CCollision::PointIsHit(clientmou, sq))
	{
		m_state = BUTTON_STATE::HIGHLIGHT;
	}
	else
	{
		m_state = BUTTON_STATE::NORMAL;
	}

	//ボタンと重なっている && 左クリック
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