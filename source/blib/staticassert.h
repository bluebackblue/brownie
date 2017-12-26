#pragma once

/**
 * Copyright (c) 2016 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE.txt
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief コンパイル時アサート。
*/


/** include
*/
#include "./types.h"
#include "./platform.h"


/** NBlib
*/
namespace NBlib
{
	#if defined(ROM_MASTER)

	#else

		/** StaticAssertValue
		*/
		template <bool> struct StaticAssertValue;

		/** [true]での特殊化。
		*/
		template <> struct StaticAssertValue<true>
		{
			struct Result
			{
				enum Id
				{
					Value = 1
				};
			};
		};

		/** [false]での特殊化。
		*/
		//template <> struct StaticAssert<false>
		//{
		//}
	
		/** StaticAssertType
		*/
		template <s32 X> struct StaticAssertType{};

	#endif


}


#if defined(ROM_MASTER)

	#define STATIC_ASSERT(X)

#else

	#define STATIC_ASSERT(X) typedef NBlib::StaticAssertType<sizeof(NBlib::StaticAssertValue<static_cast<bool>(X)>)>	_static_assert_typedef_

#endif

