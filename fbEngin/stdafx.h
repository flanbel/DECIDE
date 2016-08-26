// stdafx.h : �W���̃V�X�e�� �C���N���[�h �t�@�C���̃C���N���[�h �t�@�C���A�܂���
// �Q�Ɖ񐔂������A�����܂�ύX����Ȃ��A�v���W�F�N�g��p�̃C���N���[�h �t�@�C��
// ���L�q���܂��B
//
#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Windows �w�b�_�[����g�p����Ă��Ȃ����������O���܂��B
// Windows �w�b�_�[ �t�@�C��:
#include <windows.h>

// C �����^�C�� �w�b�_�[ �t�@�C��
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>


// TODO: �v���O�����ɕK�v�Ȓǉ��w�b�_�[�������ŎQ�Ƃ��Ă��������B
#include <d3d9.h>
#include <d3dx9.h>

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

#include "GraphicsDevice.h"		//Direct3D�Ǘ��w�b�_�C���N���[�h

#define SAFE_RELEASE(p)			{ if(p) { (p)->Release(); (p) = NULL; } }	//�C���X�^���X�����[�X
#define SAFE_DELETE_ARRAY(p)	{ if(p!=nullptr) { delete[] (p);   (p) = nullptr; } }	//�C���X�^���X�z��폜
#define SAFE_DELETE(p)			{ if(p!=nullptr) { delete (p);     (p) = nullptr; } }	//�C���X�^���X�폜


//////�������牺�ɑ���
#include <map>
#include <string>
#include <vector>
#include <list>
#include <math.h>

using namespace std;
//�V���O���g���̃C���X�^���X���擾����}�N����`
#define SINSTANCE(p) p::getInstance()

//p��J��Ԃ�
#define FOR(p) for(short i = 0;i < (int)p;i++)
//�z��̗v�f�����擾����
#define ARRAY_SIZE(p) (sizeof(p)/sizeof(p[0]))

//�E�B���h�E�T�C�Y
//#define GAME_WINDOW_WIDTH 1366
//#define GAME_WINDOW_HEIGHT 768

//�E�B���h�E�̃N���C�A���g�G���A�̃T�C�Y
#define GAME_CLIENT_WIDTH 1280
#define GAME_CLIENT_HEIGHT 720

//�V�[���̃L���b�V���̐�,1���ƃL���b�V���@�\�Ȃ�
#define SCENECASHE_NUM 2

#define VECTOR3_ZERO D3DXVECTOR3(0.0f, 0.0f, 0.0f)
#define VECTOR3_ONE D3DXVECTOR3(1.0f, 1.0f, 1.0f)

//�L�[��`
#define VK_A 0x41
#define VK_B 0x42
#define VK_C 0x43
#define VK_D 0x44
#define VK_E 0x45
#define VK_F 0x46
#define VK_G 0x47
#define VK_H 0x48
#define VK_I 0x49
#define VK_J 0x4A
#define VK_K 0x4B
#define VK_L 0x4C
#define VK_M 0x4D
#define VK_N 0x4E
#define VK_O 0x4F
#define VK_P 0x50
#define VK_Q 0x51
#define VK_R 0x52
#define VK_S 0x53
#define VK_T 0x54
#define VK_U 0x55
#define VK_V 0x56
#define VK_W 0x57
#define VK_X 0x58
#define VK_Y 0x59
#define VK_Z 0x5A

//�O���[�o���ϐ�
//�E�B���h�E�̍��W
extern RECT WINDOW_POS;
//�N���C�A���g�G���A�̏c�Ɖ��̃T�C�Y
extern RECT CLIENT_RECT;

//�f�o�b�O���[�h�t���O
extern bool g_DebugMode;

#include "support.h"
#include "Vector.h"
#include "Timer.h"