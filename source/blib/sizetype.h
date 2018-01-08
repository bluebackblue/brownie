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
		/** ww
		*/
		T ww;

		/** h
		*/
		T hh;

		/** constructor
		*/
		Size2DType() noexcept
			:
			ww(static_cast<T>(0)),
			hh(static_cast<T>(0))
		{
		}

		/** constructor
		*/
		explicit Size2DType(const T& a_value) noexcept
			:
			ww(a_value),
			hh(a_value)
		{
		}

		/** constructor
		*/
		explicit Size2DType(const T& a_ww,const T& a_hh) noexcept
			:
			ww(a_ww),
			hh(a_hh)
		{
		}

		/** copy constructor
		*/
		Size2DType(const Size2DType<T>& a_instance) noexcept
			:
			ww(a_instance.ww),
			hh(a_instance.hh)
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
			this->ww = a_right.ww;
			this->hh = a_right.hh;
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
			return Size2DType<T>(-this->ww,-this->hh);
		}

		/** t_1 += t_2;
		*/
		Size2DType<T>& operator +=(const Size2DType<T>& a_right)
		{
			this->ww += a_right.ww;
			this->hh += a_right.hh;
			return *this;
		}

		/** t_1 -= t_2;
		*/
		Size2DType<T>& operator -=(const Size2DType<T>& a_right)
		{
			this->ww -= a_right.ww;
			this->hh -= a_right.hh;
			return *this;
		}

		/** t_1 *= t_2;
		*/
		Size2DType<T>& operator *=(const Size2DType<T>& a_right)
		{
			this->ww *= a_right.ww;
			this->hh *= a_right.hh;
			return *this;
		}

		/** t_1 /= t_2;
		*/
		Size2DType<T>& operator /=(const Size2DType<T>& a_right)
		{
			this->ww /= a_right.ww;
			this->hh /= a_right.hh;
			return *this;
		}

		/** t_1 = 2;
		*/
		Size2DType<T>& operator =(const T& a_right_value)
		{
			this->ww = a_right_value;
			this->hh = a_right_value;
			return *this;
		}

		/** t_1 += 2;
		*/
		Size2DType<T>& operator +=(const T& a_right_value)
		{
			this->ww += a_right_value;
			this->hh += a_right_value;
			return *this;
		}

		/** t_1 -= 2;
		*/
		Size2DType<T>& operator -=(const T& a_right_value)
		{
			this->ww -= a_right_value;
			this->hh -= a_right_value;
			return *this;
		}

		/** t_1 *= 2;
		*/
		Size2DType<T>& operator *=(const T& a_right_value)
		{
			this->ww *= a_right_value;
			this->hh *= a_right_value;
			return *this;
		}

		/** t_1 /= 2;
		*/
		Size2DType<T>& operator /=(const T& a_right_value)
		{
			this->ww /= a_right_value;
			this->hh /= a_right_value;
			return *this;
		}

		/** キャスト。
		*/
		template <typename T2> explicit operator Size2DType<T2>() const noexcept
		{
			return Size2DType<T2>(static_cast<T2>(this->ww),static_cast<T2>(this->hh));
		}

		/** Set
		*/
		void Set(const T& a_value)
		{
			this->ww = a_value;
			this->hh = a_value;
		}

		/** Set
		*/
		void Set(const T& a_ww,const T& a_hh)
		{
			this->ww = a_ww;
			this->hh = a_hh;
		}

		/** 加算。
		*/
		void Add(const T& a_ww,const T& a_hh)
		{
			this->ww += a_ww;
			this->hh += a_hh;
		}

		/** 減算。
		*/
		void Sub(const T& a_ww,const T& a_hh)
		{
			this->ww -= a_ww;
			this->hh -= a_hh;
		}

		/** 乗算。
		*/
		void Mul(const T& a_ww,const T& a_hh)
		{
			this->ww *= a_ww;
			this->hh *= a_hh;
		}

		/** 除算。
		*/
		void Div(const T& a_ww,const T& a_hh)
		{
			this->ww /= a_ww;
			this->hh /= a_hh;
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

