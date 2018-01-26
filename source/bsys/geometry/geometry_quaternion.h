#pragma once

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
	struct Geometry_Quaternion
	{
		/** raw
		*/
		Geometry_Quaternion_Raw raw;

		/** raw
		*/
		inline f32& x();

		/** y
		*/
		inline f32& y();

		/** z
		*/
		inline f32& z();

		/** w
		*/
		inline f32& w();

		/** x
		*/
		inline const f32& x() const;

		/** y
		*/
		inline const f32& y() const;

		/** z
		*/
		inline const f32& z() const;

		/** w
		*/
		inline const f32& w() const;

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
		inline Geometry_Quaternion(f32 a_xx,f32 a_yy,f32 a_zz,f32 a_ww);

		/** constructor
		*/
		inline Geometry_Quaternion(f32 a_rad,const Geometry_Vector3& a_normal);

		/** destructor
		*/
		inline nonvirtual ~Geometry_Quaternion();

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

