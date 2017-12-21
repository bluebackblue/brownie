

/**
 * Copyright (c) 2016 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief �e�X�g�B
*/


/** include
*/
#include "../include.h"


/** include
*/
#include "./test12_debug_callback.h"


/** include
*/
#include "./test12_windowmenu_log.h"


/**
*/
#include <regex>


/** DEF_TEST_INDEX
*/
#if(DEF_TEST_INDEX == 12)

/** constructor
*/
Test12_WindowMenu_Log::Test12_WindowMenu_Log(f32 a_offset_x,f32 a_offset_y)
	:
	NBsys::NWindowMenu::WindowMenu_Window_Base(),
	endrequest(false),
	//window_logtext
	debuglog_counter(-1)
{
	//�����B
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

	/** �E�B���h�E�B
	*/
	sharedptr<NBsys::NWindowMenu::WindowMenu_Window_Window> t_window = this->CreateChild<NBsys::NWindowMenu::WindowMenu_Window_Window>("window");

	//�E�B���h�E -> �{�f�B�[�w�i�B
	sharedptr<NBsys::NWindowMenu::WindowMenu_Window_Plate> t_bodybg = t_window->CreateChild<NBsys::NWindowMenu::WindowMenu_Window_Plate>("");

	//�E�B���h�E -> �{�f�B�[�w�i�@-> ���O�e�L�X�g�B
	for(s32 ii=0;ii<COUNTOF(this->window_logtext);ii++){
		this->window_logtext[ii] = t_bodybg->CreateChild<NBsys::NWindowMenu::WindowMenu_Window_Text>("");
	}

	//�E�B���h�E�B
	{
		NBsys::NWindowMenu::WindowMenu_Window_Window::InitItem t_inititem;
		t_inititem.mode = NBsys::NWindowMenu::WindowMenu_Mode::Vertical;	//�c�ς݁B
		t_inititem.offset.Set(a_offset_x,a_offset_y);
		t_inititem.size.SetW(300.0f);
		t_inititem.size.SetH_StretchChild();
		t_window->Initialize(t_inititem);
		{
			t_window->window_title_text->string = L"���O";

			t_window->window_title_bg->color = t_window->color_title_bg_normal;
			t_window->window_title_closebutton->color_normal = NBsys::NColor::Color_F(0.3f,0.3f,0.3f,1.0f);
			t_window->window_title_closebutton->color_on = NBsys::NColor::Color_F(0.4f,0.4f,0.4f,1.0f);
			t_window->window_title_closebutton->color_ondown = NBsys::NColor::Color_F(0.3f,0.3f,1.0f,1.0f);
			t_window->window_title_text->color = NBsys::NColor::Color_F(1.0f,1.0f,1.0f,1.0f);

			t_window->SetTitleHeight(16.0f);
			t_window->SetTitleBgColor(NBsys::NColor::Color_F(0.3f,0.3f,0.3f,1.0f),NBsys::NColor::Color_F(0.7f,0.3f,0.3f,1.0f));
		}
	}

	//�E�B���h�E -> �{�f�B�[�w�i�B
	{
		NBsys::NWindowMenu::WindowMenu_Window_Plate::InitItem t_inititem;
		t_inititem.mode = NBsys::NWindowMenu::WindowMenu_Mode::Vertical;	//�c�ς݁B
		t_inititem.size.SetH_StretchChild();

		t_bodybg->Initialize(t_inititem);
		{
			t_bodybg->color = NBsys::NColor::Color_F(0.1f,0.1f,0.1f,1.0f);
			t_bodybg->texture_id = -1;
			t_bodybg->mouseblock = true;
		}
	}

	//�E�B���h�E -> �{�f�B�[�w�i�@-> ���O�e�L�X�g�B
	for(s32 ii=0;ii<COUNTOF(this->window_logtext);ii++){
		NBsys::NWindowMenu::WindowMenu_Window_Text::InitItem t_inititem;
		t_inititem.mode = NBsys::NWindowMenu::WindowMenu_Mode::Horizontal;	//���ς݁B
		t_inititem.size.SetH(16);
		this->window_logtext[ii]->Initialize(t_inititem);
	}
}

/** destructor
*/
Test12_WindowMenu_Log::~Test12_WindowMenu_Log()
{
}

/** �폜���N�G�X�g�B�擾�B
*/
bool Test12_WindowMenu_Log::CallBack_GetDeleteRequest()
{
	return this->endrequest;
}

/** �폜���N�G�X�g�B�ݒ�B
*/
void Test12_WindowMenu_Log::CallBack_SetDeleteRequest()
{
	this->endrequest = true;
}

/** �X�V�����B
*/
void Test12_WindowMenu_Log::CallBack_Update()
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

