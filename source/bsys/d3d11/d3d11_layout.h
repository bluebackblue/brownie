#pragma once

/**
 * Copyright (c) 2017 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief ÇcÇRÇcÇPÇPÅB
*/


/** include
*/
#include "../types/types.h"


/** include
*/
#include "../window/window.h"
#include "../color/color.h"
#include "../file/file.h"


/** NBsys::ND3d11
*/
#if(BSYS_D3D11_ENABLE)
namespace NBsys{namespace ND3d11
{
	/** D3d11_FormatType
	*/
	struct D3d11_FormatType
	{
		enum Id
		{
			R32G32B32_FLOAT,
			R32G32B32A32_FLOAT,
		};
	};

	/** D3d11_Layout
	*/
	struct D3d11_Layout
	{
		std::string				semantic_name;
		int						semantic_index;
		D3d11_FormatType::Id	format;
		int						input_slot;
		int						offset;

		D3d11_Layout(const std::string& a_semantic_name,int a_semantic_index,D3d11_FormatType::Id a_format,int a_input_slot,int a_offset)
			:
			semantic_name(a_semantic_name),
			semantic_index(a_semantic_index),
			format(a_format),
			input_slot(a_input_slot),
			offset(a_offset)
		{
		}
	};
}}
#endif

