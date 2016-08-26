
//�O����`
class CGameObject;

//_TRANSFORM_H_��define��`����Ă��Ȃ���Ύ��s�����B
#ifndef _TRANSFORM_H_
//�����Œ�`���邱�Ƃœ��ڈȍ~�ǂݍ��܂�Ȃ��B
#define _TRANSFORM_H_

//�g�����X�t�H�[���N���X
class CTransform
{
public:
	CTransform();
	~CTransform();

	//CGameObject(����)��Ԃ�(�g����������̂��E�E�E�H)
	//�߂�l�FCGameObject* ����
	CGameObject* GameObject();

	void GameObject(CGameObject* object);

	//�e��Ԃ��֐�
	//�߂�l�FCTransform* �e�̃A�h���X
	CTransform* Parent();

	//�����̐e�ɓo�^����
	//�߂�l�Fbool �o�^�ł������ۂ�
	//�������FCTransform
	bool SetParent(CTransform* parent);

	//�q������������֐�
	//�߂�l�FCTransform* �q�b�g�����q�̃A�h���X
	//�������Fstring �q���̖��O
	CTransform* FindChild(string childname);

	//�q�̐���Ԃ��֐�
	//�߂�l�Fint �q�̐�
	int ChildCnt();

	//�q�������擾
	map<string, CTransform*> Children();

	//���[�J������g�����X�t�H�[�����X�V
	//�߂�l�F�Ȃ�
	//�����F�Ȃ�
	void UpdateTransform();

	//�g�����X�t�H�[�����烏�[���h�s��X�V
	//�߂�l�F�Ȃ�
	//�����F�Ȃ�
	void UpdateWolrdMatrix();

	//���
	void Release();

	//�Q�b�^�[
	D3DXMATRIX WorldMatrix();

	//�Q�b�^�[
	D3DXMATRIX RotateMatrix();

	//�N�H�[�^�j�I����ݒ肷��֐�
	//�������Ffloat x��],�������Ffloat y��],��O�����Ffloat z��]
	//void SetLocalRotation(float x,float y,float z)
	//{
	//	D3DXQUATERNION q = D3DXQUATERNION(0.0f, 0.0f, 0.0f, 1.0f);
	//	D3DXMATRIX rot;
	//	//��]�s�񐶐�
	//	D3DXMatrixRotationYawPitchRoll(&rot, y, x, z);
	//	//��]�s�񂩂�N�H�[�^�j�I������
	//	D3DXMatrixRotationQuaternion(&rot, &q);

	//	LocalRotation = q;
	//}

	D3DXVECTOR3					Position;			//�ŏI�|�W�V����
	D3DXVECTOR3					LocalPosition;		//���[�J���|�W�V����
	D3DXVECTOR3					Scale;				//�ŏI�X�P�[��
	D3DXVECTOR3					LocalScale;			//���[�J���X�P�[��
	D3DXVECTOR3					Rotation;			//��]
	D3DXVECTOR3					LocalRotation;		//���[�J����]
private:
	CGameObject*				m_GameObject;	//�����̃A�h���X
	CTransform*					m_Parent;		//�e�̃A�h���X
	map<string, CTransform*>	m_Children;		//�q���B�̃A�h���X���i�[����map
	
	D3DXMATRIX					m_RotateMatrix;	//��]�s��
	D3DXMATRIX					m_WorldMatrix;	//���[���h�s��
};
//#ifndef�̏I���������B
#endif //_TRANSFORM_H_