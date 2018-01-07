

/**
 * Copyright (c) 2016-2017 blueback
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

		/** pack_file
		*/
		sharedptr<NBsys::NFile::File_Pack_Object> pack_file;

		/** wave_file
		*/
		sharedptr<NBsys::NFile::File_Object> wave_file;

		/** wave
		*/
		sharedptr<NBsys::NWave::Wave> wave;

		/** soundbuffer_id
		*/
		s32 soundbuffer_id;

		/** soundbuffer_lastplay_id
		*/
		s32 soundbuffer_lastplay_id;

		/** step
		*/
		s32 step;

	public:

		/** constructor
		*/
		App()
			:
			soundbuffer_id(-1),
			soundbuffer_lastplay_id(-1),
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

		/** Load
		*/
		void Load()
		{
			if(this->soundbuffer_id < 0){
				this->soundbuffer_id = NBsys::NDsound::CreateSoundBuffer(this->wave,false);
			}
		}

		/** UnLoad
		*/
		void UnLoad()
		{
			if(this->soundbuffer_id >= 0){
				NBsys::NDsound::DeleteSoundBuffer(this->soundbuffer_id);
				this->soundbuffer_id = -1;
			}
		}

		/** Play
		*/
		void Play()
		{
			if(this->soundbuffer_id >= 0){
				this->soundbuffer_lastplay_id = NBsys::NDsound::Play(this->soundbuffer_id,true,false,true);
			}
		}

		/** 初期化更新。
		*/
		virtual bool Initialize_Update()
		{
			//テクスチャ。
			if(this->windowmenu_texture == nullptr){
				this->windowmenu_texture.reset(new NCommon::WindowMenu_Texture(150.0f,150.0f,this->d3d11));
				NBsys::NWindowMenu::GetSystemInstance()->Add(this->windowmenu_texture);
			}

			//ログ。
			if(this->windowmenu_log == nullptr){
				this->windowmenu_log.reset(new NCommon::WindowMenu_Log(200.0f,200.0f));
				NBsys::NWindowMenu::GetSystemInstance()->Add(this->windowmenu_log);
			}

			//ボタンリスト。
			if(this->windowmenu_buttonlist == nullptr){
				this->windowmenu_buttonlist.reset(new NCommon::WindowMenu_ButtonList(300.0f,300.0f,this->d3d11));
				NBsys::NWindowMenu::GetSystemInstance()->Add(this->windowmenu_buttonlist);
			}

			return true;
		}

		/** 更新。
		*/
		virtual void Update(f32 a_delta)
		{
			this->camera_time += a_delta;

			//カメラ回転。
			this->camera_position.Set_X(NMath::cos_f(this->camera_time / 10) * 20);
			this->camera_position.Set_Y(NMath::sin_f(this->camera_time / 10) * 20);

			if(this->step == 0){
				this->pack_file.reset(new NBsys::NFile::File_Pack_Object(NCommon::DeviceIndex::TestData,L"秋山裕和n77.pac",L"sound"));
				this->step++;
			}else if(this->step == 1){
				if(this->pack_file->IsBusy() == false){
					ASSERT(this->pack_file->GetErrorCode() == ErrorCode::Success);
					this->step++;
				}
			}else if(this->step == 2){
				this->wave_file.reset(new NBsys::NFile::File_Object(NCommon::DeviceIndex::TestData,L"sound/n77.ogg",-1,nullptr,0));
				this->step++;
			}else if(this->step == 3){
				if(this->wave_file->IsBusy() == false){
					this->wave = NBsys::NWave::CreateWave_Ogg(this->wave_file->GetLoadData(),static_cast<s32>(this->wave_file->GetLoadSize()),L"n77_ogg");

					this->windowmenu_buttonlist->AddButton(L"Capture",std::bind(&App::Capture,this));
					this->windowmenu_buttonlist->AddButton(L"Load",std::bind(&App::Load,this));
					this->windowmenu_buttonlist->AddButton(L"UnLoad",std::bind(&App::UnLoad,this));
					this->windowmenu_buttonlist->AddButton(L"Play",std::bind(&App::Play,this));
					this->step++;
				}
			}else if(this->step == 4){

				//最後に再生されたサウンドバッファのチェック。
				if(this->soundbuffer_lastplay_id >= 0){
					if(NBsys::NDsound::IsPlay(this->soundbuffer_lastplay_id) == true){
						{
							sharedptr<NCommon::Render2D_Item_Font> t_font(new NCommon::Render2D_Item_Font(99999));
							t_font->x = 0.0f;
							t_font->y = 50.0f;
							t_font->w = 0.0f;
							t_font->h = 0.0f;
							t_font->clip = false;
							t_font->size = 16.0f;
							t_font->fonttexture_type = NBsys::ND3d11::D3d11_FontTextureType::SFont;
							t_font->color = NBsys::NColor::Color_F(0.0f,1.0f,1.0f,1.0f);
							t_font->alignment_x = -1;
							t_font->alignment_y = -1;
							t_font->string = L"Play Now";

							this->render2d->Draw(t_font);
						}
					}else{
						this->soundbuffer_lastplay_id = -1;
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

				//ライン描画。
				this->drawline->Render(t_view * t_projection);
			}

			//２Ｄ描画。
			{
				//クリア。
				this->d3d11->Render_ClearDepthStencilView();

				//深度ステンシル。チェックなし。書き込みなし。
				this->d3d11->Render_SetDepthStencilState(this->depthstencilstate_check_off_write_off_id);

				//文字描画。
				{
					//描画。
					this->render2d->Render();
				}

				//ウィンドウメニュー。
				{
					NBsys::NWindowMenu::GetSystemInstance()->Draw();

					//描画。
					this->render2d->Render();
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
		t_app->Finalize();
		return;
	}


}
#endif

