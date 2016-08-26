#include "Robo.h"

CRobo::CRobo()
{
	m_CharacterName = L"Robo";
	m_CharaState = { 4, 3, 5, 2, 1 };
}

void CRobo::Start()
{
	//���f���ǂݍ���
	m_ModelData = SINSTANCE(CSkinModelManager)->LoadModel("Robo.X");
	if (m_ModelData.GetAnimationController() != NULL)
	{
		//�A�j���[�V����������
		m_Animation.Init(m_ModelData.GetAnimationController());
		m_Animation.PlayAnimation(0, 1.0f);
	}
	//��̃t���[����������
	//�Ȃ�������NULL�������
	pHand = (D3DXFRAME_DERIVED*)D3DXFrameFind(m_ModelData.GetFrameRoot(), "RightLowerArm_branch");
}

void CRobo::Update()
{
	m_Animation.Update(SINSTANCE(CTimer)->DeltaTime());
}

void CRobo::Render()
{

}