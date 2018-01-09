#pragma once

/**
 * Copyright (c) 2016-2018 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE.txt
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief Ｄ３Ｄ１１。
*/


/** include
*/
#pragma warning(push)
#pragma warning(disable:4464)
#include "../types/types.h"
#pragma warning(pop)


/** include
*/
#pragma warning(push)
#pragma warning(disable:4464)
#include "../font/font.h"
#include "../texture/texture.h"
#include "../vertex/vertex.h"
#pragma warning(pop)


/** include
*/
#include "./d3d11_impl.h"


/** NBsys::NOpengl
*/
#if(BSYS_D3D11_ENABLE)
#pragma warning(push)
#pragma warning(disable:4710 4820)
namespace NBsys{namespace ND3d11
{
	/** D3d11_Impl_Font
	*/
	#if(BSYS_FONT_ENABLE)
	class D3d11_Impl_Font
	{
	private:

		/** Item
		*/
		struct Item
		{
			/** 文字コード。
			*/
			wchar code;

			/** 描画が完了するまで書き換えを禁止する。
			*/
			bool lock;

			/** fontstate
			*/
			NBsys::NFont::Font_State fontstate;

			/** constructor
			*/
			Item(wchar a_code)
				:
				code(a_code),
				lock(false),
				fontstate()
			{
			}

			/** destructor
			*/
			nonvirtual ~Item()
			{
			}
		};

	private:

		/** d3d11_impl
		*/
		D3d11_Impl& d3d11_impl;

		/** font
		*/
		sharedptr<NBsys::NFont::Font> font;

		/** fonttexture_type
		*/
		D3d11_FontTextureType::Id fonttexture_type;

		/** texture_size
		*/
		Size2DType<s32> texture_size;

		/** texture
		*/
		sharedptr<NBsys::NTexture::Texture> texture;

		/** textureid
		*/
		s32 textureid;

		/** list
		*/
		STLVector<Item>::Type list;

		/** maplist

		wchar	: 文字コード。
		s32		: リストのインデックス。

		*/
		STLMap<wchar,u32>::Type maplist;

	public:

		/** constructor
		*/
		D3d11_Impl_Font(D3d11_Impl& a_opengl_impl,const sharedptr<NBsys::NFont::Font>& a_font,s32 a_texture_width,const STLWString& a_name,D3d11_FontTextureType::Id a_fonttexture_type);

		/** destructor
		*/
		nonvirtual ~D3d11_Impl_Font();

	private:

		/** copy constructor禁止。
		*/
		D3d11_Impl_Font(const D3d11_Impl_Font& a_this) = delete;

		/** コピー禁止。
		*/
		void operator =(const D3d11_Impl_Font& a_this) = delete;

	private:

		/** 書き換え可能位置の検索。
		*/
		s32 FindNoLockFontIndex();

	public:

		/** ResetLock
		*/
		void ResetLock();

		/** GetTexture
		*/
		s32 GetTexture();
		
		/** 文字列から必要な文字を抽出。
		*/
		bool PreUpdateFontTexture(const STLWString& a_string);

		/** テクスチャーに書き込む。
		*/
		void WriteFontTexture();
		
		/** バーテックス作成。
		*/
		void MakeFontVertex(const STLWString& a_string,sharedptr<NBsys::NVertex::Vertex<NBsys::NVertex::Vertex_Data_Pos3Uv2Color4TextureIndex4>>& a_vertex,const Rect2DType_R<f32>& a_viewrect,NBsys::NFont::Font_Alignment::Id a_alignment,f32 a_z,const Size2DType<f32>& a_view_size,const NBsys::NColor::Color_F& a_color);

	};
	#endif


}}
#pragma warning(pop)
#endif

