#pragma once

/**
 * Copyright (c) 2016 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief �X�^�b�N����̗̈�m�ہB
*/


/** include
*/
#include "./types.h"
#include "./platform.h"


/*

	�X�^�b�N�̈悩�烁�����[�����蓖�Ă܂��B

*/


#if defined(PLATFORM_VCWIN)

	#define MALLOCA(SIZE)	_malloca(SIZE)

#else

	#error

#endif


#if defined(PLATFORM_VCWIN)

	#define FREEA(POINTER)	_freea(POINTER)

#else

	#error

#endif

