#ifndef _TESTSCENE_H_
#define _TESTSCENE_H_

#include "Scene.h"
#include "Button.h"
//���낢��e�X�g�����
class CTestScene:public CScene
{
public:
	CTestScene();
	~CTestScene();
	HRESULT Start();
	HRESULT Update();
	HRESULT Draw();
private:
	CButton m_button;
};
#endif //_TESTSCENE_H_