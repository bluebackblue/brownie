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

	/** D3d11_VertexShader
	*/
	struct D3d11_VertexShader
	{
		/** muid
		*/
		Muid muid;

		/** vertexshader
		*/
		//IDirect3DVertexShader11* vertexshader;

		/** vertexdeclaration
		*/
		//IDirect3DVertexDeclaration11* vertexdeclaration;

		/** constructor
		*/
		D3d11_VertexShader(Muid& a_muid/*,IDirect3DVertexShader11* a_vertexshader,IDirect3DVertexDeclaration11* a_vertexdeclaration*/)
			:
			muid(a_muid)
			//vertexshader(a_vertexshader),
			//vertexdeclaration(a_vertexdeclaration)
		{
		}

		/** destructor
		*/
		nonvirtual ~D3d11_VertexShader()
		{
		}
	};

}}
#endif

