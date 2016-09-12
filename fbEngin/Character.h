
#ifndef _CHARACTER_H_
#define _CHARACTER_H_

#include "SkinModelData.h"
#include "Animation.h"
#include "SkinModelManager.h"

//キャラクターのステータス
struct STATE
{
	short hp;			//体力
	short power;		//力
	short defense;		//防御
	short skill;		//技量
	short speed;		//スピード

	STATE::STATE()
	{
		hp = 0;
		power = 0;
		defense = 0;
		skill = 0;
		speed = 0;	
	}

	STATE::STATE(short h,short p,short d,short s,short sp)
	{
		hp = h;
		power = p;
		defense = d;
		skill = s;
		speed = sp;
	}
};

enum STATE_PATTERN		//キャラクターの行動パターン（仮）
{
	STAY,		//待機
	FIGHTING,	//ファイティングポーズ
	WALK,		//歩き
	RUN,		//走り
	PUNCH,		//パンチ
	KICK,		//キック
	ITEM_BRANDISH	//アイテムを振る
};

//キャラクターの基底クラス
//キャラクターのデータ(情報)を扱う
//CharacterInfoのほうが良かったかも
class CCharacter
{
public:
	CCharacter()
	{
		pHand = nullptr;
		m_AnimationSpeed = 1.0;
		m_Pattern = STATE_PATTERN::STAY;
	};

	~CCharacter()
	{
	}

	//初期化を行う関数(一度のみ呼ばれる)
	virtual void Start() = 0;

	//更新を行う関数
	virtual void Update() = 0;

	//描画を行う関数
	virtual void Render() = 0;

	//モデルデータへアクセスするためのポインタを返す
	CSkinModelData* GetModelData()
	{
		return &m_ModelData;
	}
	//手のフレーム取得
	D3DXFRAME_DERIVED* GetHand()
	{
		if (pHand)
			return pHand;
		else
			return nullptr;
	}
	//キャラクターの名前取得
	WCHAR* GetCharaName()
	{
		return m_CharacterName;
	}

	STATE GetState()
	{
		return m_CharaState;
	}

	//アニメーション再生
	//第一引数：int アニメーションの添え字
	//第二引数：float 保管時間
	void PlayAnimation(int animationSetIndex, float interpolateTime)
	{
		m_Animation.PlayAnimation(animationSetIndex, interpolateTime);
	}

	void SetPattern(STATE_PATTERN pat)
	{
		m_Pattern = pat;
	}
protected:
	//キャラクターのモデルデータの値
	CSkinModelData m_ModelData;
	//アニメーション管理
	CAnimation m_Animation;
	//各オブジェクトのアニメーションコントローラー
	ID3DXAnimationController* m_pAnime;
	//アニメーション再生スピード倍率
	float m_AnimationSpeed;

	//キャラクターの名前
	WCHAR* m_CharacterName;
	//手のフレームへのポインタ
	D3DXFRAME_DERIVED* pHand;
	//ステータス
	STATE m_CharaState;
	//パターン
	STATE_PATTERN m_Pattern;
};

#endif //_CHARACTER_H_