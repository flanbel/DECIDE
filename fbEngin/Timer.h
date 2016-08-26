
#ifndef _TIMER_H_
#define _TIMER_H_

#include <time.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib ")

//���ԊǗ��N���X
class CTimer
{
public:
	CTimer(){};
	void Initialize();
	void Update();
	//�f���^�^�C���擾
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
	//�O��̃A�b�v�f�[�g�ƍ��̃A�b�v�f�[�g�Ƃ̎������i�[(�~���b�P��)
	double m_DeltaTime;
	//�O��̎��Ԋi�[
	DWORD  m_beforeTime;
	//�t���[���p�[�Z�J���h(1�b�Ԃɂł�t���[���̐�)
	float m_FPS;

	static CTimer* m_pInstance;
};
#endif //_TIMER_H_