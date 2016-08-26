

#ifndef _TEXTURE_H_
#define _TEXTURE_H_

typedef struct _TEXTURE
{
	string texpath;					//�e�N�X�`���ւ̃p�X
	LPDIRECT3DTEXTURE9 pTexture;	//�e�N�X�`���ւ̃|�C���^
	D3DXIMAGE_INFO imgInfo;			//�e�N�X�`�����
	D3DXVECTOR2 pivot;				//��_

	//�R���X�g���N�^
	_TEXTURE::_TEXTURE()
	{
		pTexture = nullptr;
		pivot = D3DXVECTOR2(0.5f, 0.5f);
	}

	//�e�N�X�`���ւ̃|�C���^�������[�X����
	void _TEXTURE::Release()
	{
		SAFE_DELETE(pTexture);
	}

}TEXTURE;	//�e�N�X�`���֌W�̏�񂪓����Ă���\����

//���ׂĂ�2D�e�N�X�`�����Ǘ�
class CTextureManager
{
public:
	~CTextureManager();

	//�O������g���p
	//�����Ƃ��Ď󂯎�����t�@�C��������e�N�X�`���̏����擾���Ԃ��֐�
	//�摜�t�@�C����Image�t�H���_�ɓ����Ă��镨�̂ݓǂݍ��߂�
	//����:string �摜�t�@�C���̖��O(�g���q�܂�)
	TEXTURE LoadTexture(string filename);

	//�V���O���g��
	static CTextureManager* getInstance();
private:
	//�摜���쐬
	HRESULT SetTexture(TEXTURE& tex);
	//�e�N�X�`�����i�[����map
	map<UINT64,TEXTURE> m_TexMap;
	//���̂��`
	static CTextureManager* m_pInstance;
};
#endif //_TEXTURE_H_