
#ifndef _SCENE_H_
#define _SCENE_H_

#include "EffectManager.h"
#include "Effect.h"

//色持ち頂点の頂点情報定義
#define D3DFVF_COLORVERTEX (D3DFVF_XYZW|D3DFVF_DIFFUSE)

//頂点情報(色持ち)
struct ColorVertex
{
	float x, y, z;			//頂点座標
	float w;				//？？
	unsigned long color;	//頂点色
};

//シーンの基底クラス
class CScene
{
public:
	CScene();
	~CScene(){};

	//初期化を行う関数(一度のみ呼ばれる)
	//オブジェクトのAwakeとStartの後に呼ばれる。
	virtual HRESULT Start() = 0;

	//更新を行う関数
	//オブジェクトのUpdateとLateUpdateの間に呼ばれる。
	virtual HRESULT Update() = 0;

	//描画を行う関数
	//オブジェクトのRenderより後に呼ばれる
	virtual HRESULT Draw() = 0;

	//フェード初期化
	void InitFade();
	//フェードアウト
	void FadeOut();
	//フェード描画
	void DrawFade();
private:
protected:
	//頂点
	ColorVertex m_vertices[4];
	//エフェクト
	CEffect* m_pEffect;
	//フェードフラグ
	bool m_Fade;
	
	//フェード終了
	bool m_endFade;
};
#endif //_SCENE_H_