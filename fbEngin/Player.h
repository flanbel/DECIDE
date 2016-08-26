
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "3DObject.h"
#include "Character.h"
#include "Item.h"
#include "Input.h"

#include "Collision.h"
#include "ShowCollision.h"

class CPlayer :public C3DObject
{
public:
	CPlayer(string name = "");
	~CPlayer();

	//初期化を行う関数(一度のみ呼ばれる)
	void Start();

	//更新を行う関数
	void Update();

	//描画を行う関数
	void Render();

	void LateUpdate()override;

	//移動
	void Move();
	//回転
	void Turn();

	//キャラクターへの参照セット
	void SetCharacter(CCharacter* pC)
	{
		m_pChara = pC;
	}

	//アイテムを手に持たせる
	void SetItem(const list<CItem*>& itemlist);
	//アイテムを捨てる関数
	void ThrowAwayItem();
	//近くにあるアイテムを探す
	CItem* NearItem(const list<CItem*>& itemlist);
private:
	//キャラクター情報保持
	CCharacter* m_pChara;
	//持っているアイテム
	CItem* m_pHasItem;
	//入力
	CInputManager m_input;
	//方向
	D3DXVECTOR3 m_dir;

	//あたり判定表示(デバッグ用)
	CShowCollision m_show;

	//ステータス
	STATE m_State;
};

#endif //_PLAYER_H_