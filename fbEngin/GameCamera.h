
#ifndef _GAMECAMERA_H_
#define _GAMECAMERA_H_

#include "Camera.h"

class CGameCamera : public CCamera
{
public:
	CGameCamera(int num);
	//ƒJƒƒ‰ˆÚ“®ŠÖ”
	void Move() override;
private:
	//
	int m_PlayerNumber;
};
#endif //_GAMECAMERA_H_