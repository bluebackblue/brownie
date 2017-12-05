

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


/** DEF_TEST10
*/
#if defined(DEF_TEST10)


/** include
*/
#include "./test10_main.h"


/** include
*/
#include "../common/d3d11_drawline.h"


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
static s32 s_width = 800;


/** s_height
*/
static s32 s_height = 600;


/** s_window
*/
static sharedptr<NBsys::NWindow::Window> s_window;


/** s_d3d11
*/
static sharedptr<NBsys::ND3d11::D3d11> s_d3d11;


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

	/** ライン描画。
	*/
	sharedptr<common::D3d11_DrawLine_Manager> drawline_manager;

	/** カメラ。
	*/
	NBsys::NGeometry::Geometry_Vector3 camera_position;
	NBsys::NGeometry::Geometry_Vector3 camera_up;
	NBsys::NGeometry::Geometry_Vector3 camera_target;
	f32 camera_fov_deg;
	f32 camera_near;
	f32 camera_far;

	/** ターゲット。
	*/
	f32 target_time;
	NBsys::NGeometry::Geometry_Vector3 target_from;
	NBsys::NGeometry::Geometry_Vector3 target_to_a;
	NBsys::NGeometry::Geometry_Vector3 target_to_b;

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

		//ライン描画。
		this->drawline_manager.reset(new common::D3d11_DrawLine_Manager(s_d3d11));
	}

	/** destructor
	*/
	~App()
	{
	}

public:
	/** 更新。
	*/
	void Update(f32 a_delta)
	{
		//ライン描画。
		this->drawline_manager->PreUpdate();

		switch(this->step){
		case 0:
			{
				if(this->drawline_manager->IsBusy() == true){
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
				}

				{
					this->target_time = 0.0f;
					this->target_from.Set(10,10,10);
					this->target_to_a.Set(0,0,10);
					this->target_to_b.Set(3,0,0);
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
				this->target_time += a_delta;

				//カメラ回転。
				this->camera_position.x = Math::cosf(this->target_time / 10) * 20;
				this->camera_position.z = Math::sinf(this->target_time / 10) * 20;

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
			//プロジェクション。
			NBsys::NGeometry::Geometry_Matrix_44 t_projection;
			t_projection.Set_PerspectiveProjectionMatrix(static_cast<f32>(s_width),static_cast<f32>(s_height),this->camera_fov_deg,this->camera_near,this->camera_far);

			//ビュー。
			NBsys::NGeometry::Geometry_Matrix_44 t_view;
			t_view.Set_ViewMatrix(this->camera_target,this->camera_position,this->camera_up);

			//ライン描画。
			this->drawline_manager->DrawLine(NBsys::NGeometry::Geometry_Vector3(-100,0,0),NBsys::NGeometry::Geometry_Vector3(100,0,0),NBsys::NColor::Color_F(1.0f,0.0f,0.0f,1.0f));
			this->drawline_manager->DrawLine(NBsys::NGeometry::Geometry_Vector3(0,-100,0),NBsys::NGeometry::Geometry_Vector3(0,100,0),NBsys::NColor::Color_F(0.0f,1.0f,0.0f,1.0f));
			this->drawline_manager->DrawLine(NBsys::NGeometry::Geometry_Vector3(0,0,-100),NBsys::NGeometry::Geometry_Vector3(0,0,100),NBsys::NColor::Color_F(0.0f,0.0f,1.0f,1.0f));

			{
				NBsys::NGeometry::Geometry_Matrix_44 t_matrix_a;
				NBsys::NGeometry::Geometry_Matrix_44 t_matrix_b;

				//fromからaを向くマトリックス。
				t_matrix_a.Set_Lookat(this->target_from,this->target_to_a,NBsys::NGeometry::Geometry_Vector3(0,1,0));
				//fromからbを向くマトリックス。
				t_matrix_b.Set_Lookat(this->target_from,this->target_to_b,NBsys::NGeometry::Geometry_Vector3(0,1,0));

				//fromからaを向く姿勢。
				NBsys::NGeometry::Geometry_Quaternion t_quat_a = t_matrix_a.Make_Quaternion();
				//fromからbを向く姿勢。
				NBsys::NGeometry::Geometry_Quaternion t_quat_b = t_matrix_b.Make_Quaternion();

				//ライン描画。
				{
					NBsys::NGeometry::Geometry_Matrix_44 t_matrix_a = t_quat_a.Make_Matrix();
					NBsys::NGeometry::Geometry_Vector3 t_to_a = this->target_from + t_matrix_a.Make_AxisZ() * 5;
					this->drawline_manager->DrawLine(this->target_from,t_to_a,NBsys::NColor::Color_F(0.0f,0.0f,1.0f,1.0f));
				}

				//ライン描画。
				{
					NBsys::NGeometry::Geometry_Matrix_44 t_matrix_b = t_quat_b.Make_Matrix();
					NBsys::NGeometry::Geometry_Vector3 t_to_b = this->target_from + t_matrix_b.Make_AxisZ() * 5;
					this->drawline_manager->DrawLine(this->target_from,t_to_b,NBsys::NColor::Color_F(1.0f,0.0f,0.0f,1.0f));
				}

				//ライン描画。
				{
					NBsys::NGeometry::Geometry_Matrix_44 t_matrix_b = t_quat_a.Make_Slerp(t_quat_b,Math::absf(Math::cosf(this->target_time)));
					NBsys::NGeometry::Geometry_Vector3 t_to_b = this->target_from + t_matrix_b.Make_AxisZ() * 20;
					this->drawline_manager->DrawLine(this->target_from,t_to_b,NBsys::NColor::Color_F(1.0f,1.0f,1.0f,1.0f));
				}
			}

			//ライン描画。
			this->drawline_manager->Update(t_view * t_projection);
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
	TAGLOG("main","DEF_TEST10");

	NBsys::NFile::StartSystem(1);
	NBsys::NFile::SetRoot(0,L"./project_test");

	s_window.reset(new NBsys::NWindow::Window());
	s_d3d11.reset(new NBsys::ND3d11::D3d11());
	s_app.reset(new App());

	s_window->Create(L"sample",s_width,s_height);
	s_d3d11->Render_Create(s_window,s_width,s_height);

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

	NBsys::NFile::EndSystemRequest();
	NBsys::NFile::EndWaitSystem();

	return;
}
#endif

