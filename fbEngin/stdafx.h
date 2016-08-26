// stdafx.h : 標準のシステム インクルード ファイルのインクルード ファイル、または
// 参照回数が多く、かつあまり変更されない、プロジェクト専用のインクルード ファイル
// を記述します。
//
#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Windows ヘッダーから使用されていない部分を除外します。
// Windows ヘッダー ファイル:
#include <windows.h>

// C ランタイム ヘッダー ファイル
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>


// TODO: プログラムに必要な追加ヘッダーをここで参照してください。
#include <d3d9.h>
#include <d3dx9.h>

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

#include "GraphicsDevice.h"		//Direct3D管理ヘッダインクルード

#define SAFE_RELEASE(p)			{ if(p) { (p)->Release(); (p) = NULL; } }	//インスタンスリリース
#define SAFE_DELETE_ARRAY(p)	{ if(p!=nullptr) { delete[] (p);   (p) = nullptr; } }	//インスタンス配列削除
#define SAFE_DELETE(p)			{ if(p!=nullptr) { delete (p);     (p) = nullptr; } }	//インスタンス削除


//////ここから下に足す
#include <map>
#include <string>
#include <vector>
#include <list>
#include <math.h>

using namespace std;
//シングルトンのインスタンスを取得するマクロ定義
#define SINSTANCE(p) p::getInstance()

//p回繰り返す
#define FOR(p) for(short i = 0;i < (int)p;i++)
//配列の要素数を取得する
#define ARRAY_SIZE(p) (sizeof(p)/sizeof(p[0]))

//ウィンドウサイズ
//#define GAME_WINDOW_WIDTH 1366
//#define GAME_WINDOW_HEIGHT 768

//ウィンドウのクライアントエリアのサイズ
#define GAME_CLIENT_WIDTH 1280
#define GAME_CLIENT_HEIGHT 720

//シーンのキャッシュの数,1だとキャッシュ機能なし
#define SCENECASHE_NUM 2

#define VECTOR3_ZERO D3DXVECTOR3(0.0f, 0.0f, 0.0f)
#define VECTOR3_ONE D3DXVECTOR3(1.0f, 1.0f, 1.0f)

//キー定義
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

//グローバル変数
//ウィンドウの座標
extern RECT WINDOW_POS;
//クライアントエリアの縦と横のサイズ
extern RECT CLIENT_RECT;

//デバッグモードフラグ
extern bool g_DebugMode;

#include "support.h"
#include "Vector.h"
#include "Timer.h"