

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

			//更新。
			{
				for(STLList<sharedptr<WindowMenu_Window_Base>>::iterator t_it = this->list.begin();t_it != t_it_end;++t_it){
					(*t_it)->Update();
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
			(*t_it)->Draw();
		}
	}

	/** Add
	*/
	void WindowMenu::Add(const sharedptr<WindowMenu_Window_Base>& a_window)
	{
		this->list.push_back(a_window);
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

