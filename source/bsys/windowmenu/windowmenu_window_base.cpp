

/**
 * Copyright (c) 2016-2017 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE.txt
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief デバッグメニュー。
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
#include "./windowmenu.h"


/** include
*/
#include "./windowmenu_window_base.h"


/** warning

4710 : この関数はインライン展開のために選択されましたが、コンパイラはインライン展開を実行しませんでした。

*/
#pragma warning(disable:4710)


/** NBsys::NWindowMenu
*/
#if(BSYS_WINDOWMENU_ENABLE)
namespace NBsys{namespace NWindowMenu
{
	/** constructor
	*/
	WindowMenu_Window_Base::WindowMenu_Window_Base(const STLString& a_name,WindowMenu_WindowType::Id a_type)
		:
		enable(false),
		type(a_type),
		parent(nullptr),
		child_list(),
		name(a_name),
		z_sort(0),
		mode(WindowMenu_Mode::Free),
		offset(),
		size(),
		outrange_mouseevent(false),
		draw_enable(true),
		calc_x_fix(false),
		calc_y_fix(false),
		calc_w_fix(false),
		calc_h_fix(false),
		calc_rect(0.0f),
		calc_child_index(-1),
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
		this->enable = true;

		this->mode = a_inititem.mode;
		this->offset = a_inititem.offset;
		this->size = a_inititem.size;
		this->outrange_mouseevent = false;
		this->draw_enable = true;
		this->calc_x_fix = false;
		this->calc_y_fix = false;
		this->calc_w_fix = false;
		this->calc_h_fix = false;
		this->calc_rect.Set(0.0f);

		this->calc_child_index = -1;
		this->calc_it = STLList<sharedptr<WindowMenu_Window_Base>>::iterator();
	}


	/** 子の追加。
	*/
	void WindowMenu_Window_Base::AddChild(sharedptr<WindowMenu_Window_Base> a_window,s32 a_z_sort_add)
	{
		if(a_window->parent != nullptr){
			a_window->parent->RemoveChild(a_window);
		}

		this->child_list.push_back(a_window);
		a_window->parent = this;
		a_window->z_sort = this->z_sort + a_z_sort_add;

		//領域再計算、親子関係変更。
		GetSystemInstance()->SetChangeRect();
	}


	/** 子の削除。
	*/
	void WindowMenu_Window_Base::RemoveChild(sharedptr<WindowMenu_Window_Base> a_window)
	{
		auto t_it = std::find_if(this->child_list.cbegin(),this->child_list.cend(),
			[&](const sharedptr<WindowMenu_Window_Base> a_item){
				return (a_item.get() == a_window.get());
			}
		);

		if(t_it != this->child_list.cend()){
			this->child_list.erase(t_it);
			a_window->parent = nullptr;

			//領域再計算、親子関係変更。
			GetSystemInstance()->SetChangeRect();
		}
	}


	/** 子を探す。
	*/
	const sharedptr<WindowMenu_Window_Base>& WindowMenu_Window_Base::FindChild(const STLString& a_name) const
	{
		auto t_it_end = this->child_list.cend();

		auto t_it = std::find_if(this->child_list.cbegin(),t_it_end,
			[&](const sharedptr<WindowMenu_Window_Base> a_item){
				return (a_item->name == a_name);
			}
		);

		if(t_it != t_it_end){
			return *t_it;
		}

		for(auto t_it = this->child_list.cbegin();t_it != t_it_end;++t_it){
			decltype(auto) t_find = t_it->get()->FindChild(a_name);
			if(t_find != nullptr){
				return t_find;
			}
		}

		return sharedptr_null<WindowMenu_Window_Base>();
	}


	/** IsRange
	*/
	bool WindowMenu_Window_Base::IsRange(const Position2DType<f32> a_pos)
	{
		if((this->calc_rect.xx < a_pos.xx)&&(a_pos.xx < this->calc_rect.xx + this->calc_rect.ww)&&(this->calc_rect.yy < a_pos.yy)&&(a_pos.yy < this->calc_rect.yy + this->calc_rect.hh)){
			return true;
		}
		return false;
	}


	/** サイズ計算。
	*/
	void WindowMenu_Window_Base::Calc(STLList<WindowMenu_Window_Base*>::Type& a_work)
	{
		while(a_work.size() > 0){
			auto t_it = a_work.begin();
			while(t_it != a_work.end()){
				WindowMenu_Window_Base* t_target = *t_it;

				if(t_target->calc_x_fix == false){
					t_target->CalcX();
				}

				if(t_target->calc_y_fix == false){
					t_target->CalcY();
				}

				if(t_target->calc_w_fix == false){
					if(t_target->size.type_w == WindowMenu_SizeType::Fix){
						//固定。
						t_target->CalcW_Fix();
					}else if(t_target->size.type_w == WindowMenu_SizeType::StretchChild){
						//子に合わせる。
						t_target->CalcW_StretchChild();
					}else if(t_target->size.type_w == WindowMenu_SizeType::StretchParent){
						//親に合わせる。
						t_target->CalcW_StretchParent();
					}
				}

				if(t_target->calc_h_fix == false){
					if(t_target->size.type_h == WindowMenu_SizeType::Fix){
						//固定。
						t_target->CalcH_Fix();
					}else if(t_target->size.type_h == WindowMenu_SizeType::StretchChild){
						//子に合わせる。
						t_target->CalcH_StretchChild();
					}else if(t_target->size.type_h == WindowMenu_SizeType::StretchParent){
						//親に合わせる。
						t_target->CalcH_StretchParent();
					}
				}

				if((t_target->calc_x_fix == true)&&(t_target->calc_y_fix == true)&&(t_target->calc_w_fix == true)&&(t_target->calc_h_fix == true)){
					t_it = a_work.erase(t_it);
				}else{
					++t_it;
				}
			}
		}
	}


	/** サイズ計算。
	*/
	void WindowMenu_Window_Base::CalcRect(STLList<WindowMenu_Window_Base*>::Type& a_work)
	{
		a_work.push_back(this);

		auto t_it_end = this->child_list.cend();
		for(auto t_it = this->child_list.begin();t_it != t_it_end;++t_it){
			t_it->get()->CalcRect(a_work);
		}
	}


	/** サイズ計算。
	*/
	void WindowMenu_Window_Base::CalcX()
	{
		if(this->parent == nullptr){
			//ルート。
			this->calc_rect.xx = this->offset.xx;
			this->calc_x_fix = true;
		}else{
			if(this->parent->mode == WindowMenu_Mode::Horizontal){
				//累積。
				if(this->calc_child_index == 0){
					//累積の一番最初。
					if(this->parent->calc_x_fix == true){
						this->calc_rect.xx = this->parent->calc_rect.xx + this->offset.xx;
						this->calc_x_fix = true;
					}else{
						//親の計算待ち。
					}
				}else{
					auto t_it_prev = std::prev(this->calc_it);
					WindowMenu_Window_Base* t_prev = t_it_prev->get();
					if((t_prev->calc_x_fix == true)&&(t_prev->calc_w_fix == true)){
						this->calc_rect.xx = t_prev->calc_rect.xx + t_prev->calc_rect.ww + this->offset.xx;
						this->calc_x_fix = true;
					}else{
						//一つ前の計算待ち。
					}
				}
			}else{
				//親の位置と自分のオフセット。
				if(this->parent->calc_x_fix == true){
					this->calc_rect.xx = this->parent->calc_rect.xx + this->offset.xx;
					this->calc_x_fix = true;
				}else{
					//親の計算待ち。
				}
			}
		}
	}


	/** サイズ計算。
	*/
	void WindowMenu_Window_Base::CalcY()
	{
		if(this->parent == nullptr){
			//ルート。
			this->calc_rect.yy = this->offset.yy;
			this->calc_y_fix = true;
		}else{
			if(this->parent->mode == WindowMenu_Mode::Vertical){
				//累積。
				if(this->calc_child_index == 0){
					//累積の一番最初。
					if(this->parent->calc_y_fix == true){
						this->calc_rect.yy = this->parent->calc_rect.yy + this->offset.yy;
						this->calc_y_fix = true;
					}else{
						//親の計算待ち。
					}
				}else{
					auto t_it_prev = std::prev(this->calc_it);
					WindowMenu_Window_Base* t_prev = t_it_prev->get();
					if((t_prev->calc_y_fix == true)&&(t_prev->calc_h_fix == true)){
						this->calc_rect.yy = t_prev->calc_rect.yy + t_prev->calc_rect.hh + this->offset.yy;
						this->calc_y_fix = true;
					}else{
						//一つ前の計算待ち。
					}
				}
			}else{
				//親の位置と自分のオフセット。
				if(this->parent->calc_y_fix == true){
					this->calc_rect.yy = this->parent->calc_rect.yy + this->offset.yy;
					this->calc_y_fix = true;
				}else{
					//親の計算待ち。
				}
			}
		}
	}


	/** サイズ計算。
	*/
	void WindowMenu_Window_Base::CalcW_Fix()
	{
		//固定。
		this->calc_rect.ww = this->size.size.ww;
		this->calc_w_fix = true;
	}


	/** サイズ計算。
	*/
	void WindowMenu_Window_Base::CalcH_Fix()
	{
		//固定。
		this->calc_rect.hh = this->size.size.hh;
		this->calc_h_fix = true;
	}


	/** サイズ計算。
	*/
	void WindowMenu_Window_Base::CalcW_StretchChild()
	{
		//子に合わせる。

		if(this->mode == WindowMenu_Mode::Horizontal){
			//累積。

			auto t_it_last = get_last_iterator(this->child_list);
			if(t_it_last == this->child_list.end()){
				//子がいない。
				this->calc_rect.ww = 0.0f;
				this->calc_w_fix = true;
			}else{
				WindowMenu_Window_Base* t_last = t_it_last->get();
				if((this->calc_x_fix == true)&&(t_last->calc_x_fix == true)&&(t_last->calc_w_fix == true)){
					this->calc_rect.ww = t_last->calc_rect.xx + t_last->calc_rect.ww - this->calc_rect.xx;
					this->calc_w_fix = true;
				}else{
					//最後の計算待ち。
				}
			}
		}else{
			//子の端を検索。

			bool t_calc = true;
			f32 t_offset_xx = 0.0f;
			auto t_it_end = this->child_list.end();
			for(auto t_it = this->child_list.begin();(t_it != t_it_end)&&(t_calc == true);++t_it){
				WindowMenu_Window_Base* t_child = t_it->get();
				if((t_child->calc_x_fix == true)&&(t_child->calc_w_fix == true)){
					f32 t_temp = t_child->calc_rect.xx + t_child->calc_rect.ww;
					if(t_offset_xx < t_temp){
						t_offset_xx = t_temp;
					}
				}else{
					//子の計算待ち。
					t_calc = false;
				}
			}
			if(t_calc == true){
				if(this->calc_x_fix == true){
					this->calc_rect.ww = t_offset_xx - this->calc_rect.xx;
					this->calc_w_fix = true;
				}
			}else{
				//子の計算待ち。
			}
		}
	}


	/** サイズ計算。
	*/
	void WindowMenu_Window_Base::CalcH_StretchChild()
	{
		//子に合わせる。

		if(this->mode == WindowMenu_Mode::Vertical){
			//累積。

			auto t_it_last = get_last_iterator(this->child_list);
			if(t_it_last == this->child_list.end()){
				//子がいない。
				this->calc_rect.hh = 0.0f;
				this->calc_h_fix = true;
			}else{
				WindowMenu_Window_Base* t_last = t_it_last->get();
				if((this->calc_x_fix == true)&&(t_last->calc_x_fix == true)&&(t_last->calc_h_fix == true)){
					this->calc_rect.hh = t_last->calc_rect.yy + t_last->calc_rect.hh - this->calc_rect.yy;
					this->calc_h_fix = true;
				}else{
					//最後の計算待ち。
				}
			}
		}else{
			//子の端を検索。

			bool t_calc = true;
			f32 t_offset_yy = 0.0f;
			auto t_it_end = this->child_list.end();
			for(auto t_it = this->child_list.begin();(t_it != t_it_end)&&(t_calc == true);++t_it){
				WindowMenu_Window_Base* t_child = t_it->get();
				if((t_child->calc_x_fix == true)&&(t_child->calc_h_fix == true)){
					f32 t_temp = t_child->calc_rect.yy + t_child->calc_rect.hh;
					if(t_offset_yy < t_temp){
						t_offset_yy = t_temp;
					}
				}else{
					//子の計算待ち。
					t_calc = false;
				}
			}
			if(t_calc == true){
				if(this->calc_x_fix == true){
					this->calc_rect.hh = t_offset_yy - this->calc_rect.yy;
					this->calc_h_fix = true;
				}
			}else{
				//子の計算待ち。
			}
		}
	}


	/** サイズ計算。
	*/
	void WindowMenu_Window_Base::CalcW_StretchParent()
	{
		//親に合わせる。

		if(this->parent == nullptr){
			//親がいない。

			this->calc_rect.ww = 0.0f;
			this->calc_w_fix =  true;
		}else if(this->parent->mode == WindowMenu_Mode::Horizontal){
			//自分が累積メンバー。

			if(this->parent->calc_w_fix == true){
				s32 t_stretch_count = 0;
				f32 t_total_ww = 0.0f;
				bool t_calc = true;

				auto t_it_end = this->parent->child_list.end();
				for(auto t_it = this->parent->child_list.begin();((t_it != t_it_end)&&(t_calc == true));++t_it){
					WindowMenu_Window_Base* t_parent_child = t_it->get();

					if(t_parent_child->size.type_w == WindowMenu_SizeType::StretchParent){
						//親に合わせるを数える。
						t_stretch_count++;
					}else{
						if(t_parent_child->calc_w_fix == true){
							t_total_ww += t_parent_child->offset.xx + t_parent_child->calc_rect.ww;
						}else{
							//親の子の計算待ち。
							t_calc = false;
						}
					}
				}

				if(t_stretch_count < 1){
					t_stretch_count = 1;
				}

				if(t_calc == true){
					this->calc_rect.ww = (this->parent->calc_rect.ww - t_total_ww) / t_stretch_count;
					this->calc_w_fix = true;
				}else{
					//親の子の計算待ち。
				}
			}else{
				//親の計算待ち。
			}
		}else{
			//親に合わせる。

			if(this->parent->calc_w_fix == true){
				this->calc_rect.ww = this->parent->calc_rect.ww - this->offset.xx;
				this->calc_w_fix = true;
			}else{
				//親の計算待ち。
			}
		}
	}


	/** サイズ計算。
	*/
	void WindowMenu_Window_Base::CalcH_StretchParent()
	{
		if(this->parent == nullptr){
			//親がいない。

			this->calc_rect.hh = 0.0f;
			this->calc_h_fix =  true;
		}else if(this->parent->mode == WindowMenu_Mode::Vertical){
			//自分が累積メンバー。

			if(this->parent->calc_h_fix == true){
				s32 t_stretch_count = 0;
				f32 t_total_hh = 0.0f;
				bool t_calc = true;

				auto t_it_end = this->parent->child_list.end();
				for(auto t_it = this->parent->child_list.begin();((t_it != t_it_end)&&(t_calc == true));++t_it){
					WindowMenu_Window_Base* t_parent_child = t_it->get();

					if(t_parent_child->size.type_h == WindowMenu_SizeType::StretchParent){
						//親に合わせるを数える。
						t_stretch_count++;
					}else{
						if(t_parent_child->calc_h_fix == true){
							t_total_hh += t_parent_child->offset.yy + t_parent_child->calc_rect.hh;
						}else{
							//親の子の計算待ち。
							t_calc = false;
						}
					}
				}

				if(t_stretch_count < 1){
					t_stretch_count = 1;
				}

				if(t_calc == true){
					this->calc_rect.hh = (this->parent->calc_rect.hh - t_total_hh) / t_stretch_count;
					this->calc_h_fix = true;
				}else{
					//親の子の計算待ち。
				}
			}else{
				//親の計算待ち。
			}
		}else{
			//親に合わせる。

			if(this->parent->calc_h_fix == true){
				this->calc_rect.hh = this->parent->calc_rect.hh - this->offset.yy;
				this->calc_h_fix = true;
			}else{
				//親の計算待ち。
			}
		}
	}


	/** システムからのマウス再起処理。
	*/
	bool WindowMenu_Window_Base::System_MouseUpdate(WindowMenu_Mouse& a_mouse)
	{
		if((this->outrange_mouseevent)||(this->IsRange(a_mouse.pos))){
			//範囲内。

			//子から処理。
			auto t_it_end = this->child_list.end();
			for(auto t_it = this->child_list.begin();t_it != t_it_end;++t_it){
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

		auto t_it_end = this->child_list.end();
		for(auto t_it = this->child_list.begin();t_it != t_it_end;++t_it){
			(*t_it)->System_Update();
		}
	}


	/** システムからの描画処理。
	*/
	void WindowMenu_Window_Base::System_Draw(s32 a_z_sort)
	{
		bool t_ret = this->CallBack_Draw(a_z_sort);
		if(t_ret == true){
			//子の描画を行う。

			auto t_it_end = this->child_list.end();
			for(auto t_it = this->child_list.begin();t_it != t_it_end;++t_it){
				(*t_it)->System_Draw(a_z_sort);
			}
		}
	}


	/** システムからのアクティブ変更処理。
	*/
	void WindowMenu_Window_Base::System_ChangeActive(bool a_active)
	{
		auto t_it_end = this->child_list.end();
		for(auto t_it = this->child_list.begin();t_it != t_it_end;++t_it){
			(*t_it)->System_ChangeActive(a_active);
		}
		this->CallBack_ChangeActive(a_active);
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
	void WindowMenu_Window_Base::CallBack_Update()
	{
	}


	/** 描画処理。
	*/
	bool WindowMenu_Window_Base::CallBack_Draw(s32 /*a_z_sort*/)
	{
		//子の描画を行う。
		return true;
	}


	/** アクティブ変更。
	*/
	void WindowMenu_Window_Base::CallBack_ChangeActive(bool /*a_active*/)
	{
	}


	/** 親の削除リクエスト。取得。
	*/
	bool WindowMenu_Window_Base::CallBack_GetDeleteRequest() const
	{
		return false;
	}


	/** 削除リクエスト。設定。
	*/
	void WindowMenu_Window_Base::CallBack_SetDeleteRequest()
	{
		if(this->parent != nullptr){
			this->parent->CallBack_SetDeleteRequest();
		}
	}


	/** 計算結果のクリア。
	*/
	void WindowMenu_Window_Base::CallBack_CalcRectClear(STLList<sharedptr<WindowMenu_Window_Base>>::iterator a_it,s32 a_index)
	{
		/** 計算結果。
		*/
		this->calc_x_fix = false;
		this->calc_y_fix = false;
		this->calc_w_fix = false;
		this->calc_h_fix = false;

		/** 計算に必要な親が所持している自分のインデックス。
		*/
		this->calc_child_index = a_index;

		/** 計算に必要な親が所持している自分のイテレータ。
		*/
		this->calc_it = a_it;

		s32 t_index = 0;
		auto t_it_end = this->child_list.end();
		for(auto t_it = this->child_list.begin();t_it != t_it_end;++t_it){
			(*t_it)->CallBack_CalcRectClear(t_it,t_index);
			t_index++;
		}
	}


}}
#endif

