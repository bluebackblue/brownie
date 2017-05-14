#pragma once

/**
 * Copyright (c) 2017 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief Ｄ３Ｄ１１。
*/


/** include
*/
#include "../types/types.h"


/** include
*/
#include "../window/window.h"
#include "../color/color.h"


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
		/** 作成。
		*/
		void Render_Create(sharedptr< NWindow::Window >& a_window,s32 a_width,s32 a_height);

		/** 削除。
		*/
		void Render_Delete();

	public:
		/** Render_ViewPort。
		*/
		void Render_ViewPort(f32 a_x,f32 a_y,f32 a_width,f32 a_height);

		/** Render_ClearRenderTargetView
		*/
		void Render_ClearRenderTargetView(NBsys::NColor::Color_F& a_color);

		/** Render_ClearDepthStencilView
		*/
		void Render_ClearDepthStencilView();

		/** Render_CreateBuffer
		*/
		void Render_CreateBuffer();

		/** Render_Present
		*/
		bool Render_Present();



		/** クリア。
		*/
		/*
		void Clear();
		*/

		/** シーン開始。
		*/
		/*
		void BeginScene();
		*/

		/** シーン終了。
		*/
		/*
		void EndScene();
		*/

	};

}}
#endif

