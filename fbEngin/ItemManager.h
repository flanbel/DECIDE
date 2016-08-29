
#ifndef _ITEMMANAGER_H_
#define _ITEMMANAGER_H_

#include "Item.h"

//アイテムを生成、管理
class CItemManager
{
public:
	CItemManager();

	//初期化を行う関数(一度のみ呼ばれる)
	//第一引数：short アイテム生成確率?
	void Start(CCamera** ppcamera, const vector<CItem*>* pitemswitch, short probability = 100);

	//更新を行う関数
	void Update();

	//描画を行う関数
	void Render();

	//アイテム全削除
	void clear()
	{
		list<CItem*>::iterator it = m_ItemList.begin();
		while (it != m_ItemList.end())
		{
			//メモリ解放
			SAFE_DELETE((*it));
			it = m_ItemList.erase(it);
		}
	}

	//アイテムリストの参照を返す
	list<CItem*>* ItemList()
	{
		return &m_ItemList;
	}
private:
	//カメラ参照
	CCamera** m_ppCamera;
	//フィールド上のアイテムを格納
	list<CItem*> m_ItemList;
	//アイテム生成確率
	short m_probability;
	//生成範囲
	D3DXVECTOR3 m_range;

	//アイテムスイッチへの参照
	vector<CItem*>* m_ItemSwitch;
	//アイテムの種類
	short m_maxnum;
};

#endif //_ITEMMANAGER_H_