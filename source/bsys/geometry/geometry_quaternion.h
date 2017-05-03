#pragma once

/**
 * Copyright (c) 2017 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief �W�I���g���B
*/


/** include
*/
#include "../types/types.h"


/** include
*/
#include "./geometry_identity.h"
#include "./geometry_quaternion_raw.h"


/** NBsys::NGeometry
*/
#if(BSYS_GEOMETRY_ENABLE)
namespace NBsys{namespace NGeometry
{
	/** Geometry_Quaternion
	*/
	struct Geometry_Quaternion : public Geometry_Quaternion_Raw
	{
		/** �R���X�g���N�^�B
		*/
		inline Geometry_Quaternion();

		/** �R���X�g���N�^�B
		*/
		inline Geometry_Quaternion(const Geometry_Quaternion& a_quaternion);

		/** �R���X�g���N�^�B
		*/
		inline Geometry_Quaternion(const f32* a_list);

		/** �R���X�g���N�^�B
		*/
		inline Geometry_Quaternion(f32 a_x,f32 a_y,f32 a_z,f32 a_w);

		/** �f�X�g���N�^�B
		*/
		//nonvirtual ~Geometry_Quaternion();

		/** Set_Normalize
		*/
		inline void Set_Normalize();
	};
}}
#endif

