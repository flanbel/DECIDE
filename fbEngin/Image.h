
#ifndef _IMAGE_H_
#define _IMAGE_H_

#include "2DObject.h"
#include "Sprite.h"

//�摜��`�悷�邾���̃N���X
class CImage :public C2DObject
{
public:
	CImage(string name = "") :C2DObject(name){};
	//���������s���֐�(��x�̂݌Ă΂��)
	void Start();

	//�X�V���s���֐�
	void Update();

	//�`����s���֐�
	void Render();
private:
};

#endif //_IMAGE_H_