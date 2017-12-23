

/**
 * Copyright (c) 2016 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief テスト。
*/


/** include
*/
#include "../include.h"


/** include
*/
#include "./test13_debug_callback.h"


/** include
*/
#include "./test13_windowmenu_log.h"


/**
*/
#include <regex>


/** DEF_TEST_INDEX
*/
#if(DEF_TEST_INDEX == 13)

/** constructor
*/
Test13_WindowMenu_Log::Test13_WindowMenu_Log(f32 a_offset_x,f32 a_offset_y)
	:
	NBsys::NWindowMenu::WindowMenu_Window_Base(),
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
			this->outrange_mouseevent = true;
		}
	}

	/** ウィンドウ。
	*/
	sharedptr<NBsys::NWindowMenu::WindowMenu_Window_Window> t_window = this->CreateChild<NBsys::NWindowMenu::WindowMenu_Window_Window>("window");

	//ウィンドウ -> ボディー背景。
	sharedptr<NBsys::NWindowMenu::WindowMenu_Window_Plate> t_bodybg = t_window->CreateChild<NBsys::NWindowMenu::WindowMenu_Window_Plate>("");

	//ウィンドウ -> ボディー背景　-> ログテキスト。
	for(s32 ii=0;ii<COUNTOF(this->window_logtext);ii++){
		this->window_logtext[ii] = t_bodybg->CreateChild<NBsys::NWindowMenu::WindowMenu_Window_Text>("");
	}

	//ウィンドウ。
	{
		NBsys::NWindowMenu::WindowMenu_Window_Window::InitItem t_inititem;
		t_inititem.mode = NBsys::NWindowMenu::WindowMenu_Mode::Vertical;	//縦積み。
		t_inititem.offset.Set(a_offset_x,a_offset_y);
		t_inititem.size.SetW(300.0f);
		t_inititem.size.SetH_StretchChild();
		t_window->Initialize(t_inititem);
		{
			t_window->window_title_text->string = L" ログ ";

			t_window->window_title_bg->color = t_window->color_title_bg_normal;
			t_window->window_title_closebutton->color_normal = NBsys::NColor::Color_F(0.3f,0.3f,0.3f,1.0f);
			t_window->window_title_closebutton->color_on = NBsys::NColor::Color_F(0.4f,0.4f,0.4f,1.0f);
			t_window->window_title_closebutton->color_ondown = NBsys::NColor::Color_F(0.3f,0.3f,1.0f,1.0f);
			t_window->window_title_text->color = NBsys::NColor::Color_F(1.0f,1.0f,1.0f,1.0f);

			t_window->SetTitleHeight(16.0f);
			t_window->SetTitleBgColor(NBsys::NColor::Color_F(0.3f,0.3f,0.3f,1.0f),NBsys::NColor::Color_F(0.7f,0.3f,0.3f,1.0f));
		}
	}

	//ウィンドウ -> ボディー背景。
	{
		NBsys::NWindowMenu::WindowMenu_Window_Plate::InitItem t_inititem;
		t_inititem.mode = NBsys::NWindowMenu::WindowMenu_Mode::Vertical;	//縦積み。
		t_inititem.size.SetH_StretchChild();

		t_bodybg->Initialize(t_inititem);
		{
			t_bodybg->color = NBsys::NColor::Color_F(0.1f,0.1f,0.1f,1.0f);
			t_bodybg->texture_id = -1;
			t_bodybg->mouseblock = true;
		}
	}

	//ウィンドウ -> ボディー背景　-> ログテキスト。
	for(s32 ii=0;ii<COUNTOF(this->window_logtext);ii++){
		NBsys::NWindowMenu::WindowMenu_Window_Text::InitItem t_inititem;
		t_inititem.mode = NBsys::NWindowMenu::WindowMenu_Mode::Horizontal;	//横積み。
		t_inititem.size.SetH(16);
		this->window_logtext[ii]->Initialize(t_inititem);
	}
}

/** destructor
*/
Test13_WindowMenu_Log::~Test13_WindowMenu_Log()
{
}

/** 削除リクエスト。取得。
*/
bool Test13_WindowMenu_Log::CallBack_GetDeleteRequest()
{
	return this->endrequest;
}

/** 削除リクエスト。設定。
*/
void Test13_WindowMenu_Log::CallBack_SetDeleteRequest()
{
	this->endrequest = true;
}

/** 更新処理。
*/
void Test13_WindowMenu_Log::CallBack_Update()
{
	if(this->debuglog_counter != GetDebugLogCounter()){
		this->debuglog_counter = GetDebugLogCounter();

		for(s32 ii=0;ii<COUNTOF(this->window_logtext);ii++){
			this->window_logtext[ii]->string = GetDebugLogString(ii);
			this->window_logtext[ii]->string = std::regex_replace(this->window_logtext[ii]->string,std::wregex(L"\n"),L" ");
			this->window_logtext[ii]->color = GetDebugLogColor(ii);
		}
	}
}

#endif

