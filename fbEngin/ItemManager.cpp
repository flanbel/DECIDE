#include "ItemManager.h"

#include "TestItem.h"
#include "GreatSowrd.h"
#include "ObjectManager.h"

CItemManager::CItemManager()
{

}

void CItemManager::Start(const vector<CItem*>* pitemswitch, short probability)
{
	m_ItemSwitch = (vector<CItem*>*)pitemswitch;
	m_probability = probability;
	m_maxnum = m_ItemSwitch->size();

	m_range = { 100, 1, 100 };
	srand((unsigned int)time(NULL));
}

void CItemManager::Update()
{
	//生成
	if (rand() % m_probability == 1)
	{
		int idx = rand() % m_maxnum;
		//アイテムスイッチからランダムに生成
		CItem* AddItem = new CTestItem("Item");//m_ItemSwitch->data()[idx];
		//アイテム初期化
		AddItem->Awake();
		AddItem->Start();
		D3DXVECTOR3 p = { (rand() % ((short)m_range.x * 2)) - m_range.x, (rand() % ((short)m_range.y * 2)) - m_range.y, (rand() % ((short)m_range.z * 2)) - m_range.z };
		AddItem->Transform()->LocalPosition = p;
		//アイテムリストに追加
		m_ItemList.push_back(AddItem);
		SINSTANCE(CObjectManager)->Add(AddItem);
	}

	//アイテム更新
	list<CItem*>::iterator it = m_ItemList.begin();
	while (it != m_ItemList.end())
	{
		if ((*it)->Delete())
		{
			//死んでいるので削除
			//メモリの解放はオブジェクトマネージャで行う
			it = m_ItemList.erase(it);
		}
		else
		{
			it++;
		}
	}
}

void CItemManager::Render()
{

}