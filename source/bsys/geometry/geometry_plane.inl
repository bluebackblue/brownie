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
#include "./geometry_plane.h"


/** NBsys::NGeometry
*/
#if(BSYS_GEOMETRY_ENABLE)
#pragma warning(push)
#pragma warning(disable:4514)
namespace NBsys{namespace NGeometry
{
	/** constructor
	*/
	inline Geometry_Plane::Geometry_Plane()
	{
	}


	/** destructor
	*/
	inline Geometry_Plane::~Geometry_Plane()
	{
	}


	/** 面の向き。
	*/
	inline const Geometry_Vector3& Geometry_Plane::GetNormal()
	{
		return this->normal;
	}


	/** 原点と面との距離。
	*/
	inline f32 Geometry_Plane::GetDistance()
	{
		return this->distance;
	}


	/** SetPlanePoint。
	*/
	inline void Geometry_Plane::SetPlanePoint(NBsys::NGeometry::Geometry_Vector3& a_planepoint_1,NBsys::NGeometry::Geometry_Vector3& a_planepoint_2,NBsys::NGeometry::Geometry_Vector3& a_planepoint_3)
	{
		NBsys::NGeometry::Geometry_Vector3 t_dir_1 = a_planepoint_1 - a_planepoint_2;
		NBsys::NGeometry::Geometry_Vector3 t_dir_2 = a_planepoint_3 - a_planepoint_2;

		this->normal.Set_Cross(t_dir_2,t_dir_1);
		this->normal.Set_Normalize();

		this->distance = this->normal.Dot(a_planepoint_2);
	}


	/** 係数設定。
	*/
	inline void Geometry_Plane::SetABCD(f32 a_normal_x,f32 a_normal_y,f32 a_normal_z,f32 a_d)
	{
		this->normal.Set(a_normal_x,a_normal_y,a_normal_z);

		f32 t_length = this->normal.Length();

		this->normal.Set_Normalize();

		ASSERT(t_length != 0.0f);

		this->distance = a_d / t_length;
	}


	/** 点と面との距離。
	*/
	inline f32 Geometry_Plane::Distance(NBsys::NGeometry::Geometry_Vector3 &a_position)
	{
		return this->normal.Dot(a_position) - this->distance;
	}


}}
#pragma warning(pop)
#endif

