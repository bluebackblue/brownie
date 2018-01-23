#pragma once

/**
 * Copyright (c) 2016-2017 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE.txt
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief Ｄ３Ｄ１１。
*/


/** include
*/
#pragma warning(push)
#pragma warning(disable:4464)
#include "../types/types.h"
#pragma warning(pop)


/** include
*/
#include "./d3d11_type.h"


/** NBsys::ND3d11
*/
#if(BSYS_D3D11_ENABLE)
#pragma warning(push)
#pragma warning(disable:4514)
namespace NBsys{namespace ND3d11
{
	/** D3d11_DisplayMode
	*/
	struct D3d11_DisplayMode
	{
		/** 「DXGI_MODE_DESC」リストのインデックス。
		*/
		s32 list_index;

		/** width
		*/
		f32 width;

		/** height
		*/
		f32 height;

		/** refresh_rate
		*/
		f32 refresh_rate;

		/** constructor
		*/
		D3d11_DisplayMode(s32 a_list_index,f32 a_width,f32 a_height,f32 a_refresh_rate)
			:
			list_index(a_list_index),
			width(a_width),
			height(a_height),
			refresh_rate(a_refresh_rate)
		{
		}

		/** destructor
		*/
		nonvirtual D3d11_DisplayMode()
		{
		}
	};


}}
#pragma warning(pop)
#endif

