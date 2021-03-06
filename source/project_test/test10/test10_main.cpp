﻿

/**
 * Copyright (c) blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE.txt
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief テスト。
*/


/** include
*/
#pragma warning(push)
#pragma warning(disable:4464)
#include "../entry.h"
#pragma warning(pop)


/** include
*/
#pragma warning(push)
#pragma warning(disable:4464)
#include "../common/common_app_base.h"
#pragma warning(pop)


/** warning

4710 : この関数はインライン展開のために選択されましたが、コンパイラはインライン展開を実行しませんでした。

*/
#pragma warning(disable:4710)


/** NTest
*/
#if(DEF_TEST_INDEX == 10)
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
			this->camera_position.Set_X(NMath::cos_f(this->camera_time / 10) * 20);
			this->camera_position.Set_Y(NMath::sin_f(this->camera_time / 10) * 20);
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
				t_projection.Set_PerspectiveProjectionMatrix(this->size,this->camera_fov_deg,this->camera_near,this->camera_far);

				//ビュー。
				t_view.Set_ViewMatrix(this->camera_target,this->camera_position,this->camera_up);

				{
					//ライン描画。
					this->drawline->DrawLine(NBsys::NGeometry::Geometry_Vector3(-100,0,0),NBsys::NGeometry::Geometry_Vector3(100,0,0),NBsys::NColor::Color_F(1.0f,0.0f,0.0f,1.0f));
					this->drawline->DrawLine(NBsys::NGeometry::Geometry_Vector3(0,-100,0),NBsys::NGeometry::Geometry_Vector3(0,100,0),NBsys::NColor::Color_F(0.0f,1.0f,0.0f,1.0f));
					this->drawline->DrawLine(NBsys::NGeometry::Geometry_Vector3(0,0,-100),NBsys::NGeometry::Geometry_Vector3(0,0,100),NBsys::NColor::Color_F(0.0f,0.0f,1.0f,1.0f));
				}

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
						NBsys::NGeometry::Geometry_Matrix_44 t_temp = t_quat_a.Make_Matrix();
						NBsys::NGeometry::Geometry_Vector3 t_to_a = this->target_from + t_temp.Make_AxisZ() * 5;
						this->drawline->DrawLine(this->target_from,t_to_a,NBsys::NColor::Color_F(0.0f,0.0f,1.0f,1.0f));
					}

					//ライン描画。
					{
						NBsys::NGeometry::Geometry_Matrix_44 t_temp = t_quat_b.Make_Matrix();
						NBsys::NGeometry::Geometry_Vector3 t_to_b = this->target_from + t_temp.Make_AxisZ() * 5;
						this->drawline->DrawLine(this->target_from,t_to_b,NBsys::NColor::Color_F(1.0f,0.0f,0.0f,1.0f));
					}

					//ライン描画。
					{
						NBsys::NGeometry::Geometry_Matrix_44 t_temp = t_quat_a.Make_Slerp(t_quat_b,NMath::abs_f(NMath::cos_f(this->camera_time)));
						NBsys::NGeometry::Geometry_Vector3 t_to_b = this->target_from + t_temp.Make_AxisZ() * 20;
						this->drawline->DrawLine(this->target_from,t_to_b,NBsys::NColor::Color_F(1.0f,1.0f,1.0f,1.0f));
					}
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
		t_app->Finalize();
		return;
	}


}
#endif

