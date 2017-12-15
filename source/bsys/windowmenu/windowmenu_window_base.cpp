

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
#include "./windowmenu.h"


/** include
*/
#include "./windowmenu_window_base.h"


/** NBsys::NWindowMenu
*/
namespace NBsys{namespace NWindowMenu
{
	/** constructor
	*/
	WindowMenu_Window_Base::WindowMenu_Window_Base(const STLString& a_name)
		:
		parent(nullptr),

		mode(WindowMenu_Mode::Free),
		child_list(),
		name(a_name),
		offset(0.0f,0.0f),
		size(WindowMenu_SizeType::Fix,0.0f,WindowMenu_SizeType::Fix,0.0f),

		calc_x(-1.0f),
		calc_y(-1.0f),
		calc_w(-1.0f),
		calc_h(-1.0f),

		calc_child_index(0),
		calc_it(STLList<sharedptr<WindowMenu_Window_Base>>::iterator())
	{
	}

	/** destructor
	*/
	WindowMenu_Window_Base::~WindowMenu_Window_Base()
	{
	}

	/** SetBase
	*/
	void WindowMenu_Window_Base::Initialize(const InitItem& a_inititem)
	{
		this->parent = nullptr;

		this->mode = a_inititem.mode;
		this->child_list.clear();

		//this->name = "";

		this->offset = a_inititem.offset;
		this->size = a_inititem.size;

		this->calc_x = -1.0f;
		this->calc_y = -1.0f;
		this->calc_w = -1.0f;
		this->calc_h = -1.0f;

		this->calc_child_index = -1;
		this->calc_it = STLList<sharedptr<WindowMenu_Window_Base>>::iterator();
	}

	/** 子の追加。
	*/
	void WindowMenu_Window_Base::AddChild(sharedptr<WindowMenu_Window_Base>& a_window)
	{
		if(a_window->parent != nullptr){
			a_window->parent->RemoveChild(a_window);
		}

		this->child_list.push_back(a_window);
		a_window->parent = this;
	}

	/** 子の削除。
	*/
	void WindowMenu_Window_Base::RemoveChild(sharedptr<WindowMenu_Window_Base>& a_window)
	{
		STLList<sharedptr<WindowMenu_Window_Base>>::iterator t_it = std::find_if(this->child_list.begin(),this->child_list.end(),
			[&](const sharedptr<WindowMenu_Window_Base>& a_item){
				return (a_item.get() == a_window.get());
			}
		);

		if(t_it != this->child_list.end()){
			this->child_list.erase(t_it);
			a_window->parent = nullptr;
		}
	}

	/** IsRange
	*/
	bool WindowMenu_Window_Base::IsRange(f32 a_x,f32 a_y)
	{
		if((this->calc_x < a_x)&&(a_x < this->calc_x + this->calc_w)&&(this->calc_y < a_y)&&(a_y < this->calc_y + this->calc_h)){
			return true;
		}
		return false;
	}

	/** システムからのマウス再起処理。
	*/
	bool WindowMenu_Window_Base::System_MouseUpdate(WindowMenu_Mouse& a_mouse)
	{
		if(this->IsRange(a_mouse.x,a_mouse.y)){
			//範囲内。

			//子から処理。
			STLList<sharedptr<WindowMenu_Window_Base>>::iterator t_it_end = this->child_list.end();
			for(STLList<sharedptr<WindowMenu_Window_Base>>::iterator t_it = this->child_list.begin();t_it != t_it_end;++t_it){
				bool t_ret = (*t_it)->System_MouseUpdate(a_mouse);
				if(t_ret == true){
					//マウス操作を親に伝えない。
					return true;
				}
			}

			bool t_ret = this->CallBack_InRangeMouseUpdate(a_mouse);
			if(t_ret == true){
				//マウス操作を親に伝えない。
				return true;
			}
		}

		//範囲外。
		return false;
	}

	/** システムからの更新処理。
	*/
	void WindowMenu_Window_Base::System_Update()
	{
		this->CallBack_Update();

		STLList<sharedptr<WindowMenu_Window_Base>>::iterator t_it_end = this->child_list.end();
		for(STLList<sharedptr<WindowMenu_Window_Base>>::iterator t_it = this->child_list.begin();t_it != t_it_end;++t_it){
			(*t_it)->System_Update();
		}
	}

	/** システムからの描画処理。
	*/
	void WindowMenu_Window_Base::System_Draw()
	{
		this->CallBack_Draw();

		STLList<sharedptr<WindowMenu_Window_Base>>::iterator t_it_end = this->child_list.end();
		for(STLList<sharedptr<WindowMenu_Window_Base>>::iterator t_it = this->child_list.begin();t_it != t_it_end;++t_it){
			(*t_it)->System_Draw();
		}
	}

	/** マウス処理。
	*/
	bool WindowMenu_Window_Base::CallBack_InRangeMouseUpdate(WindowMenu_Mouse& /*a_mouse*/)
	{
		//マウス操作を親に伝える。
		return false;
	}

	/** 更新処理。
	*/
	bool WindowMenu_Window_Base::CallBack_Update()
	{
		return true;
	}

	/** 描画処理。
	*/
	bool WindowMenu_Window_Base::CallBack_Draw()
	{
		return true;
	}

	/** 親の削除リクエスト。取得。
	*/
	bool WindowMenu_Window_Base::GetDeleteRequest()
	{
		return false;
	}

	/** 削除リクエスト。設定。
	*/
	void WindowMenu_Window_Base::SetDeleteRequest()
	{
		if(this->parent != nullptr){
			this->parent->SetDeleteRequest();
		}
	}

	/** 計算結果のクリア。
	*/
	void WindowMenu_Window_Base::CalcRectClear(STLList<sharedptr<WindowMenu_Window_Base>>::iterator a_it,s32 a_index)
	{
		/** 計算結果。
		*/
		this->calc_x = -1.0f;
		this->calc_y = -1.0f;
		this->calc_w = -1.0f;
		this->calc_h = -1.0f;

		/** 計算に必要な親が所持している自分のインデックス。
		*/
		this->calc_child_index = a_index;

		/** 計算に必要な親が所持している自分のイテレータ。
		*/
		this->calc_it = a_it;

		s32 t_index = 0;
		STLList<sharedptr<WindowMenu_Window_Base>>::iterator t_it_end = this->child_list.end();
		for(STLList<sharedptr<WindowMenu_Window_Base>>::iterator t_it = this->child_list.begin();t_it != t_it_end;++t_it){
			(*t_it)->CalcRectClear(t_it,t_index);
			t_index++;
		}
	}


	/** サイズ計算。
	*/
	void WindowMenu_Window_Base::CalcRect()
	{
		this->CalcX(WindowMenu_SizeType::Fix);
		this->CalcY(WindowMenu_SizeType::Fix);
		this->CalcW(WindowMenu_SizeType::Fix);
		this->CalcH(WindowMenu_SizeType::Fix);

		ASSERT(this->calc_x >= 0.0f);
		ASSERT(this->calc_y >= 0.0f);
		ASSERT(this->calc_w >= 0.0f);
		ASSERT(this->calc_h >= 0.0f);

		STLList<sharedptr<WindowMenu_Window_Base>>::iterator t_it_end = this->child_list.end();
		for(STLList<sharedptr<WindowMenu_Window_Base>>::iterator t_it = this->child_list.begin();t_it != t_it_end;++t_it){
			t_it->get()->CalcRect();
		}
	}

	/** サイズ計算。
	*/
	void WindowMenu_Window_Base::CalcX(WindowMenu_SizeType::Id a_from_sizetype)
	{
		if(this->calc_x < 0.0f){
			if(this->parent){
				if((this->parent->mode == WindowMenu_Mode::Free)||(this->parent->mode == WindowMenu_Mode::Vertical)){
					//自由配置。
					//縦積み。

					this->parent->CalcX(a_from_sizetype);

					this->calc_x = this->parent->calc_x + this->offset.x;
				}else if(this->parent->mode == WindowMenu_Mode::Horizontal){
					//横積み。

					if(this->calc_child_index == 0){
						//一番左。

						this->parent->CalcX(a_from_sizetype);

						this->calc_x = this->parent->calc_x + this->offset.x;
					}else{
						STLList<sharedptr<WindowMenu_Window_Base>>::iterator t_it_before = std::prev(this->calc_it);
						WindowMenu_Window_Base* t_before = t_it_before->get();

						t_before->CalcX(a_from_sizetype);

						this->calc_x = t_before->calc_x + t_before->calc_w + this->offset.x;
					}
				}
			}else{
				//ルート。
				this->calc_x = this->offset.x;
			}
		}
	}

	/** サイズ計算。
	*/
	void WindowMenu_Window_Base::CalcY(WindowMenu_SizeType::Id a_from_sizetype)
	{
		if(this->calc_y < 0.0f){
			if(this->parent){
				if((this->parent->mode == WindowMenu_Mode::Free)||(this->parent->mode == WindowMenu_Mode::Horizontal)){
					//自由配置。
					//横積み。

					this->parent->CalcY(a_from_sizetype);

					this->calc_y = this->parent->calc_y + this->offset.y;
				}else if(this->parent->mode == WindowMenu_Mode::Vertical){
					//縦積み。

					if(this->calc_child_index == 0){
						//一番上。

						this->parent->CalcY(a_from_sizetype);

						this->calc_y = this->parent->calc_y + this->offset.y;
					}else{
						STLList<sharedptr<WindowMenu_Window_Base>>::iterator t_it_before = std::prev(this->calc_it);
						WindowMenu_Window_Base* t_before = t_it_before->get();

						t_before->CalcY(a_from_sizetype);

						this->calc_y = t_before->calc_y + t_before->calc_h + this->offset.y;
					}
				}
			}else{
				//ルート。
				this->calc_y = this->offset.y;
			}
		}
	}

	/** サイズ計算。
	*/
	void WindowMenu_Window_Base::CalcW(WindowMenu_SizeType::Id a_from_sizetype)
	{
		if(this->calc_w < 0.0f){
			if(this->size.sizetype_w == WindowMenu_SizeType::Fix){
				//固定。
				this->calc_w = this->size.w;
			}else if(this->size.sizetype_w == WindowMenu_SizeType::StretchParent){
				//■親のサイズに合わせる。

				if((a_from_sizetype == WindowMenu_SizeType::Fix)||(a_from_sizetype == WindowMenu_SizeType::StretchParent)){
				}else{
					ASSERT(0);
					this->calc_w = 0.0f;
					return;
				}

				if((this->parent->mode == WindowMenu_Mode::Free)||(this->parent->mode == WindowMenu_Mode::Vertical)){
					//自由配置。
					//縦積み。

					this->parent->CalcW(WindowMenu_SizeType::StretchParent);

					this->calc_w = this->parent->calc_w;
				}else if(this->parent->mode == WindowMenu_Mode::Horizontal){
					//横積み。

					s32 t_stretch_count = 0;
					f32 t_total = 0.0f;
					STLList<sharedptr<WindowMenu_Window_Base>>::iterator t_it_end = this->parent->child_list.end();
					for(STLList<sharedptr<WindowMenu_Window_Base>>::iterator t_it = this->parent->child_list.begin();t_it != t_it_end;++t_it){
						WindowMenu_Window_Base* t_parent_child = t_it->get();

						if(t_parent_child->size.sizetype_w == WindowMenu_SizeType::StretchParent){
							t_stretch_count++;
						}else{
							t_parent_child->CalcW(WindowMenu_SizeType::StretchParent);
							t_total += t_parent_child->offset.x + t_parent_child->calc_w;
						}
					}

					this->parent->CalcW(WindowMenu_SizeType::StretchParent);

					if(t_stretch_count<1){
						t_stretch_count = 1;
					}

					this->calc_w = (this->parent->calc_w - t_total)/t_stretch_count;
				}
			}else if(this->size.sizetype_w == WindowMenu_SizeType::StretchChild){
				//■子のサイズに合わせる。

				if((a_from_sizetype == WindowMenu_SizeType::Fix)||(a_from_sizetype == WindowMenu_SizeType::StretchChild)){
				}else{
					ASSERT(0);
					this->calc_w = 0.0f;
					return;
				}

				if((this->mode == WindowMenu_Mode::Free)||(this->mode == WindowMenu_Mode::Vertical)){
					//自由配置。
					//縦積み。

					f32 t_temp = 0.0f;
					STLList<sharedptr<WindowMenu_Window_Base>>::iterator t_it_end = this->child_list.end();
					for(STLList<sharedptr<WindowMenu_Window_Base>>::iterator t_it = this->child_list.begin();t_it != t_it_end;++t_it){
						WindowMenu_Window_Base* t_child = t_it->get();

						t_child->CalcW(WindowMenu_SizeType::StretchChild);

						f32 t_offset_r = t_child->offset.x + t_child->calc_w;
						if(t_temp < t_offset_r){
							t_temp = t_offset_r;
						}
					}
					this->calc_w = t_temp;

				}else if(this->mode == WindowMenu_Mode::Horizontal){
					//横積み。
					
					f32 t_temp = 0.0f;
					STLList<sharedptr<WindowMenu_Window_Base>>::iterator t_it_end = this->child_list.end();
					for(STLList<sharedptr<WindowMenu_Window_Base>>::iterator t_it = this->child_list.begin();t_it != t_it_end;++t_it){
						WindowMenu_Window_Base* t_child = t_it->get();

						t_child->CalcW(WindowMenu_SizeType::StretchChild);

						t_temp += t_child->offset.x + t_child->calc_w;
					}
					this->calc_w = t_temp;
				}
			}
		}
	}

	/** サイズ計算。
	*/
	void WindowMenu_Window_Base::CalcH(WindowMenu_SizeType::Id a_from_sizetype)
	{
		if(this->calc_h < 0.0f){
			if(this->size.sizetype_h == WindowMenu_SizeType::Fix){
				//固定。
				this->calc_h = this->size.h;
			}else if(this->size.sizetype_h == WindowMenu_SizeType::StretchParent){
				//■親のサイズに合わせる。

				if((a_from_sizetype == WindowMenu_SizeType::Fix)||(a_from_sizetype == WindowMenu_SizeType::StretchParent)){
				}else{
					ASSERT(0);
					this->calc_h = 0.0f;
					return;
				}

				if((this->parent->mode == WindowMenu_Mode::Free)||(this->parent->mode == WindowMenu_Mode::Horizontal)){
					//自由配置。
					//横積み。

					this->parent->CalcH(WindowMenu_SizeType::StretchParent);

					this->calc_h = this->parent->calc_h;
				}else if(this->parent->mode == WindowMenu_Mode::Vertical){
					//縦積み。

					s32 t_stretch_count = 0;
					f32 t_total = 0.0f;
					STLList<sharedptr<WindowMenu_Window_Base>>::iterator t_it_end = this->parent->child_list.end();
					for(STLList<sharedptr<WindowMenu_Window_Base>>::iterator t_it = this->parent->child_list.begin();t_it != t_it_end;++t_it){
						WindowMenu_Window_Base* t_parent_child = t_it->get();

						if(t_parent_child->size.sizetype_h == WindowMenu_SizeType::StretchParent){
							t_stretch_count++;
						}else{
							t_parent_child->CalcH(WindowMenu_SizeType::StretchParent);
							t_total += t_parent_child->offset.y + t_parent_child->calc_h;
						}
					}

					this->parent->CalcH(WindowMenu_SizeType::StretchParent);

					if(t_stretch_count<1){
						t_stretch_count = 1;
					}

					this->calc_h = (this->parent->calc_h - t_total)/t_stretch_count;
				}
			}else if(this->size.sizetype_h == WindowMenu_SizeType::StretchChild){
				//■子のサイズに合わせる。

				if((a_from_sizetype == WindowMenu_SizeType::Fix)||(a_from_sizetype == WindowMenu_SizeType::StretchChild)){
				}else{
					ASSERT(0);
					this->calc_h = 0.0f;
					return;
				}

				if((this->mode == WindowMenu_Mode::Free)||(this->mode == WindowMenu_Mode::Horizontal)){
					//自由配置。
					//横積み。

					f32 t_temp = 0.0f;
					STLList<sharedptr<WindowMenu_Window_Base>>::iterator t_it_end = this->child_list.end();
					for(STLList<sharedptr<WindowMenu_Window_Base>>::iterator t_it = this->child_list.begin();t_it != t_it_end;++t_it){
						WindowMenu_Window_Base* t_child = t_it->get();

						t_child->CalcH(WindowMenu_SizeType::StretchChild);

						f32 t_offset_d =t_child->offset.y + t_child->calc_h;
						if(t_temp < t_offset_d){
							t_temp = t_offset_d;
						}
					}
					this->calc_h = t_temp;

				}else if(this->mode == WindowMenu_Mode::Vertical){
					//縦積み。
					
					f32 t_temp = 0.0f;
					STLList<sharedptr<WindowMenu_Window_Base>>::iterator t_it_end = this->child_list.end();
					for(STLList<sharedptr<WindowMenu_Window_Base>>::iterator t_it = this->child_list.begin();t_it != t_it_end;++t_it){
						WindowMenu_Window_Base* t_child = t_it->get();

						t_child->CalcH(WindowMenu_SizeType::StretchChild);

						t_temp += t_child->offset.y + t_child->calc_h;
					}
					this->calc_h = t_temp;
				}
			}
		}
	}

}}

