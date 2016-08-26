
#ifndef _GAMEOBJECT_H_
#define _GAMEOBJECT_H_

#include "Transform.h"

enum DIMENSION
{
	DNON = 0,		//指定なし
	D2 = 2,		//二次元であることを示す
	D3 = 3		//三次元であることを示す
};

//オブジェクトの祖
class CGameObject
{
public:
	CGameObject(string name = "");

	virtual ~CGameObject()
	{
		m_Transform.Release();
	}
	//Start関数よりも先に呼ばれる
	//純粋仮想関数ではないので絶対オーバーライドしなくてもいい
	virtual void Awake(){};

	//初期化を行う純粋仮想関数
	virtual void Start() = 0;

	//更新を行う純粋仮想関数
	virtual void Update() = 0;

	//更新の後に呼び出される関数
	//純粋仮想関数ではないので絶対オーバーライドしなくてもいい
	virtual void LateUpdate(){};

	//描画を行う純粋仮想関数
	virtual void Render() = 0;

	//オブジェクトの名前を取得する関数
	//戻り値：string オブジェクトの名前
	string name()
	{
		return m_Name;
	}

	//オブジェクトの名前を設定する関数
	void name(string n)
	{
		m_Name = n;
	}

	//トランスフォーム取得
	CTransform *Transform()
	{
		return &m_Transform;
	}

	//GameObject解放
	void Release()
	{
		
	}

	//オブジェクトのアクティブフラグを設定する　セッター
	void Active(bool act);

	//アクティブかどうか取得　ゲッター
	bool Active()
	{
		return m_Active;
	}

	//残すフラグ設定　セッター
	void Leave(bool leave)
	{
		m_Leave = leave;
	}

	//残すフラグ取得　ゲッター
	bool Leave()
	{
		return m_Leave;
	}

	//次元設定　セッター
	DIMENSION Dimension()
	{
		return m_Dimension;
	}
protected:
	bool m_Active;	//アクティブでないオブジェクトは描画もアップデートもされない
	string m_Name;	//オブジェクトの名前
	CTransform m_Transform;//トランスフォーム
	//オブジェクトマネージャーに残すフラグ
	bool m_Leave;
	DIMENSION m_Dimension;	//自分の次元を示す(2Dか3Dか)
};
#endif //_GAMEOBJECT_H_