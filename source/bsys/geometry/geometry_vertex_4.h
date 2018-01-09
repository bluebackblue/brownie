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
#include "./geometry_identity.h"
#include "./geometry_vector_raw.h"


/** NBsys::NGeometry
*/
#if(BSYS_GEOMETRY_ENABLE)
namespace NBsys{namespace NGeometry
{
	/** Geometry_Vector4
	*/
	struct Geometry_Vector4
	{
		/** raw
		*/
		Geometry_Vector_4_Raw raw;

		/** x
		*/
		inline const f32& x() const;

		/** x
		*/
		inline f32& x();

		/** y
		*/
		inline const f32& y() const;

		/** y
		*/
		inline f32& y();

		/** z
		*/
		inline const f32& z() const;

		/** z
		*/
		inline f32& z();

		/** w
		*/
		inline const f32& w() const;

		/** w
		*/
		inline f32& w();

		/** constructor
		*/
		inline Geometry_Vector4() noexcept;

		/** constructor
		*/
		inline Geometry_Vector4(f32 a_xx,f32 a_yy,f32 a_zz,f32 a_ww) noexcept;

		/** constructor
		*/
		inline Geometry_Vector4(f32 a_value) noexcept;

		/** constructor
		*/
		inline Geometry_Vector4(const f32* a_value_pointer) noexcept;

		/** copy constructor
		*/
		inline Geometry_Vector4(const Geometry_Vector4& a_vector) noexcept;

		/** constructor
		*/
		inline Geometry_Vector4(const Geometry_Identity_Type& /*a_identity*/) noexcept;

		/** destructor
		*/
		inline nonvirtual ~Geometry_Vector4();

		/** t_1 = t_2;
		*/
		inline Geometry_Vector4& operator =(const Geometry_Vector4& a_right);

		/** t_1 = +t_2;
		*/
		inline Geometry_Vector4 operator +() const;

		/** t_1 = -t_2;
		*/
		inline Geometry_Vector4 operator -() const;

		/** t_1 += t_2;
		*/
		inline Geometry_Vector4& operator +=(const Geometry_Vector4& a_right);

		/** t_1 -= t_2;
		*/
		inline Geometry_Vector4& operator -=(const Geometry_Vector4& a_right);

		/** t_1 *= t_2;
		*/
		inline Geometry_Vector4& operator *=(const Geometry_Vector4& a_right);

		/** t_1 /= t_2;
		*/
		inline Geometry_Vector4& operator /=(const Geometry_Vector4& a_right);

		/** t_1 = 2;
		*/
		inline Geometry_Vector4& operator =(f32 a_right_value);

		/** t_1 += 2;
		*/
		inline Geometry_Vector4& operator +=(f32 a_right_value);

		/** t_1 -= 2;
		*/
		inline Geometry_Vector4& operator -=(f32 a_right_value);

		/** t_1 *= 2;
		*/
		inline Geometry_Vector4& operator *=(f32 a_right_value);

		/** t_1 /= 2;
		*/
		inline Geometry_Vector4& operator /=(f32 a_right_value);

		/** [static]Make_Zero。
		*/
		static inline const Geometry_Vector4& Zero();

		/** [static]Make_One。
		*/
		static inline const Geometry_Vector4& One();

		/** [設定]。
		*/
		inline Geometry_Vector4& Set(f32 a_xx,f32 a_yy,f32 a_zz,f32 a_ww);

		/** [設定]。
		*/
		inline Geometry_Vector4& Set_X(f32 a_xx);

		/** [設定]。
		*/
		inline Geometry_Vector4& Set_Y(f32 a_yy);

		/** [設定]。
		*/
		inline Geometry_Vector4& Set_Z(f32 a_zz);

		/** [設定]。
		*/
		inline Geometry_Vector4& Set_W(f32 a_ww);

		/** [設定]。
		*/
		inline Geometry_Vector4& Set(const Geometry_Vector4& a_vector);

		/** [設定]Set_Zero。
		*/
		inline Geometry_Vector4& Set_Zero();

		/** [取得]。
		*/
		inline f32 Get_X();

		/** [取得]。
		*/
		inline f32 Get_Y();

		/** [取得]。
		*/
		inline f32 Get_Z();

		/** [取得]。
		*/
		inline f32 Get_W();
	};


	/** t_1 = t_2 + t_3;
	*/
	inline Geometry_Vector4 operator +(const Geometry_Vector4& a_left,const Geometry_Vector4& a_right)
	{
		return Geometry_Vector4(a_left) += a_right;
	}


	/** t_1 = t_2 - t_3;
	*/
	inline Geometry_Vector4 operator -(const Geometry_Vector4& a_left,const Geometry_Vector4& a_right)
	{
		return Geometry_Vector4(a_left) -= a_right;
	}


	/** t_1 = t_2 * t_3;
	*/
	inline Geometry_Vector4 operator *(const Geometry_Vector4& a_left,const Geometry_Vector4& a_right)
	{
		return Geometry_Vector4(a_left) *= a_right;
	}


	/** t_1 = t_2 / t_3;
	*/
	inline Geometry_Vector4 operator /(const Geometry_Vector4& a_left,const Geometry_Vector4& a_right)
	{
		return Geometry_Vector4(a_left) /= a_right;
	}


	/** t_1 = t_2 + 2;
	*/
	inline Geometry_Vector4 operator +(const Geometry_Vector4& a_left,f32 a_right_value)
	{
		return Geometry_Vector4(a_left) += a_right_value;
	}


	/** t_1 = t_2 - 2;
	*/
	inline Geometry_Vector4 operator -(const Geometry_Vector4& a_left,f32 a_right_value)
	{
		return Geometry_Vector4(a_left) -= a_right_value;
	}


	/** t_1 = t_2 * 2;
	*/
	inline Geometry_Vector4 operator *(const Geometry_Vector4& a_left,f32 a_right_value)
	{
		return Geometry_Vector4(a_left) *= a_right_value;
	}


	/** t_1 = t_2 / 2;
	*/
	inline Geometry_Vector4 operator /(const Geometry_Vector4& a_left,f32 a_right_value)
	{
		return Geometry_Vector4(a_left) /= a_right_value;
	}


}}
#endif

