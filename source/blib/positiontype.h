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

	x y

	*/
	template <typename T> struct Position2DType
	{
		/** xx
		*/
		T xx;

		/** yy
		*/
		T yy;

		/** constructor
		*/
		Position2DType() noexcept
			:
			xx(static_cast<T>(0)),
			yy(static_cast<T>(0))
		{
		}

		/** constructor
		*/
		explicit Position2DType(const T& a_value) noexcept
			:
			xx(a_value),
			yy(a_value)
		{
		}

		/** constructor
		*/
		explicit Position2DType(const T& a_xx,const T& a_yy) noexcept
			:
			xx(a_xx),
			yy(a_yy)
		{
		}

		/** copy constructor
		*/
		Position2DType(const Position2DType<T>& a_instance) noexcept
			:
			xx(a_instance.xx),
			yy(a_instance.yy)
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
			this->xx = a_right.xx;
			this->yy = a_right.yy;
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
			this->xx += a_right.xx;
			this->yy += a_right.yy;
			return *this;
		}

		/** t_1 -= t_2;
		*/
		Position2DType<T>& operator -=(const Position2DType<T>& a_right)
		{
			this->xx -= a_right.xx;
			this->yy -= a_right.yy;
			return *this;
		}

		/** t_1 *= t_2;
		*/
		Position2DType<T>& operator *=(const Position2DType<T>& a_right)
		{
			this->xx *= a_right.xx;
			this->yy *= a_right.yy;
			return *this;
		}

		/** t_1 /= t_2;
		*/
		Position2DType<T>& operator /=(const Position2DType<T>& a_right)
		{
			this->xx /= a_right.xx;
			this->yy /= a_right.yy;
			return *this;
		}

		/** t_1 = 2;
		*/
		Position2DType<T>& operator =(const T& a_right_value)
		{
			this->xx = a_right_value;
			this->yy = a_right_value;
			return *this;
		}

		/** t_1 += 2;
		*/
		Position2DType<T>& operator +=(const T& a_right_value)
		{
			this->xx += a_right_value;
			this->yy += a_right_value;
			return *this;
		}

		/** t_1 -= 2;
		*/
		Position2DType<T>& operator -=(const T& a_right_value)
		{
			this->xx -= a_right_value;
			this->yy -= a_right_value;
			return *this;
		}

		/** t_1 *= 2;
		*/
		Position2DType<T>& operator *=(const T& a_right_value)
		{
			this->xx *= a_right_value;
			this->yy *= a_right_value;
			return *this;
		}

		/** t_1 /= 2;
		*/
		Position2DType<T>& operator /=(const T& a_right_value)
		{
			this->xx /= a_right_value;
			this->yy /= a_right_value;
			return *this;
		}

		/** キャスト。
		*/
		template <typename T2> explicit operator Position2DType<T2>() const noexcept
		{
			return Position2DType<T2>(static_cast<T2>(this->xx),static_cast<T2>(this->yy));
		}

		/** Set
		*/
		void Set(const T& a_value)
		{
			this->xx = a_value;
			this->yy = a_value;
		}

		/** Set
		*/
		void Set(const T& a_xx,const T& a_yy)
		{
			this->xx = a_xx;
			this->yy = a_yy;
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


	/** t_1 = t_2 + 2;
	*/
	template <typename T> Position2DType<T> operator +(const Position2DType<T>& a_left,const T& a_right_value)
	{
		return Position2DType<T>(a_left) += a_right_value;
	}


	/** t_1 = t_2 - 2;
	*/
	template <typename T> Position2DType<T> operator -(const Position2DType<T>& a_left,const T& a_right_value)
	{
		return Position2DType<T>(a_left) -= a_right_value;
	}


	/** t_1 = t_2 * 2;
	*/
	template <typename T> Position2DType<T> operator *(const Position2DType<T>& a_left,const T& a_right_value)
	{
		return Position2DType<T>(a_left) *= a_right_value;
	}


	/** t_1 = t_2 / 2;
	*/
	template <typename T> Position2DType<T> operator /(const Position2DType<T>& a_left,const T& a_right_value)
	{
		return Position2DType<T>(a_left) /= a_right_value;
	}


}
#pragma warning(pop)

