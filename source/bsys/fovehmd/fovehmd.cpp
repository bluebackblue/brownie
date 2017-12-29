﻿

/**
 * Copyright (c) 2016-2017 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE.txt
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief FoveHMD。
*/


/** include
*/
#include <bsys_pch.h>


/** include
*/
#pragma warning(push)
#pragma warning(disable:4464)
#include "../types/types.h"
#pragma warning(pop)


/** include
*/
#include "./fovehmd.h"
#include "./fovehmd_impl.h"


/** warning

4710 : この関数はインライン展開のために選択されましたが、コンパイラはインライン展開を実行しませんでした。

*/
#pragma warning(disable:4710)


/** NBsys::NFovehmd
*/
#if(BSYS_FOVEHMD_ENABLE)
namespace NBsys{namespace NFovehmd
{
	/** constructor
	*/
	Fovehmd::Fovehmd()
	{
		this->impl.reset(new Fovehmd_Impl());
	}


	/** destructor
	*/
	nonvirtual Fovehmd::~Fovehmd()
	{
		this->impl.reset();
	}


	/** GetImpl
	*/
	sharedptr<Fovehmd_Impl> Fovehmd::GetImpl()
	{
		return this->impl;
	}


	/** ResetErrorCode
	*/
	void Fovehmd::ResetErrorCode()
	{
		this->impl->ResetErrorCode();
	}


	/** GetErrorCode
	*/
	ErrorCode Fovehmd::GetErrorCode()
	{
		return this->impl->GetErrorCode();
	}


	/** 接続開始。
	*/
	void Fovehmd::ConnectStart()
	{
		this->impl->ConnectStart();
	}


	/** 接続中。
	*/
	bool Fovehmd::ConnectUpdate()
	{
		return this->impl->ConnectUpdate();
	}


	/** サイズ取得。
	*/
	NGeometry::Geometry_Vector2& Fovehmd::GetSingleEyeResolution()
	{
		return this->impl->GetSingleEyeResolution();
	}


	/** 更新。
 	*/
	void Fovehmd::Update()
	{
		this->impl->Update();
	}


	/** GetLeftProjection
	*/
	NBsys::NGeometry::Geometry_Matrix_44 Fovehmd::GetLeftProjection(f32 a_near,f32 a_far)
	{
		return this->impl->GetLeftProjection(a_near,a_far);
	}


	/** GetRightProjection
	*/
	NBsys::NGeometry::Geometry_Matrix_44 Fovehmd::GetRightProjection(f32 a_near,f32 a_far)
	{
		return this->impl->GetRightProjection(a_near,a_far);
	}


	/** GetLeftEyeTranslate
	*/
	NBsys::NGeometry::Geometry_Matrix_44& Fovehmd::GetLeftEyeTranslate()
	{
		return this->impl->GetLeftEyeTranslate();
	}


	/** GetRightEyeTranslate
	*/
	NBsys::NGeometry::Geometry_Matrix_44& Fovehmd::GetRightEyeTranslate()
	{
		return this->impl->GetRightEyeTranslate();
	}


	/** GetIOD
	*/
	f32 Fovehmd::GetIOD()
	{
		return this->impl->GetIOD();
	}


	/** SetTexture
	*/
	void Fovehmd::SetTexture(void* a_texture_pointer)
	{
		this->impl->SetTexture(a_texture_pointer);
	}


	/** GetCameraPosition
	*/
	NBsys::NGeometry::Geometry_Vector3& Fovehmd::GetCameraPosition()
	{
		return this->impl->GetCameraPosition();
	}


	/** GetCameraQuaternion
	*/
	NBsys::NGeometry::Geometry_Quaternion& Fovehmd::GetCameraQuaternion()
	{
		return this->impl->GetCameraQuaternion();
	}


	/** GetLeftViewProjection
	*/
	NBsys::NGeometry::Geometry_Matrix_44 Fovehmd::GetLeftViewProjection(f32 a_near,f32 a_far,const NGeometry::Geometry_Vector3& a_camera_position)
	{
		return this->impl->GetLeftViewProjection(a_near,a_far,a_camera_position);
	}


	/** GetRightEyeTranslate
	*/
	NBsys::NGeometry::Geometry_Matrix_44 Fovehmd::GetRightViewProjection(f32 a_near,f32 a_far,const NGeometry::Geometry_Vector3& a_camera_position)
	{
		return this->impl->GetRightViewProjection(a_near,a_far,a_camera_position);
	}


}}
#endif

