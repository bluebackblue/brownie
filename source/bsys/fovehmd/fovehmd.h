#pragma once

/**
 * Copyright (c) 2016 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief FoveHMD。
*/


/** include
*/
#include "../types/types.h"


/** include
*/
#include "../geometry/geometry.h"


/** NBsys::NFovehmd
*/
#if(BSYS_FOVEHMD_ENABLE)
namespace NBsys{namespace NFovehmd
{
	/** Fovehmd_Impl
	*/
	class Fovehmd_Impl;


	/** Fovehmd
	*/
	class Fovehmd
	{
	private:

		/** impl
		*/
		sharedptr<Fovehmd_Impl> impl;

	public:

		/** GetImpl
		*/
		sharedptr<Fovehmd_Impl> GetImpl();

	public:

		/** constructor
		*/
		Fovehmd();

		/** destructor
		*/
		nonvirtual ~Fovehmd();

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

		/** GetLeftViewProjection
		*/
		NBsys::NGeometry::Geometry_Matrix_44 GetLeftViewProjection(f32 a_near,f32 a_far,const NGeometry::Geometry_Vector3& a_camera_position);

		/** GetRightEyeTranslate
		*/
		NBsys::NGeometry::Geometry_Matrix_44 GetRightViewProjection(f32 a_near,f32 a_far,const NGeometry::Geometry_Vector3& a_camera_position);

	};


}}
#endif

