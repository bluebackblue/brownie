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
		Position2DType() noexcept
			:
			x(static_cast<T>(0)),
			y(static_cast<T>(0))
		{
		}

		/** copy constructor
		*/
		Position2DType(const Position2DType<T>& a_instance) noexcept
			:
			x(a_instance.x),
			y(a_instance.y)
		{
		}

		/** constructor
		*/
		Position2DType(T a_x,T a_y) noexcept
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

		/** t_1 = t_2;
		*/
		Position2DType<T>& operator =(const Position2DType<T>& a_right)
		{
			this->x = a_right.x;
			this->y = a_right.y;
			return *this;
		}

		/** t_1 = +t_2;
		*/
		Position2DType<T> operator +() const
		{
			return *this;
		}

		/** t_1 = -t_2;
		*/
		Position2DType<T> operator -() const
		{
			return Position2DType<T>(-this->x,-this->y);
		}

		/** t_1 += t_2;
		*/
		Position2DType<T>& operator +=(const Position2DType<T>& a_right)
		{
			this->x += a_right.x;
			this->y += a_right.y;
			return *this;
		}

		/** t_1 -= t_2;
		*/
		Position2DType<T>& operator -=(const Position2DType<T>& a_right)
		{
			this->x -= a_right.x;
			this->y -= a_right.y;
			return *this;
		}

		/** t_1 *= t_2;
		*/
		Position2DType<T>& operator *=(const Position2DType<T>& a_right)
		{
			this->x *= a_right.x;
			this->y *= a_right.y;
			return *this;
		}

		/** t_1 /= t_2;
		*/
		Position2DType<T>& operator /=(const Position2DType<T>& a_right)
		{
			this->x /= a_right.x;
			this->y /= a_right.y;
			return *this;
		}

		/** Set
		*/
		void Set(T a_x,T a_y)
		{
			this->x = a_x;
			this->y = a_y;
		}

	};


	/** t_1 = t_2 + t_3;
	*/
	template <typename T> Position2DType<T> operator +(const Position2DType<T>& a_left,const Position2DType<T>& a_right)
	{
		return Position2DType<T>(a_left) += a_right;
	}

	/** t_1 = t_2 - t_3;
	*/
	template <typename T> Position2DType<T> operator -(const Position2DType<T>& a_left,const Position2DType<T>& a_right)
	{
		return Position2DType<T>(a_left) -= a_right;
	}

	/** t_1 = t_2 * t_3;
	*/
	template <typename T> Position2DType<T> operator *(const Position2DType<T>& a_left,const Position2DType<T>& a_right)
	{
		return Position2DType<T>(a_left) *= a_right;
	}

	/** t_1 = t_2 / t_3;
	*/
	template <typename T> Position2DType<T> operator /(const Position2DType<T>& a_left,const Position2DType<T>& a_right)
	{
		return Position2DType<T>(a_left) /= a_right;
	}


}
#pragma warning(pop)

