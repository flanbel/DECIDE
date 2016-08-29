#include "MenuScene.h"
#include "ObjectManager.h"


CMenuScene::CMenuScene()
{
}

CMenuScene::~CMenuScene()
{

}

HRESULT CMenuScene::Start()
{
	return S_OK;
}

HRESULT CMenuScene::Update()
{
	return S_OK;
}

HRESULT CMenuScene::Draw()
{
	SINSTANCE(CObjectManager)->RenderObject();
	return S_OK;
}