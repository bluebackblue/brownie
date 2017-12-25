

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
#include "./common_windowmenu_texture.h"


/** NTest
*/
#if(BSYS_WINDOWMENU_ENABLE)
namespace NTest{namespace NCommon
{
	/** constructor
	*/
	Common_WindowMenu_Texture::Common_WindowMenu_Texture(const STLWString& a_string,f32 a_offset_x,f32 a_offset_y,sharedptr<NBsys::ND3d11::D3d11>& a_d3d11)
		:
		NBsys::NWindowMenu::WindowMenu_Window_Base("Common_WindowMenu_Texture"),
		endrequest(false),
		window_texture(),
		d3d11(a_d3d11)
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
		sharedptr<NBsys::NWindowMenu::WindowMenu_Window_Plate> t_bodybg = t_window->CreateChild<NBsys::NWindowMenu::WindowMenu_Window_Plate>("bodybg");

		//�E�B���h�E -> �{�f�B�[�w�i -> �R���g���[���B
		sharedptr<NBsys::NWindowMenu::WindowMenu_Window_Area> t_control = t_bodybg->CreateChild<NBsys::NWindowMenu::WindowMenu_Window_Area>("control");

		//�E�B���h�E -> �{�f�B�[�w�i -> �R���g���[�� -> �{�^���G���A�B
		sharedptr<NBsys::NWindowMenu::WindowMenu_Window_Area> t_buttonarea = t_control->CreateChild<NBsys::NWindowMenu::WindowMenu_Window_Area>("buttonarea");

		//�E�B���h�E -> �{�f�B�[�w�i -> �R���g���[�� -> �{�^���G���A -> ���{�^���B
		sharedptr<NBsys::NWindowMenu::WindowMenu_Window_Button> t_lbutton = t_buttonarea->CreateChild<NBsys::NWindowMenu::WindowMenu_Window_Button>("lbutton");

		//�E�B���h�E -> �{�f�B�[�w�i -> �R���g���[�� -> �{�^���G���A -> �E�{�^���B
		sharedptr<NBsys::NWindowMenu::WindowMenu_Window_Button> t_rbutton = t_buttonarea->CreateChild<NBsys::NWindowMenu::WindowMenu_Window_Button>("rbutton");

		//�E�B���h�E -> �{�f�B�[�w�i -> �e�N�X�`���[�B
		sharedptr<NBsys::NWindowMenu::WindowMenu_Window_Plate> t_texture = t_bodybg->CreateChild<NBsys::NWindowMenu::WindowMenu_Window_Plate>("texture");

		//�E�B���h�E�B
		{
			NBsys::NWindowMenu::WindowMenu_Window_Window::InitItem t_inititem;
			t_inititem.mode = NBsys::NWindowMenu::WindowMenu_Mode::Vertical;	//�c�ς݁B
			t_inititem.offset.Set(a_offset_x,a_offset_y);
			t_inititem.size.SetW(400.0f);
			t_inititem.size.SetH_StretchChild();
			t_window->Initialize(t_inititem);
			{
				t_window->window_title_text->string = L"�e�N�X�`���[";

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

		//�E�B���h�E -> �{�f�B�[�w�i -> �R���g���[���B
		{
			NBsys::NWindowMenu::WindowMenu_Window_Area::InitItem t_inititem;
			t_inititem.mode = NBsys::NWindowMenu::WindowMenu_Mode::Vertical;	//�c�ς݁B
			t_inititem.size.SetH(32.0f);
			t_control->Initialize(t_inititem);
		}

		//�E�B���h�E -> �{�f�B�[�w�i -> �R���g���[�� -> �{�^���G���A�B
		{
			NBsys::NWindowMenu::WindowMenu_Window_Area::InitItem t_inititem;
			t_inititem.mode = NBsys::NWindowMenu::WindowMenu_Mode::Horizontal;	//���ς݁B
			t_buttonarea->Initialize(t_inititem);
		}

		//�E�B���h�E -> �{�f�B�[�w�i -> �R���g���[�� -> �{�^���G���A -> ���{�^���B
		{
			NBsys::NWindowMenu::WindowMenu_Window_Button::InitItem t_inititem;
			t_inititem.mode = NBsys::NWindowMenu::WindowMenu_Mode::Horizontal;	//���ς݁B
			t_lbutton->Initialize(t_inititem);
			{
				t_lbutton->color_normal = NBsys::NColor::Color_F(0.3f,0.3f,0.3f,1.0f);
				t_lbutton->color_on = NBsys::NColor::Color_F(0.4f,0.4f,0.4f,1.0f);
				t_lbutton->color_ondown = NBsys::NColor::Color_F(0.3f,0.3f,1.0f,1.0f);
				t_lbutton->string = L"<<<<<<<<<";
				t_lbutton->action = std::bind(&Common_WindowMenu_Texture::PushLeftButton,this);
			}
		}

		//�E�B���h�E -> �{�f�B�[�w�i -> �R���g���[�� -> �{�^���G���A -> �E�{�^���B
		{
			NBsys::NWindowMenu::WindowMenu_Window_Button::InitItem t_inititem;
			t_inititem.mode = NBsys::NWindowMenu::WindowMenu_Mode::Horizontal;	//���ς݁B
			t_rbutton->Initialize(t_inititem);
			{
				t_rbutton->color_normal = NBsys::NColor::Color_F(0.3f,0.3f,0.3f,1.0f);
				t_rbutton->color_on = NBsys::NColor::Color_F(0.4f,0.4f,0.4f,1.0f);
				t_rbutton->color_ondown = NBsys::NColor::Color_F(0.3f,0.3f,1.0f,1.0f);
				t_rbutton->string = L">>>>>>>>>";
				t_rbutton->action = std::bind(&Common_WindowMenu_Texture::PushRightButton,this);
			}
		}

		//�E�B���h�E -> �{�f�B�[�w�i -> �e�N�X�`���[�B
		{
			NBsys::NWindowMenu::WindowMenu_Window_Plate::InitItem t_inititem;
			t_inititem.mode = NBsys::NWindowMenu::WindowMenu_Mode::Horizontal;	//���ς݁B
			t_inititem.size.SetH(400);
			t_texture->Initialize(t_inititem);
			{
				t_texture->color = NBsys::NColor::Color_F(1.0f,0.0f,0.0f,1.0f);
				t_texture->texture_id = -1;
				t_texture->mouseblock = true;
			}
			this->window_texture = t_texture;
		}
	}


	/** destructor
	*/
	Common_WindowMenu_Texture::~Common_WindowMenu_Texture()
	{
	}


	/** �폜���N�G�X�g�B�擾�B
	*/
	bool Common_WindowMenu_Texture::CallBack_GetDeleteRequest()
	{
		return this->endrequest;
	}


	/** �폜���N�G�X�g�B�ݒ�B
	*/
	void Common_WindowMenu_Texture::CallBack_SetDeleteRequest()
	{
		this->endrequest = true;
	}


	/** ���{�^���B
	*/
	void Common_WindowMenu_Texture::PushLeftButton()
	{
		STLVector<s32>::Type t_list;
		this->d3d11->CreateTextureIdList(t_list);
		if(t_list.size() <= 0){
			this->window_texture->texture_id = -1;
			return;
		}

		std::sort(t_list.begin(),t_list.end());

		if(this->window_texture->texture_id < 0){
			this->window_texture->texture_id = *t_list.begin();
			return;
		}

		s32 t_texture_id = this->window_texture->texture_id;
		STLVector<s32>::const_iterator t_it_end = t_list.end();
		for(STLVector<s32>::const_iterator t_it = t_list.begin();t_it != t_it_end;++t_it){
			if(t_texture_id < *t_it){
				this->window_texture->texture_id = *t_it;
				return;
			}
		}

		this->window_texture->texture_id = *t_list.begin();
		return;
	}


	/** �E�{�^���B
	*/
	void Common_WindowMenu_Texture::PushRightButton()
	{
		STLVector<s32>::Type t_list;
		this->d3d11->CreateTextureIdList(t_list);
		if(t_list.size() <= 0){
			this->window_texture->texture_id = -1;
			return;
		}

		std::sort(t_list.begin(),t_list.end(),std::greater<int>());

		if(this->window_texture->texture_id < 0){
			this->window_texture->texture_id = *t_list.begin();
			return;
		}

		s32 t_texture_id = this->window_texture->texture_id;
		STLVector<s32>::const_iterator t_it_end = t_list.end();
		for(STLVector<s32>::const_iterator t_it = t_list.begin();t_it != t_it_end;++t_it){
			if(t_texture_id > *t_it){
				this->window_texture->texture_id = *t_it;
				return;
			}
		}

		this->window_texture->texture_id = *t_list.begin();
		return;
	}


}}
#endif

