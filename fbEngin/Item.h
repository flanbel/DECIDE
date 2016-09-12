
#ifndef _ITEM_H_
#define _ITEM_H_

#include "3DObject.h"
#include "SkinModelData.h"
#include "SkinModelManager.h"

//�A�C�e���̊��N���X
class CItem : public C3DObject
{
public:
	CItem(string name = "") :C3DObject(name)
	{
		m_isHas = false;
		m_life = 30.0f;
	}

	//���������s���֐�(��x�̂݌Ă΂��)
	virtual void Start()override = 0;

	//�X�V���s���֐�
	virtual void Update()override = 0;

	//�X�V�̌�ɌĂяo�����֐�
	virtual void LateUpdate()override = 0;

	//�`����s���֐�
	virtual void Render()override = 0;

	//�A�C�e�����ʃA�b�v�f�[�g
	//����ł���Ȃ�true��Ԃ�
	void ItemUpdata();

	CSkinModelData GetModelData()
	{
		return m_ModelData;
	}

	//�̂Ă�
	void Throw(const CTransform& t)
	{
		m_Transform.LocalPosition = t.LocalPosition;
		//�e���O��
		m_model.SetParent(nullptr);
		//������ĂȂ�
		m_isHas = false;
	}

	void Has()
	{
		m_isHas = true;
	}
protected:
	//���f���f�[�^
	CSkinModelData m_ModelData;
	//������Ă��邩�ǂ���
	bool m_isHas;
	//����
	float m_life;
};

#endif //_ITEM_H_