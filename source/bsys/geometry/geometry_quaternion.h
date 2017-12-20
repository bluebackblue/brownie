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
#include "./geometry_identity.h"
#include "./geometry_quaternion_raw.h"


/** include
*/
#include "./geometry_vector_decl.h"
#include "./geometry_matrix_decl.h"


/** NBsys::NGeometry
*/
#if(BSYS_GEOMETRY_ENABLE)
namespace NBsys{namespace NGeometry
{
	/** Geometry_Quaternion
	*/
	struct Geometry_Quaternion : public Geometry_Quaternion_Raw
	{
		/** constructor
		*/
		inline Geometry_Quaternion();

		/** constructor
		*/
		inline Geometry_Quaternion(const Geometry_Identity_Type& /*a_identity*/);

		/** constructor
		*/
		inline Geometry_Quaternion(const Geometry_Quaternion& a_quaternion);

		/** constructor
		*/
		inline Geometry_Quaternion(const f32* a_list);

		/** constructor
		*/
		inline Geometry_Quaternion(f32 a_x,f32 a_y,f32 a_z,f32 a_w);

		/** constructor
		*/
		inline Geometry_Quaternion(f32 a_rad,const Geometry_Vector3& a_normal);

		/** destructor
		*/
		nonvirtual inline ~Geometry_Quaternion();

		/** Set_Normalize
		*/
		inline void Set_Normalize();

		/** Set_Conjugate
		*/
		inline void Set_Conjugate();

		/** Make_Conjugate
		*/
		inline Geometry_Quaternion Make_Conjugate();

		/** [作成]マトリックス。
		*/
		inline Geometry_Matrix_44 Make_Matrix();

		/** [作成]Make_Slerp。

		a_per = 0.0f : return = this
		a_per = 1.0f : return = a_quaternion

		*/
		inline Geometry_Quaternion Make_Slerp(const Geometry_Quaternion& a_quaternion,f32 a_per) const;
	};


}}
#endif

