
#ifndef _BATTLESCENE_H_
#define _BATTLESCENE_H_

#include "Scene.h"
#include "Camera.h"
#include "ItemManager.h"
#include "Player.h"

#include "RenderTarget.h"
#include "TextureManager.h"
#include "DepthField.h"

#include "Image.h"

class CBattleScene:public CScene
{
public:
	//���������s���֐�(��x�̂݌Ă΂��)
	//�I�u�W�F�N�g��Awake��Start�̊ԂɌĂ΂��B
	HRESULT Start();

	//�X�V���s���֐�
	//�I�u�W�F�N�g��Update��LateUpdate�̊ԂɌĂ΂��B
	HRESULT Update();

	//�`����s���֐�
	//�I�u�W�F�N�g��Render����ɌĂ΂��
	HRESULT Draw();
private:
	CCamera** m_pCamera;
	CCamera* m_pMainCamera;
	CCamera* m_pShadowCamera;

	TEXTURE m_Shadowtex;
	CRenderTarget m_ShadowBuffer;

	//�A�C�e���X�C�b�`(�o������A�C�e���Ǘ�)
	vector<CItem*> m_ItemSwitch;
	CItemManager m_ItemManager;

	CPlayer* m_Player;

	CRenderTarget m_RenderTarget[2];
	TEXTURE m_tex[2];
	CDepthField m_depth;

	CImage m_i;
	
};

#endif //_BATTLESCENE_H_