// SpritePG.cpp : アプリケーションのエントリ ポイントを定義します。
//
#pragma once

#include "main.h"
//マネージャー
#include "SceneManager.h"
//シーン
#include "TestScene.h"
#include "TitleScene.h"
#include "MenuScene.h"
#include "CharaSelectScene.h"
#include "BattleScene.h"
//オブジェクト
#include "Timer.h"
#include "DInput.h"

#include "Text.h"

#define MAX_LOADSTRING 100

// グローバル変数:
HINSTANCE hInst;								// 現在のインターフェイス
TCHAR szTitle[MAX_LOADSTRING];					// タイトル バーのテキスト
TCHAR szWindowClass[MAX_LOADSTRING];			// メイン ウィンドウ クラス名

CGraphicsDevice g_graphicsDevice;
HWND g_hWnd;									//ハンドルの定義

// このコード モジュールに含まれる関数の宣言を転送します:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
void Initialize();
void Update();
void Draw();

//新しく定義するときはこの辺に

//グローバル変数
//ウィンドウの座標
RECT WINDOW_POS;
//クライアントエリアの縦と横のサイズ
RECT CLIENT_RECT;
//
bool g_DebugMode = false;
//FPSを描画する
CText* g_FPS;

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: ここにコードを挿入してください。
	MSG msg;
	HACCEL hAccelTable;

	// グローバル文字列を初期化しています。
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_FBENGIN, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// アプリケーションの初期化を実行します:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_FBENGIN));

	//初期化とか

	//ウィンドウサイズ
	GetWindowRect(g_hWnd, &WINDOW_POS);
	//クライアントエリアサイズ
	GetClientRect(g_hWnd, &CLIENT_RECT);

	//Dinput初期化
	CDirectInput input;
	input.Initialize(hInstance);
	input.MouseInit(g_hWnd);

	Initialize();

	// メイン メッセージ ループ:
	do
	{
		//メッセージが存在するか検証
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);		//仮想キーメッセージを文字メッセージに変換
			DispatchMessage(&msg);		//メッセージをウィンドウプロシージャに送出
		}
		else
		{
			//ウィンドウサイズ
			GetWindowRect(g_hWnd, &WINDOW_POS);
			//クライアントエリアサイズ
			GetClientRect(g_hWnd, &CLIENT_RECT);

			Update();
			Draw();
		}

	} while (msg.message != WM_QUIT);

	return (int) msg.wParam;
}



//
//  関数: MyRegisterClass()
//
//  目的: ウィンドウ クラスを登録します。
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
//   関数: InitInstance(HINSTANCE, int)
//
//   目的: インスタンス ハンドルを保存して、メイン ウィンドウを作成します。
//
//   コメント:
//
//        この関数で、グローバル変数でインスタンス ハンドルを保存し、
//        メイン プログラム ウィンドウを作成および表示します。
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // グローバル変数にインスタンス処理を格納します。

   //クライアントエリアからウィンドウサイズ逆算関数らしい
   /*CLIENT_RECT.left = 30;
   CLIENT_RECT.top = 50;
   CLIENT_RECT.right = GAME_CLIENT_WIDTH;
   CLIENT_RECT.bottom = GAME_CLIENT_HEIGHT;

   AdjustWindowRect(&CLIENT_RECT, WS_OVERLAPPEDWINDOW, 1);*/

   //ハンドル作成
   g_hWnd = CreateWindow(szWindowClass, "fbEngin", (WS_TILEDWINDOW),
	   CW_USEDEFAULT, 0, GAME_CLIENT_WIDTH, GAME_CLIENT_HEIGHT, NULL, NULL, hInstance, NULL);

   D3DXVECTOR2 WindowSize;
   D3DXVECTOR2 ClientSize;
   D3DXVECTOR2 Diff;

   //ウィンドウサイズ
   GetWindowRect(g_hWnd, &WINDOW_POS);
   WindowSize.x = (float)(WINDOW_POS.right - WINDOW_POS.left);
   WindowSize.y = (float)(WINDOW_POS.bottom - WINDOW_POS.top);
   //クライアントエリアサイズ
   GetClientRect(g_hWnd, &CLIENT_RECT);
   ClientSize.x = (float)(CLIENT_RECT.right - CLIENT_RECT.left);
   ClientSize.y = (float)(CLIENT_RECT.bottom - CLIENT_RECT.top);
   //差を求める
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
//  関数: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目的:    メイン ウィンドウのメッセージを処理します。
//
//  WM_COMMAND	- アプリケーション メニューの処理
//  WM_PAINT	- メイン ウィンドウの描画
//  WM_DESTROY	- 中止メッセージを表示して戻る
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
		// 選択されたメニューの解析:
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
		// TODO: 描画コードをここに追加してください...
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
		//キーの押下判定
	case WM_KEYDOWN:
		//何のキーか？
		switch (wParam)
		{
			//エスケープキー
		case VK_ESCAPE:
			//終了
			PostQuitMessage(0);
			break;
			//F3
		case VK_F3:
			//デバッグモード切替
			g_DebugMode ? g_DebugMode = false : g_DebugMode = true;
			break;
		}
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// バージョン情報ボックスのメッセージ ハンドラーです。
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
		//[バージョン情報]が押された時
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;
		//バージョン情報内の[OK]が押された時
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
	//メモリーリーク検知の(お守り?)
	//::_CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CRTDBG_ALLOC_MEM_DF);

	//デバイス初期化
	graphicsDevice().InitD3d(g_hWnd);

	SINSTANCE(CTimer)->Initialize();

	g_FPS = new CText("FPS");

	g_FPS->Start();
	//
	g_FPS->SetColor(255, 180, 0);
	//座標調整
	g_FPS->Transform()->LocalPosition = D3DXVECTOR3(1200.0f, 690.0f, 0.0f);

	//シーン追加
	//追加した順の添え字になる
	{
		//テストシーン追加
		SINSTANCE(CSceneManager)->Add(new CTestScene);
		//タイトルシーン追加
		SINSTANCE(CSceneManager)->Add(new CTitleScene);
		//メニューシーン追加
		SINSTANCE(CSceneManager)->Add(new CMenuScene);
		//キャラクター選択シーン追加
		SINSTANCE(CSceneManager)->Add(new CCharaSelectScene);
		//戦闘シーン追加
		SINSTANCE(CSceneManager)->Add(new CBattleScene);
	}
	//シーン切り替え
	SINSTANCE(CSceneManager)->ChangeScene(SCENE::TITLE);
}

void Update()
{
	SINSTANCE(CTimer)->Update();

	//FPS取得
	float f = SINSTANCE(CTimer)->FPS();

	WCHAR FPS[20] = L"FPS:";
	WCHAR fps[10] = L"0.0";

	Support::FloatToWchar(fps,f);
	Support::LinkingWchar(FPS, fps);

	g_FPS->Update();
	g_FPS->Createfont(FPS);

	//シーン更新
	SINSTANCE(CSceneManager)->UpdateScene();
}

void Draw()
{
	//画面を白色でクリア
	(*graphicsDevice()).Clear(0,
		NULL,
		D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		D3DCOLOR_XRGB(255, 255, 255),
		1.0f,
		0);

	//シーン開始
	if (SUCCEEDED((*graphicsDevice()).BeginScene()))
	{
		//シーン描画
		SINSTANCE(CSceneManager)->DrawScene();
		g_FPS->Render();
		
		//シーン終了
		(*graphicsDevice()).EndScene();
	}
	(*graphicsDevice()).Present(NULL, NULL, NULL, NULL);
}
