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
#include "./geometry_quaternion.h"


/** include
*/
#include "./geometry_matrix.h"
#include "./geometry_vector.h"


/** NBsys::NGeometry
*/
#if(BSYS_GEOMETRY_ENABLE)
#pragma warning(push)
#pragma warning(disable:4514)
namespace NBsys{namespace NGeometry
{
	/** x
	*/
	inline f32& Geometry_Quaternion::x()
	{
		return this->raw.q.xx;
	}

	
	/** y
	*/
	inline f32& Geometry_Quaternion::y()
	{
		return this->raw.q.yy;
	}

	
	/** z
	*/
	inline f32& Geometry_Quaternion::z()
	{
		return this->raw.q.zz;
	}


	/** w
	*/
	inline f32& Geometry_Quaternion::w()
	{
		return this->raw.q.ww;
	}


	/** x
	*/
	inline const f32& Geometry_Quaternion::x() const
	{
		return this->raw.q.xx;
	}

	
	/** y
	*/
	inline const f32& Geometry_Quaternion::y() const
	{
		return this->raw.q.yy;
	}


	/** z
	*/
	inline const f32& Geometry_Quaternion::z() const
	{
		return this->raw.q.zz;
	}


	/** w
	*/
	inline const f32& Geometry_Quaternion::w() const
	{
		return this->raw.q.ww;
	}


	/** constructor
	*/
	inline Geometry_Quaternion::Geometry_Quaternion()
	{
	}


	/** constructor
	*/
	inline Geometry_Quaternion::Geometry_Quaternion(const Geometry_Identity_Type& /*a_identity*/)
	{
		this->raw.q.xx = 0.0f;
		this->raw.q.yy = 0.0f;
		this->raw.q.zz = 0.0f;
		this->raw.q.ww = 1.0f;
	}


	/** constructor
	*/
	inline Geometry_Quaternion::Geometry_Quaternion(const Geometry_Quaternion& a_quaternion)
	{
		ASSERT(NMath::is_nan(a_quaternion.raw.q.xx) == false);
		ASSERT(NMath::is_nan(a_quaternion.raw.q.yy) == false);
		ASSERT(NMath::is_nan(a_quaternion.raw.q.zz) == false);
		ASSERT(NMath::is_nan(a_quaternion.raw.q.ww) == false);

		this->raw.q.xx = a_quaternion.raw.q.xx;
		this->raw.q.yy = a_quaternion.raw.q.yy;
		this->raw.q.zz = a_quaternion.raw.q.zz;
		this->raw.q.ww = a_quaternion.raw.q.ww;
	}


	/** constructor
	*/
	inline Geometry_Quaternion::Geometry_Quaternion(const f32* a_list)
	{
		ASSERT(NMath::is_nan(a_list[0]) == false);
		ASSERT(NMath::is_nan(a_list[1]) == false);
		ASSERT(NMath::is_nan(a_list[2]) == false);
		ASSERT(NMath::is_nan(a_list[3]) == false);

		this->raw.q.xx = a_list[0];
		this->raw.q.yy = a_list[1];
		this->raw.q.zz = a_list[2];
		this->raw.q.ww = a_list[3];
	}


	/** constructor
	*/
	inline Geometry_Quaternion::Geometry_Quaternion(f32 a_xx,f32 a_yy,f32 a_zz,f32 a_ww)
	{
		ASSERT(NMath::is_nan(a_xx) == false);
		ASSERT(NMath::is_nan(a_yy) == false);
		ASSERT(NMath::is_nan(a_zz) == false);
		ASSERT(NMath::is_nan(a_ww) == false);

		this->raw.q.xx = a_xx;
		this->raw.q.yy = a_yy;
		this->raw.q.zz = a_zz;
		this->raw.q.ww = a_ww;
	}


	/** constructor
	*/
	inline Geometry_Quaternion::Geometry_Quaternion(f32 a_rad,const Geometry_Vector3& a_normal)
	{
		Geometry_Vector3 t_normal = a_normal.Make_Normalize();

		#if(BSYS_GEOMETRY_MATRIX_SINCOSFAST_ENABLE)
		f32 t_sin_half = NMath::sin_f_fast(a_rad * 0.50f);
		f32 t_cos_half = NMath::cos_f_fast(a_rad * 0.50f);
		#else
		f32 t_sin_half = NMath::sinf(a_rad * 0.50f);
		f32 t_cos_half = NMath::cosf(a_rad * 0.50f);
		#endif

		this->raw.q.xx = t_sin_half * t_normal.raw.v.xx;
		this->raw.q.yy = t_sin_half * t_normal.raw.v.yy;
		this->raw.q.zz = t_sin_half * t_normal.raw.v.zz;
		this->raw.q.ww = t_cos_half;
	}


	/** destructor
	*/
	inline Geometry_Quaternion::~Geometry_Quaternion()
	{
	}


	/** Set_Normalize
	*/
	inline void Geometry_Quaternion::Set_Normalize()
	{
		f32 t_s = (this->raw.q.xx * this->raw.q.xx) + (this->raw.q.yy * this->raw.q.yy) + (this->raw.q.zz * this->raw.q.zz) + (this->raw.q.ww * this->raw.q.ww);

		t_s = NMath::sqrt_f(t_s);

		if(t_s != 0.0f){
			t_s = 1.0f / t_s;
		}

		ASSERT(NMath::is_nan(t_s) == false);

		this->raw.q.xx *= t_s;
		this->raw.q.yy *= t_s;
		this->raw.q.zz *= t_s;
		this->raw.q.ww *= t_s;
	}


	/** Set_Conjugate
	*/
	inline void Geometry_Quaternion::Set_Conjugate()
	{
		this->raw.q.xx *= -1;
		this->raw.q.yy *= -1;
		this->raw.q.zz *= -1;
	}


	/** Make_Conjugate
	*/
	inline Geometry_Quaternion Geometry_Quaternion::Make_Conjugate()
	{
		Geometry_Quaternion t_temp;
		{
			t_temp.raw.q.xx = -this->raw.q.xx;
			t_temp.raw.q.yy = -this->raw.q.yy;
			t_temp.raw.q.zz = -this->raw.q.zz;
			t_temp.raw.q.ww = this->raw.q.ww;
		}
		return t_temp;
	}


	/** [作成]マトリックス。
	*/
	inline Geometry_Matrix_44 Geometry_Quaternion::Make_Matrix()
	{
		return Geometry_Matrix_44(*this);
	}


	/** [作成]Make_Slerp。

	a_per = 0.0f : return = this
	a_per = 1.0f : return = a_quaternion

	*/
	inline Geometry_Quaternion Geometry_Quaternion::Make_Slerp(const Geometry_Quaternion& a_quaternion,f32 a_per) const
	{
		Geometry_Quaternion t_temp;

		f32 t_omega_v = (this->raw.q.xx * a_quaternion.raw.q.xx) + (this->raw.q.yy * a_quaternion.raw.q.yy) + (this->raw.q.zz * a_quaternion.raw.q.zz) + (this->raw.q.ww * a_quaternion.raw.q.ww);
		f32 t_omega = NMath::acos_f(NMath::abs_f(t_omega_v));

		f32 t_s = NMath::sin_f(t_omega);
		if(t_s < std::numeric_limits<float>::epsilon()){
			t_s = std::numeric_limits<float>::epsilon();
		}

		f32 t_from_per = NMath::sin_f(t_omega - a_per * t_omega) / t_s;
		f32 t_to_per = NMath::sin_f(a_per * t_omega) / t_s;
    
		t_temp.raw.q.xx = this->raw.q.xx * t_from_per + a_quaternion.raw.q.xx * t_to_per;
		t_temp.raw.q.yy = this->raw.q.yy * t_from_per + a_quaternion.raw.q.yy * t_to_per;
		t_temp.raw.q.zz = this->raw.q.zz * t_from_per + a_quaternion.raw.q.zz * t_to_per;
		t_temp.raw.q.ww = this->raw.q.ww * t_from_per + a_quaternion.raw.q.ww * t_to_per;

		return t_temp;
	}


}}
#pragma warning(pop)
#endif

