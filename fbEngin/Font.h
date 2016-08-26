
#ifndef _FONT_H_
#define _FONT_H_

#include "TextureManager.h"
#include "Sprite.h"

typedef struct _FONT{
	TEXTURE tex;
	GLYPHMETRICS gm;
	//TCHAR fontname;
}FONT;

//������`��R���|�[�l���g
class CFont
{
public:
	CFont();
	void Start();
	//�`��(�O���̃g�����X�t�H�[��)
	//�����Ƃ��Ď󂯎�����g�����X�t�H�[������ɕ������`��
	//�������FCTransform �g�����X�t�H�[��
	void Render(CTransform trans);

	//�����̃e�N�X�`������
	//�߂�l�F�Ȃ�
	//�������FWCHAR* �e�N�X�`���𐶐�������������(���{��ɑΉ����邽�߂Ƀ��C�h����)
	void Createfont(WCHAR*);

	//�T�C�Y�ύX
	void SetFontSize(short s)
	{
		m_FontSize = s;
	}

	//����̍�
	void SetSprite(CSprite* s)
	{
		m_pSprite = s;
	}

private:
	//�X�v���C�g
	CSprite* m_pSprite;

	//�`�悷�镶�����ێ�����
	vector<WCHAR> m_string;

	//�t�H���g�̃e�N�X�`���ێ�
	static std::map<WCHAR, FONT> m_FontMap;

	//�t�H���g�T�C�Y
	short m_FontSize;

	//�f�o�C�X�R���e�L�X�g
	static HDC m_hdc;
};
#endif //_FONT_H_