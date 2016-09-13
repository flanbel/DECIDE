
#ifndef _STAGEOBJECT_H_
#define _STAGEOBJECT_H_

#include "3DObject.h"
#include "SkinModelData.h"
#include "SkinModelManager.h"

//�X�e�[�W��̃I�u�W�F�N�g
class CStageObject : public C3DObject
{
public:
	//�t�@�C����
	CStageObject(const char *xfile, string name = "");
	~CStageObject();
	//���������s���֐�(��x�̂݌Ă΂��)
	void Start()override;

	//�X�V���s���֐�
	void Update()override;

	//�`����s���֐�
	void Render()override;
private:
	//���f���f�[�^
	CSkinModelData m_ModelData;
};



#endif //_STAGEOBJECT_H_