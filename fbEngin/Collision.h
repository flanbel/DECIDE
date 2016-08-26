
#ifndef _COLLISION_H_
#define _COLLISION_H_

//四角形のあたり判定に使う構造体
struct SquareCollision
{

	D3DXVECTOR2 leftTop;		//左上の座標
	D3DXVECTOR2 size;			//画像のサイズ
};

//円の当たり判定に使う構造体
struct CircleCollision
{
	D3DXVECTOR2 center;			//円の中心点
	FLOAT radius;				//円の半径
};

//#include "SkinModelData.h"
////3DモデルのFrameのOBBを更新する関数
////第一引数:const D3DXFRAME& フレーム,
////第二引数：const D3DXMATRIX& ワールド行列
//static void UpdateFrameOBB(const LPD3DXFRAME pFrame, const D3DXMATRIX& wolrd)
//{
//	//拡張メッシュコンテナに変換
//	D3DXMESHCONTAINER_DERIVED* pMeshContainer = (D3DXMESHCONTAINER_DERIVED*)pFrame->pMeshContainer;
//
//	//メッシュコンテナがあるなら
//	if (pMeshContainer != NULL)
//	{
//		//OBBの更新
//		//フレームのワールド行列
//		D3DXMATRIX FrameWolrd = pFrame->TransformationMatrix;
//		//ワールド行列から移動量抜き取り
//		D3DXVECTOR3 pos;
//		pos.x = wolrd._41;
//		pos.y = wolrd._42;
//		pos.z = wolrd._43;
//
//		//OBBの中心点更新(中心点+移動量)
//		pMeshContainer->obb.center = pMeshContainer->aabb.center + pos;
//		//OBBの回転量更新
//		pMeshContainer->obb.rot;
//		//OBBの各軸の半分の長さ更新
//		pMeshContainer->obb.halfsize = pMeshContainer->aabb.size;
//	}
//
//	//兄弟更新
//	if (pFrame->pFrameSibling != NULL)
//	{
//		UpdateFrameOBB(pFrame->pFrameSibling, wolrd);
//	}
//
//	//子更新
//	if (pFrame->pFrameFirstChild != NULL)
//	{
//		UpdateFrameOBB(pFrame->pFrameFirstChild, wolrd);
//	}
//}

//側
enum SIDE{ S_LEFT = 0, S_RIGHT = 1, S_TOP, S_BOTTOM };

//あたり判定のクラス
class CCollision
{
public:
	//円同士のあたり判定関数
	//第一引数：CircleCollision 円,第二引数：CircleCollision 円
	//戻り値：bool 当たったかどうか
	static bool CircleIsHit(CircleCollision a, CircleCollision b)
	{
		return (pow(a.center.x - b.center.x, 2) + pow(a.center.y - b.center.y, 2) <= pow(a.radius + b.radius, 2));
	}

	//四角形同士のあたり判定関数
	static bool SquareIsHit(SquareCollision a, SquareCollision b)
	{
		FLOAT squ1[4] = { a.leftTop.x, a.leftTop.x + a.size.x, a.leftTop.y, a.leftTop.y + a.size.y };
		FLOAT squ2[4] = { b.leftTop.x, b.leftTop.x + b.size.x, b.leftTop.y, b.leftTop.y + b.size.y };

		return (squ1[S_LEFT] < squ2[S_RIGHT] &&
				squ1[S_RIGHT] > squ2[S_LEFT] &&
				squ1[S_TOP] < squ2[S_BOTTOM] &&
				squ1[S_BOTTOM] > squ2[S_TOP]);
	}

	//点と四角形のあたり判定
	static bool PointIsHit(D3DXVECTOR2 a, SquareCollision b)
	{
		FLOAT squ[4] = { b.leftTop.x, b.leftTop.x + b.size.x, b.leftTop.y, b.leftTop.y + b.size.y };

		//四角形のなかに点があるかどうか
		return (squ[S_LEFT] < a.x &&
				squ[S_RIGHT] > a.x &&
				squ[S_TOP] < a.y &&
				squ[S_BOTTOM] > a.y);
	}

	//OBBあたり判定
	static bool OBBIsHit()
	{
		return true;
	}

	//TODO(Z.Take):短形と点のあたり判定
	//1:点
	//2:短形（支点）
	//3:短形（目的地）
	static bool ObliqueIsHit(D3DXVECTOR2 p, SquareCollision sqr, D3DXVECTOR2 obl)
	{
		//物体Xの中心座標を計算する。
		D3DXVECTOR2 buttaiXPos = sqr.leftTop;
		/*buttaiXPos.x -= sqr.size.x * 0.5f;
		buttaiXPos.y -= sqr.size.y * 0.5f;*/
		//物体Xからそよ姫に向かって伸びるベクトル。
		D3DXVECTOR2 toSoyoHime;
		toSoyoHime = p - buttaiXPos;
		//風の向きを計算する。
		D3DXVECTOR2 windDir = obl - buttaiXPos;
		//風の影響を受ける終点までの長さを求める。
		float lengthWind = D3DXVec2Length(&windDir);
		D3DXVec2Normalize(&windDir, &windDir);
		D3DXVECTOR2 toSoyoHimeDir;
		D3DXVec2Normalize(&toSoyoHimeDir, &toSoyoHime);
		if (D3DXVec2Dot(&toSoyoHimeDir, &windDir) < -0.1f){
			return false;
		}
		//そよ姫の座標を、風の方向に射影する
		float t = D3DXVec2Dot(&toSoyoHime, &windDir);
		if (t > lengthWind){
			return false;
		}
		//風の向きベクトルに射影した場合のそよ姫の座標を求める。
		D3DXVECTOR2 soyoHimePosInWindDir;
		soyoHimePosInWindDir = windDir * t;
		//そよ姫から風のベクトルに対して、垂直に落としたベクトルを求める。
		D3DXVECTOR2 v = toSoyoHime - soyoHimePosInWindDir;
		if (D3DXVec2Length(&v) > 10.0f){
			return false;
		}
		return true;
	}
};

#endif //_COLLISION_H_