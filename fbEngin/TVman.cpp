#include "TVman.h"

CTVman::CTVman()
{
	m_CharacterName = L"TVman";
	m_CharaState = { 99, 1, 1, 1, 1};
}

void CTVman::Start()
{
	//モデル読み込み
	m_ModelData = SINSTANCE(CSkinModelManager)->LoadModel("TVmanNEO.X");
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

void CTVman::Update()
{
	m_Animation.Update(SINSTANCE(CTimer)->DeltaTime());
}

void CTVman::Render()
{

}