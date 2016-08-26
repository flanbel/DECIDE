
#ifndef _STAGE_H_
#define _STAGE_H_

#include "3DObject.h"
#include "SkinModelData.h"
#include "SkinModelManager.h"

//�X�e�[�W�̊��N���X
class CStage : public C3DObject
{
public:
	CStage(string name = "") :C3DObject(name){};

	//���������s���֐�(��x�̂݌Ă΂��)
	virtual void Start()override = 0;

	//�X�V���s���֐�
	virtual void Update()override = 0;

	//�`����s���֐�
	virtual void Render()override = 0;
protected:
	//���f���f�[�^
	CSkinModelData m_ModelData;
};

#endif //_STAGE_H_