
#ifndef _COLLISION_H_
#define _COLLISION_H_

//�l�p�`�̂����蔻��Ɏg���\����
struct SquareCollision
{

	D3DXVECTOR2 leftTop;		//����̍��W
	D3DXVECTOR2 size;			//�摜�̃T�C�Y
};

//�~�̓����蔻��Ɏg���\����
struct CircleCollision
{
	D3DXVECTOR2 center;			//�~�̒��S�_
	FLOAT radius;				//�~�̔��a
};

//#include "SkinModelData.h"
////3D���f����Frame��OBB���X�V����֐�
////������:const D3DXFRAME& �t���[��,
////�������Fconst D3DXMATRIX& ���[���h�s��
//static void UpdateFrameOBB(const LPD3DXFRAME pFrame, const D3DXMATRIX& wolrd)
//{
//	//�g�����b�V���R���e�i�ɕϊ�
//	D3DXMESHCONTAINER_DERIVED* pMeshContainer = (D3DXMESHCONTAINER_DERIVED*)pFrame->pMeshContainer;
//
//	//���b�V���R���e�i������Ȃ�
//	if (pMeshContainer != NULL)
//	{
//		//OBB�̍X�V
//		//�t���[���̃��[���h�s��
//		D3DXMATRIX FrameWolrd = pFrame->TransformationMatrix;
//		//���[���h�s�񂩂�ړ��ʔ������
//		D3DXVECTOR3 pos;
//		pos.x = wolrd._41;
//		pos.y = wolrd._42;
//		pos.z = wolrd._43;
//
//		//OBB�̒��S�_�X�V(���S�_+�ړ���)
//		pMeshContainer->obb.center = pMeshContainer->aabb.center + pos;
//		//OBB�̉�]�ʍX�V
//		pMeshContainer->obb.rot;
//		//OBB�̊e���̔����̒����X�V
//		pMeshContainer->obb.halfsize = pMeshContainer->aabb.size;
//	}
//
//	//�Z��X�V
//	if (pFrame->pFrameSibling != NULL)
//	{
//		UpdateFrameOBB(pFrame->pFrameSibling, wolrd);
//	}
//
//	//�q�X�V
//	if (pFrame->pFrameFirstChild != NULL)
//	{
//		UpdateFrameOBB(pFrame->pFrameFirstChild, wolrd);
//	}
//}

//��
enum SIDE{ S_LEFT = 0, S_RIGHT = 1, S_TOP, S_BOTTOM };

//�����蔻��̃N���X
class CCollision
{
public:
	//�~���m�̂����蔻��֐�
	//�������FCircleCollision �~,�������FCircleCollision �~
	//�߂�l�Fbool �����������ǂ���
	static bool CircleIsHit(CircleCollision a, CircleCollision b)
	{
		return (pow(a.center.x - b.center.x, 2) + pow(a.center.y - b.center.y, 2) <= pow(a.radius + b.radius, 2));
	}

	//�l�p�`���m�̂����蔻��֐�
	static bool SquareIsHit(SquareCollision a, SquareCollision b)
	{
		FLOAT squ1[4] = { a.leftTop.x, a.leftTop.x + a.size.x, a.leftTop.y, a.leftTop.y + a.size.y };
		FLOAT squ2[4] = { b.leftTop.x, b.leftTop.x + b.size.x, b.leftTop.y, b.leftTop.y + b.size.y };

		return (squ1[S_LEFT] < squ2[S_RIGHT] &&
				squ1[S_RIGHT] > squ2[S_LEFT] &&
				squ1[S_TOP] < squ2[S_BOTTOM] &&
				squ1[S_BOTTOM] > squ2[S_TOP]);
	}

	//�_�Ǝl�p�`�̂����蔻��
	static bool PointIsHit(D3DXVECTOR2 a, SquareCollision b)
	{
		FLOAT squ[4] = { b.leftTop.x, b.leftTop.x + b.size.x, b.leftTop.y, b.leftTop.y + b.size.y };

		//�l�p�`�̂Ȃ��ɓ_�����邩�ǂ���
		return (squ[S_LEFT] < a.x &&
				squ[S_RIGHT] > a.x &&
				squ[S_TOP] < a.y &&
				squ[S_BOTTOM] > a.y);
	}

	//OBB�����蔻��
	static bool OBBIsHit()
	{
		return true;
	}

	//TODO(Z.Take):�Z�`�Ɠ_�̂����蔻��
	//1:�_
	//2:�Z�`�i�x�_�j
	//3:�Z�`�i�ړI�n�j
	static bool ObliqueIsHit(D3DXVECTOR2 p, SquareCollision sqr, D3DXVECTOR2 obl)
	{
		//����X�̒��S���W���v�Z����B
		D3DXVECTOR2 buttaiXPos = sqr.leftTop;
		/*buttaiXPos.x -= sqr.size.x * 0.5f;
		buttaiXPos.y -= sqr.size.y * 0.5f;*/
		//����X���炻��P�Ɍ������ĐL�т�x�N�g���B
		D3DXVECTOR2 toSoyoHime;
		toSoyoHime = p - buttaiXPos;
		//���̌������v�Z����B
		D3DXVECTOR2 windDir = obl - buttaiXPos;
		//���̉e�����󂯂�I�_�܂ł̒��������߂�B
		float lengthWind = D3DXVec2Length(&windDir);
		D3DXVec2Normalize(&windDir, &windDir);
		D3DXVECTOR2 toSoyoHimeDir;
		D3DXVec2Normalize(&toSoyoHimeDir, &toSoyoHime);
		if (D3DXVec2Dot(&toSoyoHimeDir, &windDir) < -0.1f){
			return false;
		}
		//����P�̍��W���A���̕����Ɏˉe����
		float t = D3DXVec2Dot(&toSoyoHime, &windDir);
		if (t > lengthWind){
			return false;
		}
		//���̌����x�N�g���Ɏˉe�����ꍇ�̂���P�̍��W�����߂�B
		D3DXVECTOR2 soyoHimePosInWindDir;
		soyoHimePosInWindDir = windDir * t;
		//����P���畗�̃x�N�g���ɑ΂��āA�����ɗ��Ƃ����x�N�g�������߂�B
		D3DXVECTOR2 v = toSoyoHime - soyoHimePosInWindDir;
		if (D3DXVec2Length(&v) > 10.0f){
			return false;
		}
		return true;
	}
};

#endif //_COLLISION_H_