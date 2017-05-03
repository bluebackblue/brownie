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
#include "./geometry_matrix_raw.h"
#include "./geometry_quaternion.h"


/** NBsys::NGeometry
*/
#if(BSYS_GEOMETRY_ENABLE)
namespace NBsys{namespace NGeometry
{
	/** Geometry_Matrix_44
	*/
	struct Geometry_Matrix_44;

	/** Geometry_Matrix_44
	*/
	struct Geometry_Matrix_44 : public Geometry_Matrix_44_Raw
	{
		/** �R���X�g���N�^�B
		*/
		inline Geometry_Matrix_44();

		/** �R���X�g���N�^�B
		*/
		inline Geometry_Matrix_44(
			f32 a_ax_x,f32 a_ax_y,f32 a_ax_z,f32 a_ax_w,
			f32 a_ay_x,f32 a_ay_y,f32 a_ay_z,f32 a_ay_w,
			f32 a_az_x,f32 a_az_y,f32 a_az_z,f32 a_az_w,
			f32 a_tr_x,f32 a_tr_y,f32 a_tr_z,f32 a_tr_w
		);

		/** �R���X�g���N�^�B
		*/
		inline Geometry_Matrix_44(const Geometry_Identity& /*a_identity*/);

		/** �R���X�g���N�^�B
		*/
		inline Geometry_Matrix_44(const Geometry_Quaternion& a_quaternion);

		/** �f�X�g���N�^�B
		*/
		inline ~Geometry_Matrix_44();

		/** [static]Identity�B
		*/
		static inline const Geometry_Matrix_44& Identity();

		/** [�ݒ�]Identity�B
		*/
		inline void Set_Identity();

		/** [�ݒ�]�B
		*/
		inline void Set(
			f32 a_ax_x,f32 a_ax_y,f32 a_ax_z,f32 a_ax_w,
			f32 a_ay_x,f32 a_ay_y,f32 a_ay_z,f32 a_ay_w,
			f32 a_az_x,f32 a_az_y,f32 a_az_z,f32 a_az_w,
			f32 a_tr_x,f32 a_tr_y,f32 a_tr_z,f32 a_tr_w
		);

		/** [�쐬]�w���B
		*/
		inline Geometry_Vector3 Make_AxisX() const;

		/** [�쐬]�x���B
		*/
		inline Geometry_Vector3 Make_AxisY() const;

		/** [�쐬]�y���B
		*/
		inline Geometry_Vector3 Make_AxisZ() const;

		/** [�ݒ�]�w���B
		*/
		inline void Set_AxisX(const Geometry_Vector3& a_vector);

		/** [�ݒ�]�x���B
		*/
		inline void Set_AxisY(const Geometry_Vector3& a_vector);

		/** [�ݒ�]�y���B
		*/
		inline void Set_AxisZ(const Geometry_Vector3& a_vector);

		/** [�ݒ�]���s�ړ��B
		*/
		inline void Set_Translate(f32 a_x,f32 a_y,f32 a_z);

		/** [�ݒ�]���s�ړ��B
		*/
		inline void Set_Translate(const Geometry_Vector3& a_vector);

		/** [static][�쐬]���s�ړ��B
		*/
		static inline Geometry_Matrix_44 Make_Translate(f32 a_x,f32 a_y,f32 a_z);

		/** [�쐬]���s�ړ��B
		*/
		inline Geometry_Vector3 Make_Translate_Vector() const;

		/** [�쐬]���s�ړ��B
		*/
		inline Geometry_Matrix_44 Make_Translate() const;

		/** [�ݒ�]�X�P�[���B
		*/
		inline void Calc_Scale(f32 a_x,f32 a_y,f32 a_z);

		/** [�ݒ�]�X�P�[���B
		*/
		inline void Calc_Scale(const Geometry_Vector3& a_vector);

		/** [�쐬]�e���̃X�P�[���B
		*/
		inline Geometry_Vector3 Make_Scale_Vector() const;

		/** [static][�쐬]��]�s��B
		*/
		static inline Geometry_Matrix_44 Make_RotationXYZ(f32 a_rad_x,f32 a_rad_y,f32 a_rad_z);

		/** [�쐬]��]�s��B
		*/
		inline Geometry_Matrix_44 Make_Rotation() const;

		/** [static][�쐬]��]�s��B
		*/
		static inline Geometry_Matrix_44 Make_RotationX(f32 a_rad);

		/** [static][�쐬]��]�s��B
		*/
		static inline Geometry_Matrix_44 Make_RotationY(f32 a_rad);

		/** [static][�쐬]��]�s��B
		*/
		static inline Geometry_Matrix_44 Make_RotationZ(f32 a_rad);

		/** [�ݒ�]��]�s��B
		*/
		inline void Set_RotationX(f32 a_rad);

		/** [�ݒ�]��]�s��B
		*/
		inline void Set_RotationY(f32 a_rad);

		/** [�ݒ�]��]�s��B
		*/
		inline void Set_RotationZ(f32 a_rad);

		/** [�ݒ�]��]�s��B
		*/
		inline void Set_RotationVector(const Geometry_Vector3& a_vector,f32 a_rad);

		/** [�쐬]�t�s��B
		*/
		inline Geometry_Matrix_44 Make_Inverse() const;

		/** [�ݒ�]�t�s��B
		*/
		inline void Set_Inverse();

		/** [�ݒ�]Set_Lookat�B
		*/
		inline void Set_Lookat(const Geometry_Vector3& a_position,const Geometry_Vector3& a_target,const Geometry_Vector3& a_up);

		/** [�ݒ�]Set_LookatLimit�B
		*/
		inline void Set_LookatLimit(const Geometry_Vector3& a_position,const Geometry_Vector3& a_target,const Geometry_Vector3& a_up);

		/** [�쐬]�N�I�[�^�j�I���B
		*/
		inline Geometry_Quaternion Make_Quaternion() const;

		/** [�쐬]�N�I�[�^�j�I���B
		*/
		inline Geometry_Quaternion Make_Quaternion_Safe() const;

		/** [�ݒ�]�N�I�[�^�j�I���B
		*/
		inline void Set_Quaternion(const Geometry_Quaternion& a_quaternion);

		/** [�ݒ�]�v���W�F�N�V�����B�������e�B
		*/
		inline void Set_PerspectiveProjectionMatrix(f32 a_width,f32 a_height,f32 a_fov_deg,f32 a_near,f32 a_far);

		/** [�ݒ�]�v���W�F�N�V�����B���ˉe�B
		*/
		inline void Set_OrthographicProjectionMatrix(f32 a_right,f32 a_left,f32 a_top,f32 a_bottom,f32 a_near,f32 a_far);

		/** [�ݒ�]�r���[�B
		*/
		inline void Set_ViewMatrix(const Geometry_Vector3& a_camera_target,const Geometry_Vector3& a_camera_position,const Geometry_Vector3& a_camera_up);

		/** [�ݒ�]�r���[�|�[�g�A
		*/
		inline void Set_ViewPortMatrix(f32 a_width,f32 a_height);

		/** [�ݒ�]�P�ʌ^�B
		*/
		inline Geometry_Matrix_44& operator =(const Geometry_Identity& /*a_identity*/);

		/** [�ݒ�]��Z�B
		*/
		inline Geometry_Matrix_44& operator *=(const Geometry_Matrix_44& a_matrix);

		/** [�쐬]��Z�B
		*/
		inline Geometry_Matrix_44 operator *(const Geometry_Matrix_44& a_matrix) const;

		/** [�ݒ�]��Z�B
		*/
		inline Geometry_Matrix_44& operator *=(f32 a_value);

		/** [�쐬]��Z�B
		*/
		inline Geometry_Matrix_44 operator *(f32 a_value);

		/** [�ݒ�]���Z�B
		*/
		inline Geometry_Matrix_44& operator +=(const Geometry_Matrix_44& a_matrix);

		/** [�쐬]���Z�B
		*/
		inline Geometry_Matrix_44 operator +(const Geometry_Matrix_44& a_matrix) const;
	};

}}
#endif
