

/**
 * Copyright (c) 2016 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief インクルード。
*/


/** include
*/
#include "../entry.h"


/** DEF_TEST12
*/
#if defined(DEF_TEST12)


/** include
*/
#include "./test12_main.h"


/** include
*/
#include "../common/d3d11_drawline.h"
#include "../common/d3d11_drawfont.h"
#include "../common/pad_device.h"


/** Blib_DebugAssert_Callback
*/
#if(BLIB_DEBUGASSERT_CALLBACK_ENABLE)
void Blib_DebugAssert_Callback(const char* a_message,const char* a_filename,s32 a_line)
{
}
#endif


/** Blib_DebugBreak_Callback
*/
#if(BLIB_DEBUGBREAK_CALLBACK_ENABLE)
void Blib_DebugBreak_Callback()
{
}
#endif


/** Blib_DebugLog_Callback
*/
#if(BLIB_DEBUGLOG_CALLBACK_ENABLE)
void Blib_DebugLog_Callback(const char* a_tag,const char* a_string)
{
}
#endif


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


/** s_font
*/
sharedptr<NBsys::NFont::Font> s_font16;
sharedptr<NBsys::NFont::Font> s_font32;
sharedptr<NBsys::NFont::Font> s_font64;


/** fontindex
*/
s32 s_fontindex_16 = 0;
s32 s_fontindex_32 = 1;
s32 s_fontindex_64 = 2;




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
	s32 depthstencilstate_write_on_id;
	s32 depthstencilstate_write_off_id;

	/** ライン描画。
	*/
	sharedptr<NCommon::D3d11_DrawLine_Manager> drawline_manager;

	/** フォント描画。
	*/
	sharedptr<NCommon::D3d11_DrawFont_Manager> drawfont16_manager;
	sharedptr<NCommon::D3d11_DrawFont_Manager> drawfont32_manager;
	sharedptr<NCommon::D3d11_DrawFont_Manager> drawfont64_manager;

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
		//ブレンドステータス。
		this->blendstate_id = s_d3d11->CreateBlendState(true);

		//ラスタライザー。
		this->rasterizerstate_cull_back_id = s_d3d11->CreateRasterizerState(NBsys::ND3d11::D3d11_CullType::BACK);
		this->rasterizerstate_cull_none_id = s_d3d11->CreateRasterizerState(NBsys::ND3d11::D3d11_CullType::NONE);

		/** 深度ステンシル。
		*/
		this->depthstencilstate_write_on_id = s_d3d11->CreateDepthStencilState(true,true);
		this->depthstencilstate_write_off_id = s_d3d11->CreateDepthStencilState(true,false);

		//ライン描画。
		this->drawline_manager.reset(new NCommon::D3d11_DrawLine_Manager(s_d3d11));

		//フォント描画。
		this->drawfont16_manager.reset(new NCommon::D3d11_DrawFont_Manager(s_d3d11,s_fontindex_16));
		this->drawfont32_manager.reset(new NCommon::D3d11_DrawFont_Manager(s_d3d11,s_fontindex_32));
		this->drawfont64_manager.reset(new NCommon::D3d11_DrawFont_Manager(s_d3d11,s_fontindex_64));
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
		//ライン描画。
		this->drawline_manager->PreUpdate();

		//フォント描画。
		this->drawfont16_manager->PreUpdate();
		this->drawfont32_manager->PreUpdate();
		this->drawfont64_manager->PreUpdate();

		switch(this->step){
		case 0:
			{
				if(this->drawline_manager->IsBusy() == true){
					break;
				}

				if(this->drawfont16_manager->IsBusy() == true){
					break;
				}

				if(this->drawfont32_manager->IsBusy() == true){
					break;
				}

				if(this->drawfont64_manager->IsBusy() == true){
					break;
				}

				//初期化完了。
				{
					this->camera_position = NBsys::NGeometry::Geometry_Vector3(1.0f,10.0f,-20.0f);
					this->camera_up = NBsys::NGeometry::Geometry_Vector3(0.0f,1.0f,0.0f);
					this->camera_target = NBsys::NGeometry::Geometry_Vector3(0.0f,0.0f,0.0f);
					this->camera_fov_deg = 60.0f;
					this->camera_near = 0.1f;
					this->camera_far = 1000.0f;
					this->camera_time = 0.0f;
				}

				this->step++;
			}break;
		case 1:
			{
				this->step++;
				this->draw = true;
			}break;
		case 2:
			{
				this->camera_time += a_delta;

				//カメラ回転。
				this->camera_position.x = Math::cosf(this->camera_time / 10) * 20;
				this->camera_position.z = Math::sinf(this->camera_time / 10) * 20;

			}break;
		}
	}

	/** 描画。
	*/
	void Draw()
	{
		s_d3d11->Render_ViewPort(0.0f,0.0f,static_cast<f32>(s_width),static_cast<f32>(s_height));

		//クリア。
		s_d3d11->Render_ClearRenderTargetView(NBsys::NColor::Color_F(0.3f,0.3f,0.8f,1.0f));
		s_d3d11->Render_ClearDepthStencilView();

		if(this->draw){

			//フォント描画。開始。
			s_d3d11->Render_DrawFont_StartClear(s_fontindex_16);
			s_d3d11->Render_DrawFont_StartClear(s_fontindex_32);
			s_d3d11->Render_DrawFont_StartClear(s_fontindex_64);

			//プロジェクション。
			NBsys::NGeometry::Geometry_Matrix_44 t_projection;
			t_projection.Set_PerspectiveProjectionMatrix(static_cast<f32>(s_width),static_cast<f32>(s_height),this->camera_fov_deg,this->camera_near,this->camera_far);

			//ビュー。
			NBsys::NGeometry::Geometry_Matrix_44 t_view;
			t_view.Set_ViewMatrix(this->camera_target,this->camera_position,this->camera_up);

			{
				//ライン描画。
				this->drawline_manager->DrawLine(NBsys::NGeometry::Geometry_Vector3(-100,0,0),NBsys::NGeometry::Geometry_Vector3(100,0,0),NBsys::NColor::Color_F(1.0f,0.0f,0.0f,1.0f));
				this->drawline_manager->DrawLine(NBsys::NGeometry::Geometry_Vector3(0,-100,0),NBsys::NGeometry::Geometry_Vector3(0,100,0),NBsys::NColor::Color_F(0.0f,1.0f,0.0f,1.0f));
				this->drawline_manager->DrawLine(NBsys::NGeometry::Geometry_Vector3(0,0,-100),NBsys::NGeometry::Geometry_Vector3(0,0,100),NBsys::NColor::Color_F(0.0f,0.0f,1.0f,1.0f));

				//ライン描画。
				this->drawline_manager->Update(t_view * t_projection);
			}

			{
				//プロジェクション。
				t_projection.Set_OrthographicProjectionMatrix(0,static_cast<f32>(s_width),0,static_cast<f32>(s_height),0.0f,1.0f);

				//ビュー。
				t_view.Set_Identity();

				//クリア。
				s_d3d11->Render_ClearDepthStencilView();

				//深度ステンシル。
				s_d3d11->Render_SetDepthStencilState(this->depthstencilstate_write_off_id);

				//マウス。
				NBsys::NPad::TouchValue t_mouse_l = NBsys::NPad::GetVirtualPad(NCommon::Pad_Device::Type::Pad1)->GetTouchValue(NBsys::NPad::Pad_Virtual::TouchType::MOUSEL);
			
				//文字描画。
				if(t_mouse_l.flag){
					char t_buffer[32];
					STLWString t_string = VASTRING(t_buffer,sizeof(t_buffer),L"%d %d",static_cast<s32>(t_mouse_l.x),static_cast<s32>(t_mouse_l.y));
					this->drawfont16_manager->DrawFont(t_string,16.0f,t_mouse_l.x+30,t_mouse_l.y+30,NBsys::NColor::Color_F(0.0f,1.0f,1.0f,1.0f));
					this->drawfont16_manager->DrawFont(t_string,16.0f,t_mouse_l.x-30,t_mouse_l.y-30,NBsys::NColor::Color_F(0.0f,1.0f,1.0f,1.0f));
				}

				this->drawfont32_manager->DrawFont(L"あいうえお",	32.0f,	100.0f,			100.0f,			NBsys::NColor::Color_F(1.0f,0.0f,1.0f,1.0f));
				this->drawfont64_manager->DrawFont(L"あいうえお",	64.0f,	s_width/2.0f,	s_height/2.0f,	NBsys::NColor::Color_F(1.0f,1.0f,0.0f,1.0f));

				//文字描画。
				this->drawfont16_manager->Update(t_view * t_projection);
				this->drawfont32_manager->Update(t_view * t_projection);
				this->drawfont64_manager->Update(t_view * t_projection);
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
	TAGLOG("main","DEF_TEST12");

	NBsys::NFile::StartSystem(1);
	NBsys::NFile::SetRoot(0,L"./project_test");

	NBsys::NPad::StartSystem(1);

	s_window.reset(new NBsys::NWindow::Window());
	s_d3d11.reset(new NBsys::ND3d11::D3d11());
	s_app.reset(new App());

	s_window->Create(L"sample",s_width,s_height);
	s_d3d11->Render_Create(s_window,s_width,s_height);

	s_font16.reset(new NBsys::NFont::Font(L"Arial",14));
	s_d3d11->Render_SetFont(s_fontindex_16,s_font16,16,L"font16");

	s_font32.reset(new NBsys::NFont::Font(L"Arial",28));
	s_d3d11->Render_SetFont(s_fontindex_32,s_font32,32,L"font32");

	s_font64.reset(new NBsys::NFont::Font(L"Arial",60));
	s_d3d11->Render_SetFont(s_fontindex_64,s_font64,64,L"font64");

	sharedptr<NBsys::NPad::Pad_Device_Base> t_pad_device(new NCommon::Pad_Device(s_window,s_d3d11));
	NBsys::NPad::AddDevice(t_pad_device);
	NBsys::NPad::GetVirtualPad(NCommon::Pad_Device::Type::Pad1)->AddTouch(NBsys::NPad::Pad_Virtual::TouchType::MOUSEL,NBsys::NPad::Pad_Device_Base::TouchType::DeviceTouch_1,t_pad_device);
	NBsys::NPad::GetVirtualPad(NCommon::Pad_Device::Type::Pad1)->AddTouch(NBsys::NPad::Pad_Virtual::TouchType::MOUSER,NBsys::NPad::Pad_Device_Base::TouchType::DeviceTouch_2,t_pad_device);
	NBsys::NPad::GetVirtualPad(NCommon::Pad_Device::Type::Pad1)->SetEnable(true);

	//パフォーマンスカウンター。
	u64 t_pcounter = 0ULL;

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
			if(t_delta < (1.0f / 60)){
				continue;
			}
			t_pcounter = t_pcounter_now;
		}

		//パッド。
		NBsys::NPad::Update(true);

		//更新。
		s_app->Update(t_delta);

		//リクエスト処理。
		s_d3d11->Render_Main();

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

	NBsys::NPad::EndSystem();

	NBsys::NFile::EndSystemRequest();
	NBsys::NFile::EndWaitSystem();

	return;
}
#endif

