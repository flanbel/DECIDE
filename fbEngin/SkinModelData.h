/*!
 *@brief	�X�L�����f���f�[�^
 */
#ifndef _SKINMODELDATA_H_
#define _SKINMODELDATA_H_

struct D3DXFRAME_DERIVED : public D3DXFRAME {
	D3DXMATRIXA16	CombinedTransformationMatrix;	//�����ςݍs��B
};

struct AABB	//�����s���E�{�b�N�X
{
	D3DXVECTOR3 center;		//���S�_
	D3DXVECTOR3 size;		//�T�C�Y
};

struct OBB	//�L�����E�{�b�N�X
{
	D3DXVECTOR3 center;		//�{�b�N�X�̒��S�_
	D3DXVECTOR3 rot;		//�{�b�N�X�̉�]�p�x
	D3DXVECTOR3 halfsize;	//�{�b�N�X�̊e���̔����̃T�C�Y
};

//���b�V���R���e�i���p�������g�����b�V���R���e�i
struct D3DXMESHCONTAINER_DERIVED : public D3DXMESHCONTAINER {
	//�e�N�X�`��
	LPDIRECT3DTEXTURE9* ppTextures;
	//
	LPD3DXMESH pOrigMesh;
	//
	LPD3DXATTRIBUTERANGE pAttributeTable;
	//
	DWORD NumAttributeGroups;
	//
	DWORD NumInfl;
	//
	LPD3DXBUFFER pBoneCombinationBuf;
	//�t���[���̍����ςݍs��ւ̎Q��
	D3DXMATRIX** ppBoneMatrixPtrs;
	//�{�[���̃I�t�Z�b�g�s��
	D3DXMATRIX* pBoneOffsetMatrices;
	//
	DWORD NumPaletteEntries;
	//
	bool UseSoftwareVP;
	//
	DWORD iAttributeSW;
	//AABB�T�C�Y�i�[
	AABB aabb;
	//OBB�i�[
	OBB obb;
};

//���f���̃f�[�^�������N���X
class CSkinModelData{
public:
	/*!
	 *@brief	�R���X�g���N�^�B
	 */
	CSkinModelData();
	/*!
	 *@brief	�f�X�g���N�^�B
	 */
	~CSkinModelData();
	/*!
	 * @brief	���f���f�[�^�����[�h�B
	 *@param[in]	filePath	�t�@�C���p�X�B
	 */
	void LoadModelData(const char* filePath, ID3DXAnimationController* pAnimationC = nullptr);
	/*!
	* @brief	�����[�X�B
	*/
	void Release();

	//�ŏ�(�����H)�̃t���[���擾
	LPD3DXFRAME GetFrameRoot()
	{
		return m_frameRoot;
	}

	ID3DXAnimationController* GetAnimationController()
	{
		return m_pAnimationController;
	}

	//�����Ƃ��Ď󂯎�����s���e�Ƃ���,���̍s����X�V
	//�������FD3DXMATRIX&�@���[���h�s��
	void UpdateBoneMatrix(const D3DXMATRIX& matWorld);
private:
	LPD3DXFRAME					m_frameRoot;		//�t���[�����[�g�B
	//�A�j���[�V�����R���g���[���[
	ID3DXAnimationController* m_pAnimationController;
};

#endif //_SKINMODELDATA_H_
