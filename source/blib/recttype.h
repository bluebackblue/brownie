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
		/** xx
		*/
		T xx;

		/** yy
		*/
		T yy;

		/** ww
		*/
		T ww;

		/** hh
		*/
		T hh;

		/** constructor
		*/
		Rect2DType_R() noexcept
			:
			xx(static_cast<T>(0)),
			yy(static_cast<T>(0)),
			ww(static_cast<T>(0)),
			hh(static_cast<T>(0))
		{
		}

		/** constructor
		*/
		explicit Rect2DType_R(const T& a_value) noexcept
			:
			xx(a_value),
			yy(a_value),
			ww(a_value),
			hh(a_value)
		{
		}

		/** constructor
		*/
		explicit Rect2DType_R(const T& a_xx,const T& a_yy,const T& a_ww,const T& a_hh) noexcept
			:
			xx(a_xx),
			yy(a_yy),
			ww(a_ww),
			hh(a_hh)
		{
		}

		/** copy constructor
		*/
		Rect2DType_R(const Rect2DType_R<T>& a_instance) noexcept
			:
			xx(a_instance.xx),
			yy(a_instance.yy),
			ww(a_instance.ww),
			hh(a_instance.hh)
		{
		}

		/** destructor
		*/
		nonvirtual ~Rect2DType_R()
		{
		}

		/** t_1 = t_2;
		*/
		Rect2DType_R<T>& operator =(const Rect2DType_R<T>& a_right)
		{
			this->xx = a_right.xx;
			this->yy = a_right.yy;
			this->ww = a_right.ww;
			this->hh = a_right.hh;
			return *this;
		}

		/** t_1 = +t_2;
		*/
		Rect2DType_R<T> operator +() const
		{
			return *this;
		}

		/** t_1 = -t_2;
		*/
		Rect2DType_R<T> operator -() const
		{
			return Rect2DType_R<T>(-this->xx,-this->yy,-this->ww,-this->hh);
		}

		/** t_1 += t_2;
		*/
		Rect2DType_R<T>& operator +=(const Rect2DType_R<T>& a_right)
		{
			this->xx += a_right.xx;
			this->yy += a_right.yy;
			this->ww += a_right.ww;
			this->hh += a_right.hh;
			return *this;
		}

		/** t_1 -= t_2;
		*/
		Rect2DType_R<T>& operator -=(const Rect2DType_R<T>& a_right)
		{
			this->xx -= a_right.xx;
			this->yy -= a_right.yy;
			this->ww -= a_right.ww;
			this->hh -= a_right.hh;
			return *this;
		}

		/** t_1 *= t_2;
		*/
		Rect2DType_R<T>& operator *=(const Rect2DType_R<T>& a_right)
		{
			this->xx *= a_right.xx;
			this->yy *= a_right.yy;
			this->ww *= a_right.ww;
			this->hh *= a_right.hh;
			return *this;
		}

		/** t_1 /= t_2;
		*/
		Rect2DType_R<T>& operator /=(const Rect2DType_R<T>& a_right)
		{
			this->xx /= a_right.xx;
			this->yy /= a_right.yy;
			this->ww /= a_right.ww;
			this->hh /= a_right.hh;
			return *this;
		}

		/** t_1 = 2;
		*/
		Rect2DType_R<T>& operator =(const T& a_right_valuet)
		{
			this->xx = a_right_value;
			this->yy = a_right_value;
			this->ww = a_right_value;
			this->hh = a_right_value;
			return *this;
		}

		/** t_1 += 2;
		*/
		Rect2DType_R<T>& operator +=(const T& a_right_value)
		{
			this->xx += a_right_value;
			this->yy += a_right_value;
			this->ww += a_right_value;
			this->hh += a_right_value;
			return *this;
		}

		/** t_1 -= 2;
		*/
		Rect2DType_R<T>& operator -=(const T& a_right_value)
		{
			this->xx -= a_right_value;
			this->yy -= a_right_value;
			this->ww -= a_right_value;
			this->hh -= a_right_value;
			return *this;
		}

		/** t_1 *= 2;
		*/
		Rect2DType_R<T>& operator *=(const T& a_right_value)
		{
			this->xx *= a_right_value;
			this->yy *= a_right_value;
			this->ww *= a_right_value;
			this->hh *= a_right_value;
			return *this;
		}

		/** t_1 /= 2;
		*/
		Rect2DType_R<T>& operator /=(const T& a_right_value)
		{
			this->xx /= a_right_value;
			this->yy /= a_right_value;
			this->ww /= a_right_value;
			this->hh /= a_right_value;
			return *this;
		}

		/** キャスト。
		*/
		template <typename T2> explicit operator Rect2DType_R<T2>() const noexcept
		{
			return Rect2DType_R<T2>(static_cast<T2>(this->xx),static_cast<T2>(this->yy));
		}

		/** Set
		*/
		void Set(const T& a_value)
		{
			this->xx = a_value;
			this->yy = a_value;
			this->ww = a_value;
			this->hh = a_value;
		}

		/** Set
		*/
		void Set(const T& a_xx,const T& a_yy,const T& a_ww,const T& a_hh)
		{
			this->xx = a_x;
			this->yy = a_y;
			this->ww = a_w;
			this->hh = a_h;
		}
	};


	/** t_1 = t_2 + t_3;
	*/
	template <typename T> Rect2DType_R<T> operator +(const Rect2DType_R<T>& a_left,const Rect2DType_R<T>& a_right)
	{
		return Rect2DType_R<T>(a_left) += a_right;
	}


	/** t_1 = t_2 - t_3;
	*/
	template <typename T> Rect2DType_R<T> operator -(const Rect2DType_R<T>& a_left,const Rect2DType_R<T>& a_right)
	{
		return Rect2DType_R<T>(a_left) -= a_right;
	}


	/** t_1 = t_2 * t_3;
	*/
	template <typename T> Rect2DType_R<T> operator *(const Rect2DType_R<T>& a_left,const Rect2DType_R<T>& a_right)
	{
		return Rect2DType_R<T>(a_left) *= a_right;
	}


	/** t_1 = t_2 / t_3;
	*/
	template <typename T> Rect2DType_R<T> operator /(const Rect2DType_R<T>& a_left,const Rect2DType_R<T>& a_right)
	{
		return Rect2DType_R<T>(a_left) /= a_right;
	}


	/** t_1 = t_2 + 2;
	*/
	template <typename T> Rect2DType_R<T> operator +(const Rect2DType_R<T>& a_left,const T& a_right_value)
	{
		return Rect2DType_R<T>(a_left) += a_right_value;
	}


	/** t_1 = t_2 - 2;
	*/
	template <typename T> Rect2DType_R<T> operator -(const Rect2DType_R<T>& a_left,const T& a_right_value)
	{
		return Rect2DType_R<T>(a_left) -= a_right_value;
	}


	/** t_1 = t_2 * 2;
	*/
	template <typename T> Rect2DType_R<T> operator *(const Rect2DType_R<T>& a_left,const T& a_right_value)
	{
		return Rect2DType_R<T>(a_left) *= a_right_value;
	}


	/** t_1 = t_2 / 2;
	*/
	template <typename T> Rect2DType_R<T> operator /(const Rect2DType_R<T>& a_left,const T& a_right_value)
	{
		return Rect2DType_R<T>(a_left) /= a_right_value;
	}


	/** Rect2DType_A

	x1 y1 x2 y2

	*/
	template <typename T> struct Rect2DType_A
	{
		/** x
		*/
		T x1;

		/** y
		*/
		T y1;

		/** w
		*/
		T x2;

		/** h
		*/
		T y2;

		/** constructor
		*/
		Rect2DType_A() noexcept
			:
			x1(static_cast<T>(0)),
			y1(static_cast<T>(0)),
			x2(static_cast<T>(0)),
			y2(static_cast<T>(0))
		{
		}

		/** constructor
		*/
		explicit Rect2DType_A(const T& a_value) noexcept
			:
			x1(a_value),
			y1(a_value),
			x2(a_value),
			y2(a_value)
		{
		}

		/** constructor
		*/
		explicit Rect2DType_A(const T& a_x1,const T& a_y1,const T& a_x2,const T& a_y2) noexcept
			:
			x1(a_x1),
			y1(a_y1),
			x2(a_x2),
			y2(a_y2)
		{
		}

		/** copy constructor
		*/
		Rect2DType_A(const Rect2DType_A<T>& a_instance) noexcept
			:
			x1(a_instance.x1),
			y1(a_instance.y1),
			x2(a_instance.x2),
			y2(a_instance.y2)
		{
		}

		/** destructor
		*/
		nonvirtual ~Rect2DType_A()
		{
		}

		/** t_1 = t_2;
		*/
		Rect2DType_A<T>& operator =(const Rect2DType_A<T>& a_right)
		{
			this->x1 = a_right.x1;
			this->y1 = a_right.y1;
			this->x2 = a_right.x2;
			this->y2 = a_right.y2;
			return *this;
		}

		/** t_1 = +t_2;
		*/
		Rect2DType_A<T> operator +() const
		{
			return *this;
		}

		/** t_1 = -t_2;
		*/
		Rect2DType_A<T> operator -() const
		{
			return Rect2DType_A<T>(-this->x1,-this->y1,-this->x2,-this->y2);
		}

		/** t_1 += t_2;
		*/
		Rect2DType_A<T>& operator +=(const Rect2DType_A<T>& a_right)
		{
			this->x1 += a_right.x1;
			this->y1 += a_right.y1;
			this->x2 += a_right.x2;
			this->y2 += a_right.y2;
			return *this;
		}

		/** t_1 -= t_2;
		*/
		Rect2DType_A<T>& operator -=(const Rect2DType_A<T>& a_right)
		{
			this->x1 -= a_right.x1;
			this->y1 -= a_right.y1;
			this->x2 -= a_right.x2;
			this->y2 -= a_right.y2;
			return *this;
		}

		/** t_1 *= t_2;
		*/
		Rect2DType_A<T>& operator *=(const Rect2DType_A<T>& a_right)
		{
			this->x1 *= a_right.x1;
			this->y1 *= a_right.y1;
			this->x2 *= a_right.x2;
			this->y2 *= a_right.y2;
			return *this;
		}

		/** t_1 /= t_2;
		*/
		Rect2DType_A<T>& operator /=(const Rect2DType_A<T>& a_right)
		{
			this->x1 /= a_right.x1;
			this->y1 /= a_right.y1;
			this->x2 /= a_right.x2;
			this->y2 /= a_right.y2;
			return *this;
		}

		/** t_1 = 2;
		*/
		Rect2DType_A<T>& operator =(const T& a_right_valuet)
		{
			this->xx = a_right_value;
			this->yy = a_right_value;
			this->ww = a_right_value;
			this->hh = a_right_value;
			return *this;
		}

		/** t_1 += 2;
		*/
		Rect2DType_A<T>& operator +=(const T& a_right_value)
		{
			this->x1 += a_right_value;
			this->y1 += a_right_value;
			this->x2 += a_right_value;
			this->y2 += a_right_value;
			return *this;
		}

		/** t_1 -= 2;
		*/
		Rect2DType_A<T>& operator -=(const T& a_right_value)
		{
			this->x1 -= a_right_value;
			this->y1 -= a_right_value;
			this->x2 -= a_right_value;
			this->y2 -= a_right_value;
			return *this;
		}

		/** t_1 *= 2;
		*/
		Rect2DType_A<T>& operator *=(const T& a_right_value)
		{
			this->x1 *= a_right_value;
			this->y1 *= a_right_value;
			this->x2 *= a_right_value;
			this->y2 *= a_right_value;
			return *this;
		}

		/** t_1 /= 2;
		*/
		Rect2DType_A<T>& operator /=(const T& a_right_value)
		{
			this->x1 /= a_right_value;
			this->y1 /= a_right_value;
			this->x2 /= a_right_value;
			this->y2 /= a_right_value;
			return *this;
		}

		/** キャスト。
		*/
		template <typename T2> explicit operator Rect2DType_A<T2>() const noexcept
		{
			return Rect2DType_A<T2>(static_cast<T2>(this->xx),static_cast<T2>(this->yy));
		}

		/** Set
		*/
		void Set(const T& a_value)
		{
			this->x1 = a_value;
			this->y1 = a_value;
			this->x2 = a_value;
			this->y2 = a_value;
		}

		/** Set
		*/
		void Set(const T& a_x1,const T& a_y1,const T& a_x2,const T& a_y2)
		{
			this->x1 = a_x1;
			this->y1 = a_y1;
			this->x2 = a_x2;
			this->y2 = a_y2;
		}
	};


	/** t_1 = t_2 + t_3;
	*/
	template <typename T> Rect2DType_A<T> operator +(const Rect2DType_A<T>& a_left,const Rect2DType_A<T>& a_right)
	{
		return Rect2DType_A<T>(a_left) += a_right;
	}


	/** t_1 = t_2 - t_3;
	*/
	template <typename T> Rect2DType_A<T> operator -(const Rect2DType_A<T>& a_left,const Rect2DType_A<T>& a_right)
	{
		return Rect2DType_A<T>(a_left) -= a_right;
	}


	/** t_1 = t_2 * t_3;
	*/
	template <typename T> Rect2DType_A<T> operator *(const Rect2DType_A<T>& a_left,const Rect2DType_A<T>& a_right)
	{
		return Rect2DType_A<T>(a_left) *= a_right;
	}


	/** t_1 = t_2 / t_3;
	*/
	template <typename T> Rect2DType_A<T> operator /(const Rect2DType_A<T>& a_left,const Rect2DType_A<T>& a_right)
	{
		return Rect2DType_A<T>(a_left) /= a_right;
	}


	/** t_1 = t_2 + 2;
	*/
	template <typename T> Rect2DType_A<T> operator +(const Rect2DType_A<T>& a_left,const T& a_right_value)
	{
		return Rect2DType_A<T>(a_left) += a_right_value;
	}


	/** t_1 = t_2 - 2;
	*/
	template <typename T> Rect2DType_A<T> operator -(const Rect2DType_A<T>& a_left,const T& a_right_value)
	{
		return Rect2DType_A<T>(a_left) -= a_right_value;
	}


	/** t_1 = t_2 * 2;
	*/
	template <typename T> Rect2DType_A<T> operator *(const Rect2DType_A<T>& a_left,const T& a_right_value)
	{
		return Rect2DType_A<T>(a_left) *= a_right_value;
	}


	/** t_1 = t_2 / 2;
	*/
	template <typename T> Rect2DType_A<T> operator /(const Rect2DType_A<T>& a_left,const T& a_right_value)
	{
		return Rect2DType_A<T>(a_left) /= a_right_value;
	}


}
#pragma warning(pop)

