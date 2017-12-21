#pragma once

/**
 * Copyright (c) 2016 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief ユーザーカスタマイズ用ヘッダー。
*/


/** include

	「test.h」は「build_project_test.bat」から自動生成され上書きされます。

	DEF_TEST_AUTO	: 自動チェック用デファインです。
	DEF_TEST_INDEX	: テストの切り替え用デファインです。説明は以下です。

	定義しているデファインの説明、デフォルト値は「brownie_config.h」に記述しています。

*/
#include "./test.h"


/** DEF_TEST_INDEX

	0	:	デバッグログ、デバッグブレイク、アサート。
	1	:	型、リスト。
	2	:	ファイル、ＪＳＯＮ。

	10	:	Ｄ３Ｄ１１。
	11	:	ダイクストラ法。
	12	:	ウィンドウメニュー。

*/


#if(DEF_TEST_INDEX == 0)

	#define DEF_TEST_TITLE									L"TEST 0"

#elif(DEF_TEST_INDEX == 1)

	#define DEF_TEST_TITLE									L"TEST 1"

#elif(DEF_TEST_INDEX == 2)

	#define DEF_TEST_TITLE									L"TEST 2"

#elif(DEF_TEST_INDEX == 10)

	#define DEF_TEST_TITLE									L"TEST 10"

	#define BSYS_WINDOW_ENABLE								(1)
	#define BSYS_D3D11_ENABLE								(1)

#elif(DEF_TEST_INDEX == 11)

	#define DEF_TEST_TITLE									L"TEST 11"

	#define BSYS_WINDOW_ENABLE								(1)
	#define BSYS_D3D11_ENABLE								(1)
	#define BSYS_ROOTSEARCH_ENABLE							(1)

#elif(DEF_TEST_INDEX == 12)

	#define DEF_TEST_TITLE									L"TEST 12"

	#define BSYS_WINDOW_ENABLE								(1)
	#define BSYS_D3D11_ENABLE								(1)
	#define BSYS_FONT_ENABLE								(1)
	#define BSYS_PAD_ENABLE									(1)
	#define BSYS_WINDOWMENU_ENABLE							(1)
	#define BLIB_DEBUGASSERT_CALLBACK_ENABLE				(1)
	#define BLIB_DEBUGBREAK_CALLBACK_ENABLE					(1)
	#define BLIB_DEBUGLOG_CALLBACK_ENABLE					(1)

	#define BSYS_D3D11_FONT_DRAWTYPEMAX_S					(128)
	#define BSYS_D3D11_FONT_DRAWTYPEMAX_M					(128)
	#define BSYS_D3D11_FONT_DRAWTYPEMAX_L					(32)
	#define BSYS_D3D11_FONT_DRAWTYPEMAX_EX					(16)

#elif(DEF_TEST_INDEX == 13)

	#define DEF_TEST_TITLE									L"TEST 13"

	#define BSYS_WINDOW_ENABLE								(1)
	#define BSYS_D3D11_ENABLE								(1)
	#define BSYS_FONT_ENABLE								(1)
	#define BSYS_PAD_ENABLE									(1)
	#define BSYS_WINDOWMENU_ENABLE							(1)
	#define BLIB_DEBUGASSERT_CALLBACK_ENABLE				(1)
	#define BLIB_DEBUGBREAK_CALLBACK_ENABLE					(1)
	#define BLIB_DEBUGLOG_CALLBACK_ENABLE					(1)

	#define BSYS_HTTP_ENABLE								(1)
	#define BSYS_WINSOCK_ENABLE								(1)
	#define BSYS_TEXTURE_GDIPLUS_ENABLE						(1)

#elif(DEF_TEST_INDEX == 22)

	#define DEF_TEST_TITLE									L"TEST 22"

	#define BSYS_MMD_PMX_ENABLE								(1)
	#define BSYS_MMD_VMD_ENABLE								(1)
	#define BSYS_WINDOW_ENABLE								(1)
	#define BSYS_D3D11_ENABLE								(1)
	//#define BSYS_FOVEHMD_ENABLE							(1)
	#define BSYS_TEXTURE_ENABLE								(1)
	#define BSYS_TEXTURE_GDIPLUS_ENABLE						(1)

#endif


/** メモリリークチェック。
*/
#if defined(PLATFORM_VCWIN) && (0)
#if defined(ROM_DEVELOP) || defined(ROM_DEEPDEBUG) || defined(ROM_FULLDEBUG)

	#define _CRTDBG_MAP_ALLOC
	#include <crtdbg.h>
	#define custom_new new(_NORMAL_BLOCK,__FILE__,__LINE__)
	#define new custom_new

#endif
#endif

