

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


/** include
*/
#include "../common/common_app_base.h"


/** NTest
*/
#if(DEF_TEST_INDEX == 12)
namespace NTest
{
	/** App
	*/
	class App : public NCommon::App_Base
	{
	private:

		/** step
		*/
		s32 step;

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

		/** windowmenu_texture
		*/
		sharedptr<NCommon::Common_WindowMenu_Texture> windowmenu_texture;

	public:

		/** constructor
		*/
		App()
			:
			step(0)
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
			if(this->step == 0){
				//テクスチャ。
				this->windowmenu_texture.reset(new NCommon::Common_WindowMenu_Texture(L"テクスチャー",150.0f,150.0f,this->d3d11));
				NBsys::NWindowMenu::GetSystemInstance()->Add(this->windowmenu_texture);

				//ログ。
				this->windowmenu_log.reset(new NCommon::Common_WindowMenu_Log(200.0f,200.0f));
				NBsys::NWindowMenu::GetSystemInstance()->Add(this->windowmenu_log);

				this->step++;
			}else{
				this->camera_time += a_delta;

				//カメラ回転。
				this->camera_position.x = Math::cos_f(this->camera_time / 10) * 20;
				this->camera_position.z = Math::sin_f(this->camera_time / 10) * 20;

				//FPS。
				{
					char t_buffer[32];
					STLWString t_string = VASTRING(t_buffer,sizeof(t_buffer),L"%d",static_cast<s32>(1.0f / a_delta));

					{
						sharedptr<NCommon::Render2D_Item_Font> t_font(new NCommon::Render2D_Item_Font(99999));
						t_font->x = 0.0f;
						t_font->y = 0.0f;
						t_font->w = 0.0f;
						t_font->h = 0.0f;
						t_font->clip = false;
						t_font->size = 16.0f;
						t_font->fonttexture_type = NBsys::ND3d11::D3d11_FontTextureType::SFont;
						t_font->color = NBsys::NColor::Color_F(0.0f,1.0f,1.0f,1.0f);
						t_font->alignment_x = -1;
						t_font->alignment_y = -1;
						t_font->string = t_string;

						this->render2d->Draw(t_font);
					}
				}

				{
					//マウス。
					const NBsys::NPad::TouchValue& t_mouse_l = NBsys::NPad::GetVirtualPad(NCommon::Pad_Device::Type::Pad1)->GetTouchValue(NBsys::NPad::Pad_Virtual::TouchType::MOUSEL);

					//文字描画。
					if(t_mouse_l.flag){
						char t_buffer[32];
						STLWString t_string = VASTRING(t_buffer,sizeof(t_buffer),L"%d %d",static_cast<s32>(t_mouse_l.x),static_cast<s32>(t_mouse_l.y));
						
						{
							sharedptr<NCommon::Render2D_Item_Font> t_font(new NCommon::Render2D_Item_Font(99999));
							t_font->x = t_mouse_l.x + 50;
							t_font->y = t_mouse_l.y + 50;
							t_font->w = 0.0f;
							t_font->h = 0.0f;
							t_font->clip = false;
							t_font->size = 16.0f;
							t_font->fonttexture_type = NBsys::ND3d11::D3d11_FontTextureType::SFont;
							t_font->color = NBsys::NColor::Color_F(0.0f,1.0f,1.0f,1.0f);
							t_font->alignment_x = -1;
							t_font->alignment_y = 0;
							t_font->string = t_string;

							this->render2d->Draw(t_font);
						}

						{
							sharedptr<NCommon::Render2D_Item_Font> t_font(new NCommon::Render2D_Item_Font(99999));
							t_font->x = t_mouse_l.x - 50;
							t_font->y = t_mouse_l.y - 50;
							t_font->w = 0.0f;
							t_font->h = 0.0f;
							t_font->clip = false;
							t_font->size = 16.0f;
							t_font->fonttexture_type = NBsys::ND3d11::D3d11_FontTextureType::SFont;
							t_font->color = NBsys::NColor::Color_F(0.0f,1.0f,1.0f,1.0f);
							t_font->alignment_x = -1;
							t_font->alignment_y = 0;
							t_font->string = t_string;

							this->render2d->Draw(t_font);
						}
					}

					{
						sharedptr<NCommon::Render2D_Item_Font> t_font(new NCommon::Render2D_Item_Font(99999));
						t_font->x = 200;
						t_font->y = 200;
						t_font->w = 0.0f;
						t_font->h = 0.0f;
						t_font->clip = false;
						t_font->size = 32.0f;
						t_font->fonttexture_type = NBsys::ND3d11::D3d11_FontTextureType::MFont;
						t_font->color = NBsys::NColor::Color_F(1.0f,1.0f,1.0f,1.0f);
						t_font->alignment_x = -1;
						t_font->alignment_y = 0;
						t_font->string = L"あいうえお";

						this->render2d->Draw(t_font);
					}

					{
						sharedptr<NCommon::Render2D_Item_Font> t_font(new NCommon::Render2D_Item_Font(99999));
						t_font->x = this->width / 2.0f;
						t_font->y = this->height / 2.0f;
						t_font->w = 0.0f;
						t_font->h = 0.0f;
						t_font->clip = false;
						t_font->size = 32.0f;
						t_font->fonttexture_type = NBsys::ND3d11::D3d11_FontTextureType::MFont;
						t_font->color = NBsys::NColor::Color_F(1.0f,1.0f,1.0f,1.0f);
						t_font->alignment_x = -1;
						t_font->alignment_y = 0;
						t_font->string = L"あいうえお";

						this->render2d->Draw(t_font);
					}
				}
			}
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

				//深度ステンシル。チェックあり。書き込みあり。
				this->d3d11->Render_SetDepthStencilState(this->depthstencilstate_check_on_write_on_id);

				//ライン描画。
				this->drawline->Render(t_view * t_projection);
			}

			//２Ｄ描画。
			{
				//クリア。
				this->d3d11->Render_ClearDepthStencilView();

				//深度ステンシル。チェックなし。書き込みなし。
				this->d3d11->Render_SetDepthStencilState(this->depthstencilstate_check_off_write_off_id);

				//レクト描画。
				//文字描画。
				{
					//描画。
					this->render2d->Render(/*t_view * t_projection*/);
				}

				//ウィンドウメニュー。
				{
					NBsys::NWindowMenu::GetSystemInstance()->Draw();

					//描画。
					this->render2d->Render(/*t_view * t_projection*/);
				}
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

