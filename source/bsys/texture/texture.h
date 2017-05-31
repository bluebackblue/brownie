#pragma once

/**
* Copyright (c) 2017 blueback
* Released under the MIT License
* https://github.com/bluebackblue/brownie/blob/master/LICENSE
* http://bbbproject.sakura.ne.jp/wordpress/mitlicense
* @brief テクスチャー。
*/


/** include
*/
#include "../types/types.h"


/** include
*/
#include "./texture_tga.h"
#include "./texture_png.h"


/** NBsys::NTexture
*/
namespace NBsys{namespace NTexture
{
	struct TextureType
	{
		enum Id
		{
			R8G8B8A8,
			Depth,
		};
	};


	/** Texture
	*/
	class Texture
	{
	private:
		sharedptr< u8 > pixel;
		s32 width;
		s32 height;
		TextureType::Id texturetype;
		STLString name;

	public:
		/** コンストラクタ。
		*/
		Texture(const sharedptr< u8 >& a_pixel,s32 a_width,s32 a_height,TextureType::Id a_texturetype,const STLString& a_name);

		/** デストラクタ。
		*/
		nonvirtual ~Texture();

	public:
		/** GetPixel
		*/
		sharedptr< u8 >& GetPixel();

		/** GetWidth
		*/
		s32 GetWidth() const;

		/** GetHeight
		*/
		s32 GetHeight() const;

		/** TextureType
		*/
		TextureType::Id GetTextureType() const;

	};

}}

