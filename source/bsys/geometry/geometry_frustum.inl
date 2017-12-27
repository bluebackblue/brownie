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
#include "./geometry_frustum.h"


/** NBsys::NGeometry
*/
#if(BSYS_GEOMETRY_ENABLE)
namespace NBsys{namespace NGeometry
{
	/** constructor
	*/
	inline Geometry_Frustum::Geometry_Frustum()
	{
	}


	/** destructor
	*/
	inline Geometry_Frustum::~Geometry_Frustum()
	{
	}


	/** SetProjection
	*/
	inline void Geometry_Frustum::SetProjection(const Geometry_Matrix_44& a_projection)
	{
		this->projection = a_projection;
	}


	/** SetView
	*/
	inline void Geometry_Frustum::SetView(const Geometry_Matrix_44& a_view)
	{
		this->view = a_view;
	}


	/** CalcPlane
	*/
	inline void Geometry_Frustum::Calc()
	{
		Geometry_Matrix_44 t_matrix = Geometry_Identity();
		
		t_matrix *= this->view;
		t_matrix *= this->projection;

		//left
		this->plane[0].SetABCD(t_matrix.ax_w() + t_matrix.ax_x(),t_matrix.ay_w() + t_matrix.ay_x(),t_matrix.az_w() + t_matrix.az_x(),- t_matrix.tr_w() - t_matrix.tr_x());

		//right
		this->plane[1].SetABCD(t_matrix.ax_w() - t_matrix.ax_x(),t_matrix.ay_w() - t_matrix.ay_x(),t_matrix.az_w() - t_matrix.az_x(),- t_matrix.tr_w() + t_matrix.tr_x());

		//bottom
		this->plane[2].SetABCD(t_matrix.ax_w() + t_matrix.ax_y(),t_matrix.ay_w() + t_matrix.ay_y(),t_matrix.az_w() + t_matrix.az_y(),- t_matrix.tr_w() - t_matrix.tr_y());

		//top
		this->plane[3].SetABCD(t_matrix.ax_w() - t_matrix.ax_y(),t_matrix.ay_w() - t_matrix.ay_y(),t_matrix.az_w() - t_matrix.az_y(),- t_matrix.tr_w() + t_matrix.tr_y());

		//near
		#if(BSYS_GEOMETRY_PERSPECTIVE_TYPE == 0x00)
		{
			//directx
			this->plane[4].SetABCD(t_matrix.ax_z(),t_matrix.ay_z(),t_matrix.az_z(),-t_matrix.tr_z());
		}
		#else
		{
			//opengl
			this->plane[4].SetABCD(t_matrix.ax_w() + t_matrix.ax_z(),t_matrix.ay_w() + t_matrix.ay_z(),t_matrix.az_w() + t_matrix.az_z(),- t_matrix.tr_w() - t_matrix.tr_z());
		}
		#endif

		//far
		this->plane[5].SetABCD(t_matrix.ax_w() - t_matrix.ax_z(),t_matrix.ay_w() - t_matrix.ay_z(),t_matrix.az_w() - t_matrix.az_z(),- t_matrix.tr_w() + t_matrix.tr_z());
	}


	/** InFrustumCheck
	*/
	inline bool Geometry_Frustum::InFrustumCheck(Geometry_Vector3& a_position)
	{
		for(s32 ii=0;ii<COUNTOF(this->plane);ii++){
			if(this->plane[ii].Distance(a_position) < 0){

				//フラスタム外。
				return false;
			}
		}

		//フラスタム内。
		return true;
	}


}}
#endif

