

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

		calc_x_fix(false),
		calc_y_fix(false),
		calc_w_fix(false),
		calc_h_fix(false),

		calc_x(0.0f),
		calc_y(0.0f),
		calc_w(0.0f),
		calc_h(0.0f)
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

		this->calc_x_fix = false;
		this->calc_y_fix = false;
		this->calc_w_fix = false;
		this->calc_h_fix = false;

		this->calc_x = 0.0f;
		this->calc_y = 0.0f;
		this->calc_w = 0.0f;
		this->calc_h = 0.0f;
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
		STLVector<sharedptr<WindowMenu_Window_Base>>::iterator t_it = std::find(this->child_list.begin(),this->child_list.end(),a_window);
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

			STLVector<sharedptr<WindowMenu_Window_Base>>::iterator t_it_end = this->child_list.end();
			for(STLVector<sharedptr<WindowMenu_Window_Base>>::iterator t_it = this->child_list.begin();t_it != t_it_end;++t_it){
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

		STLVector<sharedptr<WindowMenu_Window_Base>>::iterator t_it_end = this->child_list.end();
		for(STLVector<sharedptr<WindowMenu_Window_Base>>::iterator t_it = this->child_list.begin();t_it != t_it_end;++t_it){
			(*t_it)->System_Update();
		}
	}

	/** システムからの描画処理。
	*/
	void WindowMenu_Window_Base::System_Draw()
	{
		this->CallBack_Draw();

		STLVector<sharedptr<WindowMenu_Window_Base>>::iterator t_it_end = this->child_list.end();
		for(STLVector<sharedptr<WindowMenu_Window_Base>>::iterator t_it = this->child_list.begin();t_it != t_it_end;++t_it){
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
	void WindowMenu_Window_Base::CalcRectClear()
	{
		/** [計算結果]自分の位置。
		*/
		this->calc_x = -1.0f;
		this->calc_y = -1.0f;
		this->calc_x_fix = false;
		this->calc_y_fix = false;

		/** [計算結果]自分のサイズ。
		*/
		this->calc_w = -1.0f;
		this->calc_h = -1.0f;
		this->calc_x_fix = false;
		this->calc_y_fix = false;

		STLVector<sharedptr<WindowMenu_Window_Base>>::iterator t_it_end = this->child_list.end();
		for(STLVector<sharedptr<WindowMenu_Window_Base>>::iterator t_it = this->child_list.begin();t_it != t_it_end;++t_it){
			(*t_it)->CalcRectClear();
		}
	}

	/** サイズ計算。
	*/
	void WindowMenu_Window_Base::CalcRect()
	{
		while((this->calc_x_fix == false)||(this->calc_y_fix == false)||(this->calc_w_fix == false)||(this->calc_h_fix == false)){
			if(this->calc_x_fix == false){
				this->CalcX();
			}
			if(this->calc_y_fix == false){
				this->CalcY();
			}
			if(this->calc_w_fix == false){
				this->CalcWidth();
			}
			if(this->calc_h_fix == false){
				this->CalcHeight();
			}
		}
	}

	/** サイズ計算。
	*/
	void WindowMenu_Window_Base::CalcX()
	{
		if(this->calc_x_fix == false){
			if(this->parent == nullptr){
				this->calc_x = this->offset_x;
				this->calc_x_fix = true;
			}else{
				if(this->parent->calc_x_fix == false){
					this->parent->CalcX();
				}

				if(this->parent->calc_x_fix == true){
					switch(this->parent->mode){
					case Mode::Free:
					case Mode::Vertical:
						{
							//自由配置。
							//縦積み。

							this->calc_x = this->parent->calc_x + this->offset_x;
							this->calc_x_fix = true;

							//std::find(this->parent->child_list.begin(),this->parent->child_list.end(),[](const sharedptr<WindowMenu_Window_Base>& a_item){
							//});
						}break;
					}
				}
			}
		}
	}

	/** サイズ計算。
	*/
	void WindowMenu_Window_Base::CalcY()
	{
		if(this->calc_y_fix == false){
			if(this->parent == nullptr){
				this->calc_y = this->offset_y;
				this->calc_y_fix = true;
			}else{
				if(this->parent->calc_y_fix == false){
					this->parent->CalcY();
				}
				if(this->parent->calc_y_fix == true){
					this->calc_y = this->parent->calc_y + this->offset_y;
					this->calc_y_fix = true;
				}
			}
		}
	}

	/** サイズ計算。
	*/
	void WindowMenu_Window_Base::CalcWidth()
	{
		if(this->calc_w_fix == false){
			if(this->width >= 0.0f){
				//固定。
				this->calc_w = this->width;
				this->calc_w_fix = true;
			}else{
				//自動。

				if(this->parent == nullptr){

					STLVector<sharedptr<WindowMenu_Window_Base>>::iterator t_it_end = this->child_list.end();
					switch(this->mode){
					case Mode::Free:
					case Mode::Vertical:
						{
							//自由配置。
							//縦積み。

							f32 t_width = 0.0f;

							for(STLVector<sharedptr<WindowMenu_Window_Base>>::iterator t_it = this->child_list.begin();t_it != t_it_end;++t_it){
								WindowMenu_Window_Base* t_child = t_it->get();
								if(t_child->calc_w_fix == false){
									t_child->CalcWidth();
								}
								if(t_child->calc_w_fix == true && t_child->calc_x_fix == true){
									f32 t_temp_w = t_child->calc_w + t_child->calc_x;

									if(t_child->calc_w > t_width){
										t_width = t_child->calc_w;
									}
								}else{
									t_width = -1.0f;
									break;
								}
							}

							if(t_width >= 0.0f){
								this->calc_w = t_width;
								this->calc_w_fix = true;
							}
						}break;
					case Mode::Horizontal:
						{
							//横済み。

							f32 t_width = 0.0f;

							for(STLVector<sharedptr<WindowMenu_Window_Base>>::iterator t_it = this->child_list.begin();t_it != t_it_end;++t_it){
								WindowMenu_Window_Base* t_child = t_it->get();
								if(t_child->calc_w_fix == false){
									t_child->CalcWidth();
								}
								if(t_child->calc_w_fix == true){
									if(t_child->calc_w > t_width){
										t_width += t_child->calc_w;
									}
								}else{
									t_width = -1.0f;
									break;
								}
							}

							if(t_width >= 0.0f){
								this->calc_w = t_width;
								this->calc_w_fix = true;
							}
						}break;
					}
				}else{
					if(this->parent->calc_w_fix == false){
						this->parent->CalcWidth();
					}
					if(this->parent->calc_w_fix == true){
						if(this->child_list.size() == 1){
							this->calc_w = this->parent->calc_w - this->calc_x;
							this->calc_w_fix = true;
						}
					}

				}
			}
		}
	}

	/** サイズ計算。
	*/
	void WindowMenu_Window_Base::CalcHeight()
	{
	}
}}




























	#if(0)
	/** CalcWidth
	*/
	f32 WindowMenu_Window_Base::CalcWidth()
	{

	}
	/** CalcHeight
	*/
	f32 WindowMenu_Window_Base::CalcHeight()
	{
		//[設定値]自分のサイズ。
		f32 t_height = this->height;

		if(t_height < 0.0f){
			//サイズ自動計算。

			//親のサイズから。
			t_height = this->CalcHeightFromParent();

			//子のサイズから。
			if(t_height < 0.0f){
				t_height = this->CalcHeightFromChild();
			}

			//自分以外のサイズから。
			if(t_height >= 0.0f){
				if(this->parent){
					if(this->parent->child_list.size() > 1){
						if(this->parent->mode == Mode::Horizontal){
							t_height = this->CalcHeightFromOtherItem(t_height);
						}
					}
				}
			}
		}

		ASSERT(t_height >= 0.0f);
		return t_height;
	}

	/** CalcWidthFromParent
	*/
	f32 WindowMenu_Window_Base::CalcWidthFromParent()
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
	f32 WindowMenu_Window_Base::CalcHeightFromParent()
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
	f32 WindowMenu_Window_Base::CalcWidthFromChild()
	{
		//自分のサイズを使用。
		f32 t_width = this->width;

		//子のサイズを使用。
		if(t_width < 0.0f){

			t_width = 0.0f;

			STLVector<sharedptr<WindowMenu_Window_Base>>::iterator t_it_end = this->child_list.end();

			switch(this->mode){
			case Mode::Free:
				{
					//自由配置。
					for(STLVector<sharedptr<WindowMenu_Window_Base>>::iterator t_it = this->child_list.begin();t_it != t_it_end;++t_it){
						f32 t_width_temp = (*t_it)->CalcWidthFromChild();
						if(t_width_temp > t_width){
							t_width = t_width_temp;
						}
					}
				}break;
			case Mode::Vertical:
				{
					//縦。
					for(STLVector<sharedptr<WindowMenu_Window_Base>>::iterator t_it = this->child_list.begin();t_it != t_it_end;++t_it){
						f32 t_width_temp = (*t_it)->CalcWidthFromChild();
						if(t_width_temp > t_width){
							t_width = t_width_temp;
						}
					}
				}break;
			case Mode::Horizontal:
				{
					//横。
					for(STLVector<sharedptr<WindowMenu_Window_Base>>::iterator t_it = this->child_list.begin();t_it != t_it_end;++t_it){
						t_width += (*t_it)->CalcWidthFromChild();
					}
				}break;
			}
		}

		return t_width;
	}

	/** CalcHeightFromChild
	*/
	f32 WindowMenu_Window_Base::CalcHeightFromChild()
	{
		//自分のサイズを使用。
		f32 t_height = this->height;

		//子のサイズを使用。
		if(t_height < 0.0f){

			t_height = 0.0f;

			STLVector<sharedptr<WindowMenu_Window_Base>>::iterator t_it_end = this->child_list.end();

			switch(this->mode){
			case Mode::Free:
				{
					//自由配置。
					for(STLVector<sharedptr<WindowMenu_Window_Base>>::iterator t_it = this->child_list.begin();t_it != t_it_end;++t_it){
						f32 t_height_temp = (*t_it)->CalcHeightFromChild();
						if(t_height_temp > t_height){
							t_height = t_height_temp;
						}
					}
				}break;
			case Mode::Vertical:
				{
					//縦。
					for(STLVector<sharedptr<WindowMenu_Window_Base>>::iterator t_it = this->child_list.begin();t_it != t_it_end;++t_it){
						t_height += (*t_it)->CalcHeightFromChild();
					}
				}break;
			case Mode::Horizontal:
				{
					//横。
					for(STLVector<sharedptr<WindowMenu_Window_Base>>::iterator t_it = this->child_list.begin();t_it != t_it_end;++t_it){
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

	/** CalcWidthFromOtherItem
	*/
	f32 WindowMenu_Window_Base::CalcWidthFromOtherItem(f32 a_all_width)
	{
		f32 t_width = 0.0f;

		if(this->parent){

			STLVector<sharedptr<WindowMenu_Window_Base>>::iterator t_it_end = this->parent->child_list.end();

			switch(this->parent->mode){
			case Mode::Free:
				{
					//自由配置。
					t_width = a_all_width;
				}break;
			case Mode::Vertical:
				{
					//縦。
					t_width = a_all_width;
				}break;
			case Mode::Horizontal:
				{
					//横。
					for(STLVector<sharedptr<WindowMenu_Window_Base>>::iterator t_it = this->parent->child_list.begin();t_it != t_it_end;++t_it){
						f32 t_temp_width = (*t_it)->CalcWidthFromChild();
						if(t_temp_width >= 0.0f){
							t_width += t_temp_width;
						}else{
							ASSERT(t_it->get() == this);
						}
					}
				}break;
			}
		}

		return t_width;
	}

	/** CalcHeightFromOtherItem
	*/
	f32 WindowMenu_Window_Base::CalcHeightFromOtherItem(f32 a_all_height)
	{
		f32 t_height = 0.0f;

		if(this->parent){

			STLVector<sharedptr<WindowMenu_Window_Base>>::iterator t_it_end = this->parent->child_list.end();

			switch(this->parent->mode){
			case Mode::Free:
				{
					//自由配置。
					t_height = a_all_height;
				}break;
			case Mode::Vertical:
				{
					//縦。
					for(STLVector<sharedptr<WindowMenu_Window_Base>>::iterator t_it = this->parent->child_list.begin();t_it != t_it_end;++t_it){
						f32 t_temp_height = (*t_it)->CalcHeightFromChild();
						if(t_temp_height >= 0.0f){
							t_height += t_temp_height;
						}else{
							ASSERT(t_it->get() == this);
						}
					}
				}break;
			case Mode::Horizontal:
				{
					//横。
					t_height = a_all_height;
				}break;
			}
		}

		return t_height;
	}

	#endif

	/** 親の横幅設定値を検索。
	*/
	//f32 WindowMenu_Window_Base::SearchParentWidth()
	//{
	//	if(this->width >= 0.0f){
	//		return this->width;
	//	}
	//
	//	if(this->parent != nullptr){
	//		return this->parent->SearchParentWidth();
	//	}
	//
	//	return -1;
	//}

	/** 親の縦幅設定値を検索。
	*/
	//f32 WindowMenu_Window_Base::SearchParentHeight()
	//{
	//	if(this->height >= 0.0f){
	//		return this->height;
	//	}
	//
	//	if(this->parent != nullptr){
	//		return this->parent->SearchParentHeight();
	//	}
	//
	//	return -1;
	//}

	/** CalcWidth
	*/
	//void WindowMenu_Window_Base::CalcWidth()
	//{
	//	if(this->calc_w < 0.0f){
	//		if(this->width >= 0.0f){
	//			this->calc_w = this->width;
	//		}else{
	//			f32 t_total_width = this->SearchParentWidth();
	//			if(t_total_width >= 0.0f){
	//				if(this->parent){
	//					if(this->parent->mode == Mode::Horizontal){
	//						if(this->parent->child_list.size() >= 2){
	//							//this->calc_w = t_total_width - t_other_width;
	//						}else{
	//							this->calc_w = t_total_width;
	//						}
	//					}else{
	//						this->calc_w = t_total_width;
	//					}
	//				}else{
	//					this->calc_w = t_total_width;
	//				}
	//			}else{
	//				//this->calc_w = t_child_total;
	//			}
	//		}
	//	}
	//}

	/** CalcHeight
	*/
	//void WindowMenu_Window_Base::CalcHeight()
	//{
	//	if(this->calc_w < 0.0f){
	//		if(this->height >= 0.0f){
	//			this->calc_h = this->height;
	//		}else{
	//			f32 t_total_height = this->SearchParentHeight();
	//		}
	//	}
	//}


		/** 表示位置計算リクエスト。
	*/
	//void WindowMenu_Window_Base::CalcRequest()
	//{
	//	//[計算結果]親の位置。
	//	this->calc_parent_x = -1;
	//	this->calc_parent_y = -1;
	//
	//	//[計算結果]自分の位置。
	//	this->calc_x = -1;
	//	this->calc_y = -1;
	//
	//	//[計算結果]自分のサイズ。
	//	this->calc_w = -1;
	//	this->calc_h = -1;
	//}

	/** 表示位置計算。
	*/
	//void WindowMenu_Window_Base::CalcRect(f32 a_parent_offset_x,f32 a_parent_offset_y)
	//{
	//	//[計算結果]親の位置。
	//	this->calc_parent_x = a_parent_offset_x;
	//	this->calc_parent_y = a_parent_offset_y;
	//
	//	//[計算結果]自分の位置。
	//	this->calc_x = this->calc_parent_x + this->offset_x;
	//	this->calc_y = this->calc_parent_y + this->offset_y;
	//
	//	//[計算結果]自分のサイズ。
	//	if(this->calc_w < 0.0f){
	//		if(this->width >= 0.0f){
	//			this->calc_w = this->width;
	//		}else{
	//			//自動計算。
	//
	//			bool t_from_parent = false;
	//
	//			if(this->parent){
	//				if(this->parent->mode == Mode::Horizontal){
	//					if(this->parent->child_list.size() >= 2){
	//						//this->calc_w = t_total_width - t_other_width;
	//					}else{
	//						t_from_parent = true;
	//					}
	//				}else{
	//					t_from_parent = true;
	//				}
	//			}
	//
	//
	//		}
	//
	//
	//		this->CalcWidth();
	//	}
	//	if(this->calc_h < 0.0f){
	//		this->CalcHeight();
	//	}
	//
	//	STLVector<sharedptr<WindowMenu_Window_Base>>::iterator t_it_end = this->child_list.end();
	//
	//	switch(this->mode){
	//	case Mode::Free:
	//		{
	//			//自由配置。
	//			for(STLVector<sharedptr<WindowMenu_Window_Base>>::iterator t_it = this->child_list.begin();t_it != t_it_end;++t_it){
	//				(*t_it)->CalcRect(this->calc_x,this->calc_y);
	//			}
	//		}break;
	//	case Mode::Vertical:
	//		{
	//			//縦。
	//			f32 t_y = this->calc_y;
	//			for(STLVector<sharedptr<WindowMenu_Window_Base>>::iterator t_it = this->child_list.begin();t_it != t_it_end;++t_it){
	//				(*t_it)->CalcRect(this->calc_x,t_y);
	//				t_y += (*t_it)->calc_h;
	//			}
	//		}break;
	//	case Mode::Horizontal:
	//		{
	//			//横。
	//			f32 t_x = this->calc_x;
	//			for(STLVector<sharedptr<WindowMenu_Window_Base>>::iterator t_it = this->child_list.begin();t_it != t_it_end;++t_it){
	//				(*t_it)->CalcRect(t_x,this->calc_y);
	//				t_x += (*t_it)->calc_w;
	//			}
	//		}break;
	//	}
	//}