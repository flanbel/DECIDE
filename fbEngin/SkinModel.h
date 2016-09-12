#include "SkinModelData.h"

#ifndef _SKINMODEL_H_
#define _SKINMODEL_H_
#include "TextureManager.h"

//�`��^�C�v
enum TYPE
{
	SHADOW,		//�e�𗎂Ƃ����ǂ���
	BLOOM,		//�������ӂꂳ���邩�ǂ���
	EDGE,		//�G�b�W�������邩�ǂ���
	TOON,		//�g�D�[���V�F�[�_�������邩�ǂ���
	SPECULAR,	//�X�y�L�����[���C�g��K�p���邩�ǂ���
	FRESNEL,	//�t���l�����˂�K�p���邩�ǂ���
	TYPE_NUM	//TYPE�̑���
};

//
enum MODE
{
	STANDARD,		//�ʏ�`��
	MINIMUM,	//�Œ���̕`��
};

class CEffect;
class CTransform;
class CCamera;
class CLight;

//���f���̕`����s���N���X
class CSkinModel{
public:
	CSkinModel(CTransform* ptrans);
	~CSkinModel();

	//3D���f���̕`����Ăяo��
	//�������FCCamera* �Q�[���J����,
	//�������FCCamera* ���C�g�̃J����,
	//��O�����FCLight* ���C�g(�C��)�@= nullptr
	//��l�����FMODE �`�惂�[�h = STANDARD
	void Render(CCamera*, CCamera*, CLight* = nullptr,MODE = MODE::STANDARD);

	//���f���f�[�^�̍s��X�V
	void UpdateFrameMatrix();

	//�F�ݒ�
	void BlendColor(D3DXVECTOR4 color)
	{
		m_BlendColor = color;
	}
	//�V�F�[�_�[�w��
	void RenderType(TYPE type, bool flg)
	{
		m_RenderType[type] = flg;
	}
	//���f���f�[�^�փA�N�Z�X���邽�߂̃|�C���^�ݒ�
	void SetModelData(CSkinModelData* pD)
	{
		m_pModelDate = pD;
	}
	//���f���̐e�̍s��ݒ�
	void SetParent(D3DXMATRIX* pP)
	{
		m_Parent = pP;
	}

	D3DXMATRIX* GetParent()
	{
		return m_Parent;
	}

	//�g�����X�t�H�[���ύX
	//�r���ŕς������Ƃ��Ɏg��
	void SetTransForm(CTransform* pT)
	{
		m_pTrans = pT;
	}

	void SetDepth(TEXTURE tex)
	{
		m_pLightDepth = tex;
	}
private:
	//�G�t�F�N�g�ւ̎Q��
	CEffect* m_pEffect;
	//���f���f�[�^�փA�N�Z�X���邽�߂̃|�C���^�ێ�
	CSkinModelData* m_pModelDate;
	//�e�s��
	D3DXMATRIX* m_Parent;

	//�`��^�C�v
	bool m_RenderType[TYPE::TYPE_NUM];
	//�`�惂�[�h
	MODE m_Mode;

	//������F
	D3DXVECTOR4 m_BlendColor;

	//�ێ��p
	CTransform* m_pTrans;
	CCamera* m_pCamera;
	CCamera* m_pLightCamera;	//���C�g�̃J����
	CLight* m_pLight;

	TEXTURE m_pLightDepth;		//���C�g���猩���[�x�e�N�X�`��




	//�v���C�x�[�g�֐�

	//�q�Ƃ��Z����ꊇ�ŕ`�悷�邽�߂̍ċA�֐�
	void DrawFrame(LPD3DXFRAME pFrame);
	
	//�`�敪��
	void CSkinModel::DrawMeshContainer(
		D3DXMESHCONTAINER_DERIVED* pMeshContainerBase,
		LPD3DXFRAME pFrameBase
		);

	//�A�j���[�V�������胂�f���`��
	void RenderAnimate(D3DXMESHCONTAINER_DERIVED* pMeshContainerBase, D3DXFRAME_DERIVED* pFrame);
	//�A�j���[�V�����Ȃ����f���`��
	void RenderNonAnimate(D3DXMESHCONTAINER_DERIVED* pMeshContainerBase, D3DXFRAME_DERIVED* pFrame);

	//�A�j���[�V�������胂�f���`��
	void RenderAnimateMini(D3DXMESHCONTAINER_DERIVED* pMeshContainerBase, D3DXFRAME_DERIVED* pFrame);
	//�A�j���[�V�����Ȃ����f���`��
	void RenderNonAnimateMini(D3DXMESHCONTAINER_DERIVED* pMeshContainerBase, D3DXFRAME_DERIVED* pFrame);
};
#endif //_SKINMODEL_H_