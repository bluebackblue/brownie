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
		/** コンストラクタ。
		*/
		inline Geometry_Matrix_44();

		/** コンストラクタ。
		*/
		inline Geometry_Matrix_44(
			f32 a_ax_x,f32 a_ax_y,f32 a_ax_z,f32 a_ax_w,
			f32 a_ay_x,f32 a_ay_y,f32 a_ay_z,f32 a_ay_w,
			f32 a_az_x,f32 a_az_y,f32 a_az_z,f32 a_az_w,
			f32 a_tr_x,f32 a_tr_y,f32 a_tr_z,f32 a_tr_w
		);

		/** コンストラクタ。
		*/
		inline Geometry_Matrix_44(const Geometry_Identity& /*a_identity*/);

		/** コンストラクタ。
		*/
		inline Geometry_Matrix_44(const Geometry_Quaternion& a_quaternion);

		/** デストラクタ。
		*/
		inline ~Geometry_Matrix_44();

		/** [static]Identity。
		*/
		static inline const Geometry_Matrix_44& Identity();

		/** [設定]Identity。
		*/
		inline void Set_Identity();

		/** [設定]。
		*/
		inline void Set(
			f32 a_ax_x,f32 a_ax_y,f32 a_ax_z,f32 a_ax_w,
			f32 a_ay_x,f32 a_ay_y,f32 a_ay_z,f32 a_ay_w,
			f32 a_az_x,f32 a_az_y,f32 a_az_z,f32 a_az_w,
			f32 a_tr_x,f32 a_tr_y,f32 a_tr_z,f32 a_tr_w
		);

		/** [作成]Ｘ軸。
		*/
		inline Geometry_Vector3 Make_AxisX() const;

		/** [作成]Ｙ軸。
		*/
		inline Geometry_Vector3 Make_AxisY() const;

		/** [作成]Ｚ軸。
		*/
		inline Geometry_Vector3 Make_AxisZ() const;

		/** [設定]Ｘ軸。
		*/
		inline void Set_AxisX(const Geometry_Vector3& a_vector);

		/** [設定]Ｙ軸。
		*/
		inline void Set_AxisY(const Geometry_Vector3& a_vector);

		/** [設定]Ｚ軸。
		*/
		inline void Set_AxisZ(const Geometry_Vector3& a_vector);

		/** [設定]平行移動。
		*/
		inline void Set_Translate(f32 a_x,f32 a_y,f32 a_z);

		/** [設定]平行移動。
		*/
		inline void Set_Translate(const Geometry_Vector3& a_vector);

		/** [static][作成]平行移動。
		*/
		static inline Geometry_Matrix_44 Make_Translate(f32 a_x,f32 a_y,f32 a_z);

		/** [作成]平行移動。
		*/
		inline Geometry_Vector3 Make_Translate_Vector() const;

		/** [作成]平行移動。
		*/
		inline Geometry_Matrix_44 Make_Translate() const;

		/** [設定]スケール。
		*/
		inline void Calc_Scale(f32 a_x,f32 a_y,f32 a_z);

		/** [設定]スケール。
		*/
		inline void Calc_Scale(const Geometry_Vector3& a_vector);

		/** [作成]各軸のスケール。
		*/
		inline Geometry_Vector3 Make_Scale_Vector() const;

		/** [static][作成]回転行列。
		*/
		static inline Geometry_Matrix_44 Make_RotationXYZ(f32 a_rad_x,f32 a_rad_y,f32 a_rad_z);

		/** [作成]回転行列。
		*/
		inline Geometry_Matrix_44 Make_Rotation() const;

		/** [static][作成]回転行列。
		*/
		static inline Geometry_Matrix_44 Make_RotationX(f32 a_rad);

		/** [static][作成]回転行列。
		*/
		static inline Geometry_Matrix_44 Make_RotationY(f32 a_rad);

		/** [static][作成]回転行列。
		*/
		static inline Geometry_Matrix_44 Make_RotationZ(f32 a_rad);

		/** [設定]回転行列。
		*/
		inline void Set_RotationX(f32 a_rad);

		/** [設定]回転行列。
		*/
		inline void Set_RotationY(f32 a_rad);

		/** [設定]回転行列。
		*/
		inline void Set_RotationZ(f32 a_rad);

		/** [設定]回転行列。
		*/
		inline void Set_RotationVector(const Geometry_Vector3& a_vector,f32 a_rad);

		/** [作成]逆行列。
		*/
		inline Geometry_Matrix_44 Make_Inverse() const;

		/** [設定]逆行列。
		*/
		inline void Set_Inverse();

		/** [設定]Set_Lookat。
		*/
		inline void Set_Lookat(const Geometry_Vector3& a_position,const Geometry_Vector3& a_target,const Geometry_Vector3& a_up);

		/** [設定]Set_LookatLimit。
		*/
		inline void Set_LookatLimit(const Geometry_Vector3& a_position,const Geometry_Vector3& a_target,const Geometry_Vector3& a_up);

		/** [作成]クオータニオン。
		*/
		inline Geometry_Quaternion Make_Quaternion() const;

		/** [作成]クオータニオン。
		*/
		inline Geometry_Quaternion Make_Quaternion_Safe() const;

		/** [設定]クオータニオン。
		*/
		inline void Set_Quaternion(const Geometry_Quaternion& a_quaternion);

		/** [設定]プロジェクション。透視投影。
		*/
		inline void Set_PerspectiveProjectionMatrix(f32 a_width,f32 a_height,f32 a_fov_deg,f32 a_near,f32 a_far);

		/** [設定]プロジェクション。正射影。
		*/
		inline void Set_OrthographicProjectionMatrix(f32 a_right,f32 a_left,f32 a_top,f32 a_bottom,f32 a_near,f32 a_far);

		/** [設定]ビュー。
		*/
		inline void Set_ViewMatrix(const Geometry_Vector3& a_camera_target,const Geometry_Vector3& a_camera_position,const Geometry_Vector3& a_camera_up);

		/** [設定]ビューポート、
		*/
		inline void Set_ViewPortMatrix(f32 a_width,f32 a_height);

		/** [設定]単位型。
		*/
		inline Geometry_Matrix_44& operator =(const Geometry_Identity& /*a_identity*/);

		/** [設定]乗算。
		*/
		inline Geometry_Matrix_44& operator *=(const Geometry_Matrix_44& a_matrix);

		/** [作成]乗算。
		*/
		inline Geometry_Matrix_44 operator *(const Geometry_Matrix_44& a_matrix) const;

		/** [設定]乗算。
		*/
		inline Geometry_Matrix_44& operator *=(f32 a_value);

		/** [作成]乗算。
		*/
		inline Geometry_Matrix_44 operator *(f32 a_value);

		/** [設定]加算。
		*/
		inline Geometry_Matrix_44& operator +=(const Geometry_Matrix_44& a_matrix);

		/** [作成]加算。
		*/
		inline Geometry_Matrix_44 operator +(const Geometry_Matrix_44& a_matrix) const;
	};

}}
#endif
