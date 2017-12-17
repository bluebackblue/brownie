

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


/** DEF_TEST12
*/
#if defined(DEF_TEST12)

/** constructor
*/
Test12_WindowMenu_Log::Test12_WindowMenu_Log(f32 a_offset_x,f32 a_offset_y)
	:
	NBsys::NWindowMenu::WindowMenu_Window_Base(),
	endrequest(false),
	title_bg(),
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
	for(s32 ii=0;ii<COUNTOF(this->logtext);ii++){
		this->logtext[ii] = t_bodybg->CreateChild<NBsys::NWindowMenu::WindowMenu_Window_Text>("");
	}

	//�E�B���h�E�B
	{
		NBsys::NWindowMenu::WindowMenu_Window_Window::InitItem t_inititem;
		t_inititem.mode = NBsys::NWindowMenu::WindowMenu_Mode::Vertical;	//�c�ς݁B
		t_inititem.offset.Set(a_offset_x,a_offset_y);
		t_inititem.size.SetW(400.0f);
		t_inititem.size.SetH_StretchChild();
		t_inititem.color_title_bg_normal = NBsys::NColor::Color_F(0.3f,0.3f,0.3f,1.0f);
		t_inititem.color_title_bg_active = NBsys::NColor::Color_F(0.7f,0.3f,0.3f,1.0f);
		t_inititem.color_closebutton_nomal = NBsys::NColor::Color_F(0.3f,0.3f,0.3f,1.0f);
		t_inititem.color_closebutton_on = NBsys::NColor::Color_F(0.4f,0.4f,0.4f,1.0f);
		t_inititem.color_closebutton_ondown = NBsys::NColor::Color_F(0.3f,0.3f,1.0f,1.0f);
		t_inititem.color_title_text = NBsys::NColor::Color_F(1.0f,1.0f,1.0f,1.0f);
		t_window->Initialize(t_inititem);
		{
			this->title_bg = t_window->title_bg;
		}
	}

	//�E�B���h�E -> �{�f�B�[�w�i�B
	{
		NBsys::NWindowMenu::WindowMenu_Window_Plate::InitItem t_inititem;
		t_inititem.mode = NBsys::NWindowMenu::WindowMenu_Mode::Vertical;	//�c�ς݁B
		t_inititem.size.SetH_StretchChild();
		{
			t_inititem.color = NBsys::NColor::Color_F(0.1f,0.1f,0.1f,1.0f);
			t_inititem.texture_id = -1;
			t_inititem.mouseblock = true;
		}
		t_bodybg->Initialize(t_inititem);
	}

	//�E�B���h�E -> �{�f�B�[�w�i�@-> ���O�e�L�X�g�B
	for(s32 ii=0;ii<COUNTOF(this->logtext);ii++){
		NBsys::NWindowMenu::WindowMenu_Window_Text::InitItem t_inititem;
		t_inititem.mode = NBsys::NWindowMenu::WindowMenu_Mode::Horizontal;	//���ς݁B
		t_inititem.size.SetH(16);
		this->logtext[ii]->Initialize(t_inititem);
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

		for(s32 ii=0;ii<COUNTOF(this->logtext);ii++){
			CharToWchar(GetDebugLogString(ii),this->logtext[ii]->string);
			this->logtext[ii]->string = std::regex_replace(this->logtext[ii]->string,std::wregex(L"\n"),L" ");
			this->logtext[ii]->color = GetDebugLogColor(ii);
		}
	}
}

#endif

