#include "SelectCursor.h"
#include "SelectIcon.h"

CSelectCursor::CSelectCursor(string name) :C2DObject(name)
{
	//m_Sprite.LoadTexture("a");
}

void CSelectCursor::Start()
{
	it = m_SelectList.begin();
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
	if (m_input.isPressed(VK_UP))
	{
		//前のノードがないなら
		if (it != m_SelectList.begin())
		{
			//移動
			it--;
		}
		else
		{
			//最後に行く
			it = m_SelectList.end();
			it--;
		}
		//移動したのでフラグ削除
		m_NowSelect->Select(false);
	}

	if (m_input.isPressed(VK_DOWN))
	{
		//次のノードがないなら
		if (++it == m_SelectList.end())
		{
			//最初に戻る
			it = m_SelectList.begin();
		}
		//移動したのでフラグ削除
		m_NowSelect->Select(false);
	}

	m_NowSelect = m_SelectList._Myval(it._Mynode());
	//新たに決定したのでフラグtrue
	m_NowSelect->Select(true);

	//アイコンのポジション
	/*D3DXVECTOR3 pos = m_NowSelect->Transform()->LocalPosition;
	float halfw = (float)m_NowSelect->GetTex().imgInfo.Width / 2;
	pos.x -= halfw;
	m_Transform.LocalPosition = pos;*/
}