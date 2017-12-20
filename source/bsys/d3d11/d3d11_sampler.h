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


/**
*/
#include "./d3d11_type.h"


/** NBsys::ND3d11
*/
#if(BSYS_D3D11_ENABLE)
namespace NBsys{namespace ND3d11
{
	/** D3d11_Sampler
	*/
	struct D3d11_Sampler
	{
		D3d11_TextureAddressType::Id textureaddrestype_u;
		D3d11_TextureAddressType::Id textureaddrestype_v;
		D3d11_TextureAddressType::Id textureaddrestype_w;

		D3d11_FilterType::Id filtertype;

		/** constructor
		*/
		D3d11_Sampler()
			:
			textureaddrestype_u(D3d11_TextureAddressType::Clamp),
			textureaddrestype_v(D3d11_TextureAddressType::Clamp),
			textureaddrestype_w(D3d11_TextureAddressType::Clamp),
			filtertype(D3d11_FilterType::MIN_MAG_MIP_LINEAR)
		{
		}

		/** destructor
		*/
		nonvirtual ~D3d11_Sampler()
		{
		}
	};
}}
#endif

