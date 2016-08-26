#include "ItemManager.h"

#include "TestItem.h"

CItemManager::CItemManager()
{

}

void CItemManager::Start(const CCamera* pcamera, const vector<CItem*>* pitemswitch, short probability)
{
	m_pCamera = (CCamera*)pcamera;
	m_ItemSwitch = (vector<CItem*>*)pitemswitch;
	m_probability = probability;
	m_maxnum = m_ItemSwitch->size();

	m_range = { 200, 1, 200 };
	srand(time(NULL));
}

void CItemManager::Update()
{
	//����
	if (rand() % m_probability == 1)
	{
		//�A�C�e���X�C�b�`���烉���_���ɐ���
		CItem* AddItem = new CTestItem;// m_ItemSwitch->data()[rand() % m_maxnum];
		//�A�C�e��������
		AddItem->SetCamera(m_pCamera);
		AddItem->Awake();
		AddItem->Start();
		D3DXVECTOR3 p = { (rand() % ((short)m_range.x * 2)) - m_range.x, (rand() % ((short)m_range.y * 2)) - m_range.y, (rand() % ((short)m_range.z * 2)) - m_range.z };
		AddItem->Transform()->LocalPosition = p;
		//�A�C�e�����X�g�ɒǉ�
		m_ItemList.push_back(AddItem);
	}

	//�A�C�e���X�V
	list<CItem*>::iterator it = m_ItemList.begin();
	while (it != m_ItemList.end())
	{
		(*it)->Update();
		(*it)->LateUpdate();
		if ((*it)->ItemUpdata())
		{
			//����ł���̂ō폜
			SAFE_DELETE((*it));
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
	for each(CItem* item in m_ItemList)
	{
		item->Render();
	}
}