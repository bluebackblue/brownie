

/**
 * Copyright (c) 2017 blueback
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
	WindowMenu::WindowMenu(sharedptr<WindowMenu_Callback_Base> a_callback)
		:
		callback(a_callback),
		list(),
		mouse(),
		active(),
		changeactive_check(true),
		changerect_check(true)
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
				if((*t_it)->CallBack_GetDeleteRequest() == true){
					t_it = this->list.erase(t_it);

					//アクティブ変更チェック。
					this->changeactive_check = true;
				}else{
					t_it++;
				}
			}
		}

		//マウスの値取得。
		GetSystemInstance()->callback->GetMouse_Callback(this->mouse.x,this->mouse.y,this->mouse.on_l,this->mouse.on_r,this->mouse.down_l,this->mouse.down_r,this->mouse.up_l,this->mouse.up_r);

		{
			STLList<sharedptr<WindowMenu_Window_Base>>::iterator t_it_begin = this->list.begin();
			STLList<sharedptr<WindowMenu_Window_Base>>::iterator t_it_end = this->list.end();
			if(t_it_begin != t_it_end){
				//マウス更新。
				{
					STLList<sharedptr<WindowMenu_Window_Base>>::iterator t_it_movetolast = t_it_end;
					STLList<sharedptr<WindowMenu_Window_Base>>::iterator t_it = t_it_end;
			
					for(;;){
						t_it--;

						WindowMenu_Window_Base* t_instance = t_it->get();

						if(t_instance->enable == true){
							
							//無効時は呼び出さないコールバック。
							bool t_ret = t_instance->System_MouseUpdate(this->mouse);
							if(t_ret == true){
								//マウス操作を次に伝えない。

								//最後尾へ移動。
								if(this->mouse.down_l || this->mouse.down_r){
									STLList<sharedptr<WindowMenu_Window_Base>>::iterator t_it_last = STLList<sharedptr<WindowMenu_Window_Base>>::get_last(this->list);
									if(t_it != t_it_last){
										t_it_movetolast = t_it;
									}
								}

								break;
							}
						}
						
						if(t_it == t_it_begin){
							break;
						}
					}

					//最後尾へ移動。
					if(t_it_movetolast != t_it_end){
						sharedptr<WindowMenu_Window_Base> t_active = *t_it_movetolast;
						
						this->list.erase(t_it_movetolast);
						this->list.push_back(t_active);

						//アクティブ変更チェック。
						this->changeactive_check = true;

					}
				}

				//アクティブ変更チェック。
				if(this->changeactive_check  == true){
					STLList<sharedptr<WindowMenu_Window_Base>>::iterator t_it_last = STLList<sharedptr<WindowMenu_Window_Base>>::get_last(this->list);

					if(t_it_last != this->list.end()){
						if(this->active.get() != (*t_it_last).get()){
							//アクティブ解除。
							if(this->active){
								this->active->System_ChangeActive(false);
							}

							this->active = *t_it_last;
							
							//アクティブ設定。
							if(this->active){
								this->active->System_ChangeActive(true);
							}
						}
					}else{
						//リストが空。
						this->active.reset();
					}
				}

				//更新。
				{
					for(STLList<sharedptr<WindowMenu_Window_Base>>::iterator t_it = this->list.begin();t_it != t_it_end;++t_it){
						WindowMenu_Window_Base* t_instance = t_it->get();

						if(t_instance->enable){
							//無効時は呼び出さないコールバック。
							t_instance->System_Update();
						}
					}
				}
			}
		}

		//領域再計算、親子関係変更。
		if(this->changerect_check){
			STLList<sharedptr<WindowMenu_Window_Base>>::iterator t_it_end = this->list.end();
			for(STLList<sharedptr<WindowMenu_Window_Base>>::iterator t_it = this->list.begin();t_it != t_it_end;++t_it){
				WindowMenu_Window_Base* t_instance = t_it->get();

				if(t_instance->enable == true){
					//無効時は呼び出さないコールバック。
					t_instance->CallBack_CalcRectClear(STLList<sharedptr<WindowMenu_Window_Base>>::iterator(),-1);
				}
			}
			{
				for(STLList<sharedptr<WindowMenu_Window_Base>>::iterator t_it = this->list.begin();t_it != t_it_end;++t_it){
					WindowMenu_Window_Base* t_instance = t_it->get();

					if(t_instance->enable == true){
						//無効時は呼び出さないコールバック。
						t_instance->CalcRect();
					}
				}
			}
			this->changerect_check = false;
		}
	}


	/** Draw
	*/
	void WindowMenu::Draw(s32 a_z_sort_add)
	{
		//領域再計算、親子関係変更。
		if(this->changerect_check){
			STLList<sharedptr<WindowMenu_Window_Base>>::iterator t_it_end = this->list.end();
			for(STLList<sharedptr<WindowMenu_Window_Base>>::iterator t_it = this->list.begin();t_it != t_it_end;++t_it){
				WindowMenu_Window_Base* t_instance = t_it->get();

				if(t_instance->enable == true){
					//無効時は呼び出さないコールバック。
					t_instance->CallBack_CalcRectClear(STLList<sharedptr<WindowMenu_Window_Base>>::iterator(),-1);
				}
			}
			{
				for(STLList<sharedptr<WindowMenu_Window_Base>>::iterator t_it = this->list.begin();t_it != t_it_end;++t_it){
					WindowMenu_Window_Base* t_instance = t_it->get();

					if(t_instance->enable == true){
						//無効時は呼び出さないコールバック。
						t_instance->CalcRect();
					}
				}
			}
			this->changerect_check = false;
		}

		s32 t_z_sort = 0;
		STLList<sharedptr<WindowMenu_Window_Base>>::iterator t_it_end = this->list.end();
		for(STLList<sharedptr<WindowMenu_Window_Base>>::iterator t_it = this->list.begin();t_it != t_it_end;++t_it){
			WindowMenu_Window_Base* t_instance = t_it->get();

			if(t_instance->enable){
				//無効時は呼び出さないコールバック。
				t_instance->System_Draw(t_z_sort);
			}

			t_z_sort += a_z_sort_add;
		}
	}


	/** Add
	*/
	void WindowMenu::Add(const sharedptr<WindowMenu_Window_Base> a_window)
	{
		this->list.push_back(a_window);

		//アクティブ変更チェック。
		this->changeactive_check = true;
	}


	/** 領域再計算、親子関係変更。
	*/
	void WindowMenu::SetChangeRect()
	{
		this->changerect_check = true;
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
	void StartSystem(sharedptr<WindowMenu_Callback_Base> a_callback)
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

