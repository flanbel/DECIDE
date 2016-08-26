#include "Transform.h"
#include "GameObject.h"

CTransform::CTransform()
{
	m_GameObject = nullptr;
	m_Parent = nullptr;
	m_Children.clear();

	Position = VECTOR3_ZERO;
	LocalPosition = VECTOR3_ZERO;
	//Rotation = D3DXQUATERNION(0.0f, 0.0f, 0.0f, 1.0f);
	//LocalRotation = D3DXQUATERNION(0.0f, 0.0f, 0.0f, 1.0f);
	Rotation = VECTOR3_ZERO;
	LocalRotation = VECTOR3_ZERO;
	Scale = VECTOR3_ONE;
	LocalScale = VECTOR3_ONE;

	D3DXMatrixIdentity(&m_WorldMatrix);
}

CTransform::~CTransform()
{
	
}

CGameObject* CTransform::GameObject()
{
	return m_GameObject;
}

void CTransform::GameObject(CGameObject* object)
{
	m_GameObject = object;
}

//�e��Ԃ��֐�
//�߂�l�FCTransform* �e�̃A�h���X
CTransform* CTransform::Parent()
{
	return m_Parent;
};

//�����̃g�����X�t�H�[���������̐e�ɓo�^����
//�߂�l�Fbool �o�^�ł������ۂ�
//�������FCTransform
bool CTransform::SetParent(CTransform* parent)
{
	//�q�ɓ������O�����Ȃ�������
	auto child = parent->m_Children.find(this->m_GameObject->name());
	//�q�b�g���Ȃ������B
	if (child == parent->m_Children.end())
	{
		//�e�ɓo�^
		this->m_Parent = parent;
		//�e�̎q�Ɏ�����o�^
		parent->m_Children.insert(make_pair(this->m_GameObject->name(), this));

		return true;
	}
	//�q�b�g���Ă��܂����B
	else
	{
		//�o�^�ł��Ȃ������|��\��
		//�ꏊ
		string place;
		//�s��
		string line;
		Support::IntToString(&line, __LINE__);
		//�t�@�C����
		string file = __FILE__;
		place = "�t�@�C�����F"+ file + '\n' +"�s���F" + line + "�s"+ "�ŃG���[���������܂����B\n";
		string log = this->m_GameObject->name() + "�͓������O�̎q�����ɓo�^����Ă����̂�" + parent->m_GameObject->name() + "�ɓo�^�ł��܂���ł����B";
		log = place + log;
		MessageBox(NULL, log.c_str(), TEXT("�G���["), MB_OK);
		return false;
	}
}

//�q������������֐�
//�߂�l�FCTransform* �q�b�g�����q�̃A�h���X
//�������Fstring �q���̖��O
CTransform* CTransform::FindChild(string childname)
{
	//�q�̌���
	auto child = m_Children.find(childname);
	//�q�b�g����
	if (child != m_Children.end())
	{
		//�q��Ԃ�
		return child->second;
	}
	//�q�b�g���Ȃ�����
	else
	{
		return nullptr;
	}
};

//�q�̐���Ԃ��֐�
//�߂�l�Fint �q�̐�
int CTransform::ChildCnt()
{
	return m_Children.size();
};

//�q�������擾
map<string, CTransform*> CTransform::Children()
{
	return m_Children;
};

//���[�J������g�����X�t�H�[�����X�V
//�e����X�V���Ă����ׂ�
//�߂�l�F�Ȃ�
//�����F�Ȃ�
void CTransform::UpdateTransform()
{
	//�e������Ȃ�
	if (m_Parent) {
		//�e������B
		D3DXMATRIX mParentWorld = m_Parent->WorldMatrix();
		D3DXVECTOR3 qParentRot = m_Parent->Rotation;
		D3DXVECTOR3 pscale = m_Parent->Scale;
		//�e�̃��[���h�s�����Z���āA���[�J�����W�����[���h���W�ɕϊ�����B
		D3DXVECTOR4 pos;
		D3DXVec3Transform(&pos, &LocalPosition, &mParentWorld);
		//�|�W�V����
		Position.x = pos.x;
		Position.y = pos.y;
		Position.z = pos.z;
		//�X�P�[���l
		Scale.x = LocalScale.x * pscale.x;
		Scale.y = LocalScale.y * pscale.y;
		Scale.z = LocalScale.z * pscale.z;
		//�N�H�[�^�j�I���@������
		Rotation.x = LocalRotation.x;
		Rotation.y = LocalRotation.y;
		Rotation.z = LocalRotation.z;
		//Rotation = LocalRotation * qParentRot;
	}
	else {
		//���[�J�������̂܂�
		Position = LocalPosition;
		Scale = LocalScale;
		Rotation = LocalRotation;
	}

	UpdateWolrdMatrix();
}

//�g�����X�t�H�[�����烏�[���h�s��X�V
//�߂�l�F�Ȃ�
//�����F�Ȃ�
void CTransform::UpdateWolrdMatrix()
{
	//���[���h�s������߂�B
	D3DXMATRIX scale, pos;
	//�T�C�Y
	D3DXMatrixScaling(&scale, Scale.x, Scale.y, Scale.z);
	//��]
	D3DXMatrixRotationYawPitchRoll(&m_RotateMatrix, D3DXToRadian(Rotation.y), D3DXToRadian(Rotation.x), D3DXToRadian(Rotation.z));
	//D3DXMatrixRotationQuaternion(&rotate, &Rotation);
	//�|�W�V����
	D3DXMatrixTranslation(&pos, Position.x, Position.y, Position.z);
	m_WorldMatrix = scale * m_RotateMatrix * pos;
}

//�g�����X�t�H�[�����
void CTransform::Release()
{
	map<string, CTransform*>::iterator it = m_Children.begin();
	while (it != m_Children.end())
	{
		//�e���폜
		it->second->m_Parent = nullptr;
		it++;
	}
	m_Children.clear();
}

//////�ȉ��Z�b�^�[�E�Q�b�^�[


//�Q�b�^�[
D3DXMATRIX CTransform::WorldMatrix()
{
	return m_WorldMatrix;
}

//�Q�b�^�[
D3DXMATRIX CTransform::RotateMatrix()
{
	return m_RotateMatrix;
}