#pragma once

/**
 * Copyright (c) 2017 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief �c�R�c�P�P�B
*/


/** include
*/
#include "../types/types.h"


/** include
*/
#include "../window/window.h"


/** NBsys::ND3d11
*/
#if(BSYS_D3D11_ENABLE)
namespace NBsys{namespace ND3d11
{
	/** D3d11_Impl
	*/
	class D3d11_Impl;

	/** D3d11
	*/
	class D3d11
	{
	private:
		/** impl
		*/
		sharedptr< D3d11_Impl > impl;

	public:
		/** GetImpl
		*/
		sharedptr< D3d11_Impl >& GetImpl();

	public:
		/** constructor
		*/
		D3d11();

		/** destructor
		*/
		nonvirtual ~D3d11();

	public:
		/** �쐬�B
		*/
		void Create(sharedptr< NWindow::Window >& a_window,s32 a_width,s32 a_height);

		/** �폜�B
		*/
		void Delete();

		/** �N���A�B
		*/
		/*
		void Clear();
		*/

		/** �V�[���J�n�B
		*/
		/*
		void BeginScene();
		*/

		/** �V�[���I���B
		*/
		/*
		void EndScene();
		*/

	};

}}
#endif

