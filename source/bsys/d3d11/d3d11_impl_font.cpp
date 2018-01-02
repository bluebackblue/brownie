﻿

/**
 * Copyright (c) 2016-2017 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE.txt
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief Ｄ３Ｄ１１。
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
#include "./d3d11_impl_font.h"


/** warning

4710 : この関数はインライン展開のために選択されましたが、コンパイラはインライン展開を実行しませんでした。

*/
#pragma warning(disable:4710)


/** NBsys::ND3d11
*/
#if((BSYS_D3D11_ENABLE)&&(BSYS_FONT_ENABLE))
#pragma warning(push)
#pragma warning(disable:4710)
namespace NBsys{namespace ND3d11
{
	/** constructor
	*/
	D3d11_Impl_Font::D3d11_Impl_Font(D3d11_Impl& a_opengl_impl,const sharedptr<NBsys::NFont::Font>& a_font,s32 a_texture_width,const STLWString& a_name,D3d11_FontTextureType::Id a_fonttexture_type)
		:
		d3d11_impl(a_opengl_impl),
		font(a_font),
		fonttexture_type(a_fonttexture_type),
		//texturewidth,
		//textureheight,
		//texture,
		//textureid,
		list(),
		maplist()
	{
		this->texturewidth = NTexture::CalcJustWidth(a_texture_width);

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
		case NBsys::ND3d11::D3d11_FontTextureType::Max:
		default:
			{
				ASSERT(0);
			}break;
		}

		this->textureheight = NTexture::CalcJustWidth(this->texturewidth * t_drawtypemax);

		sharedptr<u8> t_pixel(new u8[static_cast<u32>(this->texturewidth * this->textureheight * 4)]);

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
	D3d11_Impl_Font::~D3d11_Impl_Font()
	{
	}


	/** 書き換え可能位置の検索。
	*/
	s32 D3d11_Impl_Font::FindNoLockFontIndex()
	{
		for(u32 ii=0;ii<this->list.size();ii++){
			if((this->list[ii].lock == false)&&(this->list[ii].code == nullchar)){
				return static_cast<s32>(ii);
			}
		}

		for(u32 ii=0;ii<this->list.size();ii++){
			if(this->list[ii].lock == false){
				return static_cast<s32>(ii);
			}
		}

		return -1;
	}


	/** ResetLock
	*/
	void D3d11_Impl_Font::ResetLock()
	{
		for(u32 ii=0;ii<this->list.size();ii++){
			this->list[ii].lock = false;
		}
	}


	/** GetTexture
	*/
	s32 D3d11_Impl_Font::GetTexture()
	{
		return this->textureid;
	}

		
	/** PreUpdateFontTexture
	*/
	bool D3d11_Impl_Font::PreUpdateFontTexture(const STLWString& a_string)
	{
		bool t_change = false;

		for(u32 ii=0;ii<a_string.length();ii++){

			wchar t_code = a_string[ii];

			if(t_code != nullwchar){
				s32 t_font_index = 0;

				auto t_it = std::as_const(this->maplist).find(t_code);
				if(t_it != this->maplist.cend()){
					//すでに作成済み。
				}else{
					//書き換え可能位置の検索。
					t_font_index = this->FindNoLockFontIndex();

					if(t_font_index >= 0){
						wchar t_old_code = this->list[static_cast<u32>(t_font_index)].code;
						if(t_old_code != nullwchar){
							//旧コードを削除。
							auto t_it_old = std::as_const(this->maplist).find(t_old_code);
							if(t_it_old != this->maplist.cend()){
								this->maplist.erase(t_it_old);
							}
						}

						wchar t_wchar[2] = {t_code,nullwchar};
						UNUSED(t_wchar);
						DEEPDEBUG_TAGLOG(BSYS_D3D11_DEBUG_ENABLE,L"d3d11_impl_font",L"%s",t_wchar);

						//テクスチャーに書き込み。
						NBsys::NFont::Font_State t_font_state = this->font->GetPixel_R8G8B8A8(this->texture->GetPixel(),t_font_index * (this->texturewidth * this->texturewidth * 4),this->texturewidth,this->texturewidth,t_code);
						t_change = true;

						//登録。
						this->list[static_cast<u32>(t_font_index)].code = t_code;
						this->list[static_cast<u32>(t_font_index)].lock = true;
						this->list[static_cast<u32>(t_font_index)].fontstate = t_font_state;
						this->maplist.insert(std::make_pair(t_code,t_font_index));
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
	void D3d11_Impl_Font::WriteFontTexture()
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
		case NBsys::ND3d11::D3d11_FontTextureType::Max:
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
				if(static_cast<s32>(t_mapped_resource.RowPitch) == t_from_pitch){
					u8* t_to = &reinterpret_cast<u8*>(t_mapped_resource.pData)[t_change_min * this->texturewidth * t_mapped_resource.RowPitch];
					u8* t_from = &this->texture->GetPixel().get()[t_change_min * this->texturewidth * t_from_pitch];

					s32 t_size = (t_change_max - t_change_min + 1) * this->texturewidth * t_from_pitch;
					NMemory::Copy(t_to,t_size,t_from,t_size);
				}else{
					for(s32 ii=t_change_min;ii<=t_change_max;ii++){
						u32 t_blocksize_to = static_cast<u32>(ii * t_mapped_resource.RowPitch * this->texturewidth);
						u32 t_blocksize_from = static_cast<u32>(ii * t_from_pitch * this->texturewidth);

						for(s32 yy=0;yy<this->texturewidth;yy++){
							u8* t_to = &reinterpret_cast<u8*>(t_mapped_resource.pData)[yy * t_mapped_resource.RowPitch + t_blocksize_to];
							u8* t_from = &this->texture->GetPixel().get()[yy * t_from_pitch + t_blocksize_from];

							s32 t_size = t_from_pitch;
							NMemory::Copy(t_to,t_size,t_from,t_size);
						}
					}
				}

				this->d3d11_impl.GetDeviceContext()->Unmap(t_texture->texture2d.get(),0);
			}
		}
	}

		
	/** MakeFontVertex
	*/
	void D3d11_Impl_Font::MakeFontVertex(const STLWString& a_string,sharedptr<NBsys::NVertex::Vertex<NBsys::NVertex::Vertex_Data_Pos3Uv2Color4TextureIndex4>>& a_vertex,f32 a_x,f32 a_y,f32 a_w,f32 a_h,s32 a_alignment_x,s32 a_alignment_y,f32 a_z,f32 a_view_size_w,f32 a_view_size_h,const NBsys::NColor::Color_F& a_color)
	{
		f32 t_scale_w = a_view_size_w / static_cast<f32>(this->texturewidth);
		f32 t_scale_h = a_view_size_h / static_cast<f32>(this->texturewidth);

		f32 t_string_w = 0.0f;
		f32 t_string_h = a_view_size_h;

		STLVector<u32>::Type t_work_list;
		{
			for(u32 ii=0;ii<a_string.length();ii++){
				wchar t_code = a_string[ii];
				if(t_code != nullwchar){
					auto t_it = std::as_const(this->maplist).find(t_code);
					if(t_it != this->maplist.cend()){
						//リストに追加。
						u32 t_font_index = t_it->second;
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

			u32 ii_max = static_cast<u32>(t_work_list.size());
			for(u32 ii=0;ii<ii_max;ii++){
				u32 t_font_index = t_work_list[ii];
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
					t_vertex.color_rr = a_color.r();
					t_vertex.color_gg = a_color.g();
					t_vertex.color_bb = a_color.b();
					t_vertex.color_aa = a_color.a();

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


}}
#pragma warning(pop)
#endif
