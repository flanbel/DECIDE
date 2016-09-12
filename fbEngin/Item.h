
#ifndef _ITEM_H_
#define _ITEM_H_

#include "3DObject.h"
#include "SkinModelData.h"
#include "SkinModelManager.h"

//アイテムの基底クラス
class CItem : public C3DObject
{
public:
	CItem(string name = "") :C3DObject(name)
	{
		m_isHas = false;
		m_life = 30.0f;
	}

	//初期化を行う関数(一度のみ呼ばれる)
	virtual void Start()override = 0;

	//更新を行う関数
	virtual void Update()override = 0;

	//更新の後に呼び出される関数
	virtual void LateUpdate()override = 0;

	//描画を行う関数
	virtual void Render()override = 0;

	//アイテム共通アップデート
	//死んでいるならtrueを返す
	void ItemUpdata();

	CSkinModelData GetModelData()
	{
		return m_ModelData;
	}

	//捨てる
	void Throw(const CTransform& t)
	{
		m_Transform.LocalPosition = t.LocalPosition;
		//親を外す
		m_model.SetParent(nullptr);
		//持たれてない
		m_isHas = false;
	}

	void Has()
	{
		m_isHas = true;
	}
protected:
	//モデルデータ
	CSkinModelData m_ModelData;
	//持たれているかどうか
	bool m_isHas;
	//寿命
	float m_life;
};

#endif //_ITEM_H_