
#ifndef _GAMEOBJECT_H_
#define _GAMEOBJECT_H_

#include "Transform.h"

enum DIMENSION
{
	DNON = 0,		//�w��Ȃ�
	D2 = 2,		//�񎟌��ł��邱�Ƃ�����
	D3 = 3		//�O�����ł��邱�Ƃ�����
};

//�I�u�W�F�N�g�̑c
class CGameObject
{
public:
	CGameObject(string name = "");

	virtual ~CGameObject()
	{
		m_Transform.Release();
	}
	//Start�֐�������ɌĂ΂��
	//�������z�֐��ł͂Ȃ��̂Ő�΃I�[�o�[���C�h���Ȃ��Ă�����
	virtual void Awake(){};

	//���������s���������z�֐�
	virtual void Start() = 0;

	//�X�V���s���������z�֐�
	virtual void Update() = 0;

	//�X�V�̌�ɌĂяo�����֐�
	//�������z�֐��ł͂Ȃ��̂Ő�΃I�[�o�[���C�h���Ȃ��Ă�����
	virtual void LateUpdate(){};

	//�`����s���������z�֐�
	virtual void Render() = 0;

	//�I�u�W�F�N�g�̖��O���擾����֐�
	//�߂�l�Fstring �I�u�W�F�N�g�̖��O
	string name()
	{
		return m_Name;
	}

	//�I�u�W�F�N�g�̖��O��ݒ肷��֐�
	void name(string n)
	{
		m_Name = n;
	}

	//�g�����X�t�H�[���擾
	CTransform *Transform()
	{
		return &m_Transform;
	}

	//GameObject���
	void Release()
	{
		
	}

	//�I�u�W�F�N�g�̃A�N�e�B�u�t���O��ݒ肷��@�Z�b�^�[
	void Active(bool act);

	//�A�N�e�B�u���ǂ����擾�@�Q�b�^�[
	bool Active()
	{
		return m_Active;
	}

	//�c���t���O�ݒ�@�Z�b�^�[
	void Leave(bool leave)
	{
		m_Leave = leave;
	}

	//�c���t���O�擾�@�Q�b�^�[
	bool Leave()
	{
		return m_Leave;
	}

	//�����ݒ�@�Z�b�^�[
	DIMENSION Dimension()
	{
		return m_Dimension;
	}
protected:
	bool m_Active;	//�A�N�e�B�u�łȂ��I�u�W�F�N�g�͕`����A�b�v�f�[�g������Ȃ�
	string m_Name;	//�I�u�W�F�N�g�̖��O
	CTransform m_Transform;//�g�����X�t�H�[��
	//�I�u�W�F�N�g�}�l�[�W���[�Ɏc���t���O
	bool m_Leave;
	DIMENSION m_Dimension;	//�����̎���������(2D��3D��)
};
#endif //_GAMEOBJECT_H_