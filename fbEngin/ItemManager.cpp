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
	//����
	if (rand() % m_probability == 1)
	{
		int idx = rand() % m_maxnum;
		//�A�C�e���X�C�b�`���烉���_���ɐ���
		CItem* AddItem = new CTestItem("Item");//m_ItemSwitch->data()[idx];
		//�A�C�e��������
		AddItem->Awake();
		AddItem->Start();
		D3DXVECTOR3 p = { (rand() % ((short)m_range.x * 2)) - m_range.x, (rand() % ((short)m_range.y * 2)) - m_range.y, (rand() % ((short)m_range.z * 2)) - m_range.z };
		AddItem->Transform()->LocalPosition = p;
		//�A�C�e�����X�g�ɒǉ�
		m_ItemList.push_back(AddItem);
		SINSTANCE(CObjectManager)->Add(AddItem);
	}

	//�A�C�e���X�V
	list<CItem*>::iterator it = m_ItemList.begin();
	while (it != m_ItemList.end())
	{
		if ((*it)->Delete())
		{
			//����ł���̂ō폜
			//�������̉���̓I�u�W�F�N�g�}�l�[�W���ōs��
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