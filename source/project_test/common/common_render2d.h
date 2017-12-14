#pragma once

/**
 * Copyright (c) 2016 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief コモン。フォント描画。
*/


/** include
*/
#include "../include.h"


/** NCommon
*/
#if(BSYS_D3D11_ENABLE)
namespace NCommon
{
	/** 描画アイテム。
	*/
	struct Render2D_Item
	{
		/** Type
		*/
		struct Type
		{
			enum Id
			{
				None = 0,

				//レクト描画。
				Rect,

				//フォント描画。
				Font,

				Max,
			};
		};

		/** レクト描画。
		*/
		struct RectData
		{
			s32 z;

			f32 x;
			f32 y;
			f32 w;
			f32 h;

			s32 texture_id;
			NBsys::NColor::Color_F color;

			RectData(s32 a_z,f32 a_x,f32 a_y,f32 a_w,f32 a_h,s32 a_texture_id,const NBsys::NColor::Color_F& a_color)
				:
				z(a_z),
				x(a_x),
				y(a_y),
				w(a_w),
				h(a_h),
				texture_id(a_texture_id),
				color(a_color)
			{
			}
			nonvirtual ~RectData()
			{
			}
		};

		/** フォント描画。
		*/
		struct FontData
		{
			s32 z;

			f32 x;
			f32 y;
			f32 size;
			s32 texture_index;

			NBsys::NColor::Color_F color;
			STLWString string;

			FontData(s32 a_z,f32 a_x,f32 a_y,f32 a_size,s32 a_texture_index,const NBsys::NColor::Color_F& a_color,const STLWString& a_string)
				:
				z(a_z),
				x(a_x),
				y(a_y),
				size(a_size),
				texture_index(a_texture_index),
				color(a_color),
				string(a_string)
			{
			}
			nonvirtual ~FontData()
			{
			}
		};

		/** バリアント型。
		*/
		struct Data
		{
			s32 z;

			Type::Id type;

			f32 x;
			f32 y;
			f32 w;
			f32 h;
			f32 size;

			s32 texture_index;
			s32 texture_id;
			NBsys::NColor::Color_F color;

			STLWString string;
		};

		Data data;
		u8 raw[32];

		/** constructor
		*/
		Render2D_Item(const RectData& a_data)
		{
			this->data.z = a_data.z;

			this->data.type = Type::Rect;

			this->data.x = a_data.x;
			this->data.y = a_data.y;
			this->data.w = a_data.w;
			this->data.h = a_data.h;
			this->data.texture_id = a_data.texture_id;
			this->data.color = a_data.color;
		}

		/** constructor
		*/
		Render2D_Item(const FontData& a_data)
		{
			this->data.z = a_data.z;

			this->data.type = Type::Font;

			this->data.x = a_data.x;
			this->data.y = a_data.y;
			this->data.size = a_data.size;
			this->data.texture_index = a_data.texture_index;
			this->data.color = a_data.color;
			this->data.string = a_data.string;
		}

		/** destructor
		*/
		nonvirtual ~Render2D_Item()
		{
		}
	};

	/** Render2D_Material_Base
	*/
	class Render2D_Material_Base
	{
	public:
		Render2D_Material_Base()
		{
		}
		virtual ~Render2D_Material_Base()
		{
		}
	public:
		/** 初期化。
		*/
		virtual void Initialize_Update() = 0;

		/** 初期化チェック。
		*/
		virtual bool IsInitialized() = 0;

		/** 描画。
		*/
		virtual void PreRenderOnce(STLList<Render2D_Item>::Type& a_list) = 0;

		/** 描画。
		*/
		virtual void Render(NBsys::NGeometry::Geometry_Matrix_44& a_view_projection,STLList<Render2D_Item>::const_iterator a_it_start,STLList<Render2D_Item>::const_iterator a_it_end) = 0;
	};

	class Render2D
	{
	private:
		/** list
		*/
		STLList<Render2D_Item>::Type list;

		/** material_list
		*/
		sharedptr<Render2D_Material_Base> material_list[Render2D_Item::Type::Max];

	public:

		/** constructor
		*/
		Render2D()
		{
		}

		/** destructor
		*/
		nonvirtual ~Render2D()
		{
		}

		/** SetMaterial
		*/
		void SetMaterial(Render2D_Item::Type::Id a_type,sharedptr<Render2D_Material_Base>& a_material)
		{
			this->material_list[a_type] = a_material;
		}

		/** DrawRect
		*/
		void DrawRect(s32 a_z,f32 a_x,f32 a_y,f32 a_w,f32 a_h,s32 a_texture_id,const NBsys::NColor::Color_F& a_color)
		{
			Render2D_Item t_item(Render2D_Item::RectData(a_z,a_x,a_y,a_w,a_h,a_texture_id,a_color));
			this->list.push_back(t_item);
		}

		/** DrawFont
		*/
		void DrawFont(s32 a_z,f32 a_x,f32 a_y,f32 a_size,s32 a_texture_index,const NBsys::NColor::Color_F& a_color,const STLWString& a_string)
		{
			Render2D_Item t_item(Render2D_Item::FontData(a_z,a_x,a_y,a_size,a_texture_index,a_color,a_string));
			this->list.push_back(t_item);
		}

		/** Render
		*/
		void Render(NBsys::NGeometry::Geometry_Matrix_44& a_view_projection)
		{
			//ソート。
			this->list.sort([](const Render2D_Item& a_item_a,const Render2D_Item& a_item_b){
				return (a_item_a.data.z > a_item_b.data.z);
			});

			//描画。
			{
				STLList<Render2D_Item>::const_iterator t_it_end = this->list.end();
				STLList<Render2D_Item>::const_iterator t_it = this->list.begin();

				for(s32 ii=0;ii<COUNTOF(this->material_list);ii++){
					if(this->material_list[ii].get() != nullptr){
						this->material_list[ii]->PreRenderOnce(this->list);
					}
				}

				Render2D_Item::Type::Id t_current_type = Render2D_Item::Type::None;
				STLList<Render2D_Item>::const_iterator t_it_renderstart = t_it;
				if(t_it != t_it_end){
					t_current_type = t_it->data.type;
				}

				while(t_it != t_it_end){

					if(t_it->data.type != t_current_type){
						this->material_list[t_current_type]->Render(a_view_projection,t_it_renderstart,t_it);

						t_current_type = t_it->data.type;
						t_it_renderstart = t_it;
					}

					t_it++;
				}

				if(t_it_renderstart != t_it_end){
					this->material_list[t_current_type]->Render(a_view_projection,t_it_renderstart,t_it_end);
				}
			}

			//クリア。
			this->list.clear();
		}

	};

}
#endif

