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
			/** float2
			*/
			R32G32_FLOAT,

			/** float3 
			*/
			R32G32B32_FLOAT,

			/** float4
			*/
			R32G32B32A32_FLOAT,

			/** u32
			*/
			R8G8B8A8_UINT,

			/** u8
			*/
			R8_UINT
		};
	};

	/** D3d11_TopologyType
	*/
	struct D3d11_TopologyType
	{
		enum Id
		{
			/**
			*/
			PointList,

			/**
			*/
			LineList,

			/**
			*/
			LineStrip,

			/**
			*/
			TriangleList,

			/**
			*/
			TriangleStrip,
		};
	};

	/** D3d11_CullType
	*/
	struct D3d11_CullType
	{
		enum Id
		{
			/** 両面描画。
			*/
			None,

			/** 前向きを描画しない。
			*/
			Front,

			/** 後ろ向きを描画しない。
			*/
			Back,
		};
	};

	/** D3d11_FontTextureType
	*/
	#if(BSYS_FONT_ENABLE)
	struct D3d11_FontTextureType
	{
		enum Id
		{
			//小フォント。
			SFont = 0,

			//中フォント
			MFont,

			//大フォント。
			LFont,

			//特大フォント。
			ExFont,

			Max,
		};
	};
	#endif

}}
#endif


