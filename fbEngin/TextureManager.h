

#ifndef _TEXTURE_H_
#define _TEXTURE_H_

typedef struct _TEXTURE
{
	string texpath;					//テクスチャへのパス
	LPDIRECT3DTEXTURE9 pTexture;	//テクスチャへのポインタ
	D3DXIMAGE_INFO imgInfo;			//テクスチャ情報
	D3DXVECTOR2 pivot;				//基点

	//コンストラクタ
	_TEXTURE::_TEXTURE()
	{
		pTexture = nullptr;
		pivot = D3DXVECTOR2(0.5f, 0.5f);
	}

	//テクスチャへのポインタをリリースする
	void _TEXTURE::Release()
	{
		SAFE_DELETE(pTexture);
	}

}TEXTURE;	//テクスチャ関係の情報が入っている構造体

//すべての2Dテクスチャを管理
class CTextureManager
{
public:
	~CTextureManager();

	//外部から使う用
	//引数として受け取ったファイル名からテクスチャの情報を取得し返す関数
	//画像ファイルはImageフォルダに入っている物のみ読み込める
	//引数:string 画像ファイルの名前(拡張子含む)
	TEXTURE LoadTexture(string filename);

	//シングルトン
	static CTextureManager* getInstance();
private:
	//画像情報作成
	HRESULT SetTexture(TEXTURE& tex);
	//テクスチャを格納するmap
	map<UINT64,TEXTURE> m_TexMap;
	//実体を定義
	static CTextureManager* m_pInstance;
};
#endif //_TEXTURE_H_