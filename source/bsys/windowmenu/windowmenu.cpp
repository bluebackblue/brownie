

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


/** NBsys::NWindowMenu
*/
#if(BSYS_WINDOWMENU_ENABLE)
namespace NBsys{namespace NWindowMenu
{
	/** s_windowmenu
	*/
	sharedptr<WindowMenu> s_windowmenu;

	/** constructor
	*/
	WindowMenu::WindowMenu(sharedptr<WindowMenu_Callback_Base>& a_callback)
		:
		callback(a_callback)
	{
	}

	/** destructor
	*/
	WindowMenu::~WindowMenu()
	{
	}

	/** Update
	*/
	void WindowMenu::Update()
	{
		//削除リクエスト。
		{
			STLList<sharedptr<WindowMenu_Window_Base>>::iterator t_it = this->list.begin();
			while(t_it != this->list.end()){
				if((*t_it)->GetDeleteRequest() == true){
					t_it = this->list.erase(t_it);
				}else{
					t_it++;
				}
			}
		}

		{
			STLList<sharedptr<WindowMenu_Window_Base>>::iterator t_it_end = this->list.end();

			//表示位置計算。
			{
				for(STLList<sharedptr<WindowMenu_Window_Base>>::iterator t_it = this->list.begin();t_it != t_it_end;++t_it){
					(*t_it)->CalcRect(0.0f,0.0f);
				}
			}

			//マウス更新。
			{
				GetSystemInstance()->callback->GetMouse_Callback(this->mouse.x,this->mouse.y,this->mouse.on_l,this->mouse.on_r,this->mouse.down_l,this->mouse.down_r,this->mouse.up_l,this->mouse.up_r);

				STLList<sharedptr<WindowMenu_Window_Base>>::iterator t_it_begin = this->list.begin();
				STLList<sharedptr<WindowMenu_Window_Base>>::iterator t_it = this->list.end();
				if(t_it_begin != t_it_end){
					for(;;){
						t_it--;
						bool t_ret = (*t_it)->System_MouseUpdate(this->mouse);
						if(t_ret == true){
							//範囲内。
							break;
						}else if(t_it == t_it_begin){
							break;
						}
					}
				}
			}

			//更新。
			{
				for(STLList<sharedptr<WindowMenu_Window_Base>>::iterator t_it = this->list.begin();t_it != t_it_end;++t_it){
					(*t_it)->System_Update();
				}
			}
		}
	}

	/** Draw
	*/
	void WindowMenu::Draw()
	{
		STLList<sharedptr<WindowMenu_Window_Base>>::iterator t_it_end = this->list.end();
		for(STLList<sharedptr<WindowMenu_Window_Base>>::iterator t_it = this->list.begin();t_it != t_it_end;++t_it){
			(*t_it)->System_Draw();
		}
	}

	/** Add
	*/
	void WindowMenu::Add(const sharedptr<WindowMenu_Window_Base>& a_window)
	{
		this->list.push_back(a_window);
	}

	/** GetList
	*/
	STLList<sharedptr<WindowMenu_Window_Base>>::Type& WindowMenu::GetList()
	{
		return this->list;
	}

	/** GetMouse
	*/
	WindowMenu_Mouse& WindowMenu::GetMouse()
	{
		return this->mouse;
	}

	/** GetCallback
	*/
	sharedptr<WindowMenu_Callback_Base>& WindowMenu::GetCallback()
	{
		return this->callback;
	}

	/** システムの開始。
	*/
	void StartSystem(sharedptr<WindowMenu_Callback_Base>& a_callback)
	{
		s_windowmenu.reset(new WindowMenu(a_callback));
	}

	/** システムの終了。
	*/
	void EndSystem()
	{
		ASSERT(s_windowmenu.use_count() == 1);
		s_windowmenu.reset();
	}

	/** システムのインスタンス取得。
	*/
	sharedptr<WindowMenu>& GetSystemInstance()
	{
		return s_windowmenu;
	}
}}
#endif

