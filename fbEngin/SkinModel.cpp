#include "SkinModel.h"
#include "EffectManager.h"
#include "Effect.h"
#include "support.h"
#include "TextureManager.h"

#include "Transform.h"
#include "Camera.h"
#include "Light.h"

extern UINT                 g_NumBoneMatricesMax;
extern D3DXMATRIXA16*       g_pBoneMatrices ;

CSkinModel::CSkinModel(CTransform* ptrans)
{
	FOR(TYPE::TYPE_NUM)
	{
		m_RenderType[i] = false;
	}
	m_BlendColor = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	//初期化の際に標準ライトセット
	m_pLight = &CLight::Standard;
	m_Parent = nullptr;
	m_pTrans = ptrans;
}

CSkinModel::~CSkinModel()
{

}

void CSkinModel::DrawMeshContainer(
	D3DXMESHCONTAINER_DERIVED* pMeshContainer,
	LPD3DXFRAME pFrameBase
	)
{
	D3DXFRAME_DERIVED* pFrame = (D3DXFRAME_DERIVED*)pFrameBase;
	
	//スキン情報の有無(ボーンの有無)
	if (pMeshContainer->pSkinInfo != NULL)
	{
		//ボーンがあるならこっち
		RenderAnimate(pMeshContainer,pFrame);
	}
	else
	{
		//ボーンのないモデルはこっち
		RenderNonAnimate(pMeshContainer, pFrame);
	}
}

//再帰関数
void CSkinModel::DrawFrame(LPD3DXFRAME pFrame)
{
	D3DXMESHCONTAINER_DERIVED* pMeshContainer;

	pMeshContainer = (D3DXMESHCONTAINER_DERIVED*)pFrame->pMeshContainer;
	//繋がっているメッシュコンテナがなくなるまで続ける
	while (pMeshContainer != NULL)
	{
		//メッシュ描画
		DrawMeshContainer(
			pMeshContainer,
			pFrame
			);
		//次のメッシュコンテナ
		//一つのフレームにコンテナは複数ある？
		pMeshContainer = (D3DXMESHCONTAINER_DERIVED*)pMeshContainer->pNextMeshContainer;
	}

	//兄弟が居るならを兄弟を読み込む
	if (pFrame->pFrameSibling != NULL)
	{
		DrawFrame(pFrame->pFrameSibling);
	}

	//子が居るなら子を読み込む
	if (pFrame->pFrameFirstChild != NULL)
	{
		DrawFrame(pFrame->pFrameFirstChild);
	}
}


void CSkinModel::Render(CCamera* pcamera, CCamera* plightcamera, CLight* plight)
{
	//カメラ設定
	m_pCamera = pcamera;
	m_pLightCamera = plightcamera;
	if (plight != nullptr)
		m_pLight = plight;

	//モデルデータがあるなら
	if (m_pModelDate)
	{
		UpdateFrameMatrix();
		//再帰関数呼び出し
		DrawFrame(m_pModelDate->GetFrameRoot());
	}
}

void CSkinModel::RenderAnimate(D3DXMESHCONTAINER_DERIVED* pMeshContainer, D3DXFRAME_DERIVED* pFrame)
{

	//アニメーション有り
	//エフェクト読み込み
	m_pEffect = SINSTANCE(CEffectManager)->LoadEffect("AnimationModel.fx");

	m_pEffect->SetTechnique("NormalRender");
	m_pEffect->Begin(0, D3DXFX_DONOTSAVESTATE);
	m_pEffect->BeginPass(0);

	//ライトの向きを転送。
	m_pEffect->SetVectorArray("g_diffuseLightDirection", m_pLight->GetDLight().Direction, sizeof(m_pLight->GetDLight().Direction));
	//ライトのカラーを転送。
	m_pEffect->SetVectorArray("g_diffuseLightColor", m_pLight->GetDLight().Color, sizeof(m_pLight->GetDLight().Color));
	//環境光
	m_pEffect->SetVector("g_ambientLight", &m_pLight->GetAmbient());

	UINT iAttrib;
	//バッファー
	LPD3DXBONECOMBINATION pBoneComb = LPD3DXBONECOMBINATION(pMeshContainer->pBoneCombinationBuf->GetBufferPointer());
	//各マテリアル
	for (iAttrib = 0; iAttrib < pMeshContainer->NumAttributeGroups; iAttrib++)
	{
		//ボーン
		for (DWORD iPaletteEntry = 0; iPaletteEntry < pMeshContainer->NumPaletteEntries; ++iPaletteEntry)
		{
			DWORD iMatrixIndex = pBoneComb[iAttrib].BoneId[iPaletteEntry];
			if (iMatrixIndex != UINT_MAX)
			{
				//骨の最終的な行列計算
				D3DXMatrixMultiply(
					&g_pBoneMatrices[iPaletteEntry],
					//骨のオフセット(移動)行列
					&pMeshContainer->pBoneOffsetMatrices[iMatrixIndex],
					//フレームのワールド行列
					pMeshContainer->ppBoneMatrixPtrs[iMatrixIndex]
					);
			}
		}

		//こっちは普通にワールドマトリックスを渡す
		m_pEffect->SetMatrix("g_rotationMatrix", &m_pTrans->RotateMatrix());
		//m_pEffect->SetMatrix("g_worldMatrix", &pFrame->CombinedTransformationMatrix);		//骨にかけているからいらないよ(ppBoneMatrixPtrs)
		m_pEffect->SetMatrix("g_viewMatrix", &m_pCamera->View());
		m_pEffect->SetMatrix("g_projectionMatrix", &m_pCamera->Projection());

		//骨のワールド行列配列
		m_pEffect->SetMatrixArray("g_mWorldMatrixArray", g_pBoneMatrices, pMeshContainer->NumPaletteEntries);
		//骨の数]
		m_pEffect->SetFloat("g_numBone", (float)pMeshContainer->NumInfl);

		//ディフューズカラー取得
		D3DXVECTOR4* Diffuse = (D3DXVECTOR4*)&pMeshContainer->pMaterials[iAttrib].MatD3D.Diffuse;

		//テクスチャが格納されていればセット
		if (pMeshContainer->ppTextures[iAttrib] != NULL)
		{
			// ディフューズテクスチャ。
			m_pEffect->SetTexture("g_diffuseTexture", pMeshContainer->ppTextures[iAttrib]);
			m_pEffect->SetBool("Texflg", true);
		}
		//テクスチャがないならカラーセット
		else if (Diffuse != NULL)
		{
			m_pEffect->SetVector("g_diffuseMaterial", Diffuse);
			m_pEffect->SetBool("Texflg", false);
		}

		// ボーン数。
		m_pEffect->SetInt("CurNumBones", pMeshContainer->NumInfl - 1);

		// draw the subset with the current world matrix palette and material state
		m_pEffect->CommitChanges();
		pMeshContainer->MeshData.pMesh->DrawSubset(iAttrib);
	}
	m_pEffect->EndPass();
	m_pEffect->End();
}

//アニメーションなし。
void CSkinModel::RenderNonAnimate(D3DXMESHCONTAINER_DERIVED* pMeshContainer, D3DXFRAME_DERIVED* pFrame)
{
	////ワールド行列を格納
	//D3DXMATRIX Wolrd;			//最終的なモデルの座標
	//D3DXMATRIX parent = m_pTrans->WorldMatrix();
	////計算
	//D3DXMatrixMultiply(&Wolrd, &pFrame->TransformationMatrix, &parent);

	//エフェクト読み込み
	m_pEffect = SINSTANCE(CEffectManager)->LoadEffect("3Dmodel.fx");

	//エッジ描画
	if (m_RenderType[TYPE::EDGE])
	{
		//背面描画
		(*graphicsDevice()).SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);

		//テクニックをセット
		m_pEffect->SetTechnique("EdgeRender");
		m_pEffect->Begin(NULL, D3DXFX_DONOTSAVESHADERSTATE);
		m_pEffect->BeginPass(0);

		//各行列をセット。
		//こっちは計算されたマトリックスを渡す
		m_pEffect->SetMatrix("g_rotationMatrix", &pFrame->CombinedTransformationMatrix);
		m_pEffect->SetMatrix("g_worldMatrix", &pFrame->CombinedTransformationMatrix);
		m_pEffect->SetMatrix("g_viewMatrix", &m_pCamera->View());
		m_pEffect->SetMatrix("g_projectionMatrix", &m_pCamera->Projection());

		//マテリアルの数
		DWORD MaterialNum = pMeshContainer->NumMaterials;
		//マテリアル
		D3DXMATERIAL *mtrl = (D3DXMATERIAL*)(pMeshContainer->pMaterials);

		//モデル描画
		for (DWORD i = 0; i < MaterialNum; i++)
		{
			//この関数を呼び出すことで、データの転送が確定する。描画を行う前に一回だけ呼び出す。
			m_pEffect->CommitChanges();
			// Draw the mesh subset
			pMeshContainer->MeshData.pMesh->DrawSubset(i);
		}

		m_pEffect->EndPass();
		m_pEffect->End();

		//背面描画を元に戻す
		(*graphicsDevice()).SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	}

	//透過処理有効
	(*graphicsDevice()).SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	//半透明合成
	(*graphicsDevice()).SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	(*graphicsDevice()).SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	//加算合成
	/*(*graphicsDevice()).SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);
	(*graphicsDevice()).SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);*/

	//通常描画
	{
		//テクニックをセット
		m_pEffect->SetTechnique("NormalRender");

		//※beginとendは必ず対にする。
		m_pEffect->Begin(NULL, D3DXFX_DONOTSAVESHADERSTATE);
		m_pEffect->BeginPass(0);

		//ライトの向きを転送。
		m_pEffect->SetVectorArray("g_diffuseLightDirection", m_pLight->GetDLight().Direction, sizeof(m_pLight->GetDLight().Direction));
		//ライトのカラーを転送。
		m_pEffect->SetVectorArray("g_diffuseLightColor", m_pLight->GetDLight().Color, sizeof(m_pLight->GetDLight().Color));
		//環境光
		m_pEffect->SetVector("g_ambientLight", &m_pLight->GetAmbient());

		//スペキュラーライト
		{
			//視点
			D3DXVECTOR4 eyepos = D3DXVECTOR4(m_pCamera->Pos(), 1.0f);
			m_pEffect->SetVector("g_eyePos", &eyepos);
			m_pEffect->SetBool("Specflg", m_RenderType[TYPE::SPECULAR]);
		}

		//フレネル反射
		{
			//カメラの回転行列の逆行列作成
			D3DXMATRIX viewMatrixRotInv;
			D3DXMatrixInverse(&viewMatrixRotInv, NULL, &m_pCamera->Rotation());
			m_pEffect->SetMatrix("g_viewMatrixRotInv", &viewMatrixRotInv);
			m_pEffect->SetBool("Fresnelflg", m_RenderType[TYPE::FRESNEL]);
		}

		//トゥーンレンダーかけるよ。
		{
			TEXTURE toontex = SINSTANCE(CTextureManager)->LoadTexture("toon.png");
			m_pEffect->SetTexture("g_toonTexture", toontex.pTexture);
			CVector3 toonLight = { -1.0f, -1.0f, 1.0f };

			//太陽からモデルへの方向
			//D3DXVECTOR3 dir = m_pTrans->Position() - m_pCamera->m_Pos;

			/*toonLight.x = dir.x;
		toonLight.y = dir.y;
		toonLight.z = dir.z;*/

			//正規化
			toonLight.Normalize();
			m_pEffect->SetVector("g_toonLight", &D3DXVECTOR4(toonLight.x, toonLight.y, toonLight.z, 1.0f));
			m_pEffect->SetBool("Toonflg", m_RenderType[TYPE::TOON]);
		}

		//影のテクスチャを持っている
		
		if (m_pLightDepth.pTexture != nullptr)
		{
			D3DXMATRIX LVP = m_pLightCamera->View() * m_pLightCamera->Projection();
			m_pEffect->SetMatrix("g_LVP", &LVP);
			m_pEffect->SetTexture("g_LVPTex", m_pLightDepth.pTexture);
			m_pEffect->SetBool("Shadowflg", true);
		}
		else
		{
			m_pEffect->SetBool("Shadowflg", false);
		}
		

		{
			//色の倍率
			m_pEffect->SetVector("g_blendColor", &m_BlendColor);
		}

		//各行列をセット。
		m_pEffect->SetMatrix("g_rotationMatrix", &pFrame->CombinedTransformationMatrix);

		m_pEffect->SetMatrix("g_worldMatrix", &pFrame->CombinedTransformationMatrix);
		m_pEffect->SetMatrix("g_viewMatrix", &m_pCamera->View());
		m_pEffect->SetMatrix("g_projectionMatrix", &m_pCamera->Projection());

		//マテリアルの数
		DWORD MaterialNum = pMeshContainer->NumMaterials;
		//マテリアル
		D3DXMATERIAL *mtrl = (D3DXMATERIAL*)(pMeshContainer->pMaterials);

		//モデル描画
		for (DWORD i = 0; i < MaterialNum; i++)
		{
			//ディフューズカラー
			D3DXVECTOR4* Diffuse = (D3DXVECTOR4*)&mtrl[i].MatD3D.Diffuse;

			//スペキュラーカラー(光沢?)
			D3DXVECTOR4* Specular = (D3DXVECTOR4*)&mtrl[i].MatD3D.Specular;

			//テクスチャー
			LPDIRECT3DTEXTURE9 texture = pMeshContainer->ppTextures[i];

			//テクスチャが格納されていればセット
			if (texture != NULL)
			{
				m_pEffect->SetTexture("g_Texture", texture);
				m_pEffect->SetBool("g_Texflg", true);
			}
			//テクスチャがないならカラーセット
			else if (Diffuse != NULL)
			{
				m_pEffect->SetVector("g_diffuseMaterial", Diffuse);
				m_pEffect->SetBool("g_Texflg", false);
			}

			//この関数を呼び出すことで、データの転送が確定する。描画を行う前に一回だけ呼び出す。
			m_pEffect->CommitChanges();
			// Draw the mesh subset
			pMeshContainer->MeshData.pMesh->DrawSubset(i);
		}

		m_pEffect->EndPass();
		m_pEffect->End();
	}

	//変更したステートを元に戻す
	(*graphicsDevice()).SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
	(*graphicsDevice()).SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);
	(*graphicsDevice()).SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ZERO);
}

//モデルデータの行列更新
void CSkinModel::UpdateFrameMatrix()
{
	//モデルデータがあるなら
	if (m_pModelDate)
	{
		//掛けるワールド行列
		D3DXMATRIX wolrd;
		D3DXMatrixIdentity(&wolrd);
		if (m_Parent == nullptr)
			//自分のワールド行列
			wolrd = m_pTrans->WorldMatrix();
		else
			//親のワールド行列
			wolrd = *m_Parent;

		m_pModelDate->UpdateBoneMatrix(wolrd);	//行列を更新。
	}
	else
	{
		//モデルデータないですよ
	}
}