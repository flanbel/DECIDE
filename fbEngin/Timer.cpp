#include "Timer.h"

CTimer* CTimer::m_pInstance = new CTimer();


//これは,timeGetTimeを使うver
//他には高分解能カウンタと高分解能周波数を使った,より精度の高い方法もある(KBCFreamwork)
void CTimer::Initialize()
{
	m_DeltaTime = 0.0f;
	//パソコンを起動して何ミリ秒経過したか取得
	m_beforeTime = timeGetTime();
	m_FPS = 0;
}

void CTimer::Update()
{
	//今の時間を取得
	DWORD afterTime = timeGetTime();
	//前回と今の差をデルタタイムに設定(ミリ秒を秒に変換)
	m_DeltaTime = (afterTime - m_beforeTime) / 1000.0f;
	//beforeを更新
	m_beforeTime = afterTime;

	static float fps = 0;
	static double time = 0;
	time += m_DeltaTime;

	if (time > 1.0f)
	{
		time = 0;
		//FPS更新
		m_FPS = fps;
		fps = 0;
	}
	else
	{
		//60フレーム
		//16ミリ秒より遅ければ(大きければ)FPSは少なくなる
		fps += (float)((1.0f / 60.0f) / m_DeltaTime);
	}
}

CTimer* CTimer::getInstance()
{
	//なかった場合初期化
	if (m_pInstance == NULL)
	{
		m_pInstance = new CTimer();
	}
	return m_pInstance;
}