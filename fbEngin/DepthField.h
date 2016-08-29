
#ifndef _DEPTHFIELD_H_
#define _DEPTHFIELD_H_

#include "RenderTarget.h"
#include "GaussianFilter.h"
#include "Sprite.h"

//��ʊE�[�x
class CDepthField :public CSprite
{
public:
	void Initialize();
	void DepthofField(TEXTURE* tex1,TEXTURE* Depth);
private:
	CGaussianFilter m_Gaussian;
	CRenderTarget m_RT[4];
	TEXTURE m_tex[4];
};


#endif //DEPTHFIELD