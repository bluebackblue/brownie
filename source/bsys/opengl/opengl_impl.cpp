

/**
 * Copyright (c) 2017 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief OpenGL�B
*/


/** include
*/
#include <bsys_pch.h>


/** include
*/
#include "../types/types.h"


/** include
*/
#include "./opengl_impl.h"
#include "./opengl.h"
#include "./opengl_impl_vertexbuffer.h"
//#include "./opengl_impl_actionbatching.h"
//#include "./opengl_impl_font.h"


/** include
*/
#include "./opengl_impl_actionbatching_vertexbuffer_create.h"
#include "./opengl_impl_actionbatching_vertexbuffer_delete.h"
#include "./opengl_impl_actionbatching_shader_load.h"
#include "./opengl_impl_actionbatching_shader_delete.h"


/** lib
*/
#if(BSYS_OPENGL_ENABLE)
	#if defined(ROM_MASTER)
		#if defined(ROM_32BIT)

			#pragma comment(lib,"glfw-3.2.1/glfw-3.2.1.bin.WIN32/lib-vc2015/glfw3.lib")
			#pragma comment(lib,"glew-2.0.0/lib/Release/Win32/glew32s.lib")
			#pragma comment(lib,"opengl32.lib")

		#else

			#pragma comment(lib,"glfw-3.2.1/glfw-3.2.1.bin.WIN64/lib-vc2015/glfw3.lib")
			#pragma comment(lib,"glew-2.0.0/lib/Release/x64/glew32s.lib")
			#pragma comment(lib,"opengl32.lib")

		#endif
	#else
		#if defined(ROM_32BIT)

			#pragma comment(lib,"glfw-3.2.1/glfw-3.2.1.bin.WIN32/lib-vc2015/glfw3.lib")
			#pragma comment(lib,"glew-2.0.0/lib/Release/Win32/glew32s.lib")
			#pragma comment(lib,"opengl32.lib")

		#else

			#pragma comment(lib,"glfw-3.2.1/glfw-3.2.1.bin.WIN64/lib-vc2015/glfw3.lib")
			#pragma comment(lib,"glew-2.0.0/lib/Release/x64/glew32s.lib")
			#pragma comment(lib,"opengl32.lib")

		#endif
	#endif
#endif


/** NBsys::NOpengl
*/
#if(BSYS_OPENGL_ENABLE)
namespace NBsys{namespace NOpengl
{
	namespace NImpl
	{
		/** CreateShader�B
		*/
		bool CreateShader(bool a_is_vertex,const STLWString& a_name,const GLchar** a_source,s32 a_countof,RawID& a_out_shader_rawid)
		{
			RawID t_shader_rawid;

			//glCreateShader
			if(a_is_vertex == true){
				t_shader_rawid.rawid = glCreateShader(GL_VERTEX_SHADER);
			}else{
				t_shader_rawid.rawid = glCreateShader(GL_FRAGMENT_SHADER);
			}

			if(t_shader_rawid.IsInvalid() == false){

				//glShaderSource
				glShaderSource(t_shader_rawid.rawid,a_countof,a_source,nullptr);

				{
					//glCompileShader
					glCompileShader(t_shader_rawid.rawid);

					GLint t_status = GL_FALSE;
					glGetShaderiv(t_shader_rawid.rawid,GL_COMPILE_STATUS,&t_status);
					if(t_status == GL_FALSE){
						GLint t_infoLogLength;
						glGetShaderiv(t_shader_rawid.rawid,GL_INFO_LOG_LENGTH,&t_infoLogLength);
						sharedptr< GLchar > t_logbuffer(new GLchar[t_infoLogLength],default_delete< GLchar[] >());
						glGetShaderInfoLog(t_shader_rawid.rawid,t_infoLogLength,NULL,t_logbuffer.get());
						TAGLOG("CreateShader","%ls %s",a_name.c_str(),t_logbuffer.get());
						return false;
					}else{
						TAGLOG("CreateShader","%ls ok",a_name.c_str());
					}
				}

				a_out_shader_rawid = t_shader_rawid;
				return true;
			}

			ASSERT(0);
			return false;
		}

		/** LinkShader�B
		*/
		bool LinkShader(const STLWString& a_vertex_name,const STLWString& a_fragment_name,const RawID& a_vertexshader_rawid,const RawID& a_fragmentshader_rawid,RawID& a_out_shaderprogram_rawid)
		{
			RawID t_shaderprogram_rawid;

			//glCreateProgram
			t_shaderprogram_rawid.rawid = glCreateProgram();

			if(t_shaderprogram_rawid.IsInvalid() == false){

				{
					//glAttachShader
					glAttachShader(t_shaderprogram_rawid.rawid,a_vertexshader_rawid.rawid);

					//glAttachShader
					glAttachShader(t_shaderprogram_rawid.rawid,a_fragmentshader_rawid.rawid);
				}

				{
					//gl_LinkProgram
					glLinkProgram(t_shaderprogram_rawid.rawid);

					GLint t_status = GL_FALSE;
					glGetProgramiv(t_shaderprogram_rawid.rawid,GL_LINK_STATUS,&t_status);
					if(t_status == GL_FALSE){
						GLint t_infoLogLength;
						glGetProgramiv(t_shaderprogram_rawid.rawid,GL_INFO_LOG_LENGTH,&t_infoLogLength);
						sharedptr< GLchar > t_logbuffer(new GLchar[t_infoLogLength],default_delete< GLchar[] >());
						glGetProgramInfoLog(t_shaderprogram_rawid.rawid,t_infoLogLength,NULL,t_logbuffer.get());
						TAGLOG("LinkShader","%ls %ls %s",a_vertex_name.c_str(),a_fragment_name.c_str(),t_logbuffer.get());
						return false;
					}else{
						TAGLOG("LinkShader","%ls %ls ok",a_vertex_name.c_str(),a_fragment_name.c_str());
					}
				}

				a_out_shaderprogram_rawid = t_shaderprogram_rawid;
				return true;
			}

			ASSERT(0);
			return false;
		}

		/** DeleteShader
		*/
		void DeleteShader(const RawID& a_vertexshader_rawid,const RawID& a_fragmentshader_rawid,RawID& a_shaderprogram_rawid)
		{
			if((a_shaderprogram_rawid.IsInvalid() == false) && (a_vertexshader_rawid.IsInvalid() == false)){
				glDetachShader(a_shaderprogram_rawid.rawid,a_vertexshader_rawid.rawid);
			}
			if((a_shaderprogram_rawid.IsInvalid() == false) && (a_fragmentshader_rawid.IsInvalid() == false)){
				glDetachShader(a_shaderprogram_rawid.rawid,a_fragmentshader_rawid.rawid);
			}

			if(a_shaderprogram_rawid.IsInvalid() == false){
				glDeleteProgram(a_shaderprogram_rawid.rawid);
			}

			if(a_vertexshader_rawid.IsInvalid() == false){
				glDeleteShader(a_vertexshader_rawid.rawid);
			}

			if(a_fragmentshader_rawid.IsInvalid() == false){
				glDeleteShader(a_fragmentshader_rawid.rawid);
			}
		}
	}

	/** constructor
	*/
	Opengl_Impl::Opengl_Impl() throw()
		:
		lockobject(),
		window(nullptr),
		performance_counter_update(0ULL),
		update_proc(nullptr),
		draw_proc(nullptr),
		mouse_l(false),
		mouse_r(false),
		mouse_x(0),
		mouse_y(0),
		id_maker(),
		actionbatching(),
		vertexbuffer_list(),
		shaderstate_list(),
		current_shaderprogram_rawid(),
		current_vertexarray_rawid()
	{
		this->shaderstate_list.reserve(BSYS_OPENGL_SHADERIDMAX);
		for(s32 ii=0;ii<BSYS_OPENGL_SHADERIDMAX;ii++){
			this->shaderstate_list.push_back(sharedptr< Opengl_Impl_ShaderState >());
		}


		#if(0)

		current_framebuffer_rawid(),
		current_texture_rawid(),

		#endif
	}

	/** destructor
	*/
	Opengl_Impl::~Opengl_Impl() throw()
	{
	}

	/** Init�B
	*/
	void Opengl_Impl::Init(bool (*a_update_proc)(f32 a_delta,bool a_endrequest),void (*a_draw_proc)())
	{
		AutoLock t_autolock(this->lockobject);

		{
			{
				s32 t_ret_glfw = glfwInit();

				if(t_ret_glfw != GL_FALSE){

					this->window = glfwCreateWindow(BSYS_OPENGL_WIDTH,BSYS_OPENGL_HEIGHT,"window",WIN_NULL,WIN_NULL);
					if(this->window == nullptr){

						glfwTerminate();
						ASSERT(0);

					}

				}else{

					ASSERT(0);

				}

				if(this->window != nullptr){
					glfwMakeContextCurrent(this->window);

					GLenum t_ret_glew = glewInit();

					if(t_ret_glew == GLEW_OK){
					}else{

						ASSERT(0);

					}
				}else{

					ASSERT(0);

				}
			}

			{
				TAGLOG("GL_VENDOR",											"%s",glGetString(GL_VENDOR));
				TAGLOG("GL_RENDERER",										"%s",glGetString(GL_RENDERER));
				TAGLOG("GL_VERSION",										"%s",glGetString(GL_VERSION));
				TAGLOG("GL_SHADING_LANGUAGE_VERSION",						"%s",glGetString(GL_SHADING_LANGUAGE_VERSION));

				{
					GLint t_max_textureunit = 0;

					glGetIntegerv(GL_MAX_TEXTURE_UNITS,						&t_max_textureunit);
					TAGLOG("GL_MAX_TEXTURE_UNITS",							"%d",t_max_textureunit);

					glGetIntegerv(GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS,		&t_max_textureunit);
					TAGLOG("GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS",				"%d",t_max_textureunit);

					glGetIntegerv(GL_MAX_TEXTURE_SIZE,						&t_max_textureunit);
					TAGLOG("GL_MAX_TEXTURE_SIZE",							"%d",t_max_textureunit);

					glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS,				&t_max_textureunit);
					TAGLOG("GL_MAX_TEXTURE_IMAGE_UNITS",					"%d",t_max_textureunit);
				}
			}

			//�����ݒ�B
			{
				glfwSwapInterval(1);

				//glColor4f(1.0f,1.0f,1.0f,1.0f);
				//glNormal3f(0.0f,1.0f,0.0f);
				//glDisable(GL_LIGHTING);
			}

			this->update_proc = a_update_proc;
			this->draw_proc = a_draw_proc;

			u64 t_pcounter_now = PerformanceCounter::GetPerformanceCounter();
			this->performance_counter_update = t_pcounter_now;
		}
	}

	/** Main�B
	*/
	void Opengl_Impl::Main()
	{
		AutoLock t_autolock(this->lockobject);

		{
			bool t_loop = true;

			while(t_loop == true){

				glfwPollEvents();

				{
					if(glfwGetMouseButton(this->window,GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS){
						this->mouse_l = true;
					}else{
						this->mouse_l = false;
					}
					if(glfwGetMouseButton(this->window,GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS){
						this->mouse_r = true;
					}else{
						this->mouse_r = false;
					}
				}

				{
					f64 t_x = 0.0;
					f64 t_y = 0.0;
					glfwGetCursorPos(this->window,&t_x,&t_y);
					{
						this->mouse_x = static_cast<s32>(t_x);
						this->mouse_y = static_cast<s32>(t_y);
					}
				}

				if(this->update_proc != nullptr){
					u64 t_pcounter_now = PerformanceCounter::GetPerformanceCounter();
					u64 t_pcounter_sec = PerformanceCounter::GetPerformanceSecCounter();

					s32 t_count = 0;
					for(s32 ii=0;ii<3;ii++){
						u64 t_count_update = t_pcounter_now - this->performance_counter_update;
						if(t_count_update >= (t_pcounter_sec / BSYS_OPENGL_UPDATE_FPS)){
							this->performance_counter_update += (t_pcounter_sec / BSYS_OPENGL_UPDATE_FPS);

							if(this->update_proc != nullptr){

								AutoUnlock t_autounlock(t_autolock);

								t_count++;
								bool t_ret = (*this->update_proc)(1.0f/BSYS_OPENGL_UPDATE_FPS,glfwWindowShouldClose(this->window)!=0);
								if(t_ret == true){
									//�p���B
								}else{
									//���f�B
									t_loop = false;
									break;
								}
							}
						}else{
							break;
						}
					}

					//�t���[���X�L�b�v�B
					if(t_count >= 3){
						this->performance_counter_update = t_pcounter_now;
					}
				}

				{
					AutoUnlock t_autounlock(t_autolock);

					{
						AutoLock t_autolock_actionbatching(this->actionbatching_lockobject);

						this->actionbatching.Update(1.0f);
					}

					if(this->draw_proc != nullptr){
						(*this->draw_proc)();
					}
				}

				glfwSwapBuffers(this->window);
			}

			glfwTerminate();

			this->update_proc = nullptr;
			this->draw_proc = nullptr;
		}
	}

	/** StartBatching
	*/
	void Opengl_Impl::StartBatching(sharedptr< NBsys::NActionBatching::ActionBatching_ActionList >& a_actionlist)
	{
		AutoLock t_autolock_actionbatching(this->actionbatching_lockobject);

		{
			this->actionbatching.StartBatching(a_actionlist);
		}
	}

	/** �o�[�e�b�N�X�o�b�t�@�쐬�B
	*/
	s32 Opengl_Impl::CreateVertexBuffer(const sharedptr< u8 >& a_data_byte,s32 a_size_byte,s32 a_stride_byte)
	{
		AutoLock t_autolock(this->lockobject);

		{
			//�o�[�e�b�N�X�o�b�t�@�h�c�B
			s32 t_vertexbuffer_id = this->id_maker.MakeID();

			//�o�[�e�b�N�X�o�b�t�@�B
			sharedptr< Opengl_Impl_VertexBuffer > t_vertexbuffer(new Opengl_Impl_VertexBuffer(a_data_byte,a_size_byte,a_stride_byte));

			//�����_�[�R�}���h�B
			sharedptr< NBsys::NActionBatching::ActionBatching_ActionList > t_actionlist = new NBsys::NActionBatching::ActionBatching_ActionList();
			{
				t_actionlist->Add(new Opengl_Impl_ActionBatching_VertexBuffer_Create(*this,t_vertexbuffer));
			}
			this->StartBatching(t_actionlist);

			//�Ǘ����X�g�B
			this->vertexbuffer_list.insert(STLMap< s32 , sharedptr< Opengl_Impl_VertexBuffer > >::value_type(t_vertexbuffer_id,t_vertexbuffer));

			return t_vertexbuffer_id;
		}
	}

	/** �o�[�e�b�N�X�o�b�t�@�폜�B
	*/
	void Opengl_Impl::DeleteVertexBuffer(s32 a_vertexbufferid)
	{
		AutoLock t_autolock(this->lockobject);

		{
			//�o�[�e�b�N�X�o�b�t�@�B
			STLMap< s32 , sharedptr< Opengl_Impl_VertexBuffer > >::iterator t_it = this->vertexbuffer_list.find(a_vertexbufferid);
			sharedptr< Opengl_Impl_VertexBuffer >& t_vertexbuffer = t_it->second;

			//�����_�[�R�}���h�B
			sharedptr< NBsys::NActionBatching::ActionBatching_ActionList > t_actionlist = new NBsys::NActionBatching::ActionBatching_ActionList();
			{
				t_actionlist->Add(new Opengl_Impl_ActionBatching_VertexBuffer_Delete(*this,t_vertexbuffer));
			}
			this->StartBatching(t_actionlist);

			//�Ǘ����X�g�B
			this->vertexbuffer_list.erase(t_it);
		}
	}

	/** �V�F�[�_�[���[�h�J�n�B
	*/
	void Opengl_Impl::LoadShaderRequest(const sharedptr< Opengl_ShaderLayout >& a_shaderlayout,AsyncResult< bool >& a_asyncresult)
	{
		AutoLock t_autolock(this->lockobject);
		
		{
			//�����_�[�R�}���h�B
			sharedptr< NBsys::NActionBatching::ActionBatching_ActionList > t_actionlist = new NBsys::NActionBatching::ActionBatching_ActionList();
			{
				t_actionlist->Add(new Opengl_Impl_ActionBatching_Shader_Load(*this,a_shaderlayout,a_asyncresult));
			}
			this->StartBatching(t_actionlist);
		}
	}

	/** �V�F�[�_�[�폜�B
	*/
	void Opengl_Impl::DeleteShader(s32 a_shaderid)
	{
		AutoLock t_autolock(this->lockobject);
		
		{
			//�V�F�[�_�[�X�e�[�^�X�B
			sharedptr< Opengl_Impl_ShaderState > t_shaderstate = this->shaderstate_list[a_shaderid];

			//�����_�[�R�}���h�B
			sharedptr< NBsys::NActionBatching::ActionBatching_ActionList > t_actionlist = new NBsys::NActionBatching::ActionBatching_ActionList();
			{
				t_actionlist->Add(new Opengl_Impl_ActionBatching_Shader_Delete(*this,t_shaderstate));
			}
			this->StartBatching(t_actionlist);

			//�Ǘ����X�g�B
			this->shaderstate_list[a_shaderid].reset();
		}
	}

	#if(0)

	/** SetShadeModel
	*/
	void Opengl_Impl::SetShadeModel(Opengl_ShadeModelType::Id a_shademodeltype)
	{
		//AutoLock t_autolock(this->lockobject);

		{
			if(a_shademodeltype == Opengl_ShadeModelType::Flat){
				#if(BSYS_OPENGL_DETAILLOG_ENABLE)
				{
					TAGLOG("gl",VASTRING_DEBUG("glShadeModel : GL_FLAT"));
				}
				#endif

				glShadeModel(GL_FLAT);
			}else{
				#if(BSYS_OPENGL_DETAILLOG_ENABLE)
				{
					TAGLOG("gl",VASTRING_DEBUG("glShadeModel : GL_SMOOTH"));
				}
				#endif

				glShadeModel(GL_SMOOTH);
			}
		}
	}

	/** [���C���X���b�h]�e�N�X�`���\�쐬�B
	*/
	s32 Opengl_Impl::CreateTexture(const sharedptr< NBsys::NTexture::Texture >& a_texture)
	{
		AutoLock t_autolock(this->lockobject);

		{
			//�e�N�X�`���[�B
			sharedptr< Opengl_Impl_Texture > t_texture(new Opengl_Impl_Texture(a_texture));

			//�����_�[�R�}���h�B
			sharedptr< NBsys::NActionBatching::ActionBatching_ActionList > t_actionlist = new NBsys::NActionBatching::ActionBatching_ActionList();
			{
				t_batching->Add(new Opengl_Impl_ActionBatching_CreateTexture(*this,t_texture));
			}
			this->StartBatching(t_batching);

			//�e�N�X�`���[�h�c�쐬�B
			s32 t_texture_id = this->id_maker.MakeID();

			//�Ǘ����X�g�ɓo�^�B
			this->texture_list.insert(STLMap< s32 , sharedptr< Opengl_Impl_Texture > >::value_type(t_texture_id,t_texture));

			return t_texture_id;
		}
	}

	/** [���C���X���b�h]�e�N�X�`���[�����B
	*/
	void Opengl_Impl::DeleteTexture(s32 a_textureid)
	{
		AutoLock t_autolock(this->lockobject);

		{
			//�e�N�X�`���[�B
			STLMap< s32 , sharedptr< Opengl_Impl_Texture > >::iterator t_it = this->texture_list.find(a_textureid);
			sharedptr< Opengl_Impl_Texture >& t_texture = t_it->second;

			//�����_�[�R�}���h�B
			sharedptr< NBsys::NActionBatching::ActionBatching_ActionList > t_actionlist = new NBsys::NActionBatching::ActionBatching_ActionList();
			{
				t_batching->Add(new Opengl_Impl_ActionBatching_DeleteTexture(*this,t_texture));
			}
			this->StartBatching(t_batching);

			//�Ǘ����X�g��������B
			this->texture_list.erase(t_it);
		}
	}

	/** [���C���X���b�h]�t���[���o�b�t�@�쐬�B
	*/
	s32 Opengl_Impl::CreateFrameBuffer(s32 a_textureid_depth,s32 a_textureid_color0)
	{
		AutoLock t_autolock(this->lockobject);

		{
			sharedptr< Opengl_Impl_Texture > t_texture_depth;
			sharedptr< Opengl_Impl_Texture > t_texture_color0;

			//�e�N�X�`���[�BDepth�B
			{
				STLMap< s32 , sharedptr< Opengl_Impl_Texture > >::iterator t_it = this->texture_list.find(a_textureid_depth);
				if(t_it != this->texture_list.end()){
					t_texture_depth = t_it->second;
				}
			}
		
			//�e�N�X�`���[�BColor0�B
			{
				STLMap< s32 , sharedptr< Opengl_Impl_Texture > >::iterator t_it = this->texture_list.find(a_textureid_color0);
				if(t_it != this->texture_list.end()){
					t_texture_color0 = t_it->second;
				}
			}

			//�t���[���o�b�t�@�B
			sharedptr< Opengl_Impl_FrameBuffer > t_framebuffer(new Opengl_Impl_FrameBuffer(t_texture_depth,t_texture_color0));

			//�����_�[�R�}���h�B
			sharedptr< NBsys::NActionBatching::ActionBatching_ActionList > t_actionlist = new NBsys::NActionBatching::ActionBatching_ActionList();
			{
				t_batching->Add(new Opengl_Impl_ActionBatching_CreateFrameBuffer(*this,t_framebuffer));
			}
			this->StartBatching(t_batching);

			//�t���[���o�b�t�@�h�c�쐬�B
			s32 t_framebuffer_id = this->id_maker.MakeID();

			//�Ǘ����X�g�ɓo�^�B
			this->framebuffer_list.insert(STLMap< s32 , sharedptr< Opengl_Impl_FrameBuffer > >::value_type(t_framebuffer_id,t_framebuffer));

			return t_framebuffer_id;
		}
	}

	/** [���C���X���b�h]�t���[���o�b�t�@�폜�B
	*/
	/*
	void Opengl_Impl::Render_SetFrameBuffer(s32 a_framebufferid)
	{
		//AutoLock t_autolock(this->lockobject);

		{
		}
	}
	*/

	/** GetMouse
	*/
	void Opengl_Impl::GetMouse(s32& a_x,s32& a_y,bool& a_left,bool& a_right)
	{
		AutoLock t_autolock(this->lockobject);

		{
			a_x = this->mouse_x;
			a_y = this->mouse_y;
			a_left = this->mouse_l;
			a_right = this->mouse_r;
		}
	}

	/** SetFont
	*/
	void Opengl_Impl::SetFont(sharedptr< NBsys::NFont::Font >& a_font,s32 a_texture_width,const STLString& a_name)
	{
		AutoLock t_autolock(this->lockobject);

		{
			this->font.reset(new Opengl_Impl_Font(*this,a_font,a_texture_width,a_name));
		}
	}

	/** �e�N�X�`���[�q�`�v�h�c�擾�B
	*/
	RawID Opengl_Impl::GetTexture_RawID(s32 a_textureid)
	{
		AutoLock t_autolock(this->lockobject);

		{
			STLMap< s32 , sharedptr< Opengl_Impl_Texture > >::iterator t_it = this->texture_list.find(a_textureid);

			if(t_it != this->texture_list.end()){
				return(t_it->second)->GetTexture_RawID();
			}

			return RawID();
		}
	}

	#endif

	/** [�`�施��]�N���A�J���[�ݒ�B
	*/
	void Opengl_Impl::Render_SetClearColor(const NBsys::NColor::Color_F& a_color)
	{
		//AutoLock t_autolock(this->lockobject);

		{
			#if(BSYS_OPENGL_DETAILLOG_ENABLE)
			{
				TAGLOG("gl",VASTRING_DEBUG("glClearColor : %f : %f : %f : %f",a_color.F_GetR(),a_color.F_GetG(),a_color.F_GetB(),a_color.F_GetA()));
			}
			#endif

			glClearColor(a_color.F_GetR(),a_color.F_GetG(),a_color.F_GetB(),a_color.F_GetA());
		}
	}

	/** [�`�施��]�N���A�o�b�t�@�B
	*/
	void Opengl_Impl::Render_ClearBuffer(bool a_depth,bool a_color)
	{
		//AutoLock t_autolock(this->lockobject);

		{
			GLbitfield t_mask = 0x00000000;

			if(a_depth == true){

				#if(BSYS_OPENGL_DETAILLOG_ENABLE)
				{
					TAGLOG("gl",VASTRING_DEBUG("glClear : GL_DEPTH_BUFFER_BIT"));
				}
				#endif

				t_mask |= GL_DEPTH_BUFFER_BIT;
			}
			if(a_color |= true){

				#if(BSYS_OPENGL_DETAILLOG_ENABLE)
				{
					TAGLOG("gl",VASTRING_DEBUG("glClear : GL_DEPTH_BUFFER_BIT"));
				}
				#endif

				t_mask |= GL_COLOR_BUFFER_BIT;
			}

			if(t_mask > 0x00000000){
				glClear(t_mask);
			}
		}
	}

	/** [�`�施��]���[���h���C���`��B

	�E�� : �e�w = X�� / �l�����w = Y�� / ���w = Z���B

	*/
	#if(ROM_DEVELOP)
	void Opengl_Impl::Render_DrawWorldLine()
	{
		//AutoLock t_autolock(this->lockobject);

		{
			glBegin(GL_LINES);
			{
				//x:blue.
				{
					glColor3f(1.0f,1.0f,1.0f);
					glVertex3f(0.0f,0.0f,0.0f);
					glColor3f(1.0f,1.0f,1.0f);
					glVertex3f(-1000.0f,0.0f,0.0f);

					glColor3f(0.0f,0.0f,1.0f);
					glVertex3f(0.0f,0.0f,0.0f);
					glColor3f(0.0f,0.0f,1.0f);
					glVertex3f(1000.0f,0.0f,0.0f);
				}

				//y:green
				{
					glColor3f(1.0f,1.0f,1.0f);
					glVertex3f(0.0f,0.0f,0.0f);
					glColor3f(1.0f,1.0f,1.0f);
					glVertex3f(0.0f,-1000.0f,0.0f);

					glColor3f(0.0f,1.0f,0.0f);
					glVertex3f(0.0f,0.0f,0.0f);
					glColor3f(0.0f,1.0f,0.0f);
					glVertex3f(0.0f,1000.0f,0.0f);
				}

				//z:red
				{
					glColor3f(1.0f,1.0f,1.0f);
					glVertex3f(0.0f,0.0f,0.0f);
					glColor3f(1.0f,1.0f,1.0f);
					glVertex3f(0.0f,0.0f,-1000.0f);

					glColor3f(1.0f,0.0f,0.0f);
					glVertex3f(0.0f,0.0f,0.0f);
					glColor3f(1.0f,0.0f,0.0f);
					glVertex3f(0.0f,0.0f,1000.0f);
				}
			}
			glEnd();
		}
	}
	#endif

	/** [�`�施��]�o�[�e�b�N�X�o�b�t�@�쐬�B
	*/
	void Opengl_Impl::Render_CreateVertexBuffer(sharedptr< Opengl_Impl_VertexBuffer >& a_vertexbuffer)
	{
		//AutoLock t_autolock(this->lockobject);

		{
			RawID t_vertexbuffer_rawid;

			{
				glGenBuffers(1,&t_vertexbuffer_rawid.rawid);

				#if(BSYS_OPENGL_DETAILLOG_ENABLE)
				{
					TAGLOG("gl",VASTRING_DEBUG("glGenBuffers : vertexbuffer_rawid = %d",t_vertexbuffer_rawid.rawid));
				}
				#endif
			}

			if(t_vertexbuffer_rawid.IsInvalid() == false){
				a_vertexbuffer->SetVertexBuffer_RawID(t_vertexbuffer_rawid);

				#if(BSYS_OPENGL_DETAILLOG_ENABLE)
				{
					TAGLOG("gl",VASTRING_DEBUG("glBindBuffer : GL_ARRAY_BUFFER : vertexbuffer_rawid = %d",t_vertexbuffer_rawid.rawid));
				}
				#endif
			
				glBindBuffer(GL_ARRAY_BUFFER,t_vertexbuffer_rawid.rawid);

				{
					//GL_DYNAMIC_DRAW : �f�[�^�ύX�\�ȃo�[�e�b�N�X�o�b�t�@�B
					//GL_STATIC_DRAW : �f�[�^�ύX�s�ȃo�[�e�b�N�X�o�b�t�@�B

					const u8* t_data_byte = a_vertexbuffer->GetDataByte().get();
					s32 t_size_byte = a_vertexbuffer->GetSizeByte();

					#if(BSYS_OPENGL_DETAILLOG_ENABLE)
					{
						TAGLOG("gl",VASTRING_DEBUG("glBufferData : GL_ARRAY_BUFFER : t_size_byte = %d : data_byte = 0x%08x : GL_STATIC_DRAW",t_size_byte,t_data_byte));
					}
					#endif

					glBufferData(GL_ARRAY_BUFFER,t_size_byte,t_data_byte,GL_STATIC_DRAW);
				}

				#if(BSYS_OPENGL_DETAILLOG_ENABLE)
				{
					TAGLOG("gl",VASTRING_DEBUG("glBindBuffer : GL_ARRAY_BUFFER : 0"));
				}
				#endif

				glBindBuffer(GL_ARRAY_BUFFER,0);
			}else{
				ASSERT(0);
			}
		}
	}

	/** [�`�施��]�o�[�e�b�N�X�o�b�t�@�폜�B
	*/
	void Opengl_Impl::Render_DeleteVertexBuffer(sharedptr< Opengl_Impl_VertexBuffer >& a_vertexbuffer)
	{
		//AutoLock t_autolock(this->lockobject);

		{
			if(a_vertexbuffer){
				RawID t_vertexbuffer_rawid = a_vertexbuffer->GetVertexBuffer_RawID();

				if(t_vertexbuffer_rawid.IsInvalid() == false){

					#if(BSYS_OPENGL_DETAILLOG_ENABLE)
					{
						TAGLOG("gl",VASTRING_DEBUG("glDeleteBuffers : vertexbuffer_rawid = %d",t_vertexbuffer_rawid.rawid));
					}
					#endif

					glDeleteBuffers(1,&t_vertexbuffer_rawid.rawid);
				}else{
					ASSERT(0);
				}
			}else{
				ASSERT(0);
			}
		}
	}

	/** [�`�施��]�V�F�[�_�[���[�h�B
	*/
	void Opengl_Impl::Render_LoadShader(sharedptr< Opengl_ShaderLayout >& a_shaderlayout)
	{
		AutoLock t_autolock(this->lockobject);

		{
			s32 ii_max = a_shaderlayout->GetMax();	
			for(s32 ii=0;ii<ii_max;ii++){
				Opengl_ShaderLayout::Item& t_item = a_shaderlayout->GetItem(ii);

				sharedptr< Opengl_Impl_ShaderState > t_shaderstate(new Opengl_Impl_ShaderState());

				bool t_isload = true;
				if(t_item.vertex_fileobject->GetErrorCode() == ErrorCode::Id::Success){
					ASSERT(t_item.vertex_fileobject->GetAddAllocateSize() >= 1);
					t_item.vertex_fileobject->GetLoadData().get()[t_item.vertex_fileobject->GetLoadSize()] = 0x00;
				}else{
					t_isload = false;
				}

				if(t_item.fragment_fileobject->GetErrorCode() == ErrorCode::Id::Success){
					ASSERT(t_item.fragment_fileobject->GetAddAllocateSize() >= 1);
					t_item.fragment_fileobject->GetLoadData().get()[t_item.fragment_fileobject->GetLoadSize()] = 0x00;
				}else{
					t_isload = false;
				}

				if(t_isload == false){
					//�ǂݍ��ݎ��s�B

					ASSERT(0);
				}else{
					//�ǂݍ��ݐ����B

					const GLchar* t_vertex_source[] = {
						reinterpret_cast< GLchar* >(t_item.vertex_fileobject->GetLoadData().get())
					};
					const GLchar* t_fragment_source[] = {
						reinterpret_cast< GLchar* >(t_item.fragment_fileobject->GetLoadData().get())
					};

					bool t_enable = false;

					//�쐬�ƃ����N�B
					if(NImpl::CreateShader(true,t_item.vertex_fileobject->GetFileNameShort(),t_vertex_source,COUNTOF(t_vertex_source),t_shaderstate->vertexshader_rawid) == true){
						if(NImpl::CreateShader(false,t_item.fragment_fileobject->GetFileNameShort(),t_fragment_source,COUNTOF(t_fragment_source),t_shaderstate->fragmentshader_rawid) == true){
							if(NImpl::LinkShader(t_item.vertex_fileobject->GetFileNameShort(),t_item.fragment_fileobject->GetFileNameShort(),t_shaderstate->vertexshader_rawid,t_shaderstate->fragmentshader_rawid,t_shaderstate->shaderprogram_rawid) == true){
								t_enable = true;
							}
						}
					}

					if(t_enable == false){

						//�쐬�ƃ����N�Ɏ��s�B

						t_shaderstate.reset();

						ASSERT(0);
					}else{

						//�쐬�ƃ����N�ɐ����B

						//�J�����g�V�F�[�_�[�ݒ�B
						glUseProgram(t_shaderstate->shaderprogram_rawid.rawid);
						this->current_shaderprogram_rawid = t_shaderstate->shaderprogram_rawid;

						//�J�����g�V�F�[�_�[�p�B���_�z��I�u�W�F�N�g�쐬�B
						glGenVertexArrays(1,&t_shaderstate->vertexarray_rawid.rawid);

						//�J�����g�V�F�[�_�[�p�B�O���[�o���ϐ��쐬�B
						if(t_item.uniform_list != nullptr){
							s32 jj_max = static_cast<s32>(t_item.uniform_list->size());
							for(s32 jj=0;jj<jj_max;jj++){
								Opengl_ShaderLayout::Uniform& t_value = t_item.uniform_list->at(jj);
								GLint t_location = glGetUniformLocation(t_shaderstate->shaderprogram_rawid.rawid,t_value.name.c_str());
								t_shaderstate->uniform_list.insert(
									STLMap< STLString , Opengl_Impl_ShaderState::Uniform >::value_type(
										t_value.name,
										Opengl_Impl_ShaderState::Uniform(
											t_location,
											t_value.shadervaluetype,
											t_value.countof
										)
									)
								);
							}
						}

						//�J�����g�V�F�[�_�[�p�B���_�ϐ��쐬�B
						if(t_item.attribute_list != nullptr){
							s32 jj_max = static_cast<s32>(t_item.attribute_list->size());
							for(s32 jj=0;jj<jj_max;jj++){
								Opengl_ShaderLayout::Attribute& t_value = t_item.attribute_list->at(jj);
								GLint t_location = glGetAttribLocation(t_shaderstate->shaderprogram_rawid.rawid,t_value.name.c_str());
								t_shaderstate->attribute_list.insert(
									STLMap< STLString , Opengl_Impl_ShaderState::Attribute >::value_type(
										t_value.name,
										Opengl_Impl_ShaderState::Attribute(
											t_location,
											t_value.shadervaluetype
										)
									)
								);
							}
						}
					
						//�J�����g�V�F�[�_�[�����B
						glUseProgram(0);
						this->current_shaderprogram_rawid.SetInvalid();

						//�ݒ�B
						this->shaderstate_list[t_item.shaderid] = t_shaderstate;
					}
				}
			}
		}
	}

	/** [�`�施��]�V�F�[�_�[�폜�B
	*/
	void Opengl_Impl::Render_DeleteShader(sharedptr< Opengl_Impl_ShaderState >& a_shaderstate)
	{
		AutoLock t_autolock(this->lockobject);

		if(a_shaderstate){
			//glDeleteVertexArrays
			glDeleteVertexArrays(1,&a_shaderstate->vertexarray_rawid.rawid);
			
			//DeleteShader
			NImpl::DeleteShader(a_shaderstate->vertexshader_rawid,a_shaderstate->fragmentshader_rawid,a_shaderstate->shaderprogram_rawid);
		}else{
			ASSERT(0);
		}
	}

	/** Render_SetShader�B
	*/
	void Opengl_Impl::Render_SetShader(s32 a_shaderid)
	{
		AutoLock t_autolock(this->lockobject);

		{
			if(a_shaderid >= 0){

				//�ݒ�B

				sharedptr< Opengl_Impl_ShaderState >& t_shaderstate = this->shaderstate_list[a_shaderid];

				if(t_shaderstate){

					#if(BSYS_OPENGL_DETAILLOG_ENABLE)
					{
						TAGLOG("gl",VASTRING_DEBUG("glUseProgram : shaderprogram_rawid = %d",t_shaderstate.shaderprogram_rawid));
					}
					#endif

					glUseProgram(t_shaderstate->shaderprogram_rawid.rawid);
					this->current_shaderprogram_rawid = t_shaderstate->shaderprogram_rawid;

					#if(BSYS_OPENGL_DETAILLOG_ENABLE)
					{
						TAGLOG("gl",VASTRING_DEBUG("glBindVertexArray : vertexarray_rawid = %d",t_shaderstate.vertexarray_rawid));
					}
					#endif

					glBindVertexArray(t_shaderstate->vertexarray_rawid.rawid);
					this->current_vertexarray_rawid = t_shaderstate->vertexarray_rawid;
				}else{
					ASSERT(0);

					#if(BSYS_OPENGL_DETAILLOG_ENABLE)
					{
						TAGLOG("gl",VASTRING_DEBUG("glBindVertexArray : 0"));
					}
					#endif

					glBindVertexArray(0);
					this->current_vertexarray_rawid.SetInvalid();

					#if(BSYS_OPENGL_DETAILLOG_ENABLE)
					{
						TAGLOG("gl",VASTRING_DEBUG("glUseProgram : 0"));
					}
					#endif

					glUseProgram(0);
					this->current_shaderprogram_rawid.SetInvalid();
				}
			}else{

				//�����B

				#if(BSYS_OPENGL_DETAILLOG_ENABLE)
				{
					TAGLOG("gl",VASTRING_DEBUG("glBindVertexArray : 0"));
				}
				#endif

				glBindVertexArray(0);
				this->current_vertexarray_rawid.SetInvalid();

				#if(BSYS_OPENGL_DETAILLOG_ENABLE)
				{
					TAGLOG("gl",VASTRING_DEBUG("glUseProgram : 0"));
				}
				#endif

				glUseProgram(0);
				this->current_shaderprogram_rawid.SetInvalid();
			}
		}
	}

	/** Render_SetVertexBuffer�B
	*/
	void Opengl_Impl::Render_SetVertexBuffer(s32 a_vertexbufferid)
	{
		AutoLock t_autolock(this->lockobject);

		{
			ASSERT(this->current_vertexarray_rawid.IsInvalid() == false);

			if(a_vertexbufferid >= 0){
				RawID t_vertexbuffer_rawid;
				STLMap< s32 , sharedptr< Opengl_Impl_VertexBuffer > >::iterator t_it_vertexbuffer = this->vertexbuffer_list.find(a_vertexbufferid);
				if(t_it_vertexbuffer != this->vertexbuffer_list.end()){
					t_vertexbuffer_rawid = t_it_vertexbuffer->second->GetVertexBuffer_RawID();
				}

				if(t_vertexbuffer_rawid.IsInvalid() == false){
					#if(BSYS_OPENGL_DETAILLOG_ENABLE)
					{
						TAGLOG("gl",VASTRING_DEBUG("glBindBuffer : GL_ARRAY_BUFFER : vertexbuffer_rawid = %d",t_vertexbuffer_rawid.rawid));
					}
					#endif

					glBindBuffer(GL_ARRAY_BUFFER,t_vertexbuffer_rawid.rawid);
				}else{
					ASSERT(0);
				}
			}else{
				#if(BSYS_OPENGL_DETAILLOG_ENABLE)
				{
					TAGLOG("gl",VASTRING_DEBUG("glBindBuffer : GL_ARRAY_BUFFER : 0"));
				}
				#endif

				glBindBuffer(GL_ARRAY_BUFFER,0);
			}
		}
	}

	/** Render_SetAttributeParameter�B

	a_shaderid		:	�V�F�[�_�[�h�c�B
	a_name			:	�ϐ����B
	a_stride_byte	:	�f�[�^���B
	a_offset_byte	:	�f�[�^�I�t�Z�b�g�B

	return			:	�g�p�o�C�g���B

	*/
	s32 Opengl_Impl::Render_SetAttributeParameter(s32 a_shaderid,const STLString& a_name,s32 a_stride_byte,s32 a_offset_byte)
	{
		AutoLock t_autolock(this->lockobject);

		{
			s32 t_use_byte = 0;

			sharedptr< Opengl_Impl_ShaderState >& t_shaderstate = this->shaderstate_list[a_shaderid];

			if(t_shaderstate){

				STLMap< STLString , Opengl_Impl_ShaderState::Attribute >::const_iterator t_it = t_shaderstate->attribute_list.find(a_name);
				if(t_it != t_shaderstate->attribute_list.end()){

					s32 t_size = 1;

					GLenum t_type = GL_FLOAT;

					switch(t_it->second.shadervaluetype){
					case Opengl_ShaderValueType::Float:
						{
							t_size = 1;
							t_type = GL_FLOAT;

							t_use_byte = 4 * t_size;
						}break;
					case Opengl_ShaderValueType::Float2:
					case Opengl_ShaderValueType::Vector2:
						{
							t_size = 2;
							t_type = GL_FLOAT;

							t_use_byte = 4 * t_size;
						}break;
					case Opengl_ShaderValueType::Float3:
					case Opengl_ShaderValueType::Vector3:
						{
							t_size = 3;
							t_type = GL_FLOAT;

							t_use_byte = 4 * t_size;
						}break;
					case Opengl_ShaderValueType::Float4:
					case Opengl_ShaderValueType::Vector4:
						{
							t_size = 4;
							t_type = GL_FLOAT;

							t_use_byte = 4 * t_size;
						}break;
					case Opengl_ShaderValueType::Float16:
					case Opengl_ShaderValueType::Matrix:
						{
							t_size = 16;
							t_type = GL_FLOAT;

							t_use_byte = 4 * t_size;
						}break;
					case Opengl_ShaderValueType::IntToFloat:
						{
							t_size = 1;
							t_type = GL_INT;

							t_use_byte = 4 * t_size;
						}break;
					case Opengl_ShaderValueType::Int2ToFloat2:
						{
							t_size = 2;
							t_type = GL_INT;

							t_use_byte = 4 * t_size;
						}break;
					case Opengl_ShaderValueType::Int3ToFloat3:
						{
							t_size = 3;
							t_type = GL_INT;

							t_use_byte = 4 * t_size;
						}break;
					case Opengl_ShaderValueType::Int4ToFloat4:
						{
							t_size = 4;
							t_type = GL_INT;

							t_use_byte = 4 * t_size;
						}break;
					default:
						{
							ASSERT(0);
						}break;
					}

					#if(BSYS_OPENGL_DETAILLOG_ENABLE)
					{
						TAGLOG("gl",VASTRING_DEBUG("glEnableVertexAttribArray : location = %d ",t_it->second.location));
					}
					#endif

					glEnableVertexAttribArray(t_it->second.location);

					#if(BSYS_OPENGL_DETAILLOG_ENABLE)
					{
						TAGLOG("gl",VASTRING_DEBUG("glVertexAttribPointer : location = %d : size = %d : type = %d : GL_FALSE : stride_byte = %d : offset_byte = %d",t_it->second.location,t_size,t_type,a_stride_byte,a_offset_byte));
					}
					#endif

					glVertexAttribPointer(t_it->second.location,t_size,t_type,GL_FALSE,a_stride_byte,(static_cast< char* >(nullptr) + (a_offset_byte)));
				}
			}else{
				ASSERT(0);
			}

			return t_use_byte;
		}
	}

	/** Render_DrawArray_Triangle

	a_offset	: �J�n���钸�_�B
	a_countof	: �`�悷�钸�_���B

	*/
	void Opengl_Impl::Render_DrawArray_Triangle(s32 a_vertex_offset,s32 a_vertex_countof)
	{
		//AutoLock t_autolock(this->lockobject);

		{
			ASSERT((a_vertex_countof % 3) == 0);

			#if(BSYS_OPENGL_DETAILLOG_ENABLE)
			{
				TAGLOG("gl",VASTRING_DEBUG("glDrawArrays : GL_TRIANGLES : vertex_offset = %d : vertex_countof = %d",a_vertex_offset,a_vertex_countof));
			}
			#endif

			glDrawArrays(GL_TRIANGLES,a_vertex_offset,a_vertex_countof);
		}
	}

	/** Render_ViewPort�B
	*/
	void Opengl_Impl::Render_ViewPort(f32 a_x,f32 a_y,f32 a_width,f32 a_height)
	{
		//AutoLock t_autolock(this->lockobject);

		{
			#if(BSYS_OPENGL_DETAILLOG_ENABLE)
			{
				TAGLOG("gl",VASTRING_DEBUG("glViewport : %d : %d : %d : %d",static_cast<s32>(a_x),static_cast<s32>(a_y),static_cast<s32>(a_width),static_cast<s32>(a_height)));
			}
			#endif

			glViewport(static_cast<s32>(a_x),static_cast<s32>(a_y),static_cast<s32>(a_width),static_cast<s32>(a_height));
		}
	}

	/** Render_SetVertexUniform

	a_shaderid		:	�V�F�[�_�[�h�c�B
	a_name			:	�ϐ����B
	a_data_byte		:	�f�[�^�B
	a_countof		:	�z�񐔁B

	*/
	void Opengl_Impl::Render_SetUniformParameter(s32 a_shaderid,const STLString& a_name,const void* a_data_byte,s32 a_countof)
	{
		AutoLock t_autolock(this->lockobject);

		{
			sharedptr< Opengl_Impl_ShaderState >& t_shaderstate = this->shaderstate_list[a_shaderid];

			if(t_shaderstate){
				STLMap< STLString , Opengl_Impl_ShaderState::Uniform >::const_iterator t_it = t_shaderstate->uniform_list.find(a_name);
				if(t_it != t_shaderstate->uniform_list.end()){

					ASSERT(a_countof <= t_it->second.countof);

					switch(t_it->second.shadervaluetype){
					case Opengl_ShaderValueType::Float:
						{
							#if(BSYS_OPENGL_DETAILLOG_ENABLE)
							{
								TAGLOG("gl",VASTRING_DEBUG("glUniform1fv : location = %d : countof = %d : GL_FALSE : data_byte = 0x%08x",t_it->second.location,a_countof,a_data_byte));
							}
							#endif

							glUniform1fv(t_it->second.location,a_countof,reinterpret_cast< const GLfloat* >(a_data_byte));
						}break;
					case Opengl_ShaderValueType::Float2:
					case Opengl_ShaderValueType::Vector2:
						{
							#if(BSYS_OPENGL_DETAILLOG_ENABLE)
							{
								TAGLOG("gl",VASTRING_DEBUG("glUniform2fv : location = %d : countof = %d : GL_FALSE : data_byte = 0x%08x",t_it->second.location,a_countof,a_data_byte));
							}
							#endif

							glUniform2fv(t_it->second.location,a_countof,reinterpret_cast< const GLfloat* >(a_data_byte));
						}break;
					case Opengl_ShaderValueType::Float3:
					case Opengl_ShaderValueType::Vector3:
						{
							#if(BSYS_OPENGL_DETAILLOG_ENABLE)
							{
								TAGLOG("gl",VASTRING_DEBUG("glUniform3fv : location = %d : countof = %d : GL_FALSE : data_byte = 0x%08x",t_it->second.location,a_countof,a_data_byte));
							}
							#endif

							glUniform3fv(t_it->second.location,a_countof,reinterpret_cast< const GLfloat* >(a_data_byte));
						}break;
					case Opengl_ShaderValueType::Float4:
					case Opengl_ShaderValueType::Vector4:
						{
							#if(BSYS_OPENGL_DETAILLOG_ENABLE)
							{
								TAGLOG("gl",VASTRING_DEBUG("glUniform4fv : location = %d : countof = %d : GL_FALSE : data_byte = 0x%08x",t_it->second.location,a_countof,a_data_byte));
							}
							#endif

							glUniform4fv(t_it->second.location,a_countof,reinterpret_cast< const GLfloat* >(a_data_byte));
						}break;
					case Opengl_ShaderValueType::Float16:
					case Opengl_ShaderValueType::Matrix:
						{
							#if(BSYS_OPENGL_DETAILLOG_ENABLE)
							{
								TAGLOG("gl",VASTRING_DEBUG("glUniformMatrix4fv : location = %d : countof = %d : GL_FALSE : data_byte = 0x%08x",t_it->second.location,a_countof,a_data_byte));
							}
							#endif

							glUniformMatrix4fv(t_it->second.location,a_countof,GL_FALSE,reinterpret_cast< const GLfloat* >(a_data_byte));
						}break;
					case Opengl_ShaderValueType::IntToFloat:
						{
							ASSERT(0);
						}break;
					case Opengl_ShaderValueType::Int2ToFloat2:
						{
							ASSERT(0);
						}break;
					case Opengl_ShaderValueType::Int3ToFloat3:
						{
							ASSERT(0);
						}break;
					case Opengl_ShaderValueType::Int4ToFloat4:
						{
							ASSERT(0);
						}break;
					default:
						{
							ASSERT(0);
						}break;
					}
				}else{
					ASSERT(0);
				}
			}else{
				ASSERT(0);
			}
		}
	}

	/** Render_SetDepthTest�B
	*/
	void Opengl_Impl::Render_SetDepthTest(bool a_flag)
	{
		//AutoLock t_autolock(this->lockobject);
	
		{
			if(a_flag == true){
				#if(BSYS_OPENGL_DETAILLOG_ENABLE)
				{
					TAGLOG("gl",VASTRING_DEBUG("glEnable : GL_DEPTH_TEST"));
				}
				#endif

				glEnable(GL_DEPTH_TEST);
			}else{
				#if(BSYS_OPENGL_DETAILLOG_ENABLE)
				{
					TAGLOG("gl",VASTRING_DEBUG("glDisable : GL_DEPTH_TEST"));
				}
				#endif

				glDisable(GL_DEPTH_TEST);
			}
		}
	}

	#if(0)

	/** Render_CreateFrameBuffer�B
	*/
	void Opengl_Impl::Render_CreateFrameBuffer(sharedptr< Opengl_Impl_FrameBuffer >& a_framebuffer)
	{
		AutoLock t_autolock(this->lockobject);

		{
			RawID t_framebuffer_rawid;

			{
				glGenFramebuffersEXT(1,&t_framebuffer_rawid.rawid);

				#if(BSYS_OPENGL_DETAILLOG_ENABLE)
				{
					TAGLOG("gl",VASTRING_DEBUG("glGenFramebuffersEXT : framebuffer_rawid = %d",t_framebuffer_rawid.rawid));
				}
				#endif
			}

			{
				a_framebuffer->SetFrameBuffer_RawID(t_framebuffer_rawid);

				{
					#if(BSYS_OPENGL_DETAILLOG_ENABLE)
					{
						TAGLOG("gl",VASTRING_DEBUG("glBindFramebufferEXT : GL_FRAMEBUFFER_EXT : framebuffer_rawid = %d",t_framebuffer_rawid.rawid));
					}
					#endif

					glBindFramebufferEXT(GL_FRAMEBUFFER_EXT,t_framebuffer_rawid.rawid);
					this->current_framebuffer_rawid = t_framebuffer_rawid;
				}

				/** �t���[���o�b�t�@�I�u�W�F�N�g�Ƀf�v�X�o�b�t�@�p�̃e�N�X�`������������
				*/
				{
					if(a_framebuffer->GetTexture_Depth() != nullptr){
						RawID t_texture_rawid = a_framebuffer->GetTexture_Depth()->GetTexture_RawID();

						#if(BSYS_OPENGL_DETAILLOG_ENABLE)
						{
							TAGLOG("gl",VASTRING_DEBUG("glFramebufferTexture2DEXT : GL_FRAMEBUFFER_EXT : GL_DEPTH_ATTACHMENT_EXT : GL_TEXTURE_2D : texture_rawid = %d : level = %d",t_texture_rawid.rawid,0));
						}
						#endif

						glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT,GL_DEPTH_ATTACHMENT_EXT,GL_TEXTURE_2D,t_texture_rawid.rawid,0);
					}
				
					if(a_framebuffer->GetTexture_Color0() != nullptr){
						RawID t_texture_rawid = a_framebuffer->GetTexture_Color0()->GetTexture_RawID();

						#if(BSYS_OPENGL_DETAILLOG_ENABLE)
						{
							TAGLOG("gl",VASTRING_DEBUG("glFramebufferTexture2DEXT : GL_FRAMEBUFFER_EXT : GL_COLOR_ATTACHMENT0_EXT : GL_TEXTURE_2D : texture_rawid = %d : level = %d",t_texture_rawid.rawid,0));
						}
						#endif

						glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT,GL_COLOR_ATTACHMENT0_EXT,GL_TEXTURE_2D,t_texture_rawid.rawid,0);
					}
				}

				/** �J���[�o�b�t�@�������̂œǂݏ������Ȃ��B
				*/
				/*
				{
					#if(BSYS_OPENGL_DETAILLOG_ENABLE)
					{
						TAGLOG("gl",VASTRING_DEBUG("glDrawBuffer : GL_NONE"));
					}
					#endif

					glDrawBuffer(GL_NONE);

					#if(BSYS_OPENGL_DETAILLOG_ENABLE)
					{
						TAGLOG("gl",VASTRING_DEBUG("glReadBuffer : GL_NONE"));
					}
					#endif

					glReadBuffer(GL_NONE);
				}
				*/

				{
					#if(BSYS_OPENGL_DETAILLOG_ENABLE)
					{
						TAGLOG("gl",VASTRING_DEBUG("glCheckFramebufferStatusEXT : GL_FRAMEBUFFER_EXT"));
					}
					#endif

					GLenum t_status = glCheckFramebufferStatusEXT(GL_FRAMEBUFFER_EXT);
					if(t_status != GL_FRAMEBUFFER_COMPLETE_EXT){
						ASSERT(0);
					}
				}

				#if(BSYS_OPENGL_DETAILLOG_ENABLE)
				{
					TAGLOG("gl",VASTRING_DEBUG("glBindFramebufferEXT : GL_FRAMEBUFFER_EXT : 0"));
				}
				#endif

				glBindFramebufferEXT(GL_FRAMEBUFFER_EXT,0);
				this->current_framebuffer_rawid.SetInvalid();
			}
		}
	}

	/** Render_CreateTexture�B
	*/
	void Opengl_Impl::Render_CreateTexture(sharedptr< Opengl_Impl_Texture >& a_texture)
	{
		AutoLock t_autolock(this->lockobject);

		{
			RawID t_texture_rawid;

			{
				glGenTextures(1,&t_texture_rawid.rawid);

				#if(BSYS_OPENGL_DETAILLOG_ENABLE)
				{
					TAGLOG("gl",VASTRING_DEBUG("glGenTextures : texture_rawid = %d",t_texture_rawid));
				}
				#endif
			}

			if(t_texture_rawid.IsInvalid() == false){
				a_texture->SetTexture_RawID(t_texture_rawid);

				switch(a_texture->GetTexture()->GetTextureType()){
				case NBsys::NTexture::TextureType::Depth:
					{

						{
							#if(BSYS_OPENGL_DETAILLOG_ENABLE)
							{
								TAGLOG("gl",VASTRING_DEBUG("glBindTexture : GL_TEXTURE_2D : texture_rawid = %d",t_texture_rawid));
							}
							#endif

							glBindTexture(GL_TEXTURE_2D,t_texture_rawid.rawid);
							this->current_texture_rawid = t_texture_rawid;
						}

						/** �T�C�Y�B
						*/
						s32 t_width = a_texture->GetTexture()->GetWidth();
						s32 t_height = a_texture->GetTexture()->GetHeight();

						/** �e�N�X�`���̊��蓖�āB
						*/
						{
							#if(BSYS_OPENGL_DETAILLOG_ENABLE)
							{
								TAGLOG("gl",VASTRING_DEBUG("glTexImage2D : GL_TEXTURE_2D : level = %d : GL_DEPTH_COMPONENT : width = %d : height = %d : border = %d : GL_DEPTH_COMPONENT : GL_UNSIGNED_BYTE",0,t_width,t_height,0));
							}
							#endif

							glTexImage2D(
								GL_TEXTURE_2D,
								0,
								GL_DEPTH_COMPONENT,
								t_width,
								t_height,
								0,
								GL_DEPTH_COMPONENT,
								GL_UNSIGNED_BYTE,
								nullptr
							);
						}

						/** �e�N�X�`�����g��E�k��������@�̎w��B
						*/
						glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
						glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);

						/** �e�N�X�`���̌J��Ԃ����@�̎w��B
						*/
						glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP);
						glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP);

						//�������ރ|���S���̃e�N�X�`�����W�l�̂q�ƃe�N�X�`���Ƃ̔�r���s���悤�ɂ���B
						glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_COMPARE_MODE,GL_COMPARE_R_TO_TEXTURE);
  
						//�����q�̒l���e�N�X�`���̒l�ȉ��Ȃ�^�i�܂�����j�B
						glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_COMPARE_FUNC,GL_LEQUAL);
  
						//��r�̌��ʂ��P�x�l�Ƃ��ē���B
						glTexParameteri(GL_TEXTURE_2D,GL_DEPTH_TEXTURE_MODE,GL_LUMINANCE);
  
						{
							#if(BSYS_OPENGL_DETAILLOG_ENABLE)
							{
								TAGLOG("gl",VASTRING_DEBUG("glBindTexture : GL_TEXTURE_2D : 0"));
							}
							#endif

							glBindTexture(GL_TEXTURE_2D,0);
							this->current_texture_rawid.SetInvalid();
						}
					}break;
				case NBsys::NTexture::TextureType::R8G8B8A8:
					{

						{
							#if(BSYS_OPENGL_DETAILLOG_ENABLE)
							{
								TAGLOG("gl",VASTRING_DEBUG("glBindTexture : GL_TEXTURE_2D : texture_rawid = %d",t_texture_rawid.rawid));
							}
							#endif

							glBindTexture(GL_TEXTURE_2D,t_texture_rawid.rawid);
							this->current_texture_rawid = t_texture_rawid;
						}

						/** �T�C�Y�B
						*/
						s32 t_width = a_texture->GetTexture()->GetWidth();
						s32 t_height = a_texture->GetTexture()->GetHeight();

						{
							#if(BSYS_OPENGL_DETAILLOG_ENABLE)
							{
								TAGLOG("gl",VASTRING_DEBUG("glTexImage2D : GL_TEXTURE_2D : level = %d : GL_RGBA : width = %d : height = %d : border = %d : GL_RGBA : GL_UNSIGNED_BYTE",0,t_width,t_height,0));
							}
							#endif

							glTexImage2D(
								GL_TEXTURE_2D,
								0,
								GL_RGBA,
								t_width,
								t_height,
								0,
								GL_RGBA,
								GL_UNSIGNED_BYTE,
								a_texture->GetTexture()->GetPixel().get()
							);
						}

						/** �e�N�X�`�����g��E�k��������@�̎w��B
						*/
						glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
						glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);

						/** �e�N�X�`���̌J��Ԃ����@�̎w��B
						*/
						glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
						glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);

						{
							#if(BSYS_OPENGL_DETAILLOG_ENABLE)
							{
								TAGLOG("gl",VASTRING_DEBUG("glBindTexture : GL_TEXTURE_2D : 0"));
							}
							#endif

							glBindTexture(GL_TEXTURE_2D,0);
							this->current_texture_rawid.SetInvalid();
						}
					}break;
				default:
					{
						ASSERT(0);
					}break;
				}
			}
		}
	}

	/** Render_DeleteTexture�B
	*/
	void Opengl_Impl::Render_DeleteTexture(sharedptr< Opengl_Impl_Texture >& a_texture)
	{
		//AutoLock t_autolock(this->lockobject);

		{
			RawID t_texture_rawid = a_texture->GetTexture_RawID();

			if(t_texture_rawid.IsInvalid() == false){

				#if(BSYS_OPENGL_DETAILLOG_ENABLE)
				{
					TAGLOG("gl",VASTRING_DEBUG("glDeleteTextures : texture_rawid = %d",t_texture_rawid.rawid));
				}
				#endif

				glDeleteTextures(1,&t_texture_rawid.rawid);
			}else{
				ASSERT(0);
			}

			t_texture_rawid.SetInvalid();
			a_texture->SetTexture_RawID(t_texture_rawid);
		}
	}



	/** [�����_�[�X���b�hRender_SetColorMask�B
	*/
	void Opengl_Impl::Render_SetColorMask(bool a_r,bool a_g,bool a_b,bool a_a)
	{
		AutoLock t_autolock(this->lockobject);

		{
			#if(BSYS_OPENGL_DETAILLOG_ENABLE)
			{
				TAGLOG("gl",VASTRING_DEBUG("glColorMask : %d : %d : %d : %d",((a_r)?(1):(0)),((a_g)?(1):(0)),((a_b)?(1):(0)),((a_a)?(1):(0))));
			}
			#endif

			glColorMask(((a_r)?(GL_TRUE):(GL_FALSE)),((a_g)?(GL_TRUE):(GL_FALSE)),((a_b)?(GL_TRUE):(GL_FALSE)),((a_a)?(GL_TRUE):(GL_FALSE)));
		}
	}

	/** Render_SetPolygonOffset�B

	(+1.0f,+1.0f) : ���葤�B
	(-1.0f,-1.0f) : ��O���B

	*/
	void Opengl_Impl::Render_SetPolygonOffset(bool a_flag,f32 a_factor,f32 a_unit)
	{
		//AutoLock t_autolock(this->lockobject);

		{
			if(a_flag == true){
				#if(BSYS_OPENGL_DETAILLOG_ENABLE)
				{
					TAGLOG("gl",VASTRING_DEBUG("glEnable : GL_POLYGON_OFFSET_FILL"));
				}
				#endif

				glEnable(GL_POLYGON_OFFSET_FILL);

				#if(BSYS_OPENGL_DETAILLOG_ENABLE)
				{
					TAGLOG("gl",VASTRING_DEBUG("glPolygonOffset : factor = %d : unit = %d",a_factor,a_unit));
				}
				#endif

				glPolygonOffset(a_factor,a_unit);
			}else{
				#if(BSYS_OPENGL_DETAILLOG_ENABLE)
				{
					TAGLOG("gl",VASTRING_DEBUG("glDisable : GL_POLYGON_OFFSET_FILL"));
				}
				#endif

				glDisable(GL_POLYGON_OFFSET_FILL);
			}
		}
	}

	#endif



	#if(0)

	/** Render_SetTextureDirect�B
	*/
	void Opengl_Impl::Render_SetTextureDirect(s32 a_textureunitid,s32 a_textureid)
	{
		AutoLock t_autolock(this->lockobject);

		{
			{
				#if(BSYS_OPENGL_DETAILLOG_ENABLE)
				{
					TAGLOG("gl",VASTRING_DEBUG("glActiveTexture : GL_TEXTURE%d",a_textureunitid));
				}
				#endif

				switch(a_textureunitid){
				case 0:glActiveTexture(GL_TEXTURE0);break;
				case 1:glActiveTexture(GL_TEXTURE1);break;
				case 2:glActiveTexture(GL_TEXTURE2);break;
				case 3:glActiveTexture(GL_TEXTURE3);break;
				case 4:glActiveTexture(GL_TEXTURE4);break;
				case 5:glActiveTexture(GL_TEXTURE5);break;
				case 6:glActiveTexture(GL_TEXTURE6);break;
				case 7:glActiveTexture(GL_TEXTURE7);break;
				case 8:glActiveTexture(GL_TEXTURE8);break;
				case 9:glActiveTexture(GL_TEXTURE9);break;
				case 10:glActiveTexture(GL_TEXTURE10);break;
				case 11:glActiveTexture(GL_TEXTURE11);break;
				case 12:glActiveTexture(GL_TEXTURE12);break;
				case 13:glActiveTexture(GL_TEXTURE13);break;
				case 14:glActiveTexture(GL_TEXTURE14);break;
				case 15:glActiveTexture(GL_TEXTURE15);break;
				case 16:glActiveTexture(GL_TEXTURE16);break;
				case 17:glActiveTexture(GL_TEXTURE17);break;
				case 18:glActiveTexture(GL_TEXTURE18);break;
				case 19:glActiveTexture(GL_TEXTURE19);break;
				case 20:glActiveTexture(GL_TEXTURE20);break;
				case 21:glActiveTexture(GL_TEXTURE21);break;
				case 22:glActiveTexture(GL_TEXTURE22);break;
				case 23:glActiveTexture(GL_TEXTURE23);break;
				case 24:glActiveTexture(GL_TEXTURE24);break;
				case 25:glActiveTexture(GL_TEXTURE25);break;
				case 26:glActiveTexture(GL_TEXTURE26);break;
				case 27:glActiveTexture(GL_TEXTURE27);break;
				case 28:glActiveTexture(GL_TEXTURE28);break;
				case 29:glActiveTexture(GL_TEXTURE29);break;
				case 30:glActiveTexture(GL_TEXTURE30);break;
				case 31:glActiveTexture(GL_TEXTURE31);break;
				default:{ASSERT(0);}break;
				}
			}

			if(a_textureid >= 0){
				STLMap< s32 , sharedptr< Opengl_Impl_Texture > >::iterator t_it = this->texture_list.find(a_textureid);
				if(t_it != this->texture_list.end()){
					RawID t_texture_rawid = (t_it->second)->GetTexture_RawID();
					if(t_texture_rawid.IsInvalid() == false){

						#if(BSYS_OPENGL_DETAILLOG_ENABLE)
						{
							TAGLOG("gl",VASTRING_DEBUG("glEnable : GL_TEXTURE_2D"));
						}
						#endif

						glEnable(GL_TEXTURE_2D);

						#if(BSYS_OPENGL_DETAILLOG_ENABLE)
						{
							TAGLOG("gl",VASTRING_DEBUG("glBindTexture : GL_TEXTURE_2D : texture_rawid = %d",t_texture_rawid.rawid));
						}
						#endif

						glBindTexture(GL_TEXTURE_2D,t_texture_rawid.rawid);
						this->current_texture_rawid = t_texture_rawid;
						return;
					}
				}
			}

			#if(BSYS_OPENGL_DETAILLOG_ENABLE)
			{
				TAGLOG("gl",VASTRING_DEBUG("glBindTexture : GL_TEXTURE_2D : 0"));
			}
			#endif

			glBindTexture(GL_TEXTURE_2D,0);
			this->current_texture_rawid.SetInvalid();

			#if(BSYS_OPENGL_DETAILLOG_ENABLE)
			{
				TAGLOG("gl",VASTRING_DEBUG("glDisable : GL_TEXTURE_2D"));
			}
			#endif

			glDisable(GL_TEXTURE_2D);
		}
	}

	/** Render_SetFrameBuffer�B
	*/
	void Opengl_Impl::Render_SetFrameBuffer(s32 a_framebufferid)
	{
		AutoLock t_autolock(this->lockobject);

		{
			if(a_framebufferid >= 0){
				STLMap< s32 , sharedptr< Opengl_Impl_FrameBuffer > >::iterator t_it = this->framebuffer_list.find(a_framebufferid);
				if(t_it != this->framebuffer_list.end()){
					RawID t_framebuffer_rawid = (t_it->second)->GetFrameBuffer_RawID();
					if(t_framebuffer_rawid.IsInvalid() == false){

						#if(BSYS_OPENGL_DETAILLOG_ENABLE)
						{
							TAGLOG("gl",VASTRING_DEBUG("glBindFramebufferEXT : GL_FRAMEBUFFER_EXT : framebuffer_rawid = %d",t_framebuffer_rawid.rawid));
						}
						#endif

						glBindFramebufferEXT(GL_FRAMEBUFFER_EXT,t_framebuffer_rawid.rawid);
						this->current_framebuffer_rawid = t_framebuffer_rawid;

						return;
					}
				}
			}

			#if(BSYS_OPENGL_DETAILLOG_ENABLE)
			{
				TAGLOG("gl",VASTRING_DEBUG("glBindFramebufferEXT : GL_FRAMEBUFFER_EXT : 0"));
			}
			#endif

			glBindFramebufferEXT(GL_FRAMEBUFFER_EXT,0);
			this->current_framebuffer_rawid.SetInvalid();
		}
	}

	/** Render_SetProjectionMatrix�B
	*/
	void Opengl_Impl::Render_SetProjectionMatrix(const NBsys::NGeometry::Geometry_Matrix_44& a_projection)
	{
		//AutoLock t_autolock(this->lockobject);

		{
			#if(BSYS_OPENGL_DETAILLOG_ENABLE)
			{
				TAGLOG("gl",VASTRING_DEBUG("glMatrixMode : GL_PROJECTION"));
			}
			#endif

			glMatrixMode(GL_PROJECTION);

			#if(BSYS_OPENGL_DETAILLOG_ENABLE)
			{
				TAGLOG("gl",VASTRING_DEBUG("glLoadIdentity"));
			}
			#endif

			glLoadIdentity();
		
			#if(BSYS_OPENGL_DETAILLOG_ENABLE)
			{
				TAGLOG("gl",VASTRING_DEBUG("glLoadMatrixf"));
			}
			#endif

			glLoadMatrixf(&a_projection.m[0][0]);
		}
	}

	/** Render_SetViewMatrix�B
	*/
	void Opengl_Impl::Render_SetViewMatrix(const NBsys::NGeometry::Geometry_Matrix_44& a_view)
	{
		//AutoLock t_autolock(this->lockobject);

		{
			#if(BSYS_OPENGL_DETAILLOG_ENABLE)
			{
				TAGLOG("gl",VASTRING_DEBUG("glMatrixMode : GL_MODELVIEW"));
			}
			#endif

			glMatrixMode(GL_MODELVIEW);

			#if(BSYS_OPENGL_DETAILLOG_ENABLE)
			{
				TAGLOG("gl",VASTRING_DEBUG("glLoadIdentity"));
			}
			#endif

			glLoadIdentity();

			#if(BSYS_OPENGL_DETAILLOG_ENABLE)
			{
				TAGLOG("gl",VASTRING_DEBUG("glLoadMatrixf"));
			}
			#endif

			glLoadMatrixf(&a_view.m[0][0]);
		}
	}






	/** Render_SetAlphaBlend�B
	*/
	void Opengl_Impl::Render_SetAlphaBlend(bool a_flag)
	{
		//AutoLock t_autolock(this->lockobject);

		{
			if(a_flag == true){
				#if(BSYS_OPENGL_DETAILLOG_ENABLE)
				{
					TAGLOG("gl",VASTRING_DEBUG("glEnable : GL_BLEND"));
				}
				#endif

				glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
				glEnable(GL_BLEND);
			}else{
				#if(BSYS_OPENGL_DETAILLOG_ENABLE)
				{
					TAGLOG("gl",VASTRING_DEBUG("glDisable : GL_BLEND"));
				}
				#endif

				glDisable(GL_BLEND);
			}
		}
	}






	/** Render_SetUniformTexture�B
	*/
	void Opengl_Impl::Render_SetUniformTexture(s32 a_shaderid,const STLString& a_name,s32 a_textureid)
	{
		AutoLock t_autolock(this->lockobject);

		{
			if(this->shaderstate_list[a_shaderid].enable == true){

				STLMap< STLString , Opengl_Impl::Uniform >::const_iterator t_it = this->shaderstate_list[a_shaderid].uniform_list.find(a_name);
				if(t_it != this->shaderstate_list[a_shaderid].uniform_list.end()){

					RawID t_texture_rawid;
					{
						if(a_textureid >= 0){
							STLMap< s32 , sharedptr< Opengl_Impl_Texture > >::iterator t_it = this->texture_list.find(a_textureid);
							if(t_it != this->texture_list.end()){
								t_texture_rawid = (t_it->second)->GetTexture_RawID();
							}
						}
					}

					if(t_texture_rawid.IsInvalid() == false){

						GLenum t_activetexture = GL_TEXTURE0;
						GLint t_activetexture_id = 0;

						switch(t_it->second.shadervaluetype){
						case Opengl_ShaderValueType::Texture0:
							{
								t_activetexture = GL_TEXTURE0;
								t_activetexture_id = 0;
							}break;
						case Opengl_ShaderValueType::Texture1:
							{
								t_activetexture = GL_TEXTURE1;
								t_activetexture_id = 1;
							}break;
						case Opengl_ShaderValueType::Texture2:
							{
								t_activetexture = GL_TEXTURE2;
								t_activetexture_id = 2;
							}break;
						case Opengl_ShaderValueType::Texture3:
							{
								t_activetexture = GL_TEXTURE3;
								t_activetexture_id = 3;
							}break;
						case Opengl_ShaderValueType::Texture4:
							{
								t_activetexture = GL_TEXTURE4;
								t_activetexture_id = 4;
							}break;
						case Opengl_ShaderValueType::Texture5:
							{
								t_activetexture = GL_TEXTURE5;
								t_activetexture_id = 5;
							}break;
						case Opengl_ShaderValueType::Texture6:
							{
								t_activetexture = GL_TEXTURE6;
								t_activetexture_id = 6;
							}break;
						case Opengl_ShaderValueType::Texture7:
							{
								t_activetexture = GL_TEXTURE7;
								t_activetexture_id = 7;
							}break;
						case Opengl_ShaderValueType::Texture8:
							{
								t_activetexture = GL_TEXTURE8;
								t_activetexture_id = 8;
							}break;
						case Opengl_ShaderValueType::Texture9:
							{
								t_activetexture = GL_TEXTURE9;
								t_activetexture_id = 9;
							}break;
						case Opengl_ShaderValueType::Texture10:
							{
								t_activetexture = GL_TEXTURE10;
								t_activetexture_id = 10;
							}break;
						case Opengl_ShaderValueType::Texture11:
							{
								t_activetexture = GL_TEXTURE11;
								t_activetexture_id = 11;
							}break;
						case Opengl_ShaderValueType::Texture12:
							{
								t_activetexture = GL_TEXTURE12;
								t_activetexture_id = 12;
							}break;
						case Opengl_ShaderValueType::Texture13:
							{
								t_activetexture = GL_TEXTURE13;
								t_activetexture_id = 13;
							}break;
						case Opengl_ShaderValueType::Texture14:
							{
								t_activetexture = GL_TEXTURE14;
								t_activetexture_id = 14;
							}break;
						case Opengl_ShaderValueType::Texture15:
							{
								t_activetexture = GL_TEXTURE15;
								t_activetexture_id = 15;
							}break;
						case Opengl_ShaderValueType::Texture16:
							{
								t_activetexture = GL_TEXTURE16;
								t_activetexture_id = 16;
							}break;
						case Opengl_ShaderValueType::Texture17:
							{
								t_activetexture = GL_TEXTURE17;
								t_activetexture_id = 17;
							}break;
						case Opengl_ShaderValueType::Texture18:
							{
								t_activetexture = GL_TEXTURE18;
								t_activetexture_id = 18;
							}break;
						case Opengl_ShaderValueType::Texture19:
							{
								t_activetexture = GL_TEXTURE19;
								t_activetexture_id = 19;
							}break;
						case Opengl_ShaderValueType::Texture20:
							{
								t_activetexture = GL_TEXTURE20;
								t_activetexture_id = 20;
							}break;
						case Opengl_ShaderValueType::Texture21:
							{
								t_activetexture = GL_TEXTURE21;
								t_activetexture_id = 21;
							}break;
						case Opengl_ShaderValueType::Texture22:
							{
								t_activetexture = GL_TEXTURE22;
								t_activetexture_id = 22;
							}break;
						case Opengl_ShaderValueType::Texture23:
							{
								t_activetexture = GL_TEXTURE23;
								t_activetexture_id = 23;
							}break;
						case Opengl_ShaderValueType::Texture24:
							{
								t_activetexture = GL_TEXTURE24;
								t_activetexture_id = 24;
							}break;
						case Opengl_ShaderValueType::Texture25:
							{
								t_activetexture = GL_TEXTURE25;
								t_activetexture_id = 25;
							}break;
						case Opengl_ShaderValueType::Texture26:
							{
								t_activetexture = GL_TEXTURE26;
								t_activetexture_id = 26;
							}break;
						case Opengl_ShaderValueType::Texture27:
							{
								t_activetexture = GL_TEXTURE27;
								t_activetexture_id = 27;
							}break;
						case Opengl_ShaderValueType::Texture28:
							{
								t_activetexture = GL_TEXTURE28;
								t_activetexture_id = 28;
							}break;
						case Opengl_ShaderValueType::Texture29:
							{
								t_activetexture = GL_TEXTURE29;
								t_activetexture_id = 29;
							}break;
						case Opengl_ShaderValueType::Texture30:
							{
								t_activetexture = GL_TEXTURE30;
								t_activetexture_id = 30;
							}break;
						case Opengl_ShaderValueType::Texture31:
							{
								t_activetexture = GL_TEXTURE31;
								t_activetexture_id = 31;
							}break;
						default:
							{
								ASSERT(0);
							}break;
						}

						#if(BSYS_OPENGL_DETAILLOG_ENABLE)
						{
							TAGLOG("gl",VASTRING_DEBUG("glEnable : GL_TEXTURE_2D"));
						}
						#endif

						glEnable(GL_TEXTURE_2D);

						#if(BSYS_OPENGL_DETAILLOG_ENABLE)
						{
							TAGLOG("gl",VASTRING_DEBUG("glActiveTexture : GL_TEXTURE%d",t_activetexture_id));
						}
						#endif

						glActiveTexture(t_activetexture);
				
						#if(BSYS_OPENGL_DETAILLOG_ENABLE)
						{
							TAGLOG("gl",VASTRING_DEBUG("glBindTexture : GL_TEXTURE_2D : texture_rawid = %d",t_texture_rawid.rawid));
						}
						#endif

						glBindTexture(GL_TEXTURE_2D,t_texture_rawid.rawid);
						this->current_texture_rawid = t_texture_rawid;

						#if(BSYS_OPENGL_DETAILLOG_ENABLE)
						{
							TAGLOG("gl",VASTRING_DEBUG("glUniform1i : location = %d : activetexture_id = %d",t_it->second.location,t_activetexture_id));
						}
						#endif

						glUniform1i(t_it->second.location,t_activetexture_id);
					}
				}else{
					ASSERT(0);
				}
			}else{
				ASSERT(0);
			}
		}
	}



	/** Render_DrawArray_Quads
	*/
	void Opengl_Impl::Render_DrawArray_Quads(s32 a_vertex_offset,s32 a_vertex_countof)
	{
		//AutoLock t_autolock(this->lockobject);
		
		{
			ASSERT((a_vertex_countof % 4) == 0);

			#if(BSYS_OPENGL_DETAILLOG_ENABLE)
			{
				TAGLOG("gl",VASTRING_DEBUG("glDrawArrays : GL_QUADS : vertex_offset = %d : vertex_countof = %d",a_vertex_offset,a_vertex_countof));
			}
			#endif

			glDrawArrays(GL_QUADS,a_vertex_offset,a_vertex_countof);
		}
	}

	/** Render_DrawFont_StartClear
	*/
	void Opengl_Impl::Render_DrawFont_StartClear()
	{
		AutoLock t_autolock(this->lockobject);

		{
			if(this->font != nullptr){
				this->font->ResetLock();
			}
		}
	}

	/** Render_DrawFont�B
	*/
	void Opengl_Impl::Render_DrawFont(const STLWString& a_string,f32 a_font_size,f32 a_x,f32 a_y,const NBsys::NColor::Color_F& a_color)
	{
		AutoLock t_autolock(this->lockobject);

		{
			if(this->font != nullptr){
				this->font->DrawFont(a_string,a_font_size,a_x,a_y,a_color);
			}
		}
	}

	/** Render_DrawRect�B
	*/
	void Opengl_Impl::Render_DrawRect(f32 a_x,f32 a_y,f32 a_w,f32 a_h,s32 a_textureid,const NBsys::NColor::Color_F& a_color)
	{
		AutoLock t_autolock(this->lockobject);

		{
			this->Render_SetTextureDirect(0,a_textureid);

			glBegin(GL_QUADS);
			{
				glColor4f(a_color.r,a_color.g,a_color.b,a_color.a);

				f32 t_rect_x0 = a_x;
				f32 t_rect_x1 = a_x + a_w;
				f32 t_rect_y0 = a_y;
				f32 t_rect_y1 = a_y + a_h;

				if(a_textureid < 0){
					glVertex2f(t_rect_x0,t_rect_y0);
					glVertex2f(t_rect_x1,t_rect_y0);
					glVertex2f(t_rect_x1,t_rect_y1);
					glVertex2f(t_rect_x0,t_rect_y1);
				}else{
					glTexCoord2f(0.0f,0.0f);
					glVertex2f(t_rect_x0,t_rect_y0);

					glTexCoord2f(1.0f,0.0f);
					glVertex2f(t_rect_x1,t_rect_y0);

					glTexCoord2f(1.0f,1.0f);
					glVertex2f(t_rect_x1,t_rect_y1);

					glTexCoord2f(0.0f,1.0f);
					glVertex2f(t_rect_x0,t_rect_y1);
				}
			}
			glEnd();
		}
	}

	#endif

}}
#endif

