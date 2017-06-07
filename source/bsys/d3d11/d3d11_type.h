#pragma once

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


/** NBsys::ND3d11
*/
#if(BSYS_D3D11_ENABLE)
namespace NBsys{namespace ND3d11
{
	/** D3d11_LayoutFormatType
	*/
	struct D3d11_LayoutFormatType
	{
		enum Id
		{
			/** float3 
			*/
			R32G32B32_FLOAT,

			/** float4
			*/
			R32G32B32A32_FLOAT,

			/** float2
			*/
			R32G32_FLOAT
		};
	};

	/** D3d11_CullType
	*/
	struct D3d11_CullType
	{
		enum Id
		{
			/** —¼–Ê•`‰æB
			*/
			NONE,

			/** ‘OŒü‚«‚ğ•`‰æ‚µ‚È‚¢B
			*/
			FRONT,

			/** Œã‚ëŒü‚«‚ğ•`‰æ‚µ‚È‚¢B
			*/
			BACK,
		};
	};

}}
#endif


