#pragma once

/**
 * Copyright (c) 2016-2017 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE.txt
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief user_customize
*/


/** include

	test.h

	DEF_TEST_AUTO	: 自動テストを実行します。
	DEF_TEST_INDEX	: テスト番号を設定します。

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

	#define DEF_TEST_STRING									L"0"

	#define BSYS_COMMANDLINE_ENABLE							(1)

#elif(DEF_TEST_INDEX == 1)

	#define DEF_TEST_STRING									L"1"

#elif(DEF_TEST_INDEX == 2)

	#define DEF_TEST_STRING									L"2"
	#define BSYS_FILE_ENABLE								(1)

#elif(DEF_TEST_INDEX == 3)

	#define DEF_TEST_STRING									L"2"

	#define BSYS_WINDOW_ENABLE								(1)

#elif(DEF_TEST_INDEX == 10)

	#define DEF_TEST_STRING									L"10"

	#define BSYS_D3D11_ENABLE								(1)

	#define BSYS_WINDOWMENU_ENABLE							(1)

#elif(DEF_TEST_INDEX == 11)

	#define DEF_TEST_STRING									L"11"

	#define BSYS_D3D11_ENABLE								(1)

	#define BSYS_WINDOWMENU_ENABLE							(1)

#elif(DEF_TEST_INDEX == 12)

	#define DEF_TEST_STRING									L"12"

	#define BSYS_D3D11_ENABLE								(1)
	
	#define BSYS_WINDOWMENU_ENABLE							(1)

	#define BSYS_MMD_ENABLE									(1)

#elif(DEF_TEST_INDEX == 22)

	#define DEF_TEST_STRING									L"22"

	#define BSYS_D3D11_ENABLE								(1)

	#define BSYS_WINDOWMENU_ENABLE							(1)

	#define BSYS_MMD_ENABLE									(1)

#endif


/** BSYS_WINDOWMENU_ENABLE
*/
#if defined(BSYS_WINDOWMENU_ENABLE) && (BSYS_WINDOWMENU_ENABLE)

	#if !defined(BLIB_DEBUGASSERT_CALLBACK_ENABLE)
	#define BLIB_DEBUGASSERT_CALLBACK_ENABLE				(1)
	#endif

	#if !defined(BLIB_DEBUGBREAK_CALLBACK_ENABLE)
	#define BLIB_DEBUGBREAK_CALLBACK_ENABLE					(1)
	#endif

	#if !defined(BLIB_DEBUGLOG_CALLBACK_ENABLE)
	#define BLIB_DEBUGLOG_CALLBACK_ENABLE					(1)
	#endif

	#if !defined(BSYS_PAD_ENABLE)
	#define BSYS_PAD_ENABLE									(1)
	#endif

#endif

/** BSYS_MMD_ENABLE
*/
#if defined(BSYS_MMD_ENABLE) && (BSYS_MMD_ENABLE)

	#if !defined(BSYS_TEXTURE_GDIPLUS_ENABLE)
		#define BSYS_TEXTURE_GDIPLUS_ENABLE					(1)
	#endif

#endif


/** DEF_TEST_AUTO
*/
#if defined(DEF_TEST_AUTO) && (DEF_TEST_AUTO)

	#if !defined(BSYS_HTTP_ENABLE)
	#define BSYS_HTTP_ENABLE								(1)
	#endif

	#if !defined(BSYS_WINSOCK_ENABLE)
	#define BSYS_WINSOCK_ENABLE								(1)
	#endif

	#if !defined(BSYS_TEXTURE_GDIPLUS_ENABLE)
	#define BSYS_TEXTURE_GDIPLUS_ENABLE						(1)
	#endif

	#if !defined(BSYS_TEXTURE_ENABLE)
	#define BSYS_TEXTURE_ENABLE								(1)
	#endif

	#if !defined(BLIB_DEBUGASSERT_CALLBACK_ENABLE)
	#define BLIB_DEBUGASSERT_CALLBACK_ENABLE				(1)
	#endif

	#if !defined(BLIB_DEBUGBREAK_CALLBACK_ENABLE)
	#define BLIB_DEBUGBREAK_CALLBACK_ENABLE					(1)
	#endif

	#if !defined(BLIB_DEBUGLOG_CALLBACK_ENABLE)
	#define BLIB_DEBUGLOG_CALLBACK_ENABLE					(1)
	#endif

#endif


/** BSYS_D3D11_ENABLE
*/
#if defined(BSYS_D3D11_ENABLE) && (BSYS_D3D11_ENABLE)

	#if !defined(BSYS_GEOMETRY_ENABLE)
	#define BSYS_GEOMETRY_ENABLE							(1)
	#endif

	#if !defined(BSYS_VERTEX_ENABLE)
	#define BSYS_VERTEX_ENABLE								(1)
	#endif

	#if !defined(BSYS_COLOR_ENABLE)
	#define BSYS_COLOR_ENABLE								(1)
	#endif

	#if !defined(BSYS_ACTIONBATCHING_ENABLE)
	#define BSYS_ACTIONBATCHING_ENABLE						(1)
	#endif

	#if !defined(BSYS_FILE_ENABLE)
	#define BSYS_FILE_ENABLE								(1)
	#endif

	#if !defined(BSYS_WINDOW_ENABLE)
	#define BSYS_WINDOW_ENABLE								(1)
	#endif

	#if !defined(BSYS_TEXTURE_ENABLE)
	#define BSYS_TEXTURE_ENABLE								(1)
	#endif

	#if !defined(BSYS_FONT_ENABLE)
	#define BSYS_FONT_ENABLE								(1)
	#endif

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

