#include "GameObject.h"

CGameObject::CGameObject(string name)
{
	//自分を登録
	m_Transform.GameObject(this);
	m_Active = true;
	m_Name = name;
	m_Delete = false;
	m_Dimension = DIMENSION::DNON;
}

void CGameObject::Active(bool act)
{
	m_Active = act;
	//子が居る
	if (m_Transform.ChildCnt() > 0)
	{
		//いったん取り出す
		map<string, CTransform*> child = m_Transform.Children();
		//イテレータ取得
		map<string, CTransform*>::iterator it = child.begin();
		//終わりまでループ
		while (it != child.end())
		{
			//子を同じ状態にする
			it->second->GameObject()->m_Active = act;
			it++;
		}
	}
}