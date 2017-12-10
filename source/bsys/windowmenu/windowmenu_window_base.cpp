

/**
 * Copyright (c) 2017 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief デバッグメニュー。
*/


/** include
*/
#include <bsys_pch.h>


/** include
*/
#include "../types/types.h"


/** include
*/
#include "./debugmenu.h"


/** include
*/
#include "./debugmenu_window_base.h"


/** NBsys::NDebugMenu
*/
namespace NBsys{namespace NDebugMenu
{
	/** constructor
	*/
	DebugMenu_Window_Base::DebugMenu_Window_Base()
		:
		me(nullptr),
		parent(nullptr),
		mode(Mode::Free),
		child_list(),

		offset_x(-1.0f),
		offset_y(-1.0f),
		width(-1.0f),
		height(-1.0f),

		z(0.0f),

		calc_x(-1.0f),
		calc_y(-1.0f),
		calc_w(-1.0f),
		calc_h(-1.0f),
		calc_parent_x(-1.0f),
		calc_parent_y(-1.0f)
	{
	}

	/** destructor
	*/
	DebugMenu_Window_Base::~DebugMenu_Window_Base()
	{
	}

	/** SetBase
	*/
	void DebugMenu_Window_Base::Initialize(Mode::Id a_mode,f32 a_offset_x,f32 a_offset_y,f32 a_width,f32 a_height,f32 a_z)
	{
		this->me = this;
		this->parent = nullptr;
		this->child_list.clear();

		this->mode = a_mode;

		this->offset_x = a_offset_x;
		this->offset_y = a_offset_y;
		this->width = a_width;
		this->height = a_height;
		this->z = a_z;
	}

	/** CalcWidth
	*/
	f32 DebugMenu_Window_Base::CalcWidth()
	{
		f32 t_width = this->CalcWidthFromParent();

		if(t_width < 0.0f){
			t_width = this->CalcWidthFromChild();
		}

		ASSERT(t_width >= 0.0f);
		return t_width;
	}
	/** CalcHeight
	*/
	f32 DebugMenu_Window_Base::CalcHeight()
	{
		f32 t_height = this->CalcHeightFromParent();

		if(t_height < 0.0f){
			t_height = this->CalcHeightFromChild();
		}

		ASSERT(t_height >= 0.0f);
		return t_height;
	}

	/** CalcWidthFromParent
	*/
	f32 DebugMenu_Window_Base::CalcWidthFromParent()
	{
		//自分のサイズを使用。
		f32 t_width = this->width;

		//親のサイズを使用。
		if(t_width < 0.0f){
			if(this->parent != nullptr){
				t_width = this->parent->CalcWidthFromParent();
			}
		}

		return t_width;
	}
	/** CalcHeightFromParent
	*/
	f32 DebugMenu_Window_Base::CalcHeightFromParent()
	{
		//自分のサイズを使用。
		f32 t_height = this->height;

		//親のサイズを使用。
		if(t_height < 0.0f){
			if(this->parent != nullptr){
				t_height = this->parent->CalcHeightFromParent();
			}
		}

		return t_height;
	}

	/** CalcWidthFromChild
	*/
	f32 DebugMenu_Window_Base::CalcWidthFromChild()
	{
		//自分のサイズを使用。
		f32 t_width = this->width;

		//子のサイズを使用。
		if(t_width < 0.0f){

			t_width = 0.0f;

			STLVector<sharedptr<DebugMenu_Window_Base>>::iterator t_it_end = this->child_list.end();

			switch(this->mode){
			case Mode::Free:
				{
					//自由配置。
					for(STLVector<sharedptr<DebugMenu_Window_Base>>::iterator t_it = this->child_list.begin();t_it != t_it_end;++t_it){
						f32 t_width_temp = (*t_it)->CalcWidthFromChild();
						if(t_width_temp > t_width){
							t_width = t_width_temp;
						}
					}
				}break;
			case Mode::Vertical:
				{
					//縦。
					for(STLVector<sharedptr<DebugMenu_Window_Base>>::iterator t_it = this->child_list.begin();t_it != t_it_end;++t_it){
						f32 t_width_temp = (*t_it)->CalcWidthFromChild();
						if(t_width_temp > t_width){
							t_width = t_width_temp;
						}
					}
				}break;
			case Mode::Horizontal:
				{
					//横。
					for(STLVector<sharedptr<DebugMenu_Window_Base>>::iterator t_it = this->child_list.begin();t_it != t_it_end;++t_it){
						t_width += (*t_it)->CalcWidthFromChild();
					}
				}break;
			}
		}

		return t_width;
	}

	/** CalcHeightFromChild
	*/
	f32 DebugMenu_Window_Base::CalcHeightFromChild()
	{
		//自分のサイズを使用。
		f32 t_height = this->height;

		//子のサイズを使用。
		if(t_height < 0.0f){

			t_height = 0.0f;

			STLVector<sharedptr<DebugMenu_Window_Base>>::iterator t_it_end = this->child_list.end();

			switch(this->mode){
			case Mode::Free:
				{
					//自由配置。
					for(STLVector<sharedptr<DebugMenu_Window_Base>>::iterator t_it = this->child_list.begin();t_it != t_it_end;++t_it){
						f32 t_height_temp = (*t_it)->CalcHeightFromChild();
						if(t_height_temp > t_height){
							t_height = t_height_temp;
						}
					}
				}break;
			case Mode::Vertical:
				{
					//縦。
					for(STLVector<sharedptr<DebugMenu_Window_Base>>::iterator t_it = this->child_list.begin();t_it != t_it_end;++t_it){
						t_height += (*t_it)->CalcHeightFromChild();
					}
				}break;
			case Mode::Horizontal:
				{
					//横。
					for(STLVector<sharedptr<DebugMenu_Window_Base>>::iterator t_it = this->child_list.begin();t_it != t_it_end;++t_it){
						f32 t_height_temp = (*t_it)->CalcHeightFromChild();
						if(t_height_temp > t_height){
							t_height = t_height_temp;
						}
					}
				}break;
			}
		}

		return t_height;
	}

	/** AddChild
	*/
	void DebugMenu_Window_Base::AddChild(const sharedptr<DebugMenu_Window_Base>& a_window)
	{
		this->child_list.push_back(a_window);
		this->child_list[this->child_list.size()-1]->parent = this->me;
		this->child_list[this->child_list.size()-1]->CallBack_SetParent();
	}

	/** 表示位置計算。
	*/
	void DebugMenu_Window_Base::CalcRect(f32 a_parent_offset_x,f32 a_parent_offset_y)
	{
		//[計算結果]親の位置。
		this->calc_parent_x = a_parent_offset_x;
		this->calc_parent_y = a_parent_offset_y;

		//[計算結果]自分の位置。
		this->calc_x = this->calc_parent_x + this->offset_x;
		this->calc_y = this->calc_parent_y + this->offset_y;

		//[計算結果]自分のサイズ。
		this->calc_w = this->CalcWidth();
		this->calc_h = this->CalcHeight();

		STLVector<sharedptr<DebugMenu_Window_Base>>::iterator t_it_end = this->child_list.end();

		switch(this->mode){
		case Mode::Free:
			{
				//自由配置。
				for(STLVector<sharedptr<DebugMenu_Window_Base>>::iterator t_it = this->child_list.begin();t_it != t_it_end;++t_it){
					(*t_it)->CalcRect(this->calc_x,this->calc_y);
				}
			}break;
		case Mode::Vertical:
			{
				//縦。
				f32 t_y = this->calc_y;
				for(STLVector<sharedptr<DebugMenu_Window_Base>>::iterator t_it = this->child_list.begin();t_it != t_it_end;++t_it){
					(*t_it)->CalcRect(this->calc_x,t_y);
					t_y += (*t_it)->calc_h;
				}
			}break;
		case Mode::Horizontal:
			{
				//横。
				f32 t_x = this->calc_x;
				for(STLVector<sharedptr<DebugMenu_Window_Base>>::iterator t_it = this->child_list.begin();t_it != t_it_end;++t_it){
					(*t_it)->CalcRect(t_x,this->calc_y);
					t_x += (*t_it)->calc_w;
				}
			}break;
		}
	}

	/** 更新。
	*/
	void DebugMenu_Window_Base::Update()
	{
		STLVector<sharedptr<DebugMenu_Window_Base>>::iterator t_it_end = this->child_list.end();
		for(STLVector<sharedptr<DebugMenu_Window_Base>>::iterator t_it = this->child_list.begin();t_it != t_it_end;++t_it){
			(*t_it)->Update();
		}
	}

	/** 描画。
	*/
	void DebugMenu_Window_Base::Draw()
	{
		STLVector<sharedptr<DebugMenu_Window_Base>>::iterator t_it_end = this->child_list.end();
		for(STLVector<sharedptr<DebugMenu_Window_Base>>::iterator t_it = this->child_list.begin();t_it != t_it_end;++t_it){
			(*t_it)->Draw();
		}
	}

	/** 親の削除リクエスト。取得。
	*/
	bool DebugMenu_Window_Base::GetDeleteRequest()
	{
		return false;
	}

	/** コールバック。親が接続された直後に呼び出される。
	*/
	void DebugMenu_Window_Base::CallBack_SetParent()
	{
	}
}}

