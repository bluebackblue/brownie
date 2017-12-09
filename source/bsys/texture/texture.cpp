

/**
* Copyright (c) 2017 blueback
* Released under the MIT License
* https://github.com/bluebackblue/brownie/blob/master/LICENSE
* http://bbbproject.sakura.ne.jp/wordpress/mitlicense
* @brief テクスチャー。
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

	/** CreateTexture
	*/
	sharedptr<Texture> CreateTexture(const sharedptr<u8>& a_data,s32 a_size,const STLWString& a_name)
	{
		#if(BSYS_TEXTURE_GDIPLUS_ENABLE)
		return CreateTexture_GdiPlus(a_data,a_size,a_name);
		#endif

		{
			STLWString t_filetype_string = L"";

			s32 t_offset = static_cast<s32>(a_name.size() - 4);
			
			if(t_offset >= 0){
				t_filetype_string = a_name.substr(t_offset,4);
				std::transform(t_filetype_string.begin(),t_filetype_string.end(),t_filetype_string.begin(),::tolower);
			}

			if(t_filetype_string == L".bmp"){
				return CreateTexture_Bmp(a_data,a_size,a_name);
			}else if(t_filetype_string == L".tga"){
				return CreateTexture_Tga(a_data,a_size,a_name);
			}
		}

		return nullptr;
	}

}}

