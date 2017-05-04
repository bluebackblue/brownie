

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
#include "./fovehmd.h"
#include "./fovehmd_impl.h"


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
	sharedptr< Fovehmd_Impl > Fovehmd::GetImpl()
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
}}
#endif

