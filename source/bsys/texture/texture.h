#pragma once

/**
* Copyright (c) 2017 blueback
* Released under the MIT License
* https://github.com/bluebackblue/brownie/blob/master/LICENSE.txt
* http://bbbproject.sakura.ne.jp/wordpress/mitlicense
* @brief テクスチャー。
*/


/** include
*/
#include "../types/types.h"


/** include
*/
#include "./texture_bmp.h"
#include "./texture_gdiplus.h"
#include "./texture_tga.h"


/** NBsys::NTexture
*/
#if(BSYS_TEXTURE_ENABLE)
namespace NBsys{namespace NTexture
{
	/** TextureType
	*/
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

		/** pixel
		*/
		sharedptr<u8> pixel;

		/** width
		*/
		s32 width;

		/** height
		*/
		s32 height;

		/** pitch
		*/
		s32 pitch;

		/** texturetype
		*/
		TextureType::Id texturetype;

		/** name
		*/
		STLWString name;

	public:

		/** constructor
		*/
		Texture(const sharedptr<u8>& a_pixel,s32 a_width,s32 a_height,s32 a_pitch,TextureType::Id a_texturetype,const STLWString& a_name);

		/** destructor
		*/
		nonvirtual ~Texture();

	public:

		/** GetPixel
		*/
		sharedptr<u8>& GetPixel();

		/** GetPixel
		*/
		const sharedptr<u8>& GetPixel() const;

		/** GetWidth
		*/
		s32 GetWidth() const;

		/** GetHeight
		*/
		s32 GetHeight() const;

		/** TextureType
		*/
		TextureType::Id GetTextureType() const;

		/** GetPitch
		*/
		s32 GetPitch() const;

	};


	/** CreateTexture
	*/
	sharedptr<Texture> CreateTexture(const sharedptr<u8>& a_data,s32 a_size,const STLWString& a_name);


	/** EncodeToJpg
	*/
	std::tuple<sharedptr<u8>,s32> EncodeToJpg(const sharedptr<Texture>& a_texture);


}}
#endif

