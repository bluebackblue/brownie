﻿#pragma once

/**
 * Copyright (c) 2016 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief ユーザーカスタマイズ用ヘッダー。
*/


/** DEF_TEST

	DEF_TEST0	:	デバッグログ、デバッグブレイク、アサート。
	DEF_TEST1	:	型、リスト。
	DEF_TEST2	:	ファイル、ＪＳＯＮ。

	DEF_TEST10	:	Ｄ３Ｄ１１。
	DEF_TEST11	:	ダイクストラ法。
	DEF_TEST12	:	デバッグメニュー。

*/
#define DEF_TEST12


#if defined(DEF_TEST0)

	#define DEF_TEST_TITLE									L"DEF_TEST0"

#elif defined(DEF_TEST1)

	#define DEF_TEST_TITLE									L"DEF_TEST1"

#elif defined(DEF_TEST2)

	#define DEF_TEST_TITLE									L"DEF_TEST2"

#elif defined(DEF_TEST3)

	#define DEF_TEST_TITLE									L"DEF_TEST3"

#elif defined(DEF_TEST10)

	#define DEF_TEST_TITLE									L"DEF_TEST10"

	#define BSYS_WINDOW_ENABLE								(1)
	#define BSYS_D3D11_ENABLE								(1)

#elif defined(DEF_TEST11)

	#define DEF_TEST_TITLE									L"DEF_TEST11"

	#define BSYS_WINDOW_ENABLE								(1)
	#define BSYS_D3D11_ENABLE								(1)
	#define BSYS_ROOTSEARCH_ENABLE							(1)

#elif defined(DEF_TEST12)

	#define DEF_TEST_TITLE									L"DEF_TEST12"

	#define BSYS_WINDOW_ENABLE								(1)
	#define BSYS_D3D11_ENABLE								(1)
	#define BSYS_FONT_ENABLE								(1)
	#define BSYS_PAD_ENABLE									(1)
	#define BSYS_DEBUGMENU_ENABLE							(1)

#elif defined(DEF_TEST22)

	#define DEF_TEST_TITLE									L"DEF_TEST22"

	#define BSYS_MMD_PMX_ENABLE								(1)
	#define BSYS_MMD_VMD_ENABLE								(1)
	#define BSYS_WINDOW_ENABLE								(1)
	#define BSYS_D3D11_ENABLE								(1)
	#define BSYS_FOVEHMD_ENABLE								(1)
	#define BSYS_TEXTURE_ENABLE								(1)
	#define BSYS_TEXTURE_GDIPLUS_ENABLE						(1)

#endif

