﻿#pragma once

/**
 * Copyright (c) blueback
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
	inline const f32& Geometry_Vector4::x() const
	{
		return this->raw.v.xx;
	}


	/** x
	*/
	inline f32& Geometry_Vector4::x()
	{
		return this->raw.v.xx;
	}


	/** y
	*/
	inline const f32& Geometry_Vector4::y() const
	{
		return this->raw.v.yy;
	}


	/** y
	*/
	inline f32& Geometry_Vector4::y()
	{
		return this->raw.v.yy;
	}


	/** z
	*/
	inline const f32& Geometry_Vector4::z() const
	{
		return this->raw.v.zz;
	}


	/** z
	*/
	inline f32& Geometry_Vector4::z()
	{
		return this->raw.v.zz;
	}


	/** w
	*/
	inline const f32& Geometry_Vector4::w() const
	{
		return this->raw.v.ww;
	}


	/** w
	*/
	inline f32& Geometry_Vector4::w()
	{
		return this->raw.v.ww;
	}


	/** constructor
	*/
	inline Geometry_Vector4::Geometry_Vector4() noexcept
	{
	}


	/** constructor
	*/
	inline Geometry_Vector4::Geometry_Vector4(f32 a_xx,f32 a_yy,f32 a_zz,f32 a_ww) noexcept
	{
		this->raw.v.xx = a_xx;
		this->raw.v.yy = a_yy;
		this->raw.v.zz = a_zz;
		this->raw.v.ww = a_ww;
	}


	/** constructor
	*/
	inline Geometry_Vector4::Geometry_Vector4(f32 a_value) noexcept
	{
		this->raw.v.xx = a_value;
		this->raw.v.yy = a_value;
		this->raw.v.zz = a_value;
		this->raw.v.ww = a_value;
	}


	/** constructor
	*/
	inline Geometry_Vector4::Geometry_Vector4(const f32* a_value_pointer) noexcept
	{
		this->raw.v.xx = a_value_pointer[0];
		this->raw.v.yy = a_value_pointer[1];
		this->raw.v.zz = a_value_pointer[2];
		this->raw.v.ww = a_value_pointer[3];
	}


	/** constructor
	*/
	inline Geometry_Vector4::Geometry_Vector4(const Geometry_Vector4& a_vector) noexcept
	{
		this->raw.v.xx = a_vector.raw.v.xx;
		this->raw.v.yy = a_vector.raw.v.yy;
		this->raw.v.zz = a_vector.raw.v.zz;
		this->raw.v.ww = a_vector.raw.v.ww;
	}


	/** constructor
	*/
	inline Geometry_Vector4::Geometry_Vector4(const Geometry_Identity_Type& /*a_identity*/) noexcept
	{
		this->Set_Zero();
	}


	/** destructor
	*/
	inline Geometry_Vector4::~Geometry_Vector4()
	{
	}


	/** t_1 = t_2;
	*/
	inline Geometry_Vector4& Geometry_Vector4::operator =(const Geometry_Vector4& a_right)
	{
		this->raw.v.xx = a_right.raw.v.xx;
		this->raw.v.yy = a_right.raw.v.yy;
		this->raw.v.zz = a_right.raw.v.zz;
		return *this;
	}


	/** t_1 = +t_2;
	*/
	inline Geometry_Vector4 Geometry_Vector4::operator +() const
	{
		return *this;
	}


	/** t_1 = -t_2;
	*/
	inline Geometry_Vector4 Geometry_Vector4::operator -() const
	{
		return Geometry_Vector4(-this->raw.v.xx,-this->raw.v.yy,-this->raw.v.zz,-this->raw.v.ww);
	}


	/** t_1 += t_2;
	*/
	inline Geometry_Vector4& Geometry_Vector4::operator +=(const Geometry_Vector4& a_right)
	{
		this->raw.v.xx += a_right.raw.v.xx;
		this->raw.v.yy += a_right.raw.v.yy;
		this->raw.v.zz += a_right.raw.v.zz;
		return *this;
	}


	/** t_1 -= t_2;
	*/
	inline Geometry_Vector4& Geometry_Vector4::operator -=(const Geometry_Vector4& a_right)
	{
		this->raw.v.xx -= a_right.raw.v.xx;
		this->raw.v.yy -= a_right.raw.v.yy;
		this->raw.v.zz -= a_right.raw.v.zz;
		return *this;
	}


	/** t_1 *= t_2;
	*/
	inline Geometry_Vector4& Geometry_Vector4::operator *=(const Geometry_Vector4& a_right)
	{
		this->raw.v.xx *= a_right.raw.v.xx;
		this->raw.v.yy *= a_right.raw.v.yy;
		this->raw.v.zz *= a_right.raw.v.zz;
		return *this;
	}


	/** t_1 /= t_2;
	*/
	inline Geometry_Vector4& Geometry_Vector4::operator /=(const Geometry_Vector4& a_right)
	{
		this->raw.v.xx /= a_right.raw.v.xx;
		this->raw.v.yy /= a_right.raw.v.yy;
		this->raw.v.zz /= a_right.raw.v.zz;
		return *this;
	}


	/** t_1 = 2;
	*/
	inline Geometry_Vector4& Geometry_Vector4::operator =(f32 a_right_value)
	{
		this->raw.v.xx = a_right_value;
		this->raw.v.yy = a_right_value;
		this->raw.v.zz = a_right_value;
		return *this;
	}


	/** t_1 += 2;
	*/
	inline Geometry_Vector4& Geometry_Vector4::operator +=(f32 a_right_value)
	{
		this->raw.v.xx += a_right_value;
		this->raw.v.yy += a_right_value;
		this->raw.v.zz += a_right_value;
		return *this;
	}


	/** t_1 -= 2;
	*/
	inline Geometry_Vector4& Geometry_Vector4::operator -=(f32 a_right_value)
	{
		this->raw.v.xx -= a_right_value;
		this->raw.v.yy -= a_right_value;
		this->raw.v.zz -= a_right_value;
		return *this;
	}


	/** t_1 *= 2;
	*/
	inline Geometry_Vector4& Geometry_Vector4::operator *=(f32 a_right_value)
	{
		this->raw.v.xx *= a_right_value;
		this->raw.v.yy *= a_right_value;
		this->raw.v.zz *= a_right_value;
		return *this;
	}


	/** t_1 /= 2;
	*/
	inline Geometry_Vector4& Geometry_Vector4::operator /=(f32 a_right_value)
	{
		this->raw.v.xx /= a_right_value;
		this->raw.v.yy /= a_right_value;
		this->raw.v.zz /= a_right_value;
		return *this;
	}


	/** [static]Zero。
	*/
	inline const Geometry_Vector4& Geometry_Vector4::Zero()
	{
		static const NGeometry::Geometry_Vector4 s_zero(0.0f,0.0f,0.0f,0.0f);

		return s_zero;
	}


	/** [static]One。
	*/
	inline const Geometry_Vector4& Geometry_Vector4::One()
	{
		static const NGeometry::Geometry_Vector4 s_one(1.0f,1.0f,1.0f,1.0f);

		return s_one;
	}


	/** [設定]。
	*/
	inline Geometry_Vector4& Geometry_Vector4::Set(f32 a_xx,f32 a_yy,f32 a_zz,f32 a_ww)
	{
		this->raw.v.xx = a_xx;
		this->raw.v.yy = a_yy;
		this->raw.v.zz = a_zz;
		this->raw.v.ww = a_ww;

		return *this;
	}


	/** [設定]。
	*/
	inline Geometry_Vector4& Geometry_Vector4::Set_X(f32 a_xx)
	{
		this->raw.v.xx = a_xx;

		return *this;
	}


	/** [設定]。
	*/
	inline Geometry_Vector4& Geometry_Vector4::Set_Y(f32 a_yy)
	{
		this->raw.v.yy = a_yy;

		return *this;
	}


	/** [設定]。
	*/
	inline Geometry_Vector4& Geometry_Vector4::Set_Z(f32 a_zz)
	{
		this->raw.v.zz = a_zz;

		return *this;
	}


	/** [設定]。
	*/
	inline Geometry_Vector4& Geometry_Vector4::Set_W(f32 a_ww)
	{
		this->raw.v.ww = a_ww;

		return *this;
	}


	/** [設定]。
	*/
	inline Geometry_Vector4& Geometry_Vector4::Set(const Geometry_Vector4& a_vector)
	{
		this->raw.v.xx = a_vector.raw.v.xx;
		this->raw.v.yy = a_vector.raw.v.yy;
		this->raw.v.zz = a_vector.raw.v.zz;
		this->raw.v.ww = a_vector.raw.v.ww;

		return *this;
	}


	/** [設定]Set_Zero。
	*/
	inline Geometry_Vector4& Geometry_Vector4::Set_Zero()
	{
		*this = Geometry_Vector4::Zero();

		return *this;
	}


	/** [取得]。
	*/
	inline f32 Geometry_Vector4::Get_X()
	{
		return this->raw.v.xx;
	}


	/** [取得]。
	*/
	inline f32 Geometry_Vector4::Get_Y()
	{
		return this->raw.v.yy;
	}


	/** [取得]。
	*/
	inline f32 Geometry_Vector4::Get_Z()
	{
		return this->raw.v.zz;
	}


	/** [取得]。
	*/
	inline f32 Geometry_Vector4::Get_W()
	{
		return this->raw.v.ww;
	}


}}
#pragma warning(pop)
#endif

