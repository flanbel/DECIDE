
#ifndef _GAUSSIANFILTER_H_
#define _GAUSSIANFILTER_H_

#include "Sprite.h"

#define NUM_WEIGHTS 8

//ガウスフィルタをかけるクラス
class CGaussianFilter : public CSprite
{
public:
	CGaussianFilter();
	void XBlur(TEXTURE* ptex,FLOAT dispersion);
	void YBlur(TEXTURE* ptex,FLOAT dispersion);
private:
	void UpdateWeight(FLOAT dispersion);

	float	m_weights[NUM_WEIGHTS];
};

#endif //_GAUSSIANFILTER_H_