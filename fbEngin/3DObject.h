
#ifndef _3DOBJECT_H_
#define _3DOBJECT_H_

#include "GameObject.h"

#include "SkinModel.h"
#include "Animation.h"
#include "Camera.h"
#include "Light.h"

class C3DObject :public CGameObject
{
public:
	C3DObject(string name = "");

	//Start�֐�������ɌĂ΂��
	//�������z�֐��ł͂Ȃ��̂Ő�΃I�[�o�[���C�h���Ȃ��Ă�����
	virtual void Awake(){};

	//���������s���֐�(��x�̂݌Ă΂��)
	virtual void Start() = 0;

	//�X�V���s���֐�
	virtual void Update() = 0;

	//�X�V�̌�ɌĂяo�����֐�
	//�������z�֐��ł͂Ȃ��̂Ő�΃I�[�o�[���C�h���Ȃ��Ă�����
	virtual void LateUpdate(){};

	//�`����s���֐�
	virtual void Render() = 0;

	//���f���f�[�^�ݒ�
	void SetModelData(CSkinModelData* pD)
	{
		m_model.SetModelData(pD);
	}
	//�J�����Z�b�g
	void SetCamera(CCamera** c)
	{
		m_ppCamera = c;
	}
	//���C�g�J�����Z�b�g
	void SetLightCamera(CCamera* c)
	{
		m_pLightCamera = c;
	}
	void SetLightDepth(TEXTURE tex)
	{
		m_model.SetDepth(tex);
	}
	//�e�̍s��ݒ�
	void SetParent(D3DXMATRIX* pP)
	{
		m_model.SetParent(pP);
	}
	//�s��Q�b�g
	D3DXMATRIX* GetParent()
	{
		return m_model.GetParent();
	}
	//���f���ړ��Ɏg���g�����X�t�H�[���ݒ�(�ύX�������Ƃ�)
	void SetTransForm(CTransform* pT)
	{
		m_model.SetTransForm(pT);
	}
	//���C�g�͊O������󂯎��Ȃ������E�E�E
	/*void SetLight(CLight* l)
	{
		m_Light = l;
	}*/
protected:
	//���f���`��}��
	CSkinModel m_model;
	//�A�j���[�V�����Ǘ�
	//CAnimation m_animetion;
	//�J����
	CCamera** m_ppCamera;
	//���C�g�J����
	CCamera* m_pLightCamera;
	//
	TEXTURE m_LightDepth;
	//���C�g(�����l�͕W�����C�g)
	CLight* m_pLight;
};

#endif //_3DOBJECT_H_