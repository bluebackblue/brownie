#pragma once

/**
 * Copyright (c) 2017 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief OpenGL。
*/


/** include
*/
#include "../types/types.h"


/** NBsys::NOpengl
*/
#if(BSYS_OPENGL_ENABLE)
namespace NBsys{namespace NOpengl
{

	/** Opengl_ShaderType
	*/
	struct Opengl_ShaderType
	{
		enum Id
		{
			/** バーテックス。
			*/
			Vertex,

			/** フラグメント。
			*/
			Fragment
		};
	};

	/**  Opengl_ShaderValueType
	*/
	struct Opengl_ShaderValueType
	{
		enum Id
		{
			Texture0,
			Texture1,
			Texture2,
			Texture3,
			Texture4,
			Texture5,
			Texture6,
			Texture7,
			Texture8,
			Texture9,
			Texture10,
			Texture11,
			Texture12,
			Texture13,
			Texture14,
			Texture15,
			Texture16,
			Texture17,
			Texture18,
			Texture19,
			Texture20,
			Texture21,
			Texture22,
			Texture23,
			Texture24,
			Texture25,
			Texture26,
			Texture27,
			Texture28,
			Texture29,
			Texture30,
			Texture31,

			/** Float。
			*/
			Float,

			/** Float2
			*/
			Float2,
			Vector2,
			
			/** Float3
			*/
			Float3,
			Vector3,

			/** Float4
			*/
			Float4,
			Vector4,

			/** Float16
			*/
			Float16,
			Matrix,

			/** 頂点情報s32 => シェーダーパラメータf32。
			*/
			IntToFloat,

			/** 頂点情報s32 => シェーダーパラメータf32。
			*/
			Int2ToFloat2,

			/** 頂点情報s32 => シェーダーパラメータf32。
			*/
			Int3ToFloat3,

			/** 頂点情報s32 => シェーダーパラメータf32。
			*/
			Int4ToFloat4,

		};
	};

	/** Opengl_ShadeModelType
	*/
	struct Opengl_ShadeModelType
	{
		enum Id
		{
			/**

			スムースシューティングの場合、ポリゴンの陰影が滑らかに表現され描画される。

			*/
			Smooth,

			/**

			フラットシューティングに設定した場合、面ごとの明るさが一定の状態として描画される。
			高速描画が可能。

			*/
			Flat
		};
	};

}}
#endif

