#include "TestChara.h"

CTestChara::CTestChara()
{
	m_CharacterName = L"TestChara";
	m_CharaState = { 3, 3, 3, 3, 3 };
}

void CTestChara::Start()
{
	//モデル読み込み
	m_ModelData = SINSTANCE(CSkinModelManager)->LoadModel("Special.X");
	if (m_ModelData.GetAnimationController() != NULL)
	{
		//アニメーション初期化
		m_Animation.Init(m_ModelData.GetAnimationController());
		m_Animation.PlayAnimation(0, 1.0f);
	}
	//手のフレームげっちゅ
	//なかったらNULLが入るよ
	pHand = (D3DXFRAME_DERIVED*)D3DXFrameFind(m_ModelData.GetFrameRoot(), "RightLowerArm_branch");
}

void CTestChara::Update()
{
	m_Animation.Update(SINSTANCE(CTimer)->DeltaTime());
}

void CTestChara::Render()
{
	
}