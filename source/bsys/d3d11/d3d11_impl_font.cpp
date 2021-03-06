﻿

/**
 * Copyright (c) blueback
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
	D3d11_Impl_Font::D3d11_Impl_Font(D3d11_Impl& a_opengl_impl,const sharedptr<NBsys::NFont::Font>& a_font,s32 a_texture_width,const STLWString& a_name,D3d11_FontTextureType::Id a_fonttexture_type,s32 a_drawtypemax)
		:
		d3d11_impl(a_opengl_impl),
		font(a_font),
		fonttexture_type(a_fonttexture_type),
		drawtypemax(a_drawtypemax),
		//texture_size,
		//texture,
		//textureid,
		list(),
		maplist()
	{
		this->texture_size.ww = NTexture::CalcJustSize(a_texture_width);

		this->texture_size.hh = NTexture::CalcJustSize(this->texture_size.ww * this->drawtypemax);

		sharedptr<u8> t_pixel(new u8[static_cast<u32>(this->texture_size.ww * this->texture_size.hh * 4)],default_delete<u8[]>());

		this->texture.reset(new NBsys::NTexture::Texture(
			t_pixel,
			Size2DType<s32>(this->texture_size.ww,this->texture_size.hh),
			this->texture_size.ww * 4,
			NBsys::NTexture::TextureType::R8G8B8A8,
			a_name
			)
		);

		this->textureid = this->d3d11_impl.CreateTexture(this->texture,true);

		for(s32 ii=0;ii<this->drawtypemax;ii++){
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
						FULLDEBUG_TAGLOG(BSYS_D3D11_DEBUG_ENABLE,L"d3d11_impl_font",L"%s",t_wchar);

						//テクスチャーに書き込み。
						NBsys::NFont::Font_State t_font_state = this->font->GetPixel_R8G8B8A8(
							this->texture->GetPixel(),
							t_font_index * (this->texture_size.ww * this->texture_size.ww * 4),
							Size2DType<s32>(this->texture_size.ww,this->texture_size.ww),
							t_code
						);
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
		s32 t_change_min = 0;
		s32 t_change_max = this->drawtypemax - 1;

		sharedptr<D3d11_Impl_Texture>& t_texture = this->d3d11_impl.GetTexture(this->textureid);
		if(t_texture){
			D3D11_MAPPED_SUBRESOURCE t_mapped_resource;

			sharedptr<ID3D11DeviceContext>& t_devicecontext = this->d3d11_impl.GetDeviceContext();
			if(t_devicecontext != nullptr){
				HRESULT t_result = t_devicecontext->Map(t_texture->texture2d.get(),0,D3D11_MAP_WRITE_DISCARD,0,&t_mapped_resource);

				if(SUCCEEDED(t_result)){
					s32 t_from_pitch = this->texture_size.ww * 4;
					if(static_cast<s32>(t_mapped_resource.RowPitch) == t_from_pitch){
						u8* t_to = &reinterpret_cast<u8*>(t_mapped_resource.pData)[t_change_min * this->texture_size.ww * t_mapped_resource.RowPitch];
						u8* t_from = &this->texture->GetPixel().get()[t_change_min * this->texture_size.ww * t_from_pitch];

						s32 t_size = (t_change_max - t_change_min + 1) * this->texture_size.ww * t_from_pitch;
						NMemory::Copy(t_to,t_size,t_from,t_size);
					}else{
						for(s32 ii=t_change_min;ii<=t_change_max;ii++){
							u32 t_blocksize_to = static_cast<u32>(ii * t_mapped_resource.RowPitch * this->texture_size.ww);
							u32 t_blocksize_from = static_cast<u32>(ii * t_from_pitch * this->texture_size.ww);

							for(s32 yy=0;yy<this->texture_size.ww;yy++){
								u8* t_to = &reinterpret_cast<u8*>(t_mapped_resource.pData)[yy * t_mapped_resource.RowPitch + t_blocksize_to];
								u8* t_from = &this->texture->GetPixel().get()[yy * t_from_pitch + t_blocksize_from];

								s32 t_size = t_from_pitch;
								NMemory::Copy(t_to,t_size,t_from,t_size);
							}
						}
					}

					t_devicecontext->Unmap(t_texture->texture2d.get(),0);
				}
			}
		}
	}

		
	/** MakeFontVertex

	a_string		: 文字列。
	a_vertex		: 出力先バーテックス。
	a_rect			: アライメント用文字領域の指定。
	a_alignment		: アライメント。
	a_z				: バーテックスZ値。
	a_view_size		: サイズ。
	a_color			: 色

	*/
	void D3d11_Impl_Font::MakeFontVertex(const STLWString& a_string,sharedptr<NBsys::NVertex::Vertex<NBsys::NVertex::Vertex_Data_Pos3Uv2Color4TextureIndex4>>& a_vertex,const Rect2DType_R<f32>& a_viewrect,NBsys::NFont::Font_Alignment::Id a_alignment,f32 a_z,const Size2DType<f32>& a_view_size,const NBsys::NColor::Color_F& a_color)
	{
		f32 t_scale_w = a_view_size.ww / static_cast<f32>(this->texture_size.ww);
		f32 t_scale_h = a_view_size.hh / static_cast<f32>(this->texture_size.ww);

		f32 t_string_w = 0.0f;
		f32 t_string_h = a_view_size.hh;

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
			f32 t_x = a_viewrect.xx;
			f32 t_y = a_viewrect.yy;

			switch(a_alignment){
			case NBsys::NFont::Font_Alignment::Center_Top:
			case NBsys::NFont::Font_Alignment::Center_VCenter:
			case NBsys::NFont::Font_Alignment::Center_Bottom:
				{
					//中。
					t_x = a_viewrect.xx + (a_viewrect.ww - t_string_w) / 2;
				}break;
			case NBsys::NFont::Font_Alignment::Right_Top:
			case NBsys::NFont::Font_Alignment::Right_VCenter:
			case NBsys::NFont::Font_Alignment::Right_Bottom:
				{
					//右。
					t_x = a_viewrect.xx + a_viewrect.ww - t_string_w;
				}break;
			default:
				{
					//左。
				}break;
			}

			switch(a_alignment){
			case NBsys::NFont::Font_Alignment::Left_VCenter:
			case NBsys::NFont::Font_Alignment::Center_VCenter:
			case NBsys::NFont::Font_Alignment::Right_VCenter:
				{
					//中。
					t_y = a_viewrect.yy + (a_viewrect.hh - t_string_h) / 2;
				}break;
			case NBsys::NFont::Font_Alignment::Left_Bottom:
			case NBsys::NFont::Font_Alignment::Center_Bottom:
			case NBsys::NFont::Font_Alignment::Right_Bottom:
				{
					//下。
					t_y = a_viewrect.yy + a_viewrect.hh - t_string_h;
				}break;
			default:
				{
					//上。
				}break;
			}

			u32 ii_max = static_cast<u32>(t_work_list.size());
			for(u32 ii=0;ii<ii_max;ii++){
				u32 t_font_index = t_work_list[ii];
				NBsys::NFont::Font_State& t_font_state = this->list[t_font_index].fontstate;

				{
					f32 t_cell_y_rate = static_cast<f32>(this->texture_size.ww) / this->texture_size.hh;

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

					f32 t_rect_x1 = t_rect_x0 + (this->texture_size.ww) * t_scale_w;
					f32 t_rect_y1 = t_rect_y0 + (this->texture_size.ww) * t_scale_h;

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

