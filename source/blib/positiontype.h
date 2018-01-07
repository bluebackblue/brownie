#pragma once

/**
 * Copyright (c) 2016-2018 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE.txt
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief 位置。
*/


/** include
*/
#include "./types.h"
#include "./platform.h"


/** NBlib
*/
#pragma warning(push)
#pragma warning(disable:4514)
namespace NBlib
{
	/** Position2DType
	*/
	template <typename T> struct Position2DType
	{
		/** x
		*/
		T x;

		/** y
		*/
		T y;

		/** constructor
		*/
		Position2DType()
			:
			x(static_cast<T>(0)),
			y(static_cast<T>(0))
		{
		}

		/** constructor
		*/
		Position2DType(T a_x,T a_y)
			:
			x(a_x),
			y(a_y)
		{
		}

		/** destructor
		*/
		nonvirtual ~Position2DType()
		{
		}

		/** Set
		*/
		void Set(T a_x,T a_y)
		{
			this->x = a_x;
			this->y = a_y;
		}
	};


}
#pragma warning(pop)

