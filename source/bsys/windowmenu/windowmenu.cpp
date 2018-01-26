

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


/** warning

4710 : この関数はインライン展開のために選択されましたが、コンパイラはインライン展開を実行しませんでした。

*/
#pragma warning(disable:4710)


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
			auto t_it = this->list.cbegin();
			while(t_it != this->list.cend()){
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
		GetSystemInstance()->callback->GetMouse_Callback(this->mouse.pos,this->mouse.on_l,this->mouse.on_r,this->mouse.down_l,this->mouse.down_r,this->mouse.up_l,this->mouse.up_r);

		{
			auto t_it_begin = this->list.cbegin();
			auto t_it_end = this->list.end();
			if(t_it_begin != t_it_end){
				//マウス更新。
				{
					bool t_mousefix = false;

					auto t_it_current = t_it_end;
					auto t_it = t_it_end;
			
					for(;;){
						t_it--;

						WindowMenu_Window_Base* t_instance = t_it->get();

						if(t_instance->enable == true){
							//有効時のみ呼び出すコールバック。
							
							t_instance->System_MouseUpdate(this->mouse,t_mousefix);
							
							if(t_mousefix == true){
								if(t_it_current == t_it_end){
									t_it_current = t_it;
								}
							}
						}
						
						if(t_it == t_it_begin){
							break;
						}
					}

					//最後尾へ移動。
					if(this->mouse.down_l || this->mouse.down_r){
						if(t_it_current != t_it_end){
							if(get_last_const_iterator(this->list) != t_it_current){
								sharedptr<WindowMenu_Window_Base> t_current = *t_it_current;
								this->list.erase(t_it_current);
								this->list.push_back(t_current);
								
								//アクティブ変更チェック。
								this->changeactive_check = true;
							}
						}
					}
				}

				//アクティブ変更チェック。
				if(this->changeactive_check  == true){
					auto t_it_last = get_last_const_iterator(this->list);

					if(t_it_last != this->list.cend()){
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
					for(auto t_it = this->list.begin();t_it != t_it_end;++t_it){
						WindowMenu_Window_Base* t_instance = t_it->get();

						if(t_instance->enable){
							//有効時のみ呼び出すコールバック。
							t_instance->System_Update();
						}
					}
				}
			}
		}

		//領域再計算、親子関係変更。
		if(this->changerect_check){
			auto t_it_end = this->list.end();
			for(auto t_it = this->list.begin();t_it != t_it_end;++t_it){
				WindowMenu_Window_Base* t_instance = t_it->get();

				if(t_instance->enable == true){
					//有効時のみ呼び出すコールバック。
					t_instance->CallBack_CalcRectClear(STLList<sharedptr<WindowMenu_Window_Base>>::iterator(),-1);
				}
			}
			{
				for(auto t_it = this->list.begin();t_it != t_it_end;++t_it){
					WindowMenu_Window_Base* t_instance = t_it->get();

					if(t_instance->enable == true){
						//有効時のみ呼び出すコールバック。

						STLList<WindowMenu_Window_Base*>::Type t_work;
						t_instance->CalcRect(t_work);
						t_instance->Calc(t_work);
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
			auto t_it_end = this->list.end();
			for(auto t_it = this->list.begin();t_it != t_it_end;++t_it){
				WindowMenu_Window_Base* t_instance = t_it->get();

				if(t_instance->enable == true){
					//有効時のみ呼び出すコールバック。
					t_instance->CallBack_CalcRectClear(STLList<sharedptr<WindowMenu_Window_Base>>::iterator(),-1);
				}
			}
			{
				for(auto t_it = this->list.begin();t_it != t_it_end;++t_it){
					WindowMenu_Window_Base* t_instance = t_it->get();

					if(t_instance->enable == true){
						//有効時のみ呼び出すコールバック。

						STLList<WindowMenu_Window_Base*>::Type t_work;
						t_instance->CalcRect(t_work);
						t_instance->Calc(t_work);
					}
				}
			}
			this->changerect_check = false;
		}

		s32 t_z_sort = 0;
		auto t_it_end = this->list.cend();
		for(auto t_it = this->list.begin();t_it != t_it_end;++t_it){
			WindowMenu_Window_Base* t_instance = t_it->get();

			if(t_instance->enable){
				//有効時のみ呼び出すコールバック。
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

