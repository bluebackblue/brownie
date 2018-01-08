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
	inline const f32& Geometry_Vector3::x() const
	{
		return this->raw.v.xx;
	}


	/** x
	*/
	inline f32& Geometry_Vector3::x()
	{
		return this->raw.v.xx;
	}


	/** y
	*/
	inline const f32& Geometry_Vector3::y() const
	{
		return this->raw.v.yy;
	}


	/** y
	*/
	inline f32& Geometry_Vector3::y()
	{
		return this->raw.v.yy;
	}


	/** z
	*/
	inline const f32& Geometry_Vector3::z() const
	{
		return this->raw.v.zz;
	}


	/** z
	*/
	inline f32& Geometry_Vector3::z()
	{
		return this->raw.v.zz;
	}


	/** constructor
	*/
	inline Geometry_Vector3::Geometry_Vector3() noexcept
	{
	}


	/** constructor
	*/
	inline Geometry_Vector3::Geometry_Vector3(f32 a_x,f32 a_y,f32 a_z) noexcept
	{
		this->raw.v.xx = a_x;
		this->raw.v.yy = a_y;
		this->raw.v.zz = a_z;
	}


	/** constructor
	*/
	inline Geometry_Vector3::Geometry_Vector3(f32 a_value) noexcept
	{
		this->raw.v.xx = a_value;
		this->raw.v.yy = a_value;
		this->raw.v.zz = a_value;
	}


	/** constructor
	*/
	inline Geometry_Vector3::Geometry_Vector3(const f32* a_value_pointer) noexcept
	{
		this->raw.v.xx = a_value_pointer[0];
		this->raw.v.yy = a_value_pointer[1];
		this->raw.v.zz = a_value_pointer[2];
	}


	/** copy constructor
	*/
	inline Geometry_Vector3::Geometry_Vector3(const Geometry_Vector3& a_vector) noexcept
	{
		this->raw.v.xx = a_vector.raw.v.xx;
		this->raw.v.yy = a_vector.raw.v.yy;
		this->raw.v.zz = a_vector.raw.v.zz;
	}


	/** constructor
	*/
	inline Geometry_Vector3::Geometry_Vector3(const Geometry_Identity_Type& /*a_identity*/) noexcept
	{
		this->Set_Zero();
	}


	/** destructor
	*/
	inline Geometry_Vector3::~Geometry_Vector3()
	{
	}


	/** t_1 = t_2;
	*/
	inline Geometry_Vector3& Geometry_Vector3::operator =(const Geometry_Vector3& a_right)
	{
		this->raw.v.xx = a_right.raw.v.xx;
		this->raw.v.yy = a_right.raw.v.yy;
		this->raw.v.zz = a_right.raw.v.zz;
		return *this;
	}


	/** t_1 = +t_2;
	*/
	inline Geometry_Vector3 Geometry_Vector3::operator +() const
	{
		return *this;
	}


	/** t_1 = -t_2;
	*/
	inline Geometry_Vector3 Geometry_Vector3::operator -() const
	{
		return Geometry_Vector3(-this->raw.v.xx,-this->raw.v.yy,-this->raw.v.zz);
	}


	/** t_1 += t_2;
	*/
	inline Geometry_Vector3& Geometry_Vector3::operator +=(const Geometry_Vector3& a_right)
	{
		this->raw.v.xx += a_right.raw.v.xx;
		this->raw.v.yy += a_right.raw.v.yy;
		this->raw.v.zz += a_right.raw.v.zz;
		return *this;
	}


	/** t_1 -= t_2;
	*/
	inline Geometry_Vector3& Geometry_Vector3::operator -=(const Geometry_Vector3& a_right)
	{
		this->raw.v.xx -= a_right.raw.v.xx;
		this->raw.v.yy -= a_right.raw.v.yy;
		this->raw.v.zz -= a_right.raw.v.zz;
		return *this;
	}


	/** t_1 *= t_2;
	*/
	inline Geometry_Vector3& Geometry_Vector3::operator *=(const Geometry_Vector3& a_right)
	{
		this->raw.v.xx *= a_right.raw.v.xx;
		this->raw.v.yy *= a_right.raw.v.yy;
		this->raw.v.zz *= a_right.raw.v.zz;
		return *this;
	}


	/** t_1 /= t_2;
	*/
	inline Geometry_Vector3& Geometry_Vector3::operator /=(const Geometry_Vector3& a_right)
	{
		this->raw.v.xx /= a_right.raw.v.xx;
		this->raw.v.yy /= a_right.raw.v.yy;
		this->raw.v.zz /= a_right.raw.v.zz;
		return *this;
	}


	/** t_1 = 2;
	*/
	inline Geometry_Vector3& Geometry_Vector3::operator =(f32 a_right_value)
	{
		this->raw.v.xx = a_right_value;
		this->raw.v.yy = a_right_value;
		this->raw.v.zz = a_right_value;
		return *this;
	}


	/** t_1 += 2;
	*/
	inline Geometry_Vector3& Geometry_Vector3::operator +=(f32 a_right_value)
	{
		this->raw.v.xx += a_right_value;
		this->raw.v.yy += a_right_value;
		this->raw.v.zz += a_right_value;
		return *this;
	}


	/** t_1 -= 2;
	*/
	inline Geometry_Vector3& Geometry_Vector3::operator -=(f32 a_right_value)
	{
		this->raw.v.xx -= a_right_value;
		this->raw.v.yy -= a_right_value;
		this->raw.v.zz -= a_right_value;
		return *this;
	}


	/** t_1 *= 2;
	*/
	inline Geometry_Vector3& Geometry_Vector3::operator *=(f32 a_right_value)
	{
		this->raw.v.xx *= a_right_value;
		this->raw.v.yy *= a_right_value;
		this->raw.v.zz *= a_right_value;
		return *this;
	}


	/** t_1 /= 2;
	*/
	inline Geometry_Vector3& Geometry_Vector3::operator /=(f32 a_right_value)
	{
		this->raw.v.xx /= a_right_value;
		this->raw.v.yy /= a_right_value;
		this->raw.v.zz /= a_right_value;
		return *this;
	}


	/** [static]Zero。
	*/
	inline const Geometry_Vector3& Geometry_Vector3::Zero()
	{
		static const NGeometry::Geometry_Vector3 s_zero(0.0f,0.0f,0.0f);

		return s_zero;
	}


	/** [static]One。
	*/
	inline const Geometry_Vector3& Geometry_Vector3::One()
	{
		static const NGeometry::Geometry_Vector3 s_one(1.0f,1.0f,1.0f);

		return s_one;
	}


	/** [設定]。
	*/
	inline Geometry_Vector3& Geometry_Vector3::Set(f32 a_x,f32 a_y,f32 a_z)
	{
		this->raw.v.xx = a_x;
		this->raw.v.yy = a_y;
		this->raw.v.zz = a_z;

		return *this;
	}


	/** [設定]。
	*/
	inline Geometry_Vector3& Geometry_Vector3::Set_X(f32 a_x)
	{
		this->raw.v.xx = a_x;

		return *this;
	}


	/** [設定]。
	*/
	inline Geometry_Vector3& Geometry_Vector3::Set_Y(f32 a_y)
	{
		this->raw.v.yy = a_y;

		return *this;
	}


	/** [設定]。
	*/
	inline Geometry_Vector3& Geometry_Vector3::Set_Z(f32 a_z)
	{
		this->raw.v.zz = a_z;

		return *this;
	}


	/** [設定]。
	*/
	inline Geometry_Vector3& Geometry_Vector3::Set(const Geometry_Vector3& a_vector)
	{
		this->raw.v.xx = a_vector.raw.v.xx;
		this->raw.v.yy = a_vector.raw.v.yy;
		this->raw.v.zz = a_vector.raw.v.zz;

		return *this;
	}


	/** [設定]Set_Zero。
	*/
	inline Geometry_Vector3& Geometry_Vector3::Set_Zero()
	{
		*this = Geometry_Vector3::Zero();

		return *this;
	}


	/** [取得]。
	*/
	inline f32 Geometry_Vector3::Get_X()
	{
		return this->raw.v.xx;
	}


	/** [取得]。
	*/
	inline f32 Geometry_Vector3::Get_Y()
	{
		return this->raw.v.yy;
	}


	/** [取得]。
	*/
	inline f32 Geometry_Vector3::Get_Z()
	{
		return this->raw.v.zz;
	}


	/** [作成]外積。
	*/
	inline Geometry_Vector3 Geometry_Vector3::Make_Cross(const Geometry_Vector3& a_vector) const
	{
		Geometry_Vector3 t_temp;
		{
			t_temp.raw.v.xx = (this->raw.v.yy * a_vector.raw.v.zz) - (this->raw.v.zz * a_vector.raw.v.yy);
			t_temp.raw.v.yy = (this->raw.v.zz * a_vector.raw.v.xx) - (this->raw.v.xx * a_vector.raw.v.zz);
			t_temp.raw.v.zz = (this->raw.v.xx * a_vector.raw.v.yy) - (this->raw.v.yy * a_vector.raw.v.xx);
		}
		return t_temp;
	}


	/** [設定]外積。
	*/
	inline Geometry_Vector3& Geometry_Vector3::Set_Cross(const Geometry_Vector3& a_vector)
	{
		f32 t_temp_x = (this->raw.v.yy * a_vector.raw.v.zz) - (this->raw.v.zz * a_vector.raw.v.yy);
		f32 t_temp_y = (this->raw.v.zz * a_vector.raw.v.xx) - (this->raw.v.xx * a_vector.raw.v.zz);
		f32 t_temp_z = (this->raw.v.xx * a_vector.raw.v.yy) - (this->raw.v.yy * a_vector.raw.v.xx);

		this->raw.v.xx = t_temp_x;
		this->raw.v.yy = t_temp_y;
		this->raw.v.zz = t_temp_z;

		return *this;
	}


	/** [設定]外積。
	*/
	inline Geometry_Vector3& Geometry_Vector3::Set_Cross(const Geometry_Vector3& a_vector_1,const Geometry_Vector3& a_vector_2)
	{
		f32 t_temp_x = (a_vector_1.raw.v.yy * a_vector_2.raw.v.zz) - (a_vector_1.raw.v.zz * a_vector_2.raw.v.yy);
		f32 t_temp_y = (a_vector_1.raw.v.zz * a_vector_2.raw.v.xx) - (a_vector_1.raw.v.xx * a_vector_2.raw.v.zz);
		f32 t_temp_z = (a_vector_1.raw.v.xx * a_vector_2.raw.v.yy) - (a_vector_1.raw.v.yy * a_vector_2.raw.v.xx);

		this->raw.v.xx = t_temp_x;
		this->raw.v.yy = t_temp_y;
		this->raw.v.zz = t_temp_z;

		return *this;
	}


	/** [設定]正規化。
	*/
	inline Geometry_Vector3& Geometry_Vector3::Set_Normalize()
	{
		f32 t_value = this->SquareLength();
		ASSERT(t_value != 0.0f);

		t_value = NMath::sqrt_f(t_value);
		ASSERT(t_value != 0.0f);

		t_value = 1.0f / t_value;

		this->raw.v.xx *= t_value;
		this->raw.v.yy *= t_value;
		this->raw.v.zz *= t_value;

		return *this;
	}


	/** [設定]正規化。
	*/
	inline Geometry_Vector3& Geometry_Vector3::Set_Normalize_Safe(const Geometry_Vector3& a_vector_safe)
	{
		f32 t_value = this->SquareLength();
		if(t_value == 0.0f){
			*this = a_vector_safe;
			return *this;
		}

		t_value = NMath::sqrt_f(t_value);
		if(t_value == 0.0f){
			*this = a_vector_safe;
			return *this;
		}

		t_value = 1.0f / t_value;

		this->raw.v.xx *= t_value;
		this->raw.v.yy *= t_value;
		this->raw.v.zz *= t_value;

		return *this;
	}


	/** [設定]正規化。
	*/
	inline f32 Geometry_Vector3::Set_Normalize_GetLength()
	{
		f32 t_value = this->SquareLength();
		if(t_value == 0.0f){
			return 0.0f;
		}

		t_value = NMath::sqrt_f(t_value);
		if(t_value == 0.0f){
			return 0.0f;
		}

		f32 t_length = t_value;

		t_value = 1.0f / t_value;

		this->raw.v.xx *= t_value;
		this->raw.v.yy *= t_value;
		this->raw.v.zz *= t_value;

		return t_length;
	}


	/** [作成]正規化。
	*/
	inline Geometry_Vector3 Geometry_Vector3::Make_Normalize() const
	{
		Geometry_Vector3 t_temp;
		{
			f32 t_value = this->SquareLength();
			ASSERT(t_value != 0.0f);

			t_value = NMath::sqrt_f(t_value);
			ASSERT(t_value != 0.0f);

			t_value = 1.0f / t_value;

			t_temp.raw.v.xx = this->raw.v.xx * t_value;
			t_temp.raw.v.yy = this->raw.v.yy * t_value;
			t_temp.raw.v.zz = this->raw.v.zz * t_value;
		}
		return t_temp;
	}


	/** [作成]正規化。
	*/
	inline Geometry_Vector3 Geometry_Vector3::Make_Normalize_Safe(const Geometry_Vector3& a_vector_safe) const
	{
		Geometry_Vector3 t_temp;
		{
			f32 t_value = this->SquareLength();
			if(t_value == 0.0f){
				return a_vector_safe;
			}

			t_value = NMath::sqrt_f(t_value);
			if(t_value == 0.0f){
				return a_vector_safe;
			}

			t_value = 1.0f / t_value;

			t_temp.raw.v.xx = this->raw.v.xx * t_value;
			t_temp.raw.v.yy = this->raw.v.yy * t_value;
			t_temp.raw.v.zz = this->raw.v.zz * t_value;
		}
		return t_temp;
	}


	/** [内積]length(this)*length(a_vector)*cos(θ)。
	*/
	inline f32 Geometry_Vector3::Dot(const Geometry_Vector3& a_vector) const
	{
		f32 t_value = (this->raw.v.xx * a_vector.raw.v.xx) + (this->raw.v.yy * a_vector.raw.v.yy) + (this->raw.v.zz * a_vector.raw.v.zz);

		return t_value;
	}


	/** [チェック]。
	*/
	inline bool Geometry_Vector3::IsZero() const
	{
		return (this->raw.v.xx == 0.0f)&&(this->raw.v.yy == 0.0f)&&(this->raw.v.zz == 0.0f);
	}


	/** [作成]長さ。
	*/
	inline f32 Geometry_Vector3::Length() const
	{
		f32 t_value = this->SquareLength();

		t_value = NMath::sqrt_f(t_value);

		return t_value;
	}


	/** [作成]長さの２乗。
	*/
	inline f32 Geometry_Vector3::SquareLength() const
	{
		return (this->raw.v.xx * this->raw.v.xx) + (this->raw.v.yy * this->raw.v.yy) + (this->raw.v.zz * this->raw.v.zz);
	}


	/** [作成]２点間の距離の２乗。
	*/
	inline f32 Geometry_Vector3::SquareDistance(const Geometry_Vector3& a_vector) const
	{
		f32 t_temp_x = (this->raw.v.xx - a_vector.raw.v.xx);
		f32 t_temp_y = (this->raw.v.yy - a_vector.raw.v.yy);
		f32 t_temp_z = (this->raw.v.zz - a_vector.raw.v.zz);

		f32 t_value = (t_temp_x * t_temp_x) + (t_temp_y * t_temp_y) + (t_temp_z * t_temp_z);

		return t_value;
	}


	/** [作成]Make_Lerp。

	a_per = 0.0f : return = this
	a_per = 1.0f : return = a_vector

	*/
	inline Geometry_Vector3 Geometry_Vector3::Make_Lerp(const Geometry_Vector3& a_vector,f32 a_per) const
	{
		Geometry_Vector3 t_temp;
		{
			t_temp.raw.v.xx = this->raw.v.xx + (a_vector.raw.v.xx - this->raw.v.xx) * a_per;
			t_temp.raw.v.yy = this->raw.v.yy + (a_vector.raw.v.yy - this->raw.v.yy) * a_per;
			t_temp.raw.v.zz = this->raw.v.zz + (a_vector.raw.v.zz - this->raw.v.zz) * a_per;
		}
		return t_temp;
	}


	/** [static][作成]Lerp

	a_per = 0.0f : return = this
	a_per = 1.0f : return = a_vector

	*/
	inline Geometry_Vector3 Geometry_Vector3::Make_Lerp(const Geometry_Vector3& a_vector_1,const Geometry_Vector3& a_vector_2,f32 a_per)
	{
		Geometry_Vector3 t_temp;
		{
			t_temp.raw.v.xx = a_vector_1.raw.v.xx + (a_vector_2.raw.v.xx - a_vector_1.raw.v.xx) * a_per;
			t_temp.raw.v.yy = a_vector_1.raw.v.yy + (a_vector_2.raw.v.yy - a_vector_1.raw.v.yy) * a_per;
			t_temp.raw.v.zz = a_vector_1.raw.v.zz + (a_vector_2.raw.v.zz - a_vector_1.raw.v.zz) * a_per;
		}
		return t_temp;
	}


	/** [設定]Set_Lerp。

	a_per = 0.0f : this = this
	a_per = 1.0f : this = a_vector

	*/
	inline void Geometry_Vector3::Set_Lerp(const Geometry_Vector3& a_vector,f32 a_per)
	{
		this->raw.v.xx += (a_vector.raw.v.xx - this->raw.v.xx) * a_per;
		this->raw.v.yy += (a_vector.raw.v.yy - this->raw.v.yy) * a_per;
		this->raw.v.zz += (a_vector.raw.v.zz - this->raw.v.zz) * a_per;
	}


	/** [設定]Lerp。

	a_per = 0.0f : this = a_vector_1
	a_per = 1.0f : this = a_vector_2

	*/
	inline void Geometry_Vector3::Set_Lerp(const Geometry_Vector3& a_vector_1,const Geometry_Vector3& a_vector_2,f32 a_per)
	{
		this->raw.v.xx = a_vector_1.raw.v.xx + (a_vector_2.raw.v.xx - a_vector_1.raw.v.xx) * a_per;
		this->raw.v.yy = a_vector_1.raw.v.yy + (a_vector_2.raw.v.yy - a_vector_1.raw.v.yy) * a_per;
		this->raw.v.zz = a_vector_1.raw.v.zz + (a_vector_2.raw.v.zz - a_vector_1.raw.v.zz) * a_per;
	}


}}
#pragma warning(pop)
#endif

