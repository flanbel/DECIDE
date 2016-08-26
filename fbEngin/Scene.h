
#ifndef _SCENE_H_
#define _SCENE_H_

#include "EffectManager.h"
#include "Effect.h"

//�F�������_�̒��_����`
#define D3DFVF_COLORVERTEX (D3DFVF_XYZW|D3DFVF_DIFFUSE)

//���_���(�F����)
struct ColorVertex
{
	float x, y, z;			//���_���W
	float w;				//�H�H
	unsigned long color;	//���_�F
};

//�V�[���̊��N���X
class CScene
{
public:
	CScene();
	~CScene(){};

	//���������s���֐�(��x�̂݌Ă΂��)
	//�I�u�W�F�N�g��Awake��Start�̌�ɌĂ΂��B
	virtual HRESULT Start() = 0;

	//�X�V���s���֐�
	//�I�u�W�F�N�g��Update��LateUpdate�̊ԂɌĂ΂��B
	virtual HRESULT Update() = 0;

	//�`����s���֐�
	//�I�u�W�F�N�g��Render����ɌĂ΂��
	virtual HRESULT Draw() = 0;

	//�t�F�[�h������
	void InitFade();
	//�t�F�[�h�A�E�g
	void FadeOut();
	//�t�F�[�h�`��
	void DrawFade();
private:
protected:
	//���_
	ColorVertex m_vertices[4];
	//�G�t�F�N�g
	CEffect* m_pEffect;
	//�t�F�[�h�t���O
	bool m_Fade;
	
	//�t�F�[�h�I��
	bool m_endFade;
};
#endif //_SCENE_H_