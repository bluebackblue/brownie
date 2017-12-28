﻿#pragma once

/**
 * Copyright (c) 2016-2017 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE.txt
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief コモン。２Ｄ描画。
*/


/** include
*/
#pragma warning(push)
#pragma warning(disable:4464)
#include "../include.h"
#pragma warning(pop)


/** NTest::NCommon
*/
#if(BSYS_D3D11_ENABLE)
namespace NTest{namespace NCommon
{
	/** Render2D_ItemType
	*/
	struct Render2D_ItemType
	{
		enum Id
		{
			None = 0,

			//レクト。
			Rect,

			//フォント。
			Font,

			Max,
		};
	};


	/** Render2D_Item_Base
	*/
	class Render2D_Item_Base
	{
	public:
		/** z_sort
		*/
		s32 z_sort;

		/** itemtype
		*/
		Render2D_ItemType::Id itemtype;

	public:
		/** constructor
		*/
		Render2D_Item_Base(s32 a_z_sort,Render2D_ItemType::Id a_itemtype)
			:
			z_sort(a_z_sort),
			itemtype(a_itemtype)
		{
		}

		/** destructor
		*/
		virtual ~Render2D_Item_Base()
		{
		}
	};


	/** Render2D_Item_Rect
	*/
	class Render2D_Item_Rect : public Render2D_Item_Base
	{
	public:

		/** xywh
		*/
		f32 x;
		f32 y;
		f32 w;
		f32 h;

		/** texture_id
		*/
		s32 texture_id;

		/** color
		*/
		NBsys::NColor::Color_F color;
		
	public:

		/** constructor
		*/
		Render2D_Item_Rect(s32 a_z_sort)
			:
			Render2D_Item_Base(a_z_sort,Render2D_ItemType::Rect),
			x(0.0f),
			y(0.0f),
			w(0.0f),
			h(0.0f),
			texture_id(-1),
			color(1.0f,1.0f,1.0f,1.0f)
		{
		}

		/** destructor
		*/
		virtual ~Render2D_Item_Rect()
		{
		}

	};


	/** Render2D_Item_Font
	*/
	#if(BSYS_FONT_ENABLE)
	class Render2D_Item_Font : public Render2D_Item_Base
	{
	public:

		/** xywh
		*/
		f32 x;
		f32 y;
		f32 w;
		f32 h;

		/** clip
		*/
		bool clip;

		/** size
		*/
		f32 size;

		/** fonttexture_type
		*/
		NBsys::ND3d11::D3d11_FontTextureType::Id fonttexture_type;

		/** color
		*/
		NBsys::NColor::Color_F color;

		/** alignment_x
		*/
		s32 alignment_x;

		/** alignment_y
		*/
		s32 alignment_y;

		/** string
		*/
		STLWString string;
		
	public:
		/** constructor
		*/
		Render2D_Item_Font(s32 a_z_sort)
			:
			Render2D_Item_Base(a_z_sort,Render2D_ItemType::Font),
			x(0.0f),
			y(0.0f),
			w(0.0f),
			h(0.0f),
			clip(false),
			size(0),
			fonttexture_type(NBsys::ND3d11::D3d11_FontTextureType::SFont),
			color(1.0f,1.0f,1.0f,1.0f),
			alignment_x(0),
			alignment_y(0),
			string(L"")
		{
		}

		/** destructor
		*/
		virtual ~Render2D_Item_Font()
		{
		}
	};
	#endif


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
		virtual void PreRenderOnce(STLList<sharedptr<Render2D_Item_Base>>::Type& a_list) = 0;

		/** 描画。
		*/
		virtual void Render(STLList<sharedptr<Render2D_Item_Base>>::const_iterator a_it_start,STLList<sharedptr<Render2D_Item_Base>>::const_iterator a_it_end) = 0;
	};


	class Render2D
	{
	private:
		/** list
		*/
		STLList<sharedptr<Render2D_Item_Base>>::Type list;

		/** material_list
		*/
		sharedptr<Render2D_Material_Base> material_list[Render2D_ItemType::Max];

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
		void SetMaterial(Render2D_ItemType::Id a_itemtype,sharedptr<Render2D_Material_Base> a_material)
		{
			this->material_list[a_itemtype] = a_material;
		}

		/** Draw
		*/
		void Draw(sharedptr<Render2D_Item_Base> a_item)
		{
			this->list.push_back(a_item);
		}

		/** Render
		*/
		void Render()
		{
			//ソート。
			this->list.sort([](const sharedptr<Render2D_Item_Base>& a_item_a,const sharedptr<Render2D_Item_Base>& a_item_b){
				return (a_item_a->z_sort < a_item_b->z_sort);
			});

			//描画。
			{
				STLList<sharedptr<Render2D_Item_Base>>::const_iterator t_it_end = this->list.end();
				STLList<sharedptr<Render2D_Item_Base>>::const_iterator t_it = this->list.begin();

				for(s32 ii=0;ii<COUNTOF(this->material_list);ii++){
					if(this->material_list[ii].get() != nullptr){
						this->material_list[ii]->PreRenderOnce(this->list);
					}
				}

				Render2D_ItemType::Id t_current_itemtype = Render2D_ItemType::None;
				STLList<sharedptr<Render2D_Item_Base>>::const_iterator t_it_renderstart = t_it;
				if(t_it != t_it_end){
					t_current_itemtype = t_it->get()->itemtype;
				}

				while(t_it != t_it_end){

					if(t_it->get()->itemtype != t_current_itemtype){
						this->material_list[t_current_itemtype]->Render(t_it_renderstart,t_it);

						t_current_itemtype = t_it->get()->itemtype;
						t_it_renderstart = t_it;
					}

					t_it++;
				}

				if(t_it_renderstart != t_it_end){
					this->material_list[t_current_itemtype]->Render(t_it_renderstart,t_it_end);
				}
			}

			//クリア。
			this->list.clear();
		}

	};


}}
#endif

