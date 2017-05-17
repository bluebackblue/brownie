#pragma once

/**
 * Copyright (c) 2016 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief ユーザーカスタマイズ用ヘッダー。
*/


/** DEF_TEST

	DEF_TEST0	:	初期化、ログ、ブレイク、アサート。
	DEF_TEST1	:	fovehmd

*/
#define DEF_TEST1


#if defined(DEF_TEST0)

#elif defined(DEF_TEST1)

	#define BSYS_WINDOW_ENABLE								(1)
	#define BSYS_D3D11_ENABLE								(1)
	#define BSYS_FOVEHMD_ENABLE								(1)

#endif

