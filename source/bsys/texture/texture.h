#pragma once

/**
* Copyright (c) 2017 blueback
* Released under the MIT License
* https://github.com/bluebackblue/brownie/blob/master/LICENSE
* http://bbbproject.sakura.ne.jp/wordpress/mitlicense
* @brief �e�N�X�`���[�B
*/


/** include
*/
#include "../types/types.h"


/** include
*/
#include "./texture_tga.h"
#include "./texture_png.h"
#include "./texture_bmp.h"


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
		s32 pitch;

		TextureType::Id texturetype;
		STLWString name;

	public:
		/** �R���X�g���N�^�B
		*/
		Texture(const sharedptr< u8 >& a_pixel,s32 a_width,s32 a_height,s32 a_pitch,TextureType::Id a_texturetype,const STLWString& a_name);

		/** �f�X�g���N�^�B
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

		/** GetPitch
		*/
		s32 GetPitch();

	};

}}

