

/**
 * Copyright (c) blueback
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


/** warning

4710 : この関数はインライン展開のために選択されましたが、コンパイラはインライン展開を実行しませんでした。

*/
#pragma warning(disable:4710)


/** NBsys::NTexture
*/
#if(BSYS_TEXTURE_ENABLE)
#pragma warning(push)
#pragma warning(disable:4514)
namespace NBsys{namespace NTexture
{
	/** コンストラクタ。
	*/
	Texture::Texture(const sharedptr<u8>& a_pixel,const Size2DType<s32>& a_size,s32 a_pitch,TextureType::Id a_texturetype,const STLWString& a_name)
		:
		pixel(a_pixel),
		size(a_size),
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


	/** GetSize
	*/
	const Size2DType<s32>& Texture::GetSize() const
	{
		return this->size;
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


	/** GetName
	*/
	const STLWString& Texture::GetName() const
	{
		return this->name;
	}


	/** ２の乗数の幅を計算する。
	*/
	s32 CalcJustSize(s32 a_size)
	{
		//幅が２の何乗か。
		f32 t_width = NBlib::NMath::log2_f(static_cast<f32>(a_size));
		
		//小数点切り上げ。
		t_width = NBlib::NMath::ceil_f(t_width);

		//幅の再計算。
		s32 t_new_width = static_cast<s32>(NBlib::NMath::pow_f(2,t_width));

		return t_new_width;
	}

	/** CreateTexture
	*/
	sharedptr<Texture> CreateTexture(const sharedptr<u8>& a_data,s32 a_size,const STLWString& a_name)
	{
		sharedptr<Texture> t_ret;

		#if(BSYS_TEXTURE_GDIPLUS_ENABLE)
		{
			t_ret = CreateTexture_GdiPlus(a_data,a_size,a_name);
			if(t_ret){
				return t_ret;
			}
		}
		#endif

		{
			STLWString t_filetype_string = L"";

			s32 t_offset = static_cast<s32>(a_name.size() - 4);
			
			if(t_offset >= 0){
				t_filetype_string = a_name.substr(static_cast<u32>(t_offset),4);
				std::transform(t_filetype_string.begin(),t_filetype_string.end(),t_filetype_string.begin(),::tolower);
			}

			if(t_filetype_string == L".bmp"){
				return CreateTexture_Bmp(a_data,a_size,a_name);
			}else if(t_filetype_string == L".tga"){
				return CreateTexture_Tga(a_data,a_size,a_name);
			}

			return nullptr;
		}
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
		#else
		UNUSED(a_texture);
		#endif

		return t_ret;
	}

	
}}
#pragma warning(pop)
#endif

