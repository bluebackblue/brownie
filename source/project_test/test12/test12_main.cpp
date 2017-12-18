﻿

/**
 * Copyright (c) 2016 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief テスト。
*/


/** include
*/
#include "../entry.h"


/** DEF_TEST_INDEX
*/
#if(DEF_TEST_INDEX == 12)


/** include
*/
#include "./test12_main.h"
#include "./test12_windowmenu_texture.h"
#include "./test12_windowmenu_log.h"

/** include
*/
#include "../common/common_render2d.h"
#include "../common/common_drawline.h"
#include "../common/common_drawrect.h"
#include "../common/common_drawfont.h"
#include "../common/common_pad_device.h"
#include "../common/common_windowmenu_callback.h"


/** s_width
*/
static s32 s_width = 1600;


/** s_height
*/
static s32 s_height = 900;


/** s_window
*/
static sharedptr<NBsys::NWindow::Window> s_window;


/** s_d3d11
*/
static sharedptr<NBsys::ND3d11::D3d11> s_d3d11;


/** render2d
*/
sharedptr<NCommon::Render2D> s_render2d;


/** s_pad_device
*/
sharedptr<NBsys::NPad::Pad_Device_Base> s_pad_device;


/** s_windowmenu_callback
*/
sharedptr<NBsys::NWindowMenu::WindowMenu_Callback_Base> s_windowmenu_callback;


/** ライン描画。
*/
sharedptr<NCommon::DrawLine_Manager> s_drawline_manager;


/** レクト描画。
*/
sharedptr<NCommon::Render2D_Material_Base> s_drawrect_material;


/** フォント描画。
*/
sharedptr<NCommon::Render2D_Material_Base> s_drawfont_material;


/** ウィンドウ。
*/
sharedptr<Test12_WindowMenu_Texture> s_window_texture_1;
sharedptr<Test12_WindowMenu_Texture> s_window_texture_2;
sharedptr<Test12_WindowMenu_Texture> s_window_texture_3;
sharedptr<Test12_WindowMenu_Log> s_window_log;


/** App
*/
class App
{
private:
	/** step
	*/
	s32 step;

	/** draw
	*/
	bool draw;

	/** blendstate_id
	*/
	s32 blendstate_id;

	/** rasterizerstate_cull
	*/
	s32 rasterizerstate_cull_back_id;
	s32 rasterizerstate_cull_none_id;

	/** depthstencilstate
	*/
	s32 depthstencilstate_check_on_write_on_id;
	s32 depthstencilstate_check_off_write_off_id;

	/** カメラ。
	*/
	NBsys::NGeometry::Geometry_Vector3 camera_position;
	NBsys::NGeometry::Geometry_Vector3 camera_up;
	NBsys::NGeometry::Geometry_Vector3 camera_target;
	f32 camera_fov_deg;
	f32 camera_near;
	f32 camera_far;
	f32 camera_time;

public:

	/** constructor
	*/
	App()
		:
		step(0),
		draw(false)
	{
	}

	/** destructor
	*/
	nonvirtual ~App()
	{
	}

public:
	/** 更新。
	*/
	void Update(f32 a_delta)
	{
		//パッド。
		NBsys::NPad::Update(true);

		//ウィンドウメニュー。
		NBsys::NWindowMenu::GetSystemInstance()->Update();

		switch(this->step){
		case 0:
			{
				//ライン描画。
				s_drawline_manager->Initialize_Update();
				if(s_drawline_manager->IsInitialized() == false){
					break;
				}

				//レクト描画。
				s_drawrect_material->Initialize_Update();
				if(s_drawrect_material->IsInitialized() == false){
					break;
				}

				//フォント描画。
				s_drawfont_material->Initialize_Update();
				if(s_drawfont_material->IsInitialized() == false){
					break;
				}

				//ブレンドステータス。
				this->blendstate_id = s_d3d11->CreateBlendState(true);

				//ラスタライザー。
				this->rasterizerstate_cull_back_id = s_d3d11->CreateRasterizerState(NBsys::ND3d11::D3d11_CullType::Back);
				this->rasterizerstate_cull_none_id = s_d3d11->CreateRasterizerState(NBsys::ND3d11::D3d11_CullType::None);

				//深度ステンシル。
				this->depthstencilstate_check_on_write_on_id = s_d3d11->CreateDepthStencilState(true,true);
				this->depthstencilstate_check_off_write_off_id = s_d3d11->CreateDepthStencilState(false,false);

				//カメラ。
				{
					this->camera_position = NBsys::NGeometry::Geometry_Vector3(1.0f,10.0f,-20.0f);
					this->camera_up = NBsys::NGeometry::Geometry_Vector3(0.0f,1.0f,0.0f);
					this->camera_target = NBsys::NGeometry::Geometry_Vector3(0.0f,0.0f,0.0f);
					this->camera_fov_deg = 60.0f;
					this->camera_near = 0.1f;
					this->camera_far = 1000.0f;
					this->camera_time = 0.0f;
				}

				//マテリアル設定。
				s_render2d->SetMaterial(NCommon::Render2D_Item::Type::Rect,s_drawrect_material);
				s_render2d->SetMaterial(NCommon::Render2D_Item::Type::Font,s_drawfont_material);

				this->step++;
			}break;
		case 1:
			{
				//ウィンドウメニュー。
				s_window_texture_1.reset(new Test12_WindowMenu_Texture(0,L"フォントテクスチャー[0]",150.0f,150.0f,s_d3d11));
				s_window_texture_2.reset(new Test12_WindowMenu_Texture(1,L"フォントテクスチャー[1]",150.0f,150.0f,s_d3d11));
				s_window_texture_3.reset(new Test12_WindowMenu_Texture(1,L"フォントテクスチャー[2]",150.0f,150.0f,s_d3d11));
				NBsys::NWindowMenu::GetSystemInstance()->Add(s_window_texture_1);
				NBsys::NWindowMenu::GetSystemInstance()->Add(s_window_texture_2);
				NBsys::NWindowMenu::GetSystemInstance()->Add(s_window_texture_3);

				s_window_log.reset(new Test12_WindowMenu_Log(150.0f,150.0f));
				NBsys::NWindowMenu::GetSystemInstance()->Add(s_window_log);

				this->step++;
				this->draw = true;
			}break;
		case 2:
			{
				this->camera_time += a_delta;

				//カメラ回転。
				this->camera_position.x = Math::cosf(this->camera_time / 10) * 20;
				this->camera_position.z = Math::sinf(this->camera_time / 10) * 20;

				//FPS。
				{
					char t_buffer[32];
					STLWString t_string = VASTRING(t_buffer,sizeof(t_buffer),L"%d",static_cast<s32>(1.0f / a_delta));
					s_render2d->DrawFont(0,0.0f,0.0f,-1.0f,-1.0f,16.0f,0,NBsys::NColor::Color_F(0.0f,1.0f,1.0f,1.0f),t_string);
				}

				{
					//マウス。
					const NBsys::NPad::TouchValue& t_mouse_l = NBsys::NPad::GetVirtualPad(NCommon::Pad_Device::Type::Pad1)->GetTouchValue(NBsys::NPad::Pad_Virtual::TouchType::MOUSEL);

					//文字描画。
					if(t_mouse_l.flag){
						char t_buffer[32];
						STLWString t_string = VASTRING(t_buffer,sizeof(t_buffer),L"%d %d",static_cast<s32>(t_mouse_l.x),static_cast<s32>(t_mouse_l.y));
						
						s_render2d->DrawFont(0,t_mouse_l.x+50,t_mouse_l.y+50,-1.0f,-1.0f,16.0f,0,NBsys::NColor::Color_F(0.0f,1.0f,1.0f,1.0f),t_string);
						s_render2d->DrawFont(0,t_mouse_l.x-50,t_mouse_l.y-50,-1.0f,-1.0f,16.0f,0,NBsys::NColor::Color_F(0.0f,1.0f,1.0f,1.0f),t_string);
					}

					s_render2d->DrawFont(1,200.0f,			200.0f,			-1.0f,-1.0f,		32.0f,		1,	NBsys::NColor::Color_F(1.0f,1.0f,1.0f,1.0f),L"あいうえお");
					s_render2d->DrawFont(1,s_width/2.0f,	s_height/2.0f,	-1.0f,-1.0f,		64.0f,		2,	NBsys::NColor::Color_F(1.0f,1.0f,1.0f,1.0f),L"あいうえお");
					
					/*
					{
						s32 t_texture_id = s_d3d11->Render_GetFontTexture(0);
						s_render2d->DrawRect(0,100,100,16*3,256*4,t_texture_id,NBsys::NColor::Color_F(1.0f,1.0f,1.0f,1.0f));
					}

					{
						s32 t_texture_id = s_d3d11->Render_GetFontTexture(1);
						s_render2d->DrawRect(0,200,100,32,256,t_texture_id,NBsys::NColor::Color_F(1.0f,1.0f,1.0f,1.0f));
					}

					{
						s32 t_texture_id = s_d3d11->Render_GetFontTexture(2);
						s_render2d->DrawRect(0,300,100,64,4096,t_texture_id,NBsys::NColor::Color_F(1.0f,1.0f,1.0f,1.0f));
					}
					*/
				}

			}break;
		}
	}

	/** 描画。
	*/
	void Draw()
	{
		//リクエスト処理。
		s_d3d11->Render_Main();

		//ビューポート。
		s_d3d11->Render_ViewPort(0.0f,0.0f,static_cast<f32>(s_width),static_cast<f32>(s_height));

		//クリア。
		s_d3d11->Render_ClearRenderTargetView(NBsys::NColor::Color_F(0.3f,0.3f,0.8f,1.0f));

		if(this->draw){

			//深度ステンシルクリア。
			s_d3d11->Render_ClearDepthStencilView();

			//プロジェクション。
			NBsys::NGeometry::Geometry_Matrix_44 t_projection;

			//ビュー。
			NBsys::NGeometry::Geometry_Matrix_44 t_view;

			//３Ｄ描画。
			{
				//プロジェクション。
				t_projection.Set_PerspectiveProjectionMatrix(static_cast<f32>(s_width),static_cast<f32>(s_height),this->camera_fov_deg,this->camera_near,this->camera_far);

				//ビュー。
				t_view.Set_ViewMatrix(this->camera_target,this->camera_position,this->camera_up);

				{
					//ライン描画。
					s_drawline_manager->DrawLine(NBsys::NGeometry::Geometry_Vector3(-100,0,0),NBsys::NGeometry::Geometry_Vector3(100,0,0),NBsys::NColor::Color_F(1.0f,0.0f,0.0f,1.0f));
					s_drawline_manager->DrawLine(NBsys::NGeometry::Geometry_Vector3(0,-100,0),NBsys::NGeometry::Geometry_Vector3(0,100,0),NBsys::NColor::Color_F(0.0f,1.0f,0.0f,1.0f));
					s_drawline_manager->DrawLine(NBsys::NGeometry::Geometry_Vector3(0,0,-100),NBsys::NGeometry::Geometry_Vector3(0,0,100),NBsys::NColor::Color_F(0.0f,0.0f,1.0f,1.0f));
				}

				//深度ステンシル。チェックあり。書き込みあり。
				s_d3d11->Render_SetDepthStencilState(this->depthstencilstate_check_on_write_on_id);

				//ライン描画。
				s_drawline_manager->Render(t_view * t_projection);
			}

			//２Ｄ描画。
			{
				//プロジェクション。
				t_projection.Set_OrthographicProjectionMatrix(0,static_cast<f32>(s_width),0,static_cast<f32>(s_height),0.0f,1.0f);

				//ビュー。
				t_view.Set_Identity();

				//クリア。
				s_d3d11->Render_ClearDepthStencilView();

				//深度ステンシル。チェックなし。書き込みなし。
				s_d3d11->Render_SetDepthStencilState(this->depthstencilstate_check_off_write_off_id);

				//レクト描画。
				//文字描画。
				{
					//描画。
					s_render2d->Render(t_view * t_projection);
				}

				//ウィンドウメニュー。
				{
					NBsys::NWindowMenu::GetSystemInstance()->Draw();

					//描画。
					s_render2d->Render(t_view * t_projection);
				}
			}
		}
	}
};


/** s_app
*/
static sharedptr<App> s_app;


/** Test_Main
*/
void Test_Main()
{
	NBsys::NFile::StartSystem(1);
	NBsys::NFile::SetRoot(0,L"./project_test");

	NBsys::NPad::StartSystem(1);

	s_window.reset(new NBsys::NWindow::Window());
	s_d3d11.reset(new NBsys::ND3d11::D3d11());
	s_app.reset(new App());

	s_window->Create(DEF_TEST_TITLE,s_width,s_height);
	s_d3d11->Render_Create(s_window,s_width,s_height);

	s_pad_device.reset(new NCommon::Pad_Device(s_window,s_d3d11));
	NBsys::NPad::AddDevice(s_pad_device);
	NBsys::NPad::GetVirtualPad(NCommon::Pad_Device::Type::Pad1)->AddButton(NBsys::NPad::Pad_Virtual::ButtonType::MOUSEL,NBsys::NPad::Pad_Device_Base::ButtonType::DeviceButton_14,s_pad_device);
	NBsys::NPad::GetVirtualPad(NCommon::Pad_Device::Type::Pad1)->AddButton(NBsys::NPad::Pad_Virtual::ButtonType::MOUSER,NBsys::NPad::Pad_Device_Base::ButtonType::DeviceButton_15,s_pad_device);
	NBsys::NPad::GetVirtualPad(NCommon::Pad_Device::Type::Pad1)->AddTouch(NBsys::NPad::Pad_Virtual::TouchType::MOUSEL,NBsys::NPad::Pad_Device_Base::TouchType::DeviceTouch_1,s_pad_device);
	NBsys::NPad::GetVirtualPad(NCommon::Pad_Device::Type::Pad1)->AddTouch(NBsys::NPad::Pad_Virtual::TouchType::MOUSER,NBsys::NPad::Pad_Device_Base::TouchType::DeviceTouch_2,s_pad_device);
	NBsys::NPad::GetVirtualPad(NCommon::Pad_Device::Type::Pad1)->SetEnable(true);

	//レンダー２Ｄ。
	s_render2d.reset(new NCommon::Render2D());

	//ライン描画。
	s_drawline_manager.reset(new NCommon::DrawLine_Manager(s_d3d11));

	//レクト描画。
	s_drawrect_material.reset(new NCommon::DrawRect_Material(s_d3d11));

	//フォント描画。
	s_drawfont_material.reset(new NCommon::DrawFont_Material(s_d3d11));

	//ウィンドウメニュー。
	s_windowmenu_callback.reset(new NCommon::WindowMenu_Callback(s_render2d));
	NBsys::NWindowMenu::StartSystem(s_windowmenu_callback);

	//パフォーマンスカウンター。
	u64 t_pcounter = PerformanceCounter::GetPerformanceCounter();

	#if(DEF_TEST_AUTO)
	f32 t_autotime = 0.0f;
	#endif

	while(true){

		//s_window
		s_window->Update();
		if(s_window->IsEnd() == true){
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

		//更新。
		s_app->Update(t_delta);

		//描画。
		s_app->Draw();

		if(s_d3d11->Render_Present() == false){
			break;
		}
	}

	s_d3d11->Render_Delete();
	s_d3d11.reset();

	s_window->Delete();
	s_window.reset();

	s_app.reset();

	NBsys::NWindowMenu::EndSystem();

	NBsys::NPad::EndSystem();

	NBsys::NFile::EndSystemRequest();
	NBsys::NFile::EndWaitSystem();

	return;
}
#endif

