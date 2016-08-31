
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
	CCamera** m_ppCamera;	//�J�����|�C���^�ւ̃|�C���^���i�[
	CCamera* m_pMainCamera;
	CCamera* m_pShadowCamera;

	TEXTURE m_Shadowtex;	//�e�̃e�N�X�`��
	CRenderTarget m_ShadowBuffer;

	
	vector<CItem*> m_ItemSwitch;	//�A�C�e���X�C�b�`(�o������A�C�e���Ǘ�)
	CItemManager m_ItemManager;

	CPlayer* m_Player;

	CRenderTarget m_RenderTarget[2];	//��ʊE�[�x�p
	TEXTURE m_tex[2];
	CDepthField m_depth;

	CImage m_i;	//�m�F�p
	
};

#endif //_BATTLESCENE_H_