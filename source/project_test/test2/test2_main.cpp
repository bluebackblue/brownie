

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


/** Test0_Main
*/
#if defined(DEF_TEST2)


/** include
*/
#include "./test2_main.h"


/** USE_FOVE
*/
#define USE_FOVE (0)


/** include
*/
//#if(USE_FOVE)
#include "../bsys/d3d11/d3d11_impl.h"
//#endif


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
static s32 s_width = 800*2;


/** s_height
*/
static s32 s_height = 600*2;


/** s_window
*/
static sharedptr< NBsys::NWindow::Window > s_window;


/** s_d3d11
*/
static sharedptr< NBsys::ND3d11::D3d11 > s_d3d11;


/** s_fovehmd
*/
#if(USE_FOVE)
static sharedptr< NBsys::NFovehmd::Fovehmd > s_fovehmd;
#endif


//s_vertex
static sharedptr< NBsys::NVertex::Vertex< NBsys::NVertex::Vertex_Data_Pos3Uv2Color4 > > s_vertex;
static sharedptr< NBsys::NMmdPmx::MmdPmx > s_mmdpmx;


//s_matrix
static NBsys::NGeometry::Geometry_Matrix_44 s_matrix = NBsys::NGeometry::Geometry_Matrix_44::Identity();


//s_pcounter
static u64 s_pcounter = 0ULL;


//s_step
static int s_step = 0;


//s_rotate
static f32 s_rotate = 0.0f;


//asyncresult
AsyncResult< bool > t_asyncresult_vertexshader;
AsyncResult< bool > t_asyncresult_pixelshader;


//id
s32 t_vertexshader_id = -1;
s32 t_pixelshader_id = -1;
s32 t_constantbuffer_id = -1;
s32 t_vertexbuffer_id = -1;

s32 t_blendstate_id = -1;

s32 t_rasterizerstate_cull_back_id = -1;
s32 t_rasterizerstate_cull_none_id = -1;


struct ModelParts
{
	STLWString patrs_name;

	s32 texture_index;
	STLWString texture_filepath;
	sharedptr< NBsys::NFile::File_Object > texture_file;
	sharedptr< NBsys::NTexture::Texture > texture;

	s32 texture_id;

	bool cullfull;
};
sharedptr< STLVector< ModelParts >::Type > s_model;


void LoadPmx()
{
	STLWString t_path = L"アリスあぴミクver1.0/";

	{
		sharedptr< NBsys::NFile::File_Object > t_pmx(new NBsys::NFile::File_Object(1,t_path + L"Appearance Miku_Alice.pmx",-1,sharedptr< NBsys::NFile::File_Allocator >(),1));
		while(t_pmx->IsBusy()){
			ThreadSleep(10);
		}
		s_mmdpmx = NBsys::NMmdPmx::Load(t_pmx);
	}

	s_vertex = new NBsys::NVertex::Vertex< NBsys::NVertex::Vertex_Data_Pos3Uv2Color4 >();
	s_model = new STLVector< ModelParts >::Type();

	for(u32 ii=0;ii<s_mmdpmx->parts_list_size;ii++){
		NBsys::NMmdPmx::MmdPmx_Parts& t_mmdpmx_parts = s_mmdpmx->parts_list[ii];
		s_model->push_back(ModelParts());

		//モデルパーツ。
		ModelParts& t_model_patrs = s_model->at(ii);

		//パーツ名。
		t_model_patrs.patrs_name = t_mmdpmx_parts.parts_name_jp;

		//バーテックスにパーツ追加。
		s_vertex->AddParts("parts");

		//パーツに頂点追加。
		for(u32 jj=0;jj<t_mmdpmx_parts.count_of_index;jj++){
			u32 t_index = s_mmdpmx->index_list.get()[t_mmdpmx_parts.start_index + jj];

			NBsys::NVertex::Vertex_Data_Pos3Uv2Color4 t_vertex;
			NBsys::NMmdPmx::MmdPmx_VertexData& t_data = s_mmdpmx->vertex_list.get()[t_index];

			f32 t_color_r = t_mmdpmx_parts.diffuse.r;
			f32 t_color_g = t_mmdpmx_parts.diffuse.g;
			f32 t_color_b = t_mmdpmx_parts.diffuse.b;
			f32 t_color_a = t_mmdpmx_parts.diffuse.a;

			NBsys::NVertex::SetColor< NBsys::NVertex::Vertex_Data_Pos3Uv2Color4 >(t_vertex,t_color_r,t_color_g,t_color_b,t_color_a);
			NBsys::NVertex::SetPos< NBsys::NVertex::Vertex_Data_Pos3Uv2Color4 >(t_vertex,t_data.position.x,t_data.position.y,t_data.position.z);
			NBsys::NVertex::SetUv< NBsys::NVertex::Vertex_Data_Pos3Uv2Color4 >(t_vertex,t_data.uv.x,t_data.uv.y);

			s_vertex->AddVertex(t_vertex);
		}

		//カリング。
		t_model_patrs.cullfull = t_mmdpmx_parts.drawmode_cullfull;

		//テクスチャーインデックス。
		t_model_patrs.texture_index = t_mmdpmx_parts.textureindex;

		//テクスチャー読み込み開始。
		if(t_model_patrs.texture_index >= 0){
			t_model_patrs.texture_filepath = Path::DirAndName(t_path,s_mmdpmx->texturename_list[t_model_patrs.texture_index]);
			t_model_patrs.texture_file = new NBsys::NFile::File_Object(1,t_model_patrs.texture_filepath,-1,sharedptr< NBsys::NFile::File_Allocator >(),1);
		}else{
			t_model_patrs.texture_filepath = Path::DirAndName(L"",L"white.bmp");
			t_model_patrs.texture_file = new NBsys::NFile::File_Object(1,t_model_patrs.texture_filepath,-1,sharedptr< NBsys::NFile::File_Allocator >(),1);
		}
	}

	for(u32 ii=0;ii<s_model->size();ii++){

		//モデルパーツ。
		ModelParts& t_model_patrs = s_model->at(ii);

		if(t_model_patrs.texture_file != nullptr){

			//テクスチャー読み込み中。
			while(t_model_patrs.texture_file->IsBusy()){
				ThreadSleep(10);
			}

			//テクスチャー作成。
			t_model_patrs.texture = NBsys::NTexture::CreateTexture(t_model_patrs.texture_file->GetLoadData(),static_cast<s32>(t_model_patrs.texture_file->GetLoadSize()),t_model_patrs.texture_file->GetFileNameShort());
			t_model_patrs.texture_id = s_d3d11->CreateTexture(t_model_patrs.texture);

		}
	}




}




/** DrawOnce
*/
void DrawOnce(NBsys::NGeometry::Geometry_Matrix_44& a_model_matrix,NBsys::NGeometry::Geometry_Matrix_44& a_view_projection,s32 a_xx,s32 a_yy,s32 a_zz)
{
	NBsys::NGeometry::Geometry_Matrix_44 t_view_projection = a_model_matrix * NBsys::NGeometry::Geometry_Matrix_44::Make_Translate(a_xx*2.0f,a_yy*2.0f,a_zz*2.0f) * a_view_projection;
	NBsys::NGeometry::Geometry_Matrix_44 t_view_projection_transpose = t_view_projection.Make_Transpose();


	s_d3d11->Render_IASetPrimitiveTopology_TriangleList();
	s_d3d11->Render_UpdateSubresource(t_constantbuffer_id,&t_view_projection_transpose.m[0][0]);
	s_d3d11->Render_VSSetShader(t_vertexshader_id);
	s_d3d11->Render_VSSetConstantBuffers(0,t_constantbuffer_id);
	s_d3d11->Render_PSSetShader(t_pixelshader_id);
	s_d3d11->Render_SetBlendState(t_blendstate_id);

	for(s32 ii=0;ii<s_model->size();ii++){

		if(s_model->at(ii).cullfull){
			//両面描画。
			s_d3d11->Render_SetRasterizerState(t_rasterizerstate_cull_none_id);
		}else{
			//カリングあり。
			s_d3d11->Render_SetRasterizerState(t_rasterizerstate_cull_back_id);
		}

		if(s_model->at(ii).texture_index >= 0){
			s_d3d11->Render_SetTexture(s_model->at(ii).texture_id);
			s_d3d11->Render_Draw(s_vertex->GetVertexCountOf(ii),s_vertex->GetVertexOffset(ii));
		}else{
			s_d3d11->Render_SetTexture(s_model->at(ii).texture_id);
			s_d3d11->Render_Draw(s_vertex->GetVertexCountOf(ii),s_vertex->GetVertexOffset(ii));
		}
	}
}


/** Draw
*/
void Draw(NBsys::NGeometry::Geometry_Matrix_44& a_model_matrix,NBsys::NGeometry::Geometry_Matrix_44& a_view_projection)
{
	for(s32 xx=-10;xx<10;xx++){
		for(s32 zz=-10;zz<10;zz++){
			s32 yy = 0;
			DrawOnce(a_model_matrix,a_view_projection,xx,yy,zz);
		}
	}
}


/** Test_Main
*/
void Test_Main()
{
	TAGLOG("main","DEF_TEST1");

	NBsys::NFile::StartSystem(2);
	NBsys::NFile::SetRoot(0,L"./project_test");
	NBsys::NFile::SetRoot(1,L"../../sdk/mmd");

	#if(USE_FOVE)
	s_fovehmd.reset(new NBsys::NFovehmd::Fovehmd());
	while(1){
		s_fovehmd->ResetErrorCode();
		s_fovehmd->ConnectStart();
		while(s_fovehmd->ConnectUpdate() == false){
			ThreadSleep(16);
		}
		if(s_fovehmd->GetErrorCode().code == ErrorCode::Success){
			break;
		}
		ThreadSleep(16);
	}
	#endif

	s_window.reset(new NBsys::NWindow::Window());
	s_d3d11.reset(new NBsys::ND3d11::D3d11());

	#if(USE_FOVE)
	s_window->Create(L"sample",static_cast<s32>(s_fovehmd->GetSingleEyeResolution().x * 2)/3,static_cast<s32>(s_fovehmd->GetSingleEyeResolution().y)/3);
	s_d3d11->Render_Create(s_window,static_cast<s32>(s_fovehmd->GetSingleEyeResolution().x * 2),static_cast<s32>(s_fovehmd->GetSingleEyeResolution().y));
	#else
	s_window->Create(L"sample",s_width,s_height);
	s_d3d11->Render_Create(s_window,s_width,s_height);
	#endif

	//ブレンドステータス。
	t_blendstate_id = s_d3d11->CreateBlendState(true);

	//ラスタライザー。
	t_rasterizerstate_cull_back_id = s_d3d11->CreateRasterizerState(NBsys::ND3d11::D3d11_CullType::BACK);
	t_rasterizerstate_cull_none_id = s_d3d11->CreateRasterizerState(NBsys::ND3d11::D3d11_CullType::NONE);

	//s_pcounter
	s_pcounter = PerformanceCounter::GetPerformanceCounter();

	LoadPmx();

	while (true)
	{
		//s_window
		s_window->Update();
		if(s_window->IsEnd() == true){
			break;
		}

		#if(USE_FOVE)
		s_fovehmd->Update();
		#endif

		float t_delta = 0.0f;
		{
			u64 t_pcounter_now = PerformanceCounter::GetPerformanceCounter();
			u64 t_pcounter_sec = PerformanceCounter::GetPerformanceSecCounter();
			t_delta = static_cast<float>(t_pcounter_now - s_pcounter) / t_pcounter_sec;
			if(t_delta < (1.0f / 60)){
				continue;
			}
			s_pcounter = t_pcounter_now;
		}

		s_d3d11->Render_Main();

		if(s_step == 0){

			sharedptr< NBsys::NFile::File_Object > t_simple_vertex_fx(	new NBsys::NFile::File_Object(0,L"simple_vertex.fx",	-1,sharedptr< NBsys::NFile::File_Allocator >(),1));
			sharedptr< NBsys::NFile::File_Object > t_simple_pixel_fx(	new NBsys::NFile::File_Object(0,L"simple_pixel.fx",		-1,sharedptr< NBsys::NFile::File_Allocator >(),1));

			t_asyncresult_vertexshader.Create(false);
			t_asyncresult_pixelshader.Create(false);

			sharedptr< STLVector< NBsys::ND3d11::D3d11_Layout >::Type > t_layout(new STLVector< NBsys::ND3d11::D3d11_Layout >::Type());
			{
				t_layout->push_back(NBsys::ND3d11::D3d11_Layout("POSITION",		0,NBsys::ND3d11::D3d11_LayoutFormatType::R32G32B32_FLOAT,		0,	0));			//12
				t_layout->push_back(NBsys::ND3d11::D3d11_Layout("TEXCOORD",		0,NBsys::ND3d11::D3d11_LayoutFormatType::R32G32_FLOAT,			0,	0 + 12));		//8
				t_layout->push_back(NBsys::ND3d11::D3d11_Layout("COLOR",		0,NBsys::ND3d11::D3d11_LayoutFormatType::R32G32B32A32_FLOAT,	0,	0 + 12 + 8));	//16
			}

			t_vertexshader_id = s_d3d11->CreateVertexShader(t_asyncresult_vertexshader,t_simple_vertex_fx,t_layout);
			t_pixelshader_id = s_d3d11->CreatePixelShader(t_asyncresult_pixelshader,t_simple_pixel_fx);
			t_constantbuffer_id = s_d3d11->CreateConstantBuffer(sizeof(float) * 16);
			t_vertexbuffer_id = s_d3d11->CreateVertexBuffer(s_vertex->GetVertexPointer(),s_vertex->GetVertexStrideByte(),0,s_vertex->GetVertexAllCountOf());

			s_step++;

		}else if(s_step == 1){

			if(t_asyncresult_vertexshader.Get() == true){
				if(t_asyncresult_pixelshader.Get() == true){
					s_step++;
				}
			}

		}else if(s_step == 2){

			s_step++;

		}else{

			#if(USE_FOVE)
			#else
			s_rotate += 0.002f;
			if(s_rotate >= 3.14f * 2){
				s_rotate -= 3.14f * 2;
			}
			s_matrix = NBsys::NGeometry::Geometry_Matrix_44::Make_RotationY(s_rotate);
			#endif

			//レイアウト。
			s_d3d11->Render_IASetInputLayout(t_vertexshader_id);
			s_d3d11->Render_IASetVertexBuffers(t_vertexbuffer_id);

			s_d3d11->Render_ClearRenderTargetView(NBsys::NColor::Color_F(0.3f,0.3f,0.8f,1.0f));
			s_d3d11->Render_ClearDepthStencilView();
			{
				//t_near
				f32 t_near = 0.1f;

				//t_far
				f32 t_far = 1000.0f;

				//t_camera_pos
				NBsys::NGeometry::Geometry_Vector3 t_camera_pos(0,2,-20);

				#if(0)
				{
					#if(USE_FOVE)
					{
						s_d3d11->Render_ViewPort(0.0f,0.0f,s_fovehmd->GetSingleEyeResolution().x,s_fovehmd->GetSingleEyeResolution().y);

						NBsys::NGeometry::Geometry_Matrix_44 t_view_projection = s_fovehmd->GetLeftViewProjection(t_near,t_far,t_camera_pos);

						DrawOnce(s_matrix,t_view_projection,0,0,0);
					}

					{
						s_d3d11->Render_ViewPort(s_fovehmd->GetSingleEyeResolution().x,0.0f,s_fovehmd->GetSingleEyeResolution().x,s_fovehmd->GetSingleEyeResolution().y);

						NBsys::NGeometry::Geometry_Matrix_44 t_view_projection = s_fovehmd->GetRightViewProjection(t_near,t_far,t_camera_pos);

						DrawOnce(s_matrix,t_view_projection,0,0,0);
					}
					#endif
				}
				#else
				{
					#if(USE_FOVE)
					s_d3d11->Render_ViewPort(0.0f,0.0f,s_fovehmd->GetSingleEyeResolution().x * 2,s_fovehmd->GetSingleEyeResolution().y);
					#else
					s_d3d11->Render_ViewPort(0.0f,0.0f,static_cast<f32>(s_width),static_cast<f32>(s_height));
					#endif

					//t_camera_target
					NBsys::NGeometry::Geometry_Vector3 t_camera_target(0.0f,10.0f,0.0f);

					//t_camera_position
					NBsys::NGeometry::Geometry_Vector3 t_camera_position(0.0f,10.0f,-20);

					//t_camera_up
					NBsys::NGeometry::Geometry_Vector3 t_camera_up(0.0f,1.0f,0.0f);

					//t_fov_deg
					f32 t_fov_deg = 60.0f;

					NBsys::NGeometry::Geometry_Matrix_44 t_projection;
					#if(USE_FOVE)
					t_projection.Set_PerspectiveProjectionMatrix(s_fovehmd->GetSingleEyeResolution().x * 2,s_fovehmd->GetSingleEyeResolution().y,t_fov_deg,t_near,t_far);
					#else
					t_projection.Set_PerspectiveProjectionMatrix(static_cast<f32>(s_width),static_cast<f32>(s_height),t_fov_deg,t_near,t_far);
					#endif

					NBsys::NGeometry::Geometry_Matrix_44 t_view;
					t_view.Set_ViewMatrix(t_camera_target,t_camera_position,t_camera_up);

					{
						#if(USE_FOVE)
						NBsys::NGeometry::Geometry_Vector3 t_fovehmd_position = s_fovehmd->GetCameraPosition();
						NBsys::NGeometry::Geometry_Quaternion t_fovehmd_quaternion = s_fovehmd->GetCameraQuaternion();
						NBsys::NGeometry::Geometry_Matrix_44 t_fovehmd_matrix(t_fovehmd_quaternion);
						#endif

						{
							#if(USE_FOVE)
							NBsys::NGeometry::Geometry_Matrix_44 t_matrix = t_fovehmd_matrix;
							t_matrix *= NBsys::NGeometry::Geometry_Matrix_44::Make_Translate(t_fovehmd_position.x,t_fovehmd_position.y,t_fovehmd_position.z);
							t_matrix *= s_fovehmd->GetLeftEyeTranslate();
							#else
							NBsys::NGeometry::Geometry_Matrix_44 t_matrix = NBsys::NGeometry::Geometry_Matrix_44::Identity();
							#endif

							t_matrix *= s_matrix;

							DrawOnce(t_matrix,t_view*t_projection,0,0,0);
						}

						#if(USE_FOVE)
						{
							#if(USE_FOVE)
							NBsys::NGeometry::Geometry_Matrix_44 t_matrix = t_fovehmd_matrix;
							t_matrix *= NBsys::NGeometry::Geometry_Matrix_44::Make_Translate(t_fovehmd_position.x,t_fovehmd_position.y,t_fovehmd_position.z);
							t_matrix *= s_fovehmd->GetRightEyeTranslate();
							#else
							NBsys::NGeometry::Geometry_Matrix_44 t_matrix = NBsys::NGeometry::Geometry_Matrix_44::Identity();
							#endif

							t_matrix *= s_matrix;

							DrawOnce(t_matrix,t_view*t_projection,0,0,0);
						}
						#endif
					}
				}
				#endif
			}

			#if(USE_FOVE)
			{
				s_fovehmd->SetTexture(s_d3d11->GetImpl()->GetBackBuffer().get());
			}
			#endif

			if(s_d3d11->Render_Present() == false){
				break;
			}
		}
	}

	s_d3d11->Render_Delete();
	s_d3d11.reset();

	s_window->Delete();
	s_window.reset();

	NBsys::NFile::EndSystemRequest();
	NBsys::NFile::EndWaitSystem();

	return;
}

#endif

