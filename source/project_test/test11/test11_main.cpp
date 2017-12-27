

/**
 * Copyright (c) 2016-2017 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE.txt
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief テスト。
*/


/** include
*/
#include "../entry.h"


/** include
*/
#include "../common/common_app_base.h"


/** NTest
*/
#if(DEF_TEST_INDEX == 11)
namespace NTest
{
	/** App
	*/
	class App : public NCommon::App_Base
	{
	private:

		/** カメラ。
		*/
		NBsys::NGeometry::Geometry_Vector3 camera_position;
		NBsys::NGeometry::Geometry_Vector3 camera_up;
		NBsys::NGeometry::Geometry_Vector3 camera_target;
		f32 camera_fov_deg;
		f32 camera_near;
		f32 camera_far;
		f32 camera_time;

		/** ターゲット。
		*/
		NBsys::NGeometry::Geometry_Vector3 target_from;
		NBsys::NGeometry::Geometry_Vector3 target_to_a;
		NBsys::NGeometry::Geometry_Vector3 target_to_b;

	public:

		/** constructor
		*/
		App()
		{
			//カメラ。
			this->camera_position = NBsys::NGeometry::Geometry_Vector3(1.0f,10.0f,-20.0f);
			this->camera_up = NBsys::NGeometry::Geometry_Vector3(0.0f,1.0f,0.0f);
			this->camera_target = NBsys::NGeometry::Geometry_Vector3(0.0f,0.0f,0.0f);
			this->camera_fov_deg = 60.0f;
			this->camera_near = 0.1f;
			this->camera_far = 1000.0f;
			this->camera_time = 0.0f;

			//ターゲット。
			this->target_from.Set(10,10,10);
			this->target_to_a.Set(0,0,10);
			this->target_to_b.Set(3,0,0);
		}

		/** destructor
		*/
		nonvirtual ~App()
		{
		}

	public:

		/** 更新。
		*/
		virtual void Update(f32 a_delta)
		{
			this->camera_time += a_delta;

			//カメラ回転。
			this->camera_position.x = Math::cos_f(this->camera_time / 10) * 20;
			this->camera_position.z = Math::sin_f(this->camera_time / 10) * 20;
		}

		/** 描画命令呼び出し。
		*/
		virtual void Render()
		{
			//プロジェクション。
			NBsys::NGeometry::Geometry_Matrix_44 t_projection;

			//ビュー。
			NBsys::NGeometry::Geometry_Matrix_44 t_view;

			//３Ｄ描画。
			{
				//プロジェクション。
				t_projection.Set_PerspectiveProjectionMatrix(static_cast<f32>(this->width),static_cast<f32>(this->height),this->camera_fov_deg,this->camera_near,this->camera_far);

				//ビュー。
				t_view.Set_ViewMatrix(this->camera_target,this->camera_position,this->camera_up);

				{
					//ライン描画。
					this->drawline->DrawLine(NBsys::NGeometry::Geometry_Vector3(-100,0,0),NBsys::NGeometry::Geometry_Vector3(100,0,0),NBsys::NColor::Color_F(1.0f,0.0f,0.0f,1.0f));
					this->drawline->DrawLine(NBsys::NGeometry::Geometry_Vector3(0,-100,0),NBsys::NGeometry::Geometry_Vector3(0,100,0),NBsys::NColor::Color_F(0.0f,1.0f,0.0f,1.0f));
					this->drawline->DrawLine(NBsys::NGeometry::Geometry_Vector3(0,0,-100),NBsys::NGeometry::Geometry_Vector3(0,0,100),NBsys::NColor::Color_F(0.0f,0.0f,1.0f,1.0f));
				}

				//ライン描画。
				this->drawline->Render(t_view * t_projection);
			}
		}
	};


	/** Test_Main
	*/
	void Test_Main()
	{
		sharedptr<App> t_app(new App());
		t_app->Initialize();
		t_app->Main();
		t_app->Delete();
		return;
	}


}
#endif

