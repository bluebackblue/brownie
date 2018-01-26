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

		/** constructor
		*/
		inline Geometry_Plane();

		/** destructor
		*/
		inline nonvirtual ~Geometry_Plane();

	public:

		/** 面の向き。
		*/
		Geometry_Vector3 normal;

		/** 原点と面との距離。
		*/
		f32 distance;

	public:

		/** 面の向き。
		*/
		inline const Geometry_Vector3& GetNormal();

		/** 原点と面との距離。
		*/
		inline f32 GetDistance();

		/** SetPlanePoint。
		*/
		inline void SetPlanePoint(NBsys::NGeometry::Geometry_Vector3& a_planepoint_1,NBsys::NGeometry::Geometry_Vector3& a_planepoint_2,NBsys::NGeometry::Geometry_Vector3& a_planepoint_3);

		/** 係数設定。
		*/
		inline void SetABCD(f32 a_normal_x,f32 a_normal_y,f32 a_normal_z,f32 a_d);

		/** 点と面との距離。
		*/
		inline f32 Distance(NBsys::NGeometry::Geometry_Vector3 &a_position);

	};

}}
#endif

