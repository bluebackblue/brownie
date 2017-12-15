

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
#include "./test12_windowmenu_log.h"


/** DEF_TEST12
*/
#if defined(DEF_TEST12)

/** constructor
*/
Test12_WindowMenu_Log::Test12_WindowMenu_Log(f32 a_offset_x,f32 a_offset_y)
	:
	NBsys::NWindowMenu::WindowMenu_Window_Base("Test12_WindowMenu_Log"),
	endrequest(false),
	titlebg()
{
	//メイン。
	this->Initialize(
		WindowMenu_Window_Base::InitItem(
			NBsys::NWindowMenu::WindowMenu_Mode::Vertical,
			NBsys::NWindowMenu::WindowMenu_Offset(a_offset_x,a_offset_y),
			NBsys::NWindowMenu::WindowMenu_Size(
				NBsys::NWindowMenu::WindowMenu_SizeType::Fix,
				400.0f,
				NBsys::NWindowMenu::WindowMenu_SizeType::StretchChild,
				-1.0f
			),
			0
		)
	);

	f32 t_title_h = 16.0f;

	//タイトル。
	{
		NBsys::NWindowMenu::WindowMenu_Window_Drag::InitItem t_titledrag_inititem(
			NBsys::NWindowMenu::WindowMenu_Mode::Horizontal,
			"title->drag",
			NBsys::NWindowMenu::WindowMenu_Offset(0.0f,0.0f),
			NBsys::NWindowMenu::WindowMenu_Size(
				NBsys::NWindowMenu::WindowMenu_SizeType::StretchParent,
				-1.0f,
				NBsys::NWindowMenu::WindowMenu_SizeType::Fix,
				t_title_h
			)
		);
		sharedptr<NBsys::NWindowMenu::WindowMenu_Window_Base> t_titledrag(new NBsys::NWindowMenu::WindowMenu_Window_Drag(t_titledrag_inititem));
		this->AddChild(t_titledrag);

		//タイトル背景。
		{
			NBsys::NWindowMenu::WindowMenu_Window_Plate::InitItem t_titlebg_inititem(
				NBsys::NWindowMenu::WindowMenu_Mode::Horizontal,
				"title",
				NBsys::NWindowMenu::WindowMenu_Offset(0.0f,0.0f),
				NBsys::NWindowMenu::WindowMenu_Size(
					NBsys::NWindowMenu::WindowMenu_SizeType::StretchParent,
					-1.0f,
					NBsys::NWindowMenu::WindowMenu_SizeType::Fix,
					t_title_h
				)
			);
			{
				t_titlebg_inititem.color = NBsys::NColor::Color_F(0.3f,0.3f,0.3f,1.0f);
				t_titlebg_inititem.texture_id = -1;
				t_titlebg_inititem.mouseblock = false;
			}
			this->titlebg = new NBsys::NWindowMenu::WindowMenu_Window_Plate(t_titlebg_inititem);
			t_titledrag->AddChild(this->titlebg);

			//タイトルラベル。
			{
				NBsys::NWindowMenu::WindowMenu_Window_Text::InitItem t_titlelabel_inititem(
					NBsys::NWindowMenu::WindowMenu_Mode::Horizontal,
					"title",
					NBsys::NWindowMenu::WindowMenu_Offset(0.0f,0.0f),
					NBsys::NWindowMenu::WindowMenu_Size(
						NBsys::NWindowMenu::WindowMenu_SizeType::StretchParent,
						-1.0f,
						NBsys::NWindowMenu::WindowMenu_SizeType::Fix,
						t_title_h
					)
				);
				{
					t_titlelabel_inititem.color = NBsys::NColor::Color_F(1.0f,0.9f,0.9f,1.0f);
					t_titlelabel_inititem.string = L"log";
				}
				sharedptr<NBsys::NWindowMenu::WindowMenu_Window_Base> t_titlelabel = new NBsys::NWindowMenu::WindowMenu_Window_Text(t_titlelabel_inititem);
				this->titlebg->AddChild(t_titlelabel);
			}
		}

		//閉じるボタン。
		{
			NBsys::NWindowMenu::WindowMenu_Window_CloseButton::InitItem t_closebutton_inititem(
				NBsys::NWindowMenu::WindowMenu_Mode::Free,
				"title->closebutton",
				NBsys::NWindowMenu::WindowMenu_Offset(0.0f,0.0f),
				NBsys::NWindowMenu::WindowMenu_Size(
					NBsys::NWindowMenu::WindowMenu_SizeType::Fix,
					t_title_h,
					NBsys::NWindowMenu::WindowMenu_SizeType::Fix,
					t_title_h
				)
			);
			{
				t_closebutton_inititem.color_nomal = NBsys::NColor::Color_F(0.3f,0.3f,0.3f,1.0f);
				t_closebutton_inititem.color_on = NBsys::NColor::Color_F(0.4f,0.4f,0.4f,1.0f);
				t_closebutton_inititem.color_ondown = NBsys::NColor::Color_F(0.3f,0.3f,1.0f,1.0f);
			}
			sharedptr<NBsys::NWindowMenu::WindowMenu_Window_Base> t_closebutton(new NBsys::NWindowMenu::WindowMenu_Window_CloseButton(t_closebutton_inititem));
			t_titledrag->AddChild(t_closebutton);
		}
	}

	//ボディー。
	{
		NBsys::NWindowMenu::WindowMenu_Window_Plate::InitItem t_body_inititem(
			NBsys::NWindowMenu::WindowMenu_Mode::Vertical,
			"body",
			NBsys::NWindowMenu::WindowMenu_Offset(0.0f,0.0f),
			NBsys::NWindowMenu::WindowMenu_Size(
				NBsys::NWindowMenu::WindowMenu_SizeType::StretchParent,
				-1.0f,
				NBsys::NWindowMenu::WindowMenu_SizeType::StretchChild,
				-1.0f
			)
		);
		{
			t_body_inititem.color = NBsys::NColor::Color_F(0.1f,0.1f,0.1f,1.0f);
			t_body_inititem.texture_id = -1;
			t_body_inititem.size.h = 256;
			t_body_inititem.mouseblock = true;
		}

		sharedptr<NBsys::NWindowMenu::WindowMenu_Window_Base> t_body(new NBsys::NWindowMenu::WindowMenu_Window_Plate(t_body_inititem));
		this->AddChild(t_body);

		{
			NBsys::NWindowMenu::WindowMenu_Window_Text::InitItem t_text_inititem(
				NBsys::NWindowMenu::WindowMenu_Mode::Horizontal,
				"text",
				NBsys::NWindowMenu::WindowMenu_Offset(0.0f,0.0f),
				NBsys::NWindowMenu::WindowMenu_Size(
					NBsys::NWindowMenu::WindowMenu_SizeType::StretchParent,
					-1.0f,
					NBsys::NWindowMenu::WindowMenu_SizeType::Fix,
					16.0f
				)
			);

			STLWString t_log[] = {
				L"[blib]platform = PLATFORM_VCWIN",
				L"[blib]rom = ROM_DEVELOP",
				L"[blib]ROM_32BIT",
				L"[blib]{0xFF,0x00,0x00,0x00} == 0x000000FF : little endian",
				L"common\\common_debug_callback.cpp(19):#if(BLIB_DEBUGASSERT_CALLBACK_ENABLE)",
			};

			NBsys::NColor::Color_F t_color[] = {
				NBsys::NColor::Color_F(1.0f,1.0f,1.0f,1.0f),
				NBsys::NColor::Color_F(1.0f,1.0f,1.0f,1.0f),
				NBsys::NColor::Color_F(1.0f,1.0f,1.0f,1.0f),
				NBsys::NColor::Color_F(1.0f,1.0f,1.0f,1.0f),
				NBsys::NColor::Color_F(1.0f,0.0f,0.0f,1.0f)
			};

			for(s32 ii=0;ii<COUNTOF(t_log);ii++){
				t_text_inititem.color = t_color[ii];
				t_text_inititem.string = t_log[ii];
				sharedptr<NBsys::NWindowMenu::WindowMenu_Window_Base> t_text(new NBsys::NWindowMenu::WindowMenu_Window_Text(t_text_inititem));
				t_body->AddChild(t_text);
			}
		}
	}
}

/** destructor
*/
Test12_WindowMenu_Log::~Test12_WindowMenu_Log()
{
}

/** 削除リクエスト。取得。
*/
bool Test12_WindowMenu_Log::CallBack_GetDeleteRequest()
{
	return this->endrequest;
}

/** 削除リクエスト。設定。
*/
void Test12_WindowMenu_Log::CallBack_SetDeleteRequest()
{
	this->endrequest = true;
}

/** アクティブ変更。
*/
void Test12_WindowMenu_Log::CallBack_ChangeActive(bool a_active)
{
	if(a_active){
		this->titlebg->color = NBsys::NColor::Color_F(0.7f,0.3f,0.3f,1.0f);
	}else{
		this->titlebg->color = NBsys::NColor::Color_F(0.3f,0.3f,0.3f,1.0f);
	}
}

#endif

