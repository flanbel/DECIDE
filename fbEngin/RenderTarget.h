
#include "TextureManager.h"

#ifndef _RENDERTARGET_H_
#define _RENDERTARGET_H_

//�����_�����O�^�[�Q�b�g�Ǘ��N���X
class CRenderTarget
{
public:
	//�����_�[�^�[�Q�b�g��ێ�
	CRenderTarget();

	//�����_�[�^�[�Q�b�g��ύX
	//�������FDWORD �ݒ肷�郌���_�[�^�[�Q�b�g�̓Y����
	void SetRenderTarget(DWORD RenderTargetIndex);
	//�ύX���������_�[�^�[�Q�b�g���o�b�N�o�b�t�@�[�ɖ߂��B
	static void BeforeRenderTarget();

	//�����_�[�^�[�Q�b�g����O��
	//�������FDWORD�@�O�����������_�[�^�[�Q�b�g�̓Y����
	static void RemoveRenderTarget(DWORD RenderTargetIndex);

	//�V���������_�����O�^�[�Q�b�g�쐬
	//�������FTEXTURE* �����_�[�^�[�Q�b�g�ɂ������e�N�X�`��,
	//�������FUINT �e�N�X�`���̉���,
	//��O�����FUINT�@�e�N�X�`���̏c��,
	//��l�����FD3DCOLOR �����_�[�^�[�Q�b�g�̐F = �f�t�H���g�͕s�����̔��F
	void CreateRenderTarget(TEXTURE* ptex, UINT texwidth, UINT texheight, D3DCOLOR color = D3DCOLOR_RGBA(255, 255, 255, 255));
private:
	//�o�b�N�o�b�t�@��ێ�
	static IDirect3DSurface9* m_pBackBuffer;
	//�[�x�o�b�N�o�b�t�@�̕ێ�
	static IDirect3DSurface9* m_pBackZ;
	//�ێ�
	static D3DVIEWPORT9 m_beforeViewport;

	//�T�[�t�F�X
	IDirect3DSurface9* m_pTexSurface;
	//�e�N�X�`���p�̐[�x
	IDirect3DSurface9* m_pTexZ;
	//�V������
	D3DVIEWPORT9 m_afterViewport;

	//�����_�[�^�[�Q�b�g���N���A����Ƃ��̐F
	D3DCOLOR m_ClearColor;
};
#endif //_RENDERTARGET_H_