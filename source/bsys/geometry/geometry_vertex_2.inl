#pragma once

/**
 * Copyright (c) 2016-2017 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE.txt
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief ジオメトリ。
*/


/** include
*/
#pragma warning(push)
#pragma warning(disable:4464)
#include "../types/types.h"
#pragma warning(pop)


/** include
*/
#include "./geometry_vector.h"


/** NBsys::NGeometry
*/
#if(BSYS_GEOMETRY_ENABLE)
#pragma warning(push)
#pragma warning(disable:4514 4710)
namespace NBsys{namespace NGeometry
{
	/** x
	*/
	inline f32& Geometry_Vector2::x()
	{
		return this->raw.v.xx;
	}


	/** y
	*/
	inline f32& Geometry_Vector2::y()
	{
		return this->raw.v.yy;
	}


	/** x
	*/
	inline const f32& Geometry_Vector2::x() const
	{
		return this->raw.v.xx;
	}


	/** y
	*/
	inline const f32& Geometry_Vector2::y() const
	{
		return this->raw.v.yy;
	}


	/** constructor
	*/
	inline Geometry_Vector2::Geometry_Vector2() noexcept
	{
	}


	/** constructor
	*/
	inline Geometry_Vector2::Geometry_Vector2(f32 a_x,f32 a_y) noexcept
	{
		this->raw.v.xx = a_x;
		this->raw.v.yy = a_y;
	}


	/** constructor
	*/
	inline Geometry_Vector2::Geometry_Vector2(f32 a_value) noexcept
	{
		this->raw.v.xx = a_value;
		this->raw.v.yy = a_value;
	}


	/** constructor
	*/
	inline Geometry_Vector2::Geometry_Vector2(const f32* a_value_pointer) noexcept
	{
		this->raw.v.xx = a_value_pointer[0];
		this->raw.v.yy = a_value_pointer[1];
	}


	/** copy constructor
	*/
	inline Geometry_Vector2::Geometry_Vector2(const Geometry_Vector2& a_vector) noexcept
	{
		*this = a_vector;
	}


	/** constructor
	*/
	inline Geometry_Vector2::Geometry_Vector2(const Geometry_Identity_Type& /*a_identity*/) noexcept
	{
		this->Set_Zero();
	}


	/** destructor
	*/
	inline Geometry_Vector2::~Geometry_Vector2()
	{
	}


	/** t_1 = t_2;
	*/
	inline Geometry_Vector2& Geometry_Vector2::operator =(const Geometry_Vector2& a_right)
	{
		this->raw.v.xx = a_right.raw.v.xx;
		this->raw.v.yy = a_right.raw.v.yy;
		return *this;
	}


	/** t_1 = +t_2;
	*/
	inline Geometry_Vector2 Geometry_Vector2::operator +() const
	{
		return *this;
	}


	/** t_1 = -t_2;
	*/
	inline Geometry_Vector2 Geometry_Vector2::operator -() const
	{
		return Geometry_Vector2(-this->raw.v.xx,-this->raw.v.yy);
	}


	/** t_1 += t_2;
	*/
	inline Geometry_Vector2& Geometry_Vector2::operator +=(const Geometry_Vector2& a_right)
	{
		this->raw.v.xx += a_right.raw.v.xx;
		this->raw.v.yy += a_right.raw.v.yy;
		return *this;
	}


	/** t_1 -= t_2;
	*/
	inline Geometry_Vector2& Geometry_Vector2::operator -=(const Geometry_Vector2& a_right)
	{
		this->raw.v.xx -= a_right.raw.v.xx;
		this->raw.v.yy -= a_right.raw.v.yy;
		return *this;
	}


	/** t_1 *= t_2;
	*/
	inline Geometry_Vector2& Geometry_Vector2::operator *=(const Geometry_Vector2& a_right)
	{
		this->raw.v.xx *= a_right.raw.v.xx;
		this->raw.v.yy *= a_right.raw.v.yy;
		return *this;
	}


	/** t_1 /= t_2;
	*/
	inline Geometry_Vector2& Geometry_Vector2::operator /=(const Geometry_Vector2& a_right)
	{
		this->raw.v.xx /= a_right.raw.v.xx;
		this->raw.v.yy /= a_right.raw.v.yy;
		return *this;
	}


	/** t_1 = 2;
	*/
	inline Geometry_Vector2& Geometry_Vector2::operator =(f32 a_right_value)
	{
		this->raw.v.xx = a_right_value;
		this->raw.v.yy = a_right_value;
		return *this;
	}


	/** t_1 += 2;
	*/
	inline Geometry_Vector2& Geometry_Vector2::operator +=(f32 a_right_value)
	{
		this->raw.v.xx += a_right_value;
		this->raw.v.yy += a_right_value;
		return *this;
	}


	/** t_1 -= 2;
	*/
	inline Geometry_Vector2& Geometry_Vector2::operator -=(f32 a_right_value)
	{
		this->raw.v.xx -= a_right_value;
		this->raw.v.yy -= a_right_value;
		return *this;
	}


	/** t_1 *= 2;
	*/
	inline Geometry_Vector2& Geometry_Vector2::operator *=(f32 a_right_value)
	{
		this->raw.v.xx *= a_right_value;
		this->raw.v.yy *= a_right_value;
		return *this;
	}


	/** t_1 /= 2;
	*/
	inline Geometry_Vector2& Geometry_Vector2::operator /=(f32 a_right_value)
	{
		this->raw.v.xx /= a_right_value;
		this->raw.v.yy /= a_right_value;
		return *this;
	}


	/** [static]Zero。
	*/
	inline const Geometry_Vector2& Geometry_Vector2::Zero()
	{
		static const NGeometry::Geometry_Vector2 s_zero(0.0f,0.0f);

		return s_zero;
	}


	/** [static]One。
	*/
	inline const Geometry_Vector2& Geometry_Vector2::One()
	{
		static const NGeometry::Geometry_Vector2 s_one(1.0f,1.0f);

		return s_one;
	}


	/** [設定]。
	*/
	inline Geometry_Vector2& Geometry_Vector2::Set(f32 a_x,f32 a_y)
	{
		this->raw.v.xx = a_x;
		this->raw.v.yy = a_y;

		return *this;
	}


	/** [設定]。
	*/
	inline Geometry_Vector2& Geometry_Vector2::Set_X(f32 a_x)
	{
		this->raw.v.xx = a_x;

		return *this;
	}


	/** [設定]。
	*/
	inline Geometry_Vector2& Geometry_Vector2::Set_Y(f32 a_y)
	{
		this->raw.v.yy = a_y;

		return *this;
	}


	/** [設定]。
	*/
	inline Geometry_Vector2& Geometry_Vector2::Set(const Geometry_Vector2& a_vector)
	{
		this->raw.v.xx = a_vector.raw.v.xx;
		this->raw.v.yy = a_vector.raw.v.yy;

		return *this;
	}


	/** [設定]Set_Zero。
	*/
	inline Geometry_Vector2& Geometry_Vector2::Set_Zero()
	{
		*this = Geometry_Vector2::Zero();

		return *this;
	}


	/** [取得]。
	*/
	inline f32 Geometry_Vector2::Get_X()
	{
		return this->raw.v.xx;
	}


	/** [取得]。
	*/
	inline f32 Geometry_Vector2::Get_Y()
	{
		return this->raw.v.yy;
	}


}}


/** NBsys::NGeometry
*/
namespace NBsys{namespace NGeometry
{
	/** t_1 = t_2 + t_3;
	*/
	inline Geometry_Vector2 operator +(const Geometry_Vector2& a_left,const Geometry_Vector2& a_right)
	{
		return Geometry_Vector2(a_left) += a_right;
	}


	/** t_1 = t_2 - t_3;
	*/
	inline Geometry_Vector2 operator -(const Geometry_Vector2& a_left,const Geometry_Vector2& a_right)
	{
		return Geometry_Vector2(a_left) -= a_right;
	}


	/** t_1 = t_2 * t_3;
	*/
	inline Geometry_Vector2 operator *(const Geometry_Vector2& a_left,const Geometry_Vector2& a_right)
	{
		return Geometry_Vector2(a_left) *= a_right;
	}


	/** t_1 = t_2 / t_3;
	*/
	inline Geometry_Vector2 operator /(const Geometry_Vector2& a_left,const Geometry_Vector2& a_right)
	{
		return Geometry_Vector2(a_left) /= a_right;
	}


	/** t_1 = t_2 + 2;
	*/
	inline Geometry_Vector2 operator +(const Geometry_Vector2& a_left,f32 a_right_value)
	{
		return Geometry_Vector2(a_left) += a_right_value;
	}


	/** t_1 = t_2 - 2;
	*/
	inline Geometry_Vector2 operator -(const Geometry_Vector2& a_left,f32 a_right_value)
	{
		return Geometry_Vector2(a_left) -= a_right_value;
	}


	/** t_1 = t_2 * 2;
	*/
	inline Geometry_Vector2 operator *(const Geometry_Vector2& a_left,f32 a_right_value)
	{
		return Geometry_Vector2(a_left) *= a_right_value;
	}


	/** t_1 = t_2 / 2;
	*/
	inline Geometry_Vector2 operator /(const Geometry_Vector2& a_left,f32 a_right_value)
	{
		return Geometry_Vector2(a_left) /= a_right_value;
	}


}}
#pragma warning(pop)
#endif

