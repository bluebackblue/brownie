

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
		sharedptr<NCommon::WindowMenu_Texture> windowmenu_texture;

		/**
		*/
		struct ModelParts //todo
		{
			STLWString patrs_name;

			s32 texture_index;
			STLWString texture_filepath;
			sharedptr<NBsys::NFile::File_Object> texture_file;
			sharedptr<NBsys::NTexture::Texture> texture;

			s32 texture_id;

			bool cullfull;

			ModelParts()
				:
				texture_index(0),
				texture_id(-1),
				cullfull(true)
			{
			}
		};
		/** バーテックスシェーダ。定数。
		*/
		struct VS_ConstantBuffer_B0
		{
			NBsys::NGeometry::Geometry_Matrix_44 view_projection;

			VS_ConstantBuffer_B0()
				:
				view_projection(NBsys::NGeometry::Geometry_Identity())
			{
			}

			~VS_ConstantBuffer_B0()
			{
			}
		};

		/** ピクセルシェーダ。定数。
		*/
		struct PS_ConstantBuffer_B1
		{
			/**

			00000001 : テクスチャー使用。
			00000010 :
			00000100 :
			00001000 :
			00010000 :
			00100000 :
			01000000 :
			10000000 :

			*/
			u32 flag1;
			u32 flag2;
			u32 flag3;
			u32 flag4;

			PS_ConstantBuffer_B1()
				:
				flag1(0),
				flag2(0),
				flag3(0),
				flag4(0)
			{
			}
		};

		
		/** mmd
		*/
		s32 mmd_step;
		sharedptr<STLVector<ModelParts>::Type> mmd_model;
		sharedptr<NBsys::NMmd::Mmd_Pmx> mmd_pmx;
		sharedptr<NBsys::NMmd::Mmd_Vmd> mmd_vmd;
		sharedptr<NBsys::NVertex::Vertex<NBsys::NVertex::Vertex_Data_Pos3Uv2Color4>> mmd_vertex;
		AsyncResult<bool> mmd_asyncresult_vertexshader;
		AsyncResult<bool> mmd_asyncresult_pixelshader;
		s32 mmd_vertexshader_id;
		s32 mmd_pixelshader_id;
		s32 mmd_vs_constantbuffer_b0_id;
		s32 mmd_ps_constantbuffer_b1_id;
		s32 mmd_vertexbuffer_id;

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
			this->camera_target = NBsys::NGeometry::Geometry_Vector3(0.0f,10.0f,0.0f);
			this->camera_fov_deg = 60.0f;
			this->camera_near = 0.1f;
			this->camera_far = 1000.0f;
			this->camera_time = 0.0f;

			//ターゲット。
			this->target_from.Set(10,10,10);
			this->target_to_a.Set(0,0,10);
			this->target_to_b.Set(3,0,0);

			{
				this->mmd_step = 0;
				//this->mmd_model;
				//this->mmd_pmx;
				//this->mmd_vmd;
				//this->mmd_vertex;
				//this->mmd_asyncresult_vertexshader;
				//this->mmd_asyncresult_pixelshader;
				this->mmd_vertexshader_id = -1;
				this->mmd_pixelshader_id = -1;
				this->mmd_vs_constantbuffer_b0_id = -1;
				this->mmd_ps_constantbuffer_b1_id = -1;
				this->mmd_vertexbuffer_id = -1;
			}
		}

		/** destructor
		*/
		nonvirtual ~App()
		{
		}

	public:

		/** Mmd_CreateShader
		*/
		void Mmd_CreateShader()
		{
			sharedptr<NBsys::NFile::File_Object> t_simple_vertex_fx(new NBsys::NFile::File_Object(1,L"simple_vertex.fx",-1,sharedptr<NBsys::NFile::File_Allocator>(),1));
			sharedptr<NBsys::NFile::File_Object> t_simple_pixel_fx(new NBsys::NFile::File_Object(1,L"simple_pixel.fx",-1,sharedptr<NBsys::NFile::File_Allocator>(),1));

			this->mmd_asyncresult_vertexshader.Create(false);
			this->mmd_asyncresult_pixelshader.Create(false);

			sharedptr<STLVector<NBsys::ND3d11::D3d11_Layout>::Type> t_layout(new STLVector<NBsys::ND3d11::D3d11_Layout>::Type());
			{
				s32 t_offset = 0;

				t_layout->push_back(NBsys::ND3d11::D3d11_Layout("POSITION",		0,NBsys::ND3d11::D3d11_LayoutFormatType::R32G32B32_FLOAT,		0,	t_offset));
				t_offset += sizeof(f32) * 3;

				t_layout->push_back(NBsys::ND3d11::D3d11_Layout("TEXCOORD",		0,NBsys::ND3d11::D3d11_LayoutFormatType::R32G32_FLOAT,			0,	t_offset));
				t_offset += sizeof(f32) * 2;

				t_layout->push_back(NBsys::ND3d11::D3d11_Layout("COLOR",		0,NBsys::ND3d11::D3d11_LayoutFormatType::R32G32B32A32_FLOAT,	0,	t_offset));
				t_offset += sizeof(f32) * 4;
			}

			this->mmd_vertexshader_id = this->d3d11->CreateVertexShader(this->mmd_asyncresult_vertexshader,t_simple_vertex_fx,t_layout);
			this->mmd_pixelshader_id = this->d3d11->CreatePixelShader(this->mmd_asyncresult_pixelshader,t_simple_pixel_fx);
			this->mmd_vs_constantbuffer_b0_id = this->d3d11->CreateConstantBuffer(0,sizeof(VS_ConstantBuffer_B0));
			this->mmd_ps_constantbuffer_b1_id = this->d3d11->CreateConstantBuffer(1,sizeof(PS_ConstantBuffer_B1));
			this->mmd_vertexbuffer_id = this->d3d11->CreateVertexBuffer(this->mmd_vertex->GetVertexPointer(),this->mmd_vertex->GetVertexStrideByte(),0,this->mmd_vertex->GetVertexAllCountOf(),false);
		}

		/** Mmd_Load
		*/
		void Mmd_Load()
		{
			STLWString t_pmx_path = L"mmd/アリスあぴミクver1.0/";
			STLWString t_pmx_name = L"Appearance Miku_Alice.pmx";

			STLWString t_vmd_path = L"mmd/nac_miraikei/";
			STLWString t_vmd_name = L"nac_miraikei.vmd";

			//ＰＭＸ読み込み。
			{
				sharedptr<NBsys::NFile::File_Object> t_fileobject_pmx(new NBsys::NFile::File_Object(2,t_pmx_path + t_pmx_name,-1,sharedptr<NBsys::NFile::File_Allocator>(),1));
				while(t_fileobject_pmx->IsBusy()){
					ThreadSleep(10);
				}
				this->mmd_pmx.reset(new NBsys::NMmd::Mmd_Pmx());
				this->mmd_pmx->Load(t_fileobject_pmx);
			}

			//ＶＭＤ読み込み。
			{
				sharedptr<NBsys::NFile::File_Object> t_fileobject_vmd(new NBsys::NFile::File_Object(2,t_vmd_path + t_vmd_name,-1,sharedptr<NBsys::NFile::File_Allocator>(),1));
				while(t_fileobject_vmd->IsBusy()){
					ThreadSleep(10);
				}
				this->mmd_vmd.reset(new NBsys::NMmd::Mmd_Vmd());
				this->mmd_vmd->Load(t_fileobject_vmd);
			}

			this->mmd_vertex = new NBsys::NVertex::Vertex<NBsys::NVertex::Vertex_Data_Pos3Uv2Color4>();
			this->mmd_model = new STLVector<ModelParts>::Type();

			for(u32 ii=0;ii<this->mmd_pmx->parts_list_size;ii++){
				NBsys::NMmd::Mmd_Pmx_Parts& t_mmd_pmx_parts = this->mmd_pmx->parts_list[ii];
				this->mmd_model->push_back(ModelParts());

				//モデルパーツ。
				ModelParts& t_model_patrs = this->mmd_model->at(ii);

				//パーツ名。
				t_model_patrs.patrs_name = t_mmd_pmx_parts.parts_name_jp;

				//バーテックスにパーツ追加。
				this->mmd_vertex->AddParts("parts");

				//パーツに頂点追加。
				for(u32 jj=0;jj<t_mmd_pmx_parts.count_of_index;jj++){
					u32 t_index = this->mmd_pmx->index_list.get()[t_mmd_pmx_parts.start_index + jj];

					NBsys::NVertex::Vertex_Data_Pos3Uv2Color4 t_vertex;
					NBsys::NMmd::Mmd_Pmx_VertexData& t_data = this->mmd_pmx->vertex_list.get()[t_index];

					f32 t_color_r = t_mmd_pmx_parts.diffuse.r;
					f32 t_color_g = t_mmd_pmx_parts.diffuse.g;
					f32 t_color_b = t_mmd_pmx_parts.diffuse.b;
					f32 t_color_a = t_mmd_pmx_parts.diffuse.a;

					NBsys::NVertex::SetColor<NBsys::NVertex::Vertex_Data_Pos3Uv2Color4>(t_vertex,t_color_r,t_color_g,t_color_b,t_color_a);
					NBsys::NVertex::SetPos<NBsys::NVertex::Vertex_Data_Pos3Uv2Color4>(t_vertex,t_data.position.x,t_data.position.y,t_data.position.z);
					NBsys::NVertex::SetUv<NBsys::NVertex::Vertex_Data_Pos3Uv2Color4>(t_vertex,t_data.uv.x,t_data.uv.y);

					this->mmd_vertex->AddVertex(t_vertex);
				}

				//カリング。
				t_model_patrs.cullfull = t_mmd_pmx_parts.drawmode_cullfull;

				//テクスチャーインデックス。
				t_model_patrs.texture_index = t_mmd_pmx_parts.textureindex;

				//テクスチャー読み込み開始。
				if(t_model_patrs.texture_index >= 0){
					t_model_patrs.texture_filepath = Path::DirAndName(t_pmx_path,this->mmd_pmx->texturename_list[t_model_patrs.texture_index]);
					t_model_patrs.texture_file = new NBsys::NFile::File_Object(2,t_model_patrs.texture_filepath,-1,sharedptr<NBsys::NFile::File_Allocator>(),1);
				}else{
					t_model_patrs.texture_filepath = Path::DirAndName(L"",L"white.bmp");
					t_model_patrs.texture_file = new NBsys::NFile::File_Object(2,t_model_patrs.texture_filepath,-1,sharedptr<NBsys::NFile::File_Allocator>(),1);
				}
			}

			for(u32 ii=0;ii<this->mmd_model->size();ii++){

				//モデルパーツ。
				ModelParts& t_model_patrs = this->mmd_model->at(ii);

				if(t_model_patrs.texture_file != nullptr){

					//テクスチャー読み込み中。
					while(t_model_patrs.texture_file->IsBusy()){
						ThreadSleep(10);
					}

					if((t_model_patrs.texture_file->GetErrorCode() == ErrorCode::Success)&&(t_model_patrs.texture_file->GetLoadSize() > 0)){
						//テクスチャー作成。
						t_model_patrs.texture = NBsys::NTexture::CreateTexture(t_model_patrs.texture_file->GetLoadData(),static_cast<s32>(t_model_patrs.texture_file->GetLoadSize()),t_model_patrs.texture_file->GetFileNameShort());
						if(t_model_patrs.texture){
							t_model_patrs.texture_id = this->d3d11->CreateTexture(t_model_patrs.texture,false);
						}
					}

				}
			}
		}

		
		/** Mmd_Render
		*/
		void Mmd_Render(const NBsys::NGeometry::Geometry_Matrix_44& a_view_projection)
		{
			NBsys::NGeometry::Geometry_Matrix_44 t_view_projection = a_view_projection;

			//シェーダー。
			this->d3d11->Render_VSSetShader(this->mmd_vertexshader_id);
			this->d3d11->Render_PSSetShader(this->mmd_pixelshader_id);
			this->d3d11->Render_SetPrimitiveTopology(NBsys::ND3d11::D3d11_TopologyType::Id::TriangleList);
			this->d3d11->Render_SetBlendState(this->blendstate_on_id);
			this->d3d11->Render_SetSamplerState(0,this->samplerstate_point_id);

			//バーテックスバッファ。
			this->d3d11->Render_SetVertexBuffer(this->mmd_vertexbuffer_id);

			for(s32 ii=0;ii<static_cast<s32>(this->mmd_model->size());ii++){
				VS_ConstantBuffer_B0 t_vs_constantbuffer_b0;
				PS_ConstantBuffer_B1 t_ps_constantbuffer_b1;

				if(this->mmd_model->at(ii).cullfull){
					//両面描画。
					this->d3d11->Render_SetRasterizerState(this->rasterizerstate_cull_none_id);
				}else{
					//後ろ向きを描画しない。
					this->d3d11->Render_SetRasterizerState(this->rasterizerstate_cull_back_id);
				}

				t_vs_constantbuffer_b0.view_projection = t_view_projection.Make_Transpose();

				//テクスチャー設定。
				if(this->mmd_model->at(ii).texture_index >= 0){
					this->d3d11->Render_SetTexture(0,this->mmd_model->at(ii).texture_id);
					t_ps_constantbuffer_b1.flag1 = 1;
				}

				//コンスタントバッファーの内容更新。
				this->d3d11->Render_UpdateSubresource(this->mmd_vs_constantbuffer_b0_id,&t_vs_constantbuffer_b0);
				this->d3d11->Render_UpdateSubresource(this->mmd_ps_constantbuffer_b1_id,&t_ps_constantbuffer_b1);

				//コンスタントバッファーをシェーダーに設定。
				this->d3d11->Render_VSSetConstantBuffers(this->mmd_vs_constantbuffer_b0_id);
				this->d3d11->Render_PSSetConstantBuffers(this->mmd_ps_constantbuffer_b1_id);

				//描画。
				this->d3d11->Render_Draw(this->mmd_vertex->GetVertexCountOf(ii),this->mmd_vertex->GetVertexOffset(ii));
			}
		}


		/** 初期化更新。
		*/
		virtual bool Initialize_Update()
		{
			if(this->mmd_step == 0){
				this->Mmd_Load();
					this->mmd_step++;				
			}else if(this->mmd_step == 1){
				this->Mmd_CreateShader();
				this->mmd_step++;
			}else if(this->mmd_step == 2){
				if(this->mmd_asyncresult_vertexshader.Get() == true){
					if(this->mmd_asyncresult_pixelshader.Get() == true){
						this->mmd_step++;
					}
				}
			}else if(this->mmd_step == 3){
				return true;
			}

			return true;
		}

		/** 更新。
		*/
		virtual void Update(f32 a_delta)
		{
			this->camera_time += a_delta;

			//カメラ回転。
			this->camera_position.x = Math::cos_f(this->camera_time / 10) * 20;
			this->camera_position.z = Math::sin_f(this->camera_time / 10) * 20;

			if(this->step == 0){
				//テクスチャ。
				this->windowmenu_texture.reset(new NCommon::WindowMenu_Texture(150.0f,150.0f,this->d3d11));
				NBsys::NWindowMenu::GetSystemInstance()->Add(this->windowmenu_texture);

				//ログ。
				this->windowmenu_log.reset(new NCommon::WindowMenu_Log(200.0f,200.0f));
				NBsys::NWindowMenu::GetSystemInstance()->Add(this->windowmenu_log);

				this->step++;
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

				this->Mmd_Render(t_view * t_projection);
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
		t_app->Delete();
		return;
	}


}
#endif

