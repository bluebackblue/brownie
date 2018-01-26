

/**
 * Copyright (c) blueback
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
#include "./windowmenu_window_resize.h"


/** warning

4710 : この関数はインライン展開のために選択されましたが、コンパイラはインライン展開を実行しませんでした。

*/
#pragma warning(disable:4710)


/** NBsys::NWindowMenu
*/
#if(BSYS_WINDOWMENU_ENABLE)
#pragma warning(push)
#pragma warning(disable:4711)
namespace NBsys{namespace NWindowMenu
{
	/** constructor
	*/
	WindowMenu_Window_Resize::WindowMenu_Window_Resize(const STLString& a_name)
		:
		WindowMenu_Window_Base(a_name,WindowMenu_WindowType::Drag),
		drag_flag(false),
		start_pos(0.0f),
		old_pos(0.0f),
		limit(128,32)
	{
	}


	/** destructor
	*/
	WindowMenu_Window_Resize::~WindowMenu_Window_Resize()
	{
	}


	/** Initialize
	*/
	void WindowMenu_Window_Resize::Initialize(const WindowMenu_Window_Base::InitItem& a_inititem)
	{
		WindowMenu_Window_Base::Initialize(a_inititem);
		{
			/** drag_flag
			*/
			this->drag_flag = false;

			/** start
			*/
			this->start_pos = 0.0f;

			/** old
			*/
			this->old_pos = 0.0f;
		}
	}

	/** システムからのマウス再起処理。

	a_mousefix	: true = マウスは処理済み。

	*/
	void WindowMenu_Window_Resize::System_MouseUpdate(WindowMenu_Mouse& a_mouse,bool& a_mousefix)
	{
		//自分の処理。
		this->CallBack_MouseUpdate(a_mouse,a_mousefix);

		//子から処理。
		auto t_it_end = this->child_list.end();
		for(auto t_it = this->child_list.begin();t_it != t_it_end;++t_it){
			(*t_it)->System_MouseUpdate(a_mouse,a_mousefix);
		}
	}

	/** マウス処理。

	a_mousefix	: true = マウスは処理済み。

	*/
	void WindowMenu_Window_Resize::CallBack_MouseUpdate(WindowMenu_Mouse& a_mouse,bool& a_mousefix)
	{
		if(this->drag_flag == true){
			//ドラッグ中。

			if((a_mouse.on_l == true)&&(this->parent != nullptr)){
				//追従。
				if(this->parent->size.type_w == WindowMenu_SizeType::Fix){
					f32 t_w = a_mouse.pos.xx - this->parent->offset.xx;
					if(t_w <= this->limit.ww){
						t_w = this->limit.ww;
					}
					this->parent->size.SetW(t_w);
					GetSystemInstance()->SetChangeRect();
				}
				if(this->parent->size.type_h == WindowMenu_SizeType::Fix){
					f32 t_h = a_mouse.pos.yy - this->parent->offset.yy;
					if(t_h <= this->limit.hh){
						t_h = this->limit.hh;
					}
					this->parent->size.SetH(t_h);
					GetSystemInstance()->SetChangeRect();
				}
			}else{
				//ドラッグ終了。
				this->drag_flag = false;
			}
		}

		if(a_mousefix == false){
			f32 t_x = this->calc_rect.xx + this->calc_rect.ww - a_mouse.pos.xx;
			f32 t_y = this->calc_rect.yy + this->calc_rect.hh - a_mouse.pos.yy;
			if((t_x * t_x) + (t_y * t_y) < 100.0f){
				//マウス処理。
				a_mousefix = true;

				//ドラッグ開始。
				if((this->drag_flag == false)&&(a_mouse.down_l == true)&&(this->parent != nullptr)){
					this->drag_flag = true;
					this->start_pos = a_mouse.pos;
					this->old_pos = this->parent->offset;
				}

				return;
			}
		}
	}


}}
#pragma warning(pop)
#endif

