#include "SkinModel.h"
#include "EffectManager.h"
#include "Effect.h"
#include "support.h"
#include "TextureManager.h"

#include "Transform.h"
#include "Camera.h"
#include "Light.h"

extern UINT                 g_NumBoneMatricesMax;
extern D3DXMATRIXA16*       g_pBoneMatrices ;

CSkinModel::CSkinModel(CTransform* ptrans)
{
	FOR(TYPE::TYPE_NUM)
	{
		m_RenderType[i] = false;
	}
	m_BlendColor = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	//�������̍ۂɕW�����C�g�Z�b�g
	m_pLight = &CLight::Standard;
	m_Parent = nullptr;
	m_pTrans = ptrans;
}

CSkinModel::~CSkinModel()
{

}

void CSkinModel::DrawMeshContainer(
	D3DXMESHCONTAINER_DERIVED* pMeshContainer,
	LPD3DXFRAME pFrameBase
	)
{
	D3DXFRAME_DERIVED* pFrame = (D3DXFRAME_DERIVED*)pFrameBase;
	
	//�X�L�����̗L��(�{�[���̗L��)
	if (pMeshContainer->pSkinInfo != NULL)
	{
		//�{�[��������Ȃ炱����
		RenderAnimate(pMeshContainer,pFrame);
	}
	else
	{
		//�{�[���̂Ȃ����f���͂�����
		RenderNonAnimate(pMeshContainer, pFrame);
	}
}

//�ċA�֐�
void CSkinModel::DrawFrame(LPD3DXFRAME pFrame)
{
	D3DXMESHCONTAINER_DERIVED* pMeshContainer;

	pMeshContainer = (D3DXMESHCONTAINER_DERIVED*)pFrame->pMeshContainer;
	//�q�����Ă��郁�b�V���R���e�i���Ȃ��Ȃ�܂ő�����
	while (pMeshContainer != NULL)
	{
		//���b�V���`��
		DrawMeshContainer(
			pMeshContainer,
			pFrame
			);
		//���̃��b�V���R���e�i
		//��̃t���[���ɃR���e�i�͕�������H
		pMeshContainer = (D3DXMESHCONTAINER_DERIVED*)pMeshContainer->pNextMeshContainer;
	}

	//�Z�킪����Ȃ���Z���ǂݍ���
	if (pFrame->pFrameSibling != NULL)
	{
		DrawFrame(pFrame->pFrameSibling);
	}

	//�q������Ȃ�q��ǂݍ���
	if (pFrame->pFrameFirstChild != NULL)
	{
		DrawFrame(pFrame->pFrameFirstChild);
	}
}


void CSkinModel::Render(CCamera* pcamera, CCamera* plightcamera, CLight* plight)
{
	//�J�����ݒ�
	m_pCamera = pcamera;
	m_pLightCamera = plightcamera;
	if (plight != nullptr)
		m_pLight = plight;

	//���f���f�[�^������Ȃ�
	if (m_pModelDate)
	{
		UpdateFrameMatrix();
		//�ċA�֐��Ăяo��
		DrawFrame(m_pModelDate->GetFrameRoot());
	}
}

void CSkinModel::RenderAnimate(D3DXMESHCONTAINER_DERIVED* pMeshContainer, D3DXFRAME_DERIVED* pFrame)
{

	//�A�j���[�V�����L��
	//�G�t�F�N�g�ǂݍ���
	m_pEffect = SINSTANCE(CEffectManager)->LoadEffect("AnimationModel.fx");

	m_pEffect->SetTechnique("NormalRender");
	m_pEffect->Begin(0, D3DXFX_DONOTSAVESTATE);
	m_pEffect->BeginPass(0);

	//���C�g�̌�����]���B
	m_pEffect->SetVectorArray("g_diffuseLightDirection", m_pLight->GetDLight().Direction, sizeof(m_pLight->GetDLight().Direction));
	//���C�g�̃J���[��]���B
	m_pEffect->SetVectorArray("g_diffuseLightColor", m_pLight->GetDLight().Color, sizeof(m_pLight->GetDLight().Color));
	//����
	m_pEffect->SetVector("g_ambientLight", &m_pLight->GetAmbient());

	UINT iAttrib;
	//�o�b�t�@�[
	LPD3DXBONECOMBINATION pBoneComb = LPD3DXBONECOMBINATION(pMeshContainer->pBoneCombinationBuf->GetBufferPointer());
	//�e�}�e���A��
	for (iAttrib = 0; iAttrib < pMeshContainer->NumAttributeGroups; iAttrib++)
	{
		//�{�[��
		for (DWORD iPaletteEntry = 0; iPaletteEntry < pMeshContainer->NumPaletteEntries; ++iPaletteEntry)
		{
			DWORD iMatrixIndex = pBoneComb[iAttrib].BoneId[iPaletteEntry];
			if (iMatrixIndex != UINT_MAX)
			{
				//���̍ŏI�I�ȍs��v�Z
				D3DXMatrixMultiply(
					&g_pBoneMatrices[iPaletteEntry],
					//���̃I�t�Z�b�g(�ړ�)�s��
					&pMeshContainer->pBoneOffsetMatrices[iMatrixIndex],
					//�t���[���̃��[���h�s��
					pMeshContainer->ppBoneMatrixPtrs[iMatrixIndex]
					);
			}
		}

		//�������͕��ʂɃ��[���h�}�g���b�N�X��n��
		m_pEffect->SetMatrix("g_rotationMatrix", &m_pTrans->RotateMatrix());
		//m_pEffect->SetMatrix("g_worldMatrix", &pFrame->CombinedTransformationMatrix);		//���ɂ����Ă��邩�炢��Ȃ���(ppBoneMatrixPtrs)
		m_pEffect->SetMatrix("g_viewMatrix", &m_pCamera->View());
		m_pEffect->SetMatrix("g_projectionMatrix", &m_pCamera->Projection());

		//���̃��[���h�s��z��
		m_pEffect->SetMatrixArray("g_mWorldMatrixArray", g_pBoneMatrices, pMeshContainer->NumPaletteEntries);
		//���̐�]
		m_pEffect->SetFloat("g_numBone", (float)pMeshContainer->NumInfl);

		//�f�B�t���[�Y�J���[�擾
		D3DXVECTOR4* Diffuse = (D3DXVECTOR4*)&pMeshContainer->pMaterials[iAttrib].MatD3D.Diffuse;

		//�e�N�X�`�����i�[����Ă���΃Z�b�g
		if (pMeshContainer->ppTextures[iAttrib] != NULL)
		{
			// �f�B�t���[�Y�e�N�X�`���B
			m_pEffect->SetTexture("g_diffuseTexture", pMeshContainer->ppTextures[iAttrib]);
			m_pEffect->SetBool("Texflg", true);
		}
		//�e�N�X�`�����Ȃ��Ȃ�J���[�Z�b�g
		else if (Diffuse != NULL)
		{
			m_pEffect->SetVector("g_diffuseMaterial", Diffuse);
			m_pEffect->SetBool("Texflg", false);
		}

		// �{�[�����B
		m_pEffect->SetInt("CurNumBones", pMeshContainer->NumInfl - 1);

		// draw the subset with the current world matrix palette and material state
		m_pEffect->CommitChanges();
		pMeshContainer->MeshData.pMesh->DrawSubset(iAttrib);
	}
	m_pEffect->EndPass();
	m_pEffect->End();
}

//�A�j���[�V�����Ȃ��B
void CSkinModel::RenderNonAnimate(D3DXMESHCONTAINER_DERIVED* pMeshContainer, D3DXFRAME_DERIVED* pFrame)
{
	////���[���h�s����i�[
	//D3DXMATRIX Wolrd;			//�ŏI�I�ȃ��f���̍��W
	//D3DXMATRIX parent = m_pTrans->WorldMatrix();
	////�v�Z
	//D3DXMatrixMultiply(&Wolrd, &pFrame->TransformationMatrix, &parent);

	//�G�t�F�N�g�ǂݍ���
	m_pEffect = SINSTANCE(CEffectManager)->LoadEffect("3Dmodel.fx");

	//�G�b�W�`��
	if (m_RenderType[TYPE::EDGE])
	{
		//�w�ʕ`��
		(*graphicsDevice()).SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);

		//�e�N�j�b�N���Z�b�g
		m_pEffect->SetTechnique("EdgeRender");
		m_pEffect->Begin(NULL, D3DXFX_DONOTSAVESHADERSTATE);
		m_pEffect->BeginPass(0);

		//�e�s����Z�b�g�B
		//�������͌v�Z���ꂽ�}�g���b�N�X��n��
		m_pEffect->SetMatrix("g_rotationMatrix", &pFrame->CombinedTransformationMatrix);
		m_pEffect->SetMatrix("g_worldMatrix", &pFrame->CombinedTransformationMatrix);
		m_pEffect->SetMatrix("g_viewMatrix", &m_pCamera->View());
		m_pEffect->SetMatrix("g_projectionMatrix", &m_pCamera->Projection());

		//�}�e���A���̐�
		DWORD MaterialNum = pMeshContainer->NumMaterials;
		//�}�e���A��
		D3DXMATERIAL *mtrl = (D3DXMATERIAL*)(pMeshContainer->pMaterials);

		//���f���`��
		for (DWORD i = 0; i < MaterialNum; i++)
		{
			//���̊֐����Ăяo�����ƂŁA�f�[�^�̓]�����m�肷��B�`����s���O�Ɉ�񂾂��Ăяo���B
			m_pEffect->CommitChanges();
			// Draw the mesh subset
			pMeshContainer->MeshData.pMesh->DrawSubset(i);
		}

		m_pEffect->EndPass();
		m_pEffect->End();

		//�w�ʕ`������ɖ߂�
		(*graphicsDevice()).SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	}

	//���ߏ����L��
	(*graphicsDevice()).SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	//����������
	(*graphicsDevice()).SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	(*graphicsDevice()).SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	//���Z����
	/*(*graphicsDevice()).SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);
	(*graphicsDevice()).SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);*/

	//�ʏ�`��
	{
		//�e�N�j�b�N���Z�b�g
		m_pEffect->SetTechnique("NormalRender");

		//��begin��end�͕K���΂ɂ���B
		m_pEffect->Begin(NULL, D3DXFX_DONOTSAVESHADERSTATE);
		m_pEffect->BeginPass(0);

		//���C�g�̌�����]���B
		m_pEffect->SetVectorArray("g_diffuseLightDirection", m_pLight->GetDLight().Direction, sizeof(m_pLight->GetDLight().Direction));
		//���C�g�̃J���[��]���B
		m_pEffect->SetVectorArray("g_diffuseLightColor", m_pLight->GetDLight().Color, sizeof(m_pLight->GetDLight().Color));
		//����
		m_pEffect->SetVector("g_ambientLight", &m_pLight->GetAmbient());

		//�X�y�L�����[���C�g
		{
			//���_
			D3DXVECTOR4 eyepos = D3DXVECTOR4(m_pCamera->Pos(), 1.0f);
			m_pEffect->SetVector("g_eyePos", &eyepos);
			m_pEffect->SetBool("Specflg", m_RenderType[TYPE::SPECULAR]);
		}

		//�t���l������
		{
			//�J�����̉�]�s��̋t�s��쐬
			D3DXMATRIX viewMatrixRotInv;
			D3DXMatrixInverse(&viewMatrixRotInv, NULL, &m_pCamera->Rotation());
			m_pEffect->SetMatrix("g_viewMatrixRotInv", &viewMatrixRotInv);
			m_pEffect->SetBool("Fresnelflg", m_RenderType[TYPE::FRESNEL]);
		}

		//�g�D�[�������_�[�������B
		{
			TEXTURE toontex = SINSTANCE(CTextureManager)->LoadTexture("toon.png");
			m_pEffect->SetTexture("g_toonTexture", toontex.pTexture);
			CVector3 toonLight = { -1.0f, -1.0f, 1.0f };

			//���z���烂�f���ւ̕���
			//D3DXVECTOR3 dir = m_pTrans->Position() - m_pCamera->m_Pos;

			/*toonLight.x = dir.x;
		toonLight.y = dir.y;
		toonLight.z = dir.z;*/

			//���K��
			toonLight.Normalize();
			m_pEffect->SetVector("g_toonLight", &D3DXVECTOR4(toonLight.x, toonLight.y, toonLight.z, 1.0f));
			m_pEffect->SetBool("Toonflg", m_RenderType[TYPE::TOON]);
		}

		//�e�̃e�N�X�`���������Ă���
		
		if (m_pLightDepth.pTexture != nullptr)
		{
			D3DXMATRIX LVP = m_pLightCamera->View() * m_pLightCamera->Projection();
			m_pEffect->SetMatrix("g_LVP", &LVP);
			m_pEffect->SetTexture("g_LVPTex", m_pLightDepth.pTexture);
			m_pEffect->SetBool("Shadowflg", true);
		}
		else
		{
			m_pEffect->SetBool("Shadowflg", false);
		}
		

		{
			//�F�̔{��
			m_pEffect->SetVector("g_blendColor", &m_BlendColor);
		}

		//�e�s����Z�b�g�B
		m_pEffect->SetMatrix("g_rotationMatrix", &pFrame->CombinedTransformationMatrix);

		m_pEffect->SetMatrix("g_worldMatrix", &pFrame->CombinedTransformationMatrix);
		m_pEffect->SetMatrix("g_viewMatrix", &m_pCamera->View());
		m_pEffect->SetMatrix("g_projectionMatrix", &m_pCamera->Projection());

		//�}�e���A���̐�
		DWORD MaterialNum = pMeshContainer->NumMaterials;
		//�}�e���A��
		D3DXMATERIAL *mtrl = (D3DXMATERIAL*)(pMeshContainer->pMaterials);

		//���f���`��
		for (DWORD i = 0; i < MaterialNum; i++)
		{
			//�f�B�t���[�Y�J���[
			D3DXVECTOR4* Diffuse = (D3DXVECTOR4*)&mtrl[i].MatD3D.Diffuse;

			//�X�y�L�����[�J���[(����?)
			D3DXVECTOR4* Specular = (D3DXVECTOR4*)&mtrl[i].MatD3D.Specular;

			//�e�N�X�`���[
			LPDIRECT3DTEXTURE9 texture = pMeshContainer->ppTextures[i];

			//�e�N�X�`�����i�[����Ă���΃Z�b�g
			if (texture != NULL)
			{
				m_pEffect->SetTexture("g_Texture", texture);
				m_pEffect->SetBool("g_Texflg", true);
			}
			//�e�N�X�`�����Ȃ��Ȃ�J���[�Z�b�g
			else if (Diffuse != NULL)
			{
				m_pEffect->SetVector("g_diffuseMaterial", Diffuse);
				m_pEffect->SetBool("g_Texflg", false);
			}

			//���̊֐����Ăяo�����ƂŁA�f�[�^�̓]�����m�肷��B�`����s���O�Ɉ�񂾂��Ăяo���B
			m_pEffect->CommitChanges();
			// Draw the mesh subset
			pMeshContainer->MeshData.pMesh->DrawSubset(i);
		}

		m_pEffect->EndPass();
		m_pEffect->End();
	}

	//�ύX�����X�e�[�g�����ɖ߂�
	(*graphicsDevice()).SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
	(*graphicsDevice()).SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);
	(*graphicsDevice()).SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ZERO);
}

//���f���f�[�^�̍s��X�V
void CSkinModel::UpdateFrameMatrix()
{
	//���f���f�[�^������Ȃ�
	if (m_pModelDate)
	{
		//�|���郏�[���h�s��
		D3DXMATRIX wolrd;
		D3DXMatrixIdentity(&wolrd);
		if (m_Parent == nullptr)
			//�����̃��[���h�s��
			wolrd = m_pTrans->WorldMatrix();
		else
			//�e�̃��[���h�s��
			wolrd = *m_Parent;

		m_pModelDate->UpdateBoneMatrix(wolrd);	//�s����X�V�B
	}
	else
	{
		//���f���f�[�^�Ȃ��ł���
	}
}