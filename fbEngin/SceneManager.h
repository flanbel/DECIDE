

#ifndef _SCENEMANAGER_H_
#define _SCENEMANAGER_H_

class CScene;
//追加した順に自分で追加
enum SCENE 
{
	NSCENE = -1,	//何のシーンでもないことを示す引数には使わないで
	TEST = 0,		//テストシーン
	TITLE,			//タイトルシーン
	MENU,			//メニューシーン
	CHARASELECT,	//キャラクターセレクト
	BATTLE,
};

//シーンを管理するクラス
class CSceneManager
{
public:
	CSceneManager()
	{
		//キャッシュ初期化
		FOR(SCENECASHE_NUM)
		{
			m_Cache[i] = SCENE::NSCENE;
		}
	}
	//シーンの追加
	void Add(CScene* pAdd);
	//シーンの初期化を行う
	//オブジェクトマネージャーに追加されているオブジェクトの初期化も勝手に呼び出す
	void StartScene();
	//シーンの更新を行う
	//オブジェクトマネージャーに追加されているオブジェクトの更新も勝手に呼び出す
	void UpdateScene();
	//シーンの描画を行う
	//オブジェクトマネージャーに追加されているオブジェクトの描画を勝手に呼び出す
	void DrawScene();
	//シーンの切り替え
	//次のシーンの初期化とアップデートを勝手に呼び出してくれる。
	void ChangeScene(SCENE key);

	//キャッシュ追加
	void AddCache(SCENE scene);
	//キャッシュにあるかどうか調べる
	short HitCache(SCENE scene);
	//インスタンスを取得
	static CSceneManager* getInstance();
private:
	SCENE m_nowScene;
	vector<CScene*> m_scenes;
	//キャッシュシーン
	SCENE m_Cache[SCENECASHE_NUM];

	//実体を一つにする。
	static CSceneManager* m_pInstance;
};
#endif //_SCENEMANAGER_H_