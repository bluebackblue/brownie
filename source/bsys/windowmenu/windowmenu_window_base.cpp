

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
		me(nullptr),
		parent(nullptr),
		mode(Mode::Free),
		child_list(),

		name(a_name),

		offset_x(-1.0f),
		offset_y(-1.0f),
		width(-1.0f),
		height(-1.0f),

		z(0),

		calc_x(-1.0f),
		calc_y(-1.0f),
		calc_w(-1.0f),
		calc_h(-1.0f),

		calc_it(),
		calc_child_index(0)
	{
	}

	/** destructor
	*/
	WindowMenu_Window_Base::~WindowMenu_Window_Base()
	{
	}

	/** SetBase
	*/
	void WindowMenu_Window_Base::Initialize(Mode::Id a_mode,f32 a_offset_x,f32 a_offset_y,f32 a_width,f32 a_height,s32 a_z)
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

		this->calc_x = -1.0f;
		this->calc_y = -1.0f;
		this->calc_w = -1.0f;
		this->calc_h = -1.0f;
	}



	/** 子の追加。
	*/
	void WindowMenu_Window_Base::AddChild(sharedptr<WindowMenu_Window_Base>& a_window)
	{
		if(a_window->parent != nullptr){
			a_window->parent->RemoveChild(a_window);
		}

		this->child_list.push_back(a_window);
		a_window->parent = this->me;
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

			this->CallBack_MouseUpdate(a_mouse);

			STLList<sharedptr<WindowMenu_Window_Base>>::iterator t_it_end = this->child_list.end();
			for(STLList<sharedptr<WindowMenu_Window_Base>>::iterator t_it = this->child_list.begin();t_it != t_it_end;++t_it){
				(*t_it)->System_MouseUpdate(a_mouse);
			}
			return true;
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
	bool WindowMenu_Window_Base::CallBack_MouseUpdate(WindowMenu_Mouse& /*a_mouse*/)
	{
		return true;
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
		/** [計算結果]自分の位置。
		*/
		this->calc_x = -1.0f;
		this->calc_y = -1.0f;

		/** [計算結果]自分のサイズ。
		*/
		this->calc_w = -1.0f;
		this->calc_h = -1.0f;

		/** 計算に必要な自分のイテレータ。
		*/
		this->calc_it = a_it;

		/** 計算に必要な自分のインデックス。
		*/
		this->calc_child_index = a_index;

		s32 t_index = 0;
		STLList<sharedptr<WindowMenu_Window_Base>>::iterator t_it_end = this->child_list.end();
		for(STLList<sharedptr<WindowMenu_Window_Base>>::iterator t_it = this->child_list.begin();t_it != t_it_end;++t_it){
			(*t_it)->CalcRectClear(t_it,t_index);
			t_index++;
		}
	}


	/** [static]サイズ計算。
	*/
	void WindowMenu_Window_Base::CalcRect(WindowMenu_Window_Base* a_window)
	{
		/*
		CalcX(a_window);
		CalcY(a_window);
		CalcW(a_window);
		CalcH(a_window);

		STLList<sharedptr<WindowMenu_Window_Base>>::iterator t_it_end = a_window->child_list.end();
		for(STLList<sharedptr<WindowMenu_Window_Base>>::iterator t_it = a_window->child_list.begin();t_it != t_it_end;++t_it){
			CalcRect(t_it->get());
		}
		*/
	}

	/** [static]サイズ計算。
	*/
	void WindowMenu_Window_Base::CalcX(WindowMenu_Window_Base* a_window)
	{
		if(a_window->calc_x < 0.0f){
			WindowMenu_Window_Base* t_parent = a_window->parent;

			if(t_parent){
				if(t_parent->mode == Mode::Free){
					//自由配置。
					a_window->calc_x = t_parent->calc_x + a_window->offset_x;
				}else if(t_parent->mode == Mode::Horizontal){
					//横積み。

					if(a_window->calc_child_index == 0){
						//一番左。
						a_window->calc_x = t_parent->calc_x + a_window->offset_x;
					}else{
						STLList<sharedptr<WindowMenu_Window_Base>>::iterator t_it_before = std::prev(a_window->calc_it);
						WindowMenu_Window_Base* t_before = t_it_before->get();

						CalcX(t_before);

						a_window->calc_x = t_before->calc_x + t_before->calc_w + a_window->offset_x;
					}
				}else if(t_parent->mode == Mode::Vertical){
					//縦積み。

					if(a_window->calc_child_index == 0){
						a_window->calc_x = t_parent->calc_x + a_window->offset_x;
					}else{
						STLList<sharedptr<WindowMenu_Window_Base>>::iterator t_it_before = std::prev(a_window->calc_it);
						WindowMenu_Window_Base* t_before = t_it_before->get();

						CalcX(t_before);

						a_window->calc_x = t_before->calc_x + a_window->offset_x;
					}
				}
			}else{
				//ルート。
				a_window->calc_x = a_window->offset_x;
			}
		}
	}

	/** [static]サイズ計算。
	*/
	void WindowMenu_Window_Base::CalcY(WindowMenu_Window_Base* a_window)
	{
		if(a_window->calc_y < 0.0f){
			WindowMenu_Window_Base* t_parent = a_window->parent;

			if(t_parent){
				if(t_parent->mode == Mode::Free){
					//自由配置。
					a_window->calc_y = t_parent->calc_y + a_window->offset_y;
				}else if(t_parent->mode == Mode::Vertical){
					//縦積み。

					if(a_window->calc_child_index == 0){
						//一番左。
						a_window->calc_y = t_parent->calc_y + a_window->offset_y;
					}else{
						STLList<sharedptr<WindowMenu_Window_Base>>::iterator t_it_before = std::prev(a_window->calc_it);
						WindowMenu_Window_Base* t_before = t_it_before->get();

						CalcY(t_before);

						a_window->calc_y = t_before->calc_y + t_before->calc_w + a_window->offset_y;
					}
				}else if(t_parent->mode == Mode::Horizontal){
					//横積み。

					if(a_window->calc_child_index == 0){
						a_window->calc_y = t_parent->calc_y + a_window->offset_y;
					}else{
						STLList<sharedptr<WindowMenu_Window_Base>>::iterator t_it_before = std::prev(a_window->calc_it);
						WindowMenu_Window_Base* t_before = t_it_before->get();

						CalcY(t_before);

						a_window->calc_y = t_before->calc_y + a_window->offset_y;
					}
				}
			}else{
				//ルート。
				a_window->calc_y = a_window->offset_y;
			}
		}
	}

	/** [static]サイズ計算。
	*/
	void WindowMenu_Window_Base::CalcW(WindowMenu_Window_Base* a_window)
	{
		if(a_window->calc_w < 0.0f){
			if(a_window->width >= 0.0f){
				//固定。
				a_window->calc_w = a_window->width;
			}else{
				//ストレッチ。
				
				WindowMenu_Window_Base* t_parent = a_window->parent;

				if(t_parent){

					if(t_parent->calc_w >= 0.0f){
						//親のサイズ計算済み。

						if(t_parent->mode == Mode::Free || t_parent->mode == Mode::Vertical){
							//自由配置。
							//縦積み。

							CalcW(t_parent);

							a_window->calc_w = t_parent->calc_w - a_window->offset_x;
						}else if(t_parent->mode == Mode::Horizontal){
							//横積み。

							//TODO:get_last_safe
							STLList<sharedptr<WindowMenu_Window_Base>>::iterator t_it_last = STLList<sharedptr<WindowMenu_Window_Base>>::get_last_safe(t_parent->child_list);
							if(t_it_last != t_parent->child_list.end()){
								//一番右の子の右端。
								s32 t_index = a_window->child_list.size() - 1;
								CalcW(t_it_last->get());
								a_window->calc_w = t_it_last->get()->offset_x + t_it_last->get()->calc_w;
							}
						}
					}

					//TODO:
					
				}else{
					//ルート。

					if(a_window->mode == Mode::Free || a_window->mode == Mode::Vertical){
						//自由配置。
						//縦積み。

						//一番右端の子を検索。
						f32 t_temp = 0.0f;
						s32 t_index = 0;
						STLList<sharedptr<WindowMenu_Window_Base>>::iterator t_it_end = a_window->child_list.end();
						for(STLList<sharedptr<WindowMenu_Window_Base>>::iterator t_it = a_window->child_list.begin();t_it != t_it_end;++t_it){
							CalcW(t_it->get());
							f32 t_offset_r = t_it->get()->offset_x + t_it->get()->calc_w;
							if(t_temp < t_offset_r){
								t_temp = t_offset_r;
							}
							t_index++;
						}
						a_window->calc_w = t_temp;
					}else if(a_window->mode == Mode::Horizontal){
						//横積み。

						//TODO:get_last_safe
						STLList<sharedptr<WindowMenu_Window_Base>>::iterator t_it_last = STLList<sharedptr<WindowMenu_Window_Base>>::get_last_safe(a_window->child_list);
						if(t_it_last != a_window->child_list.end()){
							//一番右の子の右端。
							s32 t_index = a_window->child_list.size() - 1;
							CalcW(t_it_last->get());
							a_window->calc_w = t_it_last->get()->offset_x + t_it_last->get()->calc_w;
						}else{
							a_window->calc_w = 0.0f;
						}
					}
				}
			}
		}
	}

	/** [static]サイズ計算。
	*/
	void WindowMenu_Window_Base::CalcH(WindowMenu_Window_Base* a_window)
	{
		if(a_window->calc_h < 0.0f){
			if(a_window->height >= 0.0f){
				//固定。
				a_window->calc_h = a_window->height;
			}else{
				//ストレッチ。
				
				WindowMenu_Window_Base* t_parent = a_window->parent;

				if(t_parent){

					if(t_parent->calc_h >= 0.0f){
						//親のサイズ計算済み。

						if(t_parent->mode == Mode::Free || t_parent->mode == Mode::Horizontal){
							//自由配置。
							//横積み。

							CalcW(t_parent);

							a_window->calc_h = t_parent->calc_h - a_window->offset_x;
						}else if(t_parent->mode == Mode::Vertical){
							//縦積み。

							//TODO:get_last_safe
							STLList<sharedptr<WindowMenu_Window_Base>>::iterator t_it_last = STLList<sharedptr<WindowMenu_Window_Base>>::get_last_safe(t_parent->child_list);
							if(t_it_last != t_parent->child_list.end()){
								//一番右の子の右端。
								s32 t_index = a_window->child_list.size() - 1;
								CalcW(t_it_last->get());
								a_window->calc_h = t_it_last->get()->offset_x + t_it_last->get()->calc_h;
							}
						}
					}

					//TODO:
					
				}else{
					//ルート。

					if(a_window->mode == Mode::Free || a_window->mode == Mode::Horizontal){
						//自由配置。
						//横積み。

						//一番右端の子を検索。
						f32 t_temp = 0.0f;
						s32 t_index = 0;
						STLList<sharedptr<WindowMenu_Window_Base>>::iterator t_it_end = a_window->child_list.end();
						for(STLList<sharedptr<WindowMenu_Window_Base>>::iterator t_it = a_window->child_list.begin();t_it != t_it_end;++t_it){
							CalcW(t_it->get());
							f32 t_offset_r = t_it->get()->offset_x + t_it->get()->calc_w;
							if(t_temp < t_offset_r){
								t_temp = t_offset_r;
							}
							t_index++;
						}
						a_window->calc_w = t_temp;
					}else if(a_window->mode == Mode::Vertical){
						//縦積み。

						//TODO:get_last_safe
						STLList<sharedptr<WindowMenu_Window_Base>>::iterator t_it_last = STLList<sharedptr<WindowMenu_Window_Base>>::get_last_safe(a_window->child_list);
						if(t_it_last != a_window->child_list.end()){
							//一番右の子の右端。
							s32 t_index = a_window->child_list.size() - 1;
							CalcW(t_it_last->get());
							a_window->calc_w = t_it_last->get()->offset_x + t_it_last->get()->calc_w;
						}else{
							a_window->calc_w = 0.0f;
						}
					}
				}
			}
		}
	}


}}

