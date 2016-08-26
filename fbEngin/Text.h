
#ifndef _TEXT_H_
#define _TEXT_H_

#include "2DObject.h"
#include "Font.h"

//•¶Žš—ñ‚ð•`‰æ‚·‚é‚¾‚¯‚ÌƒNƒ‰ƒX
class CText:public C2DObject
{
public:
	CText(string name = "");
	void Start()override;
	void Update()override;
	void Render()override;

	void Createfont(WCHAR* st)
	{
		m_font.Createfont(st);
	}

	void SetFontSize(short s)
	{
		m_font.SetFontSize(s);
	}

private:
	CFont m_font;
};

#endif //_TEXT_H_