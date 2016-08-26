
#ifndef _TIMER_H_
#define _TIMER_H_

#include <time.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib ")

//時間管理クラス
class CTimer
{
public:
	CTimer(){};
	void Initialize();
	void Update();
	//デルタタイム取得
	double DeltaTime()
	{
		return m_DeltaTime;
	}

	float FPS()
	{
		return m_FPS;
	}

	static CTimer* getInstance();
private:
	//前回のアップデートと今のアップデートとの時差を格納(ミリ秒単位)
	double m_DeltaTime;
	//前回の時間格納
	DWORD  m_beforeTime;
	//フレームパーセカンド(1秒間にでるフレームの数)
	float m_FPS;

	static CTimer* m_pInstance;
};
#endif //_TIMER_H_