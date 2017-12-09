

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


/** NBsys::NDebugMenu
*/
#if(BSYS_DEBUGMENU_ENABLE)
namespace NBsys{namespace NDebugMenu
{
	/** s_debugmenu
	*/
	sharedptr<DebugMenu> s_debugmenu;

	/** constructor
	*/
	DebugMenu::DebugMenu(sharedptr<DebugMenu_Callback_Base>& a_callback)
		:
		callback(a_callback)
	{
	}

	/** destructor
	*/
	DebugMenu::~DebugMenu()
	{
	}

	/** Update
	*/
	void DebugMenu::Update()
	{
		//削除リクエスト。
		{
			STLList<sharedptr<DebugMenu_Window_Base>>::iterator t_it = this->list.begin();
			while(t_it != this->list.end()){
				if((*t_it)->GetDeleteRequest() == true){
					t_it = this->list.erase(t_it);
				}else{
					t_it++;
				}
			}
		}

		{
			STLList<sharedptr<DebugMenu_Window_Base>>::iterator t_it_end = this->list.end();

			//表示位置計算。
			{
				for(STLList<sharedptr<DebugMenu_Window_Base>>::iterator t_it = this->list.begin();t_it != t_it_end;++t_it){
					(*t_it)->CalcRect(0.0f,0.0f);
				}
			}

			//更新。
			{
				for(STLList<sharedptr<DebugMenu_Window_Base>>::iterator t_it = this->list.begin();t_it != t_it_end;++t_it){
					(*t_it)->Update();
				}
			}
		}
	}

	/** Draw
	*/
	void DebugMenu::Draw()
	{
		STLList<sharedptr<DebugMenu_Window_Base>>::iterator t_it_end = this->list.end();
		for(STLList<sharedptr<DebugMenu_Window_Base>>::iterator t_it = this->list.begin();t_it != t_it_end;++t_it){
			(*t_it)->Draw();
		}
	}

	/** Add
	*/
	void DebugMenu::Add(const sharedptr<DebugMenu_Window_Base>& a_window)
	{
		this->list.push_back(a_window);
	}

	/** システムの開始。
	*/
	void StartSystem(sharedptr<DebugMenu_Callback_Base>& a_callback)
	{
		s_debugmenu.reset(new DebugMenu(a_callback));
	}

	/** システムの終了。
	*/
	void EndSystem()
	{
		ASSERT(s_debugmenu.use_count() == 1);
		s_debugmenu.reset();
	}

	/** システムのインスタンス取得。
	*/
	sharedptr<DebugMenu>& GetSystemInstance()
	{
		return s_debugmenu;
	}
}}
#endif

