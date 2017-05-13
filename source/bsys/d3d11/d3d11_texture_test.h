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


/** include
*/
#include "../../alib/include_windows.h"


/** include
*/
#if defined(PLATFORM_WIN)

	#if(ASYS_D3D11_ENABLE)

		#include <d3d11.h>

	#endif

#endif


/** NAsys::ND3d11
*/
#if(ASYS_D3D11_ENABLE)
namespace NAsys{namespace ND3d11
{

	/** D3d11_Texture
	*/
	struct D3d11_Texture
	{
		/** muid
		*/
		Muid muid;

		/** texture
		*/
		ID3D11Texture2D* texture;

		/** constructor
		*/
		D3d11_Texture(Muid& a_muid,ID3D11Texture2D* a_texture)
			:
			muid(a_muid),
			texture(a_texture)
		{
		}

		/** destructor
		*/
		nonvirtual ~D3d11_Texture()
		{
		}
	};

}}
#endif

