#ifndef _TITLESCENE_H_
#define _TITLESCENE_H_

#include "Scene.h"

//�I�u�W�F�N�g�̃w�b�_�t�@�C�����C���N���[�h
#include "SelectIcon.h"
#include "SelectCursor.h"
#include "Image.h"

//�^�C�g���V�[��
class CTitleScene :public CScene			
{
public:
	CTitleScene();
	~CTitleScene();
	HRESULT Start();
	HRESULT Update();
	HRESULT Draw();
private:
	//�b�P��
	double m_timer;
	//�V�[���؂�ւ��t���O
	bool m_ChengS;
	CSelectIcon* m_Start;
	CSelectIcon* m_Exit;
};
#endif //_TITLESCENE_H_