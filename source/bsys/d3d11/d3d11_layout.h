#pragma once

/**
 * Copyright (c) blueback
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
	/** D3d11_Layout
	*/
	struct D3d11_Layout
	{
		/** semantic_name
		*/
		STLString semantic_name;

		/** semantic_index
		*/
		s32 semantic_index;

		/** format
		*/
		D3d11_LayoutFormatType::Id format;

		/** input_slot
		*/
		s32 input_slot;

		/** offset
		*/
		s32 offset;

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
#pragma warning(pop)
#endif

