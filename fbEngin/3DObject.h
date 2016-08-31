
#ifndef _3DOBJECT_H_
#define _3DOBJECT_H_

#include "GameObject.h"

#include "SkinModel.h"
#include "Animation.h"
#include "Camera.h"
#include "Light.h"

class C3DObject :public CGameObject
{
public:
	C3DObject(string name = "");

	//Start関数よりも先に呼ばれる
	//純粋仮想関数ではないので絶対オーバーライドしなくてもいい
	virtual void Awake(){};

	//初期化を行う関数(一度のみ呼ばれる)
	virtual void Start() = 0;

	//更新を行う関数
	virtual void Update() = 0;

	//更新の後に呼び出される関数
	//純粋仮想関数ではないので絶対オーバーライドしなくてもいい
	virtual void LateUpdate(){};

	//描画を行う関数
	virtual void Render() = 0;

	//モデルデータ設定
	void SetModelData(CSkinModelData* pD)
	{
		m_model.SetModelData(pD);
	}
	//カメラセット
	void SetCamera(CCamera** c)
	{
		m_ppCamera = c;
	}
	//ライトカメラセット
	void SetLightCamera(CCamera* c)
	{
		m_pLightCamera = c;
	}
	void SetLightDepth(TEXTURE tex)
	{
		m_model.SetDepth(tex);
	}
	//親の行列設定
	void SetParent(D3DXMATRIX* pP)
	{
		m_model.SetParent(pP);
	}
	//行列ゲット
	D3DXMATRIX* GetParent()
	{
		return m_model.GetParent();
	}
	//モデル移動に使うトランスフォーム設定(変更したいとき)
	void SetTransForm(CTransform* pT)
	{
		m_model.SetTransForm(pT);
	}
	//ライトは外部から受け取らないかも・・・
	/*void SetLight(CLight* l)
	{
		m_Light = l;
	}*/
protected:
	//モデル描画媒体
	CSkinModel m_model;
	//アニメーション管理
	//CAnimation m_animetion;
	//カメラ
	CCamera** m_ppCamera;
	//ライトカメラ
	CCamera* m_pLightCamera;
	//
	TEXTURE m_LightDepth;
	//ライト(初期値は標準ライト)
	CLight* m_pLight;
};

#endif //_3DOBJECT_H_