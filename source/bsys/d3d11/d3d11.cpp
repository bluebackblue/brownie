

/**
 * Copyright (c) 2017 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief ‚c‚R‚c‚P‚PB
*/


/** include
*/
#include "../types/types.h"


/** include
*/
#include "./d3d11_impl.h"


/** include
*/
#include "./d3d11.h"


/** NBsys::Nd3d11
*/
#if(BSYS_D3D11_ENABLE)
namespace NBsys{namespace ND3d11
{
	/** constructor
	*/
	D3d11::D3d11()
	{
		this->impl.reset(new D3d11_Impl());
	}

	/** GetImpl
	*/
	sharedptr< D3d11_Impl >& D3d11::GetImpl()
	{
		return this->impl;
	}

	/** destructor
	*/
	D3d11::~D3d11()
	{
	}

	/** Create
	*/
	void D3d11::Create(sharedptr< NWindow::Window >& a_window,s32 a_width,s32 a_height)
	{
		return this->impl->Create(a_window,a_width,a_height);
	}

	/** Delete
	*/
	void D3d11::Delete()
	{
		this->impl->Delete();
	}

	/** Clear
	*/
	/*
	void D3d11::Clear()
	{
		this->impl->Clear();
	}
	*/

	/** BeginScene
	*/
	/*
	void D3d11::BeginScene()
	{
		this->impl->BeginScene();
	}
	*/

	/** EndScene
	*/
	/*
	void D3d11::EndScene()
	{
		this->impl->EndScene();
	}
	*/

}}
#endif

