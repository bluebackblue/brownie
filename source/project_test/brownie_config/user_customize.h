#pragma once

/**
 * Copyright (c) 2016-2018 blueback
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


/** デバッグ。
*/
#define BSYS_FILE_DEBUG_ENABLE								(1)
#define BLIB_THREADTEMPLATE_DEBUG_ENABLE					(1)


#if(DEF_TEST_INDEX == 0)

	#define DEF_TEST_STRING									L"0"

	#define BLIB_STDATOMIC_ENABLE							(1)
	#define BLIB_GLOBALFIXEDALLOCATOR_ENABLE				(1)
	#define BLIB_GLOBALFIXEDALLOCATOR_BLOCKSIZE				(32)
	#define BLIB_GLOBALFIXEDALLOCATOR_BLOCKMAX				(1 * 1024 * 1024)
	#define BLIB_DEBUGASSERT_CALLBACK_ENABLE				(1)
	#define BLIB_DEBUGBREAK_CALLBACK_ENABLE					(1)
	#define BLIB_DEBUGLOG_CALLBACK_ENABLE					(1)
	#define BLIB_FILEHANDLE_READWRITE_BLOCKSIZE				(4096)
	#define BLIB_FILEHANDLE_RETRYMAX						(15)
	#define BLIB_STDREGEX_ENABLE							(1)
	#define BLIB_STDMUTEX_ENABLE							(1)
	#define BLIB_STDMOVE_ENABLE								(1)
	#define BLIB_MATH_SINCOSFAST_TABLESIZE					(4096)
	#define BLIB_MEMORYCONTAINER_ENABLE						(1)
	#define BLIB_MEMORYCONTAINER_NESTMAX					(16)
	#define BLIB_MEMORYCONTAINER_THREADLOCALSLOT			(0x01)
	#define BLIB_STDRANDOM_ENABLE							(1)
	#define BLIB_STDSHAREDPTR_ENABLE						(0)
	#define BLIB_SHAREDPTR_CACHE_ENABLE						(1)
	#define BLIB_STDNULLPTR_ENABLE							(1)
	#define BLIB_JSONITEM_ENABLE							(1)
	#define BLIB_STACKTRACE_ENABLE							(1)
	#define BLIB_STDTHREAD_ENABLE							(1)
	#define BLIB_STDTHREADLOCAL_ENABLE						(1)
	#define BLIB_THREADLOCAL_ENABLE							(1)
	#define BLIB_THREADLOCAL_SLOTMAX						(32)
	#define BLIB_VASTRING_DEBUG_THREADLOCALSLOT				(0x00)
	#define BLIB_VASTRING_DEBUG_SIZE						(4 * 1024)
	#define BLIB_STDUNORDEREDMAP_ENABLE						(1)
	#define BLIB_STDALIASTEMPLATE_ENABLE					(1)
	#define BSYS_ACTIONBATCHING_ENABLE						(1)
	#define BSYS_COLOR_ENABLE								(1)
	#define BSYS_FILE_ENABLE								(1)
	#define BSYS_FILE_PACK_ENABLE							(0)
	#define BSYS_FILE_MEMORYCONTAINER						(0x01)
	#define BSYS_FILE_LISTSIZE								(512)
	#define BSYS_VERTEX_ENABLE								(1)
	#define BSYS_OPENGL_ENABLE								(1)
	#define BSYS_OPENGL_DEBUG_ENABLE						(0)
	#define BSYS_OPENGL_UPDATE_FPS							(60)
	#define BSYS_OPENGL_WIDTH								(1440)
	#define BSYS_OPENGL_HEIGHT								(810)
	#define BSYS_OPENGL_SHADERIDMAX							(32)
	#define BSYS_GEOMETRY_ENABLE							(1)
	#define BSYS_GEOMETRY_MATRIX_SINCOSFAST_ENABLE			(1)
	#define BSYS_GEOMETRY_PERSPECTIVE_TYPE					(0x00)
	#define BSYS_GEOMETRY_ROWCOLUMN_TYPE					(0x00)
	#define BSYS_GEOMETRY_LEFTRIGHT_TYPE					(0x00)
	#define BSYS_FOVEHMD_ENABLE								(0)
	#define BSYS_WINDOW_ENABLE								(1)
	#define BSYS_D3D11_ENABLE								(1)
	#define BSYS_D3D11_DEBUG_ENABLE							(1)
	#define BSYS_D3D11_FONT_DRAWTYPEMAX_S					(128)
	#define BSYS_D3D11_FONT_DRAWTYPEMAX_M					(128)
	#define BSYS_D3D11_FONT_DRAWTYPEMAX_L					(32)
	#define BSYS_D3D11_FONT_DRAWTYPEMAX_EX					(16)
	#define BSYS_MMD_ENABLE									(1)
	#define BSYS_TEXTURE_ENABLE								(1)
	#define BSYS_TEXTURE_GDIPLUS_ENABLE						(1)
	#define BSYS_FONT_ENABLE								(1)
	#define BSYS_PAD_ENABLE									(1)
	#define BSYS_WINDOWMENU_ENABLE							(1)
	#define BSYS_WINSOCK_ENABLE								(1)
	#define BSYS_HTTP_ENABLE								(1)
	#define BSYS_HTTP_USERAGENT								BROWNIE_VERSION_STRING
	#define BSYS_COMMANDLINE_ENABLE							(1)

#elif(DEF_TEST_INDEX == 1)

	#define DEF_TEST_STRING									L"1"

#elif(DEF_TEST_INDEX == 2)

	#define DEF_TEST_STRING									L"2"
	#define BSYS_FILE_ENABLE								(1)

#elif(DEF_TEST_INDEX == 3)

	#define DEF_TEST_STRING									L"2"

	#define BSYS_WINDOW_ENABLE								(1)

	//#define BSYS_OPENSSL_ENABLE							(1)
	//#define BSYS_HTTP_ENABLE								(1)
	//#define BSYS_WINSOCK_ENABLE							(1)
	//#define BSYS_HTTP_DEBUG_ENABLE						(1)

	#define BSYS_GEOMETRY_ENABLE							(1)

	#define BSYS_ACTIONBATCHING_ENABLE						(1)

	#define BSYS_FILE_ENABLE								(1)
	#define BSYS_FILE_PACK_ENABLE							(1)

	#define BSYS_WAVE_ENABLE								(1)
	#define BSYS_WAVE_DEBUG_ENABLE							(1)
	#define BSYS_DSOUND_ENABLE								(1)
	#define BSYS_DSOUND_DEBUG_ENABLE						(1)

#elif(DEF_TEST_INDEX == 10)

	#define DEF_TEST_STRING									L"10"

	#define BSYS_D3D11_ENABLE								(1)

	#define BSYS_WINDOWMENU_ENABLE							(1)

#elif(DEF_TEST_INDEX == 11)

	#define DEF_TEST_STRING									L"11"

	#define BSYS_D3D11_ENABLE								(1)

	#define BSYS_WINDOWMENU_ENABLE							(1)

	#define BSYS_DSOUND_ENABLE								(1)
	#define BSYS_DSOUND_DEBUG_ENABLE						(1)

	#define BSYS_WAVE_ENABLE								(1)
	#define BSYS_WAVE_DEBUG_ENABLE							(1)

	#define BSYS_TEXTURE_GDIPLUS_ENABLE						(1)

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

	#if !defined(BSYS_OPENSSL_ENABLE)
	#define BSYS_OPENSSL_ENABLE								(1)
	#endif

	#if !defined(BSYS_OPENSSL_DEBUG_ENABLE)
	#define BSYS_OPENSSL_DEBUG_ENABLE						(1)
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
#if defined(PLATFORM_VCWIN) && (1)
#if defined(ROM_DEVELOP) || defined(ROM_DEEPDEBUG) || defined(ROM_FULLDEBUG)

	#define _CRTDBG_MAP_ALLOC
	#include <crtdbg.h>
	#define custom_new new(_NORMAL_BLOCK,__FILE__,__LINE__)
	#define new custom_new

#endif
#endif

