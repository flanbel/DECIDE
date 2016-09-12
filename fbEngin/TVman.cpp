#include "TVman.h"

CTVman::CTVman()
{
	m_CharacterName = L"TV";
	m_CharaState = { 99, 1, 1, 1, 1};
}

void CTVman::Start()
{
	//���f���ǂݍ���
	m_ModelData = SINSTANCE(CSkinModelManager)->LoadModel("TVman/TV_Stay.X", &m_pAnime);
	if (m_pAnime != NULL)
	{
		//�A�j���[�V����������
		m_Animation.Init(m_pAnime);
		m_Animation.PlayAnimation(3, 1.0f,1);
	}
	//��̃t���[����������
	//�Ȃ�������NULL�������
	pHand = (D3DXFRAME_DERIVED*)D3DXFrameFind(m_ModelData.GetFrameRoot(), "Item");
}

void CTVman::Update()
{
	m_Animation.Update((float)SINSTANCE(CTimer)->DeltaTime());
	switch (m_Pattern)
	{
	case STAY:
		break;
	case FIGHTING:
		break;
	case WALK:
		break;
	case RUN:
		break;
	case PUNCH:
		break;
	case KICK:
		break;
	case ITEM_BRANDISH:
		break;
	default:
		break;
	}
}

void CTVman::Render()
{

}