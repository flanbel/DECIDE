
#ifndef _SHOWCHARACTER_H
#define _SHOWCHARACTER_H

#include "3DObject.h"
#include "Character.h"

//キャラクターを表示するクラス
class CShowCharacter :public C3DObject
{
public:
	CShowCharacter(string name = "");
	//初期化を行う関数(一度のみ呼ばれる)
	void Start();

	//更新を行う関数
	void Update();

	//描画を行う関数
	void Render();

	//キャラクターセット
	void SetChara(CCharacter* pC)
	{
		m_pChara = pC;
		if (m_pChara != nullptr)
		{
			//モデルデータセット
			m_model.SetModelData(m_pChara->GetModelData());
			
			y = 0;
		}
	}
private:
	//キャラクターへの参照
	CCharacter* m_pChara;
	//
	float y;
};

#endif //_SHOWCHARACTER_H