#pragma once

/**
 * Copyright (c) 2017 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief �R�����B�t�H���g�`��B
*/


/** include
*/
#include "../include.h"


/** include
*/
#include "./common_render2d.h"
#include "./common_drawline.h"
#include "./common_drawrect.h"
#include "./common_drawfont.h"
#include "./common_pad_device.h"
#include "./common_debug_callback.h"
#include "./common_windowmenu_texture.h"
#include "./common_windowmenu_log.h"
#include "./common_windowmenu_callback.h"
#include "../autotest/autotest.h"


/** NTest::NCommon
*/
#if(BSYS_D3D11_ENABLE)
namespace NTest{namespace NCommon
{
	/** App_Base
	*/
	class App_Base
	{
	public:

		/** window
		*/
		sharedptr<NBsys::NWindow::Window> window;

		/** d3d11
		*/
		sharedptr<NBsys::ND3d11::D3d11> d3d11;

		/** pad_device
		*/
		#if(BSYS_PAD_ENABLE)
		sharedptr<NBsys::NPad::Pad_Device_Base> pad_device;
		#endif

		/** autotest
		*/
		#if(DEF_TEST_AUTO)
		sharedptr<AutoTest> autotest;
		#endif

		/** width
		*/
		s32 width;

		/** height
		*/
		s32 height;

		/** drawline
		*/
		sharedptr<NCommon::DrawLine_Manager> drawline;

		/** render2d
		*/
		sharedptr<NCommon::Render2D> render2d;

		/** material_drawrect
		*/
		sharedptr<NCommon::DrawRect_Material> material_drawrect;

		/** material_drawfont
		*/
		#if(BSYS_FONT_ENABLE)
		sharedptr<NCommon::DrawFont_Material> material_drawfont;
		#endif

		/** windowmenu_texture
		*/
		#if(BSYS_WINDOWMENU_ENABLE)
		sharedptr<NCommon::Common_WindowMenu_Texture> windowmenu_texture;
		#endif

		/** windowmenu_log
		*/
		#if(BSYS_WINDOWMENU_ENABLE)
		sharedptr<NCommon::Common_WindowMenu_Log> windowmenu_log;
		#endif

		/** �������X�e�b�v�B
		*/
		s32 initialize_step;

		/** ���X�^���C�U�B�X�e�[�g�B
		*/
		s32 rasterizerstate_cull_back_id;
		s32 rasterizerstate_cull_none_id;

		/** �u�����h�B�X�e�[�g�B
		*/
		s32 blendstate_on_id;
		s32 blendstate_off_id;

		/** �f�v�X�X�e���V���B�X�e�[�g�B
		*/
		s32 depthstencilstate_check_on_write_on_id;
		s32 depthstencilstate_check_off_write_off_id;

	public:

		/** constructor
		*/
		App_Base()
			:
			window(),
			d3d11(),
			#if(DEF_TEST_AUTO)
			autotest(),
			#endif
			width(800),
			height(600),
			drawline(),
			render2d(),
			material_drawrect(),

			#if(BSYS_FONT_ENABLE)
			material_drawfont(),
			#endif

			#if(BSYS_WINDOWMENU_ENABLE)
			windowmenu_texture(),
			windowmenu_log(),
			#endif

			initialize_step(0),
			rasterizerstate_cull_back_id(-1),
			rasterizerstate_cull_none_id(-1),
			blendstate_on_id(-1),
			blendstate_off_id(-1),
			depthstencilstate_check_on_write_on_id(-1),
			depthstencilstate_check_off_write_off_id(-1)
		{
		}

		/** destructor
		*/
		nonvirtual ~App_Base()
		{
		}

		/** �������B�t�@�C���B
		*/
		virtual void Initialize_File()
		{
			NBsys::NFile::StartSystem(2);
			NBsys::NFile::SetRoot(0,L"./project_test/test" DEF_TEST_STRING);
			NBsys::NFile::SetRoot(1,L"./project_test/common");
		}

		/** �폜�B�t�@�C���B
		*/
		virtual void Delete_File()
		{
			NBsys::NFile::EndSystemRequest();
			NBsys::NFile::EndWaitSystem();
		}

		/** �������B�p�b�h�B
		*/
		virtual void Initialize_Pad()
		{
			#if(BSYS_PAD_ENABLE)
			{
				NBsys::NPad::StartSystem(1);

				this->pad_device.reset(new NCommon::Pad_Device(this->window,this->d3d11));
				NBsys::NPad::AddDevice(this->pad_device);

				NBsys::NPad::GetVirtualPad(NCommon::Pad_Device::Type::Pad1)->AddButton(NBsys::NPad::Pad_Virtual::ButtonType::MOUSEL,NBsys::NPad::Pad_Device_Base::ButtonType::DeviceButton_14,this->pad_device);
				NBsys::NPad::GetVirtualPad(NCommon::Pad_Device::Type::Pad1)->AddButton(NBsys::NPad::Pad_Virtual::ButtonType::MOUSER,NBsys::NPad::Pad_Device_Base::ButtonType::DeviceButton_15,this->pad_device);
				NBsys::NPad::GetVirtualPad(NCommon::Pad_Device::Type::Pad1)->AddTouch(NBsys::NPad::Pad_Virtual::TouchType::MOUSEL,NBsys::NPad::Pad_Device_Base::TouchType::DeviceTouch_1,this->pad_device);
				NBsys::NPad::GetVirtualPad(NCommon::Pad_Device::Type::Pad1)->AddTouch(NBsys::NPad::Pad_Virtual::TouchType::MOUSER,NBsys::NPad::Pad_Device_Base::TouchType::DeviceTouch_2,this->pad_device);
				NBsys::NPad::GetVirtualPad(NCommon::Pad_Device::Type::Pad1)->SetEnable(true);
			}
			#endif
		}

		/** �폜�B�p�b�h�B
		*/
		virtual void Delete_Pad()
		{
			#if(BSYS_PAD_ENABLE)
			{
				NBsys::NPad::EndSystem();
			}
			#endif
		}

		/** �������B�E�B���h�E���j���[�B
		*/
		virtual void Initialize_WindowMenu()
		{
			#if(BSYS_WINDOWMENU_ENABLE)
			{
				NBsys::NWindowMenu::StartSystem(new NCommon::WindowMenu_Callback(this->render2d));
			}
			#endif
		}

		/** �폜�B
		*/
		virtual void Delete_WindowMenu()
		{
			#if(BSYS_WINDOWMENU_ENABLE)
			{
				NBsys::NWindowMenu::EndSystem();
			}
			#endif
		}


		/** �������B�ʐM�B
		*/
		virtual void Initialize_Winsock()
		{
			#if(BSYS_WINSOCK_ENABLE)
			{
				NBsys::NWinsock::StartSystem();
			}
			#endif
		}

		/** �폜�B�ʐM�B
		*/
		virtual void Delete_Winsock()
		{
			#if(BSYS_WINSOCK_ENABLE)
			NBsys::NWinsock::EndSystem();
			#endif
		}

		/** �������B�E�B���h�E�B
		*/
		virtual void Initialize_Window()
		{
			std::tuple<s32,s32> t_size = NBsys::NWindow::Window::GetDesktopSize();
			this->width = std::get<0>(t_size);
			this->height = std::get<1>(t_size);

			this->window.reset(new NBsys::NWindow::Window());
			this->window->Create(L"TEST " DEF_TEST_STRING,this->width,this->height);
		}

		/** �폜�B�E�B���h�E�B
		*/
		virtual void Delete_Window()
		{
			this->window->Delete();
			this->window.reset();
		}

		/** �������Bd3d11�B
		*/
		virtual void Initialize_D3d11()
		{
			this->d3d11.reset(new NBsys::ND3d11::D3d11());
			this->d3d11->Render_Create(this->window,this->width,this->height);
		}

		/** �폜�Bd3d11
		*/
		virtual void Delete_D3d11()
		{
			this->d3d11->Render_Delete();
			this->d3d11.reset();
		}

		/** �������B���C���`��B
		*/
		virtual void Initialize_DrawLine()
		{
			this->drawline.reset(new NCommon::DrawLine_Manager(this->d3d11));
		}

		/** �폜�B���C���`��B
		*/
		virtual void Delete_DrawLine()
		{
			this->drawline.reset();
		}

		/** �������B�Q�c�`��B
		*/
		virtual void Initialize_Render2D()
		{
			this->render2d.reset(new NCommon::Render2D());
		}

		/** �폜�B�Q�c�`��B
		*/
		virtual void Delete_Render2D()
		{
			this->render2d.reset();
		}

		/** �������B�}�e���A���B���N�g�`��B
		*/
		virtual void Initialize_Material_DrawRect()
		{
			this->material_drawrect.reset(new NCommon::DrawRect_Material(this->d3d11));
		}

		/** �폜�B�}�e���A���B���N�g�`��B
		*/
		virtual void Delete_Material_DrawRect()
		{
			this->material_drawrect.reset();
		}

		/** �������B�}�e���A���B�t�H���g�`��B
		*/
		virtual void Initialize_Material_DrawFont()
		{
			#if(BSYS_FONT_ENABLE)
			this->material_drawfont.reset(new NCommon::DrawFont_Material(this->d3d11));
			#endif
		}

		/** �폜�B�}�e���A���B�t�H���g�`��B
		*/
		virtual void Delete_Material_DrawFont()
		{
			#if(BSYS_FONT_ENABLE)
			this->material_drawfont.reset();
			#endif
		}

		/** �������A
		*/
		void Initialize()
		{
			#if(DEF_TEST_AUTO)
			this->autotest.reset(new AutoTest());
			#endif

			this->Initialize_Winsock();
			this->Initialize_File();
			this->Initialize_Window();
			this->Initialize_D3d11();
			this->Initialize_Pad();

			this->Initialize_DrawLine();

			this->Initialize_Render2D();
			this->Initialize_Material_DrawRect();
			this->Initialize_Material_DrawFont();

			this->Initialize_WindowMenu();

			#if(DEF_TEST_AUTO)
			this->autotest->d3d11 = this->d3d11;
			#endif

			this->initialize_step = 0;
		}

		/** �폜�B
		*/
		void Delete()
		{
			this->Delete_WindowMenu();

			this->Delete_Material_DrawFont();
			this->Delete_Material_DrawRect();
			this->Delete_Render2D();

			this->Delete_DrawLine();

			this->Delete_Pad();
			this->Delete_D3d11();
			this->Delete_Window();
			this->Delete_File();
			this->Delete_Winsock();
		}

		/** �X�V�B���������B
		*/
		virtual void Initialize_Update()
		{
		}

		/** �X�V�B
		*/
		virtual void Update(f32 a_delta)
		{
		}

		/** �`�施�ߌĂяo���B
		*/
		virtual void Render()
		{
		}

		/** ���C���B
		*/
		void Main()
		{
			//�p�t�H�[�}���X�J�E���^�[�B
			u64 t_pcounter = PerformanceCounter::GetPerformanceCounter();

			#if(DEF_TEST_AUTO)
			f32 t_autotime = 0.0f;
			#endif

			while(true){

				this->window->Update();
				if(this->window->IsEnd() == true){
					break;
				}

				//�p�t�H�[�}���X�J�E���^�[�B
				float t_delta = 0.0f;
				{
					u64 t_pcounter_now = PerformanceCounter::GetPerformanceCounter();
					u64 t_pcounter_sec = PerformanceCounter::GetPerformanceSecCounter();
					t_delta = static_cast<float>(t_pcounter_now - t_pcounter) / t_pcounter_sec;
					if(t_delta <= 0.0f){
						continue;
					}
					t_pcounter = t_pcounter_now;
				}

				bool t_initialize_update = true;

				if(this->initialize_step == 0){
					bool t_next = true;

					if(this->drawline){
						this->drawline->Initialize_Update();
						if(this->drawline->IsInitialized() == false){
							t_next = false;
						}
					}

					#if(BSYS_FONT_ENABLE)
					if(this->material_drawfont){
						this->material_drawfont->Initialize_Update();
						if(this->material_drawfont->IsInitialized() == false){
							t_next = false;
						}
					}
					#endif

					if(this->material_drawrect){
						this->material_drawrect->Initialize_Update();
						if(this->material_drawrect->IsInitialized() == false){
							t_next = false;
						}
					}

					if(t_next == true){

						this->render2d->SetMaterial(NCommon::Render2D_ItemType::Rect,this->material_drawrect);

						#if(BSYS_FONT_ENABLE)
						this->render2d->SetMaterial(NCommon::Render2D_ItemType::Font,this->material_drawfont);
						#endif

						this->initialize_step++;
					}
				}else if(this->initialize_step == 1){

					//���X�^���C�U�B�X�e�[�g�B
					this->rasterizerstate_cull_back_id = this->d3d11->CreateRasterizerState(NBsys::ND3d11::D3d11_CullType::Back);
					this->rasterizerstate_cull_none_id = this->d3d11->CreateRasterizerState(NBsys::ND3d11::D3d11_CullType::None);

					//�u�����h�B�X�e�[�g�B
					this->blendstate_on_id = this->d3d11->CreateBlendState(true);
					this->blendstate_off_id = this->d3d11->CreateBlendState(false);

					//�f�v�X�X�e���V���B�X�e�[�g�B
					this->depthstencilstate_check_on_write_on_id = this->d3d11->CreateDepthStencilState(true,true);
					this->depthstencilstate_check_off_write_off_id = this->d3d11->CreateDepthStencilState(false,false);

					this->initialize_step++;
				}else{
					//�����������B
					t_initialize_update = false;
				}

				//�X�V�B
				if(t_initialize_update){
					this->Initialize_Update();
				}else{

					//�p�b�h�B
					#if(BSYS_PAD_ENABLE)
					NBsys::NPad::Update(true);
					#endif

					//�E�B���h�E���j���[�B
					#if(BSYS_WINDOWMENU_ENABLE)
					NBsys::NWindowMenu::GetSystemInstance()->Update();
					#endif

					this->Update(t_delta);

					//�L���v�`���[�J�n�B
					#if(DEF_TEST_AUTO)
					t_autotime += t_delta;
					if(t_autotime >= 3.0f){
						if(this->autotest->action_start == false){
							this->autotest->action_start = true;
							this->autotest->capture_step = 0;
						}
					}

					if(this->autotest->action_end == true){
						//�I���B
						break;
					}
					#endif
				}
				
				//�`�施�ߌĂяo���B
				{
					//���N�G�X�g�����B
					this->d3d11->Render_Main();

					//�r���[�|�[�g�B
					this->d3d11->Render_ViewPort(0.0f,0.0f,static_cast<f32>(this->width),static_cast<f32>(this->height));

					//�[�x�X�e���V���N���A�B
					this->d3d11->Render_ClearDepthStencilView();

					//�N���A�B
					this->d3d11->Render_ClearRenderTargetView(NBsys::NColor::Color_F(0.3f,0.3f,0.8f,1.0f));

					//�`�施�ߌĂяo���B
					if(t_initialize_update){
					}else{
						this->Render();
					}
				}

				#if(DEF_TEST_AUTO)
				this->autotest->Update();
				#endif

				this->d3d11->Render_Present();

			}
		}
	};

}}
#endif

