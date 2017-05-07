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
#include "./geometry_matrix.h"
#include "./geometry_tool.h"


/** NBsys::NGeometry
*/
#if(BSYS_GEOMETRY_ENABLE)
namespace NBsys{namespace NGeometry
{
	/** NBsys::NGeometry::NImpl_Matrix
	*/
	namespace NImpl_Matrix
	{
		/** sinf
		*/
		inline f32 sinf(f32 a_rad)
		{
			#if(BSYS_GEOMETRY_MATRIX_SINCOSFAST_ENABLE)
			return Math::sinf_fast(a_rad);
			#else
			return Math::sinf(a_rad);
			#endif
		}

		/** cosf
		*/
		inline f32 cosf(f32 a_rad)
		{
			#if(BSYS_GEOMETRY_MATRIX_SINCOSFAST_ENABLE)
			return Math::cosf_fast(a_rad);
			#else
			return Math::cosf(a_rad);
			#endif
		}
	}

	/** constructor�B
	*/
	inline Geometry_Matrix_44::Geometry_Matrix_44()
	{
	}

	/** constructor�B
	*/
	inline Geometry_Matrix_44::Geometry_Matrix_44(
		f32 a_ax_x,f32 a_ax_y,f32 a_ax_z,f32 a_ax_w,
		f32 a_ay_x,f32 a_ay_y,f32 a_ay_z,f32 a_ay_w,
		f32 a_az_x,f32 a_az_y,f32 a_az_z,f32 a_az_w,
		f32 a_tr_x,f32 a_tr_y,f32 a_tr_z,f32 a_tr_w
	)
	{
		this->ax_x = a_ax_x;
		this->ax_y = a_ax_y;
		this->ax_z = a_ax_z;
		this->ax_w = a_ax_w;

		this->ay_x = a_ay_x;
		this->ay_y = a_ay_y;
		this->ay_z = a_ay_z;
		this->ay_w = a_ay_w;

		this->az_x = a_az_x;
		this->az_y = a_az_y;
		this->az_z = a_az_z;
		this->az_w = a_az_w;

		this->tr_x = a_tr_x;
		this->tr_y = a_tr_y;
		this->tr_z = a_tr_z;
		this->tr_w = a_tr_w;
	}

	/** constructor�B
	*/
	inline Geometry_Matrix_44::Geometry_Matrix_44(const Geometry_Identity& /*a_identity*/)
	{
		*this = Geometry_Matrix_44::Identity();
	}

	/** constructor�B
	*/
	inline Geometry_Matrix_44::Geometry_Matrix_44(const Geometry_Quaternion& a_quaternion)
	{
		this->Set_Quaternion(a_quaternion);
	}

	/** constructor
	*/
	inline Geometry_Matrix_44::Geometry_Matrix_44(const f32* a_m)
	{
		this->m_11 = a_m[0];
		this->m_12 = a_m[1];
		this->m_13 = a_m[2];
		this->m_14 = a_m[3];

		this->m_21 = a_m[4];
		this->m_22 = a_m[5];
		this->m_23 = a_m[6];
		this->m_24 = a_m[7];

		this->m_31 = a_m[8];
		this->m_32 = a_m[9];
		this->m_33 = a_m[10];
		this->m_34 = a_m[11];

		this->m_41 = a_m[12];
		this->m_42 = a_m[13];
		this->m_43 = a_m[14];
		this->m_44 = a_m[15];
	}

	/** destructor�B
	*/
	inline Geometry_Matrix_44::~Geometry_Matrix_44()
	{
	}

	/** [static]Identity�B
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

	/** [�ݒ�]Identity�B
	*/
	inline void Geometry_Matrix_44::Set_Identity()
	{
		*this = Geometry_Matrix_44::Identity();
	}

	/** [�ݒ�]�B
	*/
	inline void Geometry_Matrix_44::Set(
		f32 a_ax_x,f32 a_ax_y,f32 a_ax_z,f32 a_ax_w,
		f32 a_ay_x,f32 a_ay_y,f32 a_ay_z,f32 a_ay_w,
		f32 a_az_x,f32 a_az_y,f32 a_az_z,f32 a_az_w,
		f32 a_tr_x,f32 a_tr_y,f32 a_tr_z,f32 a_tr_w
	)
	{
		this->ax_x = a_ax_x;
		this->ax_y = a_ax_y;
		this->ax_z = a_ax_z;
		this->ax_w = a_ax_w;

		this->ay_x = a_ay_x;
		this->ay_y = a_ay_y;
		this->ay_z = a_ay_z;
		this->ay_w = a_ay_w;

		this->az_x = a_az_x;
		this->az_y = a_az_y;
		this->az_z = a_az_z;
		this->az_w = a_az_w;

		this->tr_x = a_tr_x;
		this->tr_y = a_tr_y;
		this->tr_z = a_tr_z;
		this->tr_w = a_tr_w;
	}

	/** [�쐬]�w���B
	*/
	inline Geometry_Vector3 Geometry_Matrix_44::Make_AxisX() const
	{
		Geometry_Vector3 t_temp;
		{
			t_temp.x = this->ax_x;
			t_temp.y = this->ax_y;
			t_temp.z = this->ax_z;
		}
		return t_temp;
	}

	/** [�쐬]�x���B
	*/
	inline Geometry_Vector3 Geometry_Matrix_44::Make_AxisY() const
	{
		Geometry_Vector3 t_temp;
		{
			t_temp.x = this->ay_x;
			t_temp.y = this->ay_y;
			t_temp.z = this->ay_z;
		}
		return t_temp;
	}

	/** [�쐬]�y���B
	*/
	inline Geometry_Vector3 Geometry_Matrix_44::Make_AxisZ() const
	{
		Geometry_Vector3 t_temp;
		{
			t_temp.x = this->az_x;
			t_temp.y = this->az_y;
			t_temp.z = this->az_z;
		}
		return t_temp;
	}

	/** [�ݒ�]�w���B
	*/
	inline void Geometry_Matrix_44::Set_AxisX(const Geometry_Vector3& a_vector)
	{
		this->ax_x = a_vector.x;
		this->ax_y = a_vector.y;
		this->ax_z = a_vector.z;
	}

	/** [�ݒ�]�x���B
	*/
	inline void Geometry_Matrix_44::Set_AxisY(const Geometry_Vector3& a_vector)
	{
		this->ay_x = a_vector.x;
		this->ay_y = a_vector.y;
		this->ay_z = a_vector.z;
	}

	/** [�ݒ�]�y���B
	*/
	inline void Geometry_Matrix_44::Set_AxisZ(const Geometry_Vector3& a_vector)
	{
		this->az_x = a_vector.x;
		this->az_y = a_vector.y;
		this->az_z = a_vector.z;
	}

	/** [�ݒ�]���s�ړ��B
	*/
	inline void Geometry_Matrix_44::Set_Translate(f32 a_x,f32 a_y,f32 a_z)
	{
		this->tr_x = a_x;
		this->tr_y = a_y;
		this->tr_z = a_z;
	}

	/** [�ݒ�]���s�ړ��B
	*/
	inline void Geometry_Matrix_44::Set_Translate(const Geometry_Vector3& a_vector)
	{
		this->tr_x = a_vector.x;
		this->tr_y = a_vector.y;
		this->tr_z = a_vector.z;
	}

	/** [static][�쐬]���s�ړ��B
	*/
	inline Geometry_Matrix_44 Geometry_Matrix_44::Make_Translate(f32 a_x,f32 a_y,f32 a_z)
	{
		Geometry_Matrix_44 t_temp = Geometry_Identity();
		{
			t_temp.tr_x = a_x;
			t_temp.tr_y = a_y;
			t_temp.tr_z = a_z;
		}

		return t_temp;
	}

	/** [�쐬]���s�ړ��B
	*/
	inline Geometry_Vector3 Geometry_Matrix_44::Make_Translate_Vector() const
	{
		Geometry_Vector3 t_temp(this->tr_x,this->tr_y,this->tr_z);

		return t_temp;
	}

	/** [�쐬]���s�ړ��B
	*/
	inline Geometry_Matrix_44 Geometry_Matrix_44::Make_Translate() const
	{
		Geometry_Matrix_44 t_temp = Geometry_Identity();
		{
			t_temp.tr_x = this->tr_x;
			t_temp.tr_y = this->tr_y;
			t_temp.tr_z = this->tr_z;
		}

		return t_temp;
	}

	/** [���f]�X�P�[���B
	*/
	inline void Geometry_Matrix_44::Calc_Scale(f32 a_x,f32 a_y,f32 a_z)
	{
		Geometry_Vector3 t_axis_x = this->Make_AxisX();
		Geometry_Vector3 t_axis_y = this->Make_AxisY();
		Geometry_Vector3 t_axis_z = this->Make_AxisZ();

		t_axis_x.Set_Normalize();
		t_axis_y.Set_Normalize();
		t_axis_z.Set_Normalize();

		this->Set_AxisX(t_axis_x * a_x);
		this->Set_AxisY(t_axis_y * a_y);
		this->Set_AxisZ(t_axis_z * a_z);
	}

	/** [�ݒ�]�X�P�[���B
	*/
	inline void Geometry_Matrix_44::Calc_Scale(const Geometry_Vector3& a_vector)
	{
		this->Calc_Scale(a_vector.x,a_vector.y,a_vector.z);
	}

	/** [�쐬]�e���̃X�P�[���B
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

	/** [static][�쐬]��]�s��B
	*/
	inline Geometry_Matrix_44 Geometry_Matrix_44::Make_RotationXYZ(f32 a_rad_x,f32 a_rad_y,f32 a_rad_z)
	{
		Geometry_Matrix_44 t_temp = Geometry_Matrix_44::Make_RotationX(a_rad_x) * Geometry_Matrix_44::Make_RotationY(a_rad_y) * Geometry_Matrix_44::Make_RotationZ(a_rad_z);

		return t_temp;
	}

	/** [�쐬]��]�s��B
	*/
	inline Geometry_Matrix_44 Geometry_Matrix_44::Make_Rotation() const
	{
		Geometry_Matrix_44 t_temp;
		{
			f32 t_ax_value = (this->ax_x * this->ax_x) + (this->ax_y * this->ax_y) + (this->ax_z * this->ax_z);
			f32 t_ay_value = (this->ay_x * this->ay_x) + (this->ay_y * this->ay_y) + (this->ay_z * this->ay_z);
			f32 t_az_value = (this->az_x * this->az_x) + (this->az_y * this->az_y) + (this->az_z * this->az_z);

			ASSERT(t_ax_value != 0.0f);
			ASSERT(t_ay_value != 0.0f);
			ASSERT(t_az_value != 0.0f);

			t_ax_value = Math::sqrtf(t_ax_value);
			t_ay_value = Math::sqrtf(t_ay_value);
			t_az_value = Math::sqrtf(t_az_value);

			ASSERT(t_ax_value != 0.0f);
			ASSERT(t_ay_value != 0.0f);
			ASSERT(t_az_value != 0.0f);

			t_ax_value = 1.0f / t_ax_value;
			t_ay_value = 1.0f / t_ax_value;
			t_az_value = 1.0f / t_ax_value;

			t_temp.Set(
				this->ax_x * t_ax_value,this->ax_y * t_ax_value,this->ax_z * t_ax_value,0.0f,
				this->ay_x * t_ay_value,this->ay_y * t_ay_value,this->ay_z * t_ay_value,0.0f,
				this->az_x * t_az_value,this->az_y * t_az_value,this->az_z * t_az_value,0.0f,
				0.0f,0.0f,0.0f,1.0f
			);
		}
		return t_temp;
	}

	/** [static][�쐬]��]�s��B
	*/
	inline Geometry_Matrix_44 Geometry_Matrix_44::Make_RotationX(f32 a_rad)
	{
		Geometry_Matrix_44 t_temp;
		{
			f32 t_sin_x = NImpl_Matrix::sinf(a_rad);
			f32 t_cos_x = NImpl_Matrix::cosf(a_rad);

			t_temp.ax_x = 1.0f;
			t_temp.ax_y = 0.0f;
			t_temp.ax_z = 0.0f;
			t_temp.ax_w = 0.0f;

			t_temp.ay_x = 0.0f;
			t_temp.ay_y = t_cos_x;
			t_temp.ay_z = t_sin_x;
			t_temp.ay_w = 0.0f;

			t_temp.az_x = 0.0f;
			t_temp.az_y = -t_sin_x;
			t_temp.az_z = t_cos_x;
			t_temp.az_w = 0.0f;

			t_temp.tr_x = 0.0f;
			t_temp.tr_y = 0.0f;
			t_temp.tr_z = 0.0f;
			t_temp.tr_w = 1.0f;
		}
		return t_temp;
	}

	/** [static][�쐬]��]�s��B
	*/
	inline Geometry_Matrix_44 Geometry_Matrix_44::Make_RotationY(f32 a_rad)
	{
		Geometry_Matrix_44 t_temp;
		{
			f32 t_sin_y = NImpl_Matrix::sinf(a_rad);
			f32 t_cos_y = NImpl_Matrix::cosf(a_rad);

			t_temp.ax_x = t_cos_y;
			t_temp.ax_y = 0.0f;
			t_temp.ax_z = -t_sin_y;
			t_temp.ax_w = 0.0f;

			t_temp.ay_x = 0.0f;
			t_temp.ay_y = 1.0f;
			t_temp.ay_z = 0.0f;
			t_temp.ay_w = 0.0f;

			t_temp.az_x = t_sin_y;
			t_temp.az_y = 0.0f;
			t_temp.az_z = t_cos_y;
			t_temp.az_w = 0.0f;

			t_temp.tr_x = 0.0f;
			t_temp.tr_y = 0.0f;
			t_temp.tr_z = 0.0f;
			t_temp.tr_w = 1.0f;
		}
		return t_temp;
	}

	/** [static][�쐬]��]�s��B
	*/
	inline Geometry_Matrix_44 Geometry_Matrix_44::Make_RotationZ(f32 a_rad)
	{
		Geometry_Matrix_44 t_temp;
		{
			f32 t_sin_z = NImpl_Matrix::sinf(a_rad);
			f32 t_cos_z = NImpl_Matrix::cosf(a_rad);

			t_temp.ax_x = t_cos_z;
			t_temp.ax_y = t_sin_z;
			t_temp.ax_z = 0.0f;
			t_temp.ax_w = 0.0f;

			t_temp.ay_x = -t_sin_z;
			t_temp.ay_y = t_cos_z;
			t_temp.ay_z = 0.0f;
			t_temp.ay_w = 0.0f;

			t_temp.az_x = 0.0f;
			t_temp.az_y = 0.0f;
			t_temp.az_z = 1.0f;
			t_temp.az_w = 0.0f;

			t_temp.tr_x = 0.0f;
			t_temp.tr_y = 0.0f;
			t_temp.tr_z = 0.0f;
			t_temp.tr_w = 1.0f;
		}
		return t_temp;
	}

	/** [�ݒ�]��]�s��B
	*/
	inline void Geometry_Matrix_44::Set_RotationX(f32 a_rad)
	{
		f32 t_sin_x = NImpl_Matrix::sinf(a_rad);
		f32 t_cos_x = NImpl_Matrix::cosf(a_rad);

		this->ax_x = 1.0f;
		this->ax_y = 0.0f;
		this->ax_z = 0.0f;
		this->ax_w = 0.0f;

		this->ay_x = 0.0f;
		this->ay_y = t_cos_x;
		this->ay_z = t_sin_x;
		this->ay_w = 0.0f;

		this->az_x = 0.0f;
		this->az_y = -t_sin_x;
		this->az_z = t_cos_x;
		this->az_w = 0.0f;

		this->tr_x = 0.0f;
		this->tr_y = 0.0f;
		this->tr_z = 0.0f;
		this->tr_w = 1.0f;
	}

	/** [�ݒ�]��]�s��B
	*/
	inline void Geometry_Matrix_44::Set_RotationY(f32 a_rad)
	{
		f32 t_sin_y = NImpl_Matrix::sinf(a_rad);
		f32 t_cos_y = NImpl_Matrix::cosf(a_rad);

		this->ax_x = t_cos_y;
		this->ax_y = 0.0f;
		this->ax_z = -t_sin_y;
		this->ax_w = 0.0f;

		this->ay_x = 0.0f;
		this->ay_y = 1.0f;
		this->ay_z = 0.0f;
		this->ay_w = 0.0f;

		this->az_x = t_sin_y;
		this->az_y = 0.0f;
		this->az_z = t_cos_y;
		this->az_w = 0.0f;

		this->tr_x = 0.0f;
		this->tr_y = 0.0f;
		this->tr_z = 0.0f;
		this->tr_w = 1.0f;
	}

	/** [�ݒ�]��]�s��B
	*/
	inline void Geometry_Matrix_44::Set_RotationZ(f32 a_rad)
	{
		f32 t_sin_z = NImpl_Matrix::sinf(a_rad);
		f32 t_cos_z = NImpl_Matrix::cosf(a_rad);

		this->ax_x = t_cos_z;
		this->ax_y = t_sin_z;
		this->ax_z = 0.0f;
		this->ax_w = 0.0f;

		this->ay_x = -t_sin_z;
		this->ay_y = t_cos_z;
		this->ay_z = 0.0f;
		this->ay_w = 0.0f;

		this->az_x = 0.0f;
		this->az_y = 0.0f;
		this->az_z = 1.0f;
		this->az_w = 0.0f;

		this->tr_x = 0.0f;
		this->tr_y = 0.0f;
		this->tr_z = 0.0f;
		this->tr_w = 1.0f;
	}

	/** [�ݒ�]��]�s��B
	*/
	inline void Geometry_Matrix_44::Set_RotationVector(const Geometry_Vector3& a_vector,f32 a_rad)
	{
		f32 t_cos = NImpl_Matrix::cosf(a_rad);
		f32 t_sin = NImpl_Matrix::sinf(a_rad);
		f32 t_1_cos = 1 - t_cos;

		Geometry_Vector3 t_vector = a_vector.Make_Normalize();

		this->ax_x = t_1_cos * t_vector.x * t_vector.x + t_cos;
		this->ax_y = t_vector.x * t_vector.y * t_1_cos - t_vector.z * t_sin;
		this->ax_z = t_vector.x * t_vector.z * t_1_cos + t_vector.y * t_sin;
		this->ax_w = 0.0f;

		this->ay_x = t_vector.x * t_vector.y * t_1_cos + t_vector.z * t_sin;
		this->ay_y = t_1_cos * t_vector.y * t_vector.y + t_cos;
		this->ay_z = t_vector.y * t_vector.z * t_1_cos - t_vector.x * t_sin;
		this->ay_w = 0.0f;

		this->az_x = t_vector.x * t_vector.z * t_1_cos - t_vector.y * t_sin;
		this->az_y = t_vector.y * t_vector.z * t_1_cos + t_vector.x * t_sin;
		this->az_z = t_1_cos * t_vector.z * t_vector.z + t_cos;
		this->az_w = 0.0f;

		this->tr_x = 0.0f;
		this->tr_y = 0.0f;
		this->tr_z = 0.0f;
		this->tr_w = 1.0f;
	}

	/** [�쐬]�t�s��B
	*/
	inline Geometry_Matrix_44 Geometry_Matrix_44::Make_Inverse() const
	{
		f32 t_ax_x = this->ay_y * this->az_z - this->ay_z * this->az_y;
		f32 t_ax_y = this->ax_y * this->az_z - this->ax_z * this->az_y;
		f32 t_ax_z = this->ax_y * this->ay_z - this->ax_z * this->ay_y;

		f32 t_ay_x = this->ay_x * this->az_z - this->ay_z * this->az_x;
		f32 t_ay_y = this->ax_x * this->az_z - this->ax_z * this->az_x;
		f32 t_ay_z = this->ax_x * this->ay_z - this->ax_z * this->ay_x;

		f32 t_az_x = this->ay_x * this->az_y - this->ay_y * this->az_x;
		f32 t_az_y = this->ax_x * this->az_y - this->ax_y * this->az_x;
		f32 t_az_z = this->ax_x * this->ay_y - this->ax_y * this->ay_x;
		
		f32 t_det = (this->ax_x * t_ax_x) - (this->ax_y * t_ay_x) + (this->ax_z * t_az_x);
		t_det = 1.0f / t_det;

		Geometry_Matrix_44 t_temp;
		{
			t_temp.ax_x =  t_ax_x * t_det;
			t_temp.ax_y = -t_ax_y * t_det;
			t_temp.ax_z =  t_ax_z * t_det;
			t_temp.ax_w = 0.0f;

			t_temp.ay_x = -t_ay_x * t_det;
			t_temp.ay_y =  t_ay_y * t_det;
			t_temp.ay_z = -t_ay_z * t_det;
			t_temp.ay_w = 0.0f;

			t_temp.az_x =  t_az_x * t_det;
			t_temp.az_y = -t_az_y * t_det;
			t_temp.az_z =  t_az_z * t_det;
			t_temp.az_w = 0.0f;

			f32 t_tr_x = -((this->tr_x * t_temp.ax_x) + (this->tr_y * t_temp.ay_x) + (this->tr_z * t_temp.az_x));
			f32 t_tr_y = -((this->tr_x * t_temp.ax_y) + (this->tr_y * t_temp.ay_y) + (this->tr_z * t_temp.az_y));
			f32 t_tr_z = -((this->tr_x * t_temp.ax_z) + (this->tr_y * t_temp.ay_z) + (this->tr_z * t_temp.az_z));

			t_temp.tr_x = t_tr_x;
			t_temp.tr_y = t_tr_y;
			t_temp.tr_z = t_tr_z;
			t_temp.tr_w = 1.0f;
		}

		return t_temp;
	}

	/** [�ݒ�]�t�s��B
	*/
	inline void Geometry_Matrix_44::Set_Inverse()
	{
		f32 t_ax_x = (this->ay_y * this->az_z) - (this->ay_z * this->az_y);
		f32 t_ax_y = (this->ax_y * this->az_z) - (this->ax_z * this->az_y);
		f32 t_ax_z = (this->ax_y * this->ay_z) - (this->ax_z * this->ay_y);

		f32 t_ay_x = (this->ay_x * this->az_z) - (this->ay_z * this->az_x);
		f32 t_ay_y = (this->ax_x * this->az_z) - (this->ax_z * this->az_x);
		f32 t_ay_z = (this->ax_x * this->ay_z) - (this->ax_z * this->ay_x);

		f32 t_az_x = (this->ay_x * this->az_y) - (this->ay_y * this->az_x);
		f32 t_az_y = (this->ax_x * this->az_y) - (this->ax_y * this->az_x);
		f32 t_az_z = (this->ax_x * this->ay_y) - (this->ax_y * this->ay_x);
		
		f32 t_det = (this->ax_x * t_ax_x) - (this->ax_y * t_ay_x) + (this->ax_z * t_az_x);
		t_det = 1.0f / t_det;

		{
			this->ax_x =  t_ax_x * t_det;
			this->ax_y = -t_ax_y * t_det;
			this->ax_z =  t_ax_z * t_det;
			this->ax_w = 0.0f;

			this->ay_x = -t_ay_x * t_det;
			this->ay_y =  t_ay_y * t_det;
			this->ay_z = -t_ay_z * t_det;
			this->ay_w = 0.0f;

			this->az_x =  t_az_x * t_det;
			this->az_y = -t_az_y * t_det;
			this->az_z =  t_az_z * t_det;
			this->az_w = 0.0f;

			f32 t_tr_x = -((this->tr_x * this->ax_x) + (this->tr_y * this->ay_x) + (this->tr_z * this->az_x));
			f32 t_tr_y = -((this->tr_x * this->ax_y) + (this->tr_y * this->ay_y) + (this->tr_z * this->az_y));
			f32 t_tr_z = -((this->tr_x * this->ax_z) + (this->tr_y * this->ay_z) + (this->tr_z * this->az_z));

			this->tr_x = t_tr_x;
			this->tr_y = t_tr_y;
			this->tr_z = t_tr_z;
			this->tr_w = 1.0f;
		}
	}

	/** [�ݒ�]Set_Lookat�B
	*/
	inline void Geometry_Matrix_44::Set_Lookat(const Geometry_Vector3& a_position,const Geometry_Vector3& a_target,const Geometry_Vector3& a_up)
	{
		Geometry_Vector3 t_z = a_target - a_position;
		t_z.Set_Normalize();

		Geometry_Vector3 t_x = a_up.Make_Cross(t_z);
		t_x.Set_Normalize();

		Geometry_Vector3 t_y = t_z.Make_Cross(t_x);
		t_y.Set_Normalize();

		{
			this->ax_x = t_x.x;
			this->ax_y = t_x.y;
			this->ax_z = t_x.z;
			this->ax_w = 0.0f;

			this->ay_x = t_y.x;
			this->ay_y = t_y.y;
			this->ay_z = t_y.z;
			this->ay_w = 0.0f;

			this->az_x = t_z.x;
			this->az_y = t_z.y;
			this->az_z = t_z.z;
			this->az_w = 0.0f;

			this->tr_x = 0.0f;
			this->tr_y = 0.0f;
			this->tr_z = 0.0f;
			this->tr_w = 1.0f;
		}
	}
	
	/** [�ݒ�]Set_LookatLimit�B
	*/
	inline void Geometry_Matrix_44::Set_LookatLimit(const Geometry_Vector3& a_position,const Geometry_Vector3& a_target,const Geometry_Vector3& a_up)
	{
		Geometry_Vector3 t_dir = a_target - a_position;
		t_dir.Set_Normalize();

		Geometry_Vector3 t_y = a_up;
		t_y.Set_Normalize();

		Geometry_Vector3 t_x = t_y.Make_Cross(t_dir);
		t_x.Set_Normalize();

		Geometry_Vector3 t_z = t_x.Make_Cross(t_y);
		t_z.Set_Normalize();

		{
			this->ax_x = t_x.x;
			this->ax_y = t_x.y;
			this->ax_z = t_x.z;
			this->ax_w = 0.0f;

			this->ay_x = t_y.x;
			this->ay_y = t_y.y;
			this->ay_z = t_y.z;
			this->ay_w = 0.0f;

			this->az_x = t_z.x;
			this->az_y = t_z.y;
			this->az_z = t_z.z;
			this->az_w = 0.0f;

			this->tr_x = 0.0f;
			this->tr_y = 0.0f;
			this->tr_z = 0.0f;
			this->tr_w = 1.0f;
		}
	}

	/** [�쐬]�N�I�[�^�j�I���B
	*/
	inline Geometry_Quaternion Geometry_Matrix_44::Make_Quaternion() const
	{
		Geometry_Quaternion t_temp_quaternion;
		{
			f32 t_tr = this->ax_x + this->ay_y + this->az_z;
			if(t_tr > 0.0f){

				f32 t_s = Math::sqrtf(t_tr + 1.0f);
				t_temp_quaternion.w = t_s * 0.5f;
				t_s = 0.5f / t_s;

				t_temp_quaternion.x = (this->az_y - this->ay_z) * t_s;
				t_temp_quaternion.y = (this->ax_z - this->az_x) * t_s;
				t_temp_quaternion.z = (this->ay_x - this->ax_y) * t_s;

			}else{

				s32 ii = 0;
				{
					if(this->ay_y > this->ax_x){
						ii = 1;
					}
					if(this->az_z > this->m[ii][ii]){
						ii = 2;
					}
				}

				s32 t_next[3] = {1, 2, 0};
				s32 jj = t_next[ii];
				s32 kk = t_next[jj];

				f32 t_s = Math::sqrtf((this->m[ii][ii] - (this->m[jj][jj] + this->m[kk][kk])) + 1.0f);

				f32 t_temp[3];
				t_temp[ii] = t_s * 0.5f;

				if(t_s != 0.0f){
					t_s = 0.5f / t_s;
				}

				t_temp_quaternion.w = (this->m[kk][jj] - this->m[jj][kk]) * t_s;
				t_temp[jj] = (this->m[ii][jj] + this->m[jj][ii]) * t_s;
				t_temp[kk] = (this->m[ii][kk] + this->m[kk][ii]) * t_s;

				t_temp_quaternion.x = t_temp[0];
				t_temp_quaternion.y = t_temp[1];
				t_temp_quaternion.z = t_temp[2];
			}
		}
		return t_temp_quaternion;
	}

	/** [�쐬]�N�I�[�^�j�I���B
	*/
	inline Geometry_Quaternion Geometry_Matrix_44::Make_Quaternion_Safe() const
	{
		Geometry_Matrix_44 t_temp = this->Make_Rotation();
		return t_temp.Make_Quaternion();
	}

	/** [�ݒ�]�N�I�[�^�j�I���B
	*/
	inline void Geometry_Matrix_44::Set_Quaternion(const Geometry_Quaternion& a_quaternion)
	{
		f32 t_s = 2.0f / ((a_quaternion.x * a_quaternion.x) + (a_quaternion.y * a_quaternion.y) + (a_quaternion.z * a_quaternion.z) + (a_quaternion.w * a_quaternion.w));

		f32 t_wx = a_quaternion.w * a_quaternion.x * t_s;
		f32 t_wy = a_quaternion.w * a_quaternion.y * t_s;
		f32 t_wz = a_quaternion.w * a_quaternion.z * t_s;

		f32 t_xx = a_quaternion.x * a_quaternion.x * t_s;
		f32 t_xy = a_quaternion.x * a_quaternion.y * t_s;
		f32 t_xz = a_quaternion.x * a_quaternion.z * t_s;

		f32 t_yy = a_quaternion.y * a_quaternion.y * t_s;
		f32 t_yz = a_quaternion.y * a_quaternion.z * t_s;
		f32 t_zz = a_quaternion.z * a_quaternion.z * t_s;

		this->ax_x = 1.0f - (t_yy + t_zz);
		this->ax_y = t_xy - t_wz;
		this->ax_z = t_xz + t_wy;
		this->ax_w = 0.0f;

		this->ay_x = t_xy + t_wz;
		this->ay_y = 1.0f - (t_xx + t_zz);
		this->ay_z = t_yz - t_wx;
		this->ay_w = 0.0f;

		this->az_x = t_xz - t_wy;
		this->az_y = t_yz + t_wx;
		this->az_z = 1.0f - (t_xx + t_yy);
		this->az_w = 0.0f;

		this->tr_x = 0.0f;
		this->tr_y = 0.0f;
		this->tr_z = 0.0f;
		this->tr_w = 1.0f;
	}

	/** [�ݒ�]�v���W�F�N�V�����B�������e�B
	*/
	inline void Geometry_Matrix_44::Set_PerspectiveProjectionMatrix(f32 a_width,f32 a_height,f32 a_fov_deg,f32 a_near,f32 a_far)
	{
		f32 t_aspect = a_width / a_height;
		f32 t_fov_radian =  BLIB_MATH_DEG_TO_RAD(a_fov_deg);
		f32 t_scale = 1.0f / Math::tanf(t_fov_radian / 2);

		#if(BSYS_GEOMETRY_PERSPECTIVE_TYPE == 0x00)
		{
			//gluPerspective
			this->Set(
				t_scale/t_aspect, 0.0f,    0.0f,                                   0.0f,
				0.0f,             t_scale, 0.0f,                                   0.0f,
				0.0f,             0.0f,    (a_far + a_near)/(a_near - a_far),     -1.0f,
				0.0f,             0.0f,    2 * (a_far * a_near)/(a_near - a_far),  0.0f
			);
		}
		#else
		{
			//D3DXMatrixPerspectiveFovRH
			this->Set(
				t_scale/t_aspect, 0.0f,    0.0f,                                   0.0f,
				0.0f,             t_scale, 0.0f,                                   0.0f,
				0.0f,             0.0f,    a_far / (a_near - a_far),              -1.0f,
				0.0f,             0.0f,    (a_near * a_far)/(a_near - a_far),      0.0f
			);
		}
		#endif
	}

	/** [�ݒ�]�v���W�F�N�V�����B���ˉe�B
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

	/** [�ݒ�]�r���[�B
	*/
	inline void Geometry_Matrix_44::Set_ViewMatrix(const Geometry_Vector3& a_camera_target,const Geometry_Vector3& a_camera_position,const Geometry_Vector3& a_camera_up)
	{
		//TODO:

		static Geometry_Vector3 s_forward(0.0f,0.0f,1.0f);
		static Geometry_Vector3 s_side(1.0f,0.0f,0.0f);

		Geometry_Vector3 t_forward = a_camera_target - a_camera_position;
		t_forward.Set_Normalize_Safe(s_forward);

		Geometry_Vector3 t_side = t_forward.Make_Cross(a_camera_up);
		t_side.Set_Normalize_Safe(s_side);

		Geometry_Vector3 t_up = t_side.Make_Cross(t_forward);
		t_up.Set_Normalize();

		Geometry_Matrix_44 t_move(
			1.0f,0.0f,0.0f,0.0f,
			0.0f,1.0f,0.0f,0.0f,
			0.0f,0.0f,1.0f,0.0f,
			-a_camera_position.x,-a_camera_position.y,-a_camera_position.z,1.0f
		);

		Geometry_Matrix_44 t_rotation(
			t_side.x,t_up.x,-t_forward.x,0.0f,
			t_side.y,t_up.y,-t_forward.y,0.0f,
			t_side.z,t_up.z,-t_forward.z,0.0f,
			0.0f,0.0f,0.0f,1.0f
		);

		*this = t_move;
		*this *= t_rotation;
	}

	/** [�ݒ�]�r���[�|�[�g�A
	*/
	inline void Geometry_Matrix_44::Set_ViewPortMatrix(f32 a_width,f32 a_height)
	{
		this->Set(
			a_width/2,  0.0f,        0.0f, 0.0f,
			0.0f,      -a_height/2,  0.0f, 0.0f,
			0.0f,       0.0f,        1.0f, 0.0f,
			a_width/2,  a_height/2,  0.0f, 1.0f
		);
	}

	/** [�ݒ�]�P�ʌ^�B
	*/
	inline Geometry_Matrix_44& Geometry_Matrix_44::operator =(const Geometry_Identity& /*a_identity*/)
	{
		*this = Geometry_Matrix_44::Identity();

		return *this;
	}

	/** [�ݒ�]��Z�B
	*/
	inline Geometry_Matrix_44& Geometry_Matrix_44::operator *=(const Geometry_Matrix_44& a_matrix)
	{
		f32 t_ax_x = (this->ax_x * a_matrix.ax_x) + (this->ax_y * a_matrix.ay_x) + (this->ax_z * a_matrix.az_x) + (this->ax_w * a_matrix.tr_x);
		f32 t_ax_y = (this->ax_x * a_matrix.ax_y) + (this->ax_y * a_matrix.ay_y) + (this->ax_z * a_matrix.az_y) + (this->ax_w * a_matrix.tr_y);
		f32 t_ax_z = (this->ax_x * a_matrix.ax_z) + (this->ax_y * a_matrix.ay_z) + (this->ax_z * a_matrix.az_z) + (this->ax_w * a_matrix.tr_z);
		f32 t_ax_w = (this->ax_x * a_matrix.ax_w) + (this->ax_y * a_matrix.ay_w) + (this->ax_z * a_matrix.az_w) + (this->ax_w * a_matrix.tr_w);

		f32 t_ay_x = (this->ay_x * a_matrix.ax_x) + (this->ay_y * a_matrix.ay_x) + (this->ay_z * a_matrix.az_x) + (this->ay_w * a_matrix.tr_x);
		f32 t_ay_y = (this->ay_x * a_matrix.ax_y) + (this->ay_y * a_matrix.ay_y) + (this->ay_z * a_matrix.az_y) + (this->ay_w * a_matrix.tr_y);
		f32 t_ay_z = (this->ay_x * a_matrix.ax_z) + (this->ay_y * a_matrix.ay_z) + (this->ay_z * a_matrix.az_z) + (this->ay_w * a_matrix.tr_z);
		f32 t_ay_w = (this->ay_x * a_matrix.ax_w) + (this->ay_y * a_matrix.ay_w) + (this->ay_z * a_matrix.az_w) + (this->ay_w * a_matrix.tr_w);

		f32 t_az_x = (this->az_x * a_matrix.ax_x) + (this->az_y * a_matrix.ay_x) + (this->az_z * a_matrix.az_x) + (this->az_w * a_matrix.tr_x);
		f32 t_az_y = (this->az_x * a_matrix.ax_y) + (this->az_y * a_matrix.ay_y) + (this->az_z * a_matrix.az_y) + (this->az_w * a_matrix.tr_y);
		f32 t_az_z = (this->az_x * a_matrix.ax_z) + (this->az_y * a_matrix.ay_z) + (this->az_z * a_matrix.az_z) + (this->az_w * a_matrix.tr_z);
		f32 t_az_w = (this->az_x * a_matrix.ax_w) + (this->az_y * a_matrix.ay_w) + (this->az_z * a_matrix.az_w) + (this->az_w * a_matrix.tr_w);

		f32 t_tr_x = (this->tr_x * a_matrix.ax_x) + (this->tr_y * a_matrix.ay_x) + (this->tr_z * a_matrix.az_x) + (this->tr_w * a_matrix.tr_x);
		f32 t_tr_y = (this->tr_x * a_matrix.ax_y) + (this->tr_y * a_matrix.ay_y) + (this->tr_z * a_matrix.az_y) + (this->tr_w * a_matrix.tr_y);
		f32 t_tr_z = (this->tr_x * a_matrix.ax_z) + (this->tr_y * a_matrix.ay_z) + (this->tr_z * a_matrix.az_z) + (this->tr_w * a_matrix.tr_z);
		f32 t_tr_w = (this->tr_x * a_matrix.ax_w) + (this->tr_y * a_matrix.ay_w) + (this->tr_z * a_matrix.az_w) + (this->tr_w * a_matrix.tr_w);

		this->ax_x = t_ax_x;
		this->ax_y = t_ax_y;
		this->ax_z = t_ax_z;
		this->ax_w = t_ax_w;

		this->ay_x = t_ay_x;
		this->ay_y = t_ay_y;
		this->ay_z = t_ay_z;
		this->ay_w = t_ay_w;

		this->az_x = t_az_x;
		this->az_y = t_az_y;
		this->az_z = t_az_z;
		this->az_w = t_az_w;

		this->tr_x = t_tr_x;
		this->tr_y = t_tr_y;
		this->tr_z = t_tr_z;
		this->tr_w = t_tr_w;

		return *this;
	}

	/** [�쐬]��Z�B
	*/
	inline Geometry_Matrix_44 Geometry_Matrix_44::operator *(const Geometry_Matrix_44& a_matrix) const
	{
		Geometry_Matrix_44 t_temp;
		{
			t_temp.ax_x = (this->ax_x * a_matrix.ax_x) + (this->ax_y * a_matrix.ay_x) + (this->ax_z * a_matrix.az_x) + (this->ax_w * a_matrix.tr_x);
			t_temp.ax_y = (this->ax_x * a_matrix.ax_y) + (this->ax_y * a_matrix.ay_y) + (this->ax_z * a_matrix.az_y) + (this->ax_w * a_matrix.tr_y);
			t_temp.ax_z = (this->ax_x * a_matrix.ax_z) + (this->ax_y * a_matrix.ay_z) + (this->ax_z * a_matrix.az_z) + (this->ax_w * a_matrix.tr_z);
			t_temp.ax_w = (this->ax_x * a_matrix.ax_w) + (this->ax_y * a_matrix.ay_w) + (this->ax_z * a_matrix.az_w) + (this->ax_w * a_matrix.tr_w);

			t_temp.ay_x = (this->ay_x * a_matrix.ax_x) + (this->ay_y * a_matrix.ay_x) + (this->ay_z * a_matrix.az_x) + (this->ay_w * a_matrix.tr_x);
			t_temp.ay_y = (this->ay_x * a_matrix.ax_y) + (this->ay_y * a_matrix.ay_y) + (this->ay_z * a_matrix.az_y) + (this->ay_w * a_matrix.tr_y);
			t_temp.ay_z = (this->ay_x * a_matrix.ax_z) + (this->ay_y * a_matrix.ay_z) + (this->ay_z * a_matrix.az_z) + (this->ay_w * a_matrix.tr_z);
			t_temp.ay_w = (this->ay_x * a_matrix.ax_w) + (this->ay_y * a_matrix.ay_w) + (this->ay_z * a_matrix.az_w) + (this->ay_w * a_matrix.tr_w);

			t_temp.az_x = (this->az_x * a_matrix.ax_x) + (this->az_y * a_matrix.ay_x) + (this->az_z * a_matrix.az_x) + (this->az_w * a_matrix.tr_x);
			t_temp.az_y = (this->az_x * a_matrix.ax_y) + (this->az_y * a_matrix.ay_y) + (this->az_z * a_matrix.az_y) + (this->az_w * a_matrix.tr_y);
			t_temp.az_z = (this->az_x * a_matrix.ax_z) + (this->az_y * a_matrix.ay_z) + (this->az_z * a_matrix.az_z) + (this->az_w * a_matrix.tr_z);
			t_temp.az_w = (this->az_x * a_matrix.ax_w) + (this->az_y * a_matrix.ay_w) + (this->az_z * a_matrix.az_w) + (this->az_w * a_matrix.tr_w);

			t_temp.tr_x = (this->tr_x * a_matrix.ax_x) + (this->tr_y * a_matrix.ay_x) + (this->tr_z * a_matrix.az_x) + (this->tr_w * a_matrix.tr_x);
			t_temp.tr_y = (this->tr_x * a_matrix.ax_y) + (this->tr_y * a_matrix.ay_y) + (this->tr_z * a_matrix.az_y) + (this->tr_w * a_matrix.tr_y);
			t_temp.tr_z = (this->tr_x * a_matrix.ax_z) + (this->tr_y * a_matrix.ay_z) + (this->tr_z * a_matrix.az_z) + (this->tr_w * a_matrix.tr_z);
			t_temp.tr_w = (this->tr_x * a_matrix.ax_w) + (this->tr_y * a_matrix.ay_w) + (this->tr_z * a_matrix.az_w) + (this->tr_w * a_matrix.tr_w);
		}
		return t_temp;
	}

	/** [�ݒ�]��Z�B
	*/
	inline Geometry_Matrix_44& Geometry_Matrix_44::operator *=(f32 a_value)
	{
		this->ax_x *= a_value;
		this->ax_y *= a_value;
		this->ax_z *= a_value;
		this->ax_w *= a_value;

		this->ay_x *= a_value;
		this->ay_y *= a_value;
		this->ay_z *= a_value;
		this->ay_w *= a_value;

		this->az_x *= a_value;
		this->az_y *= a_value;
		this->az_z *= a_value;
		this->az_w *= a_value;

		this->tr_x *= a_value;
		this->tr_y *= a_value;
		this->tr_z *= a_value;
		this->tr_w *= a_value;

		return *this;
	}

	/** [�쐬]��Z�B
	*/
	inline Geometry_Matrix_44 Geometry_Matrix_44::operator *(f32 a_value)
	{
		Geometry_Matrix_44 t_temp;
		{
			t_temp.ax_x = this->ax_x * a_value;
			t_temp.ax_y = this->ax_y * a_value;
			t_temp.ax_z = this->ax_z * a_value;
			t_temp.ax_w = this->ax_w * a_value;

			t_temp.ay_x = this->ay_x * a_value;
			t_temp.ay_y = this->ay_y * a_value;
			t_temp.ay_z = this->ay_z * a_value;
			t_temp.ay_w = this->ay_w * a_value;

			t_temp.az_x = this->az_x * a_value;
			t_temp.az_y = this->az_y * a_value;
			t_temp.az_z = this->az_z * a_value;
			t_temp.az_w = this->az_w * a_value;

			t_temp.tr_x = this->tr_x * a_value;
			t_temp.tr_y = this->tr_y * a_value;
			t_temp.tr_z = this->tr_z * a_value;
			t_temp.tr_w = this->tr_w * a_value;
		}
		return t_temp;
	}

	/** [�ݒ�]���Z�B
	*/
	inline Geometry_Matrix_44& Geometry_Matrix_44::operator +=(const Geometry_Matrix_44& a_matrix)
	{
		this->ax_x += a_matrix.ax_x;
		this->ax_y += a_matrix.ax_y;
		this->ax_z += a_matrix.ax_z;
		this->ax_w += a_matrix.ax_w;

		this->ay_x += a_matrix.ay_x;
		this->ay_y += a_matrix.ay_y;
		this->ay_z += a_matrix.ay_z;
		this->ay_w += a_matrix.ay_w;

		this->az_x += a_matrix.az_x;
		this->az_y += a_matrix.az_y;
		this->az_z += a_matrix.az_z;
		this->az_w += a_matrix.az_w;

		this->tr_x += a_matrix.tr_x;
		this->tr_y += a_matrix.tr_y;
		this->tr_z += a_matrix.tr_z;
		this->tr_w += a_matrix.tr_w;

		return *this;
	}

	/** [�쐬]���Z�B
	*/
	inline Geometry_Matrix_44 Geometry_Matrix_44::operator +(const Geometry_Matrix_44& a_matrix) const
	{
		Geometry_Matrix_44 t_temp;
		{
			t_temp.ax_x = (this->ax_x + a_matrix.ax_x);
			t_temp.ax_y = (this->ax_y + a_matrix.ax_y);
			t_temp.ax_z = (this->ax_z + a_matrix.ax_z);
			t_temp.ax_w = (this->ax_w + a_matrix.ax_w);

			t_temp.ay_x = (this->ay_x + a_matrix.ay_x);
			t_temp.ay_y = (this->ay_y + a_matrix.ay_y);
			t_temp.ay_z = (this->ay_z + a_matrix.ay_z);
			t_temp.ay_w = (this->ay_w + a_matrix.ay_w);

			t_temp.az_x = (this->az_x + a_matrix.az_x);
			t_temp.az_y = (this->az_y + a_matrix.az_y);
			t_temp.az_z = (this->az_z + a_matrix.az_z);
			t_temp.az_w = (this->az_w + a_matrix.az_w);

			t_temp.tr_x = (this->tr_x + a_matrix.tr_x);
			t_temp.tr_y = (this->tr_y + a_matrix.tr_y);
			t_temp.tr_z = (this->tr_z + a_matrix.tr_z);
			t_temp.tr_w = (this->tr_w + a_matrix.tr_w);
		}
		return t_temp;
	}

}}
#endif

