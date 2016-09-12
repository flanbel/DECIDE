

#ifndef _OBJECTMANAGER_H_
#define _OBJECTMANAGER_H_

#include "GameObject.h"
#include "2DObject.h"
#include "3DObject.h"

#include "Camera.h"
#include "GameCamera.h"

//�I�u�W�F�N�g���Ǘ�����N���X
class CObjectManager
{
public:
	CObjectManager()
	{
		m_CasheIdx = 0;
		m_ppCamera = new CCamera*();
		(*m_ppCamera) = nullptr;
	}
	//�}�l�[�W���[�ɃI�u�W�F�N�g��ǉ�����
	//�߂�l�FCGameObject* �ǉ��ɐ��������I�u�W�F�N�g�̃|�C���^
	//�������FCGameObject* �A�h���X,bool �A�N�e�B�u = false
	CGameObject* Add(CGameObject* pAdd, bool active = true);

	//�V�[���̃X�^�[�g�̌�ɌĂяo�����
	void AwakeObject();

	//AwakeObject�̌�ɌĂяo�����
	void StartObject();

	//���t���[���V�[���̍X�V������ɌĂяo�����B
	void UpdateObject();

	//���߃t���[���V�[���̍X�V������ɌĂяo�����B
	void LateUpdateObject();

	//�V�[���̕`��̌�ɌĂяo�����
	void RenderObject();

	//�}�l�[�W���[�ɓo�^����Ă���I�u�W�F�N�g�̂���
	//�c���t���O���Ȃ����̈ȊO��S�č폜����
	void ReleaseObject();

	void SetCasheIdx(short idx)
	{
		m_CasheIdx = idx;
	}

	//�I�u�W�F�N�g�����֐�
	//�߂�l�FCGameObject* �q�b�g�����I�u�W�F�N�g�̃A�h���X�A���邢��null�|�C���^
	//�������Fstring �����������I�u�W�F�N�g�̖��O,�������FDIMENSION �������w��(�C��) = DIMENSION::DNON
	CGameObject* FindObject(string name, DIMENSION d = DIMENSION::DNON);

	//�J�����Z�b�g
	void SetCamera(CCamera** c)
	{
		m_ppCamera = c;
	}

	//
	void SetLightCamera(CCamera* c)
	{
		m_pLightCamera = c;
	}

	void SetLightDepth(TEXTURE tex)
	{
		m_LightDepth = tex;
	}
	
	static CObjectManager* getInstance();
private:
	//3D�I�u�W�F�N�g���Ǘ�����z��
	vector<C3DObject*> m_3D[SCENECASHE_NUM];

	//2D�I�u�W�F�N�g���Ǘ�����z��
	vector<C2DObject*> m_2D[SCENECASHE_NUM];

	//�J�����̃|�C���^�̎Q��
	CCamera** m_ppCamera;

	//
	CCamera* m_pLightCamera;

	//
	TEXTURE m_LightDepth;

	//�L���b�V���̓Y����
	short m_CasheIdx;
	//���̂���ɂ���B
	static CObjectManager* m_pInstance;
};
#endif //_OBJECTMANAGER_H_