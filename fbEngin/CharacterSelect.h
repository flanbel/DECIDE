
#ifndef _CHARACTERSELECT_H_
#define _CHARACTERSELECT_H_

#include "2DObject.h"

#include "Image.h"
#include "CobwebChart.h"
#include "Character.h"
#include "ShowCharacter.h"
#include "RenderTarget.h"

#include "Input.h"

//�L�����N�^�[��I������N���X
class CCharacterSelect :public C2DObject
{
public:
	CCharacterSelect(string name = "");
	//���������s���֐�(��x�̂݌Ă΂��)
	void Start();

	//�X�V���s���֐�
	void Update();

	//�`����s���֐�
	void Render();

	//�L�����N�^�[���X�g�Z�b�g
	void SetCharaList(vector<CCharacter*> list)
	{
		m_CharacterList = list;
	}

	CCharacter* GetSelectChara()
	{
		return m_SelectChara;
	}
private:
	//���[�_�[�`���[�g
	CCobwebChart m_Chart;
	//�g
	CImage m_Frame;
	//���
	CImage m_Arraw[2];
	//���O�\��
	CText m_NameText;

	CCamera m_camera;
	//3d���f���\��
	CShowCharacter m_Show;

	//�I���ł���L�����N�^�[�̏�񂪊i�[����Ă���x�N�^�[�ւ̃|�C���^
	vector<CCharacter*> m_CharacterList;
	//���X�g�̓Y����
	short m_ListIdx;
	//�I�𒆂̃L�����N�^�[
	CCharacter* m_SelectChara;
	//
	CInputManager m_input;
	
	//�����_�[�^�[�Q�b�g
	CRenderTarget m_RenderT;
};

#endif //_CHARACTERSELECT_H_