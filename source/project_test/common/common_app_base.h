#pragma once

/**
 * Copyright (c) 2017 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief コモン。フォント描画。
*/


/** include
*/
#include "../include.h"


/** include
*/
#include "./common_render2d.h"

/** include
*/
#include "../common/common_drawline.h"


/** NCommon
*/
#if(BSYS_D3D11_ENABLE)
namespace NCommon
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

		/** width
		*/
		s32 width;

		/** height
		*/
		s32 height;

		/** drawline_manager
		*/
		sharedptr<NCommon::DrawLine_Manager> drawline_manager;

		/** 初期化ステップ。
		*/
		s32 initialize_step;

		/** ラスタライザ。ステート。
		*/
		s32 rasterizerstate_cull_back_id;
		s32 rasterizerstate_cull_none_id;

		/** ブレンド。ステート。
		*/
		s32 blendstate_on_id;
		s32 blendstate_off_id;

	public:

		/** constructor
		*/
		App_Base()
			:
			window(),
			d3d11(),
			width(800),
			height(600),
			drawline_manager(),
			initialize_step(0),
			rasterizerstate_cull_back_id(-1),
			rasterizerstate_cull_none_id(-1),
			blendstate_on_id(-1),
			blendstate_off_id(-1)
		{
		}

		/** destructor
		*/
		nonvirtual ~App_Base()
		{
		}

		/** 初期化。ファイル。
		*/
		virtual void Initialize_File()
		{
			NBsys::NFile::StartSystem(2);
			NBsys::NFile::SetRoot(0,L"./project_test/test" DEF_TEST_STRING);
			NBsys::NFile::SetRoot(1,L"./project_test/common");
		}

		/** 削除。ファイル。
		*/
		virtual void Delete_File()
		{
			NBsys::NFile::EndSystemRequest();
			NBsys::NFile::EndWaitSystem();
		}

		/** 初期化。ウィンドウ。
		*/
		virtual void Initialize_Window()
		{
			std::tuple<s32,s32> t_size = NBsys::NWindow::Window::GetDesktopSize();
			this->width = std::get<0>(t_size);
			this->height = std::get<1>(t_size);

			this->window.reset(new NBsys::NWindow::Window());
			this->window->Create(L"TEST " DEF_TEST_STRING,this->width,this->height);
		}

		/** 削除。ウィンドウ。
		*/
		virtual void Delete_Window()
		{
			this->window->Delete();
			this->window.reset();
		}

		/** 初期化。d3d11。
		*/
		virtual void Initialize_D3d11()
		{
			this->d3d11.reset(new NBsys::ND3d11::D3d11());
			this->d3d11->Render_Create(this->window,this->width,this->height);
		}

		/** 削除。d3d11
		*/
		virtual void Delete_D3d11()
		{
			this->d3d11->Render_Delete();
			this->d3d11.reset();
		}

		/** 初期化。ライン描画。
		*/
		virtual void Initialize_DrawLineManager()
		{
			this->drawline_manager.reset(new NCommon::DrawLine_Manager(this->d3d11));
		}

		/** 削除。ライン描画。
		*/
		virtual void Delete_DrawLineManager()
		{
			this->drawline_manager.reset();
		}

		/** 初期化、
		*/
		void Initialize()
		{
			this->Initialize_File();
			this->Initialize_Window();
			this->Initialize_D3d11();

			this->Initialize_DrawLineManager();

			this->initialize_step = 0;
		}

		/** 更新。初期化時。
		*/
		virtual void Initialize_Update()
		{
		}

		/** 更新。
		*/
		virtual void Update(f32 a_delta)
		{
		}

		/** 描画命令呼び出し。
		*/
		virtual void Render()
		{
		}

		/** 削除。
		*/
		void Delete()
		{
			this->Delete_DrawLineManager();

			this->Delete_D3d11();
			this->Delete_Window();
			this->Delete_File();
		}

		void Main()
		{
			//パフォーマンスカウンター。
			u64 t_pcounter = PerformanceCounter::GetPerformanceCounter();

			#if(DEF_TEST_AUTO)
			f32 t_autotime = 0.0f;
			#endif

			while(true){

				this->window->Update();
				if(this->window->IsEnd() == true){
					break;
				}

				//パフォーマンスカウンター。
				float t_delta = 0.0f;
				{
					u64 t_pcounter_now = PerformanceCounter::GetPerformanceCounter();
					u64 t_pcounter_sec = PerformanceCounter::GetPerformanceSecCounter();
					t_delta = static_cast<float>(t_pcounter_now - t_pcounter) / t_pcounter_sec;
					if(t_delta <= 0.0f){
						continue;
					}
					t_pcounter = t_pcounter_now;
					#if(DEF_TEST_AUTO)
					t_autotime += t_delta;
					if(t_autotime >= 3.0f){
						break;
					}
					#endif
				}

				bool t_initialize_update = true;

				if(this->initialize_step == 0){
					bool t_next = true;

					if(this->drawline_manager){
						this->drawline_manager->Initialize_Update();
						if(this->drawline_manager->IsInitialized() == false){
							t_next = false;
						}
					}

					if(t_next == true){
						this->initialize_step++;
					}
				}else if(this->initialize_step == 1){

					//ラスタライザ。ステート。
					this->rasterizerstate_cull_back_id = this->d3d11->CreateRasterizerState(NBsys::ND3d11::D3d11_CullType::Back);
					this->rasterizerstate_cull_none_id = this->d3d11->CreateRasterizerState(NBsys::ND3d11::D3d11_CullType::None);

					//ブレンド。ステート。
					this->blendstate_on_id = this->d3d11->CreateBlendState(true);
					this->blendstate_off_id = this->d3d11->CreateBlendState(false);

					this->initialize_step++;
				}else{
					//初期化完了。
					t_initialize_update = false;
				}

				//更新。
				if(t_initialize_update){
					this->Initialize_Update();
				}else{
					this->Update(t_delta);
				}
				
				//描画命令呼び出し。
				{
					//リクエスト処理。
					this->d3d11->Render_Main();

					//ビューポート。
					this->d3d11->Render_ViewPort(0.0f,0.0f,static_cast<f32>(this->width),static_cast<f32>(this->height));

					//深度ステンシルクリア。
					this->d3d11->Render_ClearDepthStencilView();

					//クリア。
					this->d3d11->Render_ClearRenderTargetView(NBsys::NColor::Color_F(0.3f,0.3f,0.8f,1.0f));

					//描画命令呼び出し。
					if(t_initialize_update){
					}else{
						this->Render();
					}
				}

				this->d3d11->Render_Present();

			}
		}
	};
}
#endif

