

/**
 * Copyright (c) blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE.txt
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief テスト。
*/


/** include
*/
#pragma warning(push)
#pragma warning(disable:4464)
#include "../include.h"
#pragma warning(pop)


/** include
*/
#include "./common_windowmenu_log.h"


/** include
*/
#include "./common_debug_callback.h"


/** include
*/
#pragma warning(push)
#pragma warning(disable:4514 4987 4820 4625 4626 4365 5026 5027 4061 4623 4571 4774)
#include <regex>
#pragma warning(pop)


/** warning

4710 : この関数はインライン展開のために選択されましたが、コンパイラはインライン展開を実行しませんでした。

*/
#pragma warning(disable:4710)


/** NTest::NCommon
*/
#if(BSYS_WINDOWMENU_ENABLE)
#pragma warning(push)
#pragma warning(disable:4711)
namespace NTest{namespace NCommon
{
	/** constructor
	*/
	WindowMenu_Log::WindowMenu_Log(f32 a_offset_x,f32 a_offset_y)
		:
		NBsys::NWindowMenu::WindowMenu_Window_Base("WindowMenu_Log"),
		endrequest(false),
		//window_logtext
		debuglog_counter(-1)
	{
		//自分。
		{
			WindowMenu_Window_Base::InitItem t_inititem;
			t_inititem.mode = NBsys::NWindowMenu::WindowMenu_Mode::Free;
			t_inititem.size.SetW(0.0f);
			t_inititem.size.SetH(0.0f);
			this->Initialize(t_inititem);
			{
				this->clip_enable = false;
			}
		}

		//ウィンドウ。
		sharedptr<NBsys::NWindowMenu::WindowMenu_Window_Window> t_window = this->CreateChild<NBsys::NWindowMenu::WindowMenu_Window_Window>("window");

		//ウィンドウ -> サイズ変更。
		sharedptr<NBsys::NWindowMenu::WindowMenu_Window_Resize> t_window_resize = t_window->CreateChild<NBsys::NWindowMenu::WindowMenu_Window_Resize>("resize");

		//ウィンドウ -> サイズ変更 -> ボディー背景。
		sharedptr<NBsys::NWindowMenu::WindowMenu_Window_Plate> t_bodybg = t_window_resize->CreateChild<NBsys::NWindowMenu::WindowMenu_Window_Plate>("");

		//ウィンドウ -> サイズ変更 -> ボディー背景　-> ログテキスト。
		for(s32 ii=0;ii<COUNTOF(this->window_logtext);ii++){
			this->window_logtext[ii] = t_bodybg->CreateChild<NBsys::NWindowMenu::WindowMenu_Window_Text>("");
		}

		//ウィンドウ。
		{
			NBsys::NWindowMenu::WindowMenu_Window_Window::InitItem t_inititem;
			t_inititem.mode = NBsys::NWindowMenu::WindowMenu_Mode::Vertical;	//縦積み。
			t_inititem.offset.Set(a_offset_x,a_offset_y);
			t_inititem.size.SetW(300.0f);
			t_inititem.size.SetH(150.0f);
			t_window->Initialize(t_inititem);
			{
				t_window->window_title_text->string = L"ログ";

				t_window->window_title_bg->color = t_window->color_title_bg_normal;
				t_window->window_title_closebutton->color_normal = NBsys::NColor::Color_F(0.3f,0.3f,0.3f,1.0f);
				t_window->window_title_closebutton->color_on = NBsys::NColor::Color_F(0.4f,0.4f,0.4f,1.0f);
				t_window->window_title_closebutton->color_ondown = NBsys::NColor::Color_F(0.3f,0.3f,1.0f,1.0f);
				t_window->window_title_text->color = NBsys::NColor::Color_F(1.0f,1.0f,1.0f,1.0f);

				t_window->SetTitleHeight(16.0f);
				t_window->SetTitleBgColor(NBsys::NColor::Color_F(0.3f,0.3f,0.3f,1.0f),NBsys::NColor::Color_F(0.7f,0.3f,0.3f,1.0f));
			}
		}

		//ウィンドウ -> サイズ変更。
		{
			NBsys::NWindowMenu::WindowMenu_Window_Resize::InitItem t_inititem;
			t_inititem.size.SetW_StretchParent();
			t_inititem.size.SetH_StretchParent();
			t_window_resize->Initialize(t_inititem);
			{
			}
		}

		//ウィンドウ -> サイズ変更 -> ボディー背景。
		{
			NBsys::NWindowMenu::WindowMenu_Window_Plate::InitItem t_inititem;
			t_inititem.mode = NBsys::NWindowMenu::WindowMenu_Mode::Vertical;	//縦積み。
			t_inititem.size.SetW_StretchParent();
			t_inititem.size.SetH_StretchParent();
			t_bodybg->Initialize(t_inititem);
			{
				t_bodybg->color = NBsys::NColor::Color_F(0.1f,0.1f,0.1f,1.0f);
				t_bodybg->texture_id = -1;
				t_bodybg->mouseblock = true;
			}
		}

		//ウィンドウ -> サイズ変更 -> ボディー背景　-> ログテキスト。
		for(s32 ii=0;ii<COUNTOF(this->window_logtext);ii++){
			NBsys::NWindowMenu::WindowMenu_Window_Text::InitItem t_inititem;
			t_inititem.mode = NBsys::NWindowMenu::WindowMenu_Mode::Horizontal;	//横積み。
			t_inititem.size.SetW_StretchParent();
			t_inititem.size.SetH(16);
			this->window_logtext[ii]->Initialize(t_inititem);
			this->window_logtext[ii]->clip = true;
		}
	}


	/** destructor
	*/
	WindowMenu_Log::~WindowMenu_Log()
	{
	}


	/** 削除リクエスト。取得。
	*/
	bool WindowMenu_Log::CallBack_GetDeleteRequest() const
	{
		return this->endrequest;
	}


	/** 削除リクエスト。設定。
	*/
	void WindowMenu_Log::CallBack_SetDeleteRequest()
	{
		this->endrequest = true;
	}


	/** 更新処理。
	*/
	void WindowMenu_Log::CallBack_Update()
	{
		if(this->debuglog_counter != NCommon::GetDebugLogCounter()){
			this->debuglog_counter = NCommon::GetDebugLogCounter();

			s32 t_offset_index = NCommon::GetDegubLogMax() - COUNTOF(this->window_logtext) + 1;
			if(t_offset_index <= 0){
				t_offset_index = 0;
			}

			for(s32 ii=0;ii<COUNTOF(this->window_logtext);ii++){
				s32 t_read_index = t_offset_index + ii;

				this->window_logtext[ii]->string = NCommon::GetDebugLogString(t_read_index);
				this->window_logtext[ii]->color = NCommon::GetDebugLogColor(t_read_index);
			}
		}
	}


}}
#pragma warning(pop)
#endif

