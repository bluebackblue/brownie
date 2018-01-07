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
	/** Rect2DType_R

	x y w h

	*/
	template <typename T> struct Rect2DType_R
	{
		/** x
		*/
		T x;

		/** y
		*/
		T y;

		/** w
		*/
		T w;

		/** h
		*/
		T h;

		/** constructor
		*/
		Rect2DType_R()
			:
			x(static_cast<T>(0)),
			y(static_cast<T>(0)),
			w(static_cast<T>(0)),
			h(static_cast<T>(0))
		{
		}

		/** constructor
		*/
		Rect2DType_R(T a_x,T a_y,T a_w,T a_h)
			:
			x(a_x),
			y(a_y),
			w(a_w),
			h(a_h)
		{
		}

		/** destructor
		*/
		nonvirtual ~Rect2DType_R()
		{
		}

		/** Set
		*/
		void Set(T a_x,T a_y,T a_w,T a_h)
		{
			this->x = a_x;
			this->y = a_y;
			this->w = a_w;
			this->h = a_h;
		}
	};


	/** Rect2DType_A

	x1 y1 x2 y2

	*/
	template <typename T> struct Rect2DType_A
	{
		/** x1
		*/
		T x1;

		/** y1
		*/
		T y1;

		/** x2
		*/
		T x2;

		/** y2
		*/
		T y2;

		/** constructor
		*/
		Rect2DType_A()
			:
			x(static_cast<T>(0)),
			y(static_cast<T>(0)),
			w(static_cast<T>(0)),
			h(static_cast<T>(0))
		{
		}

		/** constructor
		*/
		Rect2DType_A(T a_x1,T a_y1,T a_x2,T a_y2)
			:
			x1(a_x1),
			y1(a_y1),
			x2(a_x2),
			x2(a_y2)
		{
		}
		
		/** destructor
		*/
		nonvirtual ~Rect2DType_A()
		{
		}

		/** Set
		*/
		void Set(T a_x1,T a_y1,T a_x2,T a_y2)
		{
			this->x1 = a_x1;
			this->y1 = a_y1;
			this->x2 = a_x2;
			this->x2 = a_y2;
		}
	};


}
#pragma warning(pop)

