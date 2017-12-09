#pragma once

/**
 * Copyright (c) 2016 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief コンフィグ。
*/


/** user.h
*/
#include "./user_customize.h"


/*

	std atomic

*/
#if !defined(BLIB_STDATOMIC_ENABLE)
	#define BLIB_STDATOMIC_ENABLE							(1)
#endif

/*

	グローバル固定長アロケータ。

*/
#if !defined(BLIB_GLOBALFIXEDALLOCATOR_ENABLE)
	#define BLIB_GLOBALFIXEDALLOCATOR_ENABLE				(1)
#endif
#if !defined(BLIB_GLOBALFIXEDALLOCATOR_BLOCKSIZE)
	#define BLIB_GLOBALFIXEDALLOCATOR_BLOCKSIZE				(32)
#endif
#if !defined(BLIB_GLOBALFIXEDALLOCATOR_SIZE)
	#define BLIB_GLOBALFIXEDALLOCATOR_SIZE					(1 * 1024 * 1024)
#endif

/*

	デバッグアサートコールバック。

*/
#if !defined(BLIB_DEBUGASSERT_CALLBACK_ENABLE)
	#define BLIB_DEBUGASSERT_CALLBACK_ENABLE				(0)
#endif

/*

	デバッグブレイクコールバック。

*/
#if !defined(BLIB_DEBUGBREAK_CALLBACK_ENABLE)
	#define BLIB_DEBUGBREAK_CALLBACK_ENABLE					(0)
#endif

/*

	デバッグログ。

*/
#if !defined(BLIB_DEBUGLOG_CALLBACK_ENABLE)
	#define BLIB_DEBUGLOG_CALLBACK_ENABLE					(0)
#endif

/*

	ファイルハンドル。プロックサイズ。

*/
#if !defined(BLIB_FILEHANDLE_BLOCKSIZE)
	#define BLIB_FILEHANDLE_BLOCKSIZE						(4096)
#endif

/*

	ファイルハンドル。リトライ回数。

*/
#if !defined(BLIB_FILEHANDLE_RETRYMAX)
	#define BLIB_FILEHANDLE_RETRYMAX						(15)
#endif

/*

	std regex

*/
#if !defined(BLIB_STDREGEX_ENABLE)
	#define BLIB_STDREGEX_ENABLE							(1)
#endif

/*

	std mutex

*/
#if !defined(BLIB_STDMUTEX_ENABLE)
	#define BLIB_STDMUTEX_ENABLE							(1)
#endif

/*

	std move

*/
#if !defined(BLIB_STDMOVE_ENABLE)
	#define BLIB_STDMOVE_ENABLE								(1)
#endif

/*

	Math::sin_fast / Math::cos_fast のテーブルサイズ。

*/
#if !defined(BLIB_MATH_SINCOSFAST_TABLESIZE)
	#define BLIB_MATH_SINCOSFAST_TABLESIZE					(4096)
#endif

/*

	メモリーコンテナー。

*/
#if !defined(BLIB_MEMORYCONTAINER_ENABLE)
	#define BLIB_MEMORYCONTAINER_ENABLE						(1)
#endif

/*

	メモリーコンテナー。ネスト最大値。

*/
#if !defined(BLIB_MEMORYCONTAINER_NESTMAX)
	#define BLIB_MEMORYCONTAINER_NESTMAX					(16)
#endif

/*

	メモリーコンテナー。スレッドローカルスロット。

*/
#if !defined(BLIB_MEMORYCONTAINER_THREADLOCALSLOT)
	#define BLIB_MEMORYCONTAINER_THREADLOCALSLOT			(0x01)
#endif

/*

	std random

*/
#if !defined(BLIB_STDRANDOM_ENABLE)
	#define BLIB_STDRANDOM_ENABLE							(1)
#endif

/*

	std sharedptr

*/
#if !defined(BLIB_STDSHAREDPTR_ENABLE)
	#define BLIB_STDSHAREDPTR_ENABLE						(0)
#endif

/*

	シェアードポインタ。キャッシュ。

*/
#if !defined(BLIB_SHAREDPTR_CACHE_ENABLE)
	#define BLIB_SHAREDPTR_CACHE_ENABLE						(1)
#endif

/*

	std nullptr

*/
#if !defined(BLIB_STDNULLPTR_ENABLE)
	#define BLIB_STDNULLPTR_ENABLE							(1)
#endif

/*

	ＪＳＯＮアイテム。

*/
#if !defined(BLIB_JSONITEM_ENABLE)
	#define BLIB_JSONITEM_ENABLE							(1)
#endif

/*

	スタックトレース。

*/
#if !defined(BLIB_STACKTRACE_ENABLE)
#define BLIB_STACKTRACE_ENABLE								(1)
#endif

/*

	std thread

*/
#if !defined(BLIB_STDTHREAD_ENABLE)
#define BLIB_STDTHREAD_ENABLE								(1)
#endif

/*

	std threadlocal

*/
#if !defined(BLIB_STDTHREADLOCAL_ENABLE)
	#define BLIB_STDTHREADLOCAL_ENABLE						(1)
#endif

/*

	スレッドローカル。ソロット数。

*/
#if !defined(BLIB_THREADLOCAL_SLOTMAX)
	#define BLIB_THREADLOCAL_SLOTMAX						(32)
#endif

/*

	スレッドローカル。

*/
#if !defined(BLIB_THREADLOCAL_ENABLE)
	#define BLIB_THREADLOCAL_ENABLE							(1)
#endif

/*

	可変引数文字列操作。デバッグ用。スレッドローカルスロット。

*/
#if !defined(BLIB_VASTRING_DEBUG_THREADLOCALSLOT)
	#define BLIB_VASTRING_DEBUG_THREADLOCALSLOT				(0x00)
#endif

/*

	可変引数文字列操作。デバッグ用。サイズ。

*/
#if !defined(BLIB_VASTRING_DEBUG_SIZE)
	#define BLIB_VASTRING_DEBUG_SIZE						(4 * 1024)
#endif

/*

	std unordered_map

*/
#if !defined(BLIB_STDUNORDEREDMAP_ENABLE)
	#define BLIB_STDUNORDEREDMAP_ENABLE						(1)
#endif

/*

	std alias template

*/
#if !defined(BLIB_STDALIASTEMPLATE_ENABLE)
	#define BLIB_STDALIASTEMPLATE_ENABLE					(1)
#endif

/*

	actionbatching

*/
#if !defined(BSYS_ACTIONBATCHING_ENABLE)
	#define BSYS_ACTIONBATCHING_ENABLE						(1)
#endif

/*

	color

*/
#if !defined(BSYS_COLOR_ENABLE)
	#define BSYS_COLOR_ENABLE								(1)
#endif

/*

	file

	BSYS_FILE_LISTSIZE		: 同時リクエスト数。
	BSYS_FILE_PACK_ENABLE	: パックファイル。

*/
#if !defined(BSYS_FILE_ENABLE)
	#define BSYS_FILE_ENABLE								(1)
#endif
#if !defined(BSYS_FILE_PACK_ENABLE)
	#define BSYS_FILE_PACK_ENABLE							(1)
#endif
#if !defined(BSYS_FILE_MEMORYCONTAINER)
	#define BSYS_FILE_MEMORYCONTAINER						(0x01)
#endif
#if !defined(BSYS_FILE_LISTSIZE)
	#define BSYS_FILE_LISTSIZE								(512)
#endif

/*

	vertex

*/
#if !defined(BSYS_VERTEX_ENABLE)
	#define BSYS_VERTEX_ENABLE								(1)
#endif

/*

	opengl

*/
#if !defined(BSYS_OPENGL_ENABLE)
	#define BSYS_OPENGL_ENABLE								(0)
#endif
#if !defined(BSYS_OPENGL_UPDATE_FPS)
	#define BSYS_OPENGL_UPDATE_FPS							(60)
#endif
#if !defined(BSYS_OPENGL_WIDTH)
	#define BSYS_OPENGL_WIDTH								(1440)
#endif
#if !defined(BSYS_OPENGL_HEIGHT)
	#define BSYS_OPENGL_HEIGHT								(810)
#endif
#if !defined(BSYS_OPENGL_SHADERIDMAX)
	#define BSYS_OPENGL_SHADERIDMAX							(32)
#endif

/*

	geometry

*/
#if !defined(BSYS_GEOMETRY_ENABLE)
	#define BSYS_GEOMETRY_ENABLE							(1)
#endif
#if !defined(BSYS_GEOMETRY_MATRIX_SINCOSFAST_ENABLE)
	#define BSYS_GEOMETRY_MATRIX_SINCOSFAST_ENABLE			(1)
#endif
#if !defined(BSYS_GEOMETRY_PERSPECTIVE_TYPE)
	#define BSYS_GEOMETRY_PERSPECTIVE_TYPE					(0x00)
#endif
#if !defined(BSYS_GEOMETRY_ROWCOLUMN_TYPE)
	#define BSYS_GEOMETRY_ROWCOLUMN_TYPE					(0x00)
#endif
#if !defined(BSYS_GEOMETRY_LEFTRIGHT_TYPE)
	#define BSYS_GEOMETRY_LEFTRIGHT_TYPE					(0x00)
#endif

/*

	fovehmd

*/
#if !defined(BSYS_FOVEHMD_ENABLE)
#define BSYS_FOVEHMD_ENABLE									(0)
#endif

/*

	window

*/
#if !defined(BSYS_WINDOW_ENABLE)
	#define BSYS_WINDOW_ENABLE								(0)
#endif

/*

	d3d11

	BSYS_D3D11_FONT_DRAWTYPEMAX		: 同時描画可能な文字種類数

*/
#if !defined(BSYS_D3D11_ENABLE)
	#define BSYS_D3D11_ENABLE								(0)
#endif
#if !defined(BSYS_D3D11_FONT_DRAWTYPEMAX)
	#define BSYS_D3D11_FONT_DRAWTYPEMAX						(128)
#endif


/*

	mmd

*/
#if !defined(BSYS_MMD_PMX_ENABLE)
	#define BSYS_MMD_PMX_ENABLE								(0)
#endif
#if !defined(BSYS_MMD_VMD_ENABLE)
	#define BSYS_MMD_VMD_ENABLE								(0)
#endif

/*

	テクスチャー

*/
#if !defined(BSYS_TEXTURE_ENABLE)
	#define BSYS_TEXTURE_ENABLE								(0)
#endif
#if !defined(BSYS_TEXTURE_GDIPLUS_ENABLE)
	#define BSYS_TEXTURE_GDIPLUS_ENABLE						(0)
#endif

/*

	経路探査

*/
#if !defined(BSYS_ROOTSEARCH_ENABLE)
	#define BSYS_ROOTSEARCH_ENABLE							(0)
#endif

/*

	フォント。

*/
#if !defined(BSYS_FONT_ENABLE)
	#define BSYS_FONT_ENABLE								(0)
#endif


/*

	パッド。

*/
#if !defined(BSYS_PAD_ENABLE)
	#define BSYS_PAD_ENABLE									(0)
#endif


/*

	デバッグメニュー。

*/
#if !defined(BSYS_DEBUGMENU_ENABLE)
	#define BSYS_DEBUGMENU_ENABLE							(0)
#endif


