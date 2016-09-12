#include "SkinModelData.h"

#ifndef _SKINMODEL_H_
#define _SKINMODEL_H_
#include "TextureManager.h"

//描画タイプ
enum TYPE
{
	SHADOW,		//影を落とすかどうか
	BLOOM,		//光をあふれさせるかどうか
	EDGE,		//エッジをかけるかどうか
	TOON,		//トゥーンシェーダをかけるかどうか
	SPECULAR,	//スペキュラーライトを適用するかどうか
	FRESNEL,	//フレネル反射を適用するかどうか
	TYPE_NUM	//TYPEの総数
};

//
enum MODE
{
	STANDARD,		//通常描画
	MINIMUM,	//最低限の描画
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
	//第一引数：CCamera* ゲームカメラ,
	//第二引数：CCamera* ライトのカメラ,
	//第三引数：CLight* ライト(任意)　= nullptr
	//第四引数：MODE 描画モード = STANDARD
	void Render(CCamera*, CCamera*, CLight* = nullptr,MODE = MODE::STANDARD);

	//モデルデータの行列更新
	void UpdateFrameMatrix();

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

	void SetDepth(TEXTURE tex)
	{
		m_pLightDepth = tex;
	}
private:
	//エフェクトへの参照
	CEffect* m_pEffect;
	//モデルデータへアクセスするためのポインタ保持
	CSkinModelData* m_pModelDate;
	//親行列
	D3DXMATRIX* m_Parent;

	//描画タイプ
	bool m_RenderType[TYPE::TYPE_NUM];
	//描画モード
	MODE m_Mode;

	//混ぜる色
	D3DXVECTOR4 m_BlendColor;

	//保持用
	CTransform* m_pTrans;
	CCamera* m_pCamera;
	CCamera* m_pLightCamera;	//ライトのカメラ
	CLight* m_pLight;

	TEXTURE m_pLightDepth;		//ライトから見た深度テクスチャ




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

	//アニメーションありモデル描画
	void RenderAnimateMini(D3DXMESHCONTAINER_DERIVED* pMeshContainerBase, D3DXFRAME_DERIVED* pFrame);
	//アニメーションなしモデル描画
	void RenderNonAnimateMini(D3DXMESHCONTAINER_DERIVED* pMeshContainerBase, D3DXFRAME_DERIVED* pFrame);
};
#endif //_SKINMODEL_H_