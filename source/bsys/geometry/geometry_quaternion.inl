#pragma once

/**
 * Copyright (c) 2017 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief ジオメトリ。
*/


/** include
*/
#include "../types/types.h"


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
namespace NBsys{namespace NGeometry
{

	/** constructor。
	*/
	inline Geometry_Quaternion::Geometry_Quaternion()
	{
	}

	/** constructor。
	*/
	inline Geometry_Quaternion::Geometry_Quaternion(const Geometry_Identity_Type& /*a_identity*/)
	{
		this->x = 0.0f;
		this->y = 0.0f;
		this->z = 0.0f;
		this->w = 1.0f;
	}

	/** constructor。
	*/
	inline Geometry_Quaternion::Geometry_Quaternion(const Geometry_Quaternion& a_quaternion)
	{
		ASSERT(Math::is_nan(a_quaternion.x) == false);
		ASSERT(Math::is_nan(a_quaternion.y) == false);
		ASSERT(Math::is_nan(a_quaternion.z) == false);
		ASSERT(Math::is_nan(a_quaternion.w) == false);

		this->x = a_quaternion.x;
		this->y = a_quaternion.y;
		this->z = a_quaternion.z;
		this->w = a_quaternion.w;
	}

	/** constructor。
	*/
	inline Geometry_Quaternion::Geometry_Quaternion(const f32* a_list)
	{
		ASSERT(Math::is_nan(a_list[0]) == false);
		ASSERT(Math::is_nan(a_list[1]) == false);
		ASSERT(Math::is_nan(a_list[2]) == false);
		ASSERT(Math::is_nan(a_list[3]) == false);

		this->x = a_list[0];
		this->y = a_list[1];
		this->z = a_list[2];
		this->w = a_list[3];
	}

	/** constructor。
	*/
	inline Geometry_Quaternion::Geometry_Quaternion(f32 a_x,f32 a_y,f32 a_z,f32 a_w)
	{
		ASSERT(Math::is_nan(a_x) == false);
		ASSERT(Math::is_nan(a_y) == false);
		ASSERT(Math::is_nan(a_z) == false);
		ASSERT(Math::is_nan(a_w) == false);

		this->x = a_x;
		this->y = a_y;
		this->z = a_z;
		this->w = a_w;
	}

	/** constructor。
	*/
	inline Geometry_Quaternion::Geometry_Quaternion(f32 a_rad,const Geometry_Vector3& a_normal)
	{
		Geometry_Vector3 t_normal = a_normal.Make_Normalize();

		#if(BSYS_GEOMETRY_MATRIX_SINCOSFAST_ENABLE)
		f32 t_sin_half = Math::sinf_fast(a_rad * 0.50f);
		f32 t_cos_half = Math::cosf_fast(a_rad * 0.50f);
		#else
		f32 t_sin_half = Math::sinf(a_rad * 0.50f);
		f32 t_cos_half = Math::cosf(a_rad * 0.50f);
		#endif

		this->x = t_sin_half * t_normal.x;
		this->y = t_sin_half * t_normal.y;
		this->z = t_sin_half * t_normal.z;
		this->w = t_cos_half;
	}

	/** destructor。
	*/
	inline Geometry_Quaternion::~Geometry_Quaternion()
	{
	}

	/** Set_Normalize
	*/
	inline void Geometry_Quaternion::Set_Normalize()
	{
		f32 t_s = (this->x * this->x) + (this->y * this->y) + (this->z * this->z) + (this->w * this->w);

		t_s = Math::sqrtf(t_s);

		if(t_s != 0.0f){
			t_s = 1.0f / t_s;
		}

		ASSERT(Math::is_nan(t_s) == false);

		this->x *= t_s;
		this->y *= t_s;
		this->z *= t_s;
		this->w *= t_s;
	}

	/** Set_Conjugate
	*/
	inline void Geometry_Quaternion::Set_Conjugate()
	{
		this->x *= -1;
		this->y *= -1;
		this->z *= -1;
	}

	/** Make_Conjugate
	*/
	inline Geometry_Quaternion Geometry_Quaternion::Make_Conjugate()
	{
		Geometry_Quaternion t_temp;
		{
			t_temp.x = -this->x;
			t_temp.y = -this->y;
			t_temp.z = -this->z;
			t_temp.w = this->w;
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
		{
			f32 t_cosom = (this->x * a_quaternion.x) + (this->y * a_quaternion.y) + (this->z * a_quaternion.z) + (this->w * a_quaternion.w);
			if(t_cosom < 0.0f){
				t_cosom = -t_cosom;
				t_temp.x = -a_quaternion.x;
				t_temp.y = -a_quaternion.y;
				t_temp.z = -a_quaternion.z;
				t_temp.w = -a_quaternion.w;
			}else{
				t_temp = a_quaternion;
			}

			f32 t_rate_from = 1.0f - a_per;
			f32 t_rate_to = a_per;

			if((1.0f - t_cosom) >= FLT_EPSILON){
				f32 t_omega = Math::acosf(t_cosom);
				f32 t_sinom = Math::sinf(t_omega);
				t_rate_from = Math::sinf((1.0f - a_per) * t_omega) / t_sinom;
				t_rate_to = Math::sinf(a_per * t_omega) / t_sinom;
			}

			t_temp.x = t_rate_from * this->x + t_rate_to * t_temp.x;
			t_temp.y = t_rate_from * this->y + t_rate_to * t_temp.y;
			t_temp.z = t_rate_from * this->z + t_rate_to * t_temp.z;
			t_temp.w = t_rate_from * this->w + t_rate_to * t_temp.w;
		}

		return t_temp;
	}
}}
#endif

