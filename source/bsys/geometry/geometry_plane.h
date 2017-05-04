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
#include "./geometry_vector.h"
#include "./geometry_matrix_raw.h"
#include "./geometry_quaternion.h"


/** NBsys::NGeometry
*/
#if(BSYS_GEOMETRY_ENABLE)
namespace NBsys{namespace NGeometry
{

	/** Geometry_Plane
	*/
	class Geometry_Plane
	{
	public:

		/** constructor�B
		*/
		inline Geometry_Plane();

		/** destructor�B
		*/
		nonvirtual inline ~Geometry_Plane();

	public:

		/** �ʂ̌����B
		*/
		Geometry_Vector3 normal;

		/** ���_�ƖʂƂ̋����B
		*/
		f32 distance;

	public:

		/** �ʂ̌����B
		*/
		inline const Geometry_Vector3& GetNormal();

		/** ���_�ƖʂƂ̋����B
		*/
		inline f32 GetDistance();

		/** SetPlanePoint�B
		*/
		inline void SetPlanePoint(NBsys::NGeometry::Geometry_Vector3& a_planepoint_1,NBsys::NGeometry::Geometry_Vector3& a_planepoint_2,NBsys::NGeometry::Geometry_Vector3& a_planepoint_3);

		/** �W���ݒ�B
		*/
		inline void SetABCD(f32 a_normal_x,f32 a_normal_y,f32 a_normal_z,f32 a_d);

		/** �_�ƖʂƂ̋����B
		*/
		inline f32 Distance(NBsys::NGeometry::Geometry_Vector3 &a_position);
	};

}}
#endif

