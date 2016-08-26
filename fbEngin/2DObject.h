
#ifndef _2DOBJECT_H_
#define _2DOBJECT_H_

#include "GameObject.h"
#include "Sprite.h"

//2D�̃I�u�W�F�N�g
class C2DObject:public CGameObject
{
public:
	C2DObject(string name = "");
	~C2DObject();

	//���������s���֐�(��x�̂݌Ă΂��)
	virtual void Start()override{};

	//�X�V���s���֐�
	virtual void Update()override{};

	//�`����s���֐�
	virtual void Render()override{};

	//�X�v���C�g�n����֐�

	//�摜�ύX
	void SetTex(TEXTURE tex)
	{
		m_Sprite.SetTexture(tex);
	}

	const TEXTURE GetTex()
	{
		return m_Sprite.GetTex();
	}

	TEXTURE* GetpTex()
	{
		return m_Sprite.GetpTex();
	}

	//�摜�ǂݍ���
	void LoadTex(LPCSTR n)
	{
		m_Sprite.LoadTexture(n);
	}

	//�F�ύX(�����F�ő�l��255)
	void SetColor(int r, int g, int b)
	{
		m_Sprite.SetBlendColor(r, g, b);
	}
	//���l�ύX
	void SetAlpha(float a)
	{
		m_Sprite.SetAlpha(a);
	}

	//�t�F�[�h�C���E�A�E�g����֐�
	//�������Fbool�@�C�����A�E�g��,�������Fshort ���t���[���ŏ����邩
	void Fade(bool mode, short Fream)
	{
		//�����x���Z
		m_Sprite.Fade(mode, Fream);
	}
protected:
	//�X�v���C�g
	CSprite m_Sprite;
};

#endif //_2DOBJECT_H_