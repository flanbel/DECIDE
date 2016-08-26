#include "ShowCollision.h"
#include "SkinModelManager.h"

CShowCollision::CShowCollision(string name) :C3DObject(name)
{
	//単位(1cm)四角形モデル
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
	//自分のフレーム取得
	D3DXFRAME_DERIVED* myFrame = (D3DXFRAME_DERIVED*)D3DXFrameFind(m_data.GetFrameRoot(), "CollisionBox");

	D3DXFRAME_DERIVED* pFrame = (D3DXFRAME_DERIVED*)pFrameBase;
	D3DXMESHCONTAINER_DERIVED* pMeshContainer = (D3DXMESHCONTAINER_DERIVED*)pFrameBase->pMeshContainer;
	//メッシュコンテナがあるなら
	if (pMeshContainer != NULL)
	{
		////合成済み行列
		//D3DXMATRIX world = pFrame->CombinedTransformationMatrix;
		////スケーリングして
		//D3DXMATRIX s;
		//D3DXVECTOR3 sca = pMeshContainer->aabb.size;
		//D3DXMatrixScaling(&s, sca.x, sca.y, sca.z);
		////自分の行列を渡す
		//myFrame->CombinedTransformationMatrix = s * world;

		//合成した行列を入れる
		myFrame->TransformationMatrix = pFrame->TransformationMatrix * world;
		//スケーリングして
		D3DXMATRIX s;
		D3DXVECTOR3 sca = pMeshContainer->aabb.size;
		D3DXMatrixScaling(&s, sca.x, sca.y, sca.z);
		//自分の行列を渡す
		myFrame->TransformationMatrix = s * myFrame->TransformationMatrix;
		//myFrame->TransformationMatrix = s * pFrame->CombinedTransformationMatrix;
		
		//描画
		Render();
	}

	//兄弟更新
	if (pFrame->pFrameSibling != NULL)
	{
		//同じ行列を渡す
		ShowFrameCollision(pFrame->pFrameSibling,world);
	}

	//子更新
	if (pFrame->pFrameFirstChild != NULL)
	{
		//合成した行列を渡す
		ShowFrameCollision(pFrame->pFrameFirstChild, pFrame->TransformationMatrix * world);
	}
}