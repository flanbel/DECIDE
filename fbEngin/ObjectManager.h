

#ifndef _OBJECTMANAGER_H_
#define _OBJECTMANAGER_H_

#include "GameObject.h"
#include "2DObject.h"
#include "3DObject.h"

#include "Camera.h"

//オブジェクトを管理するクラス
class CObjectManager
{
public:
	CObjectManager()
	{
		m_CasheIdx = 0;
		m_pCamera = new CCamera*();
		(*m_pCamera) = nullptr;
	}
	//マネージャーにオブジェクトを追加する
	//戻り値：CGameObject* 追加に成功したオブジェクトのポインタ
	//第一引数：CGameObject* アドレス,bool 残すかどうか = false
	CGameObject* Add(CGameObject* pAdd, bool leave = false);

	//シーンのスタートの後に呼び出される
	void AwakeObject();

	//AwakeObjectの後に呼び出される
	void StartObject();

	//毎フレームシーンの更新よりも先に呼び出される。
	void UpdateObject();

	//麻衣フレームシーンの更新よりも後に呼び出される。
	void LateUpdateObject();

	//シーンの描画の後に呼び出される
	void RenderObject();

	//マネージャーに登録されているオブジェクトのうち
	//残すフラグがないもの以外を全て削除する
	void ReleaseObject();

	void SetCasheIdx(short idx)
	{
		m_CasheIdx = idx;
	}

	//オブジェクト検索関数
	//戻り値：CGameObject* ヒットしたオブジェクトのアドレス、あるいはnullポインタ
	//第一引数：string 検索したいオブジェクトの名前,第二引数：DIMENSION 次元を指定(任意) = DIMENSION::DNON
	CGameObject* FindObject(string name, DIMENSION d = DIMENSION::DNON);

	//カメラセット
	//シーンの一番最初にやっておいた方がいいよ
	void SetCamera(CCamera* c)
	{
		(*m_pCamera) = c;
	}

	static CObjectManager* getInstance();
private:
	//3Dオブジェクトを管理する配列
	vector<C3DObject*> m_3D[SCENECASHE_NUM];

	//2Dオブジェクトを管理する配列
	vector<C2DObject*> m_2D[SCENECASHE_NUM];

	//カメラのポインタの参照
	CCamera** m_pCamera;

	//キャッシュの添え字
	short m_CasheIdx;
	//実体を一つにする。
	static CObjectManager* m_pInstance;
};
#endif //_OBJECTMANAGER_H_