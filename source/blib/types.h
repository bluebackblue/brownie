#pragma once

/**
 * Copyright (c) 2016-2017 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE.txt
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief タイプ。
*/


/** include
*/
#include "./version.h"


/** include
*/
#include <brownie_config/brownie_config.h>


/** include
*/
#include "./platform.h"


/** include
*/
//#pragma warning(push)
//#pragma warning(disable:0)
#include <cstdint>
#include <cstddef>
//#pragma warning(pop)

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

	typedef std::uintptr_t			AddressType;
}


/** 要素数。
*/
#if !defined(COUNTOF)

	#if defined(PLATFORM_VCWIN)

		#define COUNTOF(X)	static_cast<s32>(_countof(X))

	#else

		#define COUNTOF(X)	static_cast<s32>(sizeof(X)/sizeof(X[0]))

	#endif

#endif


/** 未使用変数。
*/
#if !defined(UNUSED)

	#define	UNUSED(X)			((void)&(X))

#endif


/** 仮想関数でないことの明示。
*/
#if !defined(nonvirtual)

	#define nonvirtual			/*nonvirtual*/

#endif


/** 終端文字。
*/
#if !defined(nullchar)

	#define nullchar			'\0'

#endif


/** 終端文字。
*/
#if !defined(nullwchar)

	#define nullwchar			L'\0'

#endif


/** ウィンドウズＡＰＩに使用するNULL。
*/
#if defined(PLATFORM_VCWIN) || defined(PLATFORM_GNUCWIN)

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

