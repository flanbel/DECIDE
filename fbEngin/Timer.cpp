#include "Timer.h"

CTimer* CTimer::m_pInstance = new CTimer();


//�����,timeGetTime���g��ver
//���ɂ͍�����\�J�E���^�ƍ�����\���g�����g����,��萸�x�̍������@������(KBCFreamwork)
void CTimer::Initialize()
{
	m_DeltaTime = 0.0f;
	//�p�\�R�����N�����ĉ��~���b�o�߂������擾
	m_beforeTime = timeGetTime();
	m_FPS = 0;
}

void CTimer::Update()
{
	//���̎��Ԃ��擾
	DWORD afterTime = timeGetTime();
	//�O��ƍ��̍����f���^�^�C���ɐݒ�(�~���b��b�ɕϊ�)
	m_DeltaTime = (afterTime - m_beforeTime) / 1000.0f;
	//before���X�V
	m_beforeTime = afterTime;

	static float fps = 0;
	static double time = 0;
	time += m_DeltaTime;

	if (time > 1.0f)
	{
		time = 0;
		//FPS�X�V
		m_FPS = fps;
		fps = 0;
	}
	else
	{
		//60�t���[��
		//16�~���b���x�����(�傫�����)FPS�͏��Ȃ��Ȃ�
		fps += (float)((1.0f / 60.0f) / m_DeltaTime);
	}
}

CTimer* CTimer::getInstance()
{
	//�Ȃ������ꍇ������
	if (m_pInstance == NULL)
	{
		m_pInstance = new CTimer();
	}
	return m_pInstance;
}