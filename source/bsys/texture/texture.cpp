

/**
* Copyright (c) 2017 blueback
* Released under the MIT License
* https://github.com/bluebackblue/brownie/blob/master/LICENSE
* http://bbbproject.sakura.ne.jp/wordpress/mitlicense
* @brief �e�N�X�`���[�B
*/


/** include
*/
#include <bsys_pch.h>


/** include
*/
#include "../types/types.h"


/** include
*/
#include "./texture.h"


/** NBsys::NTexture
*/
namespace NBsys{namespace NTexture
{

	/** �R���X�g���N�^�B
	*/
	Texture::Texture(const sharedptr< u8 >& a_pixel,s32 a_width,s32 a_height,s32 a_pitch,TextureType::Id a_texturetype,const STLWString& a_name)
		:
		pixel(a_pixel),
		width(a_width),
		height(a_height),
		pitch(a_pitch),
		texturetype(a_texturetype),
		name(a_name)
	{
	}

	/** �f�X�g���N�^�B
	*/
	Texture::~Texture()
	{
	}

	/** GetPixel
	*/
	sharedptr< u8 >& Texture::GetPixel()
	{
		return this->pixel;
	}

	/** GetWidth
	*/
	s32 Texture::GetWidth() const
	{
		return this->width;
	}

	/** GetHeight
	*/
	s32 Texture::GetHeight() const
	{
		return this->height;
	}

	/** TextureType
	*/
	TextureType::Id Texture::GetTextureType() const
	{
		return this->texturetype;
	}

	/** GetPitch
	*/
	s32 Texture::GetPitch()
	{
		return this->pitch;
	}

}}

