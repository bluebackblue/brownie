

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


/** DEF_TEST12
*/
#if defined(DEF_TEST12)

/** constructor
*/
Test12_WindowMenu_Log::Test12_WindowMenu_Log(f32 a_offset_x,f32 a_offset_y)
	:
	NBsys::NWindowMenu::WindowMenu_Window_Base(),
	endrequest(false),
	titlebg(),
	debuglog_counter(-1)
{
	//�����B
	{
		WindowMenu_Window_Base::InitItem t_inititem;
		t_inititem.mode = NBsys::NWindowMenu::WindowMenu_Mode::Vertical;
		t_inititem.offset.Set(a_offset_x,a_offset_y);
		t_inititem.size.SetW(400.0f);
		t_inititem.size.SetH_StretchChild();
		this->Initialize(t_inititem);
	}

	//�^�C�g���h���b�O�B
	sharedptr<NBsys::NWindowMenu::WindowMenu_Window_Drag> t_titledrag = this->CreateChild<NBsys::NWindowMenu::WindowMenu_Window_Drag>();

	//�^�C�g���h���b�O -> �^�C�g���w�i�B
	this->titlebg = t_titledrag->CreateChild<NBsys::NWindowMenu::WindowMenu_Window_Plate>();

	//�^�C�g���h���b�O -> �^�C�g���w�i -> �^�C�g�����x���B
	sharedptr<NBsys::NWindowMenu::WindowMenu_Window_Text> t_titlelabel = this->titlebg->CreateChild<NBsys::NWindowMenu::WindowMenu_Window_Text>();

	//�^�C�g���h���b�O -> �^�C�g������{�^���B
	sharedptr<NBsys::NWindowMenu::WindowMenu_Window_CloseButton> t_titleclosebutton = t_titledrag->CreateChild<NBsys::NWindowMenu::WindowMenu_Window_CloseButton>();

	//�{�f�B�[�w�i�B
	sharedptr<NBsys::NWindowMenu::WindowMenu_Window_Plate> t_bodybg = this->CreateChild<NBsys::NWindowMenu::WindowMenu_Window_Plate>();

	//�{�f�B�[�w�i�@-> ���O�e�L�X�g�B
	for(s32 ii=0;ii<COUNTOF(this->logtext);ii++){
		this->logtext[ii] = t_bodybg->CreateChild<NBsys::NWindowMenu::WindowMenu_Window_Text>();
	}

	{
		f32 t_titile_h = 16.0f;
		STLWString t_titile_string = L"Log";

		//�^�C�g���h���b�O�B
		{
			NBsys::NWindowMenu::WindowMenu_Window_Drag::InitItem t_inititem;
			t_inititem.name = "titledrag";
			t_inititem.mode = NBsys::NWindowMenu::WindowMenu_Mode::Horizontal;	//���ς݁B
			t_inititem.size.SetH(t_titile_h);
			t_titledrag->Initialize(t_inititem);
		}

		//�^�C�g���h���b�O -> �^�C�g���w�i�B
		{
			NBsys::NWindowMenu::WindowMenu_Window_Plate::InitItem t_inititem;
			t_inititem.name = "titledrag->titlebg";
			t_inititem.mode = NBsys::NWindowMenu::WindowMenu_Mode::Horizontal;	//���ς݁B
			{
				t_inititem.color = NBsys::NColor::Color_F(0.3f,0.3f,0.3f,1.0f);
				t_inititem.texture_id = -1;
				t_inititem.mouseblock = false;
			}
			this->titlebg->Initialize(t_inititem);
		}

		//�^�C�g���h���b�O -> �^�C�g���w�i -> �^�C�g�����x���B
		{
			NBsys::NWindowMenu::WindowMenu_Window_Text::InitItem t_inititem;
			t_inititem.name = "titledrag->titlebg->titlelabel";
			t_inititem.mode = NBsys::NWindowMenu::WindowMenu_Mode::Horizontal;	//���ς݁B
			{
				t_inititem.color = NBsys::NColor::Color_F(1.0f,1.0f,1.0f,1.0f);
				t_inititem.string = t_titile_string;
			}
			t_titlelabel->Initialize(t_inititem);
		}

		//�^�C�g���h���b�O -> �^�C�g������{�^���B
		{
			NBsys::NWindowMenu::WindowMenu_Window_CloseButton::InitItem t_inititem;
			t_inititem.name = "titledrag->closebutton";
			t_inititem.mode = NBsys::NWindowMenu::WindowMenu_Mode::Horizontal;	//���ς݁B
			t_inititem.size.SetW(t_titile_h);
			t_inititem.size.SetH(t_titile_h);
			{
				t_inititem.color_nomal = NBsys::NColor::Color_F(0.3f,0.3f,0.3f,1.0f);
				t_inititem.color_on = NBsys::NColor::Color_F(0.4f,0.4f,0.4f,1.0f);
				t_inititem.color_ondown = NBsys::NColor::Color_F(0.3f,0.3f,1.0f,1.0f);
			}
			t_titleclosebutton->Initialize(t_inititem);
		}

		//�{�f�B�[�w�i�B
		{
			NBsys::NWindowMenu::WindowMenu_Window_Plate::InitItem t_inititem;
			t_inititem.name = "bodybg";
			t_inititem.mode = NBsys::NWindowMenu::WindowMenu_Mode::Vertical;	//�c�ς݁B
			t_inititem.size.SetH_StretchChild();
			{
				t_inititem.color = NBsys::NColor::Color_F(0.1f,0.1f,0.1f,1.0f);
				t_inititem.texture_id = -1;
				t_inititem.mouseblock = true;
			}
			t_bodybg->Initialize(t_inititem);
		}

		//�{�f�B�[�w�i�@-> ���O�e�L�X�g�B
		for(s32 ii=0;ii<COUNTOF(this->logtext);ii++){
			NBsys::NWindowMenu::WindowMenu_Window_Text::InitItem t_inititem;
			t_inititem.name = "bodybg->logtext";
			t_inititem.mode = NBsys::NWindowMenu::WindowMenu_Mode::Horizontal;	//���ς݁B
			t_inititem.size.SetH(16);
			this->logtext[ii]->Initialize(t_inititem);
		}
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

/** �A�N�e�B�u�ύX�B
*/
void Test12_WindowMenu_Log::CallBack_ChangeActive(bool a_active)
{
	if(a_active){
		this->titlebg->color = NBsys::NColor::Color_F(0.7f,0.3f,0.3f,1.0f);
	}else{
		this->titlebg->color = NBsys::NColor::Color_F(0.3f,0.3f,0.3f,1.0f);
	}
}

/** �X�V�����B
*/
void Test12_WindowMenu_Log::CallBack_Update()
{
	if(this->debuglog_counter != GetDebugLogCounter()){
		this->debuglog_counter = GetDebugLogCounter();

		for(s32 ii=0;ii<COUNTOF(this->logtext);ii++){
			CharToWchar(GetDebugLogString(ii),this->logtext[ii]->string);
			this->logtext[ii]->color = GetDebugLogColor(ii);
		}
	}
}

#endif

