#include "CobwebChart.h"

CCobwebChart::CCobwebChart(string name) :C2DObject(name)
{
	m_MaxRank = 0;
	m_ItemNum = 0;
	m_length = 0;
	m_line.SetWidth(1.0);
	m_ProtColor = D3DCOLOR_ARGB(255, 255, 0, 0);
	m_Chenge = false;
	m_Comp = true;

	m_ProtVec = nullptr;
}

void CCobwebChart::Start()
{
	//テクスチャ作成
	m_RenderT.CreateRenderTarget(&m_tex, 256, 256);
}

void CCobwebChart::Update()
{
	m_Transform.UpdateTransform();
}

void CCobwebChart::LateUpdate()
{
	for each (CText* t in m_Text)
	{
		t->Update();
	}
}

void CCobwebChart::Render()
{
	//テクスチャがないときのみ
	//if (m_Sprite.GetTex().pTexture == nullptr)
	{
		//テクスチャ設定
		//m_Sprite.SetTexture(m_tex);
		//切り替え
		//m_RenderT.SetRenderTarget(0);

		if (m_lineVec[LINETYPE::RANK].size() > 0)
		{

			//項目数
			short size = m_ItemNum;
			//段階数ループ
			for (short n = 1; n <= m_MaxRank; n++)
			{
				//一つ多く確保
				const short vecnum = size + 1;
				D3DXVECTOR2* vec = new D3DXVECTOR2[vecnum];

				short j = 0;
				for (short i = size * (n - 1); i < size * n; i++, j++)
				{
					vec[j] = m_lineVec[LINETYPE::RANK][i];
				}
				//最後に最初の頂点を入れて繋げる
				vec[j] = m_lineVec[LINETYPE::RANK][size * (n - 1)];

				//色変更
				D3DCOLOR color;
				(n == m_MaxRank || (n % 5) == 0) ? color = D3DCOLOR_ARGB(255, 0, 255, 0) : color = D3DCOLOR_ARGB(100, 0, 255, 0);

				m_line.DrawLine(vec, vecnum, color);
				//解放
				SAFE_DELETE_ARRAY(vec);
			}
		}

		if (m_lineVec[LINETYPE::ITEM].size() > 0)
		{

			short size = m_lineVec[LINETYPE::ITEM].size();
			const short vecnum = size + 1;
			D3DXVECTOR2* vec = new D3DXVECTOR2[vecnum];
			short i;
			for (i = 0; i < size; i++)
			{
				vec[i] = m_lineVec[LINETYPE::ITEM][i];
			}
			vec[i] = m_lineVec[LINETYPE::ITEM][0];
			//色変更
			m_line.DrawLine(vec, vecnum, D3DCOLOR_ARGB(255, 0, 255, 100));
			//解放
			SAFE_DELETE_ARRAY(vec);
		}

		//元に戻す
		//m_RenderT.BeforeRenderTarget();

		//画像を作ってしまえばもう必要ないのでクリア
		//m_lineVec[LINETYPE::RANK].clear();
		//m_lineVec[LINETYPE::ITEM].clear();
	}

	//レーダーチャート描画
	//m_Sprite.Render(m_Transform);

	if (m_lineVec[LINETYPE::PROT].size() > 0)
	{
		short size = m_ItemNum + 1;
		short i;
		for (i = 0; i < m_ItemNum; i++)
		{
			m_ProtVec[i] = m_lineVec[LINETYPE::PROT][i];
		}
		m_ProtVec[i] = m_lineVec[LINETYPE::PROT][0];

		m_line.SetWidth(2.0f);
		m_line.DrawLine(m_ProtVec, size, m_ProtColor);
		m_line.SetWidth(1.0f);
	}

	//テキスト描画
	for each (CText* t in m_Text)
	{
		t->Render();
	}
}

void CCobwebChart::CreateChartBase(const short itemnum, float length, short max)
{
	//伸びる方向を反転(+方向だと下に伸びてしまうため)
	length *= -1;
	//保持
	m_MaxRank = max;
	m_ItemNum = itemnum;
	m_length = length;

	//多い場合削除
	if ((short)m_Text.size() > m_ItemNum)
	{
		vector<CText*>::iterator it = m_Text.begin();
		FOR(m_ItemNum)
		{
			it++;
		}
		while (it != m_Text.end())
		{
			SAFE_DELETE(*it);
			m_Text.erase(it);
		}
	}

	//たぶん要らないだろうけど一応
	if (m_lineVec[LINETYPE::RANK].size() > 0)
	{
		m_lineVec[LINETYPE::RANK].clear();
	}

	//間隔
	float ang = 360.0f / m_ItemNum;
	float len = m_length / (float)m_MaxRank;

	//LINETYPE::RANK
	{
		//段階数ループ
		for (short n = 1; n <= m_MaxRank; n++)
		{
			//項目数ループ
			//各頂点の座標を求める
			FOR(m_ItemNum)
			{
				float theta = D3DXToRadian(ang * i);
				float x = 0.0f, y = len * n;
				/*
				ベクトルの回転式?
				x' = x * cosθ - y * sinθ
				y' = x * sinθ + y * cosθ
				*/
				D3DXVECTOR2 vec;
				vec.x = x * cos(theta) - y * sin(theta);
				vec.y = x * sin(theta) + y * cos(theta);

				vec.x += m_Transform.Position.x;
				vec.y += m_Transform.Position.y;

				//頂点格納
				m_lineVec[LINETYPE::RANK].push_back(vec);
			}
		}
	}

	//たぶん要らないだろうけど一応
	if (m_lineVec[LINETYPE::ITEM].size() > 0)
	{
		m_lineVec[LINETYPE::ITEM].clear();
	}

	//LINETYPE::ITEM
	{
		D3DXVECTOR2 mypos = { m_Transform.Position.x, m_Transform.Position.y };
		//項目数ループ
		//各頂点の座標を求める
		FOR(m_ItemNum)
		{
			//自分のポジション格納
			m_lineVec[LINETYPE::ITEM].push_back(mypos);
			float theta = D3DXToRadian(ang * i);
			//項目までなのでマックスサイズ(元のサイズ)
			float x = 0.0f, y = m_length;
			/*
			ベクトルの回転式?
			x' = x * cosθ - y * sinθ
			y' = x * sinθ + y * cosθ
			*/
			D3DXVECTOR2 vec;
			vec.x = x * cos(theta) - y * sin(theta);
			vec.y = x * sin(theta) + y * cos(theta);

			vec += mypos;

			//頂点格納
			m_lineVec[LINETYPE::ITEM].push_back(vec);
		}
	}

	if (m_ProtVec != nullptr)
	{
		//登録されていたなら解放
		SAFE_DELETE_ARRAY(m_ProtVec);
	}
	//項目+1個分配列を確保
	m_ProtVec = new D3DXVECTOR2[m_ItemNum + 1];

	//もしプロットが項目数より少ないなら勝手に初期化
	if ((int)m_ProtArray.size() < m_ItemNum)
	{
		//差
		short Diff = m_ItemNum - m_ProtArray.size();
		//差分だけ追加
		FOR(Diff)
		{
			m_ProtArray.push_back(0);
			m_NextProtArray.push_back(0);
		}
	}
}

void CCobwebChart::CreateChartProt()
{
	//ポインタが確保されているなら
	if (m_lineVec[LINETYPE::PROT].size() > 0)
	{
		m_lineVec[LINETYPE::PROT].clear();
	}

	//1項目あたりの角度
	float ang = 360.0f / m_ItemNum;
	//1段階あたりの長さ計算
	float len = m_length / m_MaxRank;
	//評価点受け取り
	short rank;
	//プロット作成
	FOR(m_ItemNum)
	{
		//不正な数字
		if (i >= (int)m_ProtArray.size())
		{
			rank = 0;
		}
		else
		{
			rank = (short)m_ProtArray[i];
		}

		//角度算出
		float theta = D3DXToRadian(ang * i);
		float x = 0.0f, y = len * rank;
		/*
		ベクトルの回転式?
		x' = x * cosθ - y * sinθ
		y' = x * sinθ + y * cosθ
		*/
		D3DXVECTOR2 vec;
		vec.x = x * cos(theta) - y * sin(theta);
		vec.y = x * sin(theta) + y * cos(theta);

		vec.x += m_Transform.Position.x;
		vec.y += m_Transform.Position.y;

		m_lineVec[LINETYPE::PROT].push_back(vec);

		//最大
		y = m_length;
		vec.x = x * cos(theta) - y * sin(theta);
		vec.y = x * sin(theta) + y * cos(theta);

		vec.x += m_Transform.Position.x;
		vec.y += m_Transform.Position.y;
	}
}

//ネクストプロット格納
void CCobwebChart::NextProt(short* protArray)
{
	m_NextProtArray.clear();
	FOR(m_ItemNum)
	{
		//不正な数字 || メモリがない場合とかも
		//0にする
		if (protArray[i] < 0)
		{
			m_NextProtArray.push_back(0);
		}
		else
		{
			m_NextProtArray.push_back(protArray[i]);
		}
	}
	//変更フラグをtrueに
	m_Chenge = true;
	m_Comp = false;
}

//プロットの位置をネクストに違づける関数
//第一引数：float 何フレームで到達させるか
void CCobwebChart::UpdateProt(float F)
{
	//変更されているなら差を取得
	if (m_Chenge)
	{
		m_DiffProtArray.clear();
		FOR(m_ItemNum)
		{
			short diff = short(m_NextProtArray[i] - m_ProtArray[i]);
			m_DiffProtArray.push_back(diff);
		}
		m_Chenge = false;
	}

	//到達していない間のみ更新
	if (!m_Comp)
	{
		FOR(m_ItemNum)
		{
			//ネクストに近づける
			m_ProtArray[i] += (float)m_DiffProtArray[i] * (1.0f / F);
		}

		//ある程度近くなったら
		if (fabsf(m_NextProtArray[0] - m_ProtArray[0]) < 0.5f)
		{

			//1項目あたりの角度
			float ang = 360.0f / m_ItemNum;
			//1段階あたりの長さ計算
			float len = m_length / m_MaxRank;

			FOR(m_ItemNum)
			{
				//代入でぴったりセットする
				m_ProtArray[i] = m_NextProtArray[i];

				//項目数よりテキスト数が少ないなら生成
				if ((short)m_Text.size() < m_ItemNum)
				{
					//テキスト作成
					CText* text = new CText();
					text->Start();
					text->SetFontSize(30);
					text->SetColor(255, 180, 0);

					//テキストの場所を決める
					{
						//角度算出
						float theta = D3DXToRadian(ang * i);
						float x = 0.0f;

						//float y = len * m_ProtArray[i];	//ランクの長さ
						float y = m_length;					//最大の長さ

						D3DXVECTOR2 vec;
						vec.x = x * cos(theta) - y * sin(theta);
						vec.y = x * sin(theta) + y * cos(theta);

						vec.x += m_Transform.Position.x;
						vec.y += m_Transform.Position.y;

						text->Transform()->LocalPosition = D3DXVECTOR3(vec.x, vec.y, 0.0f);
					}

					m_Text.push_back(text);
				}

				//テキストの数字更新
				{
					//適当に確保
					WCHAR num[3];
					Support::IntToWchar(num, (int)m_ProtArray[i]);
					m_Text[i]->Createfont(num);
				}
			}
			m_Comp = true;
		}
	}
}