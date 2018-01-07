#pragma once

/**
 * Copyright (c) 2016-2018 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE.txt
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief 矩形。
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
	/** Size2DType

	w h

	*/
	template <typename T> struct Size2DType
	{
		/** w
		*/
		T w;

		/** h
		*/
		T h;

		/** constructor
		*/
		Size2DType()
			:
			w(static_cast<T>(0)),
			h(static_cast<T>(0))
		{
		}

		/** constructor
		*/
		Size2DType(T a_w,T a_h)
			:
			w(a_w),
			h(a_h)
		{
		}

		/** destructor
		*/
		nonvirtual ~Size2DType()
		{
		}

		/** Set
		*/
		void Set(T a_x1,T a_y1,T a_x2,T a_y2)
		{
			this->w = a_w;
			this->h = a_h;
		}
	};


}
#pragma warning(pop)

