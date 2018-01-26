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
#include "./geometry_matrix.h"
#include "./geometry_vertex_3.h"
#include "./geometry_tool.h"


/** NBsys::NGeometry
*/
#if(BSYS_GEOMETRY_ENABLE)
#pragma warning(push)
#pragma warning(disable:4514 4710)
namespace NBsys{namespace NGeometry
{
	/** ax_x
	*/
	inline f32& Geometry_Matrix_44::ax_x()
	{
		return this->raw.m.ax_x;
	}


	/** ax_y
	*/
	inline f32& Geometry_Matrix_44::ax_y()
	{
		return this->raw.m.ax_y;
	}


	/** ax_z
	*/
	inline f32& Geometry_Matrix_44::ax_z()
	{
		return this->raw.m.ax_z;
	}


	/** ax_w
	*/
	inline f32& Geometry_Matrix_44::ax_w()
	{
		return this->raw.m.ax_w;
	}


	/** ay_x
	*/
	inline f32& Geometry_Matrix_44::ay_x()
	{
		return this->raw.m.ay_x;
	}


	/** ay_y
	*/
	inline f32& Geometry_Matrix_44::ay_y()
	{
		return this->raw.m.ay_y;
	}


	/** ay_z
	*/
	inline f32& Geometry_Matrix_44::ay_z()
	{
		return this->raw.m.ay_z;
	}


	/** ay_w
	*/
	inline f32& Geometry_Matrix_44::ay_w()
	{
		return this->raw.m.ay_w;
	}


	/** az_x
	*/
	inline f32& Geometry_Matrix_44::az_x()
	{
		return this->raw.m.az_x;
	}


	/** az_y
	*/
	inline f32& Geometry_Matrix_44::az_y()
	{
		return this->raw.m.az_y;
	}


	/** az_z
	*/
	inline f32& Geometry_Matrix_44::az_z()
	{
		return this->raw.m.az_z;
	}


	/** az_w
	*/
	inline f32& Geometry_Matrix_44::az_w()
	{
		return this->raw.m.az_w;
	}


	/** tr_x
	*/
	inline f32& Geometry_Matrix_44::tr_x()
	{
		return this->raw.m.tr_x;
	}


	/** tr_y
	*/
	inline f32& Geometry_Matrix_44::tr_y()
	{
		return this->raw.m.tr_y;
	}


	/** tr_z
	*/
	inline f32& Geometry_Matrix_44::tr_z()
	{
		return this->raw.m.tr_z;
	}


	/** tr_w
	*/
	inline f32& Geometry_Matrix_44::tr_w()
	{
		return this->raw.m.tr_w;
	}


	/** ax_x
	*/
	inline const f32& Geometry_Matrix_44::ax_x() const
	{
		return this->raw.m.ax_x;
	}


	/** ax_y
	*/
	inline const f32& Geometry_Matrix_44::ax_y() const
	{
		return this->raw.m.ax_y;
	}


	/** ax_z
	*/
	inline const f32& Geometry_Matrix_44::ax_z() const
	{
		return this->raw.m.ax_z;
	}


	/** ax_w
	*/
	inline const f32& Geometry_Matrix_44::ax_w() const
	{
		return this->raw.m.ax_w;
	}


	/** ay_x
	*/
	inline const f32& Geometry_Matrix_44::ay_x() const
	{
		return this->raw.m.ay_x;
	}


	/** ay_y
	*/
	inline const f32& Geometry_Matrix_44::ay_y() const
	{
		return this->raw.m.ay_y;
	}


	/** ay_z
	*/
	inline const f32& Geometry_Matrix_44::ay_z() const
	{
		return this->raw.m.ay_z;
	}


	/** ay_w
	*/
	inline const f32& Geometry_Matrix_44::ay_w() const
	{
		return this->raw.m.ay_w;
	}


	/** az_x
	*/
	inline const f32& Geometry_Matrix_44::az_x() const
	{
		return this->raw.m.az_x;
	}


	/** az_y
	*/
	inline const f32& Geometry_Matrix_44::az_y() const
	{
		return this->raw.m.az_y;
	}


	/** az_z
	*/
	inline const f32& Geometry_Matrix_44::az_z() const
	{
		return this->raw.m.az_z;
	}


	/** az_w
	*/
	inline const f32& Geometry_Matrix_44::az_w() const
	{
		return this->raw.m.az_w;
	}


	/** tr_x
	*/
	inline const f32& Geometry_Matrix_44::tr_x() const
	{
		return this->raw.m.tr_x;
	}


	/** tr_y
	*/
	inline const f32& Geometry_Matrix_44::tr_y() const
	{
		return this->raw.m.tr_y;
	}


	/** tr_z
	*/
	inline const f32& Geometry_Matrix_44::tr_z() const
	{
		return this->raw.m.tr_z;
	}


	/** tr_w
	*/
	inline const f32& Geometry_Matrix_44::tr_w() const
	{
		return this->raw.m.tr_w;
	}


	/** constructor
	*/
	inline Geometry_Matrix_44::Geometry_Matrix_44() noexcept
	{
	}


	/** constructor
	*/
	inline Geometry_Matrix_44::Geometry_Matrix_44(
		f32 a_ax_x,f32 a_ax_y,f32 a_ax_z,f32 a_ax_w,
		f32 a_ay_x,f32 a_ay_y,f32 a_ay_z,f32 a_ay_w,
		f32 a_az_x,f32 a_az_y,f32 a_az_z,f32 a_az_w,
		f32 a_tr_x,f32 a_tr_y,f32 a_tr_z,f32 a_tr_w
	) noexcept
	{
		this->raw.m.ax_x = a_ax_x;
		this->raw.m.ax_y = a_ax_y;
		this->raw.m.ax_z = a_ax_z;
		this->raw.m.ax_w = a_ax_w;

		this->raw.m.ay_x = a_ay_x;
		this->raw.m.ay_y = a_ay_y;
		this->raw.m.ay_z = a_ay_z;
		this->raw.m.ay_w = a_ay_w;

		this->raw.m.az_x = a_az_x;
		this->raw.m.az_y = a_az_y;
		this->raw.m.az_z = a_az_z;
		this->raw.m.az_w = a_az_w;

		this->raw.m.tr_x = a_tr_x;
		this->raw.m.tr_y = a_tr_y;
		this->raw.m.tr_z = a_tr_z;
		this->raw.m.tr_w = a_tr_w;
	}


	/** constructor
	*/
	inline Geometry_Matrix_44::Geometry_Matrix_44(const Geometry_Identity_Type& /*a_identity*/) noexcept
	{
		*this = Geometry_Matrix_44::Identity();
	}


	/** constructor
	*/
	inline Geometry_Matrix_44::Geometry_Matrix_44(const Geometry_Quaternion& a_quaternion) noexcept
	{
		this->Set_Quaternion(a_quaternion);
	}


	/** constructor
	*/
	inline Geometry_Matrix_44::Geometry_Matrix_44(const f32* a_m) noexcept
	{
		this->raw.matrix[0][0] = a_m[0];
		this->raw.matrix[0][1] = a_m[1];
		this->raw.matrix[0][2] = a_m[2];
		this->raw.matrix[0][3] = a_m[3];

		this->raw.matrix[1][0] = a_m[4];
		this->raw.matrix[1][1] = a_m[5];
		this->raw.matrix[1][2] = a_m[6];
		this->raw.matrix[1][3] = a_m[7];

		this->raw.matrix[2][0] = a_m[8];
		this->raw.matrix[2][1] = a_m[9];
		this->raw.matrix[2][2] = a_m[10];
		this->raw.matrix[2][3] = a_m[11];

		this->raw.matrix[3][0] = a_m[12];
		this->raw.matrix[3][1] = a_m[13];
		this->raw.matrix[3][2] = a_m[14];
		this->raw.matrix[3][3] = a_m[15];
	}


	/** constructor
	*/
	inline Geometry_Matrix_44::Geometry_Matrix_44(const Geometry_Matrix_44& a_matrix) noexcept
	{
		this->raw.matrix[0][0] = a_matrix.raw.matrix[0][0];
		this->raw.matrix[0][1] = a_matrix.raw.matrix[0][1];
		this->raw.matrix[0][2] = a_matrix.raw.matrix[0][2];
		this->raw.matrix[0][3] = a_matrix.raw.matrix[0][3];
				
		this->raw.matrix[1][0] = a_matrix.raw.matrix[1][0];
		this->raw.matrix[1][1] = a_matrix.raw.matrix[1][1];
		this->raw.matrix[1][2] = a_matrix.raw.matrix[1][2];
		this->raw.matrix[1][3] = a_matrix.raw.matrix[1][3];
		
		this->raw.matrix[2][0] = a_matrix.raw.matrix[2][0];
		this->raw.matrix[2][1] = a_matrix.raw.matrix[2][1];
		this->raw.matrix[2][2] = a_matrix.raw.matrix[2][2];
		this->raw.matrix[2][3] = a_matrix.raw.matrix[2][3];
	
		this->raw.matrix[3][0] = a_matrix.raw.matrix[3][0];
		this->raw.matrix[3][1] = a_matrix.raw.matrix[3][1];
		this->raw.matrix[3][2] = a_matrix.raw.matrix[3][2];
		this->raw.matrix[3][3] = a_matrix.raw.matrix[3][3];
	}


	/** destructor
	*/
	inline Geometry_Matrix_44::~Geometry_Matrix_44()
	{
	}


	/** t_1 = NBsys::NGeometry::Geometry_Identity();
	*/
	inline Geometry_Matrix_44& Geometry_Matrix_44::operator =(const Geometry_Identity_Type& /*a_identity*/)
	{
		*this = Geometry_Matrix_44::Identity();
		return *this;
	}


	/** t_1 = t_2;
	*/
	inline Geometry_Matrix_44& Geometry_Matrix_44::operator =(const Geometry_Matrix_44& a_right)
	{
		this->raw.matrix[0][0] = a_right.raw.matrix[0][0];
		this->raw.matrix[0][1] = a_right.raw.matrix[0][1];
		this->raw.matrix[0][2] = a_right.raw.matrix[0][2];
		this->raw.matrix[0][3] = a_right.raw.matrix[0][3];
				
		this->raw.matrix[1][0] = a_right.raw.matrix[1][0];
		this->raw.matrix[1][1] = a_right.raw.matrix[1][1];
		this->raw.matrix[1][2] = a_right.raw.matrix[1][2];
		this->raw.matrix[1][3] = a_right.raw.matrix[1][3];
		
		this->raw.matrix[2][0] = a_right.raw.matrix[2][0];
		this->raw.matrix[2][1] = a_right.raw.matrix[2][1];
		this->raw.matrix[2][2] = a_right.raw.matrix[2][2];
		this->raw.matrix[2][3] = a_right.raw.matrix[2][3];
	
		this->raw.matrix[3][0] = a_right.raw.matrix[3][0];
		this->raw.matrix[3][1] = a_right.raw.matrix[3][1];
		this->raw.matrix[3][2] = a_right.raw.matrix[3][2];
		this->raw.matrix[3][3] = a_right.raw.matrix[3][3];
		return *this;
	}


	/** t_1 = +t_2;
	*/
	inline Geometry_Matrix_44 Geometry_Matrix_44::operator +() const
	{
		return *this;
	}


	/** t_1 = -t_2;
	*/
	inline Geometry_Matrix_44 Geometry_Matrix_44::operator -() const
	{
		return Geometry_Matrix_44(
			-this->raw.m.ax_x,-this->raw.m.ax_y,-this->raw.m.ax_z,-this->raw.m.ax_w,
			-this->raw.m.ay_x,-this->raw.m.ay_y,-this->raw.m.ay_z,-this->raw.m.ay_w,
			-this->raw.m.az_x,-this->raw.m.az_y,-this->raw.m.az_z,-this->raw.m.az_w,
			-this->raw.m.tr_x,-this->raw.m.tr_y,-this->raw.m.tr_z,-this->raw.m.tr_w
		);
	}


	/** t_1 += t_2;
	*/
	inline Geometry_Matrix_44& Geometry_Matrix_44::operator +=(const Geometry_Matrix_44& a_right)
	{
		this->raw.matrix[0][0] += a_right.raw.matrix[0][0];
		this->raw.matrix[0][1] += a_right.raw.matrix[0][1];
		this->raw.matrix[0][2] += a_right.raw.matrix[0][2];
		this->raw.matrix[0][3] += a_right.raw.matrix[0][3];

		this->raw.matrix[1][0] += a_right.raw.matrix[1][0];
		this->raw.matrix[1][1] += a_right.raw.matrix[1][1];
		this->raw.matrix[1][2] += a_right.raw.matrix[1][2];
		this->raw.matrix[1][3] += a_right.raw.matrix[1][3];

		this->raw.matrix[2][0] += a_right.raw.matrix[2][0];
		this->raw.matrix[2][1] += a_right.raw.matrix[2][1];
		this->raw.matrix[2][2] += a_right.raw.matrix[2][2];
		this->raw.matrix[2][3] += a_right.raw.matrix[2][3];

		this->raw.matrix[3][0] += a_right.raw.matrix[3][0];
		this->raw.matrix[3][1] += a_right.raw.matrix[3][1];
		this->raw.matrix[3][2] += a_right.raw.matrix[3][2];
		this->raw.matrix[3][3] += a_right.raw.matrix[3][3];
		return *this;
	}


	/** t_1 -= t_2;
	*/
	inline Geometry_Matrix_44& Geometry_Matrix_44::operator -=(const Geometry_Matrix_44& a_right)
	{
		this->raw.matrix[0][0] -= a_right.raw.matrix[0][0];
		this->raw.matrix[0][1] -= a_right.raw.matrix[0][1];
		this->raw.matrix[0][2] -= a_right.raw.matrix[0][2];
		this->raw.matrix[0][3] -= a_right.raw.matrix[0][3];

		this->raw.matrix[1][0] -= a_right.raw.matrix[1][0];
		this->raw.matrix[1][1] -= a_right.raw.matrix[1][1];
		this->raw.matrix[1][2] -= a_right.raw.matrix[1][2];
		this->raw.matrix[1][3] -= a_right.raw.matrix[1][3];

		this->raw.matrix[2][0] -= a_right.raw.matrix[2][0];
		this->raw.matrix[2][1] -= a_right.raw.matrix[2][1];
		this->raw.matrix[2][2] -= a_right.raw.matrix[2][2];
		this->raw.matrix[2][3] -= a_right.raw.matrix[2][3];

		this->raw.matrix[3][0] -= a_right.raw.matrix[3][0];
		this->raw.matrix[3][1] -= a_right.raw.matrix[3][1];
		this->raw.matrix[3][2] -= a_right.raw.matrix[3][2];
		this->raw.matrix[3][3] -= a_right.raw.matrix[3][3];
		return *this;
	}


	/** t_1 *= t_2;
	*/
	inline Geometry_Matrix_44& Geometry_Matrix_44::operator *=(const Geometry_Matrix_44& a_right)
	{
		f32 t_ax_x = (this->raw.m.ax_x * a_right.raw.m.ax_x) + (this->raw.m.ax_y * a_right.raw.m.ay_x) + (this->raw.m.ax_z * a_right.raw.m.az_x) + (this->raw.m.ax_w * a_right.raw.m.tr_x);
		f32 t_ax_y = (this->raw.m.ax_x * a_right.raw.m.ax_y) + (this->raw.m.ax_y * a_right.raw.m.ay_y) + (this->raw.m.ax_z * a_right.raw.m.az_y) + (this->raw.m.ax_w * a_right.raw.m.tr_y);
		f32 t_ax_z = (this->raw.m.ax_x * a_right.raw.m.ax_z) + (this->raw.m.ax_y * a_right.raw.m.ay_z) + (this->raw.m.ax_z * a_right.raw.m.az_z) + (this->raw.m.ax_w * a_right.raw.m.tr_z);
		f32 t_ax_w = (this->raw.m.ax_x * a_right.raw.m.ax_w) + (this->raw.m.ax_y * a_right.raw.m.ay_w) + (this->raw.m.ax_z * a_right.raw.m.az_w) + (this->raw.m.ax_w * a_right.raw.m.tr_w);

		f32 t_ay_x = (this->raw.m.ay_x * a_right.raw.m.ax_x) + (this->raw.m.ay_y * a_right.raw.m.ay_x) + (this->raw.m.ay_z * a_right.raw.m.az_x) + (this->raw.m.ay_w * a_right.raw.m.tr_x);
		f32 t_ay_y = (this->raw.m.ay_x * a_right.raw.m.ax_y) + (this->raw.m.ay_y * a_right.raw.m.ay_y) + (this->raw.m.ay_z * a_right.raw.m.az_y) + (this->raw.m.ay_w * a_right.raw.m.tr_y);
		f32 t_ay_z = (this->raw.m.ay_x * a_right.raw.m.ax_z) + (this->raw.m.ay_y * a_right.raw.m.ay_z) + (this->raw.m.ay_z * a_right.raw.m.az_z) + (this->raw.m.ay_w * a_right.raw.m.tr_z);
		f32 t_ay_w = (this->raw.m.ay_x * a_right.raw.m.ax_w) + (this->raw.m.ay_y * a_right.raw.m.ay_w) + (this->raw.m.ay_z * a_right.raw.m.az_w) + (this->raw.m.ay_w * a_right.raw.m.tr_w);

		f32 t_az_x = (this->raw.m.az_x * a_right.raw.m.ax_x) + (this->raw.m.az_y * a_right.raw.m.ay_x) + (this->raw.m.az_z * a_right.raw.m.az_x) + (this->raw.m.az_w * a_right.raw.m.tr_x);
		f32 t_az_y = (this->raw.m.az_x * a_right.raw.m.ax_y) + (this->raw.m.az_y * a_right.raw.m.ay_y) + (this->raw.m.az_z * a_right.raw.m.az_y) + (this->raw.m.az_w * a_right.raw.m.tr_y);
		f32 t_az_z = (this->raw.m.az_x * a_right.raw.m.ax_z) + (this->raw.m.az_y * a_right.raw.m.ay_z) + (this->raw.m.az_z * a_right.raw.m.az_z) + (this->raw.m.az_w * a_right.raw.m.tr_z);
		f32 t_az_w = (this->raw.m.az_x * a_right.raw.m.ax_w) + (this->raw.m.az_y * a_right.raw.m.ay_w) + (this->raw.m.az_z * a_right.raw.m.az_w) + (this->raw.m.az_w * a_right.raw.m.tr_w);

		f32 t_tr_x = (this->raw.m.tr_x * a_right.raw.m.ax_x) + (this->raw.m.tr_y * a_right.raw.m.ay_x) + (this->raw.m.tr_z * a_right.raw.m.az_x) + (this->raw.m.tr_w * a_right.raw.m.tr_x);
		f32 t_tr_y = (this->raw.m.tr_x * a_right.raw.m.ax_y) + (this->raw.m.tr_y * a_right.raw.m.ay_y) + (this->raw.m.tr_z * a_right.raw.m.az_y) + (this->raw.m.tr_w * a_right.raw.m.tr_y);
		f32 t_tr_z = (this->raw.m.tr_x * a_right.raw.m.ax_z) + (this->raw.m.tr_y * a_right.raw.m.ay_z) + (this->raw.m.tr_z * a_right.raw.m.az_z) + (this->raw.m.tr_w * a_right.raw.m.tr_z);
		f32 t_tr_w = (this->raw.m.tr_x * a_right.raw.m.ax_w) + (this->raw.m.tr_y * a_right.raw.m.ay_w) + (this->raw.m.tr_z * a_right.raw.m.az_w) + (this->raw.m.tr_w * a_right.raw.m.tr_w);

		this->raw.m.ax_x = t_ax_x;
		this->raw.m.ax_y = t_ax_y;
		this->raw.m.ax_z = t_ax_z;
		this->raw.m.ax_w = t_ax_w;

		this->raw.m.ay_x = t_ay_x;
		this->raw.m.ay_y = t_ay_y;
		this->raw.m.ay_z = t_ay_z;
		this->raw.m.ay_w = t_ay_w;

		this->raw.m.az_x = t_az_x;
		this->raw.m.az_y = t_az_y;
		this->raw.m.az_z = t_az_z;
		this->raw.m.az_w = t_az_w;

		this->raw.m.tr_x = t_tr_x;
		this->raw.m.tr_y = t_tr_y;
		this->raw.m.tr_z = t_tr_z;
		this->raw.m.tr_w = t_tr_w;

		return *this;
	}


	/** t_1 /= t_2;
	*/
	#if(0)
	inline Geometry_Matrix_44& Geometry_Matrix_44::operator /=(const Geometry_Matrix_44& a_right)
	{
	}
	#endif


	/** t_1 = 2;
	*/
	inline Geometry_Matrix_44& Geometry_Matrix_44::operator =(f32 a_right_value)
	{
		this->raw.matrix[0][0] = a_right_value;
		this->raw.matrix[0][1] = a_right_value;
		this->raw.matrix[0][2] = a_right_value;
		this->raw.matrix[0][3] = a_right_value;

		this->raw.matrix[1][0] = a_right_value;
		this->raw.matrix[1][1] = a_right_value;
		this->raw.matrix[1][2] = a_right_value;
		this->raw.matrix[1][3] = a_right_value;

		this->raw.matrix[2][0] = a_right_value;
		this->raw.matrix[2][1] = a_right_value;
		this->raw.matrix[2][2] = a_right_value;
		this->raw.matrix[2][3] = a_right_value;

		this->raw.matrix[3][0] = a_right_value;
		this->raw.matrix[3][1] = a_right_value;
		this->raw.matrix[3][2] = a_right_value;
		this->raw.matrix[3][3] = a_right_value;
		return *this;
	}


	/** t_1 += 2;
	*/
	inline Geometry_Matrix_44& Geometry_Matrix_44::operator +=(f32 a_right_value)
	{
		this->raw.matrix[0][0] += a_right_value;
		this->raw.matrix[0][1] += a_right_value;
		this->raw.matrix[0][2] += a_right_value;
		this->raw.matrix[0][3] += a_right_value;

		this->raw.matrix[1][0] += a_right_value;
		this->raw.matrix[1][1] += a_right_value;
		this->raw.matrix[1][2] += a_right_value;
		this->raw.matrix[1][3] += a_right_value;

		this->raw.matrix[2][0] += a_right_value;
		this->raw.matrix[2][1] += a_right_value;
		this->raw.matrix[2][2] += a_right_value;
		this->raw.matrix[2][3] += a_right_value;

		this->raw.matrix[3][0] += a_right_value;
		this->raw.matrix[3][1] += a_right_value;
		this->raw.matrix[3][2] += a_right_value;
		this->raw.matrix[3][3] += a_right_value;
		return *this;
	}


	/** t_1 -= 2;
	*/
	inline Geometry_Matrix_44& Geometry_Matrix_44::operator -=(f32 a_right_value)
	{
		this->raw.matrix[0][0] -= a_right_value;
		this->raw.matrix[0][1] -= a_right_value;
		this->raw.matrix[0][2] -= a_right_value;
		this->raw.matrix[0][3] -= a_right_value;

		this->raw.matrix[1][0] -= a_right_value;
		this->raw.matrix[1][1] -= a_right_value;
		this->raw.matrix[1][2] -= a_right_value;
		this->raw.matrix[1][3] -= a_right_value;

		this->raw.matrix[2][0] -= a_right_value;
		this->raw.matrix[2][1] -= a_right_value;
		this->raw.matrix[2][2] -= a_right_value;
		this->raw.matrix[2][3] -= a_right_value;

		this->raw.matrix[3][0] -= a_right_value;
		this->raw.matrix[3][1] -= a_right_value;
		this->raw.matrix[3][2] -= a_right_value;
		this->raw.matrix[3][3] -= a_right_value;
		return *this;
	}


	/** t_1 *= 2;
	*/
	inline Geometry_Matrix_44& Geometry_Matrix_44::operator *=(f32 a_right_value)
	{
		this->raw.matrix[0][0] *= a_right_value;
		this->raw.matrix[0][1] *= a_right_value;
		this->raw.matrix[0][2] *= a_right_value;
		this->raw.matrix[0][3] *= a_right_value;

		this->raw.matrix[1][0] *= a_right_value;
		this->raw.matrix[1][1] *= a_right_value;
		this->raw.matrix[1][2] *= a_right_value;
		this->raw.matrix[1][3] *= a_right_value;

		this->raw.matrix[2][0] *= a_right_value;
		this->raw.matrix[2][1] *= a_right_value;
		this->raw.matrix[2][2] *= a_right_value;
		this->raw.matrix[2][3] *= a_right_value;

		this->raw.matrix[3][0] *= a_right_value;
		this->raw.matrix[3][1] *= a_right_value;
		this->raw.matrix[3][2] *= a_right_value;
		this->raw.matrix[3][3] *= a_right_value;
		return *this;
	}


	/** t_1 /= 2;
	*/
	inline Geometry_Matrix_44& Geometry_Matrix_44::operator /=(f32 a_right_value)
	{
		f32 t_div = 1.0f / a_right_value;

		this->raw.matrix[0][0] *= t_div;
		this->raw.matrix[0][1] *= t_div;
		this->raw.matrix[0][2] *= t_div;
		this->raw.matrix[0][3] *= t_div;

		this->raw.matrix[1][0] *= t_div;
		this->raw.matrix[1][1] *= t_div;
		this->raw.matrix[1][2] *= t_div;
		this->raw.matrix[1][3] *= t_div;

		this->raw.matrix[2][0] *= t_div;
		this->raw.matrix[2][1] *= t_div;
		this->raw.matrix[2][2] *= t_div;
		this->raw.matrix[2][3] *= t_div;

		this->raw.matrix[3][0] *= t_div;
		this->raw.matrix[3][1] *= t_div;
		this->raw.matrix[3][2] *= t_div;
		this->raw.matrix[3][3] *= t_div;
		return *this;
	}


	/** [static]Identity。
	*/
	inline const Geometry_Matrix_44& Geometry_Matrix_44::Identity()
	{
		static const Geometry_Matrix_44 s_identity(
			1.0f,0.0f,0.0f,0.0f,
			0.0f,1.0f,0.0f,0.0f,
			0.0f,0.0f,1.0f,0.0f,
			0.0f,0.0f,0.0f,1.0f
		);

		return s_identity;
	}


	/** [設定]Identity。
	*/
	inline void Geometry_Matrix_44::Set_Identity()
	{
		*this = Geometry_Matrix_44::Identity();
	}


	/** [設定]。
	*/
	inline void Geometry_Matrix_44::Set(
		f32 a_ax_x,f32 a_ax_y,f32 a_ax_z,f32 a_ax_w,
		f32 a_ay_x,f32 a_ay_y,f32 a_ay_z,f32 a_ay_w,
		f32 a_az_x,f32 a_az_y,f32 a_az_z,f32 a_az_w,
		f32 a_tr_x,f32 a_tr_y,f32 a_tr_z,f32 a_tr_w
	)
	{
		this->raw.m.ax_x = a_ax_x;
		this->raw.m.ax_y = a_ax_y;
		this->raw.m.ax_z = a_ax_z;
		this->raw.m.ax_w = a_ax_w;

		this->raw.m.ay_x = a_ay_x;
		this->raw.m.ay_y = a_ay_y;
		this->raw.m.ay_z = a_ay_z;
		this->raw.m.ay_w = a_ay_w;

		this->raw.m.az_x = a_az_x;
		this->raw.m.az_y = a_az_y;
		this->raw.m.az_z = a_az_z;
		this->raw.m.az_w = a_az_w;

		this->raw.m.tr_x = a_tr_x;
		this->raw.m.tr_y = a_tr_y;
		this->raw.m.tr_z = a_tr_z;
		this->raw.m.tr_w = a_tr_w;
	}


	/** [作成]Ｘ軸。
	*/
	inline Geometry_Vector3 Geometry_Matrix_44::Make_AxisX() const
	{
		return Geometry_Vector3(
			this->raw.m.ax_x,
			this->raw.m.ax_y,
			this->raw.m.ax_z
		);
	}


	/** [作成]Ｙ軸。
	*/
	inline Geometry_Vector3 Geometry_Matrix_44::Make_AxisY() const
	{
		return Geometry_Vector3(
			this->raw.m.ay_x,
			this->raw.m.ay_y,
			this->raw.m.ay_z
		);
	}


	/** [作成]Ｚ軸。
	*/
	inline Geometry_Vector3 Geometry_Matrix_44::Make_AxisZ() const
	{
		return Geometry_Vector3(
			this->raw.m.az_x,
			this->raw.m.az_y,
			this->raw.m.az_z
		);
	}


	/** [設定]Ｘ軸。
	*/
	inline void Geometry_Matrix_44::Set_AxisX(const Geometry_Vector3& a_vector)
	{
		this->raw.m.ax_x = a_vector.raw.v.xx;
		this->raw.m.ax_y = a_vector.raw.v.yy;
		this->raw.m.ax_z = a_vector.raw.v.zz;
	}


	/** [設定]Ｙ軸。
	*/
	inline void Geometry_Matrix_44::Set_AxisY(const Geometry_Vector3& a_vector)
	{
		this->raw.m.ay_x = a_vector.raw.v.xx;
		this->raw.m.ay_y = a_vector.raw.v.yy;
		this->raw.m.ay_z = a_vector.raw.v.zz;
	}


	/** [設定]Ｚ軸。
	*/
	inline void Geometry_Matrix_44::Set_AxisZ(const Geometry_Vector3& a_vector)
	{
		this->raw.m.az_x = a_vector.raw.v.xx;
		this->raw.m.az_y = a_vector.raw.v.yy;
		this->raw.m.az_z = a_vector.raw.v.zz;
	}


	/** [設定]平行移動。
	*/
	inline void Geometry_Matrix_44::Set_Translate(f32 a_xx,f32 a_yy,f32 a_zz)
	{
		this->raw.m.tr_x = a_xx;
		this->raw.m.tr_y = a_yy;
		this->raw.m.tr_z = a_zz;
	}


	/** [設定]平行移動。
	*/
	inline void Geometry_Matrix_44::Set_Translate(const Geometry_Vector3& a_vector)
	{
		this->raw.m.tr_x = a_vector.raw.v.xx;
		this->raw.m.tr_y = a_vector.raw.v.yy;
		this->raw.m.tr_z = a_vector.raw.v.zz;
	}


	/** [static][作成]平行移動。
	*/
	inline Geometry_Matrix_44 Geometry_Matrix_44::Make_Translate(f32 a_xx,f32 a_yy,f32 a_zz)
	{
		return Geometry_Matrix_44(
			1.0f,  0.0f,  0.0f,  0.0f,
			0.0f,  1.0f,  0.0f,  0.0f,
			0.0f,  0.0f,  1.0f,  0.0f,
			a_xx,  a_yy,  a_zz,  1.0f
		);
	}


	/** [static][作成]平行移動。
	*/
	inline Geometry_Matrix_44 Geometry_Matrix_44::Make_Translate(const Geometry_Vector3& a_vector)
	{
		return Geometry_Matrix_44(
			1.0f,               0.0f,               0.0f,               0.0f,
			0.0f,               1.0f,               0.0f,               0.0f,
			0.0f,               0.0f,               1.0f,               0.0f,
			a_vector.raw.v.xx,  a_vector.raw.v.yy,  a_vector.raw.v.zz,  1.0f
		);
	}


	/** [作成]平行移動。
	*/
	inline Geometry_Vector3 Geometry_Matrix_44::Make_Translate_Vector() const
	{
		return Geometry_Vector3(
			this->raw.m.tr_x,
			this->raw.m.tr_y,
			this->raw.m.tr_z
		);
	}


	/** [作成]平行移動。
	*/
	inline Geometry_Matrix_44 Geometry_Matrix_44::Make_Translate() const
	{
		return Geometry_Matrix_44(
			1.0f,               0.0f,               0.0f,               0.0f,
			0.0f,               1.0f,               0.0f,               0.0f,
			0.0f,               0.0f,               1.0f,               0.0f,
			this->raw.m.tr_x,   this->raw.m.tr_y,   this->raw.m.tr_z,   1.0f
		);
	}


	/** [設定]スケール。
	*/
	inline void Geometry_Matrix_44::Calc_Scale(f32 a_xx,f32 a_yy,f32 a_zz)
	{
		Geometry_Vector3 t_axis_x = this->Make_AxisX();
		Geometry_Vector3 t_axis_y = this->Make_AxisY();
		Geometry_Vector3 t_axis_z = this->Make_AxisZ();

		t_axis_x.Set_Normalize();
		t_axis_y.Set_Normalize();
		t_axis_z.Set_Normalize();

		this->Set_AxisX(t_axis_x * a_xx);
		this->Set_AxisY(t_axis_y * a_yy);
		this->Set_AxisZ(t_axis_z * a_zz);
	}


	/** [設定]スケール。
	*/
	inline void Geometry_Matrix_44::Calc_Scale(const Geometry_Vector3& a_vector)
	{
		this->Calc_Scale(a_vector.raw.v.xx,a_vector.raw.v.yy,a_vector.raw.v.zz);
	}


	/** [作成]各軸のスケール。
	*/
	inline Geometry_Vector3 Geometry_Matrix_44::Make_Scale_Vector() const
	{
		Geometry_Vector3 t_temp;
		{
			Geometry_Vector3 t_axis_x = this->Make_AxisX();
			Geometry_Vector3 t_axis_y = this->Make_AxisY();
			Geometry_Vector3 t_axis_z = this->Make_AxisZ();

			t_temp.Set(t_axis_x.Length(),t_axis_y.Length(),t_axis_z.Length());
		}
		return t_temp;
	}


	/** [static][作成]回転行列。
	*/
	inline Geometry_Matrix_44 Geometry_Matrix_44::Make_RotationXYZ(f32 a_rad_x,f32 a_rad_y,f32 a_rad_z)
	{
		return Geometry_Matrix_44::Make_RotationX(a_rad_x) * Geometry_Matrix_44::Make_RotationY(a_rad_y) * Geometry_Matrix_44::Make_RotationZ(a_rad_z);
	}


	/** [作成]回転行列。
	*/
	inline Geometry_Matrix_44 Geometry_Matrix_44::Make_Rotation() const
	{
		Geometry_Matrix_44 t_temp;
		{
			f32 t_ax_value = (this->raw.m.ax_x * this->raw.m.ax_x) + (this->raw.m.ax_y * this->raw.m.ax_y) + (this->raw.m.ax_z * this->raw.m.ax_z);
			f32 t_ay_value = (this->raw.m.ay_x * this->raw.m.ay_x) + (this->raw.m.ay_y * this->raw.m.ay_y) + (this->raw.m.ay_z * this->raw.m.ay_z);
			f32 t_az_value = (this->raw.m.az_x * this->raw.m.az_x) + (this->raw.m.az_y * this->raw.m.az_y) + (this->raw.m.az_z * this->raw.m.az_z);

			ASSERT(t_ax_value != 0.0f);
			ASSERT(t_ay_value != 0.0f);
			ASSERT(t_az_value != 0.0f);

			t_ax_value = NMath::sqrt_f(t_ax_value);
			t_ay_value = NMath::sqrt_f(t_ay_value);
			t_az_value = NMath::sqrt_f(t_az_value);

			ASSERT(t_ax_value != 0.0f);
			ASSERT(t_ay_value != 0.0f);
			ASSERT(t_az_value != 0.0f);

			t_ax_value = 1.0f / t_ax_value;
			t_ay_value = 1.0f / t_ax_value;
			t_az_value = 1.0f / t_ax_value;

			t_temp.Set(
				this->raw.m.ax_x * t_ax_value,this->raw.m.ax_y * t_ax_value,this->raw.m.ax_z * t_ax_value,0.0f,
				this->raw.m.ay_x * t_ay_value,this->raw.m.ay_y * t_ay_value,this->raw.m.ay_z * t_ay_value,0.0f,
				this->raw.m.az_x * t_az_value,this->raw.m.az_y * t_az_value,this->raw.m.az_z * t_az_value,0.0f,
				0.0f,0.0f,0.0f,1.0f
			);
		}
		return t_temp;
	}


	/** [static][作成]回転行列。
	*/
	inline Geometry_Matrix_44 Geometry_Matrix_44::Make_RotationX(f32 a_rad)
	{
		Geometry_Matrix_44 t_temp;
		{
			f32 t_sin_x = NImpl_Matrix::sinf(a_rad);
			f32 t_cos_x = NImpl_Matrix::cosf(a_rad);

			t_temp.raw.m.ax_x = 1.0f;
			t_temp.raw.m.ax_y = 0.0f;
			t_temp.raw.m.ax_z = 0.0f;
			t_temp.raw.m.ax_w = 0.0f;

			t_temp.raw.m.ay_x = 0.0f;
			t_temp.raw.m.ay_y = t_cos_x;
			t_temp.raw.m.ay_z = t_sin_x;
			t_temp.raw.m.ay_w = 0.0f;

			t_temp.raw.m.az_x = 0.0f;
			t_temp.raw.m.az_y = -t_sin_x;
			t_temp.raw.m.az_z = t_cos_x;
			t_temp.raw.m.az_w = 0.0f;

			t_temp.raw.m.tr_x = 0.0f;
			t_temp.raw.m.tr_y = 0.0f;
			t_temp.raw.m.tr_z = 0.0f;
			t_temp.raw.m.tr_w = 1.0f;
		}
		return t_temp;
	}


	/** [static][作成]回転行列。
	*/
	inline Geometry_Matrix_44 Geometry_Matrix_44::Make_RotationY(f32 a_rad)
	{
		Geometry_Matrix_44 t_temp;
		{
			f32 t_sin_y = NImpl_Matrix::sinf(a_rad);
			f32 t_cos_y = NImpl_Matrix::cosf(a_rad);

			t_temp.raw.m.ax_x = t_cos_y;
			t_temp.raw.m.ax_y = 0.0f;
			t_temp.raw.m.ax_z = -t_sin_y;
			t_temp.raw.m.ax_w = 0.0f;

			t_temp.raw.m.ay_x = 0.0f;
			t_temp.raw.m.ay_y = 1.0f;
			t_temp.raw.m.ay_z = 0.0f;
			t_temp.raw.m.ay_w = 0.0f;

			t_temp.raw.m.az_x = t_sin_y;
			t_temp.raw.m.az_y = 0.0f;
			t_temp.raw.m.az_z = t_cos_y;
			t_temp.raw.m.az_w = 0.0f;

			t_temp.raw.m.tr_x = 0.0f;
			t_temp.raw.m.tr_y = 0.0f;
			t_temp.raw.m.tr_z = 0.0f;
			t_temp.raw.m.tr_w = 1.0f;
		}
		return t_temp;
	}


	/** [static][作成]回転行列。
	*/
	inline Geometry_Matrix_44 Geometry_Matrix_44::Make_RotationZ(f32 a_rad)
	{
		Geometry_Matrix_44 t_temp;
		{
			f32 t_sin_z = NImpl_Matrix::sinf(a_rad);
			f32 t_cos_z = NImpl_Matrix::cosf(a_rad);

			t_temp.raw.m.ax_x = t_cos_z;
			t_temp.raw.m.ax_y = t_sin_z;
			t_temp.raw.m.ax_z = 0.0f;
			t_temp.raw.m.ax_w = 0.0f;

			t_temp.raw.m.ay_x = -t_sin_z;
			t_temp.raw.m.ay_y = t_cos_z;
			t_temp.raw.m.ay_z = 0.0f;
			t_temp.raw.m.ay_w = 0.0f;

			t_temp.raw.m.az_x = 0.0f;
			t_temp.raw.m.az_y = 0.0f;
			t_temp.raw.m.az_z = 1.0f;
			t_temp.raw.m.az_w = 0.0f;

			t_temp.raw.m.tr_x = 0.0f;
			t_temp.raw.m.tr_y = 0.0f;
			t_temp.raw.m.tr_z = 0.0f;
			t_temp.raw.m.tr_w = 1.0f;
		}
		return t_temp;
	}


	/** [設定]回転行列。
	*/
	inline void Geometry_Matrix_44::Set_RotationX(f32 a_rad)
	{
		f32 t_sin_x = NImpl_Matrix::sinf(a_rad);
		f32 t_cos_x = NImpl_Matrix::cosf(a_rad);

		this->raw.m.ax_x = 1.0f;
		this->raw.m.ax_y = 0.0f;
		this->raw.m.ax_z = 0.0f;
		this->raw.m.ax_w = 0.0f;

		this->raw.m.ay_x = 0.0f;
		this->raw.m.ay_y = t_cos_x;
		this->raw.m.ay_z = t_sin_x;
		this->raw.m.ay_w = 0.0f;

		this->raw.m.az_x = 0.0f;
		this->raw.m.az_y = -t_sin_x;
		this->raw.m.az_z = t_cos_x;
		this->raw.m.az_w = 0.0f;

		this->raw.m.tr_x = 0.0f;
		this->raw.m.tr_y = 0.0f;
		this->raw.m.tr_z = 0.0f;
		this->raw.m.tr_w = 1.0f;
	}


	/** [設定]回転行列。
	*/
	inline void Geometry_Matrix_44::Set_RotationY(f32 a_rad)
	{
		f32 t_sin_y = NImpl_Matrix::sinf(a_rad);
		f32 t_cos_y = NImpl_Matrix::cosf(a_rad);

		this->raw.m.ax_x = t_cos_y;
		this->raw.m.ax_y = 0.0f;
		this->raw.m.ax_z = -t_sin_y;
		this->raw.m.ax_w = 0.0f;

		this->raw.m.ay_x = 0.0f;
		this->raw.m.ay_y = 1.0f;
		this->raw.m.ay_z = 0.0f;
		this->raw.m.ay_w = 0.0f;

		this->raw.m.az_x = t_sin_y;
		this->raw.m.az_y = 0.0f;
		this->raw.m.az_z = t_cos_y;
		this->raw.m.az_w = 0.0f;

		this->raw.m.tr_x = 0.0f;
		this->raw.m.tr_y = 0.0f;
		this->raw.m.tr_z = 0.0f;
		this->raw.m.tr_w = 1.0f;
	}


	/** [設定]回転行列。
	*/
	inline void Geometry_Matrix_44::Set_RotationZ(f32 a_rad)
	{
		f32 t_sin_z = NImpl_Matrix::sinf(a_rad);
		f32 t_cos_z = NImpl_Matrix::cosf(a_rad);

		this->raw.m.ax_x = t_cos_z;
		this->raw.m.ax_y = t_sin_z;
		this->raw.m.ax_z = 0.0f;
		this->raw.m.ax_w = 0.0f;

		this->raw.m.ay_x = -t_sin_z;
		this->raw.m.ay_y = t_cos_z;
		this->raw.m.ay_z = 0.0f;
		this->raw.m.ay_w = 0.0f;

		this->raw.m.az_x = 0.0f;
		this->raw.m.az_y = 0.0f;
		this->raw.m.az_z = 1.0f;
		this->raw.m.az_w = 0.0f;

		this->raw.m.tr_x = 0.0f;
		this->raw.m.tr_y = 0.0f;
		this->raw.m.tr_z = 0.0f;
		this->raw.m.tr_w = 1.0f;
	}


	/** [設定]回転行列。
	*/
	inline void Geometry_Matrix_44::Set_RotationVector(const Geometry_Vector3& a_vector,f32 a_rad)
	{
		f32 t_cos = NImpl_Matrix::cosf(a_rad);
		f32 t_sin = NImpl_Matrix::sinf(a_rad);
		f32 t_1_cos = 1 - t_cos;

		Geometry_Vector3 t_vector = a_vector.Make_Normalize();

		this->raw.m.ax_x = t_1_cos * t_vector.raw.v.xx * t_vector.raw.v.xx + t_cos;
		this->raw.m.ax_y = t_vector.raw.v.xx * t_vector.raw.v.yy * t_1_cos - t_vector.raw.v.zz * t_sin;
		this->raw.m.ax_z = t_vector.raw.v.xx * t_vector.raw.v.zz * t_1_cos + t_vector.raw.v.yy * t_sin;
		this->raw.m.ax_w = 0.0f;

		this->raw.m.ay_x = t_vector.raw.v.xx * t_vector.raw.v.yy * t_1_cos + t_vector.raw.v.zz * t_sin;
		this->raw.m.ay_y = t_1_cos * t_vector.raw.v.yy * t_vector.raw.v.yy + t_cos;
		this->raw.m.ay_z = t_vector.raw.v.yy * t_vector.raw.v.zz * t_1_cos - t_vector.raw.v.xx * t_sin;
		this->raw.m.ay_w = 0.0f;

		this->raw.m.az_x = t_vector.raw.v.xx * t_vector.raw.v.zz * t_1_cos - t_vector.raw.v.yy * t_sin;
		this->raw.m.az_y = t_vector.raw.v.yy * t_vector.raw.v.zz * t_1_cos + t_vector.raw.v.xx * t_sin;
		this->raw.m.az_z = t_1_cos * t_vector.raw.v.zz * t_vector.raw.v.zz + t_cos;
		this->raw.m.az_w = 0.0f;

		this->raw.m.tr_x = 0.0f;
		this->raw.m.tr_y = 0.0f;
		this->raw.m.tr_z = 0.0f;
		this->raw.m.tr_w = 1.0f;
	}


	/** [作成]逆行列。
	*/
	inline Geometry_Matrix_44 Geometry_Matrix_44::Make_Inverse() const
	{
		f32 t_ax_x = this->raw.m.ay_y * this->raw.m.az_z - this->raw.m.ay_z * this->raw.m.az_y;
		f32 t_ax_y = this->raw.m.ax_y * this->raw.m.az_z - this->raw.m.ax_z * this->raw.m.az_y;
		f32 t_ax_z = this->raw.m.ax_y * this->raw.m.ay_z - this->raw.m.ax_z * this->raw.m.ay_y;

		f32 t_ay_x = this->raw.m.ay_x * this->raw.m.az_z - this->raw.m.ay_z * this->raw.m.az_x;
		f32 t_ay_y = this->raw.m.ax_x * this->raw.m.az_z - this->raw.m.ax_z * this->raw.m.az_x;
		f32 t_ay_z = this->raw.m.ax_x * this->raw.m.ay_z - this->raw.m.ax_z * this->raw.m.ay_x;

		f32 t_az_x = this->raw.m.ay_x * this->raw.m.az_y - this->raw.m.ay_y * this->raw.m.az_x;
		f32 t_az_y = this->raw.m.ax_x * this->raw.m.az_y - this->raw.m.ax_y * this->raw.m.az_x;
		f32 t_az_z = this->raw.m.ax_x * this->raw.m.ay_y - this->raw.m.ax_y * this->raw.m.ay_x;
		
		f32 t_det = (this->raw.m.ax_x * t_ax_x) - (this->raw.m.ax_y * t_ay_x) + (this->raw.m.ax_z * t_az_x);
		t_det = 1.0f / t_det;

		Geometry_Matrix_44 t_temp;
		{
			t_temp.raw.m.ax_x =  t_ax_x * t_det;
			t_temp.raw.m.ax_y = -t_ax_y * t_det;
			t_temp.raw.m.ax_z =  t_ax_z * t_det;
			t_temp.raw.m.ax_w = 0.0f;

			t_temp.raw.m.ay_x = -t_ay_x * t_det;
			t_temp.raw.m.ay_y =  t_ay_y * t_det;
			t_temp.raw.m.ay_z = -t_ay_z * t_det;
			t_temp.raw.m.ay_w = 0.0f;

			t_temp.raw.m.az_x =  t_az_x * t_det;
			t_temp.raw.m.az_y = -t_az_y * t_det;
			t_temp.raw.m.az_z =  t_az_z * t_det;
			t_temp.raw.m.az_w = 0.0f;

			f32 t_tr_x = -((this->raw.m.tr_x * t_temp.raw.m.ax_x) + (this->raw.m.tr_y * t_temp.raw.m.ay_x) + (this->raw.m.tr_z * t_temp.raw.m.az_x));
			f32 t_tr_y = -((this->raw.m.tr_x * t_temp.raw.m.ax_y) + (this->raw.m.tr_y * t_temp.raw.m.ay_y) + (this->raw.m.tr_z * t_temp.raw.m.az_y));
			f32 t_tr_z = -((this->raw.m.tr_x * t_temp.raw.m.ax_z) + (this->raw.m.tr_y * t_temp.raw.m.ay_z) + (this->raw.m.tr_z * t_temp.raw.m.az_z));

			t_temp.raw.m.tr_x = t_tr_x;
			t_temp.raw.m.tr_y = t_tr_y;
			t_temp.raw.m.tr_z = t_tr_z;
			t_temp.raw.m.tr_w = 1.0f;
		}

		return t_temp;
	}


	/** [設定]逆行列。
	*/
	inline void Geometry_Matrix_44::Set_Inverse()
	{
		f32 t_ax_x = (this->raw.m.ay_y * this->raw.m.az_z) - (this->raw.m.ay_z * this->raw.m.az_y);
		f32 t_ax_y = (this->raw.m.ax_y * this->raw.m.az_z) - (this->raw.m.ax_z * this->raw.m.az_y);
		f32 t_ax_z = (this->raw.m.ax_y * this->raw.m.ay_z) - (this->raw.m.ax_z * this->raw.m.ay_y);

		f32 t_ay_x = (this->raw.m.ay_x * this->raw.m.az_z) - (this->raw.m.ay_z * this->raw.m.az_x);
		f32 t_ay_y = (this->raw.m.ax_x * this->raw.m.az_z) - (this->raw.m.ax_z * this->raw.m.az_x);
		f32 t_ay_z = (this->raw.m.ax_x * this->raw.m.ay_z) - (this->raw.m.ax_z * this->raw.m.ay_x);

		f32 t_az_x = (this->raw.m.ay_x * this->raw.m.az_y) - (this->raw.m.ay_y * this->raw.m.az_x);
		f32 t_az_y = (this->raw.m.ax_x * this->raw.m.az_y) - (this->raw.m.ax_y * this->raw.m.az_x);
		f32 t_az_z = (this->raw.m.ax_x * this->raw.m.ay_y) - (this->raw.m.ax_y * this->raw.m.ay_x);
		
		f32 t_det = (this->raw.m.ax_x * t_ax_x) - (this->raw.m.ax_y * t_ay_x) + (this->raw.m.ax_z * t_az_x);
		t_det = 1.0f / t_det;

		{
			this->raw.m.ax_x =  t_ax_x * t_det;
			this->raw.m.ax_y = -t_ax_y * t_det;
			this->raw.m.ax_z =  t_ax_z * t_det;
			this->raw.m.ax_w = 0.0f;

			this->raw.m.ay_x = -t_ay_x * t_det;
			this->raw.m.ay_y =  t_ay_y * t_det;
			this->raw.m.ay_z = -t_ay_z * t_det;
			this->raw.m.ay_w = 0.0f;

			this->raw.m.az_x =  t_az_x * t_det;
			this->raw.m.az_y = -t_az_y * t_det;
			this->raw.m.az_z =  t_az_z * t_det;
			this->raw.m.az_w = 0.0f;

			f32 t_tr_x = -((this->raw.m.tr_x * this->raw.m.ax_x) + (this->raw.m.tr_y * this->raw.m.ay_x) + (this->raw.m.tr_z * this->raw.m.az_x));
			f32 t_tr_y = -((this->raw.m.tr_x * this->raw.m.ax_y) + (this->raw.m.tr_y * this->raw.m.ay_y) + (this->raw.m.tr_z * this->raw.m.az_y));
			f32 t_tr_z = -((this->raw.m.tr_x * this->raw.m.ax_z) + (this->raw.m.tr_y * this->raw.m.ay_z) + (this->raw.m.tr_z * this->raw.m.az_z));

			this->raw.m.tr_x = t_tr_x;
			this->raw.m.tr_y = t_tr_y;
			this->raw.m.tr_z = t_tr_z;
			this->raw.m.tr_w = 1.0f;
		}
	}


	/** [作成]転置行列。
	*/
	inline Geometry_Matrix_44 Geometry_Matrix_44::Make_Transpose()
	{
		Geometry_Matrix_44 t_temp;
		{
			t_temp.raw.matrix[0][0] = this->raw.matrix[0][0];
			t_temp.raw.matrix[0][1] = this->raw.matrix[1][0];
			t_temp.raw.matrix[0][2] = this->raw.matrix[2][0];
			t_temp.raw.matrix[0][3] = this->raw.matrix[3][0];

			t_temp.raw.matrix[1][0] = this->raw.matrix[0][1];
			t_temp.raw.matrix[1][1] = this->raw.matrix[1][1];
			t_temp.raw.matrix[1][2] = this->raw.matrix[2][1];
			t_temp.raw.matrix[1][3] = this->raw.matrix[3][1];

			t_temp.raw.matrix[2][0] = this->raw.matrix[0][2];
			t_temp.raw.matrix[2][1] = this->raw.matrix[1][2];
			t_temp.raw.matrix[2][2] = this->raw.matrix[2][2];
			t_temp.raw.matrix[2][3] = this->raw.matrix[3][2];

			t_temp.raw.matrix[3][0] = this->raw.matrix[0][3];
			t_temp.raw.matrix[3][1] = this->raw.matrix[1][3];
			t_temp.raw.matrix[3][2] = this->raw.matrix[2][3];
			t_temp.raw.matrix[3][3] = this->raw.matrix[3][3];
		}

		return t_temp;
	}


	/** [設定]転置行列。
	*/
	inline void Geometry_Matrix_44::Set_Transpose()
	{
		f32 t_m_0_1 = this->raw.matrix[0][1];
		f32 t_m_0_2 = this->raw.matrix[0][2];
		f32 t_m_0_3 = this->raw.matrix[0][3];

		f32 t_m_1_2 = this->raw.matrix[1][2];
		f32 t_m_1_3 = this->raw.matrix[1][3];

		f32 t_m_2_3 = this->raw.matrix[2][3];

		this->raw.matrix[0][1] = this->raw.matrix[1][0];
		this->raw.matrix[0][2] = this->raw.matrix[2][0];
		this->raw.matrix[0][3] = this->raw.matrix[3][0];

		this->raw.matrix[1][0] = t_m_0_1;
		this->raw.matrix[1][2] = this->raw.matrix[2][1];
		this->raw.matrix[1][3] = this->raw.matrix[3][1];

		this->raw.matrix[2][0] = t_m_0_2;
		this->raw.matrix[2][1] = t_m_1_2;
		this->raw.matrix[2][3] = this->raw.matrix[3][2];

		this->raw.matrix[3][0] = t_m_0_3;
		this->raw.matrix[3][1] = t_m_1_3;
		this->raw.matrix[3][2] = t_m_2_3;
	}


	/** [設定]Set_Lookat。
	*/
	inline void Geometry_Matrix_44::Set_Lookat(const Geometry_Vector3& a_position,const Geometry_Vector3& a_target,const Geometry_Vector3& a_up)
	{
		Geometry_Vector3 t_z = a_target - a_position;
		t_z.Set_Normalize();

		//a_upは補助。
		Geometry_Vector3 t_x = a_up.Make_Cross(t_z);
		t_x.Set_Normalize();

		Geometry_Vector3 t_y = t_z.Make_Cross(t_x);
		t_y.Set_Normalize();

		{
			this->raw.m.ax_x = t_x.raw.v.xx;
			this->raw.m.ax_y = t_x.raw.v.yy;
			this->raw.m.ax_z = t_x.raw.v.zz;
			this->raw.m.ax_w = 0.0f;

			this->raw.m.ay_x = t_y.raw.v.xx;
			this->raw.m.ay_y = t_y.raw.v.yy;
			this->raw.m.ay_z = t_y.raw.v.zz;
			this->raw.m.ay_w = 0.0f;

			this->raw.m.az_x = t_z.raw.v.xx;
			this->raw.m.az_y = t_z.raw.v.yy;
			this->raw.m.az_z = t_z.raw.v.zz;
			this->raw.m.az_w = 0.0f;

			this->raw.m.tr_x = 0.0f;
			this->raw.m.tr_y = 0.0f;
			this->raw.m.tr_z = 0.0f;
			this->raw.m.tr_w = 1.0f;
		}
	}

	
	/** [設定]Set_LookatLimit。
	*/
	inline void Geometry_Matrix_44::Set_LookatLimit(const Geometry_Vector3& a_position,const Geometry_Vector3& a_target,const Geometry_Vector3& a_up)
	{
		//t_dirは補助。
		Geometry_Vector3 t_dir = a_target - a_position;
		t_dir.Set_Normalize();

		Geometry_Vector3 t_y = a_up;
		t_y.Set_Normalize();

		Geometry_Vector3 t_x = t_y.Make_Cross(t_dir);
		t_x.Set_Normalize();

		Geometry_Vector3 t_z = t_x.Make_Cross(t_y);
		t_z.Set_Normalize();

		{
			this->raw.m.ax_x = t_x.raw.v.xx;
			this->raw.m.ax_y = t_x.raw.v.yy;
			this->raw.m.ax_z = t_x.raw.v.zz;
			this->raw.m.ax_w = 0.0f;

			this->raw.m.ay_x = t_y.raw.v.xx;
			this->raw.m.ay_y = t_y.raw.v.yy;
			this->raw.m.ay_z = t_y.raw.v.zz;
			this->raw.m.ay_w = 0.0f;

			this->raw.m.az_x = t_z.raw.v.xx;
			this->raw.m.az_y = t_z.raw.v.yy;
			this->raw.m.az_z = t_z.raw.v.zz;
			this->raw.m.az_w = 0.0f;

			this->raw.m.tr_x = 0.0f;
			this->raw.m.tr_y = 0.0f;
			this->raw.m.tr_z = 0.0f;
			this->raw.m.tr_w = 1.0f;
		}
	}


	/** [作成]クオータニオン。
	*/
	inline Geometry_Quaternion Geometry_Matrix_44::Make_Quaternion() const
	{
		Geometry_Quaternion t_temp_quaternion;
		{
			f32 t_tr = this->raw.m.ax_x + this->raw.m.ay_y + this->raw.m.az_z;
			if(t_tr > 0.0f){

				f32 t_s = NMath::sqrt_f(t_tr + 1.0f);
				t_temp_quaternion.raw.q.ww = t_s * 0.5f;
				t_s = 0.5f / t_s;

				t_temp_quaternion.raw.q.xx = (this->raw.m.az_y - this->raw.m.ay_z) * t_s;
				t_temp_quaternion.raw.q.yy = (this->raw.m.ax_z - this->raw.m.az_x) * t_s;
				t_temp_quaternion.raw.q.zz = (this->raw.m.ay_x - this->raw.m.ax_y) * t_s;

			}else{

				s32 ii = 0;
				{
					if(this->raw.m.ay_y > this->raw.m.ax_x){
						ii = 1;
					}
					if(this->raw.m.az_z > this->raw.matrix[ii][ii]){
						ii = 2;
					}
				}

				s32 t_next[3] = {1,2,0};
				s32 jj = t_next[ii];
				s32 kk = t_next[jj];

				f32 t_s = NMath::sqrt_f((this->raw.matrix[ii][ii] - (this->raw.matrix[jj][jj] + this->raw.matrix[kk][kk])) + 1.0f);

				f32 t_temp[3];
				t_temp[ii] = t_s * 0.5f;

				if(t_s != 0.0f){
					t_s = 0.5f / t_s;
				}

				t_temp_quaternion.raw.q.ww = (this->raw.matrix[kk][jj] - this->raw.matrix[jj][kk]) * t_s;
				t_temp[jj] = (this->raw.matrix[ii][jj] + this->raw.matrix[jj][ii]) * t_s;
				t_temp[kk] = (this->raw.matrix[ii][kk] + this->raw.matrix[kk][ii]) * t_s;

				t_temp_quaternion.raw.q.xx = t_temp[0];
				t_temp_quaternion.raw.q.yy = t_temp[1];
				t_temp_quaternion.raw.q.zz = t_temp[2];
			}
		}
		return t_temp_quaternion;
	}


	/** [作成]クオータニオン。
	*/
	inline Geometry_Quaternion Geometry_Matrix_44::Make_Quaternion_Safe() const
	{
		Geometry_Matrix_44 t_temp = this->Make_Rotation();
		return t_temp.Make_Quaternion();
	}


	/** [設定]クオータニオン。
	*/
	inline void Geometry_Matrix_44::Set_Quaternion(const Geometry_Quaternion& a_quaternion)
	{
		f32 t_s = 2.0f / ((a_quaternion.raw.q.xx * a_quaternion.raw.q.xx) + (a_quaternion.raw.q.yy * a_quaternion.raw.q.yy) + (a_quaternion.raw.q.zz * a_quaternion.raw.q.zz) + (a_quaternion.raw.q.ww * a_quaternion.raw.q.ww));

		f32 t_wx = a_quaternion.raw.q.ww * a_quaternion.raw.q.xx * t_s;
		f32 t_wy = a_quaternion.raw.q.ww * a_quaternion.raw.q.yy * t_s;
		f32 t_wz = a_quaternion.raw.q.ww * a_quaternion.raw.q.zz * t_s;

		f32 t_xx = a_quaternion.raw.q.xx * a_quaternion.raw.q.xx * t_s;
		f32 t_xy = a_quaternion.raw.q.xx * a_quaternion.raw.q.yy * t_s;
		f32 t_xz = a_quaternion.raw.q.xx * a_quaternion.raw.q.zz * t_s;

		f32 t_yy = a_quaternion.raw.q.yy * a_quaternion.raw.q.yy * t_s;
		f32 t_yz = a_quaternion.raw.q.yy * a_quaternion.raw.q.zz * t_s;
		f32 t_zz = a_quaternion.raw.q.zz * a_quaternion.raw.q.zz * t_s;

		this->raw.m.ax_x = 1.0f - (t_yy + t_zz);
		this->raw.m.ax_y = t_xy - t_wz;
		this->raw.m.ax_z = t_xz + t_wy;
		this->raw.m.ax_w = 0.0f;

		this->raw.m.ay_x = t_xy + t_wz;
		this->raw.m.ay_y = 1.0f - (t_xx + t_zz);
		this->raw.m.ay_z = t_yz - t_wx;
		this->raw.m.ay_w = 0.0f;

		this->raw.m.az_x = t_xz - t_wy;
		this->raw.m.az_y = t_yz + t_wx;
		this->raw.m.az_z = 1.0f - (t_xx + t_yy);
		this->raw.m.az_w = 0.0f;

		this->raw.m.tr_x = 0.0f;
		this->raw.m.tr_y = 0.0f;
		this->raw.m.tr_z = 0.0f;
		this->raw.m.tr_w = 1.0f;
	}


	/** [設定]プロジェクション。透視投影。
	*/
	inline void Geometry_Matrix_44::Set_PerspectiveProjectionMatrix(const Size2DType<f32>& a_size,f32 a_fov_deg,f32 a_near,f32 a_far)
	{
		f32 t_aspect = a_size.ww / a_size.hh;
		f32 t_fov_radian =  BLIB_MATH_DEG_TO_RAD(a_fov_deg);
		f32 t_scale = 1.0f / NMath::tan_f(t_fov_radian / 2);
		f32 t_w = t_scale/t_aspect;
		f32 t_h = t_scale;

		#if(BSYS_GEOMETRY_PERSPECTIVE_TYPE == 0x00)
		{
			#if(BSYS_GEOMETRY_LEFTRIGHT_TYPE == 0x00)
			{
				//D3DXMatrixPerspectiveFovLH
				/*
				w       0       0               0
				0       h       0               0
				0       0       zf/(zf-zn)      1
				0       0       -zn*zf/(zf-zn)  0
				*/
				
				this->raw.m.ax_x = t_w;
				this->raw.m.ax_y = 0.0f;
				this->raw.m.ax_z = 0.0f;
				this->raw.m.ax_w = 0.0f;

				this->raw.m.ay_x = 0.0f;
				this->raw.m.ay_y = t_h;
				this->raw.m.ay_z = 0.0f;
				this->raw.m.ay_w = 0.0f;

				this->raw.m.az_x = 0.0f;
				this->raw.m.az_y = 0.0f;
				this->raw.m.az_z = a_far / (a_far - a_near);
				this->raw.m.az_w = 1.0f;

				this->raw.m.tr_x = 0.0f;
				this->raw.m.tr_y = 0.0f;
				this->raw.m.tr_z = -(a_near * a_far) / (a_far - a_near);
				this->raw.m.tr_w = 0.0f;
			}
			#else
			{
				//D3DXMatrixPerspectiveFovRH 
				/*
				w       0       0                0
				0       h       0                0
				0       0       zf/(zn-zf)      -1
				0       0       zn*zf/(zn-zf)    0
				*/

				this->ax_x = t_w;
				this->ax_y = 0.0f;
				this->ax_z = 0.0f;
				this->ax_w = 0.0f;

				this->ay_x = 0.0f;
				this->ay_y = t_h;
				this->ay_z = 0.0f;
				this->ay_w = 0.0f;

				this->az_x = 0.0f;
				this->az_y = 0.0f;
				this->az_z = a_far / (a_near - a_far);
				this->az_w = -1.0f;

				this->tr_x = 0.0f;
				this->tr_y = 0.0f;
				this->tr_z = a_near * a_far / (a_near - a_far);
				this->tr_w = 0.0f;
			}
			#endif
		}
		#else
		{
			#if(BSYS_GEOMETRY_LEFTRIGHT_TYPE == 0x00)
			{

				this->ax_x = t_w;
				this->ay_x = 0.0f;
				this->az_x = 0.0f;
				this->tr_x = 0.0f;

				this->ax_y = 0.0f;
				this->ay_y = t_h;
				this->az_y = 0.0f;
				this->tr_y = 0.0f;

				this->ax_z = 0.0f;
				this->ay_z = 0.0f;
				this->az_z = (a_far + a_near) / (a_far - a_near);
				this->tr_z = 1.0f;

				this->ax_w = 0.0f;
				this->ay_w = 0.0f;
				this->az_w = -2 * (a_far * a_near) / (a_far - a_near);
				this->tr_w = 0.0f;
			}
			#else
			{
				//gluPerspective

				this->ax_x = t_w;
				this->ay_x = 0.0f;
				this->az_x = 0.0f;
				this->tr_x = 0.0f;

				this->ax_y = 0.0f;
				this->ay_y = t_h;
				this->az_y = 0.0f;
				this->tr_y = 0.0f;

				this->ax_z = 0.0f;
				this->ay_z = 0.0f;
				this->az_z = (a_far + a_near) / (a_near - a_far);
				this->tr_z = -1.0f;

				this->ax_w = 0.0f;
				this->ay_w = 0.0f;
				this->az_w = 2 * (a_far * a_near) / (a_near - a_far);
				this->tr_w = 0.0f;
			}
			#endif
		}
		#endif
	}


	/** [設定]プロジェクション。正射影。
	*/
	inline void Geometry_Matrix_44::Set_OrthographicProjectionMatrix(f32 a_left,f32 a_right,f32 a_top,f32 a_bottom,f32 a_near,f32 a_far)
	{
		this->Set(
			2/(a_right - a_left),                     0.0f,                                   0.0f,                                 0.0f,
			0.0f,                                     2/(a_top - a_bottom),                   0.0f,                                 0.0f,
			0.0f,                                     0.0f,                                   -2/(a_far - a_near),                  0.0f,
			-(a_right + a_left) / (a_right - a_left), -(a_top + a_bottom)/(a_top - a_bottom), -(a_far + a_near) / (a_far - a_near), 1.0f
		);
	}


	/** [設定]ビュー。
	*/
	inline void Geometry_Matrix_44::Set_ViewMatrix(const Geometry_Vector3& a_camera_target,const Geometry_Vector3& a_camera_position,const Geometry_Vector3& a_camera_up)
	{
		#if(BSYS_GEOMETRY_LEFTRIGHT_TYPE == 0x00)
		{
			Geometry_Vector3 t_axis_zz = a_camera_target - a_camera_position;
			t_axis_zz.Set_Normalize();

			Geometry_Vector3 t_axis_xx = a_camera_up.Make_Cross(t_axis_zz);
			t_axis_xx.Set_Normalize();

			Geometry_Vector3 t_axis_yy = t_axis_zz.Make_Cross(t_axis_xx);

			this->raw.m.ax_x = t_axis_xx.raw.v.xx;
			this->raw.m.ax_y = t_axis_yy.raw.v.xx;
			this->raw.m.ax_z = t_axis_zz.raw.v.xx;
			this->raw.m.ax_w = 0.0f;

			this->raw.m.ay_x = t_axis_xx.raw.v.yy;
			this->raw.m.ay_y = t_axis_yy.raw.v.yy;
			this->raw.m.ay_z = t_axis_zz.raw.v.yy;
			this->raw.m.ay_w = 0.0f;

			this->raw.m.az_x = t_axis_xx.raw.v.zz;
			this->raw.m.az_y = t_axis_yy.raw.v.zz;
			this->raw.m.az_z = t_axis_zz.raw.v.zz;
			this->raw.m.az_w = 0.0f;

			this->raw.m.tr_x = -t_axis_xx.Dot( a_camera_position );
			this->raw.m.tr_y = -t_axis_yy.Dot( a_camera_position );
			this->raw.m.tr_z = -t_axis_zz.Dot( a_camera_position );
			this->raw.m.tr_w = 1.0f;
		}
		#else
		{
			Geometry_Vector3 t_axis_zz = a_camera_position - a_camera_target;
			t_axis_zz.Set_Normalize();

			Geometry_Vector3 t_axis_xx = a_camera_up.Make_Cross(t_axis_zz);
			t_axis_xx.Set_Normalize();

			Geometry_Vector3 t_axis_yy = t_axis_zz.Make_Cross(t_axis_xx);

			this->Set(

				t_axis_xx.x,
				t_axis_yy.x,
				t_axis_zz.x,
				0.0f,

				t_axis_xx.y,
				t_axis_yy.y,
				t_axis_zz.y,
				0.0f,

				t_axis_xx.z,
				t_axis_yy.z,
				t_axis_zz.z,
				0.0f,

				-t_axis_xx.Dot( a_camera_position ),
				-t_axis_yy.Dot( a_camera_position ),
				-t_axis_zz.Dot( a_camera_position ),
				1.0f
			);
		}
		#endif
	}


	/** [設定]ビューポート、
	*/
	inline void Geometry_Matrix_44::Set_ViewPortMatrix(const Size2DType<f32>& a_size)
	{
		this->Set(
			//------------//------------//------------//------------
			a_size.ww/2,  0.0f,         0.0f,         0.0f,
			0.0f,        -a_size.hh/2,  0.0f,         0.0f,
			0.0f,         0.0f,         1.0f,         0.0f,
			a_size.ww/2,  a_size.hh/2,  0.0f,         1.0f
		);
	}


}}
#pragma warning(pop)
#endif

