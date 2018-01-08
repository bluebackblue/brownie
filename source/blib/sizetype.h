#pragma once

/**
 * Copyright (c) 2016-2018 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE.txt
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief サイズ。
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
		Size2DType() noexcept
			:
			w(static_cast<T>(0)),
			h(static_cast<T>(0))
		{
		}

		/** copy constructor
		*/
		Size2DType(const Size2DType<T>& a_instance) noexcept
			:
			w(a_instance.w),
			h(a_instance.h)
		{
		}

		/** constructor
		*/
		Size2DType(T a_w,T a_h) noexcept
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

		/** t_1 = t_2;
		*/
		Size2DType<T>& operator =(const Size2DType<T>& a_right)
		{
			this->w = a_right.w;
			this->h = a_right.h;
			return *this;
		}

		/** t_1 = +t_2;
		*/
		Size2DType<T> operator +() const
		{
			return *this;
		}

		/** t_1 = -t_2;
		*/
		Size2DType<T> operator -() const
		{
			return Size2DType<T>(-this->w,-this->h);
		}

		/** t_1 += t_2;
		*/
		Size2DType<T>& operator +=(const Size2DType<T>& a_right)
		{
			this->w += a_right.w;
			this->h += a_right.h;
			return *this;
		}

		/** t_1 -= t_2;
		*/
		Size2DType<T>& operator -=(const Size2DType<T>& a_right)
		{
			this->w -= a_right.h;
			this->h -= a_right.h;
			return *this;
		}

		/** t_1 *= t_2;
		*/
		Size2DType<T>& operator *=(const Size2DType<T>& a_right)
		{
			this->w *= a_right.h;
			this->w *= a_right.h;
			return *this;
		}

		/** t_1 /= t_2;
		*/
		Size2DType<T>& operator /=(const Size2DType<T>& a_right)
		{
			this->w /= a_right.h;
			this->w /= a_right.h;
			return *this;
		}

		/** t_1 += 2;
		*/
		Size2DType<T>& operator +=(const T& a_right_value)
		{
			this->w += a_right_value;
			this->h += a_right_value;
			return *this;
		}

		/** t_1 -= 2;
		*/
		Size2DType<T>& operator -=(const T& a_right_value)
		{
			this->w -= a_right_value;
			this->h -= a_right_value;
			return *this;
		}

		/** t_1 *= 2;
		*/
		Size2DType<T>& operator *=(const T& a_right_value)
		{
			this->w *= a_right_value;
			this->w *= a_right_value;
			return *this;
		}

		/** t_1 /= 2;
		*/
		Size2DType<T>& operator /=(const T& a_right_value)
		{
			this->w /= a_right_value;
			this->h /= a_right_value;
			return *this;
		}

		/** Set
		*/
		void Set(T a_w,T a_h)
		{
			this->w = a_w;
			this->h = a_h;
		}
	};


	/** t_1 = t_2 + t_3;
	*/
	template <typename T> Size2DType<T> operator +(const Size2DType<T>& a_left,const Size2DType<T>& a_right)
	{
		return Size2DType<T>(a_left) += a_right;
	}


	/** t_1 = t_2 - t_3;
	*/
	template <typename T> Size2DType<T> operator -(const Size2DType<T>& a_left,const Size2DType<T>& a_right)
	{
		return Size2DType<T>(a_left) -= a_right;
	}


	/** t_1 = t_2 * t_3;
	*/
	template <typename T> Size2DType<T> operator *(const Size2DType<T>& a_left,const Size2DType<T>& a_right)
	{
		return Size2DType<T>(a_left) *= a_right;
	}


	/** t_1 = t_2 / t_3;
	*/
	template <typename T> Size2DType<T> operator /(const Size2DType<T>& a_left,const Size2DType<T>& a_right)
	{
		return Size2DType<T>(a_left) /= a_right;
	}


	/** t_1 = t_2 + 2;
	*/
	template <typename T> Size2DType<T> operator +(const Size2DType<T>& a_left,const T& a_right_value)
	{
		return Size2DType<T>(a_left) += a_right_value;
	}


	/** t_1 = t_2 - 2;
	*/
	template <typename T> Size2DType<T> operator -(const Size2DType<T>& a_left,const T& a_right_value)
	{
		return Size2DType<T>(a_left) -= a_right_value;
	}


	/** t_1 = t_2 * 2;
	*/
	template <typename T> Size2DType<T> operator *(const Size2DType<T>& a_left,const T& a_right_value)
	{
		return Size2DType<T>(a_left) *= a_right_value;
	}


	/** t_1 = t_2 / 2;
	*/
	template <typename T> Size2DType<T> operator /(const Size2DType<T>& a_left,const T& a_right_value)
	{
		return Size2DType<T>(a_left) /= a_right_value;
	}


}
#pragma warning(pop)

