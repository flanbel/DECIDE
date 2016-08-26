


#ifndef _SUPPORT_H_
#define _SUPPORT_H_

//�������[���[�N�������o
//#if _DEBUG
//#define _CRTDBG_MAP_ALLOC
//#include <crtdbg.h>
//#define NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
//#endif

//�֗��Ȋ֐����`
class Support
{
public:
	//������string�^�̕�����ɕϊ�
	//�߂�l�F������̃|�C���^(�z��)
	//�������Fstring* �i�[��|�C���^,�������Fint �ϊ�����������
	static void IntToString(string* s, int dnum)
	{
		vector<char> wst;
		//�����R�[�h�ϊ�
		do
		{
			//1����
			short n = dnum % 10;
			//�����R�[�h�ϊ�
			char wc = n + '0';
			//�o�^
			wst.push_back(wc);
			//���̌���
			dnum /= 10;
		} while (dnum != 0);

		//�����S����
		s->clear();

		//���Ԃ��t�̂Ȃ̂ŁA����������
		short i, j;
		for (i = 0, j = wst.size() - 1; j >= 0; i++, j--)
		{
			s->push_back(wst[i]);
		}
		//�I�[����
		//s = s + '\0';

	}
	//������WCHAR�^�̕�����ɕϊ�
	//�߂�l�F������̃|�C���^(�z��)
	//�������FWCHAR* �i�[��|�C���^,�������Fint �ϊ�����������
	static void IntToWchar(WCHAR* ws, int dnum)
	{
		vector<WCHAR> wst;
		//�����R�[�h�ϊ�
		do
		{
			//1����
			short n = dnum % 10;
			//�����R�[�h�ϊ�
			WCHAR wc = n + '0';
			//�o�^
			wst.push_back(wc);
			//���̌���
			dnum /= 10;
		} while (dnum != 0);

		//���Ԃ��t�̂Ȃ̂ŁA����������
		short i, j;
		for (i = 0, j = wst.size() - 1; j >= 0; i++, j--)
		{
			ws[i] = wst[j];
		}
		//�I�[����
		ws[i] = '\0';
	}

	//������WCHAR�^�̕�����ɕϊ�
	//�������FWCHAR* ��������i�[����z��,�������Fdouble �ϊ�����������,��O�����Fshort �����_�̂ǂ��܂ŕ\�����邩 = 1
	static void FloatToWchar(WCHAR* ws,double fnum,short n = 1)
	{

		for (short l = 0; l < n; l++)
		{
			fnum *= 10;
		}
		//������ + �l�̌ܓ�
		UINT64 s = (UINT64)(fnum + 0.5f);

		vector<WCHAR> wst;
		//�����R�[�h�ϊ�
		do
		{
			//1����
			short n = s % 10;
			//�����R�[�h�ϊ�
			WCHAR wc = n + '0';
			//�o�^
			wst.push_back(wc);
			//���̌���
			s /= 10;
		} while (s != 0);
		
		//���Ԃ��t�̂Ȃ̂ŁA����������
		short i, j;

		for (i = 0, j = wst.size() - 1; j >= 0; i++, j--)
		{
			//�����_�̈ʒu�ɗ�����
			if (i == wst.size() - n)
			{
				//�h�b�g������
				ws[i] = '.';
				//�Y������i�߂�
				i++;
			}
			ws[i] = wst[j];
		}
		wst.clear();
		//�I�[����
		ws[i] = '\0';
	}

	//�������ɑ������̕����������������
	//������̃|�C���^
	static void LinkingWchar(WCHAR* w1, WCHAR* w2)
	{
		short n1 = 0, n2 = 0;
		//�������𒲂ׂ�
		while (w1[++n1] != '\0');
		while (w2[++n2] != '\0');
		short i;
		for (i = 0; i < n2; i++)
		{
			w1[n1 + i] = w2[i];
		}
		//�I�[����
		w1[n1 + i] = '\0';
	}


	//�n�b�V������
	//����37
#define HASH_NUM 12

	//�����񂩂�n�b�V���l���쐬
	//����:const char* ������
	//�߂�l�FUINT64 �n�b�V���l(32bit)
	static UINT64 MakeHash(const char* string)
	{
		UINT64 hash = 0;
		int l = strlen(string);
		for (int i = 0; i < l; i++){
			hash = hash * HASH_NUM + string[i];
		}
		return hash;
	}

	//�����񂩂�n�b�V���l���쐬
	//����:const WCHAR* ������
	//�߂�l�FUINT64 �n�b�V���l(32bit)
	static UINT64 MakeHash(const WCHAR* string)
	{
		UINT64 hash = 0;
		int l = 0;
		while (string[++l] != '\0');
		for (int i = 0; i < l; i++){
			hash = hash * HASH_NUM + string[i];
		}
		return hash;
	}

	//�����񂩂�n�b�V���l���쐬
	//����:string ������
	//�߂�l�FUINT64 �n�b�V���l
	static UINT64 MakeHash(string st)
	{
		UINT64 hash = 0;
		int l = st.size();
		for (int i = 0; i < l; i++){
			hash = hash * HASH_NUM + st[i];
		}
		return hash;
	}
};

#endif //_SUPPORT_H_