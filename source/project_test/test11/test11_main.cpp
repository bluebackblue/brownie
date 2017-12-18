

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
#if(DEF_TEST_INDEX == 11)


/** include
*/
#include "./test11_main.h"


/** include
*/
#include "../common/common_drawline.h"


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


/** ライン描画。
*/
sharedptr<NCommon::DrawLine_Manager> s_drawline_manager;


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

	/** ブレンドステータス。
	*/
	s32 blendstate_id;

	/** ラスタライザー。
	*/
	s32 rasterizerstate_cull_back_id;
	s32 rasterizerstate_cull_none_id;

	/** カメラ。
	*/
	NBsys::NGeometry::Geometry_Vector3 camera_position;
	NBsys::NGeometry::Geometry_Vector3 camera_up;
	NBsys::NGeometry::Geometry_Vector3 camera_target;
	f32 camera_fov_deg;
	f32 camera_near;
	f32 camera_far;
	f32 camera_time;

	/** 経路探査。
	*/
	NBsys::NRootSearch::RootSearch_Data rootsearch_data;

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
		switch(this->step){
		case 0:
			{
				//ライン描画。
				s_drawline_manager->Initialize_Update();
				if(s_drawline_manager->IsInitialized() == false){
					break;
				}

				//ブレンドステータス。
				this->blendstate_id = s_d3d11->CreateBlendState(true);

				//ラスタライザー。
				this->rasterizerstate_cull_back_id = s_d3d11->CreateRasterizerState(NBsys::ND3d11::D3d11_CullType::Back);
				this->rasterizerstate_cull_none_id = s_d3d11->CreateRasterizerState(NBsys::ND3d11::D3d11_CullType::None);

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

				//経路探査。
				{
					this->rootsearch_data.Clear();

					NBsys::NRootSearch::RootSearch_NodeIndex t_c = this->rootsearch_data.AddNode(NBsys::NGeometry::Geometry_Vector3(1,0,1),2,true);
					NBsys::NRootSearch::RootSearch_NodeIndex t_1 = this->rootsearch_data.AddNode(NBsys::NGeometry::Geometry_Vector3(10,0,10),2,true);
					NBsys::NRootSearch::RootSearch_NodeIndex t_2 = this->rootsearch_data.AddNode(NBsys::NGeometry::Geometry_Vector3(-10,0,-10),2,true);
					NBsys::NRootSearch::RootSearch_NodeIndex t_e = this->rootsearch_data.AddNode(NBsys::NGeometry::Geometry_Vector3(15,0,-15),2,true);

					{
						s32 t_cost = static_cast<s32>((this->rootsearch_data.GetNode(t_c).GetPos() - this->rootsearch_data.GetNode(t_1).GetPos()).Length());
						this->rootsearch_data.Connect(t_c,t_1,true,t_cost);
					}

					{
						s32 t_cost = static_cast<s32>((this->rootsearch_data.GetNode(t_c).GetPos() - this->rootsearch_data.GetNode(t_2).GetPos()).Length());
						this->rootsearch_data.Connect(t_c,t_2,true,t_cost);
					}

					{
						s32 t_cost = static_cast<s32>((this->rootsearch_data.GetNode(t_1).GetPos() - this->rootsearch_data.GetNode(t_e).GetPos()).Length());
						this->rootsearch_data.Connect(t_1,t_e,true,t_cost);
					}

					{
						s32 t_cost = static_cast<s32>((this->rootsearch_data.GetNode(t_2).GetPos() - this->rootsearch_data.GetNode(t_e).GetPos()).Length());
						this->rootsearch_data.Connect(t_2,t_e,true,t_cost);
					}
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

				{
					//this->rootsearch.SearchRoot(NBsys::NGeometry::Geometry_Vector3(0,0,0),NBsys::NGeometry::Geometry_Vector3(10,0,-10));

					/*
					for(s32 ii=0;ii<static_cast<s32>(this->rootsearch.node_pool.size());ii++){
						NBsys::NGeometry::Geometry_Vector3 t_start = this->rootsearch.node_pool[ii].pos;
						for(s32 jj=0;jj<static_cast<s32>(this->rootsearch.node_pool[ii].connect_index_list.size());jj++){
							s32 t_end_index = this->rootsearch.node_pool[ii].connect_index_list[jj];
							NBsys::NGeometry::Geometry_Vector3 t_end = this->rootsearch.node_pool[t_end_index].pos;
							this->drawline_manager->DrawLine(t_start,t_end,NBsys::NColor::Color_F(1.0f,1.0f,1.0f,1.0f));
						}
					}
					*/
				}

				//ライン描画。
				s_drawline_manager->Render(t_view * t_projection);
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

	s_window.reset(new NBsys::NWindow::Window());
	s_d3d11.reset(new NBsys::ND3d11::D3d11());
	s_app.reset(new App());

	s_window->Create(DEF_TEST_TITLE,s_width,s_height);
	s_d3d11->Render_Create(s_window,s_width,s_height);

	//ライン描画。
	s_drawline_manager.reset(new NCommon::DrawLine_Manager(s_d3d11));

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

	NBsys::NFile::EndSystemRequest();
	NBsys::NFile::EndWaitSystem();

	return;
}
#endif

