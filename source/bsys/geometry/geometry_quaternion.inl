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
	inline Geometry_Quaternion::Geometry_Quaternion(const Geometry_Identity& /*a_identity*/)
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
}}
#endif

