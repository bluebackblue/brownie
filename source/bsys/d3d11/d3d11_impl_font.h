﻿#pragma once

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


/** include
*/
#include "../font/font.h"
#include "../texture/texture.h"
#include "../vertex/vertex.h"


/** include
*/
#include "./d3d11_impl.h"


/** NBsys::NOpengl
*/
#if(BSYS_D3D11_ENABLE)
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
			wchar code;
			bool lock;
			NBsys::NFont::Font_State fontstate;

			Item(wchar a_code)
				:
				code(a_code),
				lock(false)
			{
			}
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

		/** texturewidth
		*/
		s32 texturewidth;

		/** textureheight
		*/
		s32 textureheight;
	
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

		wchar	: code
		s32		: fontindex

		*/
		STLMap<wchar,s32>::Type maplist;

	public:
		/** constructor
		*/
		D3d11_Impl_Font(D3d11_Impl& a_opengl_impl,const sharedptr<NBsys::NFont::Font>& a_font,s32 a_texture_width,const STLWString& a_name,D3d11_FontTextureType::Id a_fonttexture_type)
			:
			d3d11_impl(a_opengl_impl),
			font(a_font),
			fonttexture_type(a_fonttexture_type)
		{
			this->texturewidth = static_cast<s32>(NBlib::Math::powf(2,NBlib::Math::ceilf(NBlib::Math::log2f(static_cast<f32>(a_texture_width)))));

			s32 t_drawtypemax = 0;

			switch(this->fonttexture_type){
			case NBsys::ND3d11::D3d11_FontTextureType::SFont:
				{
					t_drawtypemax = BSYS_D3D11_FONT_DRAWTYPEMAX_S;
				}break;
			case NBsys::ND3d11::D3d11_FontTextureType::MFont:
				{
					t_drawtypemax = BSYS_D3D11_FONT_DRAWTYPEMAX_M;
				}break;
			case NBsys::ND3d11::D3d11_FontTextureType::LFont:
				{
					t_drawtypemax = BSYS_D3D11_FONT_DRAWTYPEMAX_L;
				}break;
			case NBsys::ND3d11::D3d11_FontTextureType::ExFont:
				{
					t_drawtypemax = BSYS_D3D11_FONT_DRAWTYPEMAX_EX;
				}break;
			default:
				{
					ASSERT(0);
				}break;
			}

			this->textureheight = static_cast<s32>(NBlib::Math::powf(2,NBlib::Math::ceilf(NBlib::Math::log2f(static_cast<f32>(this->texturewidth * t_drawtypemax)))));

			sharedptr<u8> t_pixel(new u8[this->texturewidth * this->textureheight * 4]);

			this->texture.reset(new NBsys::NTexture::Texture(
				t_pixel,
				this->texturewidth,
				this->textureheight,
				this->texturewidth * 4,
				NBsys::NTexture::TextureType::R8G8B8A8,
				a_name
				)
			);

			this->textureid = this->d3d11_impl.CreateTexture(this->texture,true);

			for(s32 ii=0;ii<t_drawtypemax;ii++){
				this->list.push_back(Item(nullwchar));
			}
		}

		/** destructor
		*/
		nonvirtual ~D3d11_Impl_Font()
		{
		}

	private:

		/** 書き換え可能位置の検索。
		*/
		s32 FindNoLockFontIndex()
		{
			for(s32 ii=0;ii<static_cast<s32>(this->list.size());ii++){
				if((this->list[ii].lock == false)&&(this->list[ii].code == nullchar)){
					return ii;
				}
			}

			for(s32 ii=0;ii<static_cast<s32>(this->list.size());ii++){
				if(this->list[ii].lock == false){
					return ii;
				}
			}

			return -1;
		}

	public:

		/** ResetLock
		*/
		void ResetLock()
		{
			for(s32 ii=0;ii<static_cast<s32>(this->list.size());ii++){
				this->list[ii].lock = false;
			}
		}

		/** GetTexture
		*/
		s32 GetTexture()
		{
			return this->textureid;
		}
		
		/** PreUpdateFontTexture
		*/
		bool PreUpdateFontTexture(const STLWString& a_string)
		{
			bool t_change = false;

			for(s32 ii=0;ii<static_cast<s32>(a_string.length());ii++){

				wchar t_code = a_string[ii];

				if(t_code != nullwchar){
					s32 t_font_index = 0;

					STLMap<wchar,s32>::iterator t_it = this->maplist.find(t_code);
					if(t_it != this->maplist.end()){
						//すでに作成済み。
						t_font_index = t_it->second;
						ASSERT(t_font_index >= 0);
					}else{
						//書き換え可能位置の検索。
						t_font_index = this->FindNoLockFontIndex();

						if(t_font_index >= 0){
							wchar t_old_code = this->list[t_font_index].code;
							if(t_old_code != nullwchar){
								//旧コードを削除。
								STLMap<wchar,s32>::iterator t_old_it = this->maplist.find(t_old_code);
								if(t_old_it != this->maplist.end()){
									this->maplist.erase(t_old_it);
								}
							}

							#if defined(ROM_DEEPDEBUG)
							{
								wchar t_wchar[2] = {t_code,nullwchar};
								TAGLOG("UpdateFontTexture",L"%s",t_wchar);
							}
							#endif

							//テクスチャーに書き込み。
							NBsys::NFont::Font_State t_font_state = this->font->GetPixel_R8G8B8A8(this->texture->GetPixel(),t_font_index * (this->texturewidth * this->texturewidth * 4),this->texturewidth,this->texturewidth,t_code);
							t_change = true;

							//登録。
							this->list[t_font_index].code = t_code;
							this->list[t_font_index].lock = true;
							this->list[t_font_index].fontstate = t_font_state;
							this->maplist.insert(STLMap<wchar,s32>::value_type(t_code,t_font_index));
						}else{
							ASSERT(0);
						}
					}
				}
			}

			return t_change;
		}

		/** WriteFontTexture
		*/
		void WriteFontTexture()
		{
			s32 t_drawtypemax = 0;

			switch(this->fonttexture_type){
			case NBsys::ND3d11::D3d11_FontTextureType::SFont:
				{
					t_drawtypemax = BSYS_D3D11_FONT_DRAWTYPEMAX_S;
				}break;
			case NBsys::ND3d11::D3d11_FontTextureType::MFont:
				{
					t_drawtypemax = BSYS_D3D11_FONT_DRAWTYPEMAX_M;
				}break;
			case NBsys::ND3d11::D3d11_FontTextureType::LFont:
				{
					t_drawtypemax = BSYS_D3D11_FONT_DRAWTYPEMAX_L;
				}break;
			case NBsys::ND3d11::D3d11_FontTextureType::ExFont:
				{
					t_drawtypemax = BSYS_D3D11_FONT_DRAWTYPEMAX_EX;
				}break;
			default:
				{
					ASSERT(0);
				}break;
			}

			s32 t_change_min = 0;
			s32 t_change_max = t_drawtypemax - 1;

			sharedptr<D3d11_Impl_Texture>& t_texture = this->d3d11_impl.GetTexture(this->textureid);
			if(t_texture){
				D3D11_MAPPED_SUBRESOURCE t_mapped_resource;
				HRESULT t_result = this->d3d11_impl.GetDeviceContext()->Map(t_texture->texture2d.get(),0,D3D11_MAP_WRITE_DISCARD,0,&t_mapped_resource);

				if(SUCCEEDED(t_result)){
					s32 t_from_pitch = this->texturewidth * 4;
					if(t_mapped_resource.RowPitch == t_from_pitch){
						u8* t_to = &reinterpret_cast<u8*>(t_mapped_resource.pData)[t_change_min * this->texturewidth * t_mapped_resource.RowPitch];
						u8* t_from = &this->texture->GetPixel().get()[t_change_min * this->texturewidth * t_from_pitch];

						s32 t_size = (t_change_max - t_change_min + 1) * this->texturewidth * t_from_pitch;
						Memory::memcpy(t_to,t_size,t_from,t_size);
					}else{
						for(s32 ii=t_change_min;ii<=t_change_max;ii++){
							s32 t_blocksize_to = ii * t_mapped_resource.RowPitch * this->texturewidth;
							s32 t_blocksize_from = ii * t_from_pitch * this->texturewidth;

							for(s32 yy=0;yy<this->texturewidth;yy++){
								u8* t_to = &reinterpret_cast<u8*>(t_mapped_resource.pData)[yy * t_mapped_resource.RowPitch + t_blocksize_to];
								u8* t_from = &this->texture->GetPixel().get()[yy * t_from_pitch + t_blocksize_from];

								s32 t_size = t_from_pitch;
								Memory::memcpy(t_to,t_size,t_from,t_size);
							}
						}
					}

					this->d3d11_impl.GetDeviceContext()->Unmap(t_texture->texture2d.get(),0);
				}
			}
		}
		
		/** MakeFontVertex
		*/
		void MakeFontVertex(const STLWString& a_string,sharedptr<NBsys::NVertex::Vertex<NBsys::NVertex::Vertex_Data_Pos3Uv2Color4TextureIndex4>>& a_vertex,f32 a_x,f32 a_y,f32 a_w,f32 a_h,s32 a_alignment_x,s32 a_alignment_y,f32 a_z,f32 a_view_size_w,f32 a_view_size_h,const NBsys::NColor::Color_F& a_color)
		{
			f32 t_scale_w = a_view_size_w / static_cast<f32>(this->texturewidth);
			f32 t_scale_h = a_view_size_h / static_cast<f32>(this->texturewidth);

			f32 t_string_w = 0.0f;
			f32 t_string_h = a_view_size_h;

			STLVector<s32>::Type t_work_list;
			{
				for(s32 ii=0;ii<static_cast<s32>(a_string.length());ii++){
					wchar t_code = a_string[ii];
					if(t_code != nullwchar){
						STLMap<wchar,s32>::iterator t_it = this->maplist.find(t_code);
						if(t_it != this->maplist.end()){
							//リストに追加。
							s32 t_font_index = t_it->second;
							t_work_list.push_back(t_font_index);

							//幅。
							NBsys::NFont::Font_State& t_font_state = this->list[t_font_index].fontstate;
							t_string_w += static_cast<f32>(t_font_state.cell_inc_x) * t_scale_w;
						}
					}
				}
			}

			{
				f32 t_x = a_x;
				f32 t_y = a_y;

				if(a_alignment_x < 0){
					//左寄せ。
				}else if(a_alignment_x == 0){
					//中寄。
					t_x = a_x + (a_w - t_string_w) / 2;
				}else{
					//右寄せ。
					t_x = a_x + a_w - t_string_w;
				}
				
				if(a_alignment_y < 0){
					//左寄せ。
				}else if(a_alignment_y == 0){
					//中寄。
					t_y = a_y + (a_h - t_string_h) / 2;
				}else{
					//右寄せ。
					t_y = a_y + a_h - t_string_h;
				}

				s32 ii_max = static_cast<s32>(t_work_list.size());
				for(s32 ii=0;ii<ii_max;ii++){
					s32 t_font_index = t_work_list[ii];
					NBsys::NFont::Font_State& t_font_state = this->list[t_font_index].fontstate;

					{
						f32 t_cell_y_rate = static_cast<f32>(this->texturewidth) / this->textureheight;

						f32 t_uv_x0 = 0.0f;
						f32 t_uv_x1 = 1.0f;
						f32 t_uv_y0 = t_cell_y_rate * t_font_index;
						f32 t_uv_y1 = t_cell_y_rate * (t_font_index + 1);

						f32 t_rect_x0 = t_x + static_cast<f32>(t_font_state.x) * t_scale_w;
						f32 t_rect_y0 = t_y + static_cast<f32>(t_font_state.y) * t_scale_h;

						{
							s32 t_temp_x = static_cast<s32>(t_rect_x0);
							t_rect_x0 = static_cast<f32>(t_temp_x);

							s32 t_temp_y = static_cast<s32>(t_rect_y0);
							t_rect_y0 = static_cast<f32>(t_temp_y);
						}

						f32 t_rect_x1 = t_rect_x0 + (this->texturewidth) * t_scale_w;
						f32 t_rect_y1 = t_rect_y0 + (this->texturewidth) * t_scale_h;

						NBsys::NVertex::Vertex_Data_Pos3Uv2Color4TextureIndex4 t_vertex;
						t_vertex.color_rr = a_color.r;
						t_vertex.color_gg = a_color.g;
						t_vertex.color_bb = a_color.b;
						t_vertex.color_aa = a_color.a;

						t_vertex.texture_index_00 = static_cast<u8>(this->fonttexture_type);
						t_vertex.texture_index_01 = 0;
						t_vertex.texture_index_02 = 0;
						t_vertex.texture_index_03 = 0;

						//00
						{
							t_vertex.pos_xx = t_rect_x0;
							t_vertex.pos_yy = t_rect_y0;
							t_vertex.pos_zz = a_z;

							t_vertex.uv_xx = t_uv_x0;
							t_vertex.uv_yy = t_uv_y0;

							a_vertex->AddVertex(t_vertex);
						}

						//10
						{
							t_vertex.pos_xx = t_rect_x1;
							t_vertex.pos_yy = t_rect_y0;
							t_vertex.pos_zz = a_z;

							t_vertex.uv_xx = t_uv_x1;
							t_vertex.uv_yy = t_uv_y0;

							a_vertex->AddVertex(t_vertex);
						}

						//01
						{
							t_vertex.pos_xx = t_rect_x0;
							t_vertex.pos_yy = t_rect_y1;
							t_vertex.pos_zz = a_z;

							t_vertex.uv_xx = t_uv_x0;
							t_vertex.uv_yy = t_uv_y1;

							a_vertex->AddVertex(t_vertex);
						}

						//01
						{
							t_vertex.pos_xx = t_rect_x0;
							t_vertex.pos_yy = t_rect_y1;
							t_vertex.pos_zz = a_z;

							t_vertex.uv_xx = t_uv_x0;
							t_vertex.uv_yy = t_uv_y1;

							a_vertex->AddVertex(t_vertex);
						}

						//10
						{
							t_vertex.pos_xx = t_rect_x1;
							t_vertex.pos_yy = t_rect_y0;
							t_vertex.pos_zz = a_z;

							t_vertex.uv_xx = t_uv_x1;
							t_vertex.uv_yy = t_uv_y0;

							a_vertex->AddVertex(t_vertex);
						}

						//11
						{
							t_vertex.pos_xx = t_rect_x1;
							t_vertex.pos_yy = t_rect_y1;
							t_vertex.pos_zz = a_z;

							t_vertex.uv_xx = t_uv_x1;
							t_vertex.uv_yy = t_uv_y1;

							a_vertex->AddVertex(t_vertex);
						}
					}

					t_x += t_font_state.cell_inc_x * t_scale_w;
				}
			}
		}
	};
	#endif

}}
#endif

