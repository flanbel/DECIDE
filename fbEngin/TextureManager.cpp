#include "TextureManager.h"
#include "support.h"

CTextureManager* CTextureManager::m_pInstance = new CTextureManager();

CTextureManager::~CTextureManager()
{
	map<UINT64, TEXTURE>::iterator it = m_TexMap.begin();

	while (it != m_TexMap.end())
	{
		//テクスチャ解放
		it->second.Release();
	}
}

//登録、読み込みを行う
TEXTURE CTextureManager::LoadTexture(string filename)
{
	TEXTURE tex;

	UINT64 hush = Support::MakeHash(filename);
	//一致するものなし
	if (m_TexMap[hush].pTexture == nullptr)
	{
		//パスを付け足す
		tex.texpath = "Image/" + filename;

		//テクスチャ情報読み込みが成功すれば登録
		if (SUCCEEDED(SetTexture(tex)))
		{
			//mapに登録
			m_TexMap[hush] = tex;
		}
		//読み込み失敗(画像がないとか)
		else
		{
			string error = "画像パス：" + tex.texpath + " の画像の読み込みに失敗しました。";
			
			MessageBoxA(NULL, error.c_str(), "error:画像読み込みエラー", MB_OK);
		}
	}
	else
	{
		tex = m_TexMap[hush];
	}

	return tex;
}

HRESULT CTextureManager::SetTexture(TEXTURE& tex)
{
	//戻り値受け取り
	HRESULT hr;
	//テクスチャ読込　各情報をセット(画像のサイズとか)
	hr = D3DXCreateTextureFromFileEx(
		graphicsDevice(),			//グラフィックデバイスへのポインタ
		tex.texpath.c_str(),		//ファイルパス
		D3DX_DEFAULT,				//幅、D3DX_DEFAULT ならファイルから取得
		D3DX_DEFAULT,				//高さ、D3DX_DEFAULT ならファイルから取得
		D3DX_DEFAULT,				//ミップレベル？
		0,							//使い方0以外だとレンダーターゲットとして使えたりする。
		D3DFMT_UNKNOWN,				//フォーマット,D3DFMT_UNKNOWN だとファイルから取得する
		D3DPOOL_DEFAULT,			//テクスチャの配置先のメモリ指定 よくわからんからデフォで
		D3DX_FILTER_NONE,			//フィルタリングの指定,NONEだと何もしないよ
		D3DX_DEFAULT,				//ミップフィルター？
		0x00000000,					//透明にする色(透明な黒を指定)
		&tex.imgInfo,				//ファイルのデータを格納するポインタ
		NULL,						//パレット？？？
		&tex.pTexture);				//作成されたテクスチャへのポインタ

	return hr;
}

CTextureManager* CTextureManager::getInstance()
{
	//なかった場合初期化
	if (m_pInstance == NULL)
	{
		m_pInstance = new CTextureManager();
	}
	return m_pInstance;
}
