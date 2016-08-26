#include "SkinModelData.h"

#ifndef _SKINMODEL_H_
#define _SKINMODEL_H_

//描画タイプ
enum TYPE
{
	SHADOW,		//影を落とすかどうか
	EDGE,		//エッジをかけるかどうか
	TOON,		//トゥーンシェーダをかけるかどうか
	SPECULAR,	//スペキュラーライトを適用するかどうか
	FRESNEL,	//フレネル反射を適用するかどうか
	TYPE_NUM	//TYPEの総数
};

class CEffect;
class CTransform;
class CCamera;
class CLight;

//モデルの描画を行うクラス
class CSkinModel{
public:
	CSkinModel(CTransform* ptrans);
	~CSkinModel();

	//3Dモデルの描画を呼び出す
	//第一引数：CCamera* カメラ,第二引数：：CLight* ライト(任意)　= &CLight::Standard(標準ライト)
	void Render(CCamera*,CLight* = nullptr);

	//色設定
	void BlendColor(D3DXVECTOR4 color)
	{
		m_BlendColor = color;
	}
	//シェーダー指定
	void RenderType(TYPE type, bool flg)
	{
		m_RenderType[type] = flg;
	}
	//モデルデータへアクセスするためのポインタ設定
	void SetModelData(CSkinModelData* pD)
	{
		m_pModelDate = pD;
	}
	//モデルの親の行列設定
	void SetParent(D3DXMATRIX* pP)
	{
		m_Parent = pP;
	}

	D3DXMATRIX* GetParent()
	{
		return m_Parent;
	}

	//トランスフォーム変更
	//途中で変えたいときに使う
	void SetTransForm(CTransform* pT)
	{
		m_pTrans = pT;
	}

	//モデルデータの行列更新
	void UpdateFrameMatrix();
private:
	//エフェクトへの参照
	CEffect* m_pEffect;
	//モデルデータへアクセスするためのポインタ保持
	CSkinModelData* m_pModelDate;
	//親
	D3DXMATRIX* m_Parent;

	//描画タイプ
	bool m_RenderType[TYPE::TYPE_NUM];

	//混ぜる色
	D3DXVECTOR4 m_BlendColor;

	//保持用
	CTransform* m_pTrans;
	CCamera* m_pCamera;
	CLight* m_pLight;

	//プライベート関数

	//子とか兄弟も一括で描画するための再帰関数
	void DrawFrame(LPD3DXFRAME pFrame);
	
	//描画分岐
	void CSkinModel::DrawMeshContainer(
		D3DXMESHCONTAINER_DERIVED* pMeshContainerBase,
		LPD3DXFRAME pFrameBase
		);

	//アニメーションありモデル描画
	void RenderAnimate(D3DXMESHCONTAINER_DERIVED* pMeshContainerBase, D3DXFRAME_DERIVED* pFrame);
	//アニメーションなしモデル描画
	void RenderNonAnimate(D3DXMESHCONTAINER_DERIVED* pMeshContainerBase, D3DXFRAME_DERIVED* pFrame);
};
#endif //_SKINMODEL_H_