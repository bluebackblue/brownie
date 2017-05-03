

/**
 * Copyright (c) 2016 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief �G���g���[�B
*/


/** include
*/
#include "./include.h"


/** include
*/
#if defined(PLATFORM_VCWIN)

	#include "../blib/include_windows.h"

#endif


/** Test
*/
void Test();


/** Main
*/
void main(int a_argc,char** a_argv)
{
	NBlib::BootInitialize();

	Test();
}


/** WinMain
*/
#if defined(PLATFORM_VCWIN)
int WINAPI WinMain(_In_ HINSTANCE a_hinstance,_In_opt_ HINSTANCE a_prev_hinstance,_In_ LPSTR a_commandline,_In_ int a_cmdshow)
{
	main(__argc,__argv);
}
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


/** FileAllocator
*/
class FileAllocator : public NBsys::NFile::File_Allocator
{
public:
	virtual void* Alloc(u32 a_size)
	{
		return new u8[a_size];
	}
	virtual void Free(void* a_pointer)
	{
		u8* t_pointer = reinterpret_cast<u8*>(a_pointer);
		delete [] t_pointer;
	}
};


//opengl
sharedptr< NBsys::NOpengl::Opengl >& OpenGL()
{
	static sharedptr< NBsys::NOpengl::Opengl > s_opengl;
	return s_opengl;
}


//s_step
static s32 s_step = 0;


//s_vertex
static sharedptr< NBsys::NModel::Model_Vertex< NBsys::NModel::Model_Vertex_Data_PosColor > > s_vertex;


//s_vertexbuffer_id
static s32 s_vertexbuffer_id = -1;


//s_shader_id
static s32 s_shader_id = 0;


//s_file_allocator
sharedptr< NBsys::NFile::File_Allocator > s_file_allocator;


//s_device_max
static s32 s_device_max = 1;


//s_device_index
static s32 s_device_index = 0;


//s_asyncresult
static AsyncResult< bool > s_asyncresult;


/** opengl_draw
*/
void opengl_draw()
{
	if(s_step < 100){
		//�N���A�J���[�ݒ�B
		OpenGL()->Render_SetClearColor(NBsys::NColor::Color_F(0.0f,0.0f,0.0f,1.0f));

		//�N���A�B�f�v�X�B�J���[�B
		OpenGL()->Render_ClearBuffer(true,true);
	}else{
	
		{
			//�r���[�|�[�g�B
			//this->viewport.Set_ViewPortMatrix(BSYS_OPENGL_SCREEN_W,BSYS_OPENGL_SCREEN_H);

			//�v���W�F�N�V�����B
			//this->projection.Set_PerspectiveProjectionMatrix(BSYS_OPENGL_SCREEN_W,BSYS_OPENGL_SCREEN_H,this->screen_fov_deg,this->screen_near,this->screen_far);

			//�r���[�B
			//this->view.Set_ViewMatrix(this->camera_target,this->camera_position,this->camera_up);
		}

		{
			//�r���[�|�[�g�B
			//OpenGL()->Render_ViewPort(0,0,BSYS_OPENGL_SCREEN_W,BSYS_OPENGL_SCREEN_H);

			//�v���W�F�N�V�����B
			//OpenGL()->Render_SetProjectionMatrix(this->projection);

			//�r���[�B
			//OpenGL()->Render_SetViewMatrix(this->view);

			//�J���[�}�X�N�B
			//OpenGL()->Render_SetColorMask(true,true,true,true);

			//�N���A�J���[�ݒ�B
			OpenGL()->Render_SetClearColor(NBsys::NColor::Color_F(0.3f,0.3f,0.3f,1.0f));

			//�N���A�B�f�v�X�B�J���[�B
			OpenGL()->Render_ClearBuffer(true,true);

			//�f�v�X�e�X�g�B
			//OpenGL()->Render_SetDepthTest(true);

			//���[���h���C���`��B
			OpenGL()->Render_DrawWorldLine();
		}

		{
			OpenGL()->Render_SetShader(s_shader_id);
			{
				//�o�[�e�b�N�X�o�b�t�@�ݒ�B
				OpenGL()->Render_SetVertexBuffer(s_vertexbuffer_id);

				//�r���[�B�v���W�F�N�V�����B
				//Matrix t_view_projection = a_matrix * this->view * this->projection;
				//OpenGL()->Render_SetUniformParameter(a_shaderid,"a_view_projection",&t_view_projection,1);

				//���_���B
				{
					s32 t_stride_byte = s_vertex->GetVertexStrideByte();

					//a_position
					{
						s32 t_offset_byte = NBsys::NModel::GetPosOffset< NBsys::NModel::Model_Vertex_Data_PosColor >();
						OpenGL()->Render_SetAttributeParameter(s_shader_id,"a_position",t_stride_byte,t_offset_byte);
					}

					//a_color
					{
						s32 t_offset_byte = NBsys::NModel::GetColorOffset< NBsys::NModel::Model_Vertex_Data_PosColor >();
						OpenGL()->Render_SetAttributeParameter(s_shader_id,"a_color",t_stride_byte,t_offset_byte);
					}
				}

				s32 pp_max = s_vertex->GetMaxParts();
				for(s32 pp=0;pp<pp_max;pp++){
					//�o�[�e�b�N�X�I�t�Z�b�g�B
					s32 t_vertex_offset = s_vertex->GetVertexOffset(pp);

					//�o�[�e�b�N�X���B
					s32 t_vertex_countof = s_vertex->GetVertexCountOf(pp);

					//�`��B
					if(t_vertex_countof > 0){
						OpenGL()->Render_DrawArray_Triangle(t_vertex_offset,t_vertex_countof);
					}
				}
			}
			OpenGL()->Render_SetShader(-1);
		}

	}
}

bool opengl_update(f32 a_delta,bool a_endrequest)
{
	if(s_step == 0){

		NBsys::NFile::StartSystem(s_device_max);
		NBsys::NFile::SetRoot(s_device_index,L"./");

		s_step++;
	}else if(s_step == 1){

		//vertex
		{
			s_vertex = NBsys::NModel::Preset_Box< NBsys::NModel::Model_Vertex_Data_PosColor >();
		}

		//vertexbuffer_id
		{
			sharedptr< u8 > t_data_byte(reinterpret_cast< const u8* >(s_vertex->GetVertexPointer()),null_delete());
			s32 t_size_byte = s_vertex->GetVertexStrideByte() * s_vertex->GetVertexAllCountOf();
			s32 t_stride_byte = s_vertex->GetVertexStrideByte();
			s_vertexbuffer_id = OpenGL()->CreateVertexBuffer(t_data_byte,t_size_byte,t_stride_byte);
		}

		//shader
		{
			s_asyncresult.Create(false);
			sharedptr< NBsys::NOpengl::Opengl_ShaderLayout > t_shader_layout(new NBsys::NOpengl::Opengl_ShaderLayout());
			{
				sharedptr< STLVector< NBsys::NOpengl::Opengl_ShaderLayout::Uniform >::Type > t_vertex_uniform_list(new STLVector< NBsys::NOpengl::Opengl_ShaderLayout::Uniform >::Type());
				{
					t_vertex_uniform_list->push_back(NBsys::NOpengl::Opengl_ShaderLayout::Uniform("a_view_projection",NBsys::NOpengl::Opengl_ShaderValueType::Float16,1));
				}

				sharedptr< STLVector< NBsys::NOpengl::Opengl_ShaderLayout::Attribute >::Type > t_vertex_attribute_list(new STLVector< NBsys::NOpengl::Opengl_ShaderLayout::Attribute >::Type());
				{
					t_vertex_attribute_list->push_back(NBsys::NOpengl::Opengl_ShaderLayout::Attribute("a_position",NBsys::NOpengl::Opengl_ShaderValueType::Float3));
					t_vertex_attribute_list->push_back(NBsys::NOpengl::Opengl_ShaderLayout::Attribute("a_color",NBsys::NOpengl::Opengl_ShaderValueType::Float4));
				}

				t_shader_layout->AddItem(
					NBsys::NOpengl::Opengl_ShaderLayout::Item(
						s_shader_id,
						sharedptr< NBsys::NFile::File_Object >(new NBsys::NFile::File_Object(s_device_index,L"./project_test/simple.vert",-1,s_file_allocator,1)),
						sharedptr< NBsys::NFile::File_Object >(new NBsys::NFile::File_Object(s_device_index,L"./project_test/simple.frag",-1,s_file_allocator,1)),
						t_vertex_uniform_list,
						t_vertex_attribute_list
					)
				);
			}
			OpenGL()->LoadShaderRequest(t_shader_layout,s_asyncresult);
		}

		s_step++;
	}else if(s_step == 2){
		if(s_asyncresult.Get() == true){
			s_step++;
		}
	}else if(s_step == 3){
		s_step++;
	}else{
		s_step = 100;
	}

	if(a_endrequest == true){

		OpenGL()->DeleteVertexBuffer(s_vertexbuffer_id);
		s_vertexbuffer_id = -1;

		OpenGL()->DeleteShader(s_shader_id);

		s_step = -1;

		//���f�B
		return false;
	}else{
		//�p���B
		return true;
	}
}

/** Test
*/
void Test()
{
	//opengl
	OpenGL().reset(new NBsys::NOpengl::Opengl());

	//opengl init
	OpenGL()->Init(opengl_update,opengl_draw);

	//opengl main
	OpenGL()->Main();

	//EndSystemRequest
	NBsys::NFile::EndSystemRequest();

	//EndWaitSystem
	NBsys::NFile::EndWaitSystem();
}

