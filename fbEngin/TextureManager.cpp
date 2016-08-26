#include "TextureManager.h"
#include "support.h"

CTextureManager* CTextureManager::m_pInstance = new CTextureManager();

CTextureManager::~CTextureManager()
{
	map<UINT64, TEXTURE>::iterator it = m_TexMap.begin();

	while (it != m_TexMap.end())
	{
		//�e�N�X�`�����
		it->second.Release();
	}
}

//�o�^�A�ǂݍ��݂��s��
TEXTURE CTextureManager::LoadTexture(string filename)
{
	TEXTURE tex;

	UINT64 hush = Support::MakeHash(filename);
	//��v������̂Ȃ�
	if (m_TexMap[hush].pTexture == nullptr)
	{
		//�p�X��t������
		tex.texpath = "Image/" + filename;

		//�e�N�X�`�����ǂݍ��݂���������Γo�^
		if (SUCCEEDED(SetTexture(tex)))
		{
			//map�ɓo�^
			m_TexMap[hush] = tex;
		}
		//�ǂݍ��ݎ��s(�摜���Ȃ��Ƃ�)
		else
		{
			string error = "�摜�p�X�F" + tex.texpath + " �̉摜�̓ǂݍ��݂Ɏ��s���܂����B";
			
			MessageBoxA(NULL, error.c_str(), "error:�摜�ǂݍ��݃G���[", MB_OK);
		}
	}
	else
	{
		tex = m_TexMap[hush];
	}

	return tex;
}

HRESULT CTextureManager::SetTexture(TEXTURE& tex)
{
	//�߂�l�󂯎��
	HRESULT hr;
	//�e�N�X�`���Ǎ��@�e�����Z�b�g(�摜�̃T�C�Y�Ƃ�)
	hr = D3DXCreateTextureFromFileEx(
		graphicsDevice(),			//�O���t�B�b�N�f�o�C�X�ւ̃|�C���^
		tex.texpath.c_str(),		//�t�@�C���p�X
		D3DX_DEFAULT,				//���AD3DX_DEFAULT �Ȃ�t�@�C������擾
		D3DX_DEFAULT,				//�����AD3DX_DEFAULT �Ȃ�t�@�C������擾
		D3DX_DEFAULT,				//�~�b�v���x���H
		0,							//�g����0�ȊO���ƃ����_�[�^�[�Q�b�g�Ƃ��Ďg�����肷��B
		D3DFMT_UNKNOWN,				//�t�H�[�}�b�g,D3DFMT_UNKNOWN ���ƃt�@�C������擾����
		D3DPOOL_DEFAULT,			//�e�N�X�`���̔z�u��̃������w�� �悭�킩��񂩂�f�t�H��
		D3DX_FILTER_NONE,			//�t�B���^�����O�̎w��,NONE���Ɖ������Ȃ���
		D3DX_DEFAULT,				//�~�b�v�t�B���^�[�H
		0x00000000,					//�����ɂ���F(�����ȍ����w��)
		&tex.imgInfo,				//�t�@�C���̃f�[�^���i�[����|�C���^
		NULL,						//�p���b�g�H�H�H
		&tex.pTexture);				//�쐬���ꂽ�e�N�X�`���ւ̃|�C���^

	return hr;
}

CTextureManager* CTextureManager::getInstance()
{
	//�Ȃ������ꍇ������
	if (m_pInstance == NULL)
	{
		m_pInstance = new CTextureManager();
	}
	return m_pInstance;
}
