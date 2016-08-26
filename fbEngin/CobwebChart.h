
#ifndef _COBWEBCHART_H_
#define _COBWEBCHART_H_

#include "2DObject.h"
#include "2DLine.h"
#include "Text.h"
#include "RenderTarget.h"

enum LINETYPE 
{
	RANK = 0,		//����̂Ƃ�
	ITEM,			//���S����e���ڂɂ����Ẵ��C��
	PROT,			//�]���_
	LINETYPE_NUM
};

//���[�_�[�`���[�g�N���X
class CCobwebChart:public C2DObject
{
public:
	CCobwebChart(string name = "");
	~CCobwebChart()
	{
		//�v���b�g�̒��_���
		SAFE_DELETE_ARRAY(m_ProtVec);

		for each (CText* var in m_Text)
		{
			SAFE_DELETE(var);
		}
		m_Text.clear();
	}
	//���������s���֐�(��x�̂݌Ă΂��)
	void Start();

	//�X�V���s���֐�
	void Update();

	void LateUpdate();

	//�`����s���֐�
	void Render();

	//���[�_�[�`���[�g�̃x�[�X�쐬
	//�������Fshort ���ڐ�,�������Ffloat ����,��O�����Fshort �ő吔�l
	void CreateChartBase(const short itemnum, float length,short max);

	//���[�_�[�`���[�g�̃v���b�g�쐬
	//��ɃA�b�v�f�[�g���ĂԕK�v����
	void CreateChartProt();

	//�v���b�g�̐F�ݒ�
	//�������FD3DCOLOR �F
	void ProtColor(D3DXCOLOR color)
	{
		m_ProtColor = color;
	}

	//�l�N�X�g�v���b�g�i�[
	//�������Fshort[] �v���b�g���������z��
	void NextProt(short* protArray);

	//�v���b�g�̈ʒu���l�N�X�g�Ɉ�Â���֐�
	//�������Ffloat ���t���[���œ��B�����邩
	void UpdateProt(float F);
private:
	//���C��
	C2DLine m_line;
	//���̒��_�i�[
	vector<D3DXVECTOR2> m_lineVec[LINETYPE::LINETYPE_NUM];
	//�����N��
	short m_MaxRank;
	//���ڐ�
	short m_ItemNum;
	//�傫��
	float m_length;
	//�v���b�g�̐F
	D3DCOLOR m_ProtColor;
	
	//�v���b�g�̒��_�͏��Ȃ��̂ŕێ����Ă݂�
	D3DXVECTOR2* m_ProtVec;

	//�e�L�X�g�����i�[
	vector<CText*> m_Text;
	//�v���b�g�̔z��
	vector<float> m_ProtArray;
	//���̃v���b�g�̔z��
	vector<float> m_NextProtArray;
	//�v���b�g�̍�
	vector<short> m_DiffProtArray;
	//�ύX�t���O
	bool m_Chenge;
	//���B
	bool m_Comp;

	//�����_�[�^�[�Q�b�g
	CRenderTarget m_RenderT;
	//
	TEXTURE m_tex;
};

#endif //_COBWEBCHART_H_