
#ifndef _LIGHT_H_
#define _LIGHT_H_

//DiffuseLightの情報を格納する構造体
struct DIFFUSELIGHT
{
	D3DXVECTOR4* Direction;	//ライトの方向。
	D3DXVECTOR4* Color;		//ライトの色。
};

struct LIGHT
{
	D3DXVECTOR4 Direction;	//ライトの方向。
	D3DXVECTOR4 Color;		//ライトの色。
};

class CLight
{
public:
	CLight();
	//ディフューズライトを作る関数
	//第一引数：LIGHT* ライトの情報の構造体配列,第二引数：UINT ライトの数
	void CreateDiffuseLight(LIGHT* date,UINT lightnum);
	//アンビエントライト作成
	//第一引数：D3DXVECTOR4 アンビエントライトのカラー
	void CreateAmbientLight(D3DXVECTOR4 ambient);

	//ゲッター
	DIFFUSELIGHT GetDLight()
	{
		return m_DiffuseLight;
	}
	//ゲッター
	D3DXVECTOR4 GetAmbient()
	{
		return m_ambientLight;
	}

	//標準ライト
	static CLight Standard;
	//ライトを当てない
	static CLight NoLight;
private:
	int				DLIGHT_NUM;		//ディフューズライトの数
	DIFFUSELIGHT	m_DiffuseLight;	//ディフューズライト
	D3DXVECTOR4		m_ambientLight;	//環境光
};
#endif //_LIGHT_H_