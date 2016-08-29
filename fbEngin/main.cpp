// SpritePG.cpp : �A�v���P�[�V�����̃G���g�� �|�C���g���`���܂��B
//
#pragma once

#include "main.h"
//�}�l�[�W���[
#include "SceneManager.h"
//�V�[��
#include "TestScene.h"
#include "TitleScene.h"
#include "MenuScene.h"
#include "CharaSelectScene.h"
#include "BattleScene.h"
//�I�u�W�F�N�g
#include "Timer.h"
#include "DInput.h"

#include "Text.h"

#define MAX_LOADSTRING 100

// �O���[�o���ϐ�:
HINSTANCE hInst;								// ���݂̃C���^�[�t�F�C�X
TCHAR szTitle[MAX_LOADSTRING];					// �^�C�g�� �o�[�̃e�L�X�g
TCHAR szWindowClass[MAX_LOADSTRING];			// ���C�� �E�B���h�E �N���X��

CGraphicsDevice g_graphicsDevice;
HWND g_hWnd;									//�n���h���̒�`

// ���̃R�[�h ���W���[���Ɋ܂܂��֐��̐錾��]�����܂�:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
void Initialize();
void Update();
void Draw();

//�V������`����Ƃ��͂��̕ӂ�

//�O���[�o���ϐ�
//�E�B���h�E�̍��W
RECT WINDOW_POS;
//�N���C�A���g�G���A�̏c�Ɖ��̃T�C�Y
RECT CLIENT_RECT;
//
bool g_DebugMode = false;
//FPS��`�悷��
CText* g_FPS;

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: �����ɃR�[�h��}�����Ă��������B
	MSG msg;
	HACCEL hAccelTable;

	// �O���[�o������������������Ă��܂��B
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_FBENGIN, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// �A�v���P�[�V�����̏����������s���܂�:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_FBENGIN));

	//�������Ƃ�

	//�E�B���h�E�T�C�Y
	GetWindowRect(g_hWnd, &WINDOW_POS);
	//�N���C�A���g�G���A�T�C�Y
	GetClientRect(g_hWnd, &CLIENT_RECT);

	//Dinput������
	CDirectInput input;
	input.Initialize(hInstance);
	input.MouseInit(g_hWnd);

	Initialize();

	// ���C�� ���b�Z�[�W ���[�v:
	do
	{
		//���b�Z�[�W�����݂��邩����
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);		//���z�L�[���b�Z�[�W�𕶎����b�Z�[�W�ɕϊ�
			DispatchMessage(&msg);		//���b�Z�[�W���E�B���h�E�v���V�[�W���ɑ��o
		}
		else
		{
			//�E�B���h�E�T�C�Y
			GetWindowRect(g_hWnd, &WINDOW_POS);
			//�N���C�A���g�G���A�T�C�Y
			GetClientRect(g_hWnd, &CLIENT_RECT);

			Update();
			Draw();
		}

	} while (msg.message != WM_QUIT);

	return (int) msg.wParam;
}



//
//  �֐�: MyRegisterClass()
//
//  �ړI: �E�B���h�E �N���X��o�^���܂��B
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_FBENGIN));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_FBENGIN);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   �֐�: InitInstance(HINSTANCE, int)
//
//   �ړI: �C���X�^���X �n���h����ۑ����āA���C�� �E�B���h�E���쐬���܂��B
//
//   �R�����g:
//
//        ���̊֐��ŁA�O���[�o���ϐ��ŃC���X�^���X �n���h����ۑ����A
//        ���C�� �v���O���� �E�B���h�E���쐬����ѕ\�����܂��B
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // �O���[�o���ϐ��ɃC���X�^���X�������i�[���܂��B

   //�N���C�A���g�G���A����E�B���h�E�T�C�Y�t�Z�֐��炵��
   /*CLIENT_RECT.left = 30;
   CLIENT_RECT.top = 50;
   CLIENT_RECT.right = GAME_CLIENT_WIDTH;
   CLIENT_RECT.bottom = GAME_CLIENT_HEIGHT;

   AdjustWindowRect(&CLIENT_RECT, WS_OVERLAPPEDWINDOW, 1);*/

   //�n���h���쐬
   g_hWnd = CreateWindow(szWindowClass, "fbEngin", (WS_TILEDWINDOW),
	   CW_USEDEFAULT, 0, GAME_CLIENT_WIDTH, GAME_CLIENT_HEIGHT, NULL, NULL, hInstance, NULL);

   D3DXVECTOR2 WindowSize;
   D3DXVECTOR2 ClientSize;
   D3DXVECTOR2 Diff;

   //�E�B���h�E�T�C�Y
   GetWindowRect(g_hWnd, &WINDOW_POS);
   WindowSize.x = (float)(WINDOW_POS.right - WINDOW_POS.left);
   WindowSize.y = (float)(WINDOW_POS.bottom - WINDOW_POS.top);
   //�N���C�A���g�G���A�T�C�Y
   GetClientRect(g_hWnd, &CLIENT_RECT);
   ClientSize.x = (float)(CLIENT_RECT.right - CLIENT_RECT.left);
   ClientSize.y = (float)(CLIENT_RECT.bottom - CLIENT_RECT.top);
   //�������߂�
   Diff.x = WindowSize.x - ClientSize.x;
   Diff.y = WindowSize.y - ClientSize.y;

   SetWindowPos(g_hWnd, HWND_TOP, 0, 0, GAME_CLIENT_WIDTH + (int)Diff.x, GAME_CLIENT_HEIGHT + (int)Diff.y, ( SWP_NOZORDER));

   if (!g_hWnd)
   {
      return FALSE;
   }

   ShowWindow(g_hWnd, nCmdShow);
   UpdateWindow(g_hWnd);

   return TRUE;
}

//
//  �֐�: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  �ړI:    ���C�� �E�B���h�E�̃��b�Z�[�W���������܂��B
//
//  WM_COMMAND	- �A�v���P�[�V���� ���j���[�̏���
//  WM_PAINT	- ���C�� �E�B���h�E�̕`��
//  WM_DESTROY	- ���~���b�Z�[�W��\�����Ė߂�
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// �I�����ꂽ���j���[�̉��:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO: �`��R�[�h�������ɒǉ����Ă�������...
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
		//�L�[�̉�������
	case WM_KEYDOWN:
		//���̃L�[���H
		switch (wParam)
		{
			//�G�X�P�[�v�L�[
		case VK_ESCAPE:
			//�I��
			PostQuitMessage(0);
			break;
			//F3
		case VK_F3:
			//�f�o�b�O���[�h�ؑ�
			g_DebugMode ? g_DebugMode = false : g_DebugMode = true;
			break;
		}
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// �o�[�W�������{�b�N�X�̃��b�Z�[�W �n���h���[�ł��B
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
		//[�o�[�W�������]�������ꂽ��
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;
		//�o�[�W����������[OK]�������ꂽ��
	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

void Initialize()
{
	//�������[���[�N���m��(�����?)
	//::_CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CRTDBG_ALLOC_MEM_DF);

	//�f�o�C�X������
	graphicsDevice().InitD3d(g_hWnd);

	SINSTANCE(CTimer)->Initialize();

	g_FPS = new CText("FPS");

	g_FPS->Start();
	//
	g_FPS->SetColor(255, 180, 0);
	//���W����
	g_FPS->Transform()->LocalPosition = D3DXVECTOR3(1200.0f, 690.0f, 0.0f);

	//�V�[���ǉ�
	//�ǉ��������̓Y�����ɂȂ�
	{
		//�e�X�g�V�[���ǉ�
		SINSTANCE(CSceneManager)->Add(new CTestScene);
		//�^�C�g���V�[���ǉ�
		SINSTANCE(CSceneManager)->Add(new CTitleScene);
		//���j���[�V�[���ǉ�
		SINSTANCE(CSceneManager)->Add(new CMenuScene);
		//�L�����N�^�[�I���V�[���ǉ�
		SINSTANCE(CSceneManager)->Add(new CCharaSelectScene);
		//�퓬�V�[���ǉ�
		SINSTANCE(CSceneManager)->Add(new CBattleScene);
	}
	//�V�[���؂�ւ�
	SINSTANCE(CSceneManager)->ChangeScene(SCENE::TITLE);
}

void Update()
{
	SINSTANCE(CTimer)->Update();

	//FPS�擾
	float f = SINSTANCE(CTimer)->FPS();

	WCHAR FPS[20] = L"FPS:";
	WCHAR fps[10] = L"0.0";

	Support::FloatToWchar(fps,f);
	Support::LinkingWchar(FPS, fps);

	g_FPS->Update();
	g_FPS->Createfont(FPS);

	//�V�[���X�V
	SINSTANCE(CSceneManager)->UpdateScene();
}

void Draw()
{
	//��ʂ𔒐F�ŃN���A
	(*graphicsDevice()).Clear(0,
		NULL,
		D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		D3DCOLOR_XRGB(255, 255, 255),
		1.0f,
		0);

	//�V�[���J�n
	if (SUCCEEDED((*graphicsDevice()).BeginScene()))
	{
		//�V�[���`��
		SINSTANCE(CSceneManager)->DrawScene();
		g_FPS->Render();
		
		//�V�[���I��
		(*graphicsDevice()).EndScene();
	}
	(*graphicsDevice()).Present(NULL, NULL, NULL, NULL);
}
