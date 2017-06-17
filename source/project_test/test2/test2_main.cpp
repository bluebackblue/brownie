

/**
 * Copyright (c) 2016 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief �C���N���[�h�B
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


/** include
*/
#include "../common/d3d11_drawline.h"


/** USE_FOVE
*/
#define USE_FOVE (0)


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
static sharedptr< NBsys::NMmd::Mmd_Pmx > s_mmd_pmx;


//s_matrix
static NBsys::NGeometry::Geometry_Matrix_44 s_matrix = NBsys::NGeometry::Geometry_Matrix_44::Identity();


//s_pcounter
static u64 s_pcounter = 0ULL;


//s_step
static int s_step = 0;


//s_rotate
static f32 s_rotate = 0.0f;
static f32 s_rotate2 = 0.0f;


//asyncresult
AsyncResult< bool > t_asyncresult_vertexshader;
AsyncResult< bool > t_asyncresult_pixelshader;


//id
s32 t_vertexshader_id = -1;
s32 t_pixelshader_id = -1;
s32 t_vs_constantbuffer_b0_id = -1;
s32 t_ps_constantbuffer_b1_id = -1;
s32 t_vertexbuffer_id = -1;

s32 t_blendstate_id = -1;

s32 t_rasterizerstate_cull_back_id = -1;
s32 t_rasterizerstate_cull_none_id = -1;


/** �o�[�e�b�N�X�V�F�[�_�B�萔�B
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

/** �s�N�Z���V�F�[�_�B�萔�B
*/
struct PS_ConstantBuffer_B1
{
	/**

	00000001 : �e�N�X�`���[�g�p�B
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

sharedptr< common::D3d11_DrawLine_Manager > s_drawline_manager;


void LoadPmx()
{
	STLWString t_path = L"�A���X���҃~�Nver1.0/";
	STLWString t_path_pmx = L"Appearance Miku_Alice.pmx";

	//�o�l�w�ǂݍ��݁B
	{
		sharedptr< NBsys::NFile::File_Object > t_fileobject_pmx(new NBsys::NFile::File_Object(1,t_path + t_path_pmx,-1,sharedptr< NBsys::NFile::File_Allocator >(),1));
		while(t_fileobject_pmx->IsBusy()){
			ThreadSleep(10);
		}
		s_mmd_pmx.reset(new NBsys::NMmd::Mmd_Pmx());
		s_mmd_pmx->Load(t_fileobject_pmx);
	}

	s_vertex = new NBsys::NVertex::Vertex< NBsys::NVertex::Vertex_Data_Pos3Uv2Color4 >();
	s_model = new STLVector< ModelParts >::Type();

	for(u32 ii=0;ii<s_mmd_pmx->parts_list_size;ii++){
		NBsys::NMmd::Mmd_Pmx_Parts& t_mmd_pmx_parts = s_mmd_pmx->parts_list[ii];
		s_model->push_back(ModelParts());

		//���f���p�[�c�B
		ModelParts& t_model_patrs = s_model->at(ii);

		//�p�[�c���B
		t_model_patrs.patrs_name = t_mmd_pmx_parts.parts_name_jp;

		//�o�[�e�b�N�X�Ƀp�[�c�ǉ��B
		s_vertex->AddParts("parts");

		//�p�[�c�ɒ��_�ǉ��B
		for(u32 jj=0;jj<t_mmd_pmx_parts.count_of_index;jj++){
			u32 t_index = s_mmd_pmx->index_list.get()[t_mmd_pmx_parts.start_index + jj];

			NBsys::NVertex::Vertex_Data_Pos3Uv2Color4 t_vertex;
			NBsys::NMmd::Mmd_Pmx_VertexData& t_data = s_mmd_pmx->vertex_list.get()[t_index];

			f32 t_color_r = t_mmd_pmx_parts.diffuse.r;
			f32 t_color_g = t_mmd_pmx_parts.diffuse.g;
			f32 t_color_b = t_mmd_pmx_parts.diffuse.b;
			f32 t_color_a = t_mmd_pmx_parts.diffuse.a * 0.3f;

			NBsys::NVertex::SetColor< NBsys::NVertex::Vertex_Data_Pos3Uv2Color4 >(t_vertex,t_color_r,t_color_g,t_color_b,t_color_a);
			NBsys::NVertex::SetPos< NBsys::NVertex::Vertex_Data_Pos3Uv2Color4 >(t_vertex,t_data.position.x,t_data.position.y,t_data.position.z);
			NBsys::NVertex::SetUv< NBsys::NVertex::Vertex_Data_Pos3Uv2Color4 >(t_vertex,t_data.uv.x,t_data.uv.y);

			s_vertex->AddVertex(t_vertex);
		}

		//�J�����O�B
		t_model_patrs.cullfull = t_mmd_pmx_parts.drawmode_cullfull;

		//�e�N�X�`���[�C���f�b�N�X�B
		t_model_patrs.texture_index = t_mmd_pmx_parts.textureindex;

		//�e�N�X�`���[�ǂݍ��݊J�n�B
		if(t_model_patrs.texture_index >= 0){
			t_model_patrs.texture_filepath = Path::DirAndName(t_path,s_mmd_pmx->texturename_list[t_model_patrs.texture_index]);
			t_model_patrs.texture_file = new NBsys::NFile::File_Object(1,t_model_patrs.texture_filepath,-1,sharedptr< NBsys::NFile::File_Allocator >(),1);
		}else{
			t_model_patrs.texture_filepath = Path::DirAndName(L"",L"white.bmp");
			t_model_patrs.texture_file = new NBsys::NFile::File_Object(1,t_model_patrs.texture_filepath,-1,sharedptr< NBsys::NFile::File_Allocator >(),1);
		}
	}

	for(u32 ii=0;ii<s_model->size();ii++){

		//���f���p�[�c�B
		ModelParts& t_model_patrs = s_model->at(ii);

		if(t_model_patrs.texture_file != nullptr){

			//�e�N�X�`���[�ǂݍ��ݒ��B
			while(t_model_patrs.texture_file->IsBusy()){
				ThreadSleep(10);
			}

			//�e�N�X�`���[�쐬�B
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

	//�V�F�[�_�[�B
	s_d3d11->Render_VSSetShader(t_vertexshader_id);
	s_d3d11->Render_PSSetShader(t_pixelshader_id);
	s_d3d11->Render_SetPrimitiveTopology(NBsys::ND3d11::D3d11_TopologyType::Id::TriangleList);
	s_d3d11->Render_SetBlendState(t_blendstate_id);

	//�o�[�e�b�N�X�o�b�t�@�B
	s_d3d11->Render_SetVertexBuffer(t_vertexbuffer_id);

	for(s32 ii=0;ii<static_cast<s32>(s_model->size());ii++){
		VS_ConstantBuffer_B0 t_vs_constantbuffer_b0;
		PS_ConstantBuffer_B1 t_ps_constantbuffer_b1;

		if(s_model->at(ii).cullfull){
			//���ʕ`��B
			s_d3d11->Render_SetRasterizerState(t_rasterizerstate_cull_none_id);
		}else{
			//��������`�悵�Ȃ��B
			s_d3d11->Render_SetRasterizerState(t_rasterizerstate_cull_back_id);
		}

		//�e�N�X�`���[�ݒ�B
		if(s_model->at(ii).texture_index >= 0){
			s_d3d11->Render_SetTexture(0,s_model->at(ii).texture_id);
			t_ps_constantbuffer_b1.flag1 = 1;
		}

		t_vs_constantbuffer_b0.view_projection = t_view_projection.Make_Transpose();

		//�R���X�^���g�o�b�t�@�[�̓��e�X�V�B
		s_d3d11->Render_UpdateSubresource(t_vs_constantbuffer_b0_id,&t_vs_constantbuffer_b0);
		s_d3d11->Render_UpdateSubresource(t_ps_constantbuffer_b1_id,&t_ps_constantbuffer_b1);

		//�R���X�^���g�o�b�t�@�[���V�F�[�_�[�ɐݒ�B
		s_d3d11->Render_VSSetConstantBuffers(t_vs_constantbuffer_b0_id);
		s_d3d11->Render_PSSetConstantBuffers(t_ps_constantbuffer_b1_id);

		//�`��B
		s_d3d11->Render_Draw(s_vertex->GetVertexCountOf(ii),s_vertex->GetVertexOffset(ii));
	}
}


/** Test_Main
*/
void Test_Main()
{
	TAGLOG("main","DEF_TEST2");

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

	//�u�����h�X�e�[�^�X�B
	t_blendstate_id = s_d3d11->CreateBlendState(true);

	//���X�^���C�U�[�B
	t_rasterizerstate_cull_back_id = s_d3d11->CreateRasterizerState(NBsys::ND3d11::D3d11_CullType::BACK);
	t_rasterizerstate_cull_none_id = s_d3d11->CreateRasterizerState(NBsys::ND3d11::D3d11_CullType::NONE);

	//s_pcounter
	s_pcounter = PerformanceCounter::GetPerformanceCounter();

	LoadPmx();

	s_drawline_manager.reset(new common::D3d11_DrawLine_Manager(s_d3d11));

	while (true)
	{
		//s_window
		s_window->Update();
		if(s_window->IsEnd() == true){
			break;
		}

		//s_fovehmd
		#if(USE_FOVE)
		s_fovehmd->Update();
		#endif

		//performance counter
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

		//Render_Main
		s_d3d11->Render_Main();

		if(s_step == 0){

			//�쐬�B

			sharedptr< NBsys::NFile::File_Object > t_simple_vertex_fx(	new NBsys::NFile::File_Object(0,L"simple_vertex.fx",	-1,sharedptr< NBsys::NFile::File_Allocator >(),1));
			sharedptr< NBsys::NFile::File_Object > t_simple_pixel_fx(	new NBsys::NFile::File_Object(0,L"simple_pixel.fx",		-1,sharedptr< NBsys::NFile::File_Allocator >(),1));

			t_asyncresult_vertexshader.Create(false);
			t_asyncresult_pixelshader.Create(false);

			sharedptr< STLVector< NBsys::ND3d11::D3d11_Layout >::Type > t_layout(new STLVector< NBsys::ND3d11::D3d11_Layout >::Type());
			{
				s32 t_offset = 0;

				t_layout->push_back(NBsys::ND3d11::D3d11_Layout("POSITION",		0,NBsys::ND3d11::D3d11_LayoutFormatType::R32G32B32_FLOAT,		0,	t_offset));
				t_offset += sizeof(f32) * 3;

				t_layout->push_back(NBsys::ND3d11::D3d11_Layout("TEXCOORD",		0,NBsys::ND3d11::D3d11_LayoutFormatType::R32G32_FLOAT,			0,	t_offset));
				t_offset += sizeof(f32) * 2;

				t_layout->push_back(NBsys::ND3d11::D3d11_Layout("COLOR",		0,NBsys::ND3d11::D3d11_LayoutFormatType::R32G32B32A32_FLOAT,	0,	t_offset));
				t_offset += sizeof(f32) * 4;
			}

			t_vertexshader_id = s_d3d11->CreateVertexShader(t_asyncresult_vertexshader,t_simple_vertex_fx,t_layout);
			t_pixelshader_id = s_d3d11->CreatePixelShader(t_asyncresult_pixelshader,t_simple_pixel_fx);
			t_vs_constantbuffer_b0_id = s_d3d11->CreateConstantBuffer(0,sizeof(VS_ConstantBuffer_B0));
			t_ps_constantbuffer_b1_id = s_d3d11->CreateConstantBuffer(1,sizeof(PS_ConstantBuffer_B1));
			t_vertexbuffer_id = s_d3d11->CreateVertexBuffer(s_vertex->GetVertexPointer(),s_vertex->GetVertexStrideByte(),0,s_vertex->GetVertexAllCountOf(),false);

			s_step++;

		}else if(s_step == 1){

			//�쐬�҂��B

			if(t_asyncresult_vertexshader.Get() == true){
				if(t_asyncresult_pixelshader.Get() == true){

					s_drawline_manager->PreUpdate();
					if(s_drawline_manager->IsBusy() == false){
						s_step++;
					}

				}
			}

		}else if(s_step == 2){

			s_step++;

		}else{

			//�`��B

			//�N���A�B
			s_d3d11->Render_ClearRenderTargetView(NBsys::NColor::Color_F(0.3f,0.3f,0.8f,1.0f));
			s_d3d11->Render_ClearDepthStencilView();

			s32 t_left_right_index_max = 1;
			#if(USE_FOVE)
			{
				t_left_right_index_max = 2;
			}
			#endif

			for(s32 t_left_right_index=0;t_left_right_index<t_left_right_index_max;t_left_right_index++){

				//���C���`��J�n�B
				s_drawline_manager->PreUpdate();

				//�r���[�v���W�F�N�V�����B
				NBsys::NGeometry::Geometry_Matrix_44 t_view_projection;
				#if(USE_FOVE)
				{
					//t_near
					f32 t_near = 0.1f;

					//t_far
					f32 t_far = 1000.0f;

					//t_camera_position
					NBsys::NGeometry::Geometry_Vector3 t_camera_position(0,2,-20);

					#if(USE_FOVE)
					if(t_left_right_index == 0){
						s_d3d11->Render_ViewPort(0.0f,0.0f,s_fovehmd->GetSingleEyeResolution().x,s_fovehmd->GetSingleEyeResolution().y);
						t_view_projection = s_fovehmd->GetLeftViewProjection(t_near,t_far,t_camera_position);
					}else{
						s_d3d11->Render_ViewPort(s_fovehmd->GetSingleEyeResolution().x,0.0f,s_fovehmd->GetSingleEyeResolution().x,s_fovehmd->GetSingleEyeResolution().y);
						t_view_projection = s_fovehmd->GetRightViewProjection(t_near,t_far,t_camera_position);
					}
					#endif
				}
				#else
				{
					s_d3d11->Render_ViewPort(0.0f,0.0f,static_cast<f32>(s_width),static_cast<f32>(s_height));

					//t_camera_target
					NBsys::NGeometry::Geometry_Vector3 t_camera_target(0.0f,10.0f,0.0f);

					//t_camera_up
					NBsys::NGeometry::Geometry_Vector3 t_camera_up(0.0f,1.0f,0.0f);

					//t_fov_deg
					f32 t_fov_deg = 60.0f;

					//t_near
					f32 t_near = 0.1f;

					//t_far
					f32 t_far = 1000.0f;

					//t_camera_position
					NBsys::NGeometry::Geometry_Vector3 t_camera_position(0.0f,10.0f,-20);

					NBsys::NGeometry::Geometry_Matrix_44 t_projection;
					#if(USE_FOVE)
					t_projection.Set_PerspectiveProjectionMatrix(s_fovehmd->GetSingleEyeResolution().x * 2,s_fovehmd->GetSingleEyeResolution().y,t_fov_deg,t_near,t_far);
					#else
					t_projection.Set_PerspectiveProjectionMatrix(static_cast<f32>(s_width),static_cast<f32>(s_height),t_fov_deg,t_near,t_far);
					#endif

					NBsys::NGeometry::Geometry_Matrix_44 t_view;
					t_view.Set_ViewMatrix(t_camera_target,t_camera_position,t_camera_up);

					t_view_projection = t_view * t_projection;
				}
				#endif

				{
					#if(USE_FOVE)
					#else
					s_rotate += 0.002f;
					if(s_rotate >= 3.14f * 2){
						s_rotate -= 3.14f * 2;
					}
					s_matrix = NBsys::NGeometry::Geometry_Matrix_44::Make_RotationY(s_rotate);
					#endif

					NBsys::NGeometry::Geometry_Matrix_44 t_matrix = NBsys::NGeometry::Geometry_Matrix_44::Identity();
					t_matrix *= s_matrix;

					DrawOnce(t_matrix,t_view_projection,0,0,0);
				}

				{
					for(s32 ii=0;ii<static_cast<s32>(s_mmd_pmx->bone_list.size());ii++){
						NBsys::NMmd::Mmd_Pmx_Bone& t_bone = s_mmd_pmx->bone_list[ii];
						
						NBsys::NGeometry::Geometry_Matrix_44 t_matrix = NBsys::NGeometry::Geometry_Matrix_44::Identity();
						t_matrix *= s_matrix;

						NBsys::NGeometry::Geometry_Vector3 t_start = t_bone.bone_position;
						NBsys::NGeometry::Geometry_Vector3 t_end = t_bone.bone_position + NBsys::NGeometry::Geometry_Vector3(0.0f,0.0f,1.0f);

						t_start = (NBsys::NGeometry::Geometry_Matrix_44::Make_Translate(t_start.x,t_start.y,t_start.z) * t_matrix).Make_Translate_Vector();
						t_end = (NBsys::NGeometry::Geometry_Matrix_44::Make_Translate(t_end.x,t_end.y,t_end.z) * t_matrix).Make_Translate_Vector();

						s_drawline_manager->DrawLine(t_start,t_end,NBsys::NColor::Color_F(1.0f,1.0f,1.0f,1.0f));

					}
				}

				/*
				{
					s_rotate2 += 0.2f;
					if(s_rotate2 >= 3.14f * 2){
						s_rotate2 -= 3.14f * 2;
					}
					f32 t_x = Math::sinf(s_rotate2);
					s_drawline_manager->DrawLine(NBsys::NGeometry::Geometry_Vector3(0.0f,0.0f,0.0f),NBsys::NGeometry::Geometry_Vector3(t_x,5.0f,0.0f),NBsys::NColor::Color_F(1.0f,1.0f,1.0f,1.0f));
				}
				*/

				//���C���`��B
				s_drawline_manager->Update(t_view_projection);
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

