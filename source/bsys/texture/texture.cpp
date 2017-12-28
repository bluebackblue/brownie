

/**
 * Copyright (c) 2016-2017 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE.txt
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief テクスチャー。
*/


/** include
*/
#include <bsys_pch.h>


/** include
*/
#pragma warning(push)
#pragma warning(disable:4464)
#include "../types/types.h"
#pragma warning(pop)


/** include
*/
#include "./texture.h"


/** NBsys::NTexture
*/
#if(BSYS_TEXTURE_ENABLE)
namespace NBsys{namespace NTexture
{
	/** コンストラクタ。
	*/
	Texture::Texture(const sharedptr<u8>& a_pixel,s32 a_width,s32 a_height,s32 a_pitch,TextureType::Id a_texturetype,const STLWString& a_name)
		:
		pixel(a_pixel),
		width(a_width),
		height(a_height),
		pitch(a_pitch),
		texturetype(a_texturetype),
		name(a_name)
	{
	}


	/** デストラクタ。
	*/
	Texture::~Texture()
	{
	}


	/** GetPixel
	*/
	sharedptr<u8>& Texture::GetPixel()
	{
		return this->pixel;
	}


	/** GetPixel
	*/
	const sharedptr<u8>& Texture::GetPixel() const
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
	s32 Texture::GetPitch() const
	{
		return this->pitch;
	}


	/** CreateTexture
	*/
	sharedptr<Texture> CreateTexture(const sharedptr<u8>& a_data,s32 a_size,const STLWString& a_name)
	{
		#if(BSYS_TEXTURE_GDIPLUS_ENABLE)
		{
			return CreateTexture_GdiPlus(a_data,a_size,a_name);
		}
		#else
		{
			STLWString t_filetype_string = L"";

			s32 t_offset = static_cast<s32>(a_name.size() - 4);
			
			if(t_offset >= 0){
				t_filetype_string = a_name.substr(static_cast<u32>(t_offset),4);
				std::transform(t_filetype_string.cbegin(),t_filetype_string.cend(),t_filetype_string.cbegin(),::tolower);
			}

			if(t_filetype_string == L".bmp"){
				return CreateTexture_Bmp(a_data,a_size,a_name);
			}else if(t_filetype_string == L".tga"){
				return CreateTexture_Tga(a_data,a_size,a_name);
			}

			return nullptr;
		}
		#endif
	}


	/** EncodeToJpg
	*/
	std::tuple<sharedptr<u8>,s32> EncodeToJpg(const sharedptr<Texture>& a_texture)
	{
		std::tuple<sharedptr<u8>,s32> t_ret;

		#if(BSYS_TEXTURE_GDIPLUS_ENABLE)
		t_ret = EncodeToJpg_GdiPlus(a_texture);
		
		if((std::get<0>(t_ret).get() != nullptr)&&(std::get<1>(t_ret) > 0)){
			return t_ret;
		}
		#endif

		return t_ret;
	}

	
}}
#endif

