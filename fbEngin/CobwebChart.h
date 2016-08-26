
#ifndef _COBWEBCHART_H_
#define _COBWEBCHART_H_

#include "2DObject.h"
#include "2DLine.h"
#include "Text.h"
#include "RenderTarget.h"

enum LINETYPE 
{
	RANK = 0,		//周りのとこ
	ITEM,			//中心から各項目にかけてのライン
	PROT,			//評価点
	LINETYPE_NUM
};

//レーダーチャートクラス
class CCobwebChart:public C2DObject
{
public:
	CCobwebChart(string name = "");
	~CCobwebChart()
	{
		//プロットの頂点解放
		SAFE_DELETE_ARRAY(m_ProtVec);

		for each (CText* var in m_Text)
		{
			SAFE_DELETE(var);
		}
		m_Text.clear();
	}
	//初期化を行う関数(一度のみ呼ばれる)
	void Start();

	//更新を行う関数
	void Update();

	void LateUpdate();

	//描画を行う関数
	void Render();

	//レーダーチャートのベース作成
	//第一引数：short 項目数,第二引数：float 長さ,第三引数：short 最大数値
	void CreateChartBase(const short itemnum, float length,short max);

	//レーダーチャートのプロット作成
	//先にアップデートを呼ぶ必要あり
	void CreateChartProt();

	//プロットの色設定
	//第一引数：D3DCOLOR 色
	void ProtColor(D3DXCOLOR color)
	{
		m_ProtColor = color;
	}

	//ネクストプロット格納
	//第一引数：short[] プロットが入った配列
	void NextProt(short* protArray);

	//プロットの位置をネクストに違づける関数
	//第一引数：float 何フレームで到達させるか
	void UpdateProt(float F);
private:
	//ライン
	C2DLine m_line;
	//線の頂点格納
	vector<D3DXVECTOR2> m_lineVec[LINETYPE::LINETYPE_NUM];
	//ランク数
	short m_MaxRank;
	//項目数
	short m_ItemNum;
	//大きさ
	float m_length;
	//プロットの色
	D3DCOLOR m_ProtColor;
	
	//プロットの頂点は少ないので保持してみる
	D3DXVECTOR2* m_ProtVec;

	//テキストたち格納
	vector<CText*> m_Text;
	//プロットの配列
	vector<float> m_ProtArray;
	//次のプロットの配列
	vector<float> m_NextProtArray;
	//プロットの差
	vector<short> m_DiffProtArray;
	//変更フラグ
	bool m_Chenge;
	//到達
	bool m_Comp;

	//レンダーターゲット
	CRenderTarget m_RenderT;
	//
	TEXTURE m_tex;
};

#endif //_COBWEBCHART_H_