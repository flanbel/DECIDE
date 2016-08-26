
#ifndef _EFFECT_H_
#define _EFFECT_H_

class CEffect
{
public:	
	ID3DXEffect* GetEffect()
	{
		return m_pEffect;
	}

	void SetTexture(D3DXHANDLE hParameter, LPDIRECT3DBASETEXTURE9 pTexture)
	{
		m_pEffect->SetTexture(hParameter, pTexture);
	}

	void SetEffect(ID3DXEffect* effect)
	{
		m_pEffect = effect;
	}

	void Begin(UINT *pPasses, DWORD Flags)
	{
		m_pEffect->Begin(pPasses, Flags);
	}

	void BeginPass(UINT Pass)
	{
		m_pEffect->BeginPass(Pass);
	}

	void SetTechnique(LPCSTR tecname)
	{
		m_pEffect->SetTechnique(tecname);
	}

	void SetMatrix(LPCSTR parameterName, D3DXMATRIX* mat)
	{
		m_pEffect->SetMatrix(parameterName, mat);
	}

	void SetMatrixArray(D3DXHANDLE hParameter, CONST D3DXMATRIX* pMatrix, UINT Count)
	{
		m_pEffect->SetMatrixArray(hParameter, pMatrix, Count);
	}

	void SetVector(D3DXHANDLE hParameter, D3DXVECTOR4* pVector)
	{
		m_pEffect->SetVector(hParameter, pVector);
	}

	void SetVectorArray(D3DXHANDLE hParameter, D3DXVECTOR4* pVector, UINT Count)
	{
		m_pEffect->SetVectorArray(hParameter, pVector, Count);
	}

	void SetValue(D3DXHANDLE hParameter, LPCVOID pData, UINT Bytes)
	{
		m_pEffect->SetValue(hParameter, pData, Bytes);
	}

	void SetInt(D3DXHANDLE hParameter, INT n)
	{
		m_pEffect->SetInt(hParameter, n);
	}

	void SetBool(D3DXHANDLE hParameter, BOOL b)
	{
		m_pEffect->SetBool(hParameter, b);
	}

	void SetFloat(D3DXHANDLE hParameter, FLOAT f)
	{
		m_pEffect->SetFloat(hParameter,f);
	}

	void CommitChanges()
	{
		m_pEffect->CommitChanges();
	}

	void EndPass()
	{
		m_pEffect->EndPass();	
	}

	void End()
	{
		m_pEffect->End();
	}

	void Release()
	{
		if (m_pEffect != NULL) {
			m_pEffect->Release();
			//ポインタ解放
			SAFE_DELETE(m_pEffect);
		}
	}

	ID3DXEffect* GetD3DXEffect()
	{
		return m_pEffect;
	}

private:
	ID3DXEffect* m_pEffect;	//Effectへのポインタ

};
#endif //_EFFECT_H_