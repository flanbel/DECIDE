
#ifndef _IMAGE_H_
#define _IMAGE_H_

#include "2DObject.h"
#include "Sprite.h"

//画像を描画するだけのクラス
class CImage :public C2DObject
{
public:
	CImage(string name = "") :C2DObject(name){};
	//初期化を行う関数(一度のみ呼ばれる)
	void Start();

	//更新を行う関数
	void Update();

	//描画を行う関数
	void Render();
private:
};

#endif //_IMAGE_H_