#include "RenderTarget.h"

IDirect3DSurface9* CRenderTarget::m_pBackBuffer = nullptr;
IDirect3DSurface9* CRenderTarget::m_pBackZ = nullptr;
D3DVIEWPORT9 CRenderTarget::m_beforeViewport;

CRenderTarget::CRenderTarget()
{
	if (m_pBackBuffer == nullptr)
	{
		//�r���[�|�[�g�ێ�
		(*graphicsDevice()).GetViewport(&m_beforeViewport);
		//�o�b�N�o�b�t�@(�����_�����O�^�[�Q�b�g)�ێ�
		(*graphicsDevice()).GetRenderTarget(0, &m_pBackBuffer);
		//�[�x�o�b�t�@�ێ�
		(*graphicsDevice()).GetDepthStencilSurface(&m_pBackZ);
	}
}

//�V���������_�����O�^�[�Q�b�g�쐬
void CRenderTarget::CreateRenderTarget(TEXTURE* ptex, UINT texwidth, UINT texheight, D3DCOLOR color)
{
	m_ClearColor = color;

	//�e�N�X�`���쐬
	(*graphicsDevice()).CreateTexture(
		texwidth, texheight,
		1,
		D3DUSAGE_RENDERTARGET,
		D3DFMT_A8R8G8B8,
		D3DPOOL_DEFAULT,
		&ptex->pTexture,
		NULL);

	//�r���[�|�[�g�ݒ�
	//m_afterViewport = { 0, 0, texwidth, texheight, 0.0f, 1.0f };

	m_afterViewport.Width = texwidth;
	m_afterViewport.Height = texheight;
	m_afterViewport.MinZ = 0.0f;
	m_afterViewport.MaxZ = 1.0f;

	//�摜�T�C�Y����ʃT�C�Y��
	ptex->texpath = "RenderTarget";
	ptex->imgInfo.Width = texwidth;
	ptex->imgInfo.Height = texheight;

	//�T�[�t�F�X�̃C���^�[�t�F�[�X�擾
	ptex->pTexture->GetSurfaceLevel(0, &m_pTexSurface);

	//�[�x�o�b�t�@�쐬
	(*graphicsDevice()).CreateDepthStencilSurface(
		texwidth, texheight,
		D3DFMT_D24X8,
		D3DMULTISAMPLE_NONE,
		0,
		TRUE,
		&m_pTexZ,
		NULL);
}

void CRenderTarget::SetRenderTarget(DWORD Index)
{
	//�e�N�X�`���������_�����O�^�[�Q�b�g��
	(*graphicsDevice()).SetRenderTarget(Index, m_pTexSurface);
	//�e�N�X�`���p�̐[�x�o�b�t�@�쐬
	(*graphicsDevice()).SetDepthStencilSurface(m_pTexZ);
	//�r���[�|�[�g��ύX��
	(*graphicsDevice()).SetViewport(&m_afterViewport);

	//�����_�����O�^�[�Q�b�g������
	(*graphicsDevice()).Clear(
		0,
		NULL,
		D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		m_ClearColor,
		1.0f,
		0);
}

void CRenderTarget::BeforeRenderTarget()
{
	//���ɖ߂�
	(*graphicsDevice()).SetRenderTarget(0, m_pBackBuffer);
	(*graphicsDevice()).SetDepthStencilSurface(m_pBackZ);
	(*graphicsDevice()).SetViewport(&m_beforeViewport);
}

void CRenderTarget::RemoveRenderTarget(DWORD RenderTargetIndex)
{
	(*graphicsDevice()).SetRenderTarget(RenderTargetIndex, NULL);
}