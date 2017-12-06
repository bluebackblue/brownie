#pragma once

/**
 * Copyright (c) 2016 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief �^�C�v�B
*/


/** include
*/
#include <brownie_config/brownie_config.h>


/** include
*/
#include "./platform.h"


/** include
*/
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>


/** NBlib
*/
namespace NBlib
{
	/** typedef
	*/
	typedef unsigned char			u8;
	typedef unsigned short int		u16;
	typedef unsigned int			u32;
	typedef unsigned long long int	u64;
	typedef signed char				s8;
	typedef signed short int		s16;
	typedef signed int				s32;
	typedef signed long long int	s64;

	typedef float					f32;
	typedef double					f64;

	typedef wchar_t					wchar;

	typedef uintptr_t				AddressType;
}

/** �v�f���B
*/
#if !defined(COUNTOF)

	#define COUNTOF(X)	static_cast<s32>(_countof(X))

#endif

/** ���g�p�ϐ��B
*/
#if !defined(UNUSED)

	#define	UNUSED(X)			((void)&(X))

#endif

/** ���z�֐��łȂ����Ƃ̖����B
*/
#if !defined(nonvirtual)

	#define nonvirtual			/*nonvirtual*/

#endif

/** �I�[�����B
*/
#if !defined(nullchar)

	#define nullchar			'\0'

#endif

/** �I�[�����B
*/
#if !defined(nullwchar)

	#define nullwchar			L'\0'

#endif

/** �E�B���h�E�Y�`�o�h�Ɏg�p����NULL�B
*/
#if defined(PLATFORM_VCWIN)

	#define WIN_NULL			NULL

#endif

/** nullptr
*/
#if(BLIB_STDNULLPTR_ENABLE)

	#if defined(nullptr)
		#undef nullptr
	#endif

#else

	#define nullptr				NULL

#endif

