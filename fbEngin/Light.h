
#ifndef _LIGHT_H_
#define _LIGHT_H_

//DiffuseLight�̏����i�[����\����
struct DIFFUSELIGHT
{
	D3DXVECTOR4* Direction;	//���C�g�̕����B
	D3DXVECTOR4* Color;		//���C�g�̐F�B
};

struct LIGHT
{
	D3DXVECTOR4 Direction;	//���C�g�̕����B
	D3DXVECTOR4 Color;		//���C�g�̐F�B
};

class CLight
{
public:
	CLight();
	//�f�B�t���[�Y���C�g�����֐�
	//�������FLIGHT* ���C�g�̏��̍\���̔z��,�������FUINT ���C�g�̐�
	void CreateDiffuseLight(LIGHT* date,UINT lightnum);
	//�A���r�G���g���C�g�쐬
	//�������FD3DXVECTOR4 �A���r�G���g���C�g�̃J���[
	void CreateAmbientLight(D3DXVECTOR4 ambient);

	//�Q�b�^�[
	DIFFUSELIGHT GetDLight()
	{
		return m_DiffuseLight;
	}
	//�Q�b�^�[
	D3DXVECTOR4 GetAmbient()
	{
		return m_ambientLight;
	}

	//�W�����C�g
	static CLight Standard;
	//���C�g�𓖂ĂȂ�
	static CLight NoLight;
private:
	int				DLIGHT_NUM;		//�f�B�t���[�Y���C�g�̐�
	DIFFUSELIGHT	m_DiffuseLight;	//�f�B�t���[�Y���C�g
	D3DXVECTOR4		m_ambientLight;	//����
};
#endif //_LIGHT_H_