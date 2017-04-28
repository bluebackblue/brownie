#pragma once

/**
 * Copyright (c) 2016 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief �v���b�g�t�H�[���B
*/


/** include
*/
#include <brownie_config/brownie_config.h>


/** �v���b�g�t�H�[���B
*/
#if defined(PLATFORM_VCWIN)

	//PLATFORM_VCWIN

#elif defined(PLATFORM_UNKNOWN)

	//PLATFORM_UNKNOWN

#else

	#error

#endif


/** �r�b�g�B
*/
#if defined(ROM_32BIT)

	//ROM_32BIT

#elif defined(ROM_64BIT)

	//ROM_64BIT

#else

	#error

#endif


/** �����B
*/
#if defined(ROM_MASTER)

	//ROM_MASTER

#elif defined(ROM_DEVELOP)

	//ROM_DEVELOP

#elif defined(ROM_DEEPDEBUG)

	//ROM_DEEPDEBUG

#elif defined(ROM_FULLDEBUG)

	//ROM_FULLDEBUG

#else

	#error

#endif

