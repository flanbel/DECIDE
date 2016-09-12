#ifndef _CHARASELECTSCENE_H_
#define _CHARASELECTSCENE_H_

#include "Scene.h"
#include "Input.h"

#include "Camera.h"
//�I�u�W�F�N�g�̃w�b�_�t�@�C�����C���N���[�h
#include "Image.h"
#include "CobwebChart.h"
#include "CharacterSelect.h"
#include "Character.h"

//�L�����N�^�[�I���V�[��
class CCharaSelectScene :public CScene
{
public:
	CCharaSelectScene();
	~CCharaSelectScene();
	HRESULT Start();
	HRESULT Update();
	HRESULT Draw();

	//�L�����N�^�[���X�g���
	//�V�[���ړ��̍ۂɌĂԂׂ�
	void DeleteCharacterList();
	//�v���C���[�Z�b�g
	void SetPlayer();

private:
	//�L�����N�^�[���X�g
	vector<CCharacter*> m_CharacterList;
	//�L�����N�^�[�I��
	CCharacterSelect* m_Select[MAX_PLAYER_NUM];

	CInputManager m_input;
	double m_timer;

	CImage* m_BackB;
	CCobwebChart* m_Chart;
};
#endif //_CHARASELECTSCENE_H_