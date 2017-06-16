

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
#if defined(DEF_TEST1)


/** include
*/
#include "./test1_main.h"


/** USE_FOVE
*/
#define USE_FOVE (1)


/** include
*/
#if(USE_FOVE)
#include "../bsys/d3d11/d3d11_impl.h"
#endif


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
static sharedptr< NBsys::NVertex::Model_Vertex< NBsys::NModel::Model_Vertex_Data_Pos3Color4 > > s_vertex;


//s_matrix
static NBsys::NGeometry::Geometry_Matrix_44 s_matrix = NBsys::NGeometry::Geometry_Matrix_44::Identity();


//s_pcounter
static u64 s_pcounter = 0ULL;


//s_step
static int s_step = 0;


//asyncresult
AsyncResult< bool > t_asyncresult_vertexshader;
AsyncResult< bool > t_asyncresult_pixelshader;
AsyncResult< bool > t_asyncresult_constantbuffer;
AsyncResult< bool > t_asyncresult_vertexbuffer;


//id
s32 t_vertexshader_id = -1;
s32 t_pixelshader_id = -1;
s32 t_constantbuffer_id = -1;
s32 t_vertexbuffer_id = -1;


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
	s_d3d11->Render_Draw(s_vertex->GetVertexCountOf(0),s_vertex->GetVertexOffset(0));
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

	NBsys::NFile::StartSystem(1);
	NBsys::NFile::SetRoot(0,L"./project_test");

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
	s_window->Create(L"sample",800,600);
	s_d3d11->Render_Create(s_window,800,600);
	#endif

	//s_vertex
	s_vertex = NBsys::NVertex::Preset_Box< NBsys::NModel::Model_Vertex_Data_Pos3Color4 >();

	//s_pcounter
	s_pcounter = PerformanceCounter::GetPerformanceCounter();

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
			t_asyncresult_constantbuffer.Create(false);
			t_asyncresult_vertexbuffer.Create(false);

			sharedptr< STLVector< NBsys::ND3d11::D3d11_Layout >::Type > t_layout(new STLVector< NBsys::ND3d11::D3d11_Layout >::Type());
			{
				t_layout->push_back(NBsys::ND3d11::D3d11_Layout("POSITION",	0,NBsys::ND3d11::D3d11_FormatType::R32G32B32_FLOAT,		0,	0));
				t_layout->push_back(NBsys::ND3d11::D3d11_Layout("COLOR",	0,NBsys::ND3d11::D3d11_FormatType::R32G32B32A32_FLOAT,	0,	12));
			}

			t_vertexshader_id = s_d3d11->CreateVertexShader(t_asyncresult_vertexshader,t_simple_vertex_fx,t_layout);
			t_pixelshader_id = s_d3d11->CreatePixelShader(t_asyncresult_pixelshader,t_simple_pixel_fx);
			t_constantbuffer_id = s_d3d11->CreateConstantBuffer(t_asyncresult_constantbuffer,sizeof(float) * 16);
			t_vertexbuffer_id = s_d3d11->CreateVertexBuffer(t_asyncresult_vertexbuffer,s_vertex->GetVertexPointer(),s_vertex->GetVertexStrideByte(),0,s_vertex->GetVertexAllCountOf());

			s_step++;

		}else if(s_step == 1){

			if(t_asyncresult_vertexshader.Get() == true){
				if(t_asyncresult_pixelshader.Get() == true){
					if(t_asyncresult_constantbuffer.Get() == true){
						if(t_asyncresult_vertexbuffer.Get() == true){
							s_step++;
						}
					}
				}
			}

		}else if(s_step == 2){

			s_step++;

		}else{

			//レイアウト。
			s_d3d11->Render_SetVertexBuffer(t_vertexbuffer_id);

			s_d3d11->Render_ClearRenderTargetView(NBsys::NColor::Color_F(0.3f,0.3f,0.8f,1.0f));
			s_d3d11->Render_ClearDepthStencilView();
			{
				#if(0)
				{
					{
						s_d3d11->Render_ViewPort(0.0f,0.0f,s_fovehmd->GetSingleEyeResolution().x,s_fovehmd->GetSingleEyeResolution().y);

						NBsys::NGeometry::Geometry_Matrix_44 t_view_projection = s_fovehmd->GetLeftViewProjection(s_near,s_far,2.0f);

						Draw(s_matrix,t_view_projection);
					}

					{
						s_d3d11->Render_ViewPort(s_fovehmd->GetSingleEyeResolution().x,0.0f,s_fovehmd->GetSingleEyeResolution().x,s_fovehmd->GetSingleEyeResolution().y);

						NBsys::NGeometry::Geometry_Matrix_44 t_view_projection = s_fovehmd->GetRightViewProjection(s_near,s_far,2.0f);

						Draw(s_matrix,t_view_projection);
					}
				}
				#else
				{
					#if(USE_FOVE)
					s_d3d11->Render_ViewPort(0.0f,0.0f,s_fovehmd->GetSingleEyeResolution().x * 2,s_fovehmd->GetSingleEyeResolution().y);
					#else
					s_d3d11->Render_ViewPort(0.0f,0.0f,800,600);
					#endif

					//t_camera_target
					NBsys::NGeometry::Geometry_Vector3 t_camera_target(0.0f,0.0f,0.0f);

					//t_camera_position
					NBsys::NGeometry::Geometry_Vector3 t_camera_position(1.0f,1.0f,-5.0f);

					//t_camera_up
					NBsys::NGeometry::Geometry_Vector3 t_camera_up(0.0f,1.0f,0.0f);

					//s_near
					f32 t_near = 0.1f;

					//s_far
					f32 t_far = 1000.0f;

					//s_fov_deg
					f32 t_fov_deg = 60.0f;

					NBsys::NGeometry::Geometry_Matrix_44 t_projection;
					#if(USE_FOVE)
					t_projection.Set_PerspectiveProjectionMatrix(s_fovehmd->GetSingleEyeResolution().x * 2,s_fovehmd->GetSingleEyeResolution().y,t_fov_deg,t_near,t_far);
					#else
					t_projection.Set_PerspectiveProjectionMatrix(800,600,t_fov_deg,t_near,t_far);
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

