﻿#pragma once

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
#include "./d3d11_type.h"


/** NBsys::ND3d11
*/
#if(BSYS_D3D11_ENABLE)
namespace NBsys{namespace ND3d11
{
	/** D3d11_Layout
	*/
	struct D3d11_Layout
	{
		STLString						semantic_name;
		s32								semantic_index;
		D3d11_LayoutFormatType::Id		format;
		s32								input_slot;
		s32								offset;

		/** constructor
		*/
		D3d11_Layout(const STLString& a_semantic_name,s32 a_semantic_index,D3d11_LayoutFormatType::Id a_format,s32 a_input_slot,s32 a_offset)
			:
			semantic_name(a_semantic_name),
			semantic_index(a_semantic_index),
			format(a_format),
			input_slot(a_input_slot),
			offset(a_offset)
		{
		}

		/** destructor
		*/
		nonvirtual D3d11_Layout()
		{
		}
	};


}}
#endif

