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

	/** D3d11_TextureAddressType
	*/
	struct D3d11_TextureAddressType
	{
		enum Id
		{
			/**
			
			(u,v)整数区切りごとにテクスチャーを繰り返します。
			たとえば、uの値が0から3までの場合、テクスチャーが3回繰り返されます。
			
			*/
			Wrap,

			/** Mirror

			(u,v)整数区切りごとにテクスチャーを反転させます。
			たとえば、uの値が0から1までの場合、テクスチャーの処理が通常どおりに行われますが、
			1から2までの場合は反転表示(ミラー化)され、2から3までの場合は再び通常の処理が行われます。
			これ以降も、このパターンで処理されます。

			*/
			Mirror,

			/** Clamp

			範囲[0.0,1.0]の外にあるテクスチャー座標には、
			それぞれ0.0または1.0のテクスチャーカラーが設定されます。

			*/
			Clamp,

			/** Border

			範囲[0.0,1.0]の外にあるテクスチャー座標には、
			D3D11_SAMPLER_DESCまたはHLSLコードで指定した境界色が設定されます。

			*/
			Border,

			/** Mirror_Once

			D3D11_TEXTURE_ADDRESS_MIRRORおよびD3D11_TEXTURE_ADDRESS_CLAMPと似ています。
			テクスチャー座標の絶対値を取得し(0を中心としたミラーリング)、最大値に固定します。

			*/
			Mirror_Once,
		};
	};

	/** D3d11_FilterType
	*/
	struct D3d11_FilterType
	{
		enum Id
		{
			/** MIN=POINT MAG=POINT MIP=POINT
 			*/
			MIN_MAG_MIP_POINT,

			/** MIN=LINEAR MAG=LINEAR MIP=LINEAR
			*/
			MIN_MAG_MIP_LINEAR,
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


