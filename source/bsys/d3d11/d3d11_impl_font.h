#pragma once

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
		sharedptr< NFont::Font > font;

		/** texturewidth
		*/
		s32 texturewidth;
	
		/** texture
		*/
		sharedptr< NBsys::NTexture::Texture > texture;

		/** textureid
		*/
		s32 textureid;

		/** list
		*/
		STLVector< Item >::Type list;

		/** maplist

		wchar	: code
		s32		: fontindex

		*/
		STLMap< wchar , s32 >::Type maplist;

	public:
		/** constructor
		*/
		D3d11_Impl_Font(D3d11_Impl& a_opengl_impl,const sharedptr< NBsys::NFont::Font >& a_font,s32 a_texture_width,const STLString& a_name)
			:
			d3d11_impl(a_opengl_impl),
			font(a_font),
			texturewidth(a_texture_width)
		{
			sharedptr<u8> t_pixel(new u8[this->texturewidth * this->texturewidth * BSYS_D3D11_FONT_DRAWTYPEMAX * 4]);

			this->texture.reset(new NBsys::NTexture::Texture(
				t_pixel,
				this->texturewidth,
				this->texturewidth * BSYS_D3D11_FONT_DRAWTYPEMAX,
				this->texturewidth * 4,
				NBsys::NTexture::TextureType::R8G8B8A8,
				a_name
				)
				);

			this->textureid = this->d3d11_impl.CreateTexture(this->texture);

			for(s32 ii=0;ii<BSYS_D3D11_FONT_DRAWTYPEMAX;ii++){
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

		/** DrawFont
		*/
		void DrawFont(const STLWString& a_string,f32 a_font_size,f32 a_x,f32 a_y,const NBsys::NColor::Color_F& a_color)
		{
			//テクスチャー設定。
			///todo:this->d3d11_impl.Render_SetTextureDirect(0,this->textureid);

			for(s32 ii=0;ii<static_cast<s32>(a_string.length());ii++){

				wchar t_code = a_string[ii];

				if(t_code != nullwchar){
					s32 t_font_index = 0;

					STLMap< wchar , s32 >::iterator t_it = this->maplist.find(t_code);
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
								STLMap< wchar , s32 >::iterator t_old_it = this->maplist.find(t_old_code);
								if(t_old_it != this->maplist.end()){
									this->maplist.erase(t_old_it);
								}
							}

							#if !defined(ROM_MASTER)
							{
								wchar t_wchar[2] = {t_code,nullwchar};
								TAGLOG("Opengl_Impl_Font",L"%s",t_wchar);
							}
							#endif

							//テクスチャーに書き込み。
							NBsys::NFont::Font_State t_font_state = this->font->GetPixel_R8G8B8A8(this->texture->GetPixel(),t_font_index * (this->texturewidth * this->texturewidth * 4),this->texturewidth,this->texturewidth,t_code);
							u8* t_pixel = &this->texture->GetPixel().get()[t_font_index * (this->texturewidth * this->texturewidth * 4)];
							///todo:glTexSubImage2D(GL_TEXTURE_2D,0,0,t_font_index * this->texturewidth,this->texturewidth,this->texturewidth,GL_RGBA,GL_UNSIGNED_BYTE,t_pixel);

							//登録。
							this->list[t_font_index].code = t_code;
							this->list[t_font_index].lock = true;
							this->list[t_font_index].fontstate = t_font_state;
							this->maplist.insert(STLMap< wchar , s32 >::value_type(t_code,t_font_index));
						}else{
							ASSERT(0);
						}
					}
				}
			}

			f32 t_scale = a_font_size / this->texturewidth;

			///todo:glBegin(GL_QUADS);
			{
				///todo:glColor4f(a_color.r,a_color.g,a_color.b,a_color.a);

				f32 t_x = a_x;
				f32 t_y = a_y;

				for(s32 ii=0;ii<static_cast<s32>(a_string.length());ii++){
					wchar t_code = a_string[ii];

					if(t_code != nullwchar){
						STLMap< wchar , s32 >::iterator t_it = this->maplist.find(t_code);
						if(t_it != this->maplist.end()){

							s32 t_font_index = t_it->second;

							NBsys::NFont::Font_State& t_font_state = this->list[t_font_index].fontstate;

							{
								f32 t_width = 1.0f / BSYS_D3D11_FONT_DRAWTYPEMAX;
								f32 t_pix = t_width / this->texturewidth;

								f32 t_uv_x0 = 0.0f;
								f32 t_uv_y0 = t_width * t_font_index;
								f32 t_uv_x1 = 1.0f;
								f32 t_uv_y1 = t_width * (t_font_index + 1) - t_pix;

								f32 t_rect_x0 = t_x + (t_font_state.x * t_scale);
								f32 t_rect_x1 = t_rect_x0 + a_font_size;
								f32 t_rect_y0 = t_y + (t_font_state.y * t_scale);
								f32 t_rect_y1 = t_rect_y0 + a_font_size;

								///todo:glTexCoord2f(t_uv_x0,t_uv_y0);
								///todo:glVertex2f(t_rect_x0,t_rect_y0);

								///todo:glTexCoord2f(t_uv_x1,t_uv_y0);
								///todo:glVertex2f(t_rect_x1,t_rect_y0);

								///todo:glTexCoord2f(t_uv_x1,t_uv_y1);
								///todo:glVertex2f(t_rect_x1,t_rect_y1);

								///todo:glTexCoord2f(t_uv_x0,t_uv_y1);
								///todo:glVertex2f(t_rect_x0,t_rect_y1);
							}

							t_x += (t_font_state.cell_inc_x * t_scale);
						}
					}
				}
			}
			///todo:glEnd();
		}

	};

}}
#endif

