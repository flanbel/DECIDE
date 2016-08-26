#include "ShowCollision.h"
#include "SkinModelManager.h"

CShowCollision::CShowCollision(string name) :C3DObject(name)
{
	//�P��(1cm)�l�p�`���f��
	m_data = SINSTANCE(CSkinModelManager)->LoadModel("CollisionBox.X");
	m_model.SetModelData(&m_data);
	m_model.BlendColor(D3DXVECTOR4(1.0f, 0.0f, 0.0f, 0.5f));
}

void CShowCollision::Start()
{

}

void CShowCollision::Update()
{
	
}

void CShowCollision::Render()
{
	m_model.Render(m_pCamera,&CLight::NoLight);
}

void CShowCollision::ShowFrameCollision(const LPD3DXFRAME pFrameBase,const D3DXMATRIX& world)
{
	//�����̃t���[���擾
	D3DXFRAME_DERIVED* myFrame = (D3DXFRAME_DERIVED*)D3DXFrameFind(m_data.GetFrameRoot(), "CollisionBox");

	D3DXFRAME_DERIVED* pFrame = (D3DXFRAME_DERIVED*)pFrameBase;
	D3DXMESHCONTAINER_DERIVED* pMeshContainer = (D3DXMESHCONTAINER_DERIVED*)pFrameBase->pMeshContainer;
	//���b�V���R���e�i������Ȃ�
	if (pMeshContainer != NULL)
	{
		////�����ςݍs��
		//D3DXMATRIX world = pFrame->CombinedTransformationMatrix;
		////�X�P�[�����O����
		//D3DXMATRIX s;
		//D3DXVECTOR3 sca = pMeshContainer->aabb.size;
		//D3DXMatrixScaling(&s, sca.x, sca.y, sca.z);
		////�����̍s���n��
		//myFrame->CombinedTransformationMatrix = s * world;

		//���������s�������
		myFrame->TransformationMatrix = pFrame->TransformationMatrix * world;
		//�X�P�[�����O����
		D3DXMATRIX s;
		D3DXVECTOR3 sca = pMeshContainer->aabb.size;
		D3DXMatrixScaling(&s, sca.x, sca.y, sca.z);
		//�����̍s���n��
		myFrame->TransformationMatrix = s * myFrame->TransformationMatrix;
		//myFrame->TransformationMatrix = s * pFrame->CombinedTransformationMatrix;
		
		//�`��
		Render();
	}

	//�Z��X�V
	if (pFrame->pFrameSibling != NULL)
	{
		//�����s���n��
		ShowFrameCollision(pFrame->pFrameSibling,world);
	}

	//�q�X�V
	if (pFrame->pFrameFirstChild != NULL)
	{
		//���������s���n��
		ShowFrameCollision(pFrame->pFrameFirstChild, pFrame->TransformationMatrix * world);
	}
}