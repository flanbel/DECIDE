
#ifndef _SELECTCURSOR_H_
#define _SELECTCURSOR_H_

#include "2DObject.h"
#include "Sprite.h"
#include "Input.h"

class CSelectIcon;

//SelectIcon用のカーソル
class CSelectCursor:public C2DObject
{
public:
	CSelectCursor(string name = "");
	//初期化を行う関数(一度のみ呼ばれる)
	void Start()override;

	//更新を行う関数
	void Update()override;

	//描画を行う関数
	void Render()override;
	
	//リスト追加
	void AddList(CSelectIcon* icon)
	{
		m_SelectList.push_back(icon);
	}
	//リスト上のアイコンの場所に移動
	void MoveList();
private:
	//リスト
	list<CSelectIcon*> m_SelectList;
	//参照
	list<CSelectIcon*>::iterator it;
	//入力
	CInputManager m_input;
	//現在選択されているアイコン
	CSelectIcon* m_NowSelect;
};

#endif //_SELECTCURSOR_H_