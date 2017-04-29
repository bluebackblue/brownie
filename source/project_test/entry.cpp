

/**
 * Copyright (c) 2016 blueback
 * Released under the MIT License
 * https://github.com/bluebackblue/brownie/blob/master/LICENSE
 * http://bbbproject.sakura.ne.jp/wordpress/mitlicense
 * @brief エントリー。
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


//opengl
sharedptr< NBsys::NOpengl::Opengl >& OpenGL()
{
	static sharedptr< NBsys::NOpengl::Opengl > s_opengl;
	return s_opengl;
}


/** opengl_draw
*/
void opengl_draw()
{
	//通常カメラから。

	{
		//ビューポート。
		//this->viewport.Set_ViewPortMatrix(BSYS_OPENGL_SCREEN_W,BSYS_OPENGL_SCREEN_H);

		//プロジェクション。
		//this->projection.Set_PerspectiveProjectionMatrix(BSYS_OPENGL_SCREEN_W,BSYS_OPENGL_SCREEN_H,this->screen_fov_deg,this->screen_near,this->screen_far);

		//ビュー。
		//this->view.Set_ViewMatrix(this->camera_target,this->camera_position,this->camera_up);
	}

	{
		//ビューポート。
		//OpenGL()->Render_ViewPort(0,0,BSYS_OPENGL_SCREEN_W,BSYS_OPENGL_SCREEN_H);

		//プロジェクション。
		//OpenGL()->Render_SetProjectionMatrix(this->projection);

		//ビュー。
		//OpenGL()->Render_SetViewMatrix(this->view);

		//カラーマスク。
		//OpenGL()->Render_SetColorMask(true,true,true,true);

		//クリアカラー設定。
		OpenGL()->Render_SetClearColor(NBsys::NColor::Color_F(0.3f,0.3f,0.3f,1.0f));

		//クリア。デプス。カラー。
		OpenGL()->Render_ClearBuffer(true,true);

		//デプステスト。
		//OpenGL()->Render_SetDepthTest(true);

		//ワールドライン描画。
		OpenGL()->Render_DrawWorldLine();
	}


}

bool opengl_update(f32 a_delta,bool a_endrequest)
{
	if(a_endrequest == true){
		//中断。
		return false;
	}else{
		//継続。
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
}

