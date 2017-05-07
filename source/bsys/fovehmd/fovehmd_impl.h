#pragma once

/**
 * Copyright (c) 2016 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief FoveHMD�B
*/


/** include
*/
#include "../types/types.h"


/** include
*/
#include "./fovehmd_impl_include.h"
#include "../geometry/geometry.h"


/** NBsys::Fovehmd
*/
#if(BSYS_FOVEHMD_ENABLE)
namespace NBsys{namespace NFovehmd
{
	/** Fovehmd_Impl
	*/
	class Fovehmd_Impl
	{
	public:
		/** constructor
		*/
		Fovehmd_Impl() throw();

		/** destructor
		*/
		nonvirtual ~Fovehmd_Impl() throw();

	public:
		/** errorcode
		*/
		ErrorCode errorcode;

		/** headset
		*/
		sharedptr< Fove::IFVRHeadset > headset;

		/** compositor
		*/
		sharedptr< Fove::IFVRCompositor > compositor;

		/** singleeye_resolution
		*/
		NGeometry::Geometry_Vector2 singleeye_resolution;

		/** pose
		*/
		Fove::SFVR_Pose pose;

		/** camera_position
		*/
		NBsys::NGeometry::Geometry_Matrix_44 camera_position;

		/** camera_quaternion
		*/
		NBsys::NGeometry::Geometry_Quaternion camera_quaternion;

	public:
		/** ResetErrorCode
		*/
		void ResetErrorCode();

		/** GetErrorCode
		*/
		ErrorCode GetErrorCode();

		/** �ڑ��J�n�B
		*/
		void ConnectStart();

		/** �ڑ����B
		*/
		bool ConnectUpdate();

		/** �T�C�Y�擾�B
		*/
		NGeometry::Geometry_Vector2& GetSingleEyeResolution(); 

		/** �X�V�B
 		*/
		void Update();

		/** GetLeftEyeProjection
		*/
		NBsys::NGeometry::Geometry_Matrix_44 GetLeftEyeProjection();

		/** GetRightEyeProjection
		*/
		NBsys::NGeometry::Geometry_Matrix_44 GetRightEyeProjection();

		/** GetIOD
		*/
		f32 GetIOD();

		/** SetTexture
		*/
		void SetTexture(void* a_texture_pointer);

		/** GetCameraPosition
		*/
		NBsys::NGeometry::Geometry_Matrix_44& GetCameraPosition();

		/** GetCameraQuaternion
		*/
		NBsys::NGeometry::Geometry_Quaternion& GetCameraQuaternion();

	};
}}
#endif

