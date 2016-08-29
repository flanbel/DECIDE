#include "TestScene.h"
#include "ObjectManager.h"

CTestScene::CTestScene()
{
}

CTestScene::~CTestScene()
{

}

HRESULT CTestScene::Start()
{

	SINSTANCE(CObjectManager)->Add(&m_button);

	m_button.Transform()->LocalPosition = D3DXVECTOR3(100.0f, 100.0f, 0.0f);

	return S_OK;
}

HRESULT CTestScene::Update()
{
	return S_OK;
}

HRESULT CTestScene::Draw()
{
	SINSTANCE(CObjectManager)->RenderObject();
	return S_OK;
}