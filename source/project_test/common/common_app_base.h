#pragma once

/**
 * Copyright (c) 2016-2017 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE.txt
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief コモン。フォント描画。
*/


/** include
*/
#pragma warning(push)
#pragma warning(disable:4464)
#include "../include.h"
#pragma warning(pop)


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
#include "./common_windowmenu_buttonlist.h"
#include "./common_windowmenu_callback.h"
#include "./common_autotest.h"
#include "./common_device_index.h"
#include "./common_sound_streamcallback.h"


/** NTest::NCommon
*/
#if(BSYS_D3D11_ENABLE)
#pragma warning(push)
#pragma warning(disable:4514 4710)
namespace NTest{namespace NCommon
{
	/** App_Base
	*/
	class App_Base;


	/** App_Base_Thread
	*/
	class App_Base_Thread
	{
	private:

		/** endrequest
		*/
		AtomicValue<bool> endrequest;

	public:

		/** constructor
		*/
		App_Base_Thread()
			:
			endrequest(false)
		{
		}

		/** destructor
		*/
		~App_Base_Thread()
		{
		}

	public:

		/** 引数。
		*/
		struct ThreadArgument
		{
			/** threadname
			*/
			STLString threadname;

			/** stacksize
			*/
			size_t stacksize;

			/** priority
			*/
			s32 priority;

			/** app
			*/
			App_Base* app;

			/** constructor
			*/
			ThreadArgument()
				:
				threadname("App_Base_Thread"),
				stacksize(64 * 1024),
				priority(0),
				app(nullptr)
			{
			}

			/** destructor
			*/
			nonvirtual ~ThreadArgument()
			{
			}
		};

		/** スレッドメイン。
		*/
		void ThreadMain(ThreadArgument& a_threadargument);

		/** 終了リクエスト。
		*/
		void EndRequest()
		{
			this->endrequest.Store(true);
		}

	};


	/** App_Base
	*/
	class App_Base
	{
	public:

		/** s_instance
		*/
		sharedptr<ThreadTemplate<App_Base_Thread>> thread;

		/** window
		*/
		sharedptr<NBsys::NWindow::Window> window;

		/** d3d11
		*/
		sharedptr<NBsys::ND3d11::D3d11> d3d11;

		/** pcounter
		*/
		u64 pcounter;

		/** loop_time
		*/
		AtomicValue<f32> loop_time;

		/** pad_device
		*/
		#if(BSYS_PAD_ENABLE)
		sharedptr<NBsys::NPad::Pad_Device_Base> pad_device;
		#endif

		/** autotest
		*/
		#if(DEF_TEST_AUTO)
		sharedptr<AutoTest> autotest;
		f32 t_autotime;
		#endif

		/** size
		*/
		Size2DType<f32> size;

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
		sharedptr<NCommon::WindowMenu_Texture> windowmenu_texture;
		#endif

		/** windowmenu_log
		*/
		#if(BSYS_WINDOWMENU_ENABLE)
		sharedptr<NCommon::WindowMenu_Log> windowmenu_log;
		#endif

		/** windowmenu_buttonlist
		*/
		#if(BSYS_WINDOWMENU_ENABLE)
		sharedptr<NCommon::WindowMenu_ButtonList> windowmenu_buttonlist;
		#endif

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

		/** デプスステンシル。ステート。
		*/
		s32 depthstencilstate_check_on_write_on_id;
		s32 depthstencilstate_check_off_write_off_id;

		/** サンプラ。ステート。
		*/
		s32 samplerstate_point_id;

	public:

		/** constructor
		*/
		App_Base()
			:
			window(),
			d3d11(),
			pcounter(0),
			loop_time(0.0f),
			#if(DEF_TEST_AUTO)
			autotest(),
			autotime(0.0f),
			#endif
			size(800.0,600.0f),
			drawline(),
			render2d(),
			material_drawrect(),

			#if(BSYS_FONT_ENABLE)
			material_drawfont(),
			#endif

			#if(BSYS_WINDOWMENU_ENABLE)
			windowmenu_texture(),
			windowmenu_log(),
			windowmenu_buttonlist(),
			#endif

			initialize_step(0),
			rasterizerstate_cull_back_id(-1),
			rasterizerstate_cull_none_id(-1),
			blendstate_on_id(-1),
			blendstate_off_id(-1),
			depthstencilstate_check_on_write_on_id(-1),
			depthstencilstate_check_off_write_off_id(-1),
			samplerstate_point_id(-1)
		{
		}

		/** destructor
		*/
		virtual ~App_Base()
		{
		}

		/** 初期化。ファイル。
		*/
		virtual void Initialize_File()
		{
			NBsys::NFile::StartSystem(NCommon::DeviceIndex::Max);
			NBsys::NFile::SetRoot(NCommon::DeviceIndex::Local,L"./project_test/test" DEF_TEST_STRING);
			NBsys::NFile::SetRoot(NCommon::DeviceIndex::Common,L"./project_test/common");
			NBsys::NFile::SetRoot(NCommon::DeviceIndex::Sdk,L"../../sdk");
			NBsys::NFile::SetRoot(NCommon::DeviceIndex::TestData,L"../../brownie_testdata/data");
		}

		/** 削除。ファイル。
		*/
		virtual void Finalize_File()
		{
			NBsys::NFile::EndSystemRequest();
			NBsys::NFile::EndWaitSystem();
		}

		/** 初期化。パッド。
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

		/** 削除。パッド。
		*/
		virtual void Finalize_Pad()
		{
			#if(BSYS_PAD_ENABLE)
			{
				NBsys::NPad::EndSystem();
			}
			#endif
		}

		/** 初期化。DirectSound。
		*/
		virtual void Initialize_Dsound()
		{
			#if(BSYS_DSOUND_ENABLE)
			{
				NBsys::NDsound::StartSystem(this->window);
			}
			#endif
		}

		/** 削除。DirectSound。
		*/
		virtual void Finalize_Dsound()
		{
			#if(BSYS_DSOUND_ENABLE)
			{
				NBsys::NDsound::EndSystemRequest();
				NBsys::NDsound::EndSystem();
			}
			#endif
		}

		/** 初期化。ウィンドウメニュー。
		*/
		virtual void Initialize_WindowMenu()
		{
			#if(BSYS_WINDOWMENU_ENABLE)
			{
				NBsys::NWindowMenu::StartSystem(new NCommon::WindowMenu_Callback(this->render2d));
			}
			#endif
		}

		/** 削除。
		*/
		virtual void Finalize_WindowMenu()
		{
			#if(BSYS_WINDOWMENU_ENABLE)
			{
				NBsys::NWindowMenu::EndSystem();
			}
			#endif
		}

		/** 初期化。通信。
		*/
		virtual void Initialize_Winsock()
		{
			#if(BSYS_WINSOCK_ENABLE)
			{
				NBsys::NWinsock::StartSystem();
			}
			#endif

			#if(BSYS_OPENSSL_ENABLE)
			{
				NBsys::NOpenSsl::StartSystem();
			}
			#endif
		}

		/** 削除。通信。
		*/
		virtual void Finalize_Winsock()
		{
			#if(BSYS_OPENSSL_ENABLE)
			{
				NBsys::NOpenSsl::EndSystem();
			}
			#endif

			#if(BSYS_WINSOCK_ENABLE)
			{
				NBsys::NWinsock::EndSystem();
			}
			#endif
		}

		/** 初期化。ウィンドウ。
		*/
		virtual void Initialize_Window()
		{
			//
			this->size = NBsys::NWindow::Window::GetDesktopSize();

			this->window.reset(new NBsys::NWindow::Window());
			this->window->Create(L"TEST " DEF_TEST_STRING,this->size);
		}

		/** 削除。ウィンドウ。
		*/
		virtual void Finalize_Window()
		{
			this->window->Delete();
			this->window.reset();
		}

		/** 初期化。d3d11。
		*/
		virtual void Initialize_D3d11()
		{
			this->d3d11.reset(new NBsys::ND3d11::D3d11());
			this->d3d11->Render_Create(this->window,this->size);
		}

		/** 削除。d3d11
		*/
		virtual void Finalize_D3d11()
		{
			this->d3d11->Render_Delete();
			this->d3d11.reset();
		}

		/** 初期化。ライン描画。
		*/
		virtual void Initialize_DrawLine()
		{
			this->drawline.reset(new NCommon::DrawLine_Manager(this->d3d11));
		}

		/** 削除。ライン描画。
		*/
		virtual void Finalize_DrawLine()
		{
			this->drawline.reset();
		}

		/** 初期化。２Ｄ描画。
		*/
		virtual void Initialize_Render2D()
		{
			this->render2d.reset(new NCommon::Render2D());
		}

		/** 削除。２Ｄ描画。
		*/
		virtual void Finalize_Render2D()
		{
			this->render2d.reset();
		}

		/** 初期化。マテリアル。レクト描画。
		*/
		virtual void Initialize_Material_DrawRect()
		{
			this->material_drawrect.reset(new NCommon::DrawRect_Material(this->d3d11));
		}

		/** 削除。マテリアル。レクト描画。
		*/
		virtual void Finalize_Material_DrawRect()
		{
			this->material_drawrect.reset();
		}

		/** 初期化。マテリアル。フォント描画。
		*/
		virtual void Initialize_Material_DrawFont()
		{
			#if(BSYS_FONT_ENABLE)
			this->material_drawfont.reset(new NCommon::DrawFont_Material(this->d3d11));
			#endif
		}

		/** 削除。マテリアル。フォント描画。
		*/
		virtual void Finalize_Material_DrawFont()
		{
			#if(BSYS_FONT_ENABLE)
			this->material_drawfont.reset();
			#endif
		}

		/** 初期化、
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
			this->Initialize_Dsound();

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

		/** 削除。
		*/
		void Finalize()
		{
			this->Finalize_WindowMenu();

			this->Finalize_Material_DrawFont();
			this->Finalize_Material_DrawRect();
			this->Finalize_Render2D();

			this->Finalize_DrawLine();

			this->Finalize_Dsound();
			this->Finalize_Pad();
			this->Finalize_D3d11();
			this->Finalize_Window();
			this->Finalize_File();
			this->Finalize_Winsock();
		}

		/** 初期化更新。
			true	: 完了
			false	: 継続

		*/
		virtual bool Initialize_Update()
		{
			return true;
		}

		/** 更新。
		*/
		virtual void Update(f32 /*a_delta*/)
		{
		}

		/** 描画命令呼び出し。
		*/
		virtual void Render()
		{
		}

		/** ループ。
		*/
		void Loop()
		{
			//パフォーマンスカウンター。
			float t_delta = 0.0f;
			{
				u64 t_pcounter_now = PerformanceCounter::GetPerformanceCounter();
				u64 t_pcounter_sec = PerformanceCounter::GetPerformanceSecCounter();
				t_delta = static_cast<float>(t_pcounter_now - this->pcounter) / t_pcounter_sec;
				if(t_delta <= 0.0f){
					return;
				}
				this->pcounter = t_pcounter_now;
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

				if(this->Initialize_Update() == false){
					t_next = false;
				}

				if(t_next == true){

					this->render2d->SetMaterial(NCommon::Render2D_ItemType::Rect,this->material_drawrect);

					#if(BSYS_FONT_ENABLE)
					this->render2d->SetMaterial(NCommon::Render2D_ItemType::Font,this->material_drawfont);
					#endif

					this->initialize_step++;
				}
			}else if(this->initialize_step == 1){

				//ラスタライザ。ステート。
				this->rasterizerstate_cull_back_id = this->d3d11->CreateRasterizerState(NBsys::ND3d11::D3d11_CullType::Back);
				this->rasterizerstate_cull_none_id = this->d3d11->CreateRasterizerState(NBsys::ND3d11::D3d11_CullType::None);

				//ブレンド。ステート。
				this->blendstate_on_id = this->d3d11->CreateBlendState(true);
				this->blendstate_off_id = this->d3d11->CreateBlendState(false);

				//デプスステンシル。ステート。
				this->depthstencilstate_check_on_write_on_id = this->d3d11->CreateDepthStencilState(true,true);
				this->depthstencilstate_check_off_write_off_id = this->d3d11->CreateDepthStencilState(false,false);

				//サンプラ。ステート。
				{
					NBsys::ND3d11::D3d11_Sampler t_sampler;
					{
						t_sampler.textureaddrestype_u = NBsys::ND3d11::D3d11_TextureAddressType::Clamp;
						t_sampler.textureaddrestype_v = NBsys::ND3d11::D3d11_TextureAddressType::Clamp;
						t_sampler.textureaddrestype_w = NBsys::ND3d11::D3d11_TextureAddressType::Clamp;
						t_sampler.filtertype = NBsys::ND3d11::D3d11_FilterType::MIN_MAG_MIP_POINT;
					}
					this->samplerstate_point_id = this->d3d11->CreateSamplerState(t_sampler);
				}

				this->initialize_step++;
			}else{
				//初期化完了。
				t_initialize_update = false;
			}

			//更新。
			if(t_initialize_update){
			}else{

				//パッド。
				#if(BSYS_PAD_ENABLE)
				NBsys::NPad::Update(true);
				#endif

				//ウィンドウメニュー。
				#if(BSYS_WINDOWMENU_ENABLE)
				NBsys::NWindowMenu::GetSystemInstance()->Update();
				#endif

				{
					//FPS。
					if(this->render2d){

						//マウスの位置取得。
						const NBsys::NPad::TouchValue& t_mouse_l = NBsys::NPad::GetVirtualPad(NCommon::Pad_Device::Type::Pad1)->GetTouchValue(NBsys::NPad::Pad_Virtual::TouchType::MOUSEL);

						//許容値の何倍か。
						f32 t_loop_time = this->loop_time.Load() / (1.0f/60.0f);

						//文字列作成。
						STLWString t_string;
						{
							wchar t_buffer[64];
							s32 t_fps = static_cast<s32>(1.0f / t_delta);
							s32 t_mouse_x = static_cast<s32>(t_mouse_l.pos.xx);
							s32 t_mouse_y =static_cast<s32>(t_mouse_l.pos.yy);

							Size2DType<f32> t_window_size = this->window->GetClientSize();
							s32 t_window_w = static_cast<s32>(t_window_size.ww);
							s32 t_window_h = static_cast<s32>(t_window_size.hh);

							//許容値の何％か。
							s32 t_loop = static_cast<s32>(t_loop_time * 100);

							t_string = VASTRING(t_buffer,sizeof(t_buffer),L"%d : %d : (%d %d) : (%d %d)",t_fps,t_loop,t_mouse_x,t_mouse_y,t_window_w,t_window_h);
						}

						//描画登録。
						{
							sharedptr<NCommon::Render2D_Item_Font> t_font(new NCommon::Render2D_Item_Font(99999));
							t_font->clip_rect.Set(0.0f);
							t_font->clip = false;
							t_font->size = 16.0f;
							t_font->fonttexture_type = NBsys::ND3d11::D3d11_FontTextureType::SFont;

							f32 t_red = t_loop_time;
							if(t_red >= 0.5f){
								t_font->color = NBsys::NColor::Color_F(1.0f,0.0f,0.0f,1.0f);
							}else{
								t_font->color = NBsys::NColor::Color_F(1.0f,1.0f,1.0f,1.0f);
							}
							
							t_font->alignment = NBsys::NFont::Font_Alignment::Left_Top;
							t_font->string = t_string;

							this->render2d->Draw(t_font);
						}
					}

					this->Update(t_delta);
				}

				//キャプチャー開始。
				#if(DEF_TEST_AUTO)
				this->autotime += t_delta;
				if(this->autotime >= 3.0f){
					if(this->autotest->action_start == false){
						this->autotest->action_start = true;
						this->autotest->capture_step = 0;
					}
				}

				if(this->autotest->action_end == true){
					//終了。
					break;
				}
				#endif
			}

			//サウンド命令呼び出し開始。
			#if(BSYS_DSOUND_ENABLE)
			{
				NBsys::NDsound::Update();
			}
			#endif

			//描画命令呼び出し。
			{
				//リクエスト処理。
				this->d3d11->Render_Main();

				//ビューポート。
				this->d3d11->Render_ViewPort(Rect2DType_R<f32>(0.0f,0.0f,this->size.ww,this->size.hh));

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

			#if(DEF_TEST_AUTO)
			this->autotest->Update();
			#endif
		}

		/** Loop_Sync
		*/
		void Loop_Sync()
		{
			this->d3d11->Render_Present();
		}

		/** メイン。
		*/
		void Main()
		{
			//パフォーマンスカウンター。
			this->pcounter = PerformanceCounter::GetPerformanceCounter();

			{
				App_Base_Thread::ThreadArgument t_threadargument;
				{
					t_threadargument.app = this;
				}
				this->thread.reset(new ThreadTemplate<App_Base_Thread>());
				this->thread->Start(t_threadargument);
			}

			while(true){

				this->window->Update();
				if(this->window->IsEnd() == true){
					break;
				}

				{
					s64 t_counter = PerformanceCounter::GetPerformanceCounter();
					{
						this->Loop();
					}
					f32 t_counter_len = static_cast<f32>(PerformanceCounter::GetPerformanceCounter() - t_counter);
					t_counter_len /= PerformanceCounter::GetPerformanceSecCounter();
					this->loop_time.Store(t_counter_len);
				}

				{
					this->Loop_Sync();
				}

			}

			{
				this->thread->get()->EndRequest();
				this->thread->EndWait();
				this->thread.reset();
			}

		}

		/** SendDiscord
		*/
		void SendDiscord(const STLWString& a_string)
		{
			sharedptr<NBsys::NHttp::Http> t_http(new NBsys::NHttp::Http());
			t_http->SetHost("bbbproject.sakura.ne.jp");
			t_http->SetPort(80);
			t_http->SetMode(NBsys::NHttp::Http_Mode::Post);
			t_http->SetSsl(false);
			t_http->SetUrl("/www/project_discord/");

			t_http->AddPostContent("message",WcharToChar(a_string));
			//t_http->AddPostContent("debug","1");

			sharedptr<RingBufferBase<u8>> t_ringbuffer(new RingBuffer<u8,1*1024*1024,true>());
			t_http->ConnectStart(t_ringbuffer);

			STLString t_recv_string;

			while(1){
				bool t_ret = t_http->ConnectUpdate();
				if((t_ret == true)||(t_ringbuffer->GetUseSize()>0)){
					if(t_http->IsRecvHeader()){
						//ヘッダー読み込み済み。

						u8 t_buffer[64] = {0};
						s32 t_size = t_ringbuffer->GetUseSize();
						if(t_size >= sizeof(t_buffer) - 1){
							t_size = sizeof(t_buffer) - 1;
						}
						t_ringbuffer->CopyFromBuffer(t_buffer,t_size);

						t_recv_string += reinterpret_cast<char*>(t_buffer);
					}
				}else{
					t_http->ConnectEnd();
					break;
				}

				ThreadSleep(0);
			}

			t_http.reset();

			TAGLOG(L"discord","%s",t_recv_string.c_str());
		}

		/** キャプチャー。
		*/
		void Capture()
		{
			#if((BSYS_TEXTURE_ENABLE)&&(BSYS_D3D11_ENABLE)&&(BSYS_TEXTURE_GDIPLUS_ENABLE))

			sharedptr<NBsys::NTexture::Texture> t_capture_texture = this->d3d11->Render_ScreenShot();

			std::tuple<sharedptr<u8>,s32> t_jpg_data = NBsys::NTexture::EncodeToJpg(t_capture_texture);

			FileHandle t_output;
			t_output.WriteOpen(L"./output.jpg");

			t_output.Write(std::get<0>(t_jpg_data).get(),std::get<1>(t_jpg_data),0);

			t_output.Close();

			#endif
		}
	};


	/** メインスレッド。
	*/
	inline void App_Base_Thread::ThreadMain(ThreadArgument& a_threadargument)
	{
		while(1){
			ThreadSleep(0);

			/*
			{
				s64 t_counter = PerformanceCounter::GetPerformanceCounter();
				{
					a_threadargument.app->Loop();
				}
				f32 t_counter_len = static_cast<f32>(PerformanceCounter::GetPerformanceCounter() - t_counter);
				t_counter_len /= PerformanceCounter::GetPerformanceSecCounter();
				this->loop_time.Store(t_counter_len);
			}

			{
				a_threadargument.app->Loop_Sync();
			}
			*/

			//終了チェック。
			if(this->endrequest.Load()){
				break;
			}
		}
	}


}}
#pragma warning(pop)
#endif

