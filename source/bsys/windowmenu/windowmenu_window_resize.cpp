

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
		old_pos(0.0f)
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
	*/
	bool WindowMenu_Window_Resize::System_MouseUpdate(WindowMenu_Mouse& a_mouse)
	{
		if((this->outrange_mouseevent)||(this->IsRange(a_mouse.pos))){
			//範囲内。

			bool t_ret = this->CallBack_InRangeMouseUpdate(a_mouse);
			if(t_ret == true){
				//マウス操作を親に伝えない。
				return true;
			}

			//子から処理。
			auto t_it_end = this->child_list.end();
			for(auto t_it = this->child_list.begin();t_it != t_it_end;++t_it){
				bool t_ret = (*t_it)->System_MouseUpdate(a_mouse);
				if(t_ret == true){
					//マウス操作を親に伝えない。
					return true;
				}
			}
		}

		//範囲外。
		return false;
	}

	/** マウス処理。
	*/
	bool WindowMenu_Window_Resize::CallBack_InRangeMouseUpdate(WindowMenu_Mouse& a_mouse)
	{
		if(a_mouse.down_l){
			//ドラッグ開始。
			if(this->parent){
				this->drag_flag = true;
				this->start_pos = a_mouse.pos;
				this->old_pos = this->parent->offset;
			}
		}

		//マウス操作を親に伝えない。
		return true;
	}


	/** 更新処理。
	*/
	void WindowMenu_Window_Resize::CallBack_Update()
	{
		if(this->drag_flag == true){
			WindowMenu_Mouse& t_mouse = GetSystemInstance()->GetMouse();
			if(t_mouse.on_l){
				//ドラッグ中。
				if(this->parent){
					if(this->parent->size.type_w == WindowMenu_SizeType::Fix){
						this->parent->size.SetW(t_mouse.pos.xx - this->parent->offset.xx);
						//this->parent->CallBack_CalcRectClear(this->calc_it,this->calc_child_index);
						//this->parent->CalcRect();
						GetSystemInstance()->SetChangeRect();
					}
				}
			}else{
				//ドラッグ終了。
				this->drag_flag = false;
			}
		}
	}


}}
#pragma warning(pop)
#endif

