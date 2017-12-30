#pragma once

/**
 * Copyright (c) 2016-2017 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE.txt
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief FoveHMD。
*/


/** include
*/
#pragma warning(push)
#pragma warning(disable:4464)
#include "../types/types.h"
#pragma warning(pop)


/** include
*/
#pragma warning(push)
#pragma warning(disable:4464)
#include "../geometry/geometry.h"
#pragma warning(pop)


/** include
*/
#include "./fovehmd_impl_include.h"


/** NBsys::Fovehmd
*/
#if(BSYS_FOVEHMD_ENABLE)
#pragma warning(push)
#pragma warning(disable:4820)
namespace NBsys{namespace NFovehmd
{
	/** Fovehmd_Impl
	*/
	class Fovehmd_Impl
	{
	public:

		/** errorcode
		*/
		ErrorCode errorcode;

		/** headset
		*/
		sharedptr<Fove::IFVRHeadset> headset;

		/** compositor
		*/
		sharedptr<Fove::IFVRCompositor> compositor;

		/** singleeye_resolution
		*/
		NGeometry::Geometry_Vector2 singleeye_resolution;

		/** pose
		*/
		Fove::SFVR_Pose pose;

		/** camera_position
		*/
		NBsys::NGeometry::Geometry_Vector3 camera_position;

		/** camera_quaternion
		*/
		NBsys::NGeometry::Geometry_Quaternion camera_quaternion;

		/** camera_matrix
		*/
		NBsys::NGeometry::Geometry_Matrix_44 camera_matrix;

		/** projection_left
		*/
		NBsys::NGeometry::Geometry_Matrix_44 projection_left;

		/** projection_right
		*/
		NBsys::NGeometry::Geometry_Matrix_44 projection_right;

		/** translate_left
		*/
		NBsys::NGeometry::Geometry_Matrix_44 eye_translate_left;

		/** translate_right
		*/
		NBsys::NGeometry::Geometry_Matrix_44 eye_translate_right;

	public:

		/** constructor
		*/
		Fovehmd_Impl() noexcept;

		/** destructor
		*/
		nonvirtual ~Fovehmd_Impl() noexcept;

	public:

		/** ResetErrorCode
		*/
		void ResetErrorCode();

		/** GetErrorCode
		*/
		ErrorCode GetErrorCode();

		/** 接続開始。
		*/
		void ConnectStart();

		/** 接続中。
		*/
		bool ConnectUpdate();

		/** サイズ取得。
		*/
		NGeometry::Geometry_Vector2& GetSingleEyeResolution(); 

		/** 更新。
 		*/
		void Update();

		/** GetIOD
		*/
		f32 GetIOD();

		/** SetTexture
		*/
		void SetTexture(void* a_texture_pointer);

		/** GetCameraPosition
		*/
		NBsys::NGeometry::Geometry_Vector3& GetCameraPosition();

		/** GetCameraQuaternion
		*/
		NBsys::NGeometry::Geometry_Quaternion& GetCameraQuaternion();

		/** GetLeftProjection
		*/
		NBsys::NGeometry::Geometry_Matrix_44 GetLeftProjection(f32 a_near,f32 a_far);

		/** GetRightProjection
		*/
		NBsys::NGeometry::Geometry_Matrix_44 GetRightProjection(f32 a_near,f32 a_far);

		/** GetLeftEyeTranslate
		*/
		NBsys::NGeometry::Geometry_Matrix_44& GetLeftEyeTranslate();

		/** GetRightEyeTranslate
		*/
		NBsys::NGeometry::Geometry_Matrix_44& GetRightEyeTranslate();

		/** GetLeftViewProjection
		*/
		NBsys::NGeometry::Geometry_Matrix_44 GetLeftViewProjection(f32 a_near,f32 a_far,const NGeometry::Geometry_Vector3& a_camera_position);

		/** GetRightEyeTranslate
		*/
		NBsys::NGeometry::Geometry_Matrix_44 GetRightViewProjection(f32 a_near,f32 a_far,const NGeometry::Geometry_Vector3& a_camera_position);

	};


}}
#pragma warning(pop)
#endif

