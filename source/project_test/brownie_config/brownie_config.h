#pragma once

/**
 * Copyright (c) 2016 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief コンフィグ。
*/


/*

	std atomic

*/
#define BLIB_STDATOMIC_ENABLE							(1)

/*

	グローバル。固定長アロケータ。

*/
#define BLIB_GLOBALFIXEDALLOCATOR_ENABLE				(1)
#define BLIB_GLOBALFIXEDALLOCATOR_BLOCKSIZE				(32)
#define BLIB_GLOBALFIXEDALLOCATOR_SIZE					(1 * 1024 * 1024)

/*

	デバッグアサート。

*/
#define BLIB_DEBUGASSERT_CALLBACK_ENABLE				(1)


/*

	デバッグブレイク。

*/
#define BLIB_DEBUGBREAK_CALLBACK_ENABLE					(1)

/*

	デバッグログ。

*/
#define BLIB_DEBUGLOG_CALLBACK_ENABLE					(1)

/*

	ファイルハンドル。プロックサイズ。

*/
#define BLIB_FILEHANDLE_BLOCKSIZE						(4096)

/*

	ファイルハンドル。リトライ回数。

*/
#define BLIB_FILEHANDLE_RETRYMAX						(15)

/*

	std regex

*/
#define BLIB_STDREGEX_ENABLE							(1)

/*

	std mutex

*/
#define BLIB_STDMUTEX_ENABLE							(1)

/*

	Math::sin_fast / Math::cos_fast のテーブルサイズ。

*/
#define BLIB_MATH_SINCOSFAST_TABLESIZE					(4096)

/*

	メモリーコンテナー。

*/
#define BLIB_MEMORYCONTAINER_ENABLE						(1)

/*

	メモリーコンテナー。ネスト最大値。

*/
#define BLIB_MEMORYCONTAINER_NESTMAX					(16)

/*

	メモリーコンテナー。スレッドローカルスロット。

*/
#define BLIB_MEMORYCONTAINER_THREADLOCALSLOT			(0x01)

/*

	std random

*/
#define BLIB_STDRANDOM_ENABLE							(1)

/*

	std sharedptr

*/
#define BLIB_STDSHAREDPTR_ENABLE						(0)

/*

	シェアードポインタ。キャッシュ。

*/
#define BLIB_SHAREDPTR_CACHE_ENABLE						(1)

/*

	std nullptr

*/
#define BLIB_STDNULLPTR_ENABLE							(1)

/*

	ＪＳＯＮアイテム。

*/
#define BLIB_JSONITEM_ENABLE							(1)

/*

	スタックトレース。

*/
#define BLIB_STACKTRACE_ENABLE							(1)

/*

	std thread

*/
#define BLIB_STDTHREAD_ENABLE							(1)

/*

	std threadlocal

*/
#define BLIB_STDTHREADLOCAL_ENABLE						(1)

/*

	スレッドローカル。ソロット数。

*/
#define BLIB_THREADLOCAL_SLOTMAX						(32)

/*

	スレッドローカル。

*/
#define BLIB_THREADLOCAL_ENABLE							(1)

/*

	可変引数文字列操作。デバッグ用。スレッドローカルスロット。

*/
#define BLIB_VASTRING_DEBUG_THREADLOCALSLOT				(0x00)

/*

	可変引数文字列操作。デバッグ用。サイズ。

*/
#define BLIB_VASTRING_DEBUG_SIZE						(4 * 1024)

/*

	std unordered_map

*/
#define BLIB_STDUNORDEREDMAP_ENABLE						(1)

/*

	std alias template

*/
#define BLIB_STDALIASTEMPLATE_ENABLE					(1)















/*

	actionbatching

*/
#define BSYS_ACTIONBATCHING_ENABLE						(1)

/*

	color

*/
#define BSYS_COLOR_ENABLE								(1)

/*

	file

	BSYS_FILE_LISTSIZE	: 同時リクエスト数。

*/
#define BSYS_FILE_ENABLE								(1)
#define BSYS_FILE_PACK_ENABLE							(1)
#define BSYS_FILE_MEMORYCONTAINER						(0x01)
#define BSYS_FILE_LISTSIZE								(512)

/*

	model

*/
#define BSYS_MODEL_ENABLE								(1)

/*

	opengl

*/
#define BSYS_OPENGL_ENABLE								(0)
#define BSYS_OPENGL_UPDATE_FPS							(60)
#define BSYS_OPENGL_WIDTH								(1440)
#define BSYS_OPENGL_HEIGHT								(810)
#define BSYS_OPENGL_SHADERIDMAX							(32)

/*

	geometry

*/
#define BSYS_GEOMETRY_ENABLE							(1)
#define BSYS_GEOMETRY_MATRIX_SINCOSFAST_ENABLE			(1)
#define BSYS_GEOMETRY_PERSPECTIVE_TYPE					(0x01)
#define BSYS_GEOMETRY_ROWCOLUMN_TYPE					(0x01)
#define BSYS_GEOMETRY_LEFTRIGHT_TYPE					(0x01)

/*

	fovehmd

*/
#define BSYS_FOVEHMD_ENABLE								(1)



/** user.h
*/
#include "./user_customize.h"

