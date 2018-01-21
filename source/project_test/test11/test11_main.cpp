

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

		/** pack
		*/
		sharedptr<NBsys::NFile::File_Pack_Object> pack_1;
		sharedptr<NBsys::NFile::File_Pack_Object> pack_2;

		/** file
		*/
		sharedptr<NBsys::NFile::File_Object> file_bgm;
		sharedptr<NBsys::NFile::File_Object> file_se1;
		sharedptr<NBsys::NFile::File_Object> file_se2;
		sharedptr<NBsys::NFile::File_Object> file_se3;
		sharedptr<NBsys::NFile::File_Object> file_se4;
		sharedptr<NBsys::NFile::File_Object> file_se5;
		sharedptr<NBsys::NFile::File_Object> file_se6;
		sharedptr<NBsys::NFile::File_Object> file_se7;
		sharedptr<NBsys::NFile::File_Object> file_se8;
		sharedptr<NBsys::NFile::File_Object> file_se9;

		/** wave
		*/
		sharedptr<NBsys::NWave::Wave> wave_se1;
		sharedptr<NBsys::NWave::Wave> wave_se2;
		sharedptr<NBsys::NWave::Wave> wave_se3;
		sharedptr<NBsys::NWave::Wave> wave_se4;
		sharedptr<NBsys::NWave::Wave> wave_se5;
		sharedptr<NBsys::NWave::Wave> wave_se6;
		sharedptr<NBsys::NWave::Wave> wave_se7;
		sharedptr<NBsys::NWave::Wave> wave_se8;
		sharedptr<NBsys::NWave::Wave> wave_se9;

		/** soundbuffer_id
		*/
		s32 soundbuffer_id_bgm;
		s32 soundbuffer_id_se1;
		s32 soundbuffer_id_se2;
		s32 soundbuffer_id_se3;
		s32 soundbuffer_id_se4;
		s32 soundbuffer_id_se5;
		s32 soundbuffer_id_se6;
		s32 soundbuffer_id_se7;
		s32 soundbuffer_id_se8;
		s32 soundbuffer_id_se9;

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
			soundbuffer_id_bgm(-1),
			soundbuffer_id_se1(-1),
			soundbuffer_id_se2(-1),
			soundbuffer_id_se3(-1),
			soundbuffer_id_se4(-1),
			soundbuffer_id_se5(-1),
			soundbuffer_id_se6(-1),
			soundbuffer_id_se7(-1),
			soundbuffer_id_se8(-1),
			soundbuffer_id_se9(-1),
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
			if(this->soundbuffer_id_bgm < 0){
				this->soundbuffer_id_bgm = NBsys::NDsound::CreateStreamSoundBuffer(new NCommon::SoundStreamCallback_Ogg(this->file_bgm),false);
			}
			if(this->soundbuffer_id_se1 < 0){
				this->soundbuffer_id_se1 = NBsys::NDsound::CreateSoundBuffer(this->wave_se1,false);
			}
			if(this->soundbuffer_id_se2 < 0){
				this->soundbuffer_id_se2 = NBsys::NDsound::CreateSoundBuffer(this->wave_se2,false);
			}
			if(this->soundbuffer_id_se3 < 0){
				this->soundbuffer_id_se3 = NBsys::NDsound::CreateSoundBuffer(this->wave_se3,false);
			}
			if(this->soundbuffer_id_se4 < 0){
				this->soundbuffer_id_se4 = NBsys::NDsound::CreateSoundBuffer(this->wave_se4,false);
			}
			if(this->soundbuffer_id_se5 < 0){
				this->soundbuffer_id_se5 = NBsys::NDsound::CreateSoundBuffer(this->wave_se5,false);
			}
			if(this->soundbuffer_id_se6 < 0){
				this->soundbuffer_id_se6 = NBsys::NDsound::CreateSoundBuffer(this->wave_se6,false);
			}
			if(this->soundbuffer_id_se7 < 0){
				this->soundbuffer_id_se7 = NBsys::NDsound::CreateSoundBuffer(this->wave_se7,false);
			}
			if(this->soundbuffer_id_se8 < 0){
				this->soundbuffer_id_se8 = NBsys::NDsound::CreateSoundBuffer(this->wave_se8,false);
			}
			if(this->soundbuffer_id_se9 < 0){
				this->soundbuffer_id_se9 = NBsys::NDsound::CreateSoundBuffer(this->wave_se9,false);
			}

			ThreadSleep(16);
		}

		/** UnLoad
		*/
		void UnLoad()
		{
			if(this->soundbuffer_id_bgm >= 0){
				NBsys::NDsound::DeleteSoundBuffer(this->soundbuffer_id_bgm);
				this->soundbuffer_id_bgm = -1;
			}
			if(this->soundbuffer_id_se1 >= 0){
				NBsys::NDsound::DeleteSoundBuffer(this->soundbuffer_id_se1);
				this->soundbuffer_id_se1 = -1;
			}
			if(this->soundbuffer_id_se2 >= 0){
				NBsys::NDsound::DeleteSoundBuffer(this->soundbuffer_id_se2);
				this->soundbuffer_id_se2 = -1;
			}
			if(this->soundbuffer_id_se3 >= 0){
				NBsys::NDsound::DeleteSoundBuffer(this->soundbuffer_id_se3);
				this->soundbuffer_id_se3 = -1;
			}
			if(this->soundbuffer_id_se4 >= 0){
				NBsys::NDsound::DeleteSoundBuffer(this->soundbuffer_id_se4);
				this->soundbuffer_id_se4 = -1;
			}
			if(this->soundbuffer_id_se5 >= 0){
				NBsys::NDsound::DeleteSoundBuffer(this->soundbuffer_id_se5);
				this->soundbuffer_id_se5 = -1;
			}
			if(this->soundbuffer_id_se6 >= 0){
				NBsys::NDsound::DeleteSoundBuffer(this->soundbuffer_id_se6);
				this->soundbuffer_id_se6 = -1;
			}
			if(this->soundbuffer_id_se7 >= 0){
				NBsys::NDsound::DeleteSoundBuffer(this->soundbuffer_id_se7);
				this->soundbuffer_id_se7 = -1;
			}
			if(this->soundbuffer_id_se8 >= 0){
				NBsys::NDsound::DeleteSoundBuffer(this->soundbuffer_id_se8);
				this->soundbuffer_id_se8 = -1;
			}
			if(this->soundbuffer_id_se9 >= 0){
				NBsys::NDsound::DeleteSoundBuffer(this->soundbuffer_id_se9);
				this->soundbuffer_id_se9 = -1;
			}
		}

		/** Play
		*/
		void Play()
		{
			switch(GlobalRand_Get().Get(30)){
			case 0:if(this->soundbuffer_id_se1 >= 0){NBsys::NDsound::OnceShotPlay(this->soundbuffer_id_se1);}DEBUGLOG("play se1\n");break;
			case 1:if(this->soundbuffer_id_se2 >= 0){NBsys::NDsound::OnceShotPlay(this->soundbuffer_id_se2);}DEBUGLOG("play se2\n");break;
			case 2:if(this->soundbuffer_id_se3 >= 0){NBsys::NDsound::OnceShotPlay(this->soundbuffer_id_se3);}DEBUGLOG("play se3\n");break;
			case 3:if(this->soundbuffer_id_se4 >= 0){NBsys::NDsound::OnceShotPlay(this->soundbuffer_id_se4);}DEBUGLOG("play se4\n");break;
			case 4:if(this->soundbuffer_id_se5 >= 0){NBsys::NDsound::OnceShotPlay(this->soundbuffer_id_se5);}DEBUGLOG("play se5\n");break;
			case 5:if(this->soundbuffer_id_se6 >= 0){NBsys::NDsound::OnceShotPlay(this->soundbuffer_id_se6);}DEBUGLOG("play se6\n");break;
			case 6:if(this->soundbuffer_id_se7 >= 0){NBsys::NDsound::OnceShotPlay(this->soundbuffer_id_se7);}DEBUGLOG("play se7\n");break;
			case 7:if(this->soundbuffer_id_se8 >= 0){NBsys::NDsound::OnceShotPlay(this->soundbuffer_id_se8);}DEBUGLOG("play se8\n");break;
			case 8:if(this->soundbuffer_id_se9 >= 0){NBsys::NDsound::OnceShotPlay(this->soundbuffer_id_se9);}DEBUGLOG("play se9\n");break;
			}
		}

		/** Discord
		*/
		void Discord()
		{
			this->SendDiscord(L"テスト\nテスト\n");
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
				this->pack_1.reset(new NBsys::NFile::File_Pack_Object(NCommon::DeviceIndex::TestData,L"秋山裕和n77.pac",L"sound"));
				this->pack_2.reset(new NBsys::NFile::File_Pack_Object(NCommon::DeviceIndex::TestData,L"秋山裕和se.pac",L"sound"));
				this->step++;
			}else if(this->step == 1){
				if(this->pack_1->IsBusy() == true){
				}else if(this->pack_2->IsBusy() == true){
				}else{
					ASSERT(this->pack_1->GetErrorCode() == ErrorCode::Success);
					ASSERT(this->pack_2->GetErrorCode() == ErrorCode::Success);
					this->pack_1.reset();
					this->pack_2.reset();

					this->step++;
				}
			}else if(this->step == 2){
				this->file_bgm.reset(new NBsys::NFile::File_Object(NCommon::DeviceIndex::TestData,L"sound/n77.ogg",-1,nullptr,0));
				this->file_se1.reset(new NBsys::NFile::File_Object(NCommon::DeviceIndex::TestData,L"sound/se1.ogg",-1,nullptr,0));
				this->file_se2.reset(new NBsys::NFile::File_Object(NCommon::DeviceIndex::TestData,L"sound/se2.ogg",-1,nullptr,0));
				this->file_se3.reset(new NBsys::NFile::File_Object(NCommon::DeviceIndex::TestData,L"sound/se3.ogg",-1,nullptr,0));
				this->file_se4.reset(new NBsys::NFile::File_Object(NCommon::DeviceIndex::TestData,L"sound/se4.ogg",-1,nullptr,0));
				this->file_se5.reset(new NBsys::NFile::File_Object(NCommon::DeviceIndex::TestData,L"sound/se5.ogg",-1,nullptr,0));
				this->file_se6.reset(new NBsys::NFile::File_Object(NCommon::DeviceIndex::TestData,L"sound/se6.ogg",-1,nullptr,0));
				this->file_se7.reset(new NBsys::NFile::File_Object(NCommon::DeviceIndex::TestData,L"sound/se7.ogg",-1,nullptr,0));
				this->file_se8.reset(new NBsys::NFile::File_Object(NCommon::DeviceIndex::TestData,L"sound/se8.ogg",-1,nullptr,0));
				this->file_se9.reset(new NBsys::NFile::File_Object(NCommon::DeviceIndex::TestData,L"sound/se9.ogg",-1,nullptr,0));
				this->step++;
			}else if(this->step == 3){
				if(this->file_bgm->IsBusy() == true){
				}else if(this->file_se1->IsBusy() == true){
				}else if(this->file_se2->IsBusy() == true){
				}else if(this->file_se3->IsBusy() == true){
				}else if(this->file_se4->IsBusy() == true){
				}else if(this->file_se5->IsBusy() == true){
				}else if(this->file_se6->IsBusy() == true){
				}else if(this->file_se7->IsBusy() == true){
				}else if(this->file_se8->IsBusy() == true){
				}else if(this->file_se9->IsBusy() == true){
				}else{
					this->wave_se1 = NBsys::NWave::CreateWave_Ogg(this->file_se1->GetLoadData(),static_cast<s32>(this->file_se1->GetLoadSize()),L"se1");
					this->wave_se2 = NBsys::NWave::CreateWave_Ogg(this->file_se2->GetLoadData(),static_cast<s32>(this->file_se2->GetLoadSize()),L"se2");
					this->wave_se3 = NBsys::NWave::CreateWave_Ogg(this->file_se3->GetLoadData(),static_cast<s32>(this->file_se3->GetLoadSize()),L"se3");
					this->wave_se4 = NBsys::NWave::CreateWave_Ogg(this->file_se4->GetLoadData(),static_cast<s32>(this->file_se4->GetLoadSize()),L"se4");
					this->wave_se5 = NBsys::NWave::CreateWave_Ogg(this->file_se5->GetLoadData(),static_cast<s32>(this->file_se5->GetLoadSize()),L"se5");
					this->wave_se6 = NBsys::NWave::CreateWave_Ogg(this->file_se6->GetLoadData(),static_cast<s32>(this->file_se6->GetLoadSize()),L"se6");
					this->wave_se7 = NBsys::NWave::CreateWave_Ogg(this->file_se7->GetLoadData(),static_cast<s32>(this->file_se7->GetLoadSize()),L"se7");
					this->wave_se8 = NBsys::NWave::CreateWave_Ogg(this->file_se8->GetLoadData(),static_cast<s32>(this->file_se8->GetLoadSize()),L"se8");
					this->wave_se9 = NBsys::NWave::CreateWave_Ogg(this->file_se9->GetLoadData(),static_cast<s32>(this->file_se9->GetLoadSize()),L"se9");

					this->windowmenu_buttonlist->AddButton(L"Discord",std::bind(&App::Discord,this));
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
							t_font->clip_rect.Set(0.0f,50.0f,0.0f,0.0f);
							t_font->clip = false;
							t_font->size = 16.0f;
							t_font->fonttexture_type = NBsys::ND3d11::D3d11_FontTextureType::SFont;
							t_font->color = NBsys::NColor::Color_F(0.0f,1.0f,1.0f,1.0f);
							t_font->alignment = NBsys::NFont::Font_Alignment::Left_Top;
							t_font->string = L"Play Now";

							this->render2d->Draw(t_font);
						}
					}else{
						this->soundbuffer_lastplay_id = -1;
					}
				}

				//this->Play();

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
				t_projection.Set_PerspectiveProjectionMatrix(this->size,this->camera_fov_deg,this->camera_near,this->camera_far);

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
		{
			Size2DType<s32> t_1(1,1);
			Size2DType<s32> t_2(2,2);
			
			t_1 = t_2;
		}

		{
			Size2DType<s32> t_1(1,1);
			Size2DType<s32> t_2(2,2);

			t_1 = +t_2;
		}

		{
			Size2DType<s32> t_1(1,1);
			Size2DType<s32> t_2(2,2);

			t_1 = -t_2;
		}

		{
			Size2DType<s32> t_1(1,1);
			Size2DType<s32> t_2(2,2);

			t_1 += t_2;
			t_1 += 2;
		}

		{
			Size2DType<s32> t_1(1,1);
			Size2DType<s32> t_2(2,2);

			t_1 -= t_2;
			t_1 -= 2;
		}

		{
			Size2DType<s32> t_1(1,1);
			Size2DType<s32> t_2(2,2);

			t_1 *= t_2;
			t_1 *= 2;
		}

		{
			Size2DType<s32> t_1(1,1);
			Size2DType<s32> t_2(2,2);

			t_1 /= t_2;
			t_1 /= 2;
		}

		{
			Size2DType<s32> t_1(1,1);
			Size2DType<s32> t_2(2,2);
			Size2DType<s32> t_3(3,3);

			t_1 = t_2 + t_3;
			t_1 = t_2 + 2;
		}

		{
			Size2DType<s32> t_1(1,1);
			Size2DType<s32> t_2(2,2);
			Size2DType<s32> t_3(3,3);

			t_1 = t_2 - t_3;
			t_1 = t_2 - 2;
		}


		{
			Size2DType<s32> t_1(1,1);
			Size2DType<s32> t_2(2,2);
			Size2DType<s32> t_3(3,3);

			t_1 = t_2 * t_3;
			t_1 = t_2 * 2;
		}

		{
			Size2DType<s32> t_1(1,1);
			Size2DType<s32> t_2(2,2);
			Size2DType<s32> t_3(3,3);

			t_1 = t_2 / t_3;
			t_1 = t_2 / 2;
		}

		sharedptr<App> t_app(new App());
		t_app->Initialize();
		t_app->Main();
		t_app->Finalize();
		return;
	}


}
#endif

