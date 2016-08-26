/*!
 *@brief	スキンモデルデータ
 */
#ifndef _SKINMODELDATA_H_
#define _SKINMODELDATA_H_

struct D3DXFRAME_DERIVED : public D3DXFRAME {
	D3DXMATRIXA16	CombinedTransformationMatrix;	//合成済み行列。
};

struct AABB	//軸平行境界ボックス
{
	D3DXVECTOR3 center;		//中心点
	D3DXVECTOR3 size;		//サイズ
};

struct OBB	//有向境界ボックス
{
	D3DXVECTOR3 center;		//ボックスの中心点
	D3DXVECTOR3 rot;		//ボックスの回転角度
	D3DXVECTOR3 halfsize;	//ボックスの各軸の半分のサイズ
};

//メッシュコンテナを継承した拡張メッシュコンテナ
struct D3DXMESHCONTAINER_DERIVED : public D3DXMESHCONTAINER {
	//テクスチャ
	LPDIRECT3DTEXTURE9* ppTextures;
	//
	LPD3DXMESH pOrigMesh;
	//
	LPD3DXATTRIBUTERANGE pAttributeTable;
	//
	DWORD NumAttributeGroups;
	//
	DWORD NumInfl;
	//
	LPD3DXBUFFER pBoneCombinationBuf;
	//フレームの合成済み行列への参照
	D3DXMATRIX** ppBoneMatrixPtrs;
	//ボーンのオフセット行列
	D3DXMATRIX* pBoneOffsetMatrices;
	//
	DWORD NumPaletteEntries;
	//
	bool UseSoftwareVP;
	//
	DWORD iAttributeSW;
	//AABBサイズ格納
	AABB aabb;
	//OBB格納
	OBB obb;
};

//モデルのデータを扱うクラス
class CSkinModelData{
public:
	/*!
	 *@brief	コンストラクタ。
	 */
	CSkinModelData();
	/*!
	 *@brief	デストラクタ。
	 */
	~CSkinModelData();
	/*!
	 * @brief	モデルデータをロード。
	 *@param[in]	filePath	ファイルパス。
	 */
	void LoadModelData(const char* filePath, ID3DXAnimationController* pAnimationC = nullptr);
	/*!
	* @brief	リリース。
	*/
	void Release();

	//最初(根元？)のフレーム取得
	LPD3DXFRAME GetFrameRoot()
	{
		return m_frameRoot;
	}

	ID3DXAnimationController* GetAnimationController()
	{
		return m_pAnimationController;
	}

	//引数として受け取った行列を親として,骨の行列を更新
	//第一引数：D3DXMATRIX&　ワールド行列
	void UpdateBoneMatrix(const D3DXMATRIX& matWorld);
private:
	LPD3DXFRAME					m_frameRoot;		//フレームルート。
	//アニメーションコントローラー
	ID3DXAnimationController* m_pAnimationController;
};

#endif //_SKINMODELDATA_H_
